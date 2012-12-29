/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx.h>
#include "../../src/vertexdecl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
namespace std { namespace tr1 {} using namespace tr1; } // namespace std
#include <unordered_map>

#include <forsythtriangleorderoptimizer.h>

#if 0
#	define BX_TRACE(_format, ...) \
		do { \
			printf(BX_FILE_LINE_LITERAL "BGFX " _format "\n", ##__VA_ARGS__); \
		} while(0)

#	define BX_WARN(_condition, _format, ...) \
		do { \
			if (!(_condition) ) \
			{ \
				BX_TRACE(BX_FILE_LINE_LITERAL "WARN " _format, ##__VA_ARGS__); \
			} \
		} while(0)

#	define BX_CHECK(_condition, _format, ...) \
		do { \
			if (!(_condition) ) \
			{ \
				BX_TRACE(BX_FILE_LINE_LITERAL "CHECK " _format, ##__VA_ARGS__); \
				bx::debugBreak(); \
			} \
		} while(0)
#endif // 0

#define EXPECT(_condition) \
	do { \
		if (!(_condition) ) \
		{ \
			printf("Error parsing at:\n" BX_FILE_LINE_LITERAL "\nExpected: " #_condition "\n"); \
			exit(EXIT_FAILURE); \
		} \
	} while(0)

#include <bx/bx.h>
#include <bx/debug.h>
#include <bx/countof.h>
#include <bx/commandline.h>
#include <bx/timer.h>
#include <bx/readerwriter.h>
#include <bx/hash.h>
#include <bx/uint32_t.h>

#include "tokenizecmd.h"
#include "bounds.h"
#include "math.h"

struct Vector3
{
	float x;
	float y;
	float z;
};

typedef std::vector<Vector3> Vector3Array;

struct Index3
{
	int32_t m_position;
	int32_t m_texcoord;
	int32_t m_normal;
	int32_t m_vertexIndex;
};

typedef std::unordered_map<uint64_t, Index3> Index3Map;

struct Triangle
{
	uint64_t m_index[3];
};

typedef std::vector<Triangle> TriangleArray;

struct Group
{
	uint32_t m_startTriangle;
	uint32_t m_numTriangles;
	std::string m_name;
	std::string m_material;
};

typedef std::vector<Group> GroupArray;

struct Primitive
{
	uint32_t m_startVertex;
	uint32_t m_startIndex;
	uint32_t m_numVertices;
	uint32_t m_numIndices;
	std::string m_name;
};

typedef std::vector<Primitive> PrimitiveArray;

static uint32_t s_obbSteps = 17;

#define BGFX_CHUNK_MAGIC_GEO BX_MAKEFOURCC('G', 'E', 'O', 0x0)
#define BGFX_CHUNK_MAGIC_VB BX_MAKEFOURCC('V', 'B', ' ', 0x0)
#define BGFX_CHUNK_MAGIC_IB BX_MAKEFOURCC('I', 'B', ' ', 0x0)
#define BGFX_CHUNK_MAGIC_PRI BX_MAKEFOURCC('P', 'R', 'I', 0x0)

long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
}

void triangleReorder(uint16_t* _indices, uint32_t _numIndices, uint32_t _numVertices, uint16_t _cacheSize)
{
	uint16_t* newIndexList = new uint16_t[_numIndices];
	Forsyth::OptimizeFaces(_indices, _numIndices, _numVertices, newIndexList, _cacheSize);
	memcpy(_indices, newIndexList, _numIndices*2);
	delete [] newIndexList;
}

uint32_t packUint32(uint8_t _x, uint8_t _y, uint8_t _z, uint8_t _w)
{
	union
	{
		uint32_t ui32;
		uint8_t arr[4];
	} un;

	un.arr[0] = _x;
	un.arr[1] = _y;
	un.arr[2] = _z;
	un.arr[3] = _w;

	return un.ui32;
}

void unpackUint32(uint8_t _result[4], uint32_t _packed)
{
	union
	{
		uint32_t ui32;
		uint8_t arr[4];
	} un;

	un.ui32	= _packed;
	_result[0] = un.arr[0];
	_result[1] = un.arr[1];
	_result[2] = un.arr[2];
	_result[3] = un.arr[3];
}

uint32_t packF4u(float _x, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f)
{
	const uint8_t xx = uint8_t(_x*127.0f + 128.0f);
	const uint8_t yy = uint8_t(_y*127.0f + 128.0f);
	const uint8_t zz = uint8_t(_z*127.0f + 128.0f);
	const uint8_t ww = uint8_t(_w*127.0f + 128.0f);
	return packUint32(xx, yy, zz, ww);
}

void unpackF4u(float _result[4], uint32_t _packed)
{
	uint8_t unpacked[4];
	unpackUint32(unpacked, _packed);
	_result[0] = (float(unpacked[0]) - 128.0f)/127.0f;
	_result[1] = (float(unpacked[1]) - 128.0f)/127.0f;
	_result[2] = (float(unpacked[2]) - 128.0f)/127.0f;
	_result[3] = (float(unpacked[3]) - 128.0f)/127.0f;
}

uint32_t packF2h(float _x, float _y)
{
	union
	{
		uint32_t ui32;
		uint16_t arr[2];
	} un;

	un.arr[0] = bx::halfFromFloat(_x);
	un.arr[1] = bx::halfFromFloat(_y);

	return un.ui32;
}

void unpackF2h(float _result[2], uint32_t _packed)
{
	union
	{
		uint32_t ui32;
		uint16_t arr[2];
	} un;

	un.ui32 = _packed;
	_result[0] = bx::halfToFloat(un.arr[0]);
	_result[1] = bx::halfToFloat(un.arr[1]);
}

template<typename Ty>
void calcTangents(const uint16_t* _indices, uint32_t _numIndices, Ty* _vertices, uint16_t _numVertices)
{
	float* tangents = new float[6*_numVertices];
	memset(tangents, 0, 6*_numVertices*sizeof(float) );

	for (uint32_t ii = 0, num = _numIndices/3; ii < num; ++ii)
	{
		const uint16_t* indices = &_indices[ii*3];
		const Ty& v0 = _vertices[indices[0] ];
		const Ty& v1 = _vertices[indices[1] ];
		const Ty& v2 = _vertices[indices[2] ];

		const float bax = v1.m_x - v0.m_x;
		const float bay = v1.m_y - v0.m_y;
		const float baz = v1.m_z - v0.m_z;
		const float bau = v1.m_u - v0.m_u;
		const float bav = v1.m_v - v0.m_v;

		const float cax = v2.m_x - v0.m_x;
		const float cay = v2.m_y - v0.m_y;
		const float caz = v2.m_z - v0.m_z;
		const float cau = v2.m_u - v0.m_u;
		const float cav = v2.m_v - v0.m_v;

		const float det = (bau * cav - bav * cau);
		const float invDet = 1.0f / det;

		const float tx = (bax * cav - cax * bav) * invDet;
		const float ty = (bay * cav - cay * bav) * invDet;
		const float tz = (baz * cav - caz * bav) * invDet;

		const float bx = (cax * bau - bax * cau) * invDet;
		const float by = (cay * bau - bay * cau) * invDet;
		const float bz = (caz * bau - baz * cau) * invDet;

		for (uint32_t jj = 0; jj < 3; ++jj)
		{
			float* tanu = &tangents[indices[jj]*6];
			float* tanv = &tanu[3];
			tanu[0] += tx;
			tanu[1] += ty;
			tanu[2] += tz;

			tanv[0] += bx;
			tanv[1] += by;
			tanv[2] += bz;
		}
	}

	for (uint32_t ii = 0; ii < _numVertices; ++ii)
	{
		Ty& v0 = _vertices[ii];
		const float* tanu = &tangents[ii*6];
		const float* tanv = &tangents[ii*6 + 3];

		float normal[4];
		unpackF4u(normal, v0.m_normal);
		float ndt = vec3Dot(normal, tanu);

		float nxt[3];
		vec3Cross(nxt, normal, tanu);

		float tmp[3];
		tmp[0] = tanu[0] - normal[0] * ndt;
		tmp[1] = tanu[1] - normal[1] * ndt;
		tmp[2] = tanu[2] - normal[2] * ndt;

		float tangent[3];
		vec3Norm(tangent, tmp);

		float tw = vec3Dot(nxt, tanv) < 0.0f ? -1.0f : 1.0f;
		v0.m_tangent = packF4u(tangent[0], tangent[1], tangent[2], tw);
	}
} 

void writeBounds(bx::WriterI* _writer, const void* _vertices, uint32_t _numVertices, uint32_t _stride)
{
	Sphere maxSphere;
	calcMaxBoundingSphere(maxSphere, _vertices, _numVertices, _stride);

	Sphere minSphere;
	calcMinBoundingSphere(minSphere, _vertices, _numVertices, _stride);

	if (minSphere.m_radius > maxSphere.m_radius)
	{
		bx::write(_writer, maxSphere);
	}
	else
	{
		bx::write(_writer, minSphere);
	}

	Aabb aabb;
	calcAabb(aabb, _vertices, _numVertices, _stride);
	bx::write(_writer, aabb);

	Obb obb;
	calcObb(obb, _vertices, _numVertices, _stride, s_obbSteps);
	bx::write(_writer, obb);
}

void write(bx::WriterI* _writer, const uint8_t* _vertices, uint32_t _numVertices, const bgfx::VertexDecl& _decl, const uint16_t* _indices, uint32_t _numIndices, const std::string& _material, const PrimitiveArray& _primitives)
{
	uint32_t stride = _decl.getStride();
	bx::write(_writer, BGFX_CHUNK_MAGIC_VB);
	writeBounds(_writer, _vertices, _numVertices, stride);

	bx::write(_writer, _decl);
	bx::write(_writer, uint16_t(_numVertices) );
	bx::write(_writer, _vertices, _numVertices*stride);

	bx::write(_writer, BGFX_CHUNK_MAGIC_IB);
	bx::write(_writer, _numIndices);
	bx::write(_writer, _indices, _numIndices*2);

	bx::write(_writer, BGFX_CHUNK_MAGIC_PRI);
	uint16_t nameLen = uint16_t(_material.size() );
	bx::write(_writer, nameLen);
	bx::write(_writer, _material.c_str(), nameLen);
	bx::write(_writer, uint16_t(_primitives.size() ) );
	for (PrimitiveArray::const_iterator primIt = _primitives.begin(); primIt != _primitives.end(); ++primIt)
	{
		const Primitive& prim = *primIt;
		nameLen = uint16_t(prim.m_name.size() );
		bx::write(_writer, nameLen);
		bx::write(_writer, prim.m_name.c_str(), nameLen);
		bx::write(_writer, prim.m_startIndex);
		bx::write(_writer, prim.m_numIndices);
		bx::write(_writer, prim.m_startVertex);
		bx::write(_writer, prim.m_numVertices);
		writeBounds(_writer, &_vertices[prim.m_startVertex*stride], prim.m_numVertices, stride);
	}
}

void help(const char* _error = NULL)
{
	if (NULL != _error)
	{
		fprintf(stderr, "Error:\n%s\n\n", _error);
	}

	fprintf(stderr
		, "geometryc, bgfx geometry compiler tool\n"
		  "Copyright 2011-2012 Branimir Karadzic. All rights reserved.\n"
		  "License: http://www.opensource.org/licenses/BSD-2-Clause\n\n"
		);

	fprintf(stderr
		, "Usage: geometryc -f <in> -o <out>\n"

		  "\n"
		  "Supported input file types:\n"
		  "    *.obj                    Wavefront\n"

		  "\n"
		  "Options:\n"
		  "  -f <file path>           Input file path.\n"
		  "  -o <file path>           Output file path.\n"
		  "  -s, --scale <num>        Scale factor.\n"
		  "      --ccw                Counter-clockwise winding order.\n"
		  "      --flipv              Flip texture coordinate V.\n"
		  "      --obb <num>          Number of steps for calculating oriented bounding box.\n"
		  "           Default value is 17. Less steps less precise OBB is.\n"
		  "           More steps slower calculation.\n"
		  "      --packnormal <num>   Normal packing.\n"
		  "           0 - unpacked 12 bytes (default).\n"
		  "           1 - packed 4 bytes.\n"
		  "      --packuv <num>       Texture coordinate packing.\n"
		  "           0 - unpacked 8 bytes (default).\n"
		  "           1 - packed 4 bytes.\n"
		  "      --tangent            Calculate tangent vectors (packing mode is the same as normal).\n"

		  "\n"
		  "For additional information, see https://github.com/bkaradzic/bgfx\n"
		);
}

inline uint32_t rgbaToAbgr(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
{
	return (uint32_t(_r)<<0)
		 | (uint32_t(_g)<<8)
		 | (uint32_t(_b)<<16)
		 | (uint32_t(_a)<<24)
		 ;
}

int main(int _argc, const char* _argv[])
{
	bx::CommandLine cmdLine(_argc, _argv);

	const char* filePath = cmdLine.findOption('f');
	if (NULL == filePath)
	{
		help("Input file name must be specified.");
		return EXIT_FAILURE;
	}

	const char* outFilePath = cmdLine.findOption('o');
	if (NULL == outFilePath)
	{
		help("Output file name must be specified.");
		return EXIT_FAILURE;
	}

	float scale = 1.0f;
	const char* scaleArg = cmdLine.findOption('s', "scale");
	if (NULL != scaleArg)
	{
		scale = (float)atof(scaleArg);
	}

	cmdLine.hasArg(s_obbSteps, '\0', "obb");
	s_obbSteps = bx::uint32_min(bx::uint32_max(s_obbSteps, 1), 90);

	uint32_t packNormal = 0;
	cmdLine.hasArg(packNormal, '\0', "packnormal");

	uint32_t packUv = 0;
	cmdLine.hasArg(packNormal, '\0', "packuv");
	
	bool ccw = cmdLine.hasArg("ccw");
	bool flipV = cmdLine.hasArg("flipv");
	bool hasTangent = cmdLine.hasArg("tangent");

	FILE* file = fopen(filePath, "r");
	if (NULL == file)
	{
		printf("Unable to open input file '%s'.", filePath);
		exit(EXIT_FAILURE);
	}

	int64_t parseElapsed = -bx::getHPCounter();
	int64_t triReorderElapsed = 0;

	uint32_t size = (uint32_t)fsize(file);
	char* data = new char[size+1];
	size = (uint32_t)fread(data, 1, size, file);
	data[size] = '\0';
	fclose(file);

	// https://en.wikipedia.org/wiki/Wavefront_.obj_file

	Vector3Array positions;
	Vector3Array normals;
	Vector3Array texcoords;
	Index3Map indexMap;
	TriangleArray triangles;
	GroupArray groups;

	uint32_t num = 0;

	Group group;
	group.m_startTriangle = 0;
	group.m_numTriangles = 0;

	char commandLine[2048];
	uint32_t len = sizeof(commandLine);
	int argc;
	char* argv[64];
	const char* next = data;
	do
	{
		next = tokenizeCommandLine(next, commandLine, len, argc, argv, countof(argv), '\n');
		if (0 < argc)
		{
			if (0 == strcmp(argv[0], "#") )
			{
				if (2 < argc
				&&  0 == strcmp(argv[2], "polygons") )
				{
				}
			}
			else if (0 == strcmp(argv[0], "f") )
			{
				Triangle triangle;

				for (uint32_t edge = 0, numEdges = argc-1; edge < numEdges; ++edge)
				{
					Index3 index;
					index.m_texcoord = -1;
					index.m_normal = -1;
					index.m_vertexIndex = -1;

					char* vertex = argv[edge+1];
					char* texcoord = strchr(vertex, '/');
					if (NULL != texcoord)
					{
						*texcoord++ = '\0';

						char* normal = strchr(texcoord, '/');
						if (NULL != normal)
						{
							*normal++ = '\0';
							index.m_normal = atoi(normal)-1;
						}

						index.m_texcoord = atoi(texcoord)-1;
					}

					index.m_position = atoi(vertex)-1;

					uint64_t hash0 = index.m_position;
					uint64_t hash1 = uint64_t(index.m_texcoord)<<20;
					uint64_t hash2 = uint64_t(index.m_normal)<<40;
					uint64_t hash = hash0^hash1^hash2;

					std::pair<Index3Map::iterator, bool> result = indexMap.insert(std::make_pair(hash, index) );
					if (!result.second)
					{
						Index3& oldIndex = result.first->second;
						BX_CHECK(oldIndex.m_position == index.m_position
							&& oldIndex.m_texcoord == index.m_texcoord
							&& oldIndex.m_normal == index.m_normal
							, "Hash collision!"
							);
					}

					switch (edge)
					{
					case 0:
					case 1:
					case 2:
						triangle.m_index[edge] = hash;
						if (2 == edge)
						{
							if (ccw)
							{
								std::swap(triangle.m_index[1], triangle.m_index[2]);
							}
							triangles.push_back(triangle);
						}
						break;

					default:
						if (ccw)
						{
							triangle.m_index[2] = triangle.m_index[1];
							triangle.m_index[1] = hash;
						}
						else
						{
							triangle.m_index[1] = triangle.m_index[2];
							triangle.m_index[2] = hash;
						}
						triangles.push_back(triangle);
						break;
					}
				}
			}
			else if (0 == strcmp(argv[0], "g") )
			{
				EXPECT(1 < argc);
				group.m_name = argv[1];
			}
			else if (*argv[0] == 'v')
			{
				group.m_numTriangles = (uint32_t)(triangles.size() ) - group.m_startTriangle;
				if (0 < group.m_numTriangles)
				{
					groups.push_back(group);
					group.m_startTriangle = (uint32_t)(triangles.size() );
					group.m_numTriangles = 0;
				}

				if (0 == strcmp(argv[0], "vn") )
				{
					Vector3 normal;
					normal.x = (float)atof(argv[1]);
					normal.y = (float)atof(argv[2]);
					normal.z = (float)atof(argv[3]);

					normals.push_back(normal);
				}
				else if (0 == strcmp(argv[0], "vp") )
				{
					static bool once = true;
					if (once)
					{
						once = false;
						printf("warning: 'parameter space vertices' are unsupported.\n");
					}
				}
				else if (0 == strcmp(argv[0], "vt") )
				{
					Vector3 texcoord;
					texcoord.x = (float)atof(argv[1]);
					texcoord.y = 0.0f;
					texcoord.z = 0.0f;
					switch (argc)
					{
					case 4:
						texcoord.z = (float)atof(argv[3]);
						// fallthrough
					case 3:
						texcoord.y = (float)atof(argv[2]);
						break;

					default:
						break;
					}

					texcoords.push_back(texcoord);
				}
				else
				{
					float px = (float)atof(argv[1]);
					float py = (float)atof(argv[2]);
					float pz = (float)atof(argv[3]);
					float pw = 1.0f;
					if (argc > 4)
					{
						pw = (float)atof(argv[4]);
					}

					float invW = scale/pw;
					px *= invW;
					py *= invW;
					pz *= invW;

					Vector3 pos;
					pos.x = px;
					pos.y = py;
					pos.z = pz;

					positions.push_back(pos);
				}
			}
			else if (0 == strcmp(argv[0], "usemtl") )
			{
				std::string material(argv[1]);

				if (material != group.m_material)
				{
					group.m_numTriangles = (uint32_t)(triangles.size() ) - group.m_startTriangle;
					if (0 < group.m_numTriangles)
					{
						groups.push_back(group);
						group.m_startTriangle = (uint32_t)(triangles.size() );
						group.m_numTriangles = 0;
					}
				}

				group.m_material = material;
			}
// unsupported tags
// 				else if (0 == strcmp(argv[0], "mtllib") )
// 				{
// 				}
// 				else if (0 == strcmp(argv[0], "o") )
// 				{
// 				}
// 				else if (0 == strcmp(argv[0], "s") )
// 				{
// 				}
		}

		++num;
	}
	while ('\0' != *next);

	group.m_numTriangles = (uint32_t)(triangles.size() ) - group.m_startTriangle;
	if (0 < group.m_numTriangles)
	{
		groups.push_back(group);
		group.m_startTriangle = (uint32_t)(triangles.size() );
		group.m_numTriangles = 0;
	}

	delete [] data;

	int64_t now = bx::getHPCounter();
	parseElapsed += now;
	int64_t convertElapsed = -now;

	struct GroupSortByMaterial
	{
		bool operator()(const Group& _lhs, const Group& _rhs)
		{
			return _lhs.m_material < _rhs.m_material;
		}
	};

	std::sort(groups.begin(), groups.end(), GroupSortByMaterial() );

	bool hasColor = false;
	bool hasNormal;
	bool hasTexcoord;
	{
		Index3Map::const_iterator it = indexMap.begin();
		hasNormal = -1 != it->second.m_normal;
		hasTexcoord = -1 != it->second.m_texcoord;

		if (!hasTexcoord
		&&  texcoords.size() == positions.size() )
		{
			hasTexcoord = true;

			for (Index3Map::iterator it = indexMap.begin(), itEnd = indexMap.end(); it != itEnd; ++it)
			{
				it->second.m_texcoord = it->second.m_position;
			}
		}

		if (!hasNormal
		&&  normals.size() == positions.size() )
		{
			hasNormal = true;

			for (Index3Map::iterator it = indexMap.begin(), itEnd = indexMap.end(); it != itEnd; ++it)
			{
				it->second.m_normal = it->second.m_position;
			}
		}
	}

	bgfx::VertexDecl decl;
	decl.begin();
	decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);

	if (hasColor)
	{
		decl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
	}

	if (hasTexcoord)
	{
		switch (packUv)
		{
		default:
		case 0:
			decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);
			break;

		case 1:
			decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Half);
			break;
		}
	}

	if (hasNormal)
	{
		switch (packNormal)
		{
		default:
		case 0:
			decl.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float);
			if (hasTangent)
			{
				decl.add(bgfx::Attrib::Tangent, 3, bgfx::AttribType::Float);
			}
			break;

		case 1:
			decl.add(bgfx::Attrib::Normal, 4, bgfx::AttribType::Uint8, true);
			if (hasTangent)
			{
				decl.add(bgfx::Attrib::Tangent, 4, bgfx::AttribType::Uint8, true);
			}
			break;
		}
	}
	decl.end();

	uint32_t stride = decl.getStride();
	uint8_t* vertexData = new uint8_t[triangles.size() * 3 * stride];
	uint16_t* indexData = new uint16_t[triangles.size() * 3];
	int32_t numVertices = 0;
	int32_t numIndices = 0;
	int32_t numPrimitives = 0;

	uint8_t* vertices = vertexData;
	uint16_t* indices = indexData;

	std::string material = groups.begin()->m_material;

	PrimitiveArray primitives;

	bx::CrtFileWriter writer;
	if (0 != writer.open(outFilePath) )
	{
		printf("Unable to open output file '%s'.", outFilePath);
		exit(EXIT_FAILURE);
	}

	Primitive prim;
	prim.m_startVertex = 0;
	prim.m_startIndex = 0;

	uint32_t positionOffset = decl.getOffset(bgfx::Attrib::Position);
	uint32_t color0Offset = decl.getOffset(bgfx::Attrib::Color0);
	uint32_t normalOffset = decl.getOffset(bgfx::Attrib::Normal);
	uint32_t tangentOffset = decl.getOffset(bgfx::Attrib::Tangent);
	uint32_t texcoord0Offset = decl.getOffset(bgfx::Attrib::TexCoord0);

	uint32_t ii = 0;
	for (GroupArray::const_iterator groupIt = groups.begin(); groupIt != groups.end(); ++groupIt, ++ii)
	{
		for (uint32_t tri = groupIt->m_startTriangle, end = tri + groupIt->m_numTriangles; tri < end; ++tri)
		{
			if (material != groupIt->m_material
			||  65533 < numVertices)
			{
				prim.m_numVertices = numVertices - prim.m_startVertex;
				prim.m_numIndices = numIndices - prim.m_startIndex;
				if (0 < prim.m_numVertices)
				{
					primitives.push_back(prim);
				}

				triReorderElapsed -= bx::getHPCounter();
				for (PrimitiveArray::const_iterator primIt = primitives.begin(); primIt != primitives.end(); ++primIt)
				{
					const Primitive& prim = *primIt;
					triangleReorder(indexData + prim.m_startIndex, prim.m_numIndices, numVertices, 32);
				}
				triReorderElapsed += bx::getHPCounter();

				write(&writer, vertexData, numVertices, decl, indexData, numIndices, material, primitives);
				primitives.clear();

				for (Index3Map::iterator indexIt = indexMap.begin(); indexIt != indexMap.end(); ++indexIt)
				{
					indexIt->second.m_vertexIndex = -1;
				}

				vertices = vertexData;
				indices = indexData;
				numVertices = 0;
				numIndices = 0;
				prim.m_startVertex = 0;
				prim.m_startIndex = 0;
				++numPrimitives;

				material = groupIt->m_material;
			}

			Triangle& triangle = triangles[tri];
			for (uint32_t edge = 0; edge < 3; ++edge)
			{
				uint64_t hash = triangle.m_index[edge];
				Index3& index = indexMap[hash];
				if (index.m_vertexIndex == -1)
				{
		 			index.m_vertexIndex = numVertices++;

					float* position = (float*)(vertices + positionOffset);
					memcpy(position, &positions[index.m_position], 3*sizeof(float) );

					if (hasColor)
					{
						uint32_t* color0 = (uint32_t*)(vertices + color0Offset);
						*color0 = rgbaToAbgr(numVertices%255, numIndices%255, 0, 0xff);
					}

					if (hasTexcoord)
					{
						float uv[2];
						memcpy(uv, &texcoords[index.m_texcoord], 2*sizeof(float) );

						if (flipV)
						{
							uv[1] = -uv[1];
						}

						switch (packUv)
						{
						default:
						case 0:
							{
								float* texcoord0 = (float*)(vertices + texcoord0Offset);
								memcpy(texcoord0, uv, 2*sizeof(float) );
							}
							break;

						case 1:
							{
								uint32_t* texcoord0 = (uint32_t*)(vertices + texcoord0Offset);
								*texcoord0 = packF2h(uv[0], uv[1]);
							}
							break;
						}
					}

					if (hasNormal)
					{
						switch (packNormal)
						{
						default:
						case 0:
							{
								float* normal = (float*)(vertices + normalOffset);
								vec3Norm(normal, (float*)&normals[index.m_normal]);

								if (hasTangent)
								{
									float* tangent = (float*)(vertices + tangentOffset);
									memset(tangent, 0, 3*sizeof(float) );
								}
							}
							break;

						case 1:
							{
								float normal[3];
								vec3Norm(normal, (float*)&normals[index.m_normal]);
								uint32_t* nxyz0 = (uint32_t*)(vertices + normalOffset);
								*nxyz0 = packF4u(normal[0], normal[1], normal[2]);

								if (hasTangent)
								{
									uint32_t* txyz0 = (uint32_t*)(vertices + tangentOffset);
									*txyz0 = packF4u(0.0f);
								}
							}
							break;
						}
					}

					vertices += stride;
				}

				*indices++ = (uint16_t)index.m_vertexIndex;
				++numIndices;
			}
		}

		if (0 < numVertices)
		{
			prim.m_numVertices = numVertices - prim.m_startVertex;
			prim.m_numIndices = numIndices - prim.m_startIndex;
			prim.m_name = groupIt->m_name;
			primitives.push_back(prim);
			prim.m_startVertex = numVertices;
			prim.m_startIndex = numIndices;
		}

		BX_TRACE("%3d: s %5d, n %5d, %s\n"
			, ii
			, groupIt->m_startTriangle
			, groupIt->m_numTriangles
			, groupIt->m_material.c_str()
			);
	}

	if (0 < primitives.size() )
	{
		triReorderElapsed -= bx::getHPCounter();
		for (PrimitiveArray::const_iterator primIt = primitives.begin(); primIt != primitives.end(); ++primIt)
		{
			const Primitive& prim = *primIt;
			triangleReorder(indexData + prim.m_startIndex, prim.m_numIndices, numVertices, 32);
		}
		triReorderElapsed += bx::getHPCounter();

		write(&writer, vertexData, numVertices, decl, indexData, numIndices, material, primitives);
	}

	printf("size: %d\n", writer.seek() );
	writer.close();

	delete [] indexData;
	delete [] vertexData;

	now = bx::getHPCounter();
	convertElapsed += now;

	printf("parse %f [s]\ntri reorder %f [s]\nconvert %f [s]\n# %d, g %d, p %d, v %d, i %d\n"
		, double(parseElapsed)/bx::getHPFrequency()
		, double(triReorderElapsed)/bx::getHPFrequency()
		, double(convertElapsed)/bx::getHPFrequency()
		, num
		, groups.size()
		, numPrimitives
		, numVertices
		, numIndices
		);

	return EXIT_SUCCESS;
}
