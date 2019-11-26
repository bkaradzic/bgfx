#include "../src/meshoptimizer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <vector>

// This file uses assert() to verify algorithm correctness
#undef NDEBUG
#include <assert.h>

struct PV
{
	unsigned short px, py, pz;
	unsigned char nu, nv; // octahedron encoded normal, aliases .pw
	unsigned short tx, ty;
};

// note: 4 6 5 triangle here is a combo-breaker:
// we encode it without rotating, a=next, c=next - this means we do *not* bump next to 6
// which means that the next triangle can't be encoded via next sequencing!
static const unsigned int kIndexBuffer[] = {0, 1, 2, 2, 1, 3, 4, 6, 5, 7, 8, 9};

static const unsigned char kIndexDataV0[] = {
    0xe0, 0xf0, 0x10, 0xfe, 0xff, 0xf0, 0x0c, 0xff, 0x02, 0x02, 0x02, 0x00, 0x76, 0x87, 0x56, 0x67,
    0x78, 0xa9, 0x86, 0x65, 0x89, 0x68, 0x98, 0x01, 0x69, 0x00, 0x00, // clang-format :-/
};

static const PV kVertexBuffer[] = {
    {0, 0, 0, 0, 0, 0, 0},
    {300, 0, 0, 0, 0, 500, 0},
    {0, 300, 0, 0, 0, 0, 500},
    {300, 300, 0, 0, 0, 500, 500},
};

static const unsigned char kVertexDataV0[] = {
    0xa0, 0x01, 0x3f, 0x00, 0x00, 0x00, 0x58, 0x57, 0x58, 0x01, 0x26, 0x00, 0x00, 0x00, 0x01,
    0x0c, 0x00, 0x00, 0x00, 0x58, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x3f, 0x00, 0x00, 0x00, 0x17, 0x18, 0x17, 0x01, 0x26, 0x00, 0x00, 0x00, 0x01, 0x0c, 0x00,
    0x00, 0x00, 0x17, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // clang-format :-/
};

static void decodeIndexV0()
{
	const size_t index_count = sizeof(kIndexBuffer) / sizeof(kIndexBuffer[0]);

	std::vector<unsigned char> buffer(kIndexDataV0, kIndexDataV0 + sizeof(kIndexDataV0));

	unsigned int decoded[index_count];
	assert(meshopt_decodeIndexBuffer(decoded, index_count, &buffer[0], buffer.size()) == 0);
	assert(memcmp(decoded, kIndexBuffer, sizeof(kIndexBuffer)) == 0);
}

static void decodeIndex16()
{
	const size_t index_count = sizeof(kIndexBuffer) / sizeof(kIndexBuffer[0]);
	const size_t vertex_count = 10;

	std::vector<unsigned char> buffer(meshopt_encodeIndexBufferBound(index_count, vertex_count));
	buffer.resize(meshopt_encodeIndexBuffer(&buffer[0], buffer.size(), kIndexBuffer, index_count));

	unsigned short decoded[index_count];
	assert(meshopt_decodeIndexBuffer(decoded, index_count, &buffer[0], buffer.size()) == 0);

	for (size_t i = 0; i < index_count; ++i)
		assert(decoded[i] == kIndexBuffer[i]);
}

static void encodeIndexMemorySafe()
{
	const size_t index_count = sizeof(kIndexBuffer) / sizeof(kIndexBuffer[0]);
	const size_t vertex_count = 10;

	std::vector<unsigned char> buffer(meshopt_encodeIndexBufferBound(index_count, vertex_count));
	buffer.resize(meshopt_encodeIndexBuffer(&buffer[0], buffer.size(), kIndexBuffer, index_count));

	// check that encode is memory-safe; note that we reallocate the buffer for each try to make sure ASAN can verify buffer access
	for (size_t i = 0; i <= buffer.size(); ++i)
	{
		std::vector<unsigned char> shortbuffer(i);
		size_t result = meshopt_encodeIndexBuffer(i == 0 ? 0 : &shortbuffer[0], i, kIndexBuffer, index_count);

		if (i == buffer.size())
			assert(result == buffer.size());
		else
			assert(result == 0);
	}
}

static void decodeIndexMemorySafe()
{
	const size_t index_count = sizeof(kIndexBuffer) / sizeof(kIndexBuffer[0]);
	const size_t vertex_count = 10;

	std::vector<unsigned char> buffer(meshopt_encodeIndexBufferBound(index_count, vertex_count));
	buffer.resize(meshopt_encodeIndexBuffer(&buffer[0], buffer.size(), kIndexBuffer, index_count));

	// check that decode is memory-safe; note that we reallocate the buffer for each try to make sure ASAN can verify buffer access
	unsigned int decoded[index_count];

	for (size_t i = 0; i <= buffer.size(); ++i)
	{
		std::vector<unsigned char> shortbuffer(buffer.begin(), buffer.begin() + i);
		int result = meshopt_decodeIndexBuffer(decoded, index_count, i == 0 ? 0 : &shortbuffer[0], i);

		if (i == buffer.size())
			assert(result == 0);
		else
			assert(result < 0);
	}
}

static void decodeIndexRejectExtraBytes()
{
	const size_t index_count = sizeof(kIndexBuffer) / sizeof(kIndexBuffer[0]);
	const size_t vertex_count = 10;

	std::vector<unsigned char> buffer(meshopt_encodeIndexBufferBound(index_count, vertex_count));
	buffer.resize(meshopt_encodeIndexBuffer(&buffer[0], buffer.size(), kIndexBuffer, index_count));

	// check that decoder doesn't accept extra bytes after a valid stream
	std::vector<unsigned char> largebuffer(buffer);
	largebuffer.push_back(0);

	unsigned int decoded[index_count];
	assert(meshopt_decodeIndexBuffer(decoded, index_count, &largebuffer[0], largebuffer.size()) < 0);
}

static void decodeIndexRejectMalformedHeaders()
{
	const size_t index_count = sizeof(kIndexBuffer) / sizeof(kIndexBuffer[0]);
	const size_t vertex_count = 10;

	std::vector<unsigned char> buffer(meshopt_encodeIndexBufferBound(index_count, vertex_count));
	buffer.resize(meshopt_encodeIndexBuffer(&buffer[0], buffer.size(), kIndexBuffer, index_count));

	// check that decoder doesn't accept malformed headers
	std::vector<unsigned char> brokenbuffer(buffer);
	brokenbuffer[0] = 0;

	unsigned int decoded[index_count];
	assert(meshopt_decodeIndexBuffer(decoded, index_count, &brokenbuffer[0], brokenbuffer.size()) < 0);
}

static void decodeVertexV0()
{
	const size_t vertex_count = sizeof(kVertexBuffer) / sizeof(kVertexBuffer[0]);

	std::vector<unsigned char> buffer(kVertexDataV0, kVertexDataV0 + sizeof(kVertexDataV0));

	PV decoded[vertex_count];
	assert(meshopt_decodeVertexBuffer(decoded, vertex_count, sizeof(PV), &buffer[0], buffer.size()) == 0);
	assert(memcmp(decoded, kVertexBuffer, sizeof(kVertexBuffer)) == 0);
}

static void encodeVertexMemorySafe()
{
	const size_t vertex_count = sizeof(kVertexBuffer) / sizeof(kVertexBuffer[0]);

	std::vector<unsigned char> buffer(meshopt_encodeVertexBufferBound(vertex_count, sizeof(PV)));
	buffer.resize(meshopt_encodeVertexBuffer(&buffer[0], buffer.size(), kVertexBuffer, vertex_count, sizeof(PV)));

	// check that encode is memory-safe; note that we reallocate the buffer for each try to make sure ASAN can verify buffer access
	for (size_t i = 0; i <= buffer.size(); ++i)
	{
		std::vector<unsigned char> shortbuffer(i);
		size_t result = meshopt_encodeVertexBuffer(i == 0 ? 0 : &shortbuffer[0], i, kVertexBuffer, vertex_count, sizeof(PV));

		if (i == buffer.size())
			assert(result == buffer.size());
		else
			assert(result == 0);
	}
}

static void decodeVertexMemorySafe()
{
	const size_t vertex_count = sizeof(kVertexBuffer) / sizeof(kVertexBuffer[0]);

	std::vector<unsigned char> buffer(meshopt_encodeVertexBufferBound(vertex_count, sizeof(PV)));
	buffer.resize(meshopt_encodeVertexBuffer(&buffer[0], buffer.size(), kVertexBuffer, vertex_count, sizeof(PV)));

	// check that decode is memory-safe; note that we reallocate the buffer for each try to make sure ASAN can verify buffer access
	PV decoded[vertex_count];

	for (size_t i = 0; i <= buffer.size(); ++i)
	{
		std::vector<unsigned char> shortbuffer(buffer.begin(), buffer.begin() + i);
		int result = meshopt_decodeVertexBuffer(decoded, vertex_count, sizeof(PV), i == 0 ? 0 : &shortbuffer[0], i);
		(void)result;

		if (i == buffer.size())
			assert(result == 0);
		else
			assert(result < 0);
	}
}

static void decodeVertexRejectExtraBytes()
{
	const size_t vertex_count = sizeof(kVertexBuffer) / sizeof(kVertexBuffer[0]);

	std::vector<unsigned char> buffer(meshopt_encodeVertexBufferBound(vertex_count, sizeof(PV)));
	buffer.resize(meshopt_encodeVertexBuffer(&buffer[0], buffer.size(), kVertexBuffer, vertex_count, sizeof(PV)));

	// check that decoder doesn't accept extra bytes after a valid stream
	std::vector<unsigned char> largebuffer(buffer);
	largebuffer.push_back(0);

	PV decoded[vertex_count];
	assert(meshopt_decodeVertexBuffer(decoded, vertex_count, sizeof(PV), &largebuffer[0], largebuffer.size()) < 0);
}

static void decodeVertexRejectMalformedHeaders()
{
	const size_t vertex_count = sizeof(kVertexBuffer) / sizeof(kVertexBuffer[0]);

	std::vector<unsigned char> buffer(meshopt_encodeVertexBufferBound(vertex_count, sizeof(PV)));
	buffer.resize(meshopt_encodeVertexBuffer(&buffer[0], buffer.size(), kVertexBuffer, vertex_count, sizeof(PV)));

	// check that decoder doesn't accept malformed headers
	std::vector<unsigned char> brokenbuffer(buffer);
	brokenbuffer[0] = 0;

	PV decoded[vertex_count];
	assert(meshopt_decodeVertexBuffer(decoded, vertex_count, sizeof(PV), &brokenbuffer[0], brokenbuffer.size()) < 0);
}

static void clusterBoundsDegenerate()
{
	const float vbd[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	const unsigned int ibd[] = {0, 0, 0};
	const unsigned int ib1[] = {0, 1, 2};

	// all of the bounds below are degenerate as they use 0 triangles, one topology-degenerate triangle and one position-degenerate triangle respectively
	meshopt_Bounds bounds0 = meshopt_computeClusterBounds(0, 0, 0, 0, 12);
	meshopt_Bounds boundsd = meshopt_computeClusterBounds(ibd, 3, vbd, 3, 12);
	meshopt_Bounds bounds1 = meshopt_computeClusterBounds(ib1, 3, vbd, 3, 12);

	assert(bounds0.center[0] == 0 && bounds0.center[1] == 0 && bounds0.center[2] == 0 && bounds0.radius == 0);
	assert(boundsd.center[0] == 0 && boundsd.center[1] == 0 && boundsd.center[2] == 0 && boundsd.radius == 0);
	assert(bounds1.center[0] == 0 && bounds1.center[1] == 0 && bounds1.center[2] == 0 && bounds1.radius == 0);

	const float vb1[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
	const unsigned int ib2[] = {0, 1, 2, 0, 2, 1};

	// these bounds have a degenerate cone since the cluster has two triangles with opposite normals
	meshopt_Bounds bounds2 = meshopt_computeClusterBounds(ib2, 6, vb1, 3, 12);

	assert(bounds2.cone_apex[0] == 0 && bounds2.cone_apex[1] == 0 && bounds2.cone_apex[2] == 0);
	assert(bounds2.cone_axis[0] == 0 && bounds2.cone_axis[1] == 0 && bounds2.cone_axis[2] == 0);
	assert(bounds2.cone_cutoff == 1);
	assert(bounds2.cone_axis_s8[0] == 0 && bounds2.cone_axis_s8[1] == 0 && bounds2.cone_axis_s8[2] == 0);
	assert(bounds2.cone_cutoff_s8 == 127);

	// however, the bounding sphere needs to be in tact (here we only check bbox for simplicity)
	assert(bounds2.center[0] - bounds2.radius <= 0 && bounds2.center[0] + bounds2.radius >= 1);
	assert(bounds2.center[1] - bounds2.radius <= 0 && bounds2.center[1] + bounds2.radius >= 1);
	assert(bounds2.center[2] - bounds2.radius <= 0 && bounds2.center[2] + bounds2.radius >= 1);
}

static size_t allocCount;
static size_t freeCount;

static void* customAlloc(size_t size)
{
	allocCount++;

	return malloc(size);
}

static void customFree(void* ptr)
{
	freeCount++;

	free(ptr);
}

static void customAllocator()
{
	meshopt_setAllocator(customAlloc, customFree);

	assert(allocCount == 0 && freeCount == 0);

	float vb[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
	unsigned int ib[] = {0, 1, 2};
	unsigned short ibs[] = {0, 1, 2};

	// meshopt_computeClusterBounds doesn't allocate
	meshopt_computeClusterBounds(ib, 3, vb, 3, 12);
	assert(allocCount == 0 && freeCount == 0);

	// ... unless IndexAdapter is used
	meshopt_computeClusterBounds(ibs, 3, vb, 3, 12);
	assert(allocCount == 1 && freeCount == 1);

	// meshopt_optimizeVertexFetch allocates internal remap table and temporary storage for in-place remaps
	meshopt_optimizeVertexFetch(vb, ib, 3, vb, 3, 12);
	assert(allocCount == 3 && freeCount == 3);

	// ... plus one for IndexAdapter
	meshopt_optimizeVertexFetch(vb, ibs, 3, vb, 3, 12);
	assert(allocCount == 6 && freeCount == 6);

	meshopt_setAllocator(operator new, operator delete);

	// customAlloc & customFree should not get called anymore
	meshopt_optimizeVertexFetch(vb, ib, 3, vb, 3, 12);
	assert(allocCount == 6 && freeCount == 6);
}

static void emptyMesh()
{
	meshopt_optimizeVertexCache(0, 0, 0, 0);
	meshopt_optimizeVertexCacheFifo(0, 0, 0, 0, 16);
	meshopt_optimizeOverdraw(0, 0, 0, 0, 0, 12, 1.f);
}

static void simplifyStuck()
{
	// tetrahedron can't be simplified due to collapse error restrictions
	float vb1[] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1};
	unsigned int ib1[] = {0, 1, 2, 0, 2, 3, 0, 3, 1, 2, 1, 3};

	assert(meshopt_simplify(ib1, ib1, 12, vb1, 4, 12, 6, 1e-3f) == 12);

	// 5-vertex strip can't be simplified due to topology restriction since middle triangle has flipped winding
	float vb2[] = {0, 0, 0, 1, 0, 0, 2, 0, 0, 0.5f, 1, 0, 1.5f, 1, 0};
	unsigned int ib2[] = {0, 1, 3, 3, 1, 4, 1, 2, 4}; // ok
	unsigned int ib3[] = {0, 1, 3, 1, 3, 4, 1, 2, 4}; // flipped

	assert(meshopt_simplify(ib2, ib2, 9, vb2, 5, 12, 6, 1e-3f) == 6);
	assert(meshopt_simplify(ib3, ib3, 9, vb2, 5, 12, 6, 1e-3f) == 9);
}

static void simplifySloppyStuck()
{
	const float vb[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	const unsigned int ib[] = {0, 1, 2, 0, 1, 2};

	// simplifying down to 0 triangles results in 0 immediately
	assert(meshopt_simplifySloppy(0, ib, 3, vb, 3, 12, 0) == 0);

	// simplifying down to 2 triangles given that all triangles are degenerate results in 0 as well
	assert(meshopt_simplifySloppy(0, ib, 6, vb, 3, 12, 6) == 0);
}

static void simplifyPointsStuck()
{
	const float vb[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	// simplifying down to 0 points results in 0 immediately
	assert(meshopt_simplifyPoints(0, vb, 3, 12, 0) == 0);
}

void runTests()
{
	decodeIndexV0();
	decodeIndex16();
	encodeIndexMemorySafe();
	decodeIndexMemorySafe();
	decodeIndexRejectExtraBytes();
	decodeIndexRejectMalformedHeaders();

	decodeVertexV0();
	encodeVertexMemorySafe();
	decodeVertexMemorySafe();
	decodeVertexRejectExtraBytes();
	decodeVertexRejectMalformedHeaders();

	clusterBoundsDegenerate();

	customAllocator();

	emptyMesh();

	simplifyStuck();
	simplifySloppyStuck();
	simplifyPointsStuck();
}
