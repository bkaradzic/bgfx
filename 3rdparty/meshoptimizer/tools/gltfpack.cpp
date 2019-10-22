// gltfpack is part of meshoptimizer library; see meshoptimizer.h for version/license details
//
// gltfpack is a command-line tool that takes a glTF file as an input and can produce two types of files:
// - regular glb/gltf files that use data that has been optimized for GPU consumption using various cache optimizers
// and quantization
// - packed glb/gltf files that additionally use meshoptimizer codecs to reduce the size of vertex/index data; these
// files can be further compressed with deflate/etc.
//
// To load regular glb files, it should be sufficient to use a standard glTF loader (although note that these files
// use quantized position/texture coordinates that are technically invalid per spec; THREE.js and BabylonJS support
// these files out of the box).
// To load packed glb files, meshoptimizer vertex decoder needs to be integrated into the loader; demo/GLTFLoader.js
// contains a work-in-progress loader - please note that the extension specification isn't ready yet so the format
// will change!

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_NONSTDC_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#endif

#include "../src/meshoptimizer.h"

#include <algorithm>
#include <string>
#include <vector>

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cgltf.h"
#include "fast_obj.h"

struct Attr
{
	float f[4];
};

struct Stream
{
	cgltf_attribute_type type;
	int index;
	int target; // 0 = base mesh, 1+ = morph target

	std::vector<Attr> data;
};

struct Mesh
{
	cgltf_node* node;

	cgltf_material* material;
	cgltf_skin* skin;

	cgltf_primitive_type type;

	std::vector<Stream> streams;
	std::vector<unsigned int> indices;

	size_t targets;
	std::vector<float> target_weights;
	std::vector<const char*> target_names;
};

struct Settings
{
	int pos_bits;
	int tex_bits;
	int nrm_bits;
	bool nrm_unit;

	int anim_freq;
	bool anim_const;

	bool keep_named;

	float simplify_threshold;
	bool simplify_aggressive;

	bool compress;
	bool fallback;

	int verbose;
};

struct QuantizationParams
{
	float pos_offset[3];
	float pos_scale;
	int pos_bits;

	float uv_offset[2];
	float uv_scale[2];
	int uv_bits;
};

struct StreamFormat
{
	cgltf_type type;
	cgltf_component_type component_type;
	bool normalized;
	size_t stride;
};

struct NodeInfo
{
	bool keep;
	bool animated;

	unsigned int animated_paths;

	int remap;
	std::vector<size_t> meshes;
};

struct MaterialInfo
{
	bool keep;

	int remap;
};

struct BufferView
{
	enum Kind
	{
		Kind_Vertex,
		Kind_Index,
		Kind_Skin,
		Kind_Time,
		Kind_Keyframe,
		Kind_Image,
		Kind_Count
	};

	Kind kind;
	int variant;
	size_t stride;
	bool compressed;

	std::string data;

	size_t bytes;
};

const char* getError(cgltf_result result)
{
	switch (result)
	{
	case cgltf_result_file_not_found:
		return "file not found";

	case cgltf_result_io_error:
		return "I/O error";

	case cgltf_result_invalid_json:
		return "invalid JSON";

	case cgltf_result_invalid_gltf:
		return "invalid GLTF";

	case cgltf_result_out_of_memory:
		return "out of memory";

	default:
		return "unknown error";
	}
}

cgltf_accessor* getAccessor(const cgltf_attribute* attributes, size_t attribute_count, cgltf_attribute_type type, int index = 0)
{
	for (size_t i = 0; i < attribute_count; ++i)
		if (attributes[i].type == type && attributes[i].index == index)
			return attributes[i].data;

	return 0;
}

void readAccessor(std::vector<float>& data, const cgltf_accessor* accessor)
{
	assert(accessor->type == cgltf_type_scalar);

	data.resize(accessor->count);
	cgltf_accessor_unpack_floats(accessor, &data[0], data.size());
}

void readAccessor(std::vector<Attr>& data, const cgltf_accessor* accessor)
{
	size_t components = cgltf_num_components(accessor->type);

	std::vector<float> temp(accessor->count * components);
	cgltf_accessor_unpack_floats(accessor, &temp[0], temp.size());

	data.resize(accessor->count);

	for (size_t i = 0; i < accessor->count; ++i)
	{
		for (size_t k = 0; k < components && k < 4; ++k)
			data[i].f[k] = temp[i * components + k];
	}
}

void transformPosition(float* ptr, const float* transform)
{
	float x = ptr[0] * transform[0] + ptr[1] * transform[4] + ptr[2] * transform[8] + transform[12];
	float y = ptr[0] * transform[1] + ptr[1] * transform[5] + ptr[2] * transform[9] + transform[13];
	float z = ptr[0] * transform[2] + ptr[1] * transform[6] + ptr[2] * transform[10] + transform[14];

	ptr[0] = x;
	ptr[1] = y;
	ptr[2] = z;
}

void transformNormal(float* ptr, const float* transform)
{
	float x = ptr[0] * transform[0] + ptr[1] * transform[4] + ptr[2] * transform[8];
	float y = ptr[0] * transform[1] + ptr[1] * transform[5] + ptr[2] * transform[9];
	float z = ptr[0] * transform[2] + ptr[1] * transform[6] + ptr[2] * transform[10];

	float l = sqrtf(x * x + y * y + z * z);
	float s = (l == 0.f) ? 0.f : 1 / l;

	ptr[0] = x * s;
	ptr[1] = y * s;
	ptr[2] = z * s;
}

void transformMesh(Mesh& mesh, const cgltf_node* node)
{
	float transform[16];
	cgltf_node_transform_world(node, transform);

	for (size_t si = 0; si < mesh.streams.size(); ++si)
	{
		Stream& stream = mesh.streams[si];

		if (stream.type == cgltf_attribute_type_position)
		{
			for (size_t i = 0; i < stream.data.size(); ++i)
				transformPosition(stream.data[i].f, transform);
		}
		else if (stream.type == cgltf_attribute_type_normal || stream.type == cgltf_attribute_type_tangent)
		{
			for (size_t i = 0; i < stream.data.size(); ++i)
				transformNormal(stream.data[i].f, transform);
		}
	}
}

void parseMeshesGltf(cgltf_data* data, std::vector<Mesh>& meshes)
{
	for (size_t ni = 0; ni < data->nodes_count; ++ni)
	{
		cgltf_node& node = data->nodes[ni];

		if (!node.mesh)
			continue;

		const cgltf_mesh& mesh = *node.mesh;
		int mesh_id = int(&mesh - data->meshes);

		for (size_t pi = 0; pi < mesh.primitives_count; ++pi)
		{
			const cgltf_primitive& primitive = mesh.primitives[pi];

			if (primitive.type != cgltf_primitive_type_triangles && primitive.type != cgltf_primitive_type_points)
			{
				fprintf(stderr, "Warning: ignoring primitive %d of mesh %d because type %d is not supported\n", int(pi), mesh_id, primitive.type);
				continue;
			}

			if (primitive.type == cgltf_primitive_type_points && primitive.indices)
			{
				fprintf(stderr, "Warning: ignoring primitive %d of mesh %d because indexed points are not supported\n", int(pi), mesh_id);
				continue;
			}

			Mesh result;

			result.node = &node;

			result.material = primitive.material;
			result.skin = node.skin;

			result.type = primitive.type;

			if (primitive.indices)
			{
				result.indices.resize(primitive.indices->count);
				for (size_t i = 0; i < primitive.indices->count; ++i)
					result.indices[i] = unsigned(cgltf_accessor_read_index(primitive.indices, i));
			}
			else if (primitive.type != cgltf_primitive_type_points)
			{
				size_t count = primitive.attributes ? primitive.attributes[0].data->count : 0;

				// note, while we could generate a good index buffer, reindexMesh will take care of this
				result.indices.resize(count);
				for (size_t i = 0; i < count; ++i)
					result.indices[i] = unsigned(i);
			}

			for (size_t ai = 0; ai < primitive.attributes_count; ++ai)
			{
				const cgltf_attribute& attr = primitive.attributes[ai];

				if (attr.type == cgltf_attribute_type_invalid)
				{
					fprintf(stderr, "Warning: ignoring unknown attribute %s in primitive %d of mesh %d\n", attr.name, int(pi), mesh_id);
					continue;
				}

				Stream s = {attr.type, attr.index};
				readAccessor(s.data, attr.data);

				result.streams.push_back(s);
			}

			for (size_t ti = 0; ti < primitive.targets_count; ++ti)
			{
				const cgltf_morph_target& target = primitive.targets[ti];

				for (size_t ai = 0; ai < target.attributes_count; ++ai)
				{
					const cgltf_attribute& attr = target.attributes[ai];

					if (attr.type == cgltf_attribute_type_invalid)
					{
						fprintf(stderr, "Warning: ignoring unknown attribute %s in morph target %d of primitive %d of mesh %d\n", attr.name, int(ti), int(pi), mesh_id);
						continue;
					}

					Stream s = {attr.type, attr.index, int(ti + 1)};
					readAccessor(s.data, attr.data);

					result.streams.push_back(s);
				}
			}

			result.targets = primitive.targets_count;
			result.target_weights.assign(mesh.weights, mesh.weights + mesh.weights_count);
			result.target_names.assign(mesh.target_names, mesh.target_names + mesh.target_names_count);

			meshes.push_back(result);
		}
	}
}

void defaultFree(void*, void* p)
{
	free(p);
}

int textureIndex(const std::vector<std::string>& textures, const char* name)
{
	for (size_t i = 0; i < textures.size(); ++i)
		if (textures[i] == name)
			return int(i);

	return -1;
}

cgltf_data* parseSceneObj(fastObjMesh* obj)
{
	cgltf_data* data = (cgltf_data*)calloc(1, sizeof(cgltf_data));
	data->memory_free = defaultFree;

	std::vector<std::string> textures;

	for (unsigned int mi = 0; mi < obj->material_count; ++mi)
	{
		fastObjMaterial& om = obj->materials[mi];

		if (om.map_Kd.name && textureIndex(textures, om.map_Kd.name) < 0)
			textures.push_back(om.map_Kd.name);
	}

	data->images = (cgltf_image*)calloc(textures.size(), sizeof(cgltf_image));
	data->images_count = textures.size();

	for (size_t i = 0; i < textures.size(); ++i)
	{
		data->images[i].uri = strdup(textures[i].c_str());
	}

	data->textures = (cgltf_texture*)calloc(textures.size(), sizeof(cgltf_texture));
	data->textures_count = textures.size();

	for (size_t i = 0; i < textures.size(); ++i)
	{
		data->textures[i].image = &data->images[i];
	}

	data->materials = (cgltf_material*)calloc(obj->material_count, sizeof(cgltf_material));
	data->materials_count = obj->material_count;

	for (unsigned int mi = 0; mi < obj->material_count; ++mi)
	{
		cgltf_material& gm = data->materials[mi];
		fastObjMaterial& om = obj->materials[mi];

		gm.has_pbr_metallic_roughness = true;
		gm.pbr_metallic_roughness.base_color_factor[0] = 1.0f;
		gm.pbr_metallic_roughness.base_color_factor[1] = 1.0f;
		gm.pbr_metallic_roughness.base_color_factor[2] = 1.0f;
		gm.pbr_metallic_roughness.base_color_factor[3] = 1.0f;
		gm.pbr_metallic_roughness.metallic_factor = 0.0f;
		gm.pbr_metallic_roughness.roughness_factor = 1.0f;

		gm.alpha_cutoff = 0.5f;

		if (om.map_Kd.name)
		{
			gm.pbr_metallic_roughness.base_color_texture.texture = &data->textures[textureIndex(textures, om.map_Kd.name)];
			gm.pbr_metallic_roughness.base_color_texture.scale = 1.0f;

			gm.alpha_mode = (om.illum == 4 || om.illum == 6 || om.illum == 7 || om.illum == 9) ? cgltf_alpha_mode_mask : cgltf_alpha_mode_opaque;
		}

		if (om.map_d.name)
		{
			gm.alpha_mode = cgltf_alpha_mode_blend;
		}
	}

	return data;
}

void parseMeshesObj(fastObjMesh* obj, cgltf_data* data, std::vector<Mesh>& meshes)
{
	unsigned int material_count = std::max(obj->material_count, 1u);

	std::vector<size_t> vertex_count(material_count);
	std::vector<size_t> index_count(material_count);

	for (unsigned int fi = 0; fi < obj->face_count; ++fi)
	{
		unsigned int mi = obj->face_materials[fi];

		vertex_count[mi] += obj->face_vertices[fi];
		index_count[mi] += (obj->face_vertices[fi] - 2) * 3;
	}

	std::vector<size_t> mesh_index(material_count);

	for (unsigned int mi = 0; mi < material_count; ++mi)
	{
		if (index_count[mi] == 0)
			continue;

		mesh_index[mi] = meshes.size();

		meshes.push_back(Mesh());

		Mesh& mesh = meshes.back();

		if (data->materials_count)
		{
			assert(mi < data->materials_count);
			mesh.material = &data->materials[mi];
		}

		mesh.type = cgltf_primitive_type_triangles;

		mesh.streams.resize(3);
		mesh.streams[0].type = cgltf_attribute_type_position;
		mesh.streams[0].data.resize(vertex_count[mi]);
		mesh.streams[1].type = cgltf_attribute_type_normal;
		mesh.streams[1].data.resize(vertex_count[mi]);
		mesh.streams[2].type = cgltf_attribute_type_texcoord;
		mesh.streams[2].data.resize(vertex_count[mi]);
		mesh.indices.resize(index_count[mi]);
		mesh.targets = 0;
	}

	std::vector<size_t> vertex_offset(material_count);
	std::vector<size_t> index_offset(material_count);

	size_t group_offset = 0;

	for (unsigned int fi = 0; fi < obj->face_count; ++fi)
	{
		unsigned int mi = obj->face_materials[fi];
		Mesh& mesh = meshes[mesh_index[mi]];

		size_t vo = vertex_offset[mi];
		size_t io = index_offset[mi];

		for (unsigned int vi = 0; vi < obj->face_vertices[fi]; ++vi)
		{
			fastObjIndex ii = obj->indices[group_offset + vi];

			Attr p = {{obj->positions[ii.p * 3 + 0], obj->positions[ii.p * 3 + 1], obj->positions[ii.p * 3 + 2]}};
			Attr n = {{obj->normals[ii.n * 3 + 0], obj->normals[ii.n * 3 + 1], obj->normals[ii.n * 3 + 2]}};
			Attr t = {{obj->texcoords[ii.t * 2 + 0], 1.f - obj->texcoords[ii.t * 2 + 1]}};

			mesh.streams[0].data[vo + vi] = p;
			mesh.streams[1].data[vo + vi] = n;
			mesh.streams[2].data[vo + vi] = t;
		}

		for (unsigned int vi = 2; vi < obj->face_vertices[fi]; ++vi)
		{
			size_t to = io + (vi - 2) * 3;

			mesh.indices[to + 0] = unsigned(vo);
			mesh.indices[to + 1] = unsigned(vo + vi - 1);
			mesh.indices[to + 2] = unsigned(vo + vi);
		}

		vertex_offset[mi] += obj->face_vertices[fi];
		index_offset[mi] += (obj->face_vertices[fi] - 2) * 3;
		group_offset += obj->face_vertices[fi];
	}
}

bool areTextureViewsEqual(const cgltf_texture_view& lhs, const cgltf_texture_view& rhs)
{
	if (lhs.has_transform != rhs.has_transform)
		return false;

	if (lhs.has_transform)
	{
		const cgltf_texture_transform& lt = lhs.transform;
		const cgltf_texture_transform& rt = rhs.transform;

		if (memcmp(lt.offset, rt.offset, sizeof(cgltf_float) * 2) != 0)
			return false;

		if (lt.rotation != rt.rotation)
			return false;

		if (memcmp(lt.scale, rt.scale, sizeof(cgltf_float) * 2) != 0)
			return false;

		if (lt.texcoord != rt.texcoord)
			return false;
	}

	if (lhs.texture != rhs.texture)
		return false;

	if (lhs.texcoord != rhs.texcoord)
		return false;

	if (lhs.scale != rhs.scale)
		return false;

	return true;
}

bool areMaterialsEqual(const cgltf_material& lhs, const cgltf_material& rhs)
{
	if (lhs.has_pbr_metallic_roughness != rhs.has_pbr_metallic_roughness)
		return false;

	if (lhs.has_pbr_metallic_roughness)
	{
		const cgltf_pbr_metallic_roughness& lpbr = lhs.pbr_metallic_roughness;
		const cgltf_pbr_metallic_roughness& rpbr = rhs.pbr_metallic_roughness;

		if (!areTextureViewsEqual(lpbr.base_color_texture, rpbr.base_color_texture))
			return false;

		if (!areTextureViewsEqual(lpbr.metallic_roughness_texture, rpbr.metallic_roughness_texture))
			return false;

		if (memcmp(lpbr.base_color_factor, rpbr.base_color_factor, sizeof(cgltf_float) * 4) != 0)
			return false;

		if (lpbr.metallic_factor != rpbr.metallic_factor)
			return false;

		if (lpbr.roughness_factor != rpbr.roughness_factor)
			return false;
	}

	if (lhs.has_pbr_specular_glossiness != rhs.has_pbr_specular_glossiness)
		return false;

	if (lhs.has_pbr_specular_glossiness)
	{
		const cgltf_pbr_specular_glossiness& lpbr = lhs.pbr_specular_glossiness;
		const cgltf_pbr_specular_glossiness& rpbr = rhs.pbr_specular_glossiness;

		if (!areTextureViewsEqual(lpbr.diffuse_texture, rpbr.diffuse_texture))
			return false;

		if (!areTextureViewsEqual(lpbr.specular_glossiness_texture, rpbr.specular_glossiness_texture))
			return false;

		if (memcmp(lpbr.diffuse_factor, rpbr.diffuse_factor, sizeof(cgltf_float) * 4) != 0)
			return false;

		if (memcmp(lpbr.specular_factor, rpbr.specular_factor, sizeof(cgltf_float) * 3) != 0)
			return false;

		if (lpbr.glossiness_factor != rpbr.glossiness_factor)
			return false;
	}

	if (!areTextureViewsEqual(lhs.normal_texture, rhs.normal_texture))
		return false;

	if (!areTextureViewsEqual(lhs.occlusion_texture, rhs.occlusion_texture))
		return false;

	if (!areTextureViewsEqual(lhs.emissive_texture, rhs.emissive_texture))
		return false;

	if (memcmp(lhs.emissive_factor, rhs.emissive_factor, sizeof(cgltf_float) * 3) != 0)
		return false;

	if (lhs.alpha_mode != rhs.alpha_mode)
		return false;

	if (lhs.alpha_cutoff != rhs.alpha_cutoff)
		return false;

	if (lhs.double_sided != rhs.double_sided)
		return false;

	if (lhs.unlit != rhs.unlit)
		return false;

	return true;
}

void mergeMeshMaterials(cgltf_data* data, std::vector<Mesh>& meshes)
{
	for (size_t i = 0; i < meshes.size(); ++i)
	{
		Mesh& mesh = meshes[i];

		if (!mesh.material)
			continue;

		for (int j = 0; j < mesh.material - data->materials; ++j)
		{
			if (areMaterialsEqual(*mesh.material, data->materials[j]))
			{
				mesh.material = &data->materials[j];
				break;
			}
		}
	}
}

bool compareMeshTargets(const Mesh& lhs, const Mesh& rhs)
{
	if (lhs.targets != rhs.targets)
		return false;

	if (lhs.target_weights.size() != rhs.target_weights.size())
		return false;

	for (size_t i = 0; i < lhs.target_weights.size(); ++i)
		if (lhs.target_weights[i] != rhs.target_weights[i])
			return false;

	if (lhs.target_names.size() != rhs.target_names.size())
		return false;

	for (size_t i = 0; i < lhs.target_names.size(); ++i)
		if (strcmp(lhs.target_names[i], rhs.target_names[i]) != 0)
			return false;

	return true;
}

bool canMergeMeshes(const Mesh& lhs, const Mesh& rhs, const Settings& settings)
{
	if (lhs.node != rhs.node)
	{
		if (!lhs.node || !rhs.node)
			return false;

		if (lhs.node->parent != rhs.node->parent)
			return false;

		bool lhs_transform = lhs.node->has_translation | lhs.node->has_rotation | lhs.node->has_scale | lhs.node->has_matrix | (!!lhs.node->weights);
		bool rhs_transform = rhs.node->has_translation | rhs.node->has_rotation | rhs.node->has_scale | rhs.node->has_matrix | (!!rhs.node->weights);

		if (lhs_transform || rhs_transform)
			return false;

		if (settings.keep_named)
		{
			if (lhs.node->name && *lhs.node->name)
				return false;

			if (rhs.node->name && *rhs.node->name)
				return false;
		}

		// we can merge nodes that don't have transforms of their own and have the same parent
		// this is helpful when instead of splitting mesh into primitives, DCCs split mesh into mesh nodes
	}

	if (lhs.material != rhs.material)
		return false;

	if (lhs.skin != rhs.skin)
		return false;

	if (lhs.type != rhs.type)
		return false;

	if (!compareMeshTargets(lhs, rhs))
		return false;

	if (lhs.indices.empty() != rhs.indices.empty())
		return false;

	if (lhs.streams.size() != rhs.streams.size())
		return false;

	for (size_t i = 0; i < lhs.streams.size(); ++i)
		if (lhs.streams[i].type != rhs.streams[i].type || lhs.streams[i].index != rhs.streams[i].index || lhs.streams[i].target != rhs.streams[i].target)
			return false;

	return true;
}

void mergeMeshes(Mesh& target, const Mesh& mesh)
{
	assert(target.streams.size() == mesh.streams.size());

	size_t vertex_offset = target.streams[0].data.size();
	size_t index_offset = target.indices.size();

	for (size_t i = 0; i < target.streams.size(); ++i)
		target.streams[i].data.insert(target.streams[i].data.end(), mesh.streams[i].data.begin(), mesh.streams[i].data.end());

	target.indices.resize(target.indices.size() + mesh.indices.size());

	size_t index_count = mesh.indices.size();

	for (size_t i = 0; i < index_count; ++i)
		target.indices[index_offset + i] = unsigned(vertex_offset + mesh.indices[i]);
}

void mergeMeshes(std::vector<Mesh>& meshes, const Settings& settings)
{
	size_t write = 0;

	for (size_t i = 0; i < meshes.size(); ++i)
	{
		if (meshes[i].streams.empty())
			continue;

		Mesh& target = meshes[write];

		if (i != write)
		{
			Mesh& mesh = meshes[i];

			// note: this copy is expensive; we could use move in C++11 or swap manually which is a bit painful...
			target = mesh;

			mesh.streams.clear();
			mesh.indices.clear();
		}

		size_t target_vertices = target.streams[0].data.size();
		size_t target_indices = target.indices.size();

		for (size_t j = i + 1; j < meshes.size(); ++j)
		{
			Mesh& mesh = meshes[j];

			if (!mesh.streams.empty() && canMergeMeshes(target, mesh, settings))
			{
				target_vertices += mesh.streams[0].data.size();
				target_indices += mesh.indices.size();
			}
		}

		for (size_t j = 0; j < target.streams.size(); ++j)
			target.streams[j].data.reserve(target_vertices);

		target.indices.reserve(target_indices);

		for (size_t j = i + 1; j < meshes.size(); ++j)
		{
			Mesh& mesh = meshes[j];

			if (!mesh.streams.empty() && canMergeMeshes(target, mesh, settings))
			{
				mergeMeshes(target, mesh);

				mesh.streams.clear();
				mesh.indices.clear();
			}
		}

		assert(target.streams[0].data.size() == target_vertices);
		assert(target.indices.size() == target_indices);

		write++;
	}

	meshes.resize(write);
}

void reindexMesh(Mesh& mesh)
{
	size_t total_vertices = mesh.streams[0].data.size();
	size_t total_indices = mesh.indices.size();

	std::vector<meshopt_Stream> streams;
	for (size_t i = 0; i < mesh.streams.size(); ++i)
	{
		if (mesh.streams[i].target)
			continue;

		assert(mesh.streams[i].data.size() == total_vertices);

		meshopt_Stream stream = {&mesh.streams[i].data[0], sizeof(Attr), sizeof(Attr)};
		streams.push_back(stream);
	}

	std::vector<unsigned int> remap(total_vertices);
	size_t unique_vertices = meshopt_generateVertexRemapMulti(&remap[0], &mesh.indices[0], total_indices, total_vertices, &streams[0], streams.size());
	assert(unique_vertices <= total_vertices);

	meshopt_remapIndexBuffer(&mesh.indices[0], &mesh.indices[0], total_indices, &remap[0]);

	for (size_t i = 0; i < mesh.streams.size(); ++i)
	{
		assert(mesh.streams[i].data.size() == total_vertices);

		meshopt_remapVertexBuffer(&mesh.streams[i].data[0], &mesh.streams[i].data[0], total_vertices, sizeof(Attr), &remap[0]);
		mesh.streams[i].data.resize(unique_vertices);
	}
}

Stream* getStream(Mesh& mesh, cgltf_attribute_type type)
{
	for (size_t i = 0; i < mesh.streams.size(); ++i)
		if (mesh.streams[i].type == type)
			return &mesh.streams[i];

	return 0;
}

void simplifyMesh(Mesh& mesh, float threshold, bool aggressive)
{
	if (threshold >= 1)
		return;

	const Stream* positions = getStream(mesh, cgltf_attribute_type_position);
	if (!positions)
		return;

	size_t vertex_count = mesh.streams[0].data.size();

	size_t target_index_count = size_t(double(mesh.indices.size() / 3) * threshold) * 3;
	float target_error = 1e-2f;

	if (target_index_count < 1)
		return;

	std::vector<unsigned int> indices(mesh.indices.size());
	indices.resize(meshopt_simplify(&indices[0], &mesh.indices[0], mesh.indices.size(), positions->data[0].f, vertex_count, sizeof(Attr), target_index_count, target_error));
	mesh.indices.swap(indices);

	// Note: if the simplifier got stuck, we can try to reindex without normals/tangents and retry
	// For now we simply fall back to aggressive simplifier instead

	// if the mesh is complex enough and the precise simplifier got "stuck", we'll try to simplify using the sloppy simplifier which is guaranteed to reach the target count
	if (aggressive && target_index_count > 50 * 3 && mesh.indices.size() > target_index_count)
	{
		indices.resize(meshopt_simplifySloppy(&indices[0], &mesh.indices[0], mesh.indices.size(), positions->data[0].f, vertex_count, sizeof(Attr), target_index_count));
		mesh.indices.swap(indices);
	}
}

void optimizeMesh(Mesh& mesh)
{
	size_t vertex_count = mesh.streams[0].data.size();

	meshopt_optimizeVertexCache(&mesh.indices[0], &mesh.indices[0], mesh.indices.size(), vertex_count);

	std::vector<unsigned int> remap(vertex_count);
	size_t unique_vertices = meshopt_optimizeVertexFetchRemap(&remap[0], &mesh.indices[0], mesh.indices.size(), vertex_count);
	assert(unique_vertices <= vertex_count);

	meshopt_remapIndexBuffer(&mesh.indices[0], &mesh.indices[0], mesh.indices.size(), &remap[0]);

	for (size_t i = 0; i < mesh.streams.size(); ++i)
	{
		assert(mesh.streams[i].data.size() == vertex_count);

		meshopt_remapVertexBuffer(&mesh.streams[i].data[0], &mesh.streams[i].data[0], vertex_count, sizeof(Attr), &remap[0]);
		mesh.streams[i].data.resize(unique_vertices);
	}
}

struct BoneInfluence
{
	float i;
	float w;

	bool operator<(const BoneInfluence& other) const
	{
		return i < other.i;
	}
};

void sortBoneInfluences(Mesh& mesh)
{
	Stream* joints = getStream(mesh, cgltf_attribute_type_joints);
	Stream* weights = getStream(mesh, cgltf_attribute_type_weights);

	if (!joints || !weights)
		return;

	size_t vertex_count = mesh.streams[0].data.size();

	for (size_t i = 0; i < vertex_count; ++i)
	{
		Attr& ja = joints->data[i];
		Attr& wa = weights->data[i];

		BoneInfluence inf[4] = {};
		int count = 0;

		for (int k = 0; k < 4; ++k)
			if (wa.f[k] > 0.f)
			{
				inf[count].i = ja.f[k];
				inf[count].w = wa.f[k];
				count++;
			}

		std::sort(inf, inf + count);

		for (int k = 0; k < 4; ++k)
		{
			ja.f[k] = inf[k].i;
			wa.f[k] = inf[k].w;
		}
	}
}

void simplifyPointMesh(Mesh& mesh, float threshold)
{
	if (threshold >= 1)
		return;

	const Stream* positions = getStream(mesh, cgltf_attribute_type_position);
	if (!positions)
		return;

	size_t vertex_count = mesh.streams[0].data.size();

	size_t target_vertex_count = size_t(double(vertex_count) * threshold);

	if (target_vertex_count < 1)
		return;

	std::vector<unsigned int> indices(target_vertex_count);
	indices.resize(meshopt_simplifyPoints(&indices[0], positions->data[0].f, vertex_count, sizeof(Attr), target_vertex_count));

	std::vector<Attr> scratch(indices.size());

	for (size_t i = 0; i < mesh.streams.size(); ++i)
	{
		std::vector<Attr>& data = mesh.streams[i].data;

		assert(data.size() == vertex_count);

		for (size_t j = 0; j < indices.size(); ++j)
			scratch[j] = data[indices[j]];

		data = scratch;
	}
}

void sortPointMesh(Mesh& mesh)
{
	const Stream* positions = getStream(mesh, cgltf_attribute_type_position);
	if (!positions)
		return;

	size_t vertex_count = mesh.streams[0].data.size();

	std::vector<unsigned int> remap(vertex_count);
	meshopt_spatialSortRemap(&remap[0], positions->data[0].f, vertex_count, sizeof(Attr));

	for (size_t i = 0; i < mesh.streams.size(); ++i)
	{
		assert(mesh.streams[i].data.size() == vertex_count);

		meshopt_remapVertexBuffer(&mesh.streams[i].data[0], &mesh.streams[i].data[0], vertex_count, sizeof(Attr), &remap[0]);
	}
}

bool getAttributeBounds(const std::vector<Mesh>& meshes, cgltf_attribute_type type, Attr& min, Attr& max)
{
	min.f[0] = min.f[1] = min.f[2] = min.f[3] = +FLT_MAX;
	max.f[0] = max.f[1] = max.f[2] = max.f[3] = -FLT_MAX;

	Attr pad = {};

	bool valid = false;

	for (size_t i = 0; i < meshes.size(); ++i)
	{
		const Mesh& mesh = meshes[i];

		for (size_t j = 0; j < mesh.streams.size(); ++j)
		{
			const Stream& s = mesh.streams[j];

			if (s.type == type)
			{
				if (s.target == 0)
				{
					for (size_t k = 0; k < s.data.size(); ++k)
					{
						const Attr& a = s.data[k];

						min.f[0] = std::min(min.f[0], a.f[0]);
						min.f[1] = std::min(min.f[1], a.f[1]);
						min.f[2] = std::min(min.f[2], a.f[2]);
						min.f[3] = std::min(min.f[3], a.f[3]);

						max.f[0] = std::max(max.f[0], a.f[0]);
						max.f[1] = std::max(max.f[1], a.f[1]);
						max.f[2] = std::max(max.f[2], a.f[2]);
						max.f[3] = std::max(max.f[3], a.f[3]);

						valid = true;
					}
				}
				else
				{
					for (size_t k = 0; k < s.data.size(); ++k)
					{
						const Attr& a = s.data[k];

						pad.f[0] = std::max(pad.f[0], fabsf(a.f[0]));
						pad.f[1] = std::max(pad.f[1], fabsf(a.f[1]));
						pad.f[2] = std::max(pad.f[2], fabsf(a.f[2]));
						pad.f[3] = std::max(pad.f[3], fabsf(a.f[3]));
					}
				}
			}
		}
	}

	if (valid)
	{
		for (int k = 0; k < 4; ++k)
		{
			min.f[k] -= pad.f[k];
			max.f[k] += pad.f[k];
		}
	}

	return valid;
}

QuantizationParams prepareQuantization(const std::vector<Mesh>& meshes, const Settings& settings)
{
	QuantizationParams result = {};

	result.pos_bits = settings.pos_bits;

	Attr pos_min, pos_max;
	if (getAttributeBounds(meshes, cgltf_attribute_type_position, pos_min, pos_max))
	{
		result.pos_offset[0] = pos_min.f[0];
		result.pos_offset[1] = pos_min.f[1];
		result.pos_offset[2] = pos_min.f[2];
		result.pos_scale = std::max(pos_max.f[0] - pos_min.f[0], std::max(pos_max.f[1] - pos_min.f[1], pos_max.f[2] - pos_min.f[2]));
	}

	result.uv_bits = settings.tex_bits;

	Attr uv_min, uv_max;
	if (getAttributeBounds(meshes, cgltf_attribute_type_texcoord, uv_min, uv_max))
	{
		result.uv_offset[0] = uv_min.f[0];
		result.uv_offset[1] = uv_min.f[1];
		result.uv_scale[0] = uv_max.f[0] - uv_min.f[0];
		result.uv_scale[1] = uv_max.f[1] - uv_min.f[1];
	}

	return result;
}

void rescaleNormal(float& nx, float& ny, float& nz)
{
	// scale the normal to make sure the largest component is +-1.0
	// this reduces the entropy of the normal by ~1.5 bits without losing precision
	// it's better to use octahedral encoding but that requires special shader support
	float nm = std::max(fabsf(nx), std::max(fabsf(ny), fabsf(nz)));
	float ns = nm == 0.f ? 0.f : 1 / nm;

	nx *= ns;
	ny *= ns;
	nz *= ns;
}

void renormalizeWeights(uint8_t (&w)[4])
{
	int sum = w[0] + w[1] + w[2] + w[3];

	if (sum == 255)
		return;

	// we assume that the total error is limited to 0.5/component = 2
	// this means that it's acceptable to adjust the max. component to compensate for the error
	int max = 0;

	for (int k = 1; k < 4; ++k)
		if (w[k] > w[max])
			max = k;

	w[max] += uint8_t(255 - sum);
}

StreamFormat writeVertexStream(std::string& bin, const Stream& stream, const QuantizationParams& params, const Settings& settings, bool has_targets)
{
	if (stream.type == cgltf_attribute_type_position)
	{
		if (stream.target == 0)
		{
			float pos_rscale = params.pos_scale == 0.f ? 0.f : 1.f / params.pos_scale;

			for (size_t i = 0; i < stream.data.size(); ++i)
			{
				const Attr& a = stream.data[i];

				uint16_t v[4] = {
				    uint16_t(meshopt_quantizeUnorm((a.f[0] - params.pos_offset[0]) * pos_rscale, params.pos_bits)),
				    uint16_t(meshopt_quantizeUnorm((a.f[1] - params.pos_offset[1]) * pos_rscale, params.pos_bits)),
				    uint16_t(meshopt_quantizeUnorm((a.f[2] - params.pos_offset[2]) * pos_rscale, params.pos_bits)),
				    0};
				bin.append(reinterpret_cast<const char*>(v), sizeof(v));
			}

			StreamFormat format = {cgltf_type_vec3, cgltf_component_type_r_16u, false, 8};
			return format;
		}
		else
		{
			float pos_rscale = params.pos_scale == 0.f ? 0.f : 1.f / params.pos_scale;

			for (size_t i = 0; i < stream.data.size(); ++i)
			{
				const Attr& a = stream.data[i];

				int16_t v[4] = {
				    int16_t((a.f[0] >= 0.f ? 1 : -1) * meshopt_quantizeUnorm(fabsf(a.f[0]) * pos_rscale, params.pos_bits)),
				    int16_t((a.f[1] >= 0.f ? 1 : -1) * meshopt_quantizeUnorm(fabsf(a.f[1]) * pos_rscale, params.pos_bits)),
				    int16_t((a.f[2] >= 0.f ? 1 : -1) * meshopt_quantizeUnorm(fabsf(a.f[2]) * pos_rscale, params.pos_bits)),
				    0};
				bin.append(reinterpret_cast<const char*>(v), sizeof(v));
			}

			StreamFormat format = {cgltf_type_vec3, cgltf_component_type_r_16, false, 8};
			return format;
		}
	}
	else if (stream.type == cgltf_attribute_type_texcoord)
	{
		float uv_rscale[2] = {
		    params.uv_scale[0] == 0.f ? 0.f : 1.f / params.uv_scale[0],
		    params.uv_scale[1] == 0.f ? 0.f : 1.f / params.uv_scale[1],
		};

		for (size_t i = 0; i < stream.data.size(); ++i)
		{
			const Attr& a = stream.data[i];

			uint16_t v[2] = {
			    uint16_t(meshopt_quantizeUnorm((a.f[0] - params.uv_offset[0]) * uv_rscale[0], params.uv_bits)),
			    uint16_t(meshopt_quantizeUnorm((a.f[1] - params.uv_offset[1]) * uv_rscale[1], params.uv_bits)),
			};
			bin.append(reinterpret_cast<const char*>(v), sizeof(v));
		}

		StreamFormat format = {cgltf_type_vec2, cgltf_component_type_r_16u, false, 4};
		return format;
	}
	else if (stream.type == cgltf_attribute_type_normal)
	{
		bool nrm_unit = has_targets || settings.nrm_unit;
		int bits = nrm_unit ? (settings.nrm_bits > 8 ? 16 : 8) : settings.nrm_bits;

		for (size_t i = 0; i < stream.data.size(); ++i)
		{
			const Attr& a = stream.data[i];

			float nx = a.f[0], ny = a.f[1], nz = a.f[2];

			if (!nrm_unit)
				rescaleNormal(nx, ny, nz);

			if (bits > 8)
			{
				int16_t v[4] = {
				    int16_t(meshopt_quantizeSnorm(nx, bits)),
				    int16_t(meshopt_quantizeSnorm(ny, bits)),
				    int16_t(meshopt_quantizeSnorm(nz, bits)),
				    0};
				bin.append(reinterpret_cast<const char*>(v), sizeof(v));
			}
			else
			{
				int8_t v[4] = {
				    int8_t(meshopt_quantizeSnorm(nx, bits)),
				    int8_t(meshopt_quantizeSnorm(ny, bits)),
				    int8_t(meshopt_quantizeSnorm(nz, bits)),
				    0};
				bin.append(reinterpret_cast<const char*>(v), sizeof(v));
			}
		}

		if (bits > 8)
		{
			StreamFormat format = {cgltf_type_vec3, cgltf_component_type_r_16, true, 8};
			return format;
		}
		else
		{
			StreamFormat format = {cgltf_type_vec3, cgltf_component_type_r_8, true, 4};
			return format;
		}
	}
	else if (stream.type == cgltf_attribute_type_tangent)
	{
		bool nrm_unit = has_targets || settings.nrm_unit;
		int bits = nrm_unit ? (settings.nrm_bits > 8 ? 16 : 8) : settings.nrm_bits;

		for (size_t i = 0; i < stream.data.size(); ++i)
		{
			const Attr& a = stream.data[i];

			float nx = a.f[0], ny = a.f[1], nz = a.f[2], nw = a.f[3];

			if (!nrm_unit)
				rescaleNormal(nx, ny, nz);

			if (bits > 8)
			{
				int16_t v[4] = {
				    int16_t(meshopt_quantizeSnorm(nx, bits)),
				    int16_t(meshopt_quantizeSnorm(ny, bits)),
				    int16_t(meshopt_quantizeSnorm(nz, bits)),
				    int16_t(meshopt_quantizeSnorm(nw, 8))};
				bin.append(reinterpret_cast<const char*>(v), sizeof(v));
			}
			else
			{
				int8_t v[4] = {
				    int8_t(meshopt_quantizeSnorm(nx, bits)),
				    int8_t(meshopt_quantizeSnorm(ny, bits)),
				    int8_t(meshopt_quantizeSnorm(nz, bits)),
				    int8_t(meshopt_quantizeSnorm(nw, 8))};
				bin.append(reinterpret_cast<const char*>(v), sizeof(v));
			}
		}

		cgltf_type type = (stream.target == 0) ? cgltf_type_vec4 : cgltf_type_vec3;

		if (bits > 8)
		{
			StreamFormat format = {type, cgltf_component_type_r_16, true, 8};
			return format;
		}
		else
		{
			StreamFormat format = {type, cgltf_component_type_r_8, true, 4};
			return format;
		}
	}
	else if (stream.type == cgltf_attribute_type_color)
	{
		for (size_t i = 0; i < stream.data.size(); ++i)
		{
			const Attr& a = stream.data[i];

			uint8_t v[4] = {
			    uint8_t(meshopt_quantizeUnorm(a.f[0], 8)),
			    uint8_t(meshopt_quantizeUnorm(a.f[1], 8)),
			    uint8_t(meshopt_quantizeUnorm(a.f[2], 8)),
			    uint8_t(meshopt_quantizeUnorm(a.f[3], 8))};
			bin.append(reinterpret_cast<const char*>(v), sizeof(v));
		}

		StreamFormat format = {cgltf_type_vec4, cgltf_component_type_r_8u, true, 4};
		return format;
	}
	else if (stream.type == cgltf_attribute_type_weights)
	{
		for (size_t i = 0; i < stream.data.size(); ++i)
		{
			const Attr& a = stream.data[i];

			uint8_t v[4] = {
			    uint8_t(meshopt_quantizeUnorm(a.f[0], 8)),
			    uint8_t(meshopt_quantizeUnorm(a.f[1], 8)),
			    uint8_t(meshopt_quantizeUnorm(a.f[2], 8)),
			    uint8_t(meshopt_quantizeUnorm(a.f[3], 8))};

			renormalizeWeights(v);

			bin.append(reinterpret_cast<const char*>(v), sizeof(v));
		}

		StreamFormat format = {cgltf_type_vec4, cgltf_component_type_r_8u, true, 4};
		return format;
	}
	else if (stream.type == cgltf_attribute_type_joints)
	{
		unsigned int maxj = 0;

		for (size_t i = 0; i < stream.data.size(); ++i)
			maxj = std::max(maxj, unsigned(stream.data[i].f[0]));

		assert(maxj <= 65535);

		if (maxj <= 255)
		{
			for (size_t i = 0; i < stream.data.size(); ++i)
			{
				const Attr& a = stream.data[i];

				uint8_t v[4] = {
				    uint8_t(a.f[0]),
				    uint8_t(a.f[1]),
				    uint8_t(a.f[2]),
				    uint8_t(a.f[3])};
				bin.append(reinterpret_cast<const char*>(v), sizeof(v));
			}

			StreamFormat format = {cgltf_type_vec4, cgltf_component_type_r_8u, false, 4};
			return format;
		}
		else
		{
			for (size_t i = 0; i < stream.data.size(); ++i)
			{
				const Attr& a = stream.data[i];

				uint16_t v[4] = {
				    uint16_t(a.f[0]),
				    uint16_t(a.f[1]),
				    uint16_t(a.f[2]),
				    uint16_t(a.f[3])};
				bin.append(reinterpret_cast<const char*>(v), sizeof(v));
			}

			StreamFormat format = {cgltf_type_vec4, cgltf_component_type_r_16u, false, 8};
			return format;
		}
	}
	else
	{
		for (size_t i = 0; i < stream.data.size(); ++i)
		{
			const Attr& a = stream.data[i];

			float v[4] = {
			    a.f[0],
			    a.f[1],
			    a.f[2],
			    a.f[3]};
			bin.append(reinterpret_cast<const char*>(v), sizeof(v));
		}

		StreamFormat format = {cgltf_type_vec4, cgltf_component_type_r_32f, false, 16};
		return format;
	}
}

void getPositionBounds(int min[3], int max[3], const Stream& stream, const QuantizationParams& params)
{
	assert(stream.type == cgltf_attribute_type_position);
	assert(stream.data.size() > 0);

	min[0] = min[1] = min[2] = INT_MAX;
	max[0] = max[1] = max[2] = INT_MIN;

	float pos_rscale = params.pos_scale == 0.f ? 0.f : 1.f / params.pos_scale;

	if (stream.target == 0)
	{
		for (size_t i = 0; i < stream.data.size(); ++i)
		{
			const Attr& a = stream.data[i];

			for (int k = 0; k < 3; ++k)
			{
				int v = meshopt_quantizeUnorm((a.f[k] - params.pos_offset[k]) * pos_rscale, params.pos_bits);

				min[k] = std::min(min[k], v);
				max[k] = std::max(max[k], v);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < stream.data.size(); ++i)
		{
			const Attr& a = stream.data[i];

			for (int k = 0; k < 3; ++k)
			{
				int v = (a.f[k] >= 0.f ? 1 : -1) * meshopt_quantizeUnorm(fabsf(a.f[k]) * pos_rscale, params.pos_bits);

				min[k] = std::min(min[k], v);
				max[k] = std::max(max[k], v);
			}
		}
	}
}

StreamFormat writeIndexStream(std::string& bin, const std::vector<unsigned int>& stream)
{
	unsigned int maxi = 0;
	for (size_t i = 0; i < stream.size(); ++i)
		maxi = std::max(maxi, stream[i]);

	// save 16-bit indices if we can; note that we can't use restart index (65535)
	if (maxi < 65535)
	{
		for (size_t i = 0; i < stream.size(); ++i)
		{
			uint16_t v[1] = {uint16_t(stream[i])};
			bin.append(reinterpret_cast<const char*>(v), sizeof(v));
		}

		StreamFormat format = {cgltf_type_scalar, cgltf_component_type_r_16u, false, 2};
		return format;
	}
	else
	{
		for (size_t i = 0; i < stream.size(); ++i)
		{
			uint32_t v[1] = {stream[i]};
			bin.append(reinterpret_cast<const char*>(v), sizeof(v));
		}

		StreamFormat format = {cgltf_type_scalar, cgltf_component_type_r_32u, false, 4};
		return format;
	}
}

StreamFormat writeTimeStream(std::string& bin, const std::vector<float>& data)
{
	for (size_t i = 0; i < data.size(); ++i)
	{
		float v[1] = {data[i]};
		bin.append(reinterpret_cast<const char*>(v), sizeof(v));
	}

	StreamFormat format = {cgltf_type_scalar, cgltf_component_type_r_32f, false, 4};
	return format;
}

StreamFormat writeKeyframeStream(std::string& bin, cgltf_animation_path_type type, const std::vector<Attr>& data)
{
	if (type == cgltf_animation_path_type_rotation)
	{
		for (size_t i = 0; i < data.size(); ++i)
		{
			const Attr& a = data[i];

			int16_t v[4] = {
			    int16_t(meshopt_quantizeSnorm(a.f[0], 16)),
			    int16_t(meshopt_quantizeSnorm(a.f[1], 16)),
			    int16_t(meshopt_quantizeSnorm(a.f[2], 16)),
			    int16_t(meshopt_quantizeSnorm(a.f[3], 16)),
			};
			bin.append(reinterpret_cast<const char*>(v), sizeof(v));
		}

		StreamFormat format = {cgltf_type_vec4, cgltf_component_type_r_16, true, 8};
		return format;
	}
	else if (type == cgltf_animation_path_type_weights)
	{
		for (size_t i = 0; i < data.size(); ++i)
		{
			const Attr& a = data[i];

			uint8_t v[1] = {uint8_t(meshopt_quantizeUnorm(a.f[0], 8))};
			bin.append(reinterpret_cast<const char*>(v), sizeof(v));
		}

		StreamFormat format = {cgltf_type_scalar, cgltf_component_type_r_8u, true, 1};
		return format;
	}
	else
	{
		for (size_t i = 0; i < data.size(); ++i)
		{
			const Attr& a = data[i];

			float v[3] = {a.f[0], a.f[1], a.f[2]};
			bin.append(reinterpret_cast<const char*>(v), sizeof(v));
		}

		StreamFormat format = {cgltf_type_vec3, cgltf_component_type_r_32f, false, 12};
		return format;
	}
}

void compressVertexStream(std::string& bin, const std::string& data, size_t count, size_t stride)
{
	assert(data.size() == count * stride);

	std::vector<unsigned char> compressed(meshopt_encodeVertexBufferBound(count, stride));
	size_t size = meshopt_encodeVertexBuffer(&compressed[0], compressed.size(), data.c_str(), count, stride);

	bin.append(reinterpret_cast<const char*>(&compressed[0]), size);
}

void compressIndexStream(std::string& bin, const std::string& data, size_t count, size_t stride)
{
	assert(stride == 2 || stride == 4);
	assert(data.size() == count * stride);

	std::vector<unsigned char> compressed(meshopt_encodeIndexBufferBound(count, count * 3));
	size_t size = 0;

	if (stride == 2)
		size = meshopt_encodeIndexBuffer(&compressed[0], compressed.size(), reinterpret_cast<const uint16_t*>(data.c_str()), count);
	else
		size = meshopt_encodeIndexBuffer(&compressed[0], compressed.size(), reinterpret_cast<const uint32_t*>(data.c_str()), count);

	bin.append(reinterpret_cast<const char*>(&compressed[0]), size);
}

void comma(std::string& s)
{
	char ch = s.empty() ? 0 : s[s.size() - 1];

	if (ch != 0 && ch != '[' && ch != '{')
		s += ",";
}

void append(std::string& s, size_t v)
{
	char buf[32];
	sprintf(buf, "%zu", v);
	s += buf;
}

void append(std::string& s, float v)
{
	char buf[512];
	sprintf(buf, "%.9g", v);
	s += buf;
}

void append(std::string& s, const char* v)
{
	s += v;
}

void append(std::string& s, const std::string& v)
{
	s += v;
}

const char* componentType(cgltf_component_type type)
{
	switch (type)
	{
	case cgltf_component_type_r_8:
		return "5120";
	case cgltf_component_type_r_8u:
		return "5121";
	case cgltf_component_type_r_16:
		return "5122";
	case cgltf_component_type_r_16u:
		return "5123";
	case cgltf_component_type_r_32u:
		return "5125";
	case cgltf_component_type_r_32f:
		return "5126";
	default:
		return "0";
	}
}

const char* shapeType(cgltf_type type)
{
	switch (type)
	{
	case cgltf_type_scalar:
		return "SCALAR";
	case cgltf_type_vec2:
		return "VEC2";
	case cgltf_type_vec3:
		return "VEC3";
	case cgltf_type_vec4:
		return "VEC4";
	case cgltf_type_mat2:
		return "MAT2";
	case cgltf_type_mat3:
		return "MAT3";
	case cgltf_type_mat4:
		return "MAT4";
	default:
		return "";
	}
}

const char* attributeType(cgltf_attribute_type type)
{
	switch (type)
	{
	case cgltf_attribute_type_position:
		return "POSITION";
	case cgltf_attribute_type_normal:
		return "NORMAL";
	case cgltf_attribute_type_tangent:
		return "TANGENT";
	case cgltf_attribute_type_texcoord:
		return "TEXCOORD";
	case cgltf_attribute_type_color:
		return "COLOR";
	case cgltf_attribute_type_joints:
		return "JOINTS";
	case cgltf_attribute_type_weights:
		return "WEIGHTS";
	default:
		return "ATTRIBUTE";
	}
}

const char* animationPath(cgltf_animation_path_type type)
{
	switch (type)
	{
	case cgltf_animation_path_type_translation:
		return "translation";
	case cgltf_animation_path_type_rotation:
		return "rotation";
	case cgltf_animation_path_type_scale:
		return "scale";
	case cgltf_animation_path_type_weights:
		return "weights";
	default:
		return "";
	}
}

const char* lightType(cgltf_light_type type)
{
	switch (type)
	{
	case cgltf_light_type_directional:
		return "directional";
	case cgltf_light_type_point:
		return "point";
	case cgltf_light_type_spot:
		return "spot";
	default:
		return "";
	}
}

void writeTextureInfo(std::string& json, const cgltf_data* data, const cgltf_texture_view& view, const QuantizationParams& qp)
{
	assert(view.texture);

	cgltf_texture_transform transform = {};

	if (view.has_transform)
	{
		transform = view.transform;
	}
	else
	{
		transform.scale[0] = transform.scale[1] = 1.f;
	}

	transform.offset[0] += qp.uv_offset[0];
	transform.offset[1] += qp.uv_offset[1];
	transform.scale[0] *= qp.uv_scale[0] / float((1 << qp.uv_bits) - 1);
	transform.scale[1] *= qp.uv_scale[1] / float((1 << qp.uv_bits) - 1);

	append(json, "{\"index\":");
	append(json, size_t(view.texture - data->textures));
	append(json, ",\"texCoord\":");
	append(json, size_t(view.texcoord));
	append(json, ",\"extensions\":{\"KHR_texture_transform\":{");
	append(json, "\"offset\":[");
	append(json, transform.offset[0]);
	append(json, ",");
	append(json, transform.offset[1]);
	append(json, "],\"scale\":[");
	append(json, transform.scale[0]);
	append(json, ",");
	append(json, transform.scale[1]);
	append(json, "]");
	if (transform.rotation != 0.f)
	{
		append(json, ",\"rotation\":");
		append(json, transform.rotation);
	}
	append(json, "}}}");
}

void writeMaterialInfo(std::string& json, const cgltf_data* data, const cgltf_material& material, const QuantizationParams& qp)
{
	static const float white[4] = {1, 1, 1, 1};
	static const float black[4] = {0, 0, 0, 0};

	if (material.has_pbr_metallic_roughness)
	{
		const cgltf_pbr_metallic_roughness& pbr = material.pbr_metallic_roughness;

		comma(json);
		append(json, "\"pbrMetallicRoughness\":{");
		if (memcmp(pbr.base_color_factor, white, 16) != 0)
		{
			comma(json);
			append(json, "\"baseColorFactor\":[");
			append(json, pbr.base_color_factor[0]);
			append(json, ",");
			append(json, pbr.base_color_factor[1]);
			append(json, ",");
			append(json, pbr.base_color_factor[2]);
			append(json, ",");
			append(json, pbr.base_color_factor[3]);
			append(json, "]");
		}
		if (pbr.base_color_texture.texture)
		{
			comma(json);
			append(json, "\"baseColorTexture\":");
			writeTextureInfo(json, data, pbr.base_color_texture, qp);
		}
		if (pbr.metallic_factor != 1)
		{
			comma(json);
			append(json, "\"metallicFactor\":");
			append(json, pbr.metallic_factor);
		}
		if (pbr.roughness_factor != 1)
		{
			comma(json);
			append(json, "\"roughnessFactor\":");
			append(json, pbr.roughness_factor);
		}
		if (pbr.metallic_roughness_texture.texture)
		{
			comma(json);
			append(json, "\"metallicRoughnessTexture\":");
			writeTextureInfo(json, data, pbr.metallic_roughness_texture, qp);
		}
		append(json, "}");
	}

	if (material.normal_texture.texture)
	{
		comma(json);
		append(json, "\"normalTexture\":");
		writeTextureInfo(json, data, material.normal_texture, qp);
	}

	if (material.occlusion_texture.texture)
	{
		comma(json);
		append(json, "\"occlusionTexture\":");
		writeTextureInfo(json, data, material.occlusion_texture, qp);
	}

	if (material.emissive_texture.texture)
	{
		comma(json);
		append(json, "\"emissiveTexture\":");
		writeTextureInfo(json, data, material.emissive_texture, qp);
	}

	if (memcmp(material.emissive_factor, black, 12) != 0)
	{
		comma(json);
		append(json, "\"emissiveFactor\":[");
		append(json, material.emissive_factor[0]);
		append(json, ",");
		append(json, material.emissive_factor[1]);
		append(json, ",");
		append(json, material.emissive_factor[2]);
		append(json, "]");
	}

	if (material.alpha_mode != cgltf_alpha_mode_opaque)
	{
		comma(json);
		append(json, "\"alphaMode\":");
		append(json, (material.alpha_mode == cgltf_alpha_mode_blend) ? "\"BLEND\"" : "\"MASK\"");
	}

	if (material.alpha_cutoff != 0.5f)
	{
		comma(json);
		append(json, "\"alphaCutoff\":");
		append(json, material.alpha_cutoff);
	}

	if (material.double_sided)
	{
		comma(json);
		append(json, "\"doubleSided\":true");
	}

	if (material.has_pbr_specular_glossiness || material.unlit)
	{
		comma(json);
		append(json, "\"extensions\":{");

		if (material.has_pbr_specular_glossiness)
		{
			const cgltf_pbr_specular_glossiness& pbr = material.pbr_specular_glossiness;

			comma(json);
			append(json, "\"KHR_materials_pbrSpecularGlossiness\":{");
			if (pbr.diffuse_texture.texture)
			{
				comma(json);
				append(json, "\"diffuseTexture\":");
				writeTextureInfo(json, data, pbr.diffuse_texture, qp);
			}
			if (pbr.specular_glossiness_texture.texture)
			{
				comma(json);
				append(json, "\"specularGlossinessTexture\":");
				writeTextureInfo(json, data, pbr.specular_glossiness_texture, qp);
			}
			if (memcmp(pbr.diffuse_factor, white, 16) != 0)
			{
				comma(json);
				append(json, "\"diffuseFactor\":[");
				append(json, pbr.diffuse_factor[0]);
				append(json, ",");
				append(json, pbr.diffuse_factor[1]);
				append(json, ",");
				append(json, pbr.diffuse_factor[2]);
				append(json, ",");
				append(json, pbr.diffuse_factor[3]);
				append(json, "]");
			}
			if (memcmp(pbr.specular_factor, white, 12) != 0)
			{
				comma(json);
				append(json, "\"specularFactor\":[");
				append(json, pbr.specular_factor[0]);
				append(json, ",");
				append(json, pbr.specular_factor[1]);
				append(json, ",");
				append(json, pbr.specular_factor[2]);
				append(json, "]");
			}
			if (pbr.glossiness_factor != 1)
			{
				comma(json);
				append(json, "\"glossinessFactor\":");
				append(json, pbr.glossiness_factor);
			}
			append(json, "}");
		}
		if (material.unlit)
		{
			comma(json);
			append(json, "\"KHR_materials_unlit\":{}");
		}

		append(json, "}");
	}
}

bool usesTextureSet(const cgltf_material& material, int set)
{
	if (material.has_pbr_metallic_roughness)
	{
		const cgltf_pbr_metallic_roughness& pbr = material.pbr_metallic_roughness;

		if (pbr.base_color_texture.texture && pbr.base_color_texture.texcoord == set)
			return true;

		if (pbr.metallic_roughness_texture.texture && pbr.metallic_roughness_texture.texcoord == set)
			return true;
	}

	if (material.has_pbr_specular_glossiness)
	{
		const cgltf_pbr_specular_glossiness& pbr = material.pbr_specular_glossiness;

		if (pbr.diffuse_texture.texture && pbr.diffuse_texture.texcoord == set)
			return true;

		if (pbr.specular_glossiness_texture.texture && pbr.specular_glossiness_texture.texcoord == set)
			return true;
	}

	if (material.normal_texture.texture && material.normal_texture.texcoord == set)
		return true;

	if (material.occlusion_texture.texture && material.occlusion_texture.texcoord == set)
		return true;

	if (material.emissive_texture.texture && material.emissive_texture.texcoord == set)
		return true;

	return false;
}

size_t getBufferView(std::vector<BufferView>& views, BufferView::Kind kind, int variant, size_t stride, bool compressed)
{
	if (variant >= 0)
	{
		for (size_t i = 0; i < views.size(); ++i)
			if (views[i].kind == kind && views[i].variant == variant && views[i].stride == stride && views[i].compressed == compressed)
				return i;
	}

	BufferView view = {kind, variant, stride, compressed};
	views.push_back(view);

	return views.size() - 1;
}

void writeBufferView(std::string& json, BufferView::Kind kind, size_t count, size_t stride, size_t bin_offset, size_t bin_size, int compression, size_t compressed_offset, size_t compressed_size)
{
	assert(bin_size == count * stride);

	// when compression is enabled, we store uncompressed data in buffer 1 and compressed data in buffer 0
	// when compression is disabled, we store uncompressed data in buffer 0
	size_t buffer = compression >= 0 ? 1 : 0;

	append(json, "{\"buffer\":");
	append(json, buffer);
	append(json, ",\"byteOffset\":");
	append(json, bin_offset);
	append(json, ",\"byteLength\":");
	append(json, bin_size);
	if (kind == BufferView::Kind_Vertex)
	{
		append(json, ",\"byteStride\":");
		append(json, stride);
	}
	if (kind == BufferView::Kind_Vertex || kind == BufferView::Kind_Index)
	{
		append(json, ",\"target\":");
		append(json, (kind == BufferView::Kind_Vertex) ? "34962" : "34963");
	}
	if (compression >= 0)
	{
		append(json, ",\"extensions\":{");
		append(json, "\"MESHOPT_compression\":{");
		append(json, "\"buffer\":0");
		append(json, ",\"byteOffset\":");
		append(json, size_t(compressed_offset));
		append(json, ",\"byteLength\":");
		append(json, size_t(compressed_size));
		append(json, ",\"byteStride\":");
		append(json, stride);
		append(json, ",\"mode\":");
		append(json, size_t(compression));
		append(json, ",\"count\":");
		append(json, count);
		append(json, "}}");
	}
	append(json, "}");
}

void writeAccessor(std::string& json, size_t view, size_t offset, cgltf_type type, cgltf_component_type component_type, bool normalized, size_t count, const float* min = 0, const float* max = 0, size_t numminmax = 0)
{
	append(json, "{\"bufferView\":");
	append(json, view);
	append(json, ",\"byteOffset\":");
	append(json, offset);
	append(json, ",\"componentType\":");
	append(json, componentType(component_type));
	append(json, ",\"count\":");
	append(json, count);
	append(json, ",\"type\":\"");
	append(json, shapeType(type));
	append(json, "\"");

	if (normalized)
	{
		append(json, ",\"normalized\":true");
	}

	if (min && max)
	{
		assert(numminmax);

		append(json, ",\"min\":[");
		for (size_t k = 0; k < numminmax; ++k)
		{
			comma(json);
			append(json, min[k]);
		}
		append(json, "],\"max\":[");
		for (size_t k = 0; k < numminmax; ++k)
		{
			comma(json);
			append(json, max[k]);
		}
		append(json, "]");
	}

	append(json, "}");
}

float getDelta(const Attr& l, const Attr& r, cgltf_animation_path_type type)
{
	if (type == cgltf_animation_path_type_rotation)
	{
		float error = 1.f - fabsf(l.f[0] * r.f[0] + l.f[1] * r.f[1] + l.f[2] * r.f[2] + l.f[3] * r.f[3]);

		return error;
	}
	else
	{
		float error = 0;
		for (int k = 0; k < 4; ++k)
			error += fabsf(r.f[k] - l.f[k]);

		return error;
	}
}

bool isTrackConstant(const cgltf_animation_sampler& sampler, cgltf_animation_path_type type, cgltf_node* target_node, Attr* out_first = 0)
{
	const float tolerance = 1e-3f;

	size_t value_stride = (sampler.interpolation == cgltf_interpolation_type_cubic_spline) ? 3 : 1;
	size_t value_offset = (sampler.interpolation == cgltf_interpolation_type_cubic_spline) ? 1 : 0;

	size_t components = (type == cgltf_animation_path_type_weights) ? target_node->mesh->primitives[0].targets_count : 1;

	assert(sampler.input->count * value_stride * components == sampler.output->count);

	std::vector<Attr> output;
	readAccessor(output, sampler.output);

	for (size_t j = 0; j < components; ++j)
	{
		Attr first = output[j * value_stride + value_offset];

		for (size_t i = 1; i < sampler.input->count; ++i)
		{
			const Attr& attr = output[(i * components + j) * value_stride + value_offset];

			if (getDelta(first, attr, type) > tolerance)
				return false;
		}

		if (sampler.interpolation == cgltf_interpolation_type_cubic_spline)
		{
			for (size_t i = 0; i < sampler.input->count; ++i)
			{
				for (int k = 0; k < 2; ++k)
				{
					const Attr& t = output[(i * components + j) * 3 + k * 2];

					float error = fabsf(t.f[0]) + fabsf(t.f[1]) + fabsf(t.f[2]) + fabsf(t.f[3]);

					if (error > tolerance)
						return false;
				}
			}
		}
	}

	if (out_first)
		*out_first = output[value_offset];

	return true;
}

Attr interpolateLinear(const Attr& l, const Attr& r, float t, cgltf_animation_path_type type)
{
	if (type == cgltf_animation_path_type_rotation)
	{
		// Approximating slerp, https://zeux.io/2015/07/23/approximating-slerp/
		// We also handle quaternion double-cover
		float ca = l.f[0] * r.f[0] + l.f[1] * r.f[1] + l.f[2] * r.f[2] + l.f[3] * r.f[3];

		float d = fabsf(ca);
		float A = 1.0904f + d * (-3.2452f + d * (3.55645f - d * 1.43519f));
		float B = 0.848013f + d * (-1.06021f + d * 0.215638f);
		float k = A * (t - 0.5f) * (t - 0.5f) + B;
		float ot = t + t * (t - 0.5f) * (t - 1) * k;

		float t0 = 1 - ot;
		float t1 = ca > 0 ? ot : -ot;

		Attr lerp = {{
		    l.f[0] * t0 + r.f[0] * t1,
		    l.f[1] * t0 + r.f[1] * t1,
		    l.f[2] * t0 + r.f[2] * t1,
		    l.f[3] * t0 + r.f[3] * t1,
		}};

		float len = sqrtf(lerp.f[0] * lerp.f[0] + lerp.f[1] * lerp.f[1] + lerp.f[2] * lerp.f[2] + lerp.f[3] * lerp.f[3]);

		if (len > 0.f)
		{
			lerp.f[0] /= len;
			lerp.f[1] /= len;
			lerp.f[2] /= len;
			lerp.f[3] /= len;
		}

		return lerp;
	}
	else
	{
		Attr lerp = {{
		    l.f[0] * (1 - t) + r.f[0] * t,
		    l.f[1] * (1 - t) + r.f[1] * t,
		    l.f[2] * (1 - t) + r.f[2] * t,
		    l.f[3] * (1 - t) + r.f[3] * t,
		}};

		return lerp;
	}
}

Attr interpolateHermite(const Attr& v0, const Attr& t0, const Attr& v1, const Attr& t1, float t, float dt, cgltf_animation_path_type type)
{
	float s0 = 1 + t * t * (2 * t - 3);
	float s1 = t + t * t * (t - 2);
	float s2 = 1 - s0;
	float s3 = t * t * (t - 1);

	float ts1 = dt * s1;
	float ts3 = dt * s3;

	Attr lerp = {{
	    s0 * v0.f[0] + ts1 * t0.f[0] + s2 * v1.f[0] + ts3 * t1.f[0],
	    s0 * v0.f[1] + ts1 * t0.f[1] + s2 * v1.f[1] + ts3 * t1.f[1],
	    s0 * v0.f[2] + ts1 * t0.f[2] + s2 * v1.f[2] + ts3 * t1.f[2],
	    s0 * v0.f[3] + ts1 * t0.f[3] + s2 * v1.f[3] + ts3 * t1.f[3],
	}};

	if (type == cgltf_animation_path_type_rotation)
	{
		float len = sqrtf(lerp.f[0] * lerp.f[0] + lerp.f[1] * lerp.f[1] + lerp.f[2] * lerp.f[2] + lerp.f[3] * lerp.f[3]);

		if (len > 0.f)
		{
			lerp.f[0] /= len;
			lerp.f[1] /= len;
			lerp.f[2] /= len;
			lerp.f[3] /= len;
		}
	}

	return lerp;
}

void resampleKeyframes(std::vector<Attr>& data, const cgltf_animation_sampler& sampler, cgltf_animation_path_type type, cgltf_node* target_node, int frames, float mint, int freq)
{
	size_t components = (type == cgltf_animation_path_type_weights) ? target_node->mesh->primitives[0].targets_count : 1;

	std::vector<float> input;
	readAccessor(input, sampler.input);
	std::vector<Attr> output;
	readAccessor(output, sampler.output);

	size_t cursor = 0;

	for (int i = 0; i < frames; ++i)
	{
		float time = mint + float(i) / freq;

		while (cursor + 1 < sampler.input->count)
		{
			float next_time = input[cursor + 1];

			if (next_time > time)
				break;

			cursor++;
		}

		if (cursor + 1 < sampler.input->count)
		{
			float cursor_time = input[cursor + 0];
			float next_time = input[cursor + 1];

			float range = next_time - cursor_time;
			float inv_range = (range == 0.f) ? 0.f : 1.f / (next_time - cursor_time);
			float t = std::max(0.f, std::min(1.f, (time - cursor_time) * inv_range));

			for (size_t j = 0; j < components; ++j)
			{
				switch (sampler.interpolation)
				{
				case cgltf_interpolation_type_linear:
				{
					const Attr& v0 = output[(cursor + 0) * components + j];
					const Attr& v1 = output[(cursor + 1) * components + j];
					data.push_back(interpolateLinear(v0, v1, t, type));
				}
				break;

				case cgltf_interpolation_type_step:
				{
					const Attr& v = output[cursor * components + j];
					data.push_back(v);
				}
				break;

				case cgltf_interpolation_type_cubic_spline:
				{
					const Attr& v0 = output[(cursor * 3 + 1) * components + j];
					const Attr& b0 = output[(cursor * 3 + 2) * components + j];
					const Attr& a1 = output[(cursor * 3 + 3) * components + j];
					const Attr& v1 = output[(cursor * 3 + 4) * components + j];
					data.push_back(interpolateHermite(v0, b0, v1, a1, t, range, type));
				}
				break;

				default:
					assert(!"Unknown interpolation type");
				}
			}
		}
		else
		{
			size_t offset = (sampler.interpolation == cgltf_interpolation_type_cubic_spline) ? cursor * 3 + 1 : cursor;

			for (size_t j = 0; j < components; ++j)
			{
				const Attr& v = output[offset * components + j];
				data.push_back(v);
			}
		}
	}
}

void markAnimated(cgltf_data* data, std::vector<NodeInfo>& nodes)
{
	for (size_t i = 0; i < data->animations_count; ++i)
	{
		const cgltf_animation& animation = data->animations[i];

		for (size_t j = 0; j < animation.channels_count; ++j)
		{
			const cgltf_animation_channel& channel = animation.channels[j];
			const cgltf_animation_sampler& sampler = *channel.sampler;

			if (!channel.target_node)
				continue;

			NodeInfo& ni = nodes[channel.target_node - data->nodes];

			// mark nodes that have animation tracks that change their base transform as animated
			Attr first = {};
			if (!isTrackConstant(sampler, channel.target_path, channel.target_node, &first))
			{
				ni.animated_paths |= (1 << channel.target_path);
			}
			else if (channel.target_path == cgltf_animation_path_type_weights)
			{
				// we currently preserve constant weight tracks because the usecase is very rare and
				// isTrackConstant doesn't return the full set of weights to compare against
				ni.animated_paths |= (1 << channel.target_path);
			}
			else
			{
				Attr base = {};

				switch (channel.target_path)
				{
				case cgltf_animation_path_type_translation:
					memcpy(base.f, channel.target_node->translation, 3 * sizeof(float));
					break;
				case cgltf_animation_path_type_rotation:
					memcpy(base.f, channel.target_node->rotation, 4 * sizeof(float));
					break;
				case cgltf_animation_path_type_scale:
					memcpy(base.f, channel.target_node->scale, 3 * sizeof(float));
					break;
				default:
					assert(!"Unknown target path");
				}

				const float tolerance = 1e-3f;

				if (getDelta(base, first, channel.target_path) > tolerance)
				{
					ni.animated_paths |= (1 << channel.target_path);
				}
			}
		}
	}

	for (size_t i = 0; i < data->nodes_count; ++i)
	{
		NodeInfo& ni = nodes[i];

		for (cgltf_node* node = &data->nodes[i]; node; node = node->parent)
			ni.animated |= nodes[node - data->nodes].animated_paths != 0;
	}
}

void markNeededNodes(cgltf_data* data, std::vector<NodeInfo>& nodes, const std::vector<Mesh>& meshes, const Settings& settings)
{
	// mark all joints as kept
	for (size_t i = 0; i < data->skins_count; ++i)
	{
		const cgltf_skin& skin = data->skins[i];

		// for now we keep all joints directly referenced by the skin and the entire ancestry tree; we keep names for joints as well
		for (size_t j = 0; j < skin.joints_count; ++j)
		{
			NodeInfo& ni = nodes[skin.joints[j] - data->nodes];

			ni.keep = true;
		}
	}

	// mark all animated nodes as kept
	for (size_t i = 0; i < data->animations_count; ++i)
	{
		const cgltf_animation& animation = data->animations[i];

		for (size_t j = 0; j < animation.channels_count; ++j)
		{
			const cgltf_animation_channel& channel = animation.channels[j];

			if (channel.target_node)
			{
				NodeInfo& ni = nodes[channel.target_node - data->nodes];

				ni.keep = true;
			}
		}
	}

	// mark all mesh nodes as kept
	for (size_t i = 0; i < meshes.size(); ++i)
	{
		const Mesh& mesh = meshes[i];

		if (mesh.node)
		{
			NodeInfo& ni = nodes[mesh.node - data->nodes];

			ni.keep = true;
		}
	}

	// mark all light/camera nodes as kept
	for (size_t i = 0; i < data->nodes_count; ++i)
	{
		const cgltf_node& node = data->nodes[i];

		if (node.light || node.camera)
		{
			nodes[i].keep = true;
		}
	}

	// mark all named nodes as needed (if -kn is specified)
	if (settings.keep_named)
	{
		for (size_t i = 0; i < data->nodes_count; ++i)
		{
			const cgltf_node& node = data->nodes[i];

			if (node.name && *node.name)
			{
				nodes[i].keep = true;
			}
		}
	}
}

void markNeededMaterials(cgltf_data* data, std::vector<MaterialInfo>& materials, const std::vector<Mesh>& meshes)
{
	// mark all used materials as kept
	for (size_t i = 0; i < meshes.size(); ++i)
	{
		const Mesh& mesh = meshes[i];

		if (mesh.material)
		{
			MaterialInfo& mi = materials[mesh.material - data->materials];

			mi.keep = true;
		}
	}
}

void remapNodes(cgltf_data* data, std::vector<NodeInfo>& nodes, size_t& node_offset)
{
	// to keep a node, we currently need to keep the entire ancestry chain
	for (size_t i = 0; i < data->nodes_count; ++i)
	{
		if (!nodes[i].keep)
			continue;

		for (cgltf_node* node = &data->nodes[i]; node; node = node->parent)
			nodes[node - data->nodes].keep = true;
	}

	// generate sequential indices for all nodes; they aren't sorted topologically
	for (size_t i = 0; i < data->nodes_count; ++i)
	{
		NodeInfo& ni = nodes[i];

		if (ni.keep)
		{
			ni.remap = int(node_offset);

			node_offset++;
		}
	}
}

bool parseDataUri(const char* uri, std::string& mime_type, std::string& result)
{
	if (strncmp(uri, "data:", 5) == 0)
	{
		const char* comma = strchr(uri, ',');

		if (comma && comma - uri >= 7 && strncmp(comma - 7, ";base64", 7) == 0)
		{
			const char* base64 = comma + 1;
			size_t base64_size = strlen(base64);
			size_t size = base64_size - base64_size / 4;

			if (base64_size >= 2)
			{
				size -= base64[base64_size - 2] == '=';
				size -= base64[base64_size - 1] == '=';
			}

			void* data = 0;

			cgltf_options options = {};
			cgltf_result res = cgltf_load_buffer_base64(&options, size, base64, &data);

			if (res != cgltf_result_success)
				return false;

			mime_type = std::string(uri + 5, comma - 7);
			result = std::string(static_cast<const char*>(data), size);

			free(data);

			return true;
		}
	}

	return false;
}

void writeEmbeddedImage(std::string& json, std::vector<BufferView>& views, const char* data, size_t size, const char* mime_type)
{
	size_t view = getBufferView(views, BufferView::Kind_Image, -1, 1, false);

	assert(views[view].data.empty());
	views[view].data.assign(data, size);

	append(json, "\"bufferView\":");
	append(json, view);
	append(json, ",\"mimeType\":\"");
	append(json, mime_type);
	append(json, "\"");
}

void writeMeshAttributes(std::string& json, std::vector<BufferView>& views, std::string& json_accessors, size_t& accr_offset, const Mesh& mesh, int target, const QuantizationParams& qp, const Settings& settings)
{
	std::string scratch;

	for (size_t j = 0; j < mesh.streams.size(); ++j)
	{
		const Stream& stream = mesh.streams[j];

		if (stream.target != target)
			continue;

		if (stream.type == cgltf_attribute_type_texcoord && (!mesh.material || !usesTextureSet(*mesh.material, stream.index)))
			continue;

		if (stream.type == cgltf_attribute_type_tangent && (!mesh.material || !mesh.material->normal_texture.texture))
			continue;

		if ((stream.type == cgltf_attribute_type_joints || stream.type == cgltf_attribute_type_weights) && !mesh.skin)
			continue;

		scratch.clear();
		StreamFormat format = writeVertexStream(scratch, stream, qp, settings, mesh.targets > 0);

		size_t view = getBufferView(views, BufferView::Kind_Vertex, stream.type, format.stride, settings.compress);
		size_t offset = views[view].data.size();
		views[view].data += scratch;

		comma(json_accessors);
		if (stream.type == cgltf_attribute_type_position)
		{
			int min[3] = {};
			int max[3] = {};
			getPositionBounds(min, max, stream, qp);

			float minf[3] = {float(min[0]), float(min[1]), float(min[2])};
			float maxf[3] = {float(max[0]), float(max[1]), float(max[2])};

			writeAccessor(json_accessors, view, offset, format.type, format.component_type, format.normalized, stream.data.size(), minf, maxf, 3);
		}
		else
		{
			writeAccessor(json_accessors, view, offset, format.type, format.component_type, format.normalized, stream.data.size());
		}

		size_t vertex_accr = accr_offset++;

		comma(json);
		append(json, "\"");
		append(json, attributeType(stream.type));
		if (stream.type != cgltf_attribute_type_position && stream.type != cgltf_attribute_type_normal && stream.type != cgltf_attribute_type_tangent)
		{
			append(json, "_");
			append(json, size_t(stream.index));
		}
		append(json, "\":");
		append(json, vertex_accr);
	}
}

size_t writeMeshIndices(std::vector<BufferView>& views, std::string& json_accessors, size_t& accr_offset, const Mesh& mesh, const Settings& settings)
{
	std::string scratch;
	StreamFormat format = writeIndexStream(scratch, mesh.indices);

	// note: we prefer to merge all index streams together; however, index codec currently doesn't handle concatenated index streams well and loses compression ratio
	int variant = settings.compress ? -1 : 0;

	size_t view = getBufferView(views, BufferView::Kind_Index, variant, format.stride, settings.compress);
	size_t offset = views[view].data.size();
	views[view].data += scratch;

	comma(json_accessors);
	writeAccessor(json_accessors, view, offset, format.type, format.component_type, format.normalized, mesh.indices.size());

	size_t index_accr = accr_offset++;

	return index_accr;
}

size_t writeAnimationTime(std::vector<BufferView>& views, std::string& json_accessors, size_t& accr_offset, float mint, int frames, const Settings& settings)
{
	std::vector<float> time(frames);

	for (int j = 0; j < frames; ++j)
		time[j] = mint + float(j) / settings.anim_freq;

	std::string scratch;
	StreamFormat format = writeTimeStream(scratch, time);

	size_t view = getBufferView(views, BufferView::Kind_Time, 0, format.stride, settings.compress);
	size_t offset = views[view].data.size();
	views[view].data += scratch;

	comma(json_accessors);
	writeAccessor(json_accessors, view, offset, cgltf_type_scalar, format.component_type, format.normalized, frames, &time.front(), &time.back(), 1);

	size_t time_accr = accr_offset++;

	return time_accr;
}

size_t writeJointBindMatrices(std::vector<BufferView>& views, std::string& json_accessors, size_t& accr_offset, const cgltf_skin& skin, const QuantizationParams& qp, const Settings& settings)
{
	std::string scratch;

	for (size_t j = 0; j < skin.joints_count; ++j)
	{
		float transform[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

		if (skin.inverse_bind_matrices)
		{
			cgltf_accessor_read_float(skin.inverse_bind_matrices, j, transform, 16);
		}

		float node_scale = qp.pos_scale / float((1 << qp.pos_bits) - 1);

		// pos_offset has to be applied first, thus it results in an offset rotated by the bind matrix
		transform[12] += qp.pos_offset[0] * transform[0] + qp.pos_offset[1] * transform[4] + qp.pos_offset[2] * transform[8];
		transform[13] += qp.pos_offset[0] * transform[1] + qp.pos_offset[1] * transform[5] + qp.pos_offset[2] * transform[9];
		transform[14] += qp.pos_offset[0] * transform[2] + qp.pos_offset[1] * transform[6] + qp.pos_offset[2] * transform[10];

		// node_scale will be applied before the rotation/scale from transform
		for (int k = 0; k < 12; ++k)
			transform[k] *= node_scale;

		scratch.append(reinterpret_cast<const char*>(transform), sizeof(transform));
	}

	size_t view = getBufferView(views, BufferView::Kind_Skin, 0, 64, settings.compress);
	size_t offset = views[view].data.size();
	views[view].data += scratch;

	comma(json_accessors);
	writeAccessor(json_accessors, view, offset, cgltf_type_mat4, cgltf_component_type_r_32f, false, skin.joints_count);

	size_t matrix_accr = accr_offset++;

	return matrix_accr;
}

void writeMeshNode(std::string& json, size_t mesh_offset, const Mesh& mesh, cgltf_data* data, const QuantizationParams& qp)
{
	float node_scale = qp.pos_scale / float((1 << qp.pos_bits) - 1);

	comma(json);
	append(json, "{\"mesh\":");
	append(json, mesh_offset);
	if (mesh.skin)
	{
		comma(json);
		append(json, "\"skin\":");
		append(json, size_t(mesh.skin - data->skins));
	}
	append(json, ",\"translation\":[");
	append(json, qp.pos_offset[0]);
	append(json, ",");
	append(json, qp.pos_offset[1]);
	append(json, ",");
	append(json, qp.pos_offset[2]);
	append(json, "],\"scale\":[");
	append(json, node_scale);
	append(json, ",");
	append(json, node_scale);
	append(json, ",");
	append(json, node_scale);
	append(json, "]");
	if (mesh.node && mesh.node->weights_count)
	{
		append(json, ",\"weights\":[");
		for (size_t j = 0; j < mesh.node->weights_count; ++j)
		{
			comma(json);
			append(json, mesh.node->weights[j]);
		}
		append(json, "]");
	}
	append(json, "}");
}

void writeNode(std::string& json, const cgltf_node& node, const std::vector<NodeInfo>& nodes, cgltf_data* data)
{
	const NodeInfo& ni = nodes[&node - data->nodes];

	comma(json);
	append(json, "{");
	if (node.name && *node.name)
	{
		comma(json);
		append(json, "\"name\":\"");
		append(json, node.name);
		append(json, "\"");
	}
	if (node.has_translation)
	{
		comma(json);
		append(json, "\"translation\":[");
		append(json, node.translation[0]);
		append(json, ",");
		append(json, node.translation[1]);
		append(json, ",");
		append(json, node.translation[2]);
		append(json, "]");
	}
	if (node.has_rotation)
	{
		comma(json);
		append(json, "\"rotation\":[");
		append(json, node.rotation[0]);
		append(json, ",");
		append(json, node.rotation[1]);
		append(json, ",");
		append(json, node.rotation[2]);
		append(json, ",");
		append(json, node.rotation[3]);
		append(json, "]");
	}
	if (node.has_scale)
	{
		comma(json);
		append(json, "\"scale\":[");
		append(json, node.scale[0]);
		append(json, ",");
		append(json, node.scale[1]);
		append(json, ",");
		append(json, node.scale[2]);
		append(json, "]");
	}
	if (node.has_matrix)
	{
		comma(json);
		append(json, "\"matrix\":[");
		for (int k = 0; k < 16; ++k)
		{
			comma(json);
			append(json, node.matrix[k]);
		}
		append(json, "]");
	}
	if (node.children_count || !ni.meshes.empty())
	{
		comma(json);
		append(json, "\"children\":[");
		for (size_t j = 0; j < node.children_count; ++j)
		{
			const NodeInfo& ci = nodes[node.children[j] - data->nodes];

			if (ci.keep)
			{
				comma(json);
				append(json, size_t(ci.remap));
			}
		}
		for (size_t j = 0; j < ni.meshes.size(); ++j)
		{
			comma(json);
			append(json, ni.meshes[j]);
		}
		append(json, "]");
	}
	if (node.camera)
	{
		comma(json);
		append(json, "\"camera\":");
		append(json, size_t(node.camera - data->cameras));
	}
	if (node.light)
	{
		comma(json);
		append(json, "\"extensions\":{\"KHR_lights_punctual\":{\"light\":");
		append(json, size_t(node.light - data->lights));
		append(json, "}}");
	}
	append(json, "}");
}

void writeAnimation(std::string& json, std::vector<BufferView>& views, std::string& json_accessors, size_t& accr_offset, const cgltf_animation& animation, cgltf_data* data, const std::vector<NodeInfo>& nodes, const Settings& settings)
{
	std::vector<const cgltf_animation_channel*> tracks;

	for (size_t j = 0; j < animation.channels_count; ++j)
	{
		const cgltf_animation_channel& channel = animation.channels[j];

		if (!channel.target_node)
		{
			fprintf(stderr, "Warning: ignoring channel %d of animation %d because it has no target node\n", int(j), int(&animation - data->animations));
			continue;
		}

		const NodeInfo& ni = nodes[channel.target_node - data->nodes];

		if (!ni.keep)
			continue;

		if (!settings.anim_const && (ni.animated_paths & (1 << channel.target_path)) == 0)
			continue;

		tracks.push_back(&channel);
	}

	if (tracks.empty())
	{
		fprintf(stderr, "Warning: ignoring animation %d because it has no valid tracks\n", int(&animation - data->animations));
		return;
	}

	float mint = 0, maxt = 0;
	bool needs_time = false;
	bool needs_pose = false;

	for (size_t j = 0; j < tracks.size(); ++j)
	{
		const cgltf_animation_channel& channel = *tracks[j];
		const cgltf_animation_sampler& sampler = *channel.sampler;

		mint = std::min(mint, sampler.input->min[0]);
		maxt = std::max(maxt, sampler.input->max[0]);

		bool tc = isTrackConstant(sampler, channel.target_path, channel.target_node);

		needs_time = needs_time || !tc;
		needs_pose = needs_pose || tc;
	}

	// round the number of frames to nearest but favor the "up" direction
	// this means that at 10 Hz resampling, we will try to preserve the last frame <10ms
	// but if the last frame is <2ms we favor just removing this data
	int frames = 1 + int((maxt - mint) * settings.anim_freq + 0.8f);

	size_t time_accr = needs_time ? writeAnimationTime(views, json_accessors, accr_offset, mint, frames, settings) : 0;
	size_t pose_accr = needs_pose ? writeAnimationTime(views, json_accessors, accr_offset, mint, 1, settings) : 0;

	std::string json_samplers;
	std::string json_channels;

	size_t track_offset = 0;

	for (size_t j = 0; j < tracks.size(); ++j)
	{
		const cgltf_animation_channel& channel = *tracks[j];
		const cgltf_animation_sampler& sampler = *channel.sampler;

		bool tc = isTrackConstant(sampler, channel.target_path, channel.target_node);

		std::vector<Attr> track;
		resampleKeyframes(track, sampler, channel.target_path, channel.target_node, tc ? 1 : frames, mint, settings.anim_freq);

		std::string scratch;
		StreamFormat format = writeKeyframeStream(scratch, channel.target_path, track);

		size_t view = getBufferView(views, BufferView::Kind_Keyframe, channel.target_path, format.stride, settings.compress && channel.target_path != cgltf_animation_path_type_weights);
		size_t offset = views[view].data.size();
		views[view].data += scratch;

		comma(json_accessors);
		writeAccessor(json_accessors, view, offset, format.type, format.component_type, format.normalized, track.size());

		size_t data_accr = accr_offset++;

		comma(json_samplers);
		append(json_samplers, "{\"input\":");
		append(json_samplers, tc ? pose_accr : time_accr);
		append(json_samplers, ",\"output\":");
		append(json_samplers, data_accr);
		append(json_samplers, "}");

		const NodeInfo& tni = nodes[channel.target_node - data->nodes];
		size_t target_node = size_t(tni.remap);

		if (channel.target_path == cgltf_animation_path_type_weights)
		{
			assert(tni.meshes.size() == 1);
			target_node = tni.meshes[0];
		}

		comma(json_channels);
		append(json_channels, "{\"sampler\":");
		append(json_channels, track_offset);
		append(json_channels, ",\"target\":{\"node\":");
		append(json_channels, target_node);
		append(json_channels, ",\"path\":\"");
		append(json_channels, animationPath(channel.target_path));
		append(json_channels, "\"}}");

		track_offset++;
	}

	comma(json);
	append(json, "{");
	if (animation.name && *animation.name)
	{
		append(json, "\"name\":\"");
		append(json, animation.name);
		append(json, "\",");
	}
	append(json, "\"samplers\":[");
	append(json, json_samplers);
	append(json, "],\"channels\":[");
	append(json, json_channels);
	append(json, "]}");
}

void writeCamera(std::string& json, const cgltf_camera& camera)
{
	comma(json);
	append(json, "{");

	switch (camera.type)
	{
	case cgltf_camera_type_perspective:
		append(json, "\"type\":\"perspective\",\"perspective\":{");
		append(json, "\"yfov\":");
		append(json, camera.perspective.yfov);
		append(json, ",\"znear\":");
		append(json, camera.perspective.znear);
		if (camera.perspective.aspect_ratio != 0.f)
		{
			append(json, ",\"aspectRatio\":");
			append(json, camera.perspective.aspect_ratio);
		}
		if (camera.perspective.zfar != 0.f)
		{
			append(json, ",\"zfar\":");
			append(json, camera.perspective.zfar);
		}
		append(json, "}");
		break;

	case cgltf_camera_type_orthographic:
		append(json, "\"type\":\"orthographic\",\"orthographic\":{");
		append(json, "\"xmag\":");
		append(json, camera.orthographic.xmag);
		append(json, ",\"ymag\":");
		append(json, camera.orthographic.ymag);
		append(json, ",\"znear\":");
		append(json, camera.orthographic.znear);
		append(json, ",\"zfar\":");
		append(json, camera.orthographic.zfar);
		append(json, "}");
		break;

	default:
		fprintf(stderr, "Warning: skipping camera of unknown type\n");
	}

	append(json, "}");
}

void writeLight(std::string& json, const cgltf_light& light)
{
	static const float white[3] = {1, 1, 1};

	comma(json);
	append(json, "{\"type\":\"");
	append(json, lightType(light.type));
	append(json, "\"");
	if (memcmp(light.color, white, sizeof(white)) != 0)
	{
		comma(json);
		append(json, "\"color\":[");
		append(json, light.color[0]);
		append(json, ",");
		append(json, light.color[1]);
		append(json, ",");
		append(json, light.color[2]);
		append(json, "]");
	}
	if (light.intensity != 1.f)
	{
		comma(json);
		append(json, "\"intensity\":");
		append(json, light.intensity);
	}
	if (light.range != 0.f)
	{
		comma(json);
		append(json, "\"range\":");
		append(json, light.range);
	}
	if (light.type == cgltf_light_type_spot)
	{
		comma(json);
		append(json, "\"spot\":{");
		append(json, "\"innerConeAngle\":");
		append(json, light.spot_inner_cone_angle);
		append(json, ",\"outerConeAngle\":");
		append(json, light.spot_outer_cone_angle == 0.f ? 0.78539816339f : light.spot_outer_cone_angle);
		append(json, "}");
	}
	append(json, "}");
}

void finalizeBufferViews(std::string& json, std::vector<BufferView>& views, std::string& bin, std::string& fallback)
{
	for (size_t i = 0; i < views.size(); ++i)
	{
		BufferView& view = views[i];

		size_t bin_offset = bin.size();
		size_t fallback_offset = fallback.size();

		size_t count = view.data.size() / view.stride;

		int compression = -1;

		if (view.compressed)
		{
			if (view.kind == BufferView::Kind_Index)
			{
				compressIndexStream(bin, view.data, count, view.stride);
				compression = 1;
			}
			else
			{
				compressVertexStream(bin, view.data, count, view.stride);
				compression = 0;
			}

			fallback += view.data;
		}
		else
		{
			bin += view.data;
		}

		size_t raw_offset = (compression >= 0) ? fallback_offset : bin_offset;

		comma(json);
		writeBufferView(json, view.kind, count, view.stride, raw_offset, view.data.size(), compression, bin_offset, bin.size() - bin_offset);

		// record written bytes for statistics
		view.bytes = bin.size() - bin_offset;

		// align each bufferView by 4 bytes
		bin.resize((bin.size() + 3) & ~3);
		fallback.resize((fallback.size() + 3) & ~3);
	}
}

void printMeshStats(const std::vector<Mesh>& meshes, const char* name)
{
	size_t triangles = 0;
	size_t vertices = 0;

	for (size_t i = 0; i < meshes.size(); ++i)
	{
		const Mesh& mesh = meshes[i];

		triangles += mesh.indices.size() / 3;
		vertices += mesh.streams.empty() ? 0 : mesh.streams[0].data.size();
	}

	printf("%s: %d triangles, %d vertices\n", name, int(triangles), int(vertices));
}

void printAttributeStats(const std::vector<BufferView>& views, BufferView::Kind kind, const char* name)
{
	for (size_t i = 0; i < views.size(); ++i)
	{
		const BufferView& view = views[i];

		if (view.kind != kind)
			continue;

		const char* variant = "unknown";

		switch (kind)
		{
		case BufferView::Kind_Vertex:
			variant = attributeType(cgltf_attribute_type(view.variant));
			break;

		case BufferView::Kind_Index:
			variant = "index";
			break;

		case BufferView::Kind_Keyframe:
			variant = animationPath(cgltf_animation_path_type(view.variant));
			break;

		default:;
		}

		size_t count = view.data.size() / view.stride;

		printf("stats: %s %s: compressed %d bytes (%.1f bits), raw %d bytes (%d bits)\n",
		       name,
		       variant,
		       int(view.bytes),
		       double(view.bytes) / double(count) * 8,
		       int(view.data.size()),
		       int(view.stride * 8));
	}
}

void process(cgltf_data* data, std::vector<Mesh>& meshes, const Settings& settings, std::string& json, std::string& bin, std::string& fallback)
{
	if (settings.verbose)
	{
		printf("input: %d nodes, %d meshes (%d primitives), %d materials, %d skins, %d animations\n",
		       int(data->nodes_count), int(data->meshes_count), int(meshes.size()), int(data->materials_count), int(data->skins_count), int(data->animations_count));
	}

	std::vector<NodeInfo> nodes(data->nodes_count);

	markAnimated(data, nodes);

	for (size_t i = 0; i < meshes.size(); ++i)
	{
		Mesh& mesh = meshes[i];

		// note: when -kn is specified, we keep mesh-node attachment so that named nodes can be transformed
		if (mesh.node && !settings.keep_named)
		{
			NodeInfo& ni = nodes[mesh.node - data->nodes];

			// we transform all non-skinned non-animated meshes to world space
			// this makes sure that quantization doesn't introduce gaps if the original scene was watertight
			if (!ni.animated && !mesh.skin && mesh.targets == 0)
			{
				transformMesh(mesh, mesh.node);
				mesh.node = 0;
			}

			// skinned and animated meshes will be anchored to the same node that they used to be in
			// for animated meshes, this is important since they need to be transformed by the same animation
			// for skinned meshes, in theory this isn't important since the transform of the skinned node doesn't matter; in practice this affects generated bounding box in three.js
		}
	}

	mergeMeshMaterials(data, meshes);
	mergeMeshes(meshes, settings);

	markNeededNodes(data, nodes, meshes, settings);

	std::vector<MaterialInfo> materials(data->materials_count);

	markNeededMaterials(data, materials, meshes);

	if (settings.verbose)
	{
		printMeshStats(meshes, "input");
	}

	for (size_t i = 0; i < meshes.size(); ++i)
	{
		Mesh& mesh = meshes[i];

		switch (mesh.type)
		{
		case cgltf_primitive_type_points:
			assert(mesh.indices.empty());
			simplifyPointMesh(mesh, settings.simplify_threshold);
			sortPointMesh(mesh);
			break;

		case cgltf_primitive_type_triangles:
			reindexMesh(mesh);
			simplifyMesh(mesh, settings.simplify_threshold, settings.simplify_aggressive);
			optimizeMesh(mesh);
			sortBoneInfluences(mesh);
			break;

		default:
			assert(!"Unknown primitive type");
		}
	}

	if (settings.verbose)
	{
		printMeshStats(meshes, "output");
	}

	QuantizationParams qp = prepareQuantization(meshes, settings);

	std::string json_images;
	std::string json_textures;
	std::string json_materials;
	std::string json_accessors;
	std::string json_meshes;
	std::string json_nodes;
	std::string json_skins;
	std::string json_roots;
	std::string json_animations;
	std::string json_cameras;
	std::string json_lights;

	std::vector<BufferView> views;

	bool ext_pbr_specular_glossiness = false;
	bool ext_unlit = false;

	size_t accr_offset = 0;
	size_t node_offset = 0;
	size_t mesh_offset = 0;
	size_t material_offset = 0;

	for (size_t i = 0; i < data->images_count; ++i)
	{
		const cgltf_image& image = data->images[i];

		comma(json_images);
		append(json_images, "{");
		if (image.uri)
		{
			std::string mime_type;
			std::string img;

			if (parseDataUri(image.uri, mime_type, img))
			{
				writeEmbeddedImage(json_images, views, img.c_str(), img.size(), mime_type.c_str());
			}
			else
			{
				append(json_images, "\"uri\":\"");
				append(json_images, image.uri);
				append(json_images, "\"");
			}
		}
		else if (image.buffer_view && image.buffer_view->buffer->data && image.mime_type)
		{
			const char* img = static_cast<const char*>(image.buffer_view->buffer->data) + image.buffer_view->offset;
			size_t size = image.buffer_view->size;

			writeEmbeddedImage(json_images, views, img, size, image.mime_type);
		}
		else
		{
			fprintf(stderr, "Warning: ignoring image %d since it has no URI and no valid buffer data\n", int(i));
		}

		append(json_images, "}");
	}

	for (size_t i = 0; i < data->textures_count; ++i)
	{
		const cgltf_texture& texture = data->textures[i];

		comma(json_textures);
		append(json_textures, "{");
		if (texture.image)
		{
			append(json_textures, "\"source\":");
			append(json_textures, size_t(texture.image - data->images));
		}
		append(json_textures, "}");
	}

	for (size_t i = 0; i < data->materials_count; ++i)
	{
		MaterialInfo& mi = materials[i];

		if (!mi.keep)
			continue;

		const cgltf_material& material = data->materials[i];

		comma(json_materials);
		append(json_materials, "{");
		writeMaterialInfo(json_materials, data, material, qp);
		append(json_materials, "}");

		mi.remap = int(material_offset);
		material_offset++;

		ext_pbr_specular_glossiness = ext_pbr_specular_glossiness || material.has_pbr_specular_glossiness;
		ext_unlit = ext_unlit || material.unlit;
	}

	for (size_t i = 0; i < meshes.size(); ++i)
	{
		const Mesh& mesh = meshes[i];

		comma(json_meshes);
		append(json_meshes, "{\"primitives\":[");

		size_t pi = i;
		for (; pi < meshes.size(); ++pi)
		{
			const Mesh& prim = meshes[pi];

			if (prim.node != mesh.node || prim.skin != mesh.skin || prim.targets != mesh.targets)
				break;

			if (!compareMeshTargets(mesh, prim))
				break;

			comma(json_meshes);
			append(json_meshes, "{\"attributes\":{");
			writeMeshAttributes(json_meshes, views, json_accessors, accr_offset, prim, 0, qp, settings);
			append(json_meshes, "}");
			append(json_meshes, ",\"mode\":");
			append(json_meshes, size_t(prim.type));

			if (mesh.targets)
			{
				append(json_meshes, ",\"targets\":[");
				for (size_t j = 0; j < mesh.targets; ++j)
				{
					comma(json_meshes);
					append(json_meshes, "{");
					writeMeshAttributes(json_meshes, views, json_accessors, accr_offset, prim, int(1 + j), qp, settings);
					append(json_meshes, "}");
				}
				append(json_meshes, "]");
			}

			if (!prim.indices.empty())
			{
				size_t index_accr = writeMeshIndices(views, json_accessors, accr_offset, prim, settings);

				append(json_meshes, ",\"indices\":");
				append(json_meshes, index_accr);
			}

			if (prim.material)
			{
				MaterialInfo& mi = materials[prim.material - data->materials];

				assert(mi.keep);
				append(json_meshes, ",\"material\":");
				append(json_meshes, size_t(mi.remap));
			}

			append(json_meshes, "}");
		}

		append(json_meshes, "]");

		if (mesh.target_weights.size())
		{
			append(json_meshes, ",\"weights\":[");
			for (size_t j = 0; j < mesh.target_weights.size(); ++j)
			{
				comma(json_meshes);
				append(json_meshes, mesh.target_weights[j]);
			}
			append(json_meshes, "]");
		}

		if (mesh.target_names.size())
		{
			append(json_meshes, ",\"extras\":{\"targetNames\":[");
			for (size_t j = 0; j < mesh.target_names.size(); ++j)
			{
				comma(json_meshes);
				append(json_meshes, "\"");
				append(json_meshes, mesh.target_names[j]);
				append(json_meshes, "\"");
			}
			append(json_meshes, "]}");
		}

		append(json_meshes, "}");

		writeMeshNode(json_nodes, mesh_offset, mesh, data, qp);

		if (mesh.node)
		{
			NodeInfo& ni = nodes[mesh.node - data->nodes];

			assert(ni.keep);
			ni.meshes.push_back(node_offset);
		}
		else
		{
			comma(json_roots);
			append(json_roots, node_offset);
		}

		node_offset++;
		mesh_offset++;

		// skip all meshes that we've written in this iteration
		assert(pi > i);
		i = pi - 1;
	}

	remapNodes(data, nodes, node_offset);

	for (size_t i = 0; i < data->nodes_count; ++i)
	{
		NodeInfo& ni = nodes[i];

		if (!ni.keep)
			continue;

		const cgltf_node& node = data->nodes[i];

		if (!node.parent)
		{
			comma(json_roots);
			append(json_roots, size_t(ni.remap));
		}

		writeNode(json_nodes, node, nodes, data);
	}

	for (size_t i = 0; i < data->skins_count; ++i)
	{
		const cgltf_skin& skin = data->skins[i];

		size_t matrix_accr = writeJointBindMatrices(views, json_accessors, accr_offset, skin, qp, settings);

		comma(json_skins);
		append(json_skins, "{");
		append(json_skins, "\"joints\":[");
		for (size_t j = 0; j < skin.joints_count; ++j)
		{
			comma(json_skins);
			append(json_skins, size_t(nodes[skin.joints[j] - data->nodes].remap));
		}
		append(json_skins, "]");
		append(json_skins, ",\"inverseBindMatrices\":");
		append(json_skins, matrix_accr);
		if (skin.skeleton)
		{
			comma(json_skins);
			append(json_skins, "\"skeleton\":");
			append(json_skins, size_t(nodes[skin.skeleton - data->nodes].remap));
		}
		append(json_skins, "}");
	}

	for (size_t i = 0; i < data->animations_count; ++i)
	{
		const cgltf_animation& animation = data->animations[i];

		writeAnimation(json_animations, views, json_accessors, accr_offset, animation, data, nodes, settings);
	}

	for (size_t i = 0; i < data->cameras_count; ++i)
	{
		const cgltf_camera& camera = data->cameras[i];

		writeCamera(json_cameras, camera);
	}

	for (size_t i = 0; i < data->lights_count; ++i)
	{
		const cgltf_light& light = data->lights[i];

		writeLight(json_lights, light);
	}

	char version[32];
	sprintf(version, "%d.%d", MESHOPTIMIZER_VERSION / 1000, (MESHOPTIMIZER_VERSION % 1000) / 10);

	append(json, "\"asset\":{");
	append(json, "\"version\":\"2.0\",\"generator\":\"gltfpack ");
	append(json, version);
	append(json, "\"");
	if (data->asset.extras.start_offset)
	{
		append(json, ",\"extras\":");
		json.append(data->json + data->asset.extras.start_offset, data->json + data->asset.extras.end_offset);
	}
	append(json, "}");
	append(json, ",\"extensionsUsed\":[");
	append(json, "\"MESHOPT_quantized_geometry\"");
	if (settings.compress)
	{
		comma(json);
		append(json, "\"MESHOPT_compression\"");
	}
	if (!json_textures.empty())
	{
		comma(json);
		append(json, "\"KHR_texture_transform\"");
	}
	if (ext_pbr_specular_glossiness)
	{
		comma(json);
		append(json, "\"KHR_materials_pbrSpecularGlossiness\"");
	}
	if (ext_unlit)
	{
		comma(json);
		append(json, "\"KHR_materials_unlit\"");
	}
	if (data->lights_count)
	{
		comma(json);
		append(json, "\"KHR_lights_punctual\"");
	}
	append(json, "]");
	if (settings.compress && !settings.fallback)
	{
		append(json, ",\"extensionsRequired\":[");
		// Note: ideally we should include MESHOPT_quantized_geometry in the required extension list (regardless of compression)
		// This extension *only* allows the use of quantized attributes for positions/normals/etc. This happens to be supported
		// by popular JS frameworks, however, Babylon.JS refuses to load files with unsupported required extensions.
		// For now we don't include it in the list, which will be fixed at some point once this extension becomes official.
		append(json, "\"MESHOPT_compression\"");
		append(json, "]");
	}

	if (!views.empty())
	{
		std::string json_views;
		finalizeBufferViews(json_views, views, bin, fallback);

		append(json, ",\"bufferViews\":[");
		append(json, json_views);
		append(json, "]");
	}
	if (!json_accessors.empty())
	{
		append(json, ",\"accessors\":[");
		append(json, json_accessors);
		append(json, "]");
	}
	if (!json_images.empty())
	{
		append(json, ",\"images\":[");
		append(json, json_images);
		append(json, "]");
	}
	if (!json_textures.empty())
	{
		append(json, ",\"textures\":[");
		append(json, json_textures);
		append(json, "]");
	}
	if (!json_materials.empty())
	{
		append(json, ",\"materials\":[");
		append(json, json_materials);
		append(json, "]");
	}
	if (!json_meshes.empty())
	{
		append(json, ",\"meshes\":[");
		append(json, json_meshes);
		append(json, "]");
	}
	if (!json_skins.empty())
	{
		append(json, ",\"skins\":[");
		append(json, json_skins);
		append(json, "]");
	}
	if (!json_animations.empty())
	{
		append(json, ",\"animations\":[");
		append(json, json_animations);
		append(json, "]");
	}
	if (!json_roots.empty())
	{
		append(json, ",\"nodes\":[");
		append(json, json_nodes);
		append(json, "],\"scenes\":[");
		append(json, "{\"nodes\":[");
		append(json, json_roots);
		append(json, "]}]");
	}
	if (!json_cameras.empty())
	{
		append(json, ",\"cameras\":[");
		append(json, json_cameras);
		append(json, "]");
	}
	if (!json_lights.empty())
	{
		append(json, ",\"extensions\":{\"KHR_lights_punctual\":{\"lights\":[");
		append(json, json_lights);
		append(json, "]}}");
	}
	if (!json_roots.empty())
	{
		append(json, ",\"scene\":0");
	}

	if (settings.verbose)
	{
		size_t bytes[BufferView::Kind_Count] = {};

		for (size_t i = 0; i < views.size(); ++i)
		{
			BufferView& view = views[i];
			bytes[view.kind] += view.bytes;
		}

		printf("output: %d nodes, %d meshes (%d primitives), %d materials\n", int(node_offset), int(mesh_offset), int(meshes.size()), int(material_offset));
		printf("output: JSON %d bytes, buffers %d bytes\n", int(json.size()), int(bin.size()));
		printf("output: buffers: vertex %d bytes, index %d bytes, skin %d bytes, time %d bytes, keyframe %d bytes, image %d bytes\n",
		       int(bytes[BufferView::Kind_Vertex]), int(bytes[BufferView::Kind_Index]), int(bytes[BufferView::Kind_Skin]),
		       int(bytes[BufferView::Kind_Time]), int(bytes[BufferView::Kind_Keyframe]), int(bytes[BufferView::Kind_Image]));
	}

	if (settings.verbose > 1)
	{
		printAttributeStats(views, BufferView::Kind_Vertex, "vertex");
		printAttributeStats(views, BufferView::Kind_Index, "index");
		printAttributeStats(views, BufferView::Kind_Keyframe, "keyframe");
	}
}

void writeU32(FILE* out, uint32_t data)
{
	fwrite(&data, 4, 1, out);
}

bool requiresExtension(cgltf_data* data, const char* name)
{
	for (size_t i = 0; i < data->extensions_required_count; ++i)
		if (strcmp(data->extensions_required[i], name) == 0)
			return true;

	return false;
}

const char* getBaseName(const char* path)
{
	const char* slash = strrchr(path, '/');
	const char* backslash = strrchr(path, '\\');

	const char* rs = slash ? slash + 1 : path;
	const char* bs = backslash ? backslash + 1 : path;

	return std::max(rs, bs);
}

std::string getBufferSpec(const char* bin_path, size_t bin_size, const char* fallback_path, size_t fallback_size, bool fallback_ref)
{
	std::string json;
	append(json, "\"buffers\":[");
	append(json, "{");
	if (bin_path)
	{
		append(json, "\"uri\":\"");
		append(json, bin_path);
		append(json, "\"");
	}
	comma(json);
	append(json, "\"byteLength\":");
	append(json, bin_size);
	append(json, "}");
	if (fallback_ref)
	{
		comma(json);
		append(json, "{");
		if (fallback_path)
		{
			append(json, "\"uri\":\"");
			append(json, fallback_path);
			append(json, "\"");
		}
		comma(json);
		append(json, "\"byteLength\":");
		append(json, fallback_size);
		append(json, ",\"extensions\":{");
		append(json, "\"MESHOPT_compression\":{");
		append(json, "\"fallback\":true");
		append(json, "}}");
		append(json, "}");
	}
	append(json, "]");

	return json;
}

int gltfpack(const char* input, const char* output, const Settings& settings)
{
	cgltf_data* data = 0;
	std::vector<Mesh> meshes;

	const char* iext = strrchr(input, '.');

	if (iext && (strcmp(iext, ".gltf") == 0 || strcmp(iext, ".GLTF") == 0 || strcmp(iext, ".glb") == 0 || strcmp(iext, ".GLB") == 0))
	{
		cgltf_options options = {};
		cgltf_result result = cgltf_parse_file(&options, input, &data);
		result = (result == cgltf_result_success) ? cgltf_validate(data) : result;
		result = (result == cgltf_result_success) ? cgltf_load_buffers(&options, data, input) : result;

		const char* error = NULL;

		if (result != cgltf_result_success)
			error = getError(result);
		else if (requiresExtension(data, "KHR_draco_mesh_compression"))
			error = "file requires Draco mesh compression support";
		else if (requiresExtension(data, "MESHOPT_compression"))
			error = "file has already been compressed using gltfpack";

		if (error)
		{
			fprintf(stderr, "Error loading %s: %s\n", input, error);
			cgltf_free(data);
			return 2;
		}

		parseMeshesGltf(data, meshes);
	}
	else if (iext && (strcmp(iext, ".obj") == 0 || strcmp(iext, ".OBJ") == 0))
	{
		fastObjMesh* obj = fast_obj_read(input);

		if (!obj)
		{
			fprintf(stderr, "Error loading %s: file not found\n", input);
			cgltf_free(data);
			return 2;
		}

		data = parseSceneObj(obj);
		parseMeshesObj(obj, data, meshes);

		fast_obj_destroy(obj);
	}
	else
	{
		fprintf(stderr, "Error loading %s: unknown extension (expected .gltf or .glb or .obj)\n", input);
		return 2;
	}

	std::string json, bin, fallback;
	process(data, meshes, settings, json, bin, fallback);

	cgltf_free(data);

	if (!output)
	{
		return 0;
	}

	const char* oext = strrchr(output, '.');

	if (oext && (strcmp(oext, ".gltf") == 0 || strcmp(oext, ".GLTF") == 0))
	{
		std::string binpath = output;
		binpath.replace(binpath.size() - 5, 5, ".bin");

		std::string fbpath = output;
		fbpath.replace(fbpath.size() - 5, 5, ".fallback.bin");

		FILE* outjson = fopen(output, "wb");
		FILE* outbin = fopen(binpath.c_str(), "wb");
		FILE* outfb = settings.fallback ? fopen(fbpath.c_str(), "wb") : NULL;
		if (!outjson || !outbin || (!outfb && settings.fallback))
		{
			fprintf(stderr, "Error saving %s\n", output);
			return 4;
		}

		std::string bufferspec = getBufferSpec(getBaseName(binpath.c_str()), bin.size(), settings.fallback ? getBaseName(fbpath.c_str()) : NULL, fallback.size(), settings.compress);

		fprintf(outjson, "{");
		fwrite(bufferspec.c_str(), bufferspec.size(), 1, outjson);
		fprintf(outjson, ",");
		fwrite(json.c_str(), json.size(), 1, outjson);
		fprintf(outjson, "}");

		fwrite(bin.c_str(), bin.size(), 1, outbin);

		if (settings.fallback)
			fwrite(fallback.c_str(), fallback.size(), 1, outfb);

		fclose(outjson);
		fclose(outbin);
		if (outfb)
			fclose(outfb);
	}
	else if (oext && (strcmp(oext, ".glb") == 0 || strcmp(oext, ".GLB") == 0))
	{
		std::string fbpath = output;
		fbpath.replace(fbpath.size() - 4, 4, ".fallback.bin");

		FILE* out = fopen(output, "wb");
		FILE* outfb = settings.fallback ? fopen(fbpath.c_str(), "wb") : NULL;
		if (!out || (!outfb && settings.fallback))
		{
			fprintf(stderr, "Error saving %s\n", output);
			return 4;
		}

		std::string bufferspec = getBufferSpec(NULL, bin.size(), settings.fallback ? getBaseName(fbpath.c_str()) : NULL, fallback.size(), settings.compress);

		json.insert(0, "{" + bufferspec + ",");
		json.push_back('}');

		while (json.size() % 4)
			json.push_back(' ');

		while (bin.size() % 4)
			bin.push_back('\0');

		writeU32(out, 0x46546C67);
		writeU32(out, 2);
		writeU32(out, uint32_t(12 + 8 + json.size() + 8 + bin.size()));

		writeU32(out, uint32_t(json.size()));
		writeU32(out, 0x4E4F534A);
		fwrite(json.c_str(), json.size(), 1, out);

		writeU32(out, uint32_t(bin.size()));
		writeU32(out, 0x004E4942);
		fwrite(bin.c_str(), bin.size(), 1, out);

		if (settings.fallback)
			fwrite(fallback.c_str(), fallback.size(), 1, outfb);

		fclose(out);
		if (outfb)
			fclose(outfb);
	}
	else
	{
		fprintf(stderr, "Error saving %s: unknown extension (expected .gltf or .glb)\n", output);
		return 4;
	}

	return 0;
}

int main(int argc, char** argv)
{
	Settings settings = {};
	settings.pos_bits = 14;
	settings.tex_bits = 12;
	settings.nrm_bits = 8;
	settings.anim_freq = 30;
	settings.simplify_threshold = 1.f;

	const char* input = 0;
	const char* output = 0;
	bool help = false;
	int test = 0;

	for (int i = 1; i < argc; ++i)
	{
		const char* arg = argv[i];

		if (strcmp(arg, "-vp") == 0 && i + 1 < argc && isdigit(argv[i + 1][0]))
		{
			settings.pos_bits = atoi(argv[++i]);
		}
		else if (strcmp(arg, "-vt") == 0 && i + 1 < argc && isdigit(argv[i + 1][0]))
		{
			settings.tex_bits = atoi(argv[++i]);
		}
		else if (strcmp(arg, "-vn") == 0 && i + 1 < argc && isdigit(argv[i + 1][0]))
		{
			settings.nrm_bits = atoi(argv[++i]);
		}
		else if (strcmp(arg, "-vu") == 0)
		{
			settings.nrm_unit = true;
		}
		else if (strcmp(arg, "-af") == 0 && i + 1 < argc && isdigit(argv[i + 1][0]))
		{
			settings.anim_freq = atoi(argv[++i]);
		}
		else if (strcmp(arg, "-ac") == 0)
		{
			settings.anim_const = true;
		}
		else if (strcmp(arg, "-kn") == 0)
		{
			settings.keep_named = true;
		}
		else if (strcmp(arg, "-si") == 0 && i + 1 < argc && isdigit(argv[i + 1][0]))
		{
			settings.simplify_threshold = float(atof(argv[++i]));
		}
		else if (strcmp(arg, "-sa") == 0)
		{
			settings.simplify_aggressive = true;
		}
		else if (strcmp(arg, "-i") == 0 && i + 1 < argc && !input)
		{
			input = argv[++i];
		}
		else if (strcmp(arg, "-o") == 0 && i + 1 < argc && !output)
		{
			output = argv[++i];
		}
		else if (strcmp(arg, "-c") == 0)
		{
			settings.compress = true;
		}
		else if (strcmp(arg, "-cf") == 0)
		{
			settings.compress = true;
			settings.fallback = true;
		}
		else if (strcmp(arg, "-v") == 0)
		{
			settings.verbose = 1;
		}
		else if (strcmp(arg, "-vv") == 0)
		{
			settings.verbose = 2;
		}
		else if (strcmp(arg, "-h") == 0)
		{
			help = true;
		}
		else if (strcmp(arg, "-test") == 0)
		{
			test = i + 1;
			break;
		}
		else
		{
			fprintf(stderr, "Unrecognized option %s\n", arg);
			return 1;
		}
	}

	if (test)
	{
		for (int i = test; i < argc; ++i)
		{
			printf("%s\n", argv[i]);
			gltfpack(argv[i], NULL, settings);
		}

		return 0;
	}

	if (!input || !output || help)
	{
		fprintf(stderr, "Usage: gltfpack [options] -i input -o output\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "Options:\n");
		fprintf(stderr, "-i file: input file to process, .obj/.gltf/.glb\n");
		fprintf(stderr, "-o file: output file path, .gltf/.glb\n");
		fprintf(stderr, "-vp N: use N-bit quantization for positions (default: 14; N should be between 1 and 16)\n");
		fprintf(stderr, "-vt N: use N-bit quantization for texture corodinates (default: 12; N should be between 1 and 16)\n");
		fprintf(stderr, "-vn N: use N-bit quantization for normals and tangents (default: 8; N should be between 1 and 16)\n");
		fprintf(stderr, "-vu: use unit-length normal/tangent vectors (default: off)\n");
		fprintf(stderr, "-af N: resample animations at N Hz (default: 30)\n");
		fprintf(stderr, "-ac: keep constant animation tracks even if they don't modify the node transform\n");
		fprintf(stderr, "-kn: keep named nodes and meshes attached to named nodes so that named nodes can be transformed externally\n");
		fprintf(stderr, "-si R: simplify meshes to achieve the ratio R (default: 1; R should be between 0 and 1)\n");
		fprintf(stderr, "-sa: aggressively simplify to the target ratio disregarding quality\n");
		fprintf(stderr, "-c: produce compressed gltf/glb files\n");
		fprintf(stderr, "-cf: produce compressed gltf/glb files with fallback for loaders that don't support compression\n");
		fprintf(stderr, "-v: verbose output\n");
		fprintf(stderr, "-h: display this help and exit\n");

		return 1;
	}

	return gltfpack(input, output, settings);
}
