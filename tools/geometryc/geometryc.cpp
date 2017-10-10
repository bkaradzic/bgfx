/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <stdio.h>

#include <algorithm>
#include <vector>

#include <bx/string.h>
#include <bgfx/bgfx.h>
#include "../../src/vertexdecl.h"

#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>
#include <tinystl/unordered_set.h>
#include <tinystl/string.h>
#include <tinystl/vector.h>
namespace stl = tinystl;

#include <forsyth-too/forsythtriangleorderoptimizer.h>
#include <ib-compress/indexbuffercompression.h>

//#undef GEOMETRYC_USE_ASSIMP
#if GEOMETRYC_USE_ASSIMP
#include <assimp/Importer.hpp>
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#endif

#define BGFX_GEOMETRYC_VERSION_MAJOR 2
#define BGFX_GEOMETRYC_VERSION_MINOR 0

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

#include <bx/bx.h>
#include <bx/debug.h>
#include <bx/commandline.h>
#include <bx/timer.h>
#include <bx/hash.h>
#include <bx/uint32_t.h>
#include <bx/math.h>
#include <bx/file.h>

#include "bounds.h"

struct Vector3
{
	float x;
	float y;
	float z;
};

typedef stl::vector<Vector3> Vector3Array;

struct Index3
{
	int32_t m_position;
	int32_t m_texcoord;
	int32_t m_normal;
	int32_t m_vertexIndex;
	int32_t m_vbc; // Barycentric ID. Holds eigher 0, 1 or 2.


	uint64_t hash() const
	{
		uint64_t hash0 = m_position;
		uint64_t hash1 = uint64_t(m_texcoord) << 20;
		uint64_t hash2 = uint64_t(m_normal) << 40;
		uint64_t hash3 = uint64_t(m_vbc) << 60;
		uint64_t hash = hash0^hash1^hash2^hash3;
		return hash;
	}

};

typedef stl::unordered_map<uint64_t, Index3> Index3Map;


class StringsTable
{
	stl::vector<stl::string> entries;
	uint32_t sizeInChars;

public:

	typedef stl::vector<stl::string>::const_iterator const_iterator;

	static const uint32_t invalid_offset = uint32_t(-1);

	StringsTable()
	{
		sizeInChars = 0;
		entries.reserve(32);
	}

	void clear()
	{
		sizeInChars = 0;
		entries.clear();
	}

	uint32_t getSizeInChars() const
	{
		return sizeInChars;
	}

	uint32_t find(const stl::string & s) const
	{
		uint32_t offset = 0;
		for (uint32_t i = 0; i < entries.size(); i++)
		{
			if (entries[i] == s)
			{
				return offset;
			}
			offset += entries[i].size() + 1;
		}

		return invalid_offset;
	}

	uint32_t add(const stl::string & s)
	{
		uint32_t offset = find(s);
		if (offset != invalid_offset)
		{
			return offset;
		}

		offset = sizeInChars;
		sizeInChars += s.size() + 1;
		entries.push_back(s);
		return offset;
	}

	const_iterator begin() const
	{
		return entries.begin();
	}

	const_iterator end() const
	{
		return entries.end();
	}

};


struct Triangle
{
	uint64_t m_index[3];
};

typedef stl::vector<Triangle> TriangleArray;

struct Material
{
	uint32_t m_nameId;
	uint32_t m_diffuseId;
	uint32_t m_normalId;
	uint32_t m_specularId;
};

typedef stl::vector<Material> MaterialArray;

struct Group
{
	uint32_t m_startTriangle;
	uint32_t m_numTriangles;
	uint32_t m_nameId;
	uint32_t m_materialIndex;
	stl::string m_materialName;};

typedef stl::vector<Group> GroupArray;

struct Primitive
{
	uint32_t m_startVertex;
	uint32_t m_startIndex;
	uint32_t m_numVertices;
	uint32_t m_numIndices;
	uint32_t m_nameId;
};

typedef stl::vector<Primitive> PrimitiveArray;

static uint32_t s_obbSteps = 17;

#define BGFX_CHUNK_MAGIC_VB  BX_MAKEFOURCC('V', 'B', ' ', 0x1)
#define BGFX_CHUNK_MAGIC_IB  BX_MAKEFOURCC('I', 'B', ' ', 0x0)
#define BGFX_CHUNK_MAGIC_IBC BX_MAKEFOURCC('I', 'B', 'C', 0x0)
#define BGFX_CHUNK_MAGIC_PRI BX_MAKEFOURCC('P', 'R', 'I', 0x1)
#define BGFX_CHUNK_MAGIC_STR BX_MAKEFOURCC('S', 'T', 'R', 0x0)
#define BGFX_CHUNK_MAGIC_MAT BX_MAKEFOURCC('M', 'A', 'T', 0x0)

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
	bx::memCopy(_indices, newIndexList, _numIndices*2);
	delete [] newIndexList;
}

void triangleCompress(bx::WriterI* _writer, uint16_t* _indices, uint32_t _numIndices, uint8_t* _vertexData, uint32_t _numVertices, uint16_t _stride)
{
	uint32_t* vertexRemap = (uint32_t*)malloc(_numVertices*sizeof(uint32_t) );

	WriteBitstream writer;
	CompressIndexBuffer(_indices, _numIndices/3, vertexRemap, _numVertices, IBCF_AUTO, writer);
	writer.Finish();
	printf( "uncompressed: %10d, compressed: %10d, ratio: %0.2f%%\n"
		, _numIndices*2
		, (uint32_t)writer.ByteSize()
		, 100.0f - float(writer.ByteSize() ) / float(_numIndices*2)*100.0f
		);

	BX_UNUSED(_vertexData, _stride);
	uint8_t* outVertexData = (uint8_t*)malloc(_numVertices*_stride);
	for (uint32_t ii = 0; ii < _numVertices; ++ii)
	{
		uint32_t remap = vertexRemap[ii];
		remap = UINT32_MAX == remap ? ii : remap;
		bx::memCopy(&outVertexData[remap*_stride], &_vertexData[ii*_stride], _stride);
	}
	bx::memCopy(_vertexData, outVertexData, _numVertices*_stride);
	free(outVertexData);

	free(vertexRemap);

	bx::write(_writer, writer.RawData(), (uint32_t)writer.ByteSize() );
}

void packTangents(void* _vertices, uint16_t _numVertices, bgfx::VertexDecl _decl, Vector3* tangents, Vector3* bitangents)
{
	for (uint32_t i = 0; i < _numVertices; ++i)
	{
		float normal[4];
		bgfx::vertexUnpack(normal, bgfx::Attrib::Normal, _decl, _vertices, i);

		float nxt[3];
		bx::vec3Cross(nxt, (const float*)&tangents[i], normal);

		float tangent[4];
		tangent[0] = tangents[i].x;
		tangent[1] = tangents[i].y;
		tangent[2] = tangents[i].z;
		tangent[3] = bx::vec3Dot(nxt, (const float*)&bitangents[i]) < 0.0f ? -1.0f : 1.0f;
		bgfx::vertexPack(tangent, true, bgfx::Attrib::Tangent, _decl, _vertices, i);
	}

}

void calcTangents(void* _vertices, uint16_t _numVertices, bgfx::VertexDecl _decl, const uint16_t* _indices, uint32_t _numIndices)
{
	struct PosTexcoord
	{
		float m_x;
		float m_y;
		float m_z;
		float m_pad0;
		float m_u;
		float m_v;
		float m_pad1;
		float m_pad2;
	};

	float* tangents = new float[6*_numVertices];
	bx::memSet(tangents, 0, 6*_numVertices*sizeof(float) );

	PosTexcoord v0;
	PosTexcoord v1;
	PosTexcoord v2;

	for (uint32_t ii = 0, num = _numIndices/3; ii < num; ++ii)
	{
		const uint16_t* indices = &_indices[ii*3];
		uint32_t i0 = indices[0];
		uint32_t i1 = indices[1];
		uint32_t i2 = indices[2];

		bgfx::vertexUnpack(&v0.m_x, bgfx::Attrib::Position, _decl, _vertices, i0);
		bgfx::vertexUnpack(&v0.m_u, bgfx::Attrib::TexCoord0, _decl, _vertices, i0);

		bgfx::vertexUnpack(&v1.m_x, bgfx::Attrib::Position, _decl, _vertices, i1);
		bgfx::vertexUnpack(&v1.m_u, bgfx::Attrib::TexCoord0, _decl, _vertices, i1);

		bgfx::vertexUnpack(&v2.m_x, bgfx::Attrib::Position, _decl, _vertices, i2);
		bgfx::vertexUnpack(&v2.m_u, bgfx::Attrib::TexCoord0, _decl, _vertices, i2);

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
		const float* tanu = &tangents[ii*6];
		const float* tanv = &tangents[ii*6 + 3];

		float normal[4];
		bgfx::vertexUnpack(normal, bgfx::Attrib::Normal, _decl, _vertices, ii);
		float ndt = bx::vec3Dot(normal, tanu);

		float nxt[3];
		bx::vec3Cross(nxt, normal, tanu);

		float tmp[3];
		tmp[0] = tanu[0] - normal[0] * ndt;
		tmp[1] = tanu[1] - normal[1] * ndt;
		tmp[2] = tanu[2] - normal[2] * ndt;

		float tangent[4];
		bx::vec3Norm(tangent, tmp);

		tangent[3] = bx::vec3Dot(nxt, tanv) < 0.0f ? -1.0f : 1.0f;
		bgfx::vertexPack(tangent, true, bgfx::Attrib::Tangent, _decl, _vertices, ii);
	}

	delete [] tangents;
}

void write(bx::WriterI* _writer, const void* _vertices, uint32_t _numVertices, uint32_t _stride)
{
	Sphere maxSphere;
	calcMaxBoundingSphere(maxSphere, _vertices, _numVertices, _stride);

	Sphere minSphere;
	calcMinBoundingSphere(minSphere, _vertices, _numVertices, _stride, 0.01f, 1024);

	if (minSphere.m_radius > maxSphere.m_radius)
	{
		bx::write(_writer, maxSphere);
	}
	else
	{
		bx::write(_writer, minSphere);
	}

	Aabb aabb;
	toAabb(aabb, _vertices, _numVertices, _stride);
	bx::write(_writer, aabb);

	Obb obb;
	calcObb(obb, _vertices, _numVertices, _stride, s_obbSteps);
	bx::write(_writer, obb);
}

void write(bx::WriterI* _writer
		, const StringsTable& _stringTable)
{
	write(_writer, BGFX_CHUNK_MAGIC_STR);

	uint32_t sizeInChars = _stringTable.getSizeInChars();
	write(_writer, sizeInChars);
	for (StringsTable::const_iterator tableIt = _stringTable.begin(); tableIt != _stringTable.end(); ++tableIt)
	{
		const stl::string& entry = *tableIt;
		uint32_t stringSize = entry.size();
		write(_writer, entry.c_str(), stringSize + 1);
	}
}

void write(bx::WriterI* _writer
		, MaterialArray _materials)
{
	write(_writer, BGFX_CHUNK_MAGIC_MAT);

	uint32_t numMaterials = _materials.size();
	write(_writer, numMaterials);
	for (uint32_t i = 0; i < numMaterials; i++)
	{
		const Material& material = _materials[i];
		write(_writer, material.m_nameId);
		write(_writer, material.m_diffuseId);
		write(_writer, material.m_normalId);
		write(_writer, material.m_specularId);
	}
}


void write(bx::WriterI* _writer
		, const uint8_t* _vertices
		, uint32_t _numVertices
		, const bgfx::VertexDecl& _decl
		, const uint16_t* _indices
		, uint32_t _numIndices
		, const uint8_t* _compressedIndices
		, uint32_t _compressedSize
		, uint32_t _materialIndex
		, const PrimitiveArray& _primitives
		)
{
	using namespace bx;
	using namespace bgfx;

	uint32_t stride = _decl.getStride();
	write(_writer, BGFX_CHUNK_MAGIC_VB);
	write(_writer, _vertices, _numVertices, stride);

	write(_writer, _decl);

	write(_writer, uint16_t(_numVertices) );
	write(_writer, _vertices, _numVertices*stride);

	if (NULL != _compressedIndices)
	{
		write(_writer, BGFX_CHUNK_MAGIC_IBC);
		write(_writer, _numIndices);
		write(_writer, _compressedSize);
		write(_writer, _compressedIndices, _compressedSize);
	}
	else
	{
		write(_writer, BGFX_CHUNK_MAGIC_IB);
		write(_writer, _numIndices);
		write(_writer, _indices, _numIndices*2);
	}

	write(_writer, BGFX_CHUNK_MAGIC_PRI);
	write(_writer, _materialIndex);
	write(_writer, uint16_t(_primitives.size() ) );
	for (PrimitiveArray::const_iterator primIt = _primitives.begin(); primIt != _primitives.end(); ++primIt)
	{
		const Primitive& prim = *primIt;
		write(_writer, prim.m_nameId);
		write(_writer, prim.m_startIndex);
		write(_writer, prim.m_numIndices);
		write(_writer, prim.m_startVertex);
		write(_writer, prim.m_numVertices);
		write(_writer, &_vertices[prim.m_startVertex*stride], prim.m_numVertices, stride);
	}
}

inline uint32_t rgbaToAbgr(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
{
	return (uint32_t(_r)<<0)
		 | (uint32_t(_g)<<8)
		 | (uint32_t(_b)<<16)
		 | (uint32_t(_a)<<24)
		 ;
}

struct GroupSortByMaterial
{
	bool operator()(const Group& _lhs, const Group& _rhs)
	{
		return _lhs.m_materialIndex < _rhs.m_materialIndex;
	}
};

void help(const char* _error = NULL)
{
	if (NULL != _error)
	{
		fprintf(stderr, "Error:\n%s\n\n", _error);
	}

	fprintf(stderr
		, "geometryc, bgfx geometry compiler tool, version %d.%d.%d.\n"
		  "Copyright 2011-2017 Branimir Karadzic. All rights reserved.\n"
		  "License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause\n\n"
		, BGFX_GEOMETRYC_VERSION_MAJOR
		, BGFX_GEOMETRYC_VERSION_MINOR
		, BGFX_API_VERSION
		);

	fprintf(stderr
		, "Usage: geometryc -f <in> -o <out>\n"

		  "\n"
		  "Supported input file types:\n"
#if GEOMETRYC_USE_ASSIMP
		  "    *.fbx                  Autodesk\n"
		  "    *.dae                  Collada\n"
		  "    *.blend                Blender 3D\n"
		  "    *.3ds                  3ds Max 3DS\n"
		  "    *.ase                  3ds Max ASE\n"
		  "    *.obj                  Wavefront\n"
		  "    *.lwo                  LightWave\n"
		  "    *.ms3d                 Milkshape 3D\n"
#else
		  "    *.obj                  Wavefront\n"
#endif

		  "\n"
		  "Options:\n"
		  "  -h, --help               Help.\n"
		  "  -v, --version            Version information only.\n"
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
		  "      --barycentric        Adds barycentric vertex attribute (packed in bgfx::Attrib::Color1).\n"
		  "  -c, --compress           Compress indices.\n"

		  "\n"
		  "For additional information, see https://github.com/bkaradzic/bgfx\n"
		);
}


stl::string getTextureFilePath(const bx::StringView& _filePath)
{
	bx::FilePath filePath;
	filePath.set(_filePath);

	const bx::StringView path = filePath.getPath();
	const bx::StringView baseName = filePath.getBaseName();

	stl::string ddsName(baseName.getPtr(), baseName.getLength());
	ddsName.append(".dds");
	
	if (filePath.isAbsolute())
	{
		return ddsName;
	}

	bx::FilePath r;
	r.set(path);
	r.join(ddsName.c_str());

	return stl::string(r.get());
}


int main(int _argc, const char* _argv[])
{
	bx::CommandLine cmdLine(_argc, _argv);

	if (cmdLine.hasArg('v', "version") )
	{
		fprintf(stderr
			, "geometryc, bgfx geometry compiler tool, version %d.%d.%d.\n"
			, BGFX_GEOMETRYC_VERSION_MAJOR
			, BGFX_GEOMETRYC_VERSION_MINOR
			, BGFX_API_VERSION
			);
		return bx::kExitSuccess;
	}

	if (cmdLine.hasArg('h', "help") )
	{
		help();
		return bx::kExitFailure;
	}

	const char* filePath = cmdLine.findOption('f');
	if (NULL == filePath)
	{
		help("Input file name must be specified.");
		return bx::kExitFailure;
	}

	const char* outFilePath = cmdLine.findOption('o');
	if (NULL == outFilePath)
	{
		help("Output file name must be specified.");
		return bx::kExitFailure;
	}

	float scale = 1.0f;
	const char* scaleArg = cmdLine.findOption('s', "scale");
	if (NULL != scaleArg)
	{
		scale = (float)atof(scaleArg);
	}

	bool compress = cmdLine.hasArg('c', "compress");

	cmdLine.hasArg(s_obbSteps, '\0', "obb");
	s_obbSteps = bx::uint32_min(bx::uint32_max(s_obbSteps, 1), 90);

	uint32_t packNormal = 0;
	cmdLine.hasArg(packNormal, '\0', "packnormal");

	uint32_t packUv = 0;
	cmdLine.hasArg(packUv, '\0', "packuv");

	bool ccw = cmdLine.hasArg("ccw");
	bool flipV = cmdLine.hasArg("flipv");
	bool hasTangent = cmdLine.hasArg("tangent");
	bool hasBc = cmdLine.hasArg("barycentric");
	Vector3* precalculatedTangents = NULL;
	Vector3* precalculatedBitangents = NULL;

	Vector3Array positions;
	positions.reserve(512);

	Vector3Array normals;
	normals.reserve(512);

	Vector3Array texcoords;
	texcoords.reserve(512);

	TriangleArray triangles;
	triangles.reserve(512);

	GroupArray groups;
	groups.reserve(128);

	MaterialArray materials;
	materials.reserve(32);

	StringsTable stringsTable;
	Index3Map indexMap;

	int64_t parseElapsed = -bx::getHPCounter();
	int64_t triReorderElapsed = 0;
	uint32_t num = 0;

#if GEOMETRYC_USE_ASSIMP
	Assimp::Importer importer;
	const aiScene* asset = importer.ReadFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_FlipUVs);
	if (NULL == asset)
	{
		printf("Unable to open input file '%s'.", filePath);
		exit(bx::kExitFailure);
	}

	uint32_t numMeshes = asset->mNumMeshes;
	if (numMeshes == 0)
	{
		printf("There are no meshes found in the file '%s'.", filePath);
		exit(bx::kExitFailure);
	}

	aiString temp;
	stl::string materialName;
	stl::string diffuseMapName;
	stl::string normalMapName;
	stl::string specularMapName;
	for (uint32_t n = 0; n < asset->mNumMaterials; n++)
	{
		const aiMaterial* inMaterial = asset->mMaterials[n];

		if (inMaterial->Get(AI_MATKEY_NAME, temp) == aiReturn_SUCCESS)
		{
			materialName = temp.C_Str();
		}
		else
		{
			materialName = "default";
		}

		if (inMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &temp) == aiReturn_SUCCESS)
		{
			diffuseMapName = getTextureFilePath(temp.C_Str());
		}
		else
		{
			diffuseMapName = "";
		}

		if (inMaterial->GetTexture(aiTextureType_NORMALS, 0, &temp) == aiReturn_SUCCESS)
		{
			normalMapName = getTextureFilePath(temp.C_Str());
		}
		else
		{
			normalMapName = "";
		}

		if (inMaterial->GetTexture(aiTextureType_SPECULAR, 0, &temp) == aiReturn_SUCCESS)
		{
			specularMapName = getTextureFilePath(temp.C_Str());
		}
		else
		{
			specularMapName = "";
		}

		Material material;
		material.m_nameId = stringsTable.add(materialName);
		material.m_diffuseId = stringsTable.add(diffuseMapName);
		material.m_normalId = stringsTable.add(normalMapName);
		material.m_specularId = stringsTable.add(specularMapName);
		materials.push_back(material);
	}
	
	Vector3Array tangents;
	tangents.reserve(512);

	Vector3Array bitangents;
	bitangents.reserve(512);

	uint32_t startVertex = 0;
	for (uint32_t n = 0; n < numMeshes; n++)
	{
		const aiMesh* mesh = asset->mMeshes[n];

		uint32_t firstTriangle = triangles.size();

		for (uint32_t i = 0; i < mesh->mNumFaces; i++)
		{
			const aiFace& inFace = mesh->mFaces[i];
			BX_CHECK(inFace.mNumIndices == 3, "Mesh must be triangulated");
			if (inFace.mNumIndices != 3)
			{
				continue;
			}

			Triangle triangle;
			for (uint32_t edge = 0; edge < 3; ++edge)
			{
				Index3 index;
				index.m_vertexIndex = -1;
				index.m_texcoord = startVertex + inFace.mIndices[edge];
				index.m_normal = startVertex + inFace.mIndices[edge];
				index.m_position = startVertex + inFace.mIndices[edge];

				if (hasBc)
				{
					index.m_vbc = edge < 3 ? edge : (1 + (edge + 1)) & 1;
				}
				else
				{
					index.m_vbc = 0;
				}

				uint64_t hash = index.hash();

				stl::pair<Index3Map::iterator, bool> result = indexMap.insert(stl::make_pair(hash, index));
				if (!result.second)
				{
					Index3& oldIndex = result.first->second;
					BX_UNUSED(oldIndex);
					BX_CHECK(oldIndex.m_position == index.m_position
						&& oldIndex.m_texcoord == index.m_texcoord
						&& oldIndex.m_normal == index.m_normal
						, "Hash collision!"
						);
				}

				triangle.m_index[edge] = hash;
			}

			if (ccw)
			{
				std::swap(triangle.m_index[1], triangle.m_index[2]);
			}

			triangles.push_back(triangle);
		}

		uint32_t lastTriangle = triangles.size();


		for (uint32_t i = 0; i < mesh->mNumVertices; i++)
		{
			const aiVector3D& inPos = mesh->mVertices[i];

			Vector3 pos;
			pos.x = inPos.x;
			pos.y = inPos.y;
			pos.z = inPos.z;
			positions.push_back(pos);

			Vector3 uv;
			aiVector3D* uvStream0 = mesh->mTextureCoords[0];
			if (uvStream0)
			{
				const aiVector3D& inUv = uvStream0[i];
				uv.x = inUv.x;
				uv.y = inUv.y;
				uv.z = inUv.z;
			} else
			{
				uv.x = 0.0f;
				uv.y = 0.0f;
				uv.z = 0.0f;
			}
			texcoords.push_back(uv);

			const aiVector3D& inNormal = mesh->mNormals[i];
			Vector3 normal;
			normal.x = inNormal.x;
			normal.y = inNormal.y;
			normal.z = inNormal.z;
			bx::vec3Norm((float*)&normal, (float*)&normal);
			normals.push_back(normal);

			if (mesh->HasTangentsAndBitangents())
			{
				const aiVector3D& inTangent = mesh->mTangents[i];
				Vector3 tangent;
				tangent.x = inTangent.x;
				tangent.y = inTangent.y;
				tangent.z = inTangent.z;
				bx::vec3Norm((float*)&tangent, (float*)&tangent);
				tangents.push_back(tangent);

				const aiVector3D& inBitangent = mesh->mBitangents[i];
				Vector3 bitangent;
				bitangent.x = inBitangent.x;
				bitangent.y = inBitangent.y;
				bitangent.z = inBitangent.z;
				bx::vec3Norm((float*)&bitangent, (float*)&bitangent);
				bitangents.push_back(bitangent);
			}
		}

		uint32_t trianglesCount = lastTriangle - firstTriangle;

		if (trianglesCount > 0)
		{
			aiString meshName = mesh->mName;

			Group group;
			group.m_nameId = stringsTable.add(meshName.C_Str());
			group.m_materialIndex = mesh->mMaterialIndex;
			group.m_startTriangle = firstTriangle;
			group.m_numTriangles = lastTriangle - firstTriangle;
			groups.push_back(group);
		}

		startVertex = positions.size();
	}

	if (tangents.size() == positions.size() && bitangents.size() == positions.size())
	{
		hasTangent = true;
		precalculatedTangents = &tangents[0];
		precalculatedBitangents = &bitangents[0];
	}


#else

	FILE* file = fopen(filePath, "r");
	if (NULL == file)
	{
		printf("Unable to open input file '%s'.", filePath);
		exit(bx::kExitFailure);
	}

	uint32_t size = (uint32_t)fsize(file);
	char* data = new char[size+1];
	size = (uint32_t)fread(data, 1, size, file);
	data[size] = '\0';
	fclose(file);

	// https://en.wikipedia.org/wiki/Wavefront_.obj_file

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
		next = bx::tokenizeCommandLine(next, commandLine, len, argc, argv, BX_COUNTOF(argv), '\n');
		if (0 < argc)
		{
			if (0 == bx::strCmp(argv[0], "#") )
			{
				if (2 < argc
				&&  0 == bx::strCmp(argv[2], "polygons") )
				{
				}
			}
			else if (0 == bx::strCmp(argv[0], "f") )
			{
				Triangle triangle;
				bx::memSet(&triangle, 0, sizeof(Triangle) );

				const int numNormals   = (int)normals.size();
				const int numTexcoords = (int)texcoords.size();
				const int numPositions = (int)positions.size();
				for (uint32_t edge = 0, numEdges = argc-1; edge < numEdges; ++edge)
				{
					Index3 index;
					index.m_texcoord = -1;
					index.m_normal = -1;
					index.m_vertexIndex = -1;
					if (hasBc)
					{
						index.m_vbc = edge < 3 ? edge : (1+(edge+1) )&1;
					}
					else
					{
						index.m_vbc = 0;
					}

					const char* vertex = argv[edge+1];
					char* texcoord = const_cast<char*>(bx::strFind(vertex, '/') );
					if (NULL != texcoord)
					{
						*texcoord++ = '\0';

						char* normal = const_cast<char*>(bx::strFind(texcoord, '/') );
						if (NULL != normal)
						{
							*normal++ = '\0';
							int32_t nn;
							bx::fromString(&nn, normal);
							index.m_normal = (nn < 0) ? nn+numNormals : nn-1;
						}

						// https://en.wikipedia.org/wiki/Wavefront_.obj_file#Vertex_Normal_Indices_Without_Texture_Coordinate_Indices
						if(*texcoord != '\0')
						{
							int32_t tex;
							bx::fromString(&tex, texcoord);
							index.m_texcoord = (tex < 0) ? tex+numTexcoords : tex-1;
						}
					}

					int32_t pos;
					bx::fromString(&pos, vertex);
					index.m_position = (pos < 0) ? pos+numPositions : pos-1;

					uint64_t hash = index.hash();

					stl::pair<Index3Map::iterator, bool> result = indexMap.insert(stl::make_pair(hash, index) );
					if (!result.second)
					{
						Index3& oldIndex = result.first->second;
						BX_UNUSED(oldIndex);
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
			else if (0 == bx::strCmp(argv[0], "g") )
			{
				group.m_nameId = stringsTable.add(argv[1]);
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

				if (0 == bx::strCmp(argv[0], "vn") )
				{
					Vector3 normal;
					normal.x = (float)atof(argv[1]);
					normal.y = (float)atof(argv[2]);
					normal.z = (float)atof(argv[3]);

					normals.push_back(normal);
				}
				else if (0 == bx::strCmp(argv[0], "vp") )
				{
					static bool once = true;
					if (once)
					{
						once = false;
						printf("warning: 'parameter space vertices' are unsupported.\n");
					}
				}
				else if (0 == bx::strCmp(argv[0], "vt") )
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
			else if (0 == bx::strCmp(argv[0], "usemtl") )
			{
				stl::string materialName(argv[1]);

				uint32_t materialNameId = stringsTable.add(materialName);
				bool isMaterialExists = false;
				for (uint32_t i = 0; i < materials.size(); i++)
				{
					if (materials[i].m_nameId == materialNameId)
					{
						isMaterialExists = true;
						break;
					}
				}

				if (!isMaterialExists)
				{
					Material material;
					material.m_nameId = materialNameId;
					material.m_diffuseId = stringsTable.add("");
					material.m_normalId = stringsTable.add("");
					material.m_specularId = stringsTable.add("");
					materials.push_back(material);
				}

				if (0 == bx::strCmp(materialName.c_str(), group.m_materialName.c_str()))
				{
					group.m_numTriangles = (uint32_t)(triangles.size() ) - group.m_startTriangle;
					if (0 < group.m_numTriangles)
					{
						groups.push_back(group);
						group.m_startTriangle = (uint32_t)(triangles.size() );
						group.m_numTriangles = 0;
					}
				}

				group.m_materialName = materialName;
			}
// unsupported tags
// 				else if (0 == bx::strCmp(argv[0], "mtllib") )
// 				{
// 				}
// 				else if (0 == bx::strCmp(argv[0], "o") )
// 				{
// 				}
// 				else if (0 == bx::strCmp(argv[0], "s") )
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

	if (indexMap.empty())
	{
		printf("Ignoring invalid Wavefront OBJ file '%s'.\n", filePath);
		exit(bx::kExitSuccess);
	}

#endif

	int64_t now = bx::getHPCounter();
	parseElapsed += now;
	int64_t convertElapsed = -now;

	std::sort(groups.begin(), groups.end(), GroupSortByMaterial() );

	bool hasColor = false;
	bool hasNormal;
	bool hasTexcoord;
	{
		Index3Map::const_iterator it = indexMap.begin();
		hasNormal   = -1 != it->second.m_normal;
		hasTexcoord = -1 != it->second.m_texcoord;

		if (!hasTexcoord)
		{
			for (Index3Map::iterator jt = indexMap.begin(), jtEnd = indexMap.end(); jt != jtEnd && !hasTexcoord; ++jt)
			{
				hasTexcoord |= -1 != jt->second.m_texcoord;
			}

			if (hasTexcoord)
			{
				for (Index3Map::iterator jt = indexMap.begin(), jtEnd = indexMap.end(); jt != jtEnd; ++jt)
				{
					jt->second.m_texcoord = -1 == jt->second.m_texcoord ? 0 : jt->second.m_texcoord;
				}
			}
		}

		if (!hasNormal)
		{
			for (Index3Map::iterator jt = indexMap.begin(), jtEnd = indexMap.end(); jt != jtEnd && !hasNormal; ++jt)
			{
				hasNormal |= -1 != jt->second.m_normal;
			}

			if (hasNormal)
			{
				for (Index3Map::iterator jt = indexMap.begin(), jtEnd = indexMap.end(); jt != jtEnd; ++jt)
				{
					jt->second.m_normal = -1 == jt->second.m_normal ? 0 : jt->second.m_normal;
				}
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

	if (hasBc)
	{
		decl.add(bgfx::Attrib::Color1, 4, bgfx::AttribType::Uint8, true);
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
		hasTangent &= hasTexcoord;

		switch (packNormal)
		{
		default:
		case 0:
			decl.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float);
			if (hasTangent)
			{
				decl.add(bgfx::Attrib::Tangent, 4, bgfx::AttribType::Float);
			}
			break;

		case 1:
			decl.add(bgfx::Attrib::Normal, 4, bgfx::AttribType::Uint8, true, true);
			if (hasTangent)
			{
				decl.add(bgfx::Attrib::Tangent, 4, bgfx::AttribType::Uint8, true, true);
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

	uint32_t materialIndex = groups.begin()->m_materialIndex;

	PrimitiveArray primitives;

	bx::FileWriter writer;
	if (!bx::open(&writer, outFilePath) )
	{
		printf("Unable to open output file '%s'.", outFilePath);
		exit(bx::kExitFailure);
	}

	write(&writer, stringsTable);
	write(&writer, materials);

	Primitive prim;
	prim.m_startVertex = 0;
	prim.m_startIndex  = 0;

	uint32_t positionOffset = decl.getOffset(bgfx::Attrib::Position);
	uint32_t color0Offset   = decl.getOffset(bgfx::Attrib::Color0);

	bx::DefaultAllocator crtAllocator;
	bx::MemoryBlock  memBlock(&crtAllocator);

	uint32_t ii = 0;
	for (GroupArray::const_iterator groupIt = groups.begin(); groupIt != groups.end(); ++groupIt, ++ii)
	{
		for (uint32_t tri = groupIt->m_startTriangle, end = tri + groupIt->m_numTriangles; tri < end; ++tri)
		{
			if (materialIndex != groupIt->m_materialIndex
			||  65533 < numVertices)
			{
				prim.m_numVertices = numVertices - prim.m_startVertex;
				prim.m_numIndices  = numIndices  - prim.m_startIndex;
				if (0 < prim.m_numVertices)
				{
					primitives.push_back(prim);
				}

				if (hasTangent)
				{
					if (precalculatedTangents && precalculatedBitangents)
					{
						packTangents(vertexData, uint16_t(numVertices), decl, precalculatedTangents, precalculatedBitangents);
					}
					else
					{
						calcTangents(vertexData, uint16_t(numVertices), decl, indexData, numIndices);
					}
				}

				bx::MemoryWriter memWriter(&memBlock);

				triReorderElapsed -= bx::getHPCounter();
				for (PrimitiveArray::const_iterator primIt = primitives.begin(); primIt != primitives.end(); ++primIt)
				{
					const Primitive& prim1 = *primIt;
					triangleReorder(indexData + prim1.m_startIndex, prim1.m_numIndices, numVertices, 32);
					if (compress)
					{
						triangleCompress(&memWriter
							, indexData  + prim1.m_startIndex
							, prim1.m_numIndices
							, vertexData + prim1.m_startVertex
							, numVertices
							, uint16_t(stride)
							);
					}
				}
				triReorderElapsed += bx::getHPCounter();

				write(&writer
					, vertexData
					, numVertices
					, decl
					, indexData
					, numIndices
					, (uint8_t*)memBlock.more()
					, memBlock.getSize()
					, materialIndex
					, primitives
					);
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

				materialIndex = groupIt->m_materialIndex;
			}

			Triangle& triangle = triangles[tri];
			for (uint32_t edge = 0; edge < 3; ++edge)
			{
				uint64_t hash = triangle.m_index[edge];
				Index3Map::iterator indexIt = indexMap.find(hash);
				BX_CHECK(indexIt != indexMap.end(), "Can't find valid index for triangle");
				Index3& index = indexIt->second;
				if (index.m_vertexIndex == -1)
				{
		 			index.m_vertexIndex = numVertices++;

					float* position = (float*)(vertices + positionOffset);
					bx::memCopy(position, &positions[index.m_position], 3*sizeof(float) );

					if (hasColor)
					{
						uint32_t* color0 = (uint32_t*)(vertices + color0Offset);
						*color0 = rgbaToAbgr(numVertices%255, numIndices%255, 0, 0xff);
					}

					if (hasBc)
					{
						const float bc[3] =
						{
							(index.m_vbc == 0) ? 1.0f : 0.0f,
							(index.m_vbc == 1) ? 1.0f : 0.0f,
							(index.m_vbc == 2) ? 1.0f : 0.0f,
						};
						bgfx::vertexPack(bc, true, bgfx::Attrib::Color1, decl, vertices);
					}

					if (hasTexcoord)
					{
						float uv[2];
						bx::memCopy(uv, &texcoords[index.m_texcoord], 2*sizeof(float) );

						if (flipV)
						{
							uv[1] = -uv[1];
						}

						bgfx::vertexPack(uv, true, bgfx::Attrib::TexCoord0, decl, vertices);
					}

					if (hasNormal)
					{
						float normal[4];
						bx::vec3Norm(normal, (float*)&normals[index.m_normal]);
						bgfx::vertexPack(normal, true, bgfx::Attrib::Normal, decl, vertices);
					}

					vertices += stride;
				}

				*indices++ = (uint16_t)index.m_vertexIndex;
				++numIndices;
			}
		}

		prim.m_numVertices = numVertices - prim.m_startVertex;
		if (0 < prim.m_numVertices)
		{
			prim.m_numIndices = numIndices - prim.m_startIndex;
			prim.m_nameId = groupIt->m_nameId;
			primitives.push_back(prim);
			prim.m_startVertex = numVertices;
			prim.m_startIndex  = numIndices;
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
		if (hasTangent)
		{
			calcTangents(vertexData, uint16_t(numVertices), decl, indexData, numIndices);
		}

		bx::MemoryWriter memWriter(&memBlock);

		triReorderElapsed -= bx::getHPCounter();
		for (PrimitiveArray::const_iterator primIt = primitives.begin(); primIt != primitives.end(); ++primIt)
		{
			const Primitive& prim1 = *primIt;
			triangleReorder(indexData + prim1.m_startIndex, prim1.m_numIndices, numVertices, 32);
			if (compress)
			{
				triangleCompress(&memWriter
					, indexData  + prim1.m_startIndex
					, prim1.m_numIndices
					, vertexData + prim1.m_startVertex
					, numVertices
					, uint16_t(stride)
					);
			}
		}
		triReorderElapsed += bx::getHPCounter();

		write(&writer
			, vertexData
			, numVertices
			, decl
			, indexData
			, numIndices
			, (uint8_t*)memBlock.more()
			, memBlock.getSize()
			, materialIndex
			, primitives
			);
	}

	printf("size: %d\n", uint32_t(bx::seek(&writer) ) );
	bx::close(&writer);

	delete [] indexData;
	delete [] vertexData;

	now = bx::getHPCounter();
	convertElapsed += now;

	printf("parse %f [s]\ntri reorder %f [s]\nconvert %f [s]\n# %d, g %d, p %d, v %d, i %d\n"
		, double(parseElapsed)/bx::getHPFrequency()
		, double(triReorderElapsed)/bx::getHPFrequency()
		, double(convertElapsed)/bx::getHPFrequency()
		, num
		, uint32_t(groups.size() )
		, numPrimitives
		, numVertices
		, numIndices
		);

	return bx::kExitSuccess;
}
