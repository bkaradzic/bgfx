#define _CRT_SECURE_NO_WARNINGS

#include "../src/meshoptimizer.h"
#include "fast_obj.h"
#include "cgltf.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <vector>

#include <GLFW/glfw3.h>

#ifdef _WIN32
#pragma comment(lib, "opengl32.lib")
#endif

extern unsigned char* meshopt_simplifyDebugKind;
extern unsigned int* meshopt_simplifyDebugLoop;

#ifndef TRACE
unsigned char* meshopt_simplifyDebugKind;
unsigned int* meshopt_simplifyDebugLoop;
#endif

struct Options
{
	bool wireframe;
	enum
	{
		Mode_Default,
		Mode_Texture,
		Mode_Normals,
		Mode_UV,
		Mode_Kind,
	} mode;
};

struct Vertex
{
	float px, py, pz;
	float nx, ny, nz;
	float tx, ty;
};

struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	bool hasnormals;
	bool hastexture;

	// TODO: this is debug only visualization and will go away at some point
	std::vector<unsigned char> kinds;
	std::vector<unsigned int> loop;
};

Mesh parseObj(const char* path)
{
	fastObjMesh* obj = fast_obj_read(path);
	if (!obj)
	{
		printf("Error loading %s: file not found\n", path);
		return Mesh();
	}

	size_t total_indices = 0;

	for (unsigned int i = 0; i < obj->face_count; ++i)
		total_indices += 3 * (obj->face_vertices[i] - 2);

	std::vector<Vertex> vertices(total_indices);

	size_t vertex_offset = 0;
	size_t index_offset = 0;

	bool hasnormals = false;
	bool hastexture = false;

	for (unsigned int i = 0; i < obj->face_count; ++i)
	{
		for (unsigned int j = 0; j < obj->face_vertices[i]; ++j)
		{
			fastObjIndex gi = obj->indices[index_offset + j];

			Vertex v =
			{
				obj->positions[gi.p * 3 + 0],
				obj->positions[gi.p * 3 + 1],
				obj->positions[gi.p * 3 + 2],
				obj->normals[gi.n * 3 + 0],
				obj->normals[gi.n * 3 + 1],
				obj->normals[gi.n * 3 + 2],
				obj->texcoords[gi.t * 2 + 0],
				obj->texcoords[gi.t * 2 + 1],
			};

			hasnormals |= (gi.n > 0);
			hastexture |= (gi.t > 0);

			// triangulate polygon on the fly; offset-3 is always the first polygon vertex
			if (j >= 3)
			{
				vertices[vertex_offset + 0] = vertices[vertex_offset - 3];
				vertices[vertex_offset + 1] = vertices[vertex_offset - 1];
				vertex_offset += 2;
			}

			vertices[vertex_offset] = v;
			vertex_offset++;
		}

		index_offset += obj->face_vertices[i];
	}

	fast_obj_destroy(obj);

	Mesh result;

	std::vector<unsigned int> remap(total_indices);
	size_t total_vertices = meshopt_generateVertexRemap(&remap[0], NULL, total_indices, &vertices[0], total_indices, sizeof(Vertex));

	result.indices.resize(total_indices);
	meshopt_remapIndexBuffer(&result.indices[0], NULL, total_indices, &remap[0]);

	result.vertices.resize(total_vertices);
	meshopt_remapVertexBuffer(&result.vertices[0], &vertices[0], total_indices, sizeof(Vertex), &remap[0]);

	result.hasnormals = hasnormals;
	result.hastexture = hastexture;

	return result;
}

cgltf_accessor* getAccessor(const cgltf_attribute* attributes, size_t attribute_count, cgltf_attribute_type type, int index = 0)
{
	for (size_t i = 0; i < attribute_count; ++i)
		if (attributes[i].type == type && attributes[i].index == index)
			return attributes[i].data;

	return 0;
}

Mesh parseGltf(const char* path)
{
	cgltf_options options = {};
	cgltf_data* data = 0;
	cgltf_result res = cgltf_parse_file(&options, path, &data);

	if (res != cgltf_result_success)
	{
		return Mesh();
	}

	res = cgltf_load_buffers(&options, data, path);
	if (res != cgltf_result_success)
	{
		cgltf_free(data);
		return Mesh();
	}

	res = cgltf_validate(data);
	if (res != cgltf_result_success)
	{
		cgltf_free(data);
		return Mesh();
	}

	size_t total_vertices = 0;
	size_t total_indices = 0;

	for (size_t ni = 0; ni < data->nodes_count; ++ni)
	{
		if (!data->nodes[ni].mesh)
			continue;

		const cgltf_mesh& mesh = *data->nodes[ni].mesh;

		for (size_t pi = 0; pi < mesh.primitives_count; ++pi)
		{
			const cgltf_primitive& primitive = mesh.primitives[pi];

			cgltf_accessor* ai = primitive.indices;
			cgltf_accessor* ap = getAccessor(primitive.attributes, primitive.attributes_count, cgltf_attribute_type_position);

			if (!ai || !ap)
				continue;

			total_vertices += ap->count;
			total_indices += ai->count;
		}
	}

	Mesh result;
	result.vertices.resize(total_vertices);
	result.indices.resize(total_indices);

	size_t vertex_offset = 0;
	size_t index_offset = 0;

	bool hasnormals = false;
	bool hastexture = false;

	for (size_t ni = 0; ni < data->nodes_count; ++ni)
	{
		if (!data->nodes[ni].mesh)
			continue;

		const cgltf_mesh& mesh = *data->nodes[ni].mesh;

		float transform[16];
		cgltf_node_transform_world(&data->nodes[ni], transform);

		for (size_t pi = 0; pi < mesh.primitives_count; ++pi)
		{
			const cgltf_primitive& primitive = mesh.primitives[pi];

			cgltf_accessor* ai = primitive.indices;
			cgltf_accessor* ap = getAccessor(primitive.attributes, primitive.attributes_count, cgltf_attribute_type_position);

			if (!ai || !ap)
				continue;

			for (size_t i = 0; i < ai->count; ++i)
				result.indices[index_offset + i] = unsigned(vertex_offset + cgltf_accessor_read_index(ai, i));

			{
				for (size_t i = 0; i < ap->count; ++i)
				{
					float ptr[3];
					cgltf_accessor_read_float(ap, i, ptr, 3);

					result.vertices[vertex_offset + i].px = ptr[0] * transform[0] + ptr[1] * transform[4] + ptr[2] * transform[8] + transform[12];
					result.vertices[vertex_offset + i].py = ptr[0] * transform[1] + ptr[1] * transform[5] + ptr[2] * transform[9] + transform[13];
					result.vertices[vertex_offset + i].pz = ptr[0] * transform[2] + ptr[1] * transform[6] + ptr[2] * transform[10] + transform[14];
				}
			}

			if (cgltf_accessor* an = getAccessor(primitive.attributes, primitive.attributes_count, cgltf_attribute_type_normal))
			{
				for (size_t i = 0; i < ap->count; ++i)
				{
					float ptr[3];
					cgltf_accessor_read_float(an, i, ptr, 3);

					result.vertices[vertex_offset + i].nx = ptr[0] * transform[0] + ptr[1] * transform[4] + ptr[2] * transform[8];
					result.vertices[vertex_offset + i].ny = ptr[0] * transform[1] + ptr[1] * transform[5] + ptr[2] * transform[9];
					result.vertices[vertex_offset + i].nz = ptr[0] * transform[2] + ptr[1] * transform[6] + ptr[2] * transform[10];
				}

				hasnormals = true;
			}

			if (cgltf_accessor* at = getAccessor(primitive.attributes, primitive.attributes_count, cgltf_attribute_type_texcoord))
			{
				for (size_t i = 0; i < ap->count; ++i)
				{
					float ptr[2];
					cgltf_accessor_read_float(at, i, ptr, 2);

					result.vertices[vertex_offset + i].tx = ptr[0];
					result.vertices[vertex_offset + i].ty = ptr[1];
				}

				hastexture = true;
			}

			vertex_offset += ap->count;
			index_offset += ai->count;
		}
	}

	result.hasnormals = hasnormals;
	result.hastexture = hastexture;

	std::vector<unsigned int> remap(total_indices);
	size_t unique_vertices = meshopt_generateVertexRemap(&remap[0], &result.indices[0], total_indices, &result.vertices[0], total_vertices, sizeof(Vertex));

	meshopt_remapIndexBuffer(&result.indices[0], &result.indices[0], total_indices, &remap[0]);
	meshopt_remapVertexBuffer(&result.vertices[0], &result.vertices[0], total_vertices, sizeof(Vertex), &remap[0]);

	result.vertices.resize(unique_vertices);

	cgltf_free(data);

	return result;
}

Mesh loadMesh(const char* path)
{
	if (strstr(path, ".obj"))
		return parseObj(path);

	if (strstr(path, ".gltf") || strstr(path, ".glb"))
		return parseGltf(path);

	return Mesh();
}

bool saveObj(const Mesh& mesh, const char* path)
{
	std::vector<Vertex> verts = mesh.vertices;
	std::vector<unsigned int> tris = mesh.indices;
	size_t vertcount = meshopt_optimizeVertexFetch(verts.data(), tris.data(), tris.size(), verts.data(), verts.size(), sizeof(Vertex));

	FILE* obj = fopen(path, "w");
	if (!obj)
		return false;

	for (size_t i = 0; i < vertcount; ++i)
	{
		fprintf(obj, "v %f %f %f\n", verts[i].px, verts[i].py, verts[i].pz);

		if (mesh.hasnormals)
			fprintf(obj, "vn %f %f %f\n", verts[i].nx, verts[i].ny, verts[i].nz);

		if (mesh.hastexture)
			fprintf(obj, "vt %f %f %f\n", verts[i].tx, verts[i].ty, 0.f);
	}

	for (size_t i = 0; i < tris.size(); i += 3)
	{
		unsigned int i0 = tris[i + 0] + 1;
		unsigned int i1 = tris[i + 1] + 1;
		unsigned int i2 = tris[i + 2] + 1;

		if (mesh.hasnormals && mesh.hastexture)
			fprintf(obj, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", i0, i0, i0, i1, i1, i1, i2, i2, i2);
		else if (mesh.hasnormals && !mesh.hastexture)
			fprintf(obj, "f %d//%d %d//%d %d//%d\n", i0, i0, i1, i1, i2, i2);
		else if (!mesh.hasnormals && mesh.hastexture)
			fprintf(obj, "f %d/%d %d/%d %d/%d\n", i0, i0, i1, i1, i2, i2);
		else
			fprintf(obj, "f %d %d %dd\n", i0, i1, i2);
	}

	fclose(obj);

	return true;
}

Mesh optimize(const Mesh& mesh, int lod)
{
	float threshold = powf(0.5f, float(lod));
	size_t target_index_count = size_t(mesh.indices.size() * threshold);
	float target_error = 1e-2f;

	Mesh result = mesh;
	result.kinds.resize(result.vertices.size());
	result.loop.resize(result.vertices.size());
	meshopt_simplifyDebugKind = &result.kinds[0];
	meshopt_simplifyDebugLoop = &result.loop[0];
	result.indices.resize(meshopt_simplify(&result.indices[0], &result.indices[0], mesh.indices.size(), &mesh.vertices[0].px, mesh.vertices.size(), sizeof(Vertex), target_index_count, target_error));

	return result;
}

void computeNormals(Mesh& mesh)
{
	if (mesh.hasnormals)
		return;

	for (size_t i = 0; i < mesh.vertices.size(); ++i)
	{
		Vertex& v = mesh.vertices[i];

		v.nx = v.ny = v.nz = 0.f;
	}

	for (size_t i = 0; i < mesh.indices.size(); i += 3)
	{
		Vertex& v0 = mesh.vertices[mesh.indices[i + 0]];
		Vertex& v1 = mesh.vertices[mesh.indices[i + 1]];
		Vertex& v2 = mesh.vertices[mesh.indices[i + 2]];

		float v10[3] = {v1.px - v0.px, v1.py - v0.py, v1.pz - v0.pz};
		float v20[3] = {v2.px - v0.px, v2.py - v0.py, v2.pz - v0.pz};

		float normalx = v10[1] * v20[2] - v10[2] * v20[1];
		float normaly = v10[2] * v20[0] - v10[0] * v20[2];
		float normalz = v10[0] * v20[1] - v10[1] * v20[0];

		v0.nx += normalx;
		v0.ny += normaly;
		v0.nz += normalz;

		v1.nx += normalx;
		v1.ny += normaly;
		v1.nz += normalz;

		v2.nx += normalx;
		v2.ny += normaly;
		v2.nz += normalz;
	}

	for (size_t i = 0; i < mesh.vertices.size(); ++i)
	{
		Vertex& v = mesh.vertices[i];

		float nl = sqrtf(v.nx * v.nx + v.ny * v.ny + v.nz * v.nz);
		float ns = (nl == 0.f) ? 0.f : 1.f / nl;

		v.nx *= ns;
		v.ny *= ns;
		v.nz *= ns;
	}
}

void display(int x, int y, int width, int height, const Mesh& mesh, const Options& options)
{
	glViewport(x, y, width, height);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(0.f, 0.f, 1.f, 0.f);

	glPolygonMode(GL_FRONT_AND_BACK, options.wireframe ? GL_LINE : GL_FILL);

	float centerx = 0;
	float centery = 0;
	float centerz = 0;
	float centeru = 0;
	float centerv = 0;

	for (size_t i = 0; i < mesh.vertices.size(); ++i)
	{
		const Vertex& v = mesh.vertices[i];

		centerx += v.px;
		centery += v.py;
		centerz += v.pz;
		centeru += v.tx;
		centerv += v.ty;
	}

	centerx /= float(mesh.vertices.size());
	centery /= float(mesh.vertices.size());
	centerz /= float(mesh.vertices.size());
	centeru /= float(mesh.vertices.size());
	centerv /= float(mesh.vertices.size());

	float extent = 0;
	float extentuv = 0;

	for (size_t i = 0; i < mesh.vertices.size(); ++i)
	{
		const Vertex& v = mesh.vertices[i];

		extent = std::max(extent, fabsf(v.px - centerx));
		extent = std::max(extent, fabsf(v.py - centery));
		extent = std::max(extent, fabsf(v.pz - centerz));
		extentuv = std::max(extentuv, fabsf(v.tx - centeru));
		extentuv = std::max(extentuv, fabsf(v.ty - centerv));
	}

	extent *= 1.1f;
	extentuv *= 1.1f;

	float scalex = width > height ? float(height) / float(width) : 1;
	float scaley = height > width ? float(width) / float(height) : 1;

	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < mesh.indices.size(); ++i)
	{
		const Vertex& v = mesh.vertices[mesh.indices[i]];

		float intensity = -(v.pz - centerz) / extent * 0.5f + 0.5f;

		switch (options.mode)
		{
		case Options::Mode_UV:
			glColor3f(intensity, intensity, intensity);
			glVertex3f((v.tx - centeru) / extentuv * scalex, (v.ty - centerv) / extentuv * scaley, 0);
			break;

		case Options::Mode_Texture:
			glColor3f(v.tx - floorf(v.tx), v.ty - floorf(v.ty), 0.5f);
			glVertex3f((v.px - centerx) / extent * scalex, (v.py - centery) / extent * scaley, (v.pz - centerz) / extent);
			break;

		case Options::Mode_Normals:
			glColor3f(v.nx * 0.5f + 0.5f, v.ny * 0.5f + 0.5f, v.nz * 0.5f + 0.5f);
			glVertex3f((v.px - centerx) / extent * scalex, (v.py - centery) / extent * scaley, (v.pz - centerz) / extent);
			break;

		default:
			glColor3f(intensity, intensity, intensity);
			glVertex3f((v.px - centerx) / extent * scalex, (v.py - centery) / extent * scaley, (v.pz - centerz) / extent);
		}
	}

	glEnd();

	float zbias = 1e-3f;

	if (options.mode == Options::Mode_Kind && !mesh.kinds.empty() && !mesh.loop.empty())
	{
		glLineWidth(1);

		glBegin(GL_LINES);

		for (size_t i = 0; i < mesh.indices.size(); ++i)
		{
			unsigned int a = mesh.indices[i];
			unsigned int b = mesh.loop[a];

			if (b != ~0u)
			{
				const Vertex& v0 = mesh.vertices[a];
				const Vertex& v1 = mesh.vertices[b];

				unsigned char kind = mesh.kinds[a];

				glColor3f(kind == 0 || kind == 4, kind == 0 || kind == 2 || kind == 3, kind == 0 || kind == 1 || kind == 3);
				glVertex3f((v0.px - centerx) / extent * scalex, (v0.py - centery) / extent * scaley, (v0.pz - centerz) / extent - zbias);
				glVertex3f((v1.px - centerx) / extent * scalex, (v1.py - centery) / extent * scaley, (v1.pz - centerz) / extent - zbias);
			}
		}

		glEnd();

		glPointSize(3);

		glBegin(GL_POINTS);

		for (size_t i = 0; i < mesh.indices.size(); ++i)
		{
			const Vertex& v = mesh.vertices[mesh.indices[i]];
			unsigned char kind = mesh.kinds[mesh.indices[i]];

			if (kind != 0)
			{
				glColor3f(kind == 0 || kind == 4, kind == 0 || kind == 2 || kind == 3, kind == 0 || kind == 1 || kind == 3);
				glVertex3f((v.px - centerx) / extent * scalex, (v.py - centery) / extent * scaley, (v.pz - centerz) / extent - zbias * 2);
			}
		}

		glEnd();
	}
}

void stats(GLFWwindow* window, const char* path, unsigned int triangles, int lod, double time)
{
	char title[256];
	snprintf(title, sizeof(title), "%s: LOD %d - %d triangles (%.1f msec)", path, lod, triangles, time * 1000);

	glfwSetWindowTitle(window, title);
}

struct File
{
	Mesh basemesh;
	Mesh lodmesh;
	const char* path;
};

std::vector<File> files;
Options options;
bool redraw;

void keyhandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
		{
			options.wireframe = !options.wireframe;
			redraw = true;
		}
		else if (key == GLFW_KEY_T)
		{
			options.mode = options.mode == Options::Mode_Texture ? Options::Mode_Default : Options::Mode_Texture;
			redraw = true;
		}
		else if (key == GLFW_KEY_N)
		{
			options.mode = options.mode == Options::Mode_Normals ? Options::Mode_Default : Options::Mode_Normals;
			redraw = true;
		}
		else if (key == GLFW_KEY_U)
		{
			options.mode = options.mode == Options::Mode_UV ? Options::Mode_Default : Options::Mode_UV;
			redraw = true;
		}
		else if (key == GLFW_KEY_K)
		{
			options.mode = options.mode == Options::Mode_Kind ? Options::Mode_Default : Options::Mode_Kind;
			redraw = true;
		}
		else if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
		{
			int lod = int(key - GLFW_KEY_0);

			unsigned int triangles = 0;

			clock_t start = clock();
			for (auto& f : files)
			{
				f.lodmesh = optimize(f.basemesh, lod);
				triangles += unsigned(f.lodmesh.indices.size() / 3);
			}
			clock_t end = clock();

			stats(window, files[0].path, triangles, lod, double(end - start) / CLOCKS_PER_SEC);
			redraw = true;
		}
		else if (key == GLFW_KEY_S)
		{
			int i = 0;

			for (auto& f : files)
			{
				char path[32];
				sprintf(path, "result%d.obj", i);

				saveObj(f.lodmesh, path);

				printf("Saved LOD of %s to %s\n", f.path, path);
			}
		}
	}
}

void sizehandler(GLFWwindow* window, int width, int height)
{
	redraw = true;
}

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		printf("Usage: %s [.obj files]\n", argv[0]);
		return 0;
	}

	unsigned int basetriangles = 0;

	for (int i = 1; i < argc; ++i)
	{
		files.emplace_back();
		File& f = files.back();

		f.path = argv[i];
		f.basemesh = loadMesh(f.path);
		f.lodmesh = optimize(f.basemesh, 0);

		basetriangles += unsigned(f.basemesh.indices.size() / 3);
	}

	glfwInit();

	GLFWwindow* window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	glfwMakeContextCurrent(window);

	stats(window, files[0].path, basetriangles, 0, 0);

	glfwSetKeyCallback(window, keyhandler);
	glfwSetWindowSizeCallback(window, sizehandler);

	redraw = true;

	while (!glfwWindowShouldClose(window))
	{
		if (redraw)
		{
			redraw = false;

			int width, height;
			glfwGetFramebufferSize(window, &width, &height);

			glViewport(0, 0, width, height);
			glClearDepth(1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			int cols = int(ceil(sqrt(double(files.size()))));
			int rows = int(ceil(double(files.size()) / cols));

			int tilew = width / cols;
			int tileh = height / rows;

			for (size_t i = 0; i < files.size(); ++i)
			{
				File& f = files[i];
				int x = int(i) % cols;
				int y = int(i) / cols;

				if (options.mode == Options::Mode_Normals)
					computeNormals(f.lodmesh);

				display(x * tilew, y * tileh, tilew, tileh, f.lodmesh, options);
			}

			glfwSwapBuffers(window);
		}

		glfwWaitEvents();
	}
}
