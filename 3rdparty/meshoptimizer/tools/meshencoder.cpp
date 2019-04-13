// Converts .obj files to .optmesh files
// Usage: meshencoder [.obj] [.optmesh]

// Data layout:
// Header: 64b
// Object table: 16b * object_count
// Object data
// Vertex data
// Index data

#include "../src/meshoptimizer.h"
#include "objparser.h"

#include <algorithm>
#include <vector>

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

struct Header
{
	char magic[4]; // OPTM

	unsigned int group_count;
	unsigned int vertex_count;
	unsigned int index_count;
	unsigned int vertex_data_size;
	unsigned int index_data_size;

	float pos_offset[3];
	float pos_scale;
	float uv_offset[2];
	float uv_scale[2];

	unsigned int reserved[2];
};

struct Object
{
	unsigned int index_offset;
	unsigned int index_count;
	unsigned int material_length;
	unsigned int reserved;
};

struct Vertex
{
	unsigned short px, py, pz, pw; // unsigned 16-bit value, use pos_offset/pos_scale to unpack
	char nx, ny, nz, nw; // normalized signed 8-bit value
	unsigned short tx, ty; // unsigned 16-bit value, use uv_offset/uv_scale to unpack
};

float rcpSafe(float v)
{
	return v == 0.f ? 0.f : 1.f / v;
}

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		printf("Usage: %s [.obj] [.optmesh]\n", argv[0]);
		return 1;
	}

	const char* input = argv[1];
	const char* output = argv[2];

	ObjFile file;

	if (!objParseFile(file, input))
	{
		printf("Error loading %s: file not found\n", input);
		return 2;
	}

	if (!objValidate(file))
	{
		printf("Error loading %s: invalid file data\n", input);
		return 3;
	}

	float pos_offset[3] = { FLT_MAX, FLT_MAX, FLT_MAX };
	float pos_scale = 0.f;

	for (size_t i = 0; i < file.v_size; i += 3)
	{
		pos_offset[0] = std::min(pos_offset[0], file.v[i + 0]);
		pos_offset[1] = std::min(pos_offset[1], file.v[i + 1]);
		pos_offset[2] = std::min(pos_offset[2], file.v[i + 2]);
	}

	for (size_t i = 0; i < file.v_size; i += 3)
	{
		pos_scale = std::max(pos_scale, file.v[i + 0] - pos_offset[0]);
		pos_scale = std::max(pos_scale, file.v[i + 1] - pos_offset[1]);
		pos_scale = std::max(pos_scale, file.v[i + 2] - pos_offset[2]);
	}

	float uv_offset[2] = { FLT_MAX, FLT_MAX };
	float uv_scale[2] = { 0, 0 };

	for (size_t i = 0; i < file.vt_size; i += 3)
	{
		uv_offset[0] = std::min(uv_offset[0], file.vt[i + 0]);
		uv_offset[1] = std::min(uv_offset[1], file.vt[i + 1]);
	}

	for (size_t i = 0; i < file.vt_size; i += 3)
	{
		uv_scale[0] = std::max(uv_scale[0], file.vt[i + 0] - uv_offset[0]);
		uv_scale[1] = std::max(uv_scale[1], file.vt[i + 1] - uv_offset[1]);
	}

	float pos_scale_inverse = rcpSafe(pos_scale);
	float uv_scale_inverse[2] = { rcpSafe(uv_scale[0]), rcpSafe(uv_scale[1]) };

	size_t total_indices = file.f_size / 3;

	std::vector<Vertex> triangles(total_indices);

	int pos_bits = 14;
	int uv_bits = 12;

	for (size_t i = 0; i < total_indices; ++i)
	{
		int vi = file.f[i * 3 + 0];
		int vti = file.f[i * 3 + 1];
		int vni = file.f[i * 3 + 2];

		// note: we scale the vertices uniformly; this is not the best option wrt compression quality
		// however, it means we can scale the mesh uniformly without distorting the normals
		// this is helpful for backends like ThreeJS that apply mesh scaling to normals
		float px = (file.v[vi * 3 + 0] - pos_offset[0]) * pos_scale_inverse;
		float py = (file.v[vi * 3 + 1] - pos_offset[1]) * pos_scale_inverse;
		float pz = (file.v[vi * 3 + 2] - pos_offset[2]) * pos_scale_inverse;

		// normal is 0 if absent from the mesh
		float nx = vni >= 0 ? file.vn[vni * 3 + 0] : 0;
		float ny = vni >= 0 ? file.vn[vni * 3 + 1] : 0;
		float nz = vni >= 0 ? file.vn[vni * 3 + 2] : 0;

		// scale the normal to make sure the largest component is +-1.0
		// this reduces the entropy of the normal by ~1.5 bits without losing precision
		// it's better to use octahedral encoding but that requires special shader support
		float nm = std::max(fabsf(nx), std::max(fabsf(ny), fabsf(nz)));
		float ns = nm == 0.f ? 0.f : 1 / nm;

		nx *= ns;
		ny *= ns;
		nz *= ns;

		// texture coordinates are 0 if absent, and require a texture matrix to decode
		float tx = vti >= 0 ? (file.vt[vti * 3 + 0] - uv_offset[0]) * uv_scale_inverse[0] : 0;
		float ty = vti >= 0 ? (file.vt[vti * 3 + 1] - uv_offset[1]) * uv_scale_inverse[1] : 0;

		Vertex v =
		    {
		        (unsigned short)(meshopt_quantizeUnorm(px, pos_bits)),
		        (unsigned short)(meshopt_quantizeUnorm(py, pos_bits)),
		        (unsigned short)(meshopt_quantizeUnorm(pz, pos_bits)),
				0,

		        char(meshopt_quantizeSnorm(nx, 8)),
		        char(meshopt_quantizeSnorm(ny, 8)),
		        char(meshopt_quantizeSnorm(nz, 8)),
				0,

		        (unsigned short)(meshopt_quantizeUnorm(tx, uv_bits)),
		        (unsigned short)(meshopt_quantizeUnorm(ty, uv_bits)),
		    };

		triangles[i] = v;
	}

	std::vector<unsigned int> remap(total_indices);

	size_t total_vertices = meshopt_generateVertexRemap(&remap[0], NULL, total_indices, &triangles[0], total_indices, sizeof(Vertex));

	std::vector<unsigned int> indices(total_indices);
	meshopt_remapIndexBuffer(&indices[0], NULL, total_indices, &remap[0]);

	std::vector<Vertex> vertices(total_vertices);
	meshopt_remapVertexBuffer(&vertices[0], &triangles[0], total_indices, sizeof(Vertex), &remap[0]);

	for (size_t i = 0; i < file.g_size; ++i)
	{
		ObjGroup& g = file.g[i];

		meshopt_optimizeVertexCache(&indices[g.index_offset], &indices[g.index_offset], g.index_count, vertices.size());
	}

	meshopt_optimizeVertexFetch(&vertices[0], &indices[0], indices.size(), &vertices[0], vertices.size(), sizeof(Vertex));

	std::vector<unsigned char> vbuf(meshopt_encodeVertexBufferBound(vertices.size(), sizeof(Vertex)));
	vbuf.resize(meshopt_encodeVertexBuffer(&vbuf[0], vbuf.size(), &vertices[0], vertices.size(), sizeof(Vertex)));

	std::vector<unsigned char> ibuf(meshopt_encodeIndexBufferBound(indices.size(), vertices.size()));
	ibuf.resize(meshopt_encodeIndexBuffer(&ibuf[0], ibuf.size(), &indices[0], indices.size()));

	FILE* result = fopen(output, "wb");
	if (!result)
	{
		printf("Error saving %s: can't open file for writing\n", output);
		return 4;
	}

	Header header = {};
	memcpy(header.magic, "OPTM", 4);

	header.group_count = unsigned(file.g_size);
	header.vertex_count = unsigned(vertices.size());
	header.index_count = unsigned(indices.size());
	header.vertex_data_size = unsigned(vbuf.size());
	header.index_data_size = unsigned(ibuf.size());

	header.pos_offset[0] = pos_offset[0];
	header.pos_offset[1] = pos_offset[1];
	header.pos_offset[2] = pos_offset[2];
	header.pos_scale = pos_scale / float((1 << pos_bits) - 1);

	header.uv_offset[0] = uv_offset[0];
	header.uv_offset[1] = uv_offset[1];
	header.uv_scale[0] = uv_scale[0] / float((1 << uv_bits) - 1);
	header.uv_scale[1] = uv_scale[1] / float((1 << uv_bits) - 1);

	fwrite(&header, 1, sizeof(header), result);

	for (size_t i = 0; i < file.g_size; ++i)
	{
		ObjGroup& g = file.g[i];

		Object object = {};
		object.index_offset = unsigned(g.index_offset);
		object.index_count = unsigned(g.index_count);
		object.material_length = unsigned(strlen(g.material));

		fwrite(&object, 1, sizeof(object), result);
	}

	for (size_t i = 0; i < file.g_size; ++i)
	{
		ObjGroup& g = file.g[i];

		fwrite(g.material, 1, strlen(g.material), result);
	}

	fwrite(&vbuf[0], 1, vbuf.size(), result);
	fwrite(&ibuf[0], 1, ibuf.size(), result);
	fclose(result);

	return 0;
}
