#define _CRT_SECURE_NO_WARNINGS

#include "../src/meshoptimizer.h"
#include "objparser.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <vector>

#include <GLFW/glfw3.h>

#ifdef GLTF
#define CGLTF_IMPLEMENTATION
#include "cgltf.h"
#endif

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

	// TODO: this is debug only visualization and will go away at some point
	std::vector<unsigned char> kinds;
	std::vector<unsigned int> loop;
};

Mesh parseObj(const char* path)
{
	ObjFile file;

	if (!objParseFile(file, path) || !objValidate(file))
	{
		printf("Error loading %s\n", path);
		return Mesh();
	}

	size_t total_indices = file.f_size / 3;

	std::vector<Vertex> vertices(total_indices);

	for (size_t i = 0; i < total_indices; ++i)
	{
		int vi = file.f[i * 3 + 0];
		int vti = file.f[i * 3 + 1];
		int vni = file.f[i * 3 + 2];

		Vertex v =
		    {
		        file.v[vi * 3 + 0],
		        file.v[vi * 3 + 1],
		        file.v[vi * 3 + 2],

		        vni >= 0 ? file.vn[vni * 3 + 0] : 0,
		        vni >= 0 ? file.vn[vni * 3 + 1] : 0,
		        vni >= 0 ? file.vn[vni * 3 + 2] : 0,

		        vti >= 0 ? file.vt[vti * 3 + 0] : 0,
		        vti >= 0 ? file.vt[vti * 3 + 1] : 0,
		    };

		vertices[i] = v;
	}

	Mesh result;

	std::vector<unsigned int> remap(total_indices);
	size_t total_vertices = meshopt_generateVertexRemap(&remap[0], NULL, total_indices, &vertices[0], total_indices, sizeof(Vertex));

	result.indices.resize(total_indices);
	meshopt_remapIndexBuffer(&result.indices[0], NULL, total_indices, &remap[0]);

	result.vertices.resize(total_vertices);
	meshopt_remapVertexBuffer(&result.vertices[0], &vertices[0], total_indices, sizeof(Vertex), &remap[0]);

	return result;
}

#ifdef GLTF
cgltf_accessor* getAccessor(const cgltf_attribute* attributes, size_t attribute_count, cgltf_attribute_type type, int index = 0)
{
	for (size_t i = 0; i < attribute_count; ++i)
		if (attributes[i].type == type && attributes[i].index == index)
			return attributes[i].data;

	return 0;
}

template <typename T>
const T* getComponentPtr(const cgltf_accessor* a)
{
	const char* buffer = (char*)a->buffer_view->buffer->data;
	size_t offset = a->offset + a->buffer_view->offset;

	return reinterpret_cast<const T*>(&buffer[offset]);
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

			if (ai->component_type == cgltf_component_type_r_32u)
			{
				const unsigned int* ptr = getComponentPtr<unsigned int>(ai);

				for (size_t i = 0; i < ai->count; ++i)
					result.indices[index_offset + i] = unsigned(vertex_offset + ptr[i]);
			}
			else
			{
				const unsigned short* ptr = getComponentPtr<unsigned short>(ai);

				for (size_t i = 0; i < ai->count; ++i)
					result.indices[index_offset + i] = unsigned(vertex_offset + ptr[i]);
			}

			{
				const float* ptr = getComponentPtr<float>(ap);

				for (size_t i = 0; i < ap->count; ++i)
				{
					result.vertices[vertex_offset + i].px = ptr[0] * transform[0] + ptr[1] * transform[4] + ptr[2] * transform[8] + transform[12];
					result.vertices[vertex_offset + i].py = ptr[0] * transform[1] + ptr[1] * transform[5] + ptr[2] * transform[9] + transform[13];
					result.vertices[vertex_offset + i].pz = ptr[0] * transform[2] + ptr[1] * transform[6] + ptr[2] * transform[10] + transform[14];
					ptr += ap->stride / 4;
				}
			}

			if (cgltf_accessor* an = getAccessor(primitive.attributes, primitive.attributes_count, cgltf_attribute_type_normal))
			{
				const float* ptr = getComponentPtr<float>(an);

				for (size_t i = 0; i < ap->count; ++i)
				{
					result.vertices[vertex_offset + i].nx = ptr[0] * transform[0] + ptr[1] * transform[4] + ptr[2] * transform[8];
					result.vertices[vertex_offset + i].ny = ptr[0] * transform[1] + ptr[1] * transform[5] + ptr[2] * transform[9];
					result.vertices[vertex_offset + i].nz = ptr[0] * transform[2] + ptr[1] * transform[6] + ptr[2] * transform[10];
					ptr += an->stride / 4;
				}
			}

			if (cgltf_accessor* at = getAccessor(primitive.attributes, primitive.attributes_count, cgltf_attribute_type_texcoord))
			{
				const float* ptr = getComponentPtr<float>(at);

				for (size_t i = 0; i < ap->count; ++i)
				{
					result.vertices[vertex_offset + i].tx = ptr[0];
					result.vertices[vertex_offset + i].ty = ptr[1];
					ptr += at->stride / 4;
				}
			}

			vertex_offset += ap->count;
			index_offset += ai->count;
		}
	}

	std::vector<unsigned int> remap(total_indices);
	size_t unique_vertices = meshopt_generateVertexRemap(&remap[0], &result.indices[0], total_indices, &result.vertices[0], total_vertices, sizeof(Vertex));

	meshopt_remapIndexBuffer(&result.indices[0], &result.indices[0], total_indices, &remap[0]);
	meshopt_remapVertexBuffer(&result.vertices[0], &result.vertices[0], total_vertices, sizeof(Vertex), &remap[0]);

	result.vertices.resize(unique_vertices);

	cgltf_free(data);

	return result;
}
#endif

Mesh loadMesh(const char* path)
{
	if (strstr(path, ".obj"))
		return parseObj(path);

#ifdef GLTF
	if (strstr(path, ".gltf") || strstr(path, ".glb"))
		return parseGltf(path);
#endif

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
		fprintf(obj, "vn %f %f %f\n", verts[i].nx, verts[i].ny, verts[i].nz);
		fprintf(obj, "vt %f %f %f\n", verts[i].tx, verts[i].ty, 0.f);
	}

	for (size_t i = 0; i < tris.size(); i += 3)
	{
		unsigned int i0 = tris[i + 0] + 1;
		unsigned int i1 = tris[i + 1] + 1;
		unsigned int i2 = tris[i + 2] + 1;

		fprintf(obj, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", i0, i0, i0, i1, i1, i1, i2, i2, i2);
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

				display(x * tilew, y * tileh, tilew, tileh, f.lodmesh, options);
			}

			glfwSwapBuffers(window);
		}

		glfwWaitEvents();
	}
}
