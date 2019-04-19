#include "../src/meshoptimizer.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <vector>

#include "../tools/objparser.h"
#include "miniz.h"

// This file uses assert() to verify algorithm correctness
#undef NDEBUG
#include <assert.h>

#if defined(__linux__)
double timestamp()
{
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return double(ts.tv_sec) + 1e-9 * double(ts.tv_nsec);
}
#elif defined(_WIN32)
struct LARGE_INTEGER
{
	__int64 QuadPart;
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(LARGE_INTEGER* lpFrequency);

double timestamp()
{
	LARGE_INTEGER freq, counter;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&counter);
	return double(counter.QuadPart) / double(freq.QuadPart);
}
#else
double timestamp()
{
	return double(clock()) / double(CLOCKS_PER_SEC);
}
#endif

const size_t kCacheSize = 16;

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
};

union Triangle {
	Vertex v[3];
	char data[sizeof(Vertex) * 3];
};

Mesh parseObj(const char* path, double& reindex)
{
	ObjFile file;

	if (!objParseFile(file, path))
	{
		printf("Error loading %s: file not found\n", path);
		return Mesh();
	}

	if (!objValidate(file))
	{
		printf("Error loading %s: invalid file data\n", path);
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

	reindex = timestamp();

	Mesh result;

	std::vector<unsigned int> remap(total_indices);

	size_t total_vertices = meshopt_generateVertexRemap(&remap[0], NULL, total_indices, &vertices[0], total_indices, sizeof(Vertex));

	result.indices.resize(total_indices);
	meshopt_remapIndexBuffer(&result.indices[0], NULL, total_indices, &remap[0]);

	result.vertices.resize(total_vertices);
	meshopt_remapVertexBuffer(&result.vertices[0], &vertices[0], total_indices, sizeof(Vertex), &remap[0]);

	return result;
}

bool isMeshValid(const Mesh& mesh)
{
	size_t index_count = mesh.indices.size();
	size_t vertex_count = mesh.vertices.size();

	if (index_count % 3 != 0)
		return false;

	const unsigned int* indices = &mesh.indices[0];

	for (size_t i = 0; i < index_count; ++i)
		if (indices[i] >= vertex_count)
			return false;

	return true;
}

bool rotateTriangle(Triangle& t)
{
	int c01 = memcmp(&t.v[0], &t.v[1], sizeof(Vertex));
	int c02 = memcmp(&t.v[0], &t.v[2], sizeof(Vertex));
	int c12 = memcmp(&t.v[1], &t.v[2], sizeof(Vertex));

	if (c12 < 0 && c01 > 0)
	{
		// 1 is minimum, rotate 012 => 120
		Vertex tv = t.v[0];
		t.v[0] = t.v[1], t.v[1] = t.v[2], t.v[2] = tv;
	}
	else if (c02 > 0 && c12 > 0)
	{
		// 2 is minimum, rotate 012 => 201
		Vertex tv = t.v[2];
		t.v[2] = t.v[1], t.v[1] = t.v[0], t.v[0] = tv;
	}

	return c01 != 0 && c02 != 0 && c12 != 0;
}

unsigned int hashRange(const char* key, size_t len)
{
	// MurmurHash2
	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	unsigned int h = 0;

	while (len >= 4)
	{
		unsigned int k = *reinterpret_cast<const unsigned int*>(key);

		k *= m;
		k ^= k >> r;
		k *= m;

		h *= m;
		h ^= k;

		key += 4;
		len -= 4;
	}

	return h;
}

unsigned int hashMesh(const Mesh& mesh)
{
	size_t triangle_count = mesh.indices.size() / 3;

	const Vertex* vertices = &mesh.vertices[0];
	const unsigned int* indices = &mesh.indices[0];

	unsigned int h1 = 0;
	unsigned int h2 = 0;

	for (size_t i = 0; i < triangle_count; ++i)
	{
		Triangle t;
		t.v[0] = vertices[indices[i * 3 + 0]];
		t.v[1] = vertices[indices[i * 3 + 1]];
		t.v[2] = vertices[indices[i * 3 + 2]];

		// skip degenerate triangles since some algorithms don't preserve them
		if (rotateTriangle(t))
		{
			unsigned int hash = hashRange(t.data, sizeof(t.data));

			h1 ^= hash;
			h2 += hash;
		}
	}

	return h1 * 0x5bd1e995 + h2;
}

void optNone(Mesh& mesh)
{
	(void)mesh;
}

void optRandomShuffle(Mesh& mesh)
{
	size_t triangle_count = mesh.indices.size() / 3;

	unsigned int* indices = &mesh.indices[0];

	unsigned int rng = 0;

	for (size_t i = triangle_count - 1; i > 0; --i)
	{
		// Fisher-Yates shuffle
		size_t j = rng % (i + 1);

		unsigned int t;
		t = indices[3 * j + 0], indices[3 * j + 0] = indices[3 * i + 0], indices[3 * i + 0] = t;
		t = indices[3 * j + 1], indices[3 * j + 1] = indices[3 * i + 1], indices[3 * i + 1] = t;
		t = indices[3 * j + 2], indices[3 * j + 2] = indices[3 * i + 2], indices[3 * i + 2] = t;

		// LCG RNG, constants from Numerical Recipes
		rng = rng * 1664525 + 1013904223;
	}
}

void optCache(Mesh& mesh)
{
	meshopt_optimizeVertexCache(&mesh.indices[0], &mesh.indices[0], mesh.indices.size(), mesh.vertices.size());
}

void optCacheFifo(Mesh& mesh)
{
	meshopt_optimizeVertexCacheFifo(&mesh.indices[0], &mesh.indices[0], mesh.indices.size(), mesh.vertices.size(), kCacheSize);
}

void optOverdraw(Mesh& mesh)
{
	// use worst-case ACMR threshold so that overdraw optimizer can sort *all* triangles
	// warning: this significantly deteriorates the vertex cache efficiency so it is not advised; look at optComplete for the recommended method
	const float kThreshold = 3.f;
	meshopt_optimizeOverdraw(&mesh.indices[0], &mesh.indices[0], mesh.indices.size(), &mesh.vertices[0].px, mesh.vertices.size(), sizeof(Vertex), kThreshold);
}

void optFetch(Mesh& mesh)
{
	meshopt_optimizeVertexFetch(&mesh.vertices[0], &mesh.indices[0], mesh.indices.size(), &mesh.vertices[0], mesh.vertices.size(), sizeof(Vertex));
}

void optFetchRemap(Mesh& mesh)
{
	// this produces results equivalent to optFetch, but can be used to remap multiple vertex streams
	std::vector<unsigned int> remap(mesh.vertices.size());
	meshopt_optimizeVertexFetchRemap(&remap[0], &mesh.indices[0], mesh.indices.size(), mesh.vertices.size());

	meshopt_remapIndexBuffer(&mesh.indices[0], &mesh.indices[0], mesh.indices.size(), &remap[0]);
	meshopt_remapVertexBuffer(&mesh.vertices[0], &mesh.vertices[0], mesh.vertices.size(), sizeof(Vertex), &remap[0]);
}

void optComplete(Mesh& mesh)
{
	// vertex cache optimization should go first as it provides starting order for overdraw
	meshopt_optimizeVertexCache(&mesh.indices[0], &mesh.indices[0], mesh.indices.size(), mesh.vertices.size());

	// reorder indices for overdraw, balancing overdraw and vertex cache efficiency
	const float kThreshold = 1.01f; // allow up to 1% worse ACMR to get more reordering opportunities for overdraw
	meshopt_optimizeOverdraw(&mesh.indices[0], &mesh.indices[0], mesh.indices.size(), &mesh.vertices[0].px, mesh.vertices.size(), sizeof(Vertex), kThreshold);

	// vertex fetch optimization should go last as it depends on the final index order
	meshopt_optimizeVertexFetch(&mesh.vertices[0], &mesh.indices[0], mesh.indices.size(), &mesh.vertices[0], mesh.vertices.size(), sizeof(Vertex));
}

struct PackedVertex
{
	unsigned short px, py, pz;
	unsigned short pw; // padding to 4b boundary
	signed char nx, ny, nz, nw;
	unsigned short tx, ty;
};

void packMesh(std::vector<PackedVertex>& pv, const std::vector<Vertex>& vertices)
{
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		const Vertex& vi = vertices[i];
		PackedVertex& pvi = pv[i];

		pvi.px = meshopt_quantizeHalf(vi.px);
		pvi.py = meshopt_quantizeHalf(vi.py);
		pvi.pz = meshopt_quantizeHalf(vi.pz);
		pvi.pw = 0;

		pvi.nx = char(meshopt_quantizeSnorm(vi.nx, 8));
		pvi.ny = char(meshopt_quantizeSnorm(vi.ny, 8));
		pvi.nz = char(meshopt_quantizeSnorm(vi.nz, 8));
		pvi.nw = 0;

		pvi.tx = meshopt_quantizeHalf(vi.tx);
		pvi.ty = meshopt_quantizeHalf(vi.ty);
	}
}

struct PackedVertexOct
{
	unsigned short px, py, pz;
	signed char nu, nv; // octahedron encoded normal, aliases .pw
	unsigned short tx, ty;
};

void packMesh(std::vector<PackedVertexOct>& pv, const std::vector<Vertex>& vertices)
{
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		const Vertex& vi = vertices[i];
		PackedVertexOct& pvi = pv[i];

		pvi.px = meshopt_quantizeHalf(vi.px);
		pvi.py = meshopt_quantizeHalf(vi.py);
		pvi.pz = meshopt_quantizeHalf(vi.pz);

		float nsum = fabsf(vi.nx) + fabsf(vi.ny) + fabsf(vi.nz);
		float nx = vi.nx / nsum;
		float ny = vi.ny / nsum;
		float nz = vi.nz;

		float nu = nz >= 0 ? nx : (1 - fabsf(ny)) * (nx >= 0 ? 1 : -1);
		float nv = nz >= 0 ? ny : (1 - fabsf(nx)) * (ny >= 0 ? 1 : -1);

		pvi.nu = char(meshopt_quantizeSnorm(nu, 8));
		pvi.nv = char(meshopt_quantizeSnorm(nv, 8));

		pvi.tx = meshopt_quantizeHalf(vi.tx);
		pvi.ty = meshopt_quantizeHalf(vi.ty);
	}
}

void simplify(const Mesh& mesh, float threshold = 0.2f)
{
	Mesh lod;

	double start = timestamp();

	size_t target_index_count = size_t(mesh.indices.size() * threshold);
	float target_error = 1e-2f;

	lod.indices.resize(mesh.indices.size()); // note: simplify needs space for index_count elements in the destination array, not target_index_count
	lod.indices.resize(meshopt_simplify(&lod.indices[0], &mesh.indices[0], mesh.indices.size(), &mesh.vertices[0].px, mesh.vertices.size(), sizeof(Vertex), target_index_count, target_error));

	lod.vertices.resize(lod.indices.size() < mesh.vertices.size() ? lod.indices.size() : mesh.vertices.size()); // note: this is just to reduce the cost of resize()
	lod.vertices.resize(meshopt_optimizeVertexFetch(&lod.vertices[0], &lod.indices[0], lod.indices.size(), &mesh.vertices[0], mesh.vertices.size(), sizeof(Vertex)));

	double end = timestamp();

	printf("%-9s: %d triangles => %d triangles in %.2f msec\n",
	       "Simplify",
	       int(mesh.indices.size() / 3), int(lod.indices.size() / 3), (end - start) * 1000);
}

void simplifySloppy(const Mesh& mesh, float threshold = 0.2f)
{
	Mesh lod;

	double start = timestamp();

	size_t target_index_count = size_t(mesh.indices.size() * threshold);

	lod.indices.resize(target_index_count); // note: simplifySloppy, unlike simplify, is guaranteed to output results that don't exceed the requested target_index_count
	lod.indices.resize(meshopt_simplifySloppy(&lod.indices[0], &mesh.indices[0], mesh.indices.size(), &mesh.vertices[0].px, mesh.vertices.size(), sizeof(Vertex), target_index_count));

	lod.vertices.resize(lod.indices.size() < mesh.vertices.size() ? lod.indices.size() : mesh.vertices.size()); // note: this is just to reduce the cost of resize()
	lod.vertices.resize(meshopt_optimizeVertexFetch(&lod.vertices[0], &lod.indices[0], lod.indices.size(), &mesh.vertices[0], mesh.vertices.size(), sizeof(Vertex)));

	double end = timestamp();

	printf("%-9s: %d triangles => %d triangles in %.2f msec\n",
	       "SimplifyS",
	       int(mesh.indices.size() / 3), int(lod.indices.size() / 3), (end - start) * 1000);
}

void simplifyComplete(const Mesh& mesh)
{
	static const size_t lod_count = 5;

	double start = timestamp();

	// generate 4 LOD levels (1-4), with each subsequent LOD using 70% triangles
	// note that each LOD uses the same (shared) vertex buffer
	std::vector<unsigned int> lods[lod_count];

	lods[0] = mesh.indices;

	for (size_t i = 1; i < lod_count; ++i)
	{
		std::vector<unsigned int>& lod = lods[i];

		float threshold = powf(0.7f, float(i));
		size_t target_index_count = size_t(mesh.indices.size() * threshold) / 3 * 3;
		float target_error = 1e-2f;

		// we can simplify all the way from base level or from the last result
		// simplifying from the base level sometimes produces better results, but simplifying from last level is faster
		const std::vector<unsigned int>& source = lods[i - 1];

		if (source.size() < target_index_count)
			target_index_count = source.size();

		lod.resize(source.size());
		lod.resize(meshopt_simplify(&lod[0], &source[0], source.size(), &mesh.vertices[0].px, mesh.vertices.size(), sizeof(Vertex), target_index_count, target_error));
	}

	double middle = timestamp();

	// optimize each individual LOD for vertex cache & overdraw
	for (size_t i = 0; i < lod_count; ++i)
	{
		std::vector<unsigned int>& lod = lods[i];

		meshopt_optimizeVertexCache(&lod[0], &lod[0], lod.size(), mesh.vertices.size());
		meshopt_optimizeOverdraw(&lod[0], &lod[0], lod.size(), &mesh.vertices[0].px, mesh.vertices.size(), sizeof(Vertex), 1.0f);
	}

	// concatenate all LODs into one IB
	// note: the order of concatenation is important - since we optimize the entire IB for vertex fetch,
	// putting coarse LODs first makes sure that the vertex range referenced by them is as small as possible
	// some GPUs process the entire range referenced by the index buffer region so doing this optimizes the vertex transform
	// cost for coarse LODs
	// this order also produces much better vertex fetch cache coherency for coarse LODs (since they're essentially optimized first)
	// somewhat surprisingly, the vertex fetch cache coherency for fine LODs doesn't seem to suffer that much.
	size_t lod_index_offsets[lod_count] = {};
	size_t lod_index_counts[lod_count] = {};
	size_t total_index_count = 0;

	for (int i = lod_count - 1; i >= 0; --i)
	{
		lod_index_offsets[i] = total_index_count;
		lod_index_counts[i] = lods[i].size();

		total_index_count += lods[i].size();
	}

	std::vector<unsigned int> indices(total_index_count);

	for (size_t i = 0; i < lod_count; ++i)
	{
		memcpy(&indices[lod_index_offsets[i]], &lods[i][0], lods[i].size() * sizeof(lods[i][0]));
	}

	std::vector<Vertex> vertices = mesh.vertices;

	// vertex fetch optimization should go last as it depends on the final index order
	// note that the order of LODs above affects vertex fetch results
	meshopt_optimizeVertexFetch(&vertices[0], &indices[0], indices.size(), &vertices[0], vertices.size(), sizeof(Vertex));

	double end = timestamp();

	printf("%-9s: %d triangles => %d LOD levels down to %d triangles in %.2f msec, optimized in %.2f msec\n",
	       "SimplifyC",
	       int(lod_index_counts[0]) / 3, int(lod_count), int(lod_index_counts[lod_count - 1]) / 3,
	       (middle - start) * 1000, (end - middle) * 1000);

	// for using LOD data at runtime, in addition to vertices and indices you have to save lod_index_offsets/lod_index_counts.

	{
		meshopt_VertexCacheStatistics vcs0 = meshopt_analyzeVertexCache(&indices[lod_index_offsets[0]], lod_index_counts[0], vertices.size(), kCacheSize, 0, 0);
		meshopt_VertexFetchStatistics vfs0 = meshopt_analyzeVertexFetch(&indices[lod_index_offsets[0]], lod_index_counts[0], vertices.size(), sizeof(Vertex));
		meshopt_VertexCacheStatistics vcsN = meshopt_analyzeVertexCache(&indices[lod_index_offsets[lod_count - 1]], lod_index_counts[lod_count - 1], vertices.size(), kCacheSize, 0, 0);
		meshopt_VertexFetchStatistics vfsN = meshopt_analyzeVertexFetch(&indices[lod_index_offsets[lod_count - 1]], lod_index_counts[lod_count - 1], vertices.size(), sizeof(Vertex));

		typedef PackedVertexOct PV;

		std::vector<PV> pv(vertices.size());
		packMesh(pv, vertices);

		std::vector<unsigned char> vbuf(meshopt_encodeVertexBufferBound(vertices.size(), sizeof(PV)));
		vbuf.resize(meshopt_encodeVertexBuffer(&vbuf[0], vbuf.size(), &pv[0], vertices.size(), sizeof(PV)));

		std::vector<unsigned char> ibuf(meshopt_encodeIndexBufferBound(indices.size(), vertices.size()));
		ibuf.resize(meshopt_encodeIndexBuffer(&ibuf[0], ibuf.size(), &indices[0], indices.size()));

		printf("%-9s  ACMR %f...%f Overfetch %f..%f Codec VB %.1f bits/vertex IB %.1f bits/triangle\n",
		       "",
		       vcs0.acmr, vcsN.acmr, vfs0.overfetch, vfsN.overfetch,
		       double(vbuf.size()) / double(vertices.size()) * 8,
		       double(ibuf.size()) / double(indices.size() / 3) * 8);
	}
}

void optimize(const Mesh& mesh, const char* name, void (*optf)(Mesh& mesh))
{
	Mesh copy = mesh;

	double start = timestamp();
	optf(copy);
	double end = timestamp();

	assert(isMeshValid(copy));
	assert(hashMesh(mesh) == hashMesh(copy));

	meshopt_VertexCacheStatistics vcs = meshopt_analyzeVertexCache(&copy.indices[0], copy.indices.size(), copy.vertices.size(), kCacheSize, 0, 0);
	meshopt_VertexFetchStatistics vfs = meshopt_analyzeVertexFetch(&copy.indices[0], copy.indices.size(), copy.vertices.size(), sizeof(Vertex));
	meshopt_OverdrawStatistics os = meshopt_analyzeOverdraw(&copy.indices[0], copy.indices.size(), &copy.vertices[0].px, copy.vertices.size(), sizeof(Vertex));

	meshopt_VertexCacheStatistics vcs_nv = meshopt_analyzeVertexCache(&copy.indices[0], copy.indices.size(), copy.vertices.size(), 32, 32, 32);
	meshopt_VertexCacheStatistics vcs_amd = meshopt_analyzeVertexCache(&copy.indices[0], copy.indices.size(), copy.vertices.size(), 14, 64, 128);
	meshopt_VertexCacheStatistics vcs_intel = meshopt_analyzeVertexCache(&copy.indices[0], copy.indices.size(), copy.vertices.size(), 128, 0, 0);

	printf("%-9s: ACMR %f ATVR %f (NV %f AMD %f Intel %f) Overfetch %f Overdraw %f in %.2f msec\n", name, vcs.acmr, vcs.atvr, vcs_nv.atvr, vcs_amd.atvr, vcs_intel.atvr, vfs.overfetch, os.overdraw, (end - start) * 1000);
}

template <typename T>
size_t compress(const std::vector<T>& data)
{
	std::vector<unsigned char> cbuf(tdefl_compress_bound(data.size() * sizeof(T)));
	unsigned int flags = tdefl_create_comp_flags_from_zip_params(MZ_DEFAULT_LEVEL, 15, MZ_DEFAULT_STRATEGY);
	return tdefl_compress_mem_to_mem(&cbuf[0], cbuf.size(), &data[0], data.size() * sizeof(T), flags);
}

void encodeIndex(const Mesh& mesh)
{
	// allocate result outside of the timing loop to exclude memset() from decode timing
	std::vector<unsigned int> result(mesh.indices.size());

	double start = timestamp();

	std::vector<unsigned char> buffer(meshopt_encodeIndexBufferBound(mesh.indices.size(), mesh.vertices.size()));
	buffer.resize(meshopt_encodeIndexBuffer(&buffer[0], buffer.size(), &mesh.indices[0], mesh.indices.size()));

	double middle = timestamp();

	int res = meshopt_decodeIndexBuffer(&result[0], mesh.indices.size(), &buffer[0], buffer.size());
	assert(res == 0);
	(void)res;

	double end = timestamp();

	size_t csize = compress(buffer);

	for (size_t i = 0; i < mesh.indices.size(); i += 3)
	{
		assert(
		    (result[i + 0] == mesh.indices[i + 0] && result[i + 1] == mesh.indices[i + 1] && result[i + 2] == mesh.indices[i + 2]) ||
		    (result[i + 1] == mesh.indices[i + 0] && result[i + 2] == mesh.indices[i + 1] && result[i + 0] == mesh.indices[i + 2]) ||
		    (result[i + 2] == mesh.indices[i + 0] && result[i + 0] == mesh.indices[i + 1] && result[i + 1] == mesh.indices[i + 2]));
	}

	printf("IdxCodec : %.1f bits/triangle (post-deflate %.1f bits/triangle); encode %.2f msec, decode %.2f msec (%.2f GB/s)\n",
	       double(buffer.size() * 8) / double(mesh.indices.size() / 3),
	       double(csize * 8) / double(mesh.indices.size() / 3),
	       (middle - start) * 1000,
	       (end - middle) * 1000,
	       (double(result.size() * 4) / (1 << 30)) / (end - middle));
}

template <typename PV>
void packVertex(const Mesh& mesh, const char* pvn)
{
	std::vector<PV> pv(mesh.vertices.size());
	packMesh(pv, mesh.vertices);

	size_t csize = compress(pv);

	printf("VtxPack%s  : %.1f bits/vertex (post-deflate %.1f bits/vertex)\n", pvn,
	       double(pv.size() * sizeof(PV) * 8) / double(mesh.vertices.size()),
	       double(csize * 8) / double(mesh.vertices.size()));
}

template <typename PV>
void encodeVertex(const Mesh& mesh, const char* pvn)
{
	std::vector<PV> pv(mesh.vertices.size());
	packMesh(pv, mesh.vertices);

	// allocate result outside of the timing loop to exclude memset() from decode timing
	std::vector<PV> result(mesh.vertices.size());

	double start = timestamp();

	std::vector<unsigned char> vbuf(meshopt_encodeVertexBufferBound(mesh.vertices.size(), sizeof(PV)));
	vbuf.resize(meshopt_encodeVertexBuffer(&vbuf[0], vbuf.size(), &pv[0], mesh.vertices.size(), sizeof(PV)));

	double middle = timestamp();

	int res = meshopt_decodeVertexBuffer(&result[0], mesh.vertices.size(), sizeof(PV), &vbuf[0], vbuf.size());
	assert(res == 0);
	(void)res;

	double end = timestamp();

	assert(memcmp(&pv[0], &result[0], pv.size() * sizeof(PV)) == 0);

	size_t csize = compress(vbuf);

	printf("VtxCodec%1s: %.1f bits/vertex (post-deflate %.1f bits/vertex); encode %.2f msec, decode %.2f msec (%.2f GB/s)\n", pvn,
	       double(vbuf.size() * 8) / double(mesh.vertices.size()),
	       double(csize * 8) / double(mesh.vertices.size()),
	       (middle - start) * 1000,
	       (end - middle) * 1000,
	       (double(result.size() * sizeof(PV)) / (1 << 30)) / (end - middle));
}

void stripify(const Mesh& mesh)
{
	// note: input mesh is assumed to be optimized for vertex cache and vertex fetch
	double start = timestamp();
	std::vector<unsigned int> strip(meshopt_stripifyBound(mesh.indices.size()));
	strip.resize(meshopt_stripify(&strip[0], &mesh.indices[0], mesh.indices.size(), mesh.vertices.size()));
	double end = timestamp();

	Mesh copy = mesh;
	copy.indices.resize(meshopt_unstripify(&copy.indices[0], &strip[0], strip.size()));
	assert(copy.indices.size() <= meshopt_unstripifyBound(strip.size()));

	assert(isMeshValid(copy));
	assert(hashMesh(mesh) == hashMesh(copy));

	meshopt_VertexCacheStatistics vcs = meshopt_analyzeVertexCache(&copy.indices[0], mesh.indices.size(), mesh.vertices.size(), kCacheSize, 0, 0);
	meshopt_VertexCacheStatistics vcs_nv = meshopt_analyzeVertexCache(&copy.indices[0], mesh.indices.size(), mesh.vertices.size(), 32, 32, 32);
	meshopt_VertexCacheStatistics vcs_amd = meshopt_analyzeVertexCache(&copy.indices[0], mesh.indices.size(), mesh.vertices.size(), 14, 64, 128);
	meshopt_VertexCacheStatistics vcs_intel = meshopt_analyzeVertexCache(&copy.indices[0], mesh.indices.size(), mesh.vertices.size(), 128, 0, 0);

	printf("Stripify : ACMR %f ATVR %f (NV %f AMD %f Intel %f); %d strip indices (%.1f%%) in %.2f msec\n",
	       vcs.acmr, vcs.atvr, vcs_nv.atvr, vcs_amd.atvr, vcs_intel.atvr,
	       int(strip.size()), double(strip.size()) / double(mesh.indices.size()) * 100,
	       (end - start) * 1000);
}

void shadow(const Mesh& mesh)
{
	// note: input mesh is assumed to be optimized for vertex cache and vertex fetch

	double start = timestamp();
	// this index buffer can be used for position-only rendering using the same vertex data that the original index buffer uses
	std::vector<unsigned int> shadow_indices(mesh.indices.size());
	meshopt_generateShadowIndexBuffer(&shadow_indices[0], &mesh.indices[0], mesh.indices.size(), &mesh.vertices[0], mesh.vertices.size(), sizeof(float) * 3, sizeof(Vertex));
	double end = timestamp();

	// while you can't optimize the vertex data after shadow IB was constructed, you can and should optimize the shadow IB for vertex cache
	// this is valuable even if the original indices array was optimized for vertex cache!
	meshopt_optimizeVertexCache(&shadow_indices[0], &shadow_indices[0], shadow_indices.size(), mesh.vertices.size());

	meshopt_VertexCacheStatistics vcs = meshopt_analyzeVertexCache(&mesh.indices[0], mesh.indices.size(), mesh.vertices.size(), kCacheSize, 0, 0);
	meshopt_VertexCacheStatistics vcss = meshopt_analyzeVertexCache(&shadow_indices[0], shadow_indices.size(), mesh.vertices.size(), kCacheSize, 0, 0);

	std::vector<char> shadow_flags(mesh.vertices.size());
	size_t shadow_vertices = 0;

	for (size_t i = 0; i < shadow_indices.size(); ++i)
	{
		unsigned int index = shadow_indices[i];
		shadow_vertices += 1 - shadow_flags[index];
		shadow_flags[index] = 1;
	}

	printf("ShadowIB : ACMR %f (%.2fx improvement); %d shadow vertices (%.2fx improvement) in %.2f msec\n",
	       vcss.acmr, double(vcs.vertices_transformed) / double(vcss.vertices_transformed),
	       int(shadow_vertices), double(mesh.vertices.size()) / double(shadow_vertices),
	       (end - start) * 1000);
}

void meshlets(const Mesh& mesh)
{
	const size_t max_vertices = 64;
	const size_t max_triangles = 126;

	// note: input mesh is assumed to be optimized for vertex cache and vertex fetch
	double start = timestamp();
	std::vector<meshopt_Meshlet> meshlets(meshopt_buildMeshletsBound(mesh.indices.size(), max_vertices, max_triangles));
	meshlets.resize(meshopt_buildMeshlets(&meshlets[0], &mesh.indices[0], mesh.indices.size(), mesh.vertices.size(), max_vertices, max_triangles));
	double end = timestamp();

	double avg_vertices = 0;
	double avg_triangles = 0;
	size_t not_full = 0;

	for (size_t i = 0; i < meshlets.size(); ++i)
	{
		const meshopt_Meshlet& m = meshlets[i];

		avg_vertices += m.vertex_count;
		avg_triangles += m.triangle_count;
		not_full += m.vertex_count < max_vertices;
	}

	avg_vertices /= double(meshlets.size());
	avg_triangles /= double(meshlets.size());

	printf("Meshlets : %d meshlets (avg vertices %.1f, avg triangles %.1f, not full %d) in %.2f msec\n",
	       int(meshlets.size()), avg_vertices, avg_triangles, int(not_full), (end - start) * 1000);

	float camera[3] = {100, 100, 100};

	size_t rejected = 0;
	size_t rejected_s8 = 0;
	size_t rejected_alt = 0;
	size_t rejected_alt_s8 = 0;
	size_t accepted = 0;
	size_t accepted_s8 = 0;

	double startc = timestamp();
	for (size_t i = 0; i < meshlets.size(); ++i)
	{
		meshopt_Bounds bounds = meshopt_computeMeshletBounds(&meshlets[i], &mesh.vertices[0].px, mesh.vertices.size(), sizeof(Vertex));

		// trivial accept: we can't ever backface cull this meshlet
		accepted += (bounds.cone_cutoff >= 1);
		accepted_s8 += (bounds.cone_cutoff_s8 >= 127);

		// perspective projection: dot(normalize(cone_apex - camera_position), cone_axis) > cone_cutoff
		float mview[3] = {bounds.cone_apex[0] - camera[0], bounds.cone_apex[1] - camera[1], bounds.cone_apex[2] - camera[2]};
		float mviewlength = sqrtf(mview[0] * mview[0] + mview[1] * mview[1] + mview[2] * mview[2]);

		rejected += mview[0] * bounds.cone_axis[0] + mview[1] * bounds.cone_axis[1] + mview[2] * bounds.cone_axis[2] >= bounds.cone_cutoff * mviewlength;
		rejected_s8 += mview[0] * (bounds.cone_axis_s8[0] / 127.f) + mview[1] * (bounds.cone_axis_s8[1] / 127.f) + mview[2] * (bounds.cone_axis_s8[2] / 127.f) >= (bounds.cone_cutoff_s8 / 127.f) * mviewlength;

		// alternative formulation for perspective projection that doesn't use apex (and uses cluster bounding sphere instead):
		// dot(normalize(center - camera_position), cone_axis) > cone_cutoff + radius / length(center - camera_position)
		float cview[3] = {bounds.center[0] - camera[0], bounds.center[1] - camera[1], bounds.center[2] - camera[2]};
		float cviewlength = sqrtf(cview[0] * cview[0] + cview[1] * cview[1] + cview[2] * cview[2]);

		rejected_alt += cview[0] * bounds.cone_axis[0] + cview[1] * bounds.cone_axis[1] + cview[2] * bounds.cone_axis[2] >= bounds.cone_cutoff * cviewlength + bounds.radius;
		rejected_alt_s8 += cview[0] * (bounds.cone_axis_s8[0] / 127.f) + cview[1] * (bounds.cone_axis_s8[1] / 127.f) + cview[2] * (bounds.cone_axis_s8[2] / 127.f) >= (bounds.cone_cutoff_s8 / 127.f) * cviewlength + bounds.radius;
	}
	double endc = timestamp();

	printf("ConeCull : rejected apex %d (%.1f%%) / center %d (%.1f%%), trivially accepted %d (%.1f%%) in %.2f msec\n",
	       int(rejected), double(rejected) / double(meshlets.size()) * 100,
	       int(rejected_alt), double(rejected_alt) / double(meshlets.size()) * 100,
	       int(accepted), double(accepted) / double(meshlets.size()) * 100,
	       (endc - startc) * 1000);
	printf("ConeCull8: rejected apex %d (%.1f%%) / center %d (%.1f%%), trivially accepted %d (%.1f%%) in %.2f msec\n",
	       int(rejected_s8), double(rejected_s8) / double(meshlets.size()) * 100,
	       int(rejected_alt_s8), double(rejected_alt_s8) / double(meshlets.size()) * 100,
	       int(accepted_s8), double(accepted_s8) / double(meshlets.size()) * 100,
	       (endc - startc) * 1000);
}

bool loadMesh(Mesh& mesh, const char* path)
{
	double start = timestamp();
	double middle;
	mesh = parseObj(path, middle);
	double end = timestamp();

	if (mesh.vertices.empty())
	{
		printf("Mesh %s is empty, skipping\n", path);
		return false;
	}

	printf("# %s: %d vertices, %d triangles; read in %.2f msec; indexed in %.2f msec\n", path, int(mesh.vertices.size()), int(mesh.indices.size() / 3), (middle - start) * 1000, (end - middle) * 1000);
	return true;
}

void processDeinterleaved(const char* path)
{
	// Most algorithms in the library work out of the box with deinterleaved geometry, but some require slightly special treatment;
	// this code runs a simplified version of complete opt. pipeline using deinterleaved geo. There's no compression performed but you
	// can trivially run it by quantizing all elements and running meshopt_encodeVertexBuffer once for each vertex stream.
	ObjFile file;
	if (!objParseFile(file, path) || !objValidate(file))
	{
		printf("Error loading %s: file not found or invalid file data\n", path);
		return;
	}

	size_t total_indices = file.f_size / 3;

	std::vector<float> unindexed_pos(total_indices * 3);
	std::vector<float> unindexed_nrm(total_indices * 3);
	std::vector<float> unindexed_uv(total_indices * 2);

	for (size_t i = 0; i < total_indices; ++i)
	{
		int vi = file.f[i * 3 + 0];
		int vti = file.f[i * 3 + 1];
		int vni = file.f[i * 3 + 2];

		unindexed_pos[i * 3 + 0] = file.v[vi * 3 + 0];
		unindexed_pos[i * 3 + 1] = file.v[vi * 3 + 1];
		unindexed_pos[i * 3 + 2] = file.v[vi * 3 + 2];

		if (vni >= 0)
		{
			unindexed_nrm[i * 3 + 0] = file.vn[vni * 3 + 0];
			unindexed_nrm[i * 3 + 1] = file.vn[vni * 3 + 1];
			unindexed_nrm[i * 3 + 2] = file.vn[vni * 3 + 2];
		}

		if (vti >= 0)
		{
			unindexed_uv[i * 2 + 0] = file.vt[vti * 3 + 0];
			unindexed_uv[i * 2 + 1] = file.vt[vti * 3 + 1];
		}
	}

	double start = timestamp();

	meshopt_Stream streams[] = {
	    {&unindexed_pos[0], sizeof(float) * 3, sizeof(float) * 3},
	    {&unindexed_nrm[0], sizeof(float) * 3, sizeof(float) * 3},
	    {&unindexed_uv[0], sizeof(float) * 2, sizeof(float) * 2},
	};

	std::vector<unsigned int> remap(total_indices);

	size_t total_vertices = meshopt_generateVertexRemapMulti(&remap[0], NULL, total_indices, total_indices, streams, sizeof(streams) / sizeof(streams[0]));

	std::vector<unsigned int> indices(total_indices);
	meshopt_remapIndexBuffer(&indices[0], NULL, total_indices, &remap[0]);

	std::vector<float> pos(total_vertices * 3);
	meshopt_remapVertexBuffer(&pos[0], &unindexed_pos[0], total_indices, sizeof(float) * 3, &remap[0]);

	std::vector<float> nrm(total_vertices * 3);
	meshopt_remapVertexBuffer(&nrm[0], &unindexed_nrm[0], total_indices, sizeof(float) * 3, &remap[0]);

	std::vector<float> uv(total_vertices * 2);
	meshopt_remapVertexBuffer(&uv[0], &unindexed_uv[0], total_indices, sizeof(float) * 2, &remap[0]);

	double reindex = timestamp();

	meshopt_optimizeVertexCache(&indices[0], &indices[0], total_indices, total_vertices);

	meshopt_optimizeVertexFetchRemap(&remap[0], &indices[0], total_indices, total_vertices);
	meshopt_remapVertexBuffer(&pos[0], &pos[0], total_vertices, sizeof(float) * 3, &remap[0]);
	meshopt_remapVertexBuffer(&nrm[0], &nrm[0], total_vertices, sizeof(float) * 3, &remap[0]);
	meshopt_remapVertexBuffer(&uv[0], &uv[0], total_vertices, sizeof(float) * 2, &remap[0]);

	double optimize = timestamp();

	// note: since shadow index buffer is computed based on regular vertex/index buffer, the stream points at the indexed data - not unindexed_pos
	meshopt_Stream shadow_stream = {&pos[0], sizeof(float) * 3, sizeof(float) * 3};

	std::vector<unsigned int> shadow_indices(total_indices);
	meshopt_generateShadowIndexBufferMulti(&shadow_indices[0], &indices[0], total_indices, total_vertices, &shadow_stream, 1);

	meshopt_optimizeVertexCache(&shadow_indices[0], &shadow_indices[0], total_indices, total_vertices);

	double shadow = timestamp();

	printf("Deintrlvd: %d vertices, reindexed in %.2f msec, optimized in %.2f msec, generated & optimized shadow indices in %.2f msec\n",
	       int(total_vertices), (reindex - start) * 1000, (optimize - reindex) * 1000, (shadow - optimize) * 1000);
}

void process(const char* path)
{
	Mesh mesh;
	if (!loadMesh(mesh, path))
		return;

	optimize(mesh, "Original", optNone);
	optimize(mesh, "Random", optRandomShuffle);
	optimize(mesh, "Cache", optCache);
	optimize(mesh, "CacheFifo", optCacheFifo);
	optimize(mesh, "Overdraw", optOverdraw);
	optimize(mesh, "Fetch", optFetch);
	optimize(mesh, "FetchMap", optFetchRemap);
	optimize(mesh, "Complete", optComplete);

	Mesh copy = mesh;
	meshopt_optimizeVertexCache(&copy.indices[0], &copy.indices[0], copy.indices.size(), copy.vertices.size());
	meshopt_optimizeVertexFetch(&copy.vertices[0], &copy.indices[0], copy.indices.size(), &copy.vertices[0], copy.vertices.size(), sizeof(Vertex));

	stripify(copy);
	meshlets(copy);
	shadow(copy);

	encodeIndex(copy);
	packVertex<PackedVertex>(copy, "");
	encodeVertex<PackedVertex>(copy, "");
	encodeVertex<PackedVertexOct>(copy, "O");

	simplify(mesh);
	simplifySloppy(mesh);
	simplifyComplete(mesh);

	if (path)
		processDeinterleaved(path);
}

void processDev(const char* path)
{
	Mesh mesh;
	if (!loadMesh(mesh, path))
		return;

	simplify(mesh, 0.01f);
	simplifySloppy(mesh, 0.01f);
}

int main(int argc, char** argv)
{
	void runTests();

	if (argc == 1)
	{
		runTests();
	}
	else
	{
		if (strcmp(argv[1], "-d") == 0)
		{
			for (int i = 2; i < argc; ++i)
			{
				processDev(argv[i]);
			}
		}
		else
		{
			for (int i = 1; i < argc; ++i)
			{
				process(argv[i]);
			}

			runTests();
		}
	}
}
