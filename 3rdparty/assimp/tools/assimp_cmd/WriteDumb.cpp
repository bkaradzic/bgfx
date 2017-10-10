/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2017, assimp team


All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the following 
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

/** @file  WriteTextDumb.cpp
 *  @brief Implementation of the 'assimp dump' utility
 */

#include "Main.h"
#include "../code/ProcessHelper.h"

const char* AICMD_MSG_DUMP_HELP = 
"assimp dump <model> [<out>] [-b] [-s] [-z] [common parameters]\n"
"\t -b Binary output \n"
"\t -s Shortened  \n"
"\t -z Compressed  \n"
"\t[See the assimp_cmd docs for a full list of all common parameters]  \n"
"\t -cfast    Fast post processing preset, runs just a few important steps \n"
"\t -cdefault Default post processing: runs all recommended steps\n"
"\t -cfull    Fires almost all post processing steps \n"
;

#include "../../code/assbin_chunks.h"

FILE* out = NULL;
bool shortened = false;

// -----------------------------------------------------------------------------------
// Compress a binary dump file (beginning at offset head_size)
void CompressBinaryDump(const char* file, unsigned int head_size)
{
	// for simplicity ... copy the file into memory again and compress it there
	FILE* p = fopen(file,"r");
	fseek(p,0,SEEK_END);
	const uint32_t size = ftell(p);
	fseek(p,0,SEEK_SET);

	if (size<head_size) {
		fclose(p);
		return;
	}

	uint8_t* data = new uint8_t[size];
	fread(data,1,size,p);

	uLongf out_size = (uLongf)((size-head_size) * 1.001 + 12.);
	uint8_t* out = new uint8_t[out_size];

	compress2(out,&out_size,data+head_size,size-head_size,9);
	fclose(p);
	p = fopen(file,"w");

	fwrite(data,head_size,1,p);
	fwrite(&out_size,4,1,p); // write size of uncompressed data
	fwrite(out,out_size,1,p);

	fclose(p);
	delete[] data;
	delete[] out;
}

// -----------------------------------------------------------------------------------
// Write a magic start value for each serialized data structure
inline uint32_t WriteMagic(uint32_t magic)
{
	fwrite(&magic,4,1,out);
	fwrite(&magic,4,1,out);
	return ftell(out)-4;
}

// use template specializations rather than regular overloading to be able to 
// explicitly select the right 'overload' to leave no doubts on what is called,
// retaining the possibility of letting the compiler select.
template <typename T> uint32_t Write(const T&);

// -----------------------------------------------------------------------------------
// Serialize an aiString
template <>
inline uint32_t Write<aiString>(const aiString& s)
{
	const uint32_t s2 = (uint32_t)s.length;
	fwrite(&s,4,1,out);
	fwrite(s.data,s2,1,out);
	return s2+4;
}

// -----------------------------------------------------------------------------------
// Serialize an unsigned int as uint32_t
template <>
inline uint32_t Write<unsigned int>(const unsigned int& w)
{
	const uint32_t t = (uint32_t)w;
	if (w > t) {
		// this shouldn't happen, integers in Assimp data structures never exceed 2^32
		printf("loss of data due to 64 -> 32 bit integer conversion");
	}
	
	fwrite(&t,4,1,out);
	return 4;
}

// -----------------------------------------------------------------------------------
// Serialize an unsigned int as uint16_t
template <>
inline uint32_t Write<uint16_t>(const uint16_t& w)
{
	fwrite(&w,2,1,out);
	return 2;
}

// -----------------------------------------------------------------------------------
// Serialize a float
template <>
inline uint32_t Write<float>(const float& f)
{
	static_assert(sizeof(float)==4, "sizeof(float)==4");
	fwrite(&f,4,1,out);
	return 4;
}

// -----------------------------------------------------------------------------------
// Serialize a double
template <>
inline uint32_t Write<double>(const double& f)
{
	static_assert(sizeof(double)==8, "sizeof(double)==8");
	fwrite(&f,8,1,out);
	return 8;
}

// -----------------------------------------------------------------------------------
// Serialize a vec3
template <>
inline uint32_t Write<aiVector3D>(const aiVector3D& v)
{
	uint32_t t = Write<float>(v.x);
	t += Write<float>(v.y);
	t += Write<float>(v.z);
	return t;
}

// -----------------------------------------------------------------------------------
// Serialize a color value
template <>
inline uint32_t Write<aiColor4D>(const aiColor4D& v)
{
	uint32_t t = Write<float>(v.r);
	t += Write<float>(v.g);
	t += Write<float>(v.b);
	t += Write<float>(v.a);
	return t;
}

// -----------------------------------------------------------------------------------
// Serialize a quaternion
template <>
inline uint32_t Write<aiQuaternion>(const aiQuaternion& v)
{
	uint32_t t = Write<float>(v.w);
	t += Write<float>(v.x);
	t += Write<float>(v.y);
	t += Write<float>(v.z);
	return 16;
}


// -----------------------------------------------------------------------------------
// Serialize a vertex weight
template <>
inline uint32_t Write<aiVertexWeight>(const aiVertexWeight& v)
{
	uint32_t t = Write<unsigned int>(v.mVertexId);
	return t+Write<float>(v.mWeight);
}

// -----------------------------------------------------------------------------------
// Serialize a mat4x4
template <>
inline uint32_t Write<aiMatrix4x4>(const aiMatrix4x4& m)
{
	for (unsigned int i = 0; i < 4;++i) {
		for (unsigned int i2 = 0; i2 < 4;++i2) {
			Write<float>(m[i][i2]);
		}
	}
	return 64;
}

// -----------------------------------------------------------------------------------
// Serialize an aiVectorKey
template <>
inline uint32_t Write<aiVectorKey>(const aiVectorKey& v)
{
	const uint32_t t = Write<double>(v.mTime);
	return t + Write<aiVector3D>(v.mValue);
}

// -----------------------------------------------------------------------------------
// Serialize an aiQuatKey
template <>
inline uint32_t Write<aiQuatKey>(const aiQuatKey& v)
{
	const uint32_t t = Write<double>(v.mTime);
	return t + Write<aiQuaternion>(v.mValue);
}

// -----------------------------------------------------------------------------------
// Write the min/max values of an array of Ts to the file
template <typename T>
inline uint32_t WriteBounds(const T* in, unsigned int size)
{
	T minc,maxc;
	Assimp::ArrayBounds(in,size,minc,maxc);

	const uint32_t t = Write<T>(minc);
	return t + Write<T>(maxc);
}



// -----------------------------------------------------------------------------------
void ChangeInteger(uint32_t ofs,uint32_t n)
{
	const uint32_t cur = ftell(out);
	fseek(out,ofs,SEEK_SET);
	fwrite(&n,4,1,out);
	fseek(out,cur,SEEK_SET);
}

// -----------------------------------------------------------------------------------
uint32_t WriteBinaryNode(const aiNode* node)
{
	uint32_t len = 0, old = WriteMagic(ASSBIN_CHUNK_AINODE);
	len += Write<aiString>(node->mName);
	len += Write<aiMatrix4x4>(node->mTransformation);
	len += Write<unsigned int>(node->mNumChildren);
	len += Write<unsigned int>(node->mNumMeshes);

	for (unsigned int i = 0; i < node->mNumMeshes;++i) {
		len += Write<unsigned int>(node->mMeshes[i]);
	}

	for (unsigned int i = 0; i < node->mNumChildren;++i) {
		len += WriteBinaryNode(node->mChildren[i])+8;
	}

	ChangeInteger(old,len);
	return len;
}

// -----------------------------------------------------------------------------------
uint32_t WriteBinaryTexture(const aiTexture* tex)
{
	uint32_t len = 0, old = WriteMagic(ASSBIN_CHUNK_AITEXTURE);

	len += Write<unsigned int>(tex->mWidth);
	len += Write<unsigned int>(tex->mHeight);
	len += static_cast<uint32_t>(fwrite(tex->achFormatHint,1,4,out));

	if(!shortened) {
		if (!tex->mHeight) {
			len += static_cast<uint32_t>(fwrite(tex->pcData,1,tex->mWidth,out));
		}
		else {
			len += static_cast<uint32_t>(fwrite(tex->pcData,1,tex->mWidth*tex->mHeight*4,out));
		}
	}

	ChangeInteger(old,len);
	return len;
}

// -----------------------------------------------------------------------------------
uint32_t WriteBinaryBone(const aiBone* b)
{
	uint32_t len = 0, old = WriteMagic(ASSBIN_CHUNK_AIBONE);

	len += Write<aiString>(b->mName);
	len += Write<unsigned int>(b->mNumWeights);
	len += Write<aiMatrix4x4>(b->mOffsetMatrix);

	// for the moment we write dumb min/max values for the bones, too.
	// maybe I'll add a better, hash-like solution later
	if (shortened) {
		len += WriteBounds(b->mWeights,b->mNumWeights);
	} // else write as usual
	else len += static_cast<uint32_t>(fwrite(b->mWeights,1,b->mNumWeights*sizeof(aiVertexWeight),out));

	ChangeInteger(old,len);
	return len;
}

// -----------------------------------------------------------------------------------
uint32_t WriteBinaryMesh(const aiMesh* mesh)
{
	uint32_t len = 0, old = WriteMagic(ASSBIN_CHUNK_AIMESH);

	len += Write<unsigned int>(mesh->mPrimitiveTypes);
	len += Write<unsigned int>(mesh->mNumVertices);
	len += Write<unsigned int>(mesh->mNumFaces);
	len += Write<unsigned int>(mesh->mNumBones);
	len += Write<unsigned int>(mesh->mMaterialIndex);

	// first of all, write bits for all existent vertex components
	unsigned int c = 0;
	if (mesh->mVertices) {
		c |= ASSBIN_MESH_HAS_POSITIONS;
	}
	if (mesh->mNormals) {
		c |= ASSBIN_MESH_HAS_NORMALS;
	}
	if (mesh->mTangents && mesh->mBitangents) {
		c |= ASSBIN_MESH_HAS_TANGENTS_AND_BITANGENTS;
	}
	for (unsigned int n = 0; n < AI_MAX_NUMBER_OF_TEXTURECOORDS;++n) {
		if (!mesh->mTextureCoords[n]) {
			break;
		}
		c |= ASSBIN_MESH_HAS_TEXCOORD(n);
	}
	for (unsigned int n = 0; n < AI_MAX_NUMBER_OF_COLOR_SETS;++n) {
		if (!mesh->mColors[n]) {
			break;
		}
		c |= ASSBIN_MESH_HAS_COLOR(n);
	}
	len += Write<unsigned int>(c);

	aiVector3D minVec, maxVec;
	if (mesh->mVertices) {
		if (shortened) {
			len += WriteBounds(mesh->mVertices,mesh->mNumVertices);
		} // else write as usual
		else len += static_cast<uint32_t>(fwrite(mesh->mVertices,1,12*mesh->mNumVertices,out));
	}
	if (mesh->mNormals) {
		if (shortened) {
			len += WriteBounds(mesh->mNormals,mesh->mNumVertices);
		} // else write as usual
		else len += static_cast<uint32_t>(fwrite(mesh->mNormals,1,12*mesh->mNumVertices,out));
	}
	if (mesh->mTangents && mesh->mBitangents) {
		if (shortened) {
			len += WriteBounds(mesh->mTangents,mesh->mNumVertices);
			len += WriteBounds(mesh->mBitangents,mesh->mNumVertices);
		} // else write as usual
		else {
			len += static_cast<uint32_t>(fwrite(mesh->mTangents,1,12*mesh->mNumVertices,out));
			len += static_cast<uint32_t>(fwrite(mesh->mBitangents,1,12*mesh->mNumVertices,out));
		}
	}
	for (unsigned int n = 0; n < AI_MAX_NUMBER_OF_COLOR_SETS;++n) {
		if (!mesh->mColors[n])
			break;

		if (shortened) {
			len += WriteBounds(mesh->mColors[n],mesh->mNumVertices);
		} // else write as usual
		else len += static_cast<uint32_t>(fwrite(mesh->mColors[n],16*mesh->mNumVertices,1,out));
	}
	for (unsigned int n = 0; n < AI_MAX_NUMBER_OF_TEXTURECOORDS;++n) {
		if (!mesh->mTextureCoords[n])
			break;

		// write number of UV components
		len += Write<unsigned int>(mesh->mNumUVComponents[n]);

		if (shortened) {
			len += WriteBounds(mesh->mTextureCoords[n],mesh->mNumVertices);
		} // else write as usual
		else len += static_cast<uint32_t>(fwrite(mesh->mTextureCoords[n],12*mesh->mNumVertices,1,out));
	}

	// write faces. There are no floating-point calculations involved
	// in these, so we can write a simple hash over the face data
	// to the dump file. We generate a single 32 Bit hash for 512 faces
	// using Assimp's standard hashing function.
	if (shortened) {
		unsigned int processed = 0;
		for (unsigned int job;(job = std::min(mesh->mNumFaces-processed,512u));processed += job) {

			uint32_t hash = 0;
			for (unsigned int a = 0; a < job;++a) {

				const aiFace& f = mesh->mFaces[processed+a];
				uint32_t tmp = f.mNumIndices;
				hash = SuperFastHash(reinterpret_cast<const char*>(&tmp),sizeof tmp,hash);
				for (unsigned int i = 0; i < f.mNumIndices; ++i) {
					static_assert(AI_MAX_VERTICES <= 0xffffffff, "AI_MAX_VERTICES <= 0xffffffff");
					tmp = static_cast<uint32_t>( f.mIndices[i] );
					hash = SuperFastHash(reinterpret_cast<const char*>(&tmp),sizeof tmp,hash);
				}
			}
			len += Write<unsigned int>(hash);
		}
	}
	else // else write as usual
	{
		// if there are less than 2^16 vertices, we can simply use 16 bit integers ...
		for (unsigned int i = 0; i < mesh->mNumFaces;++i) {
			const aiFace& f = mesh->mFaces[i];

			static_assert(AI_MAX_FACE_INDICES <= 0xffff, "AI_MAX_FACE_INDICES <= 0xffff");
			len += Write<uint16_t>(f.mNumIndices);

			for (unsigned int a = 0; a < f.mNumIndices;++a) {
				if (mesh->mNumVertices < (1u<<16)) {
					len += Write<uint16_t>(f.mIndices[a]);
				}
				else len += Write<unsigned int>(f.mIndices[a]);
			}
		}
	}

	// write bones
	if (mesh->mNumBones) {
		for (unsigned int a = 0; a < mesh->mNumBones;++a) {
			const aiBone* b = mesh->mBones[a];
			len += WriteBinaryBone(b)+8;
		}
	}

	ChangeInteger(old,len);
	return len;
}

// -----------------------------------------------------------------------------------
uint32_t WriteBinaryMaterialProperty(const aiMaterialProperty* prop)
{
	uint32_t len = 0, old = WriteMagic(ASSBIN_CHUNK_AIMATERIALPROPERTY);

	len += Write<aiString>(prop->mKey);
	len += Write<unsigned int>(prop->mSemantic);
	len += Write<unsigned int>(prop->mIndex);

	len += Write<unsigned int>(prop->mDataLength);
	len += Write<unsigned int>((unsigned int)prop->mType);
	len += static_cast<uint32_t>(fwrite(prop->mData,1,prop->mDataLength,out));

	ChangeInteger(old,len);
	return len;
}

// -----------------------------------------------------------------------------------
uint32_t WriteBinaryMaterial(const aiMaterial* mat)
{
	uint32_t len = 0, old = WriteMagic(ASSBIN_CHUNK_AIMATERIAL);

	len += Write<unsigned int>(mat->mNumProperties);
	for (unsigned int i = 0; i < mat->mNumProperties;++i) {
		len += WriteBinaryMaterialProperty(mat->mProperties[i])+8;
	}

	ChangeInteger(old,len);
	return len;
}

// -----------------------------------------------------------------------------------
uint32_t WriteBinaryNodeAnim(const aiNodeAnim* nd)
{
	uint32_t len = 0, old = WriteMagic(ASSBIN_CHUNK_AINODEANIM);

	len += Write<aiString>(nd->mNodeName);
	len += Write<unsigned int>(nd->mNumPositionKeys);
	len += Write<unsigned int>(nd->mNumRotationKeys);
	len += Write<unsigned int>(nd->mNumScalingKeys);
	len += Write<unsigned int>(nd->mPreState);
	len += Write<unsigned int>(nd->mPostState);

	if (nd->mPositionKeys) {
		if (shortened) {
			len += WriteBounds(nd->mPositionKeys,nd->mNumPositionKeys);

		} // else write as usual
		else len += static_cast<uint32_t>(fwrite(nd->mPositionKeys,1,nd->mNumPositionKeys*sizeof(aiVectorKey),out));
	}
	if (nd->mRotationKeys) {
		if (shortened) {
			len += WriteBounds(nd->mRotationKeys,nd->mNumRotationKeys);

		} // else write as usual
		else len += static_cast<uint32_t>(fwrite(nd->mRotationKeys,1,nd->mNumRotationKeys*sizeof(aiQuatKey),out));
	}
	if (nd->mScalingKeys) {
		if (shortened) {
			len += WriteBounds(nd->mScalingKeys,nd->mNumScalingKeys);

		} // else write as usual
		else len += static_cast<uint32_t>(fwrite(nd->mScalingKeys,1,nd->mNumScalingKeys*sizeof(aiVectorKey),out));
	}

	ChangeInteger(old,len);
	return len;
}


// -----------------------------------------------------------------------------------
uint32_t WriteBinaryAnim(const aiAnimation* anim)
{
	uint32_t len = 0, old = WriteMagic(ASSBIN_CHUNK_AIANIMATION);

	len += Write<aiString> (anim->mName);
	len += Write<double> (anim->mDuration);
	len += Write<double> (anim->mTicksPerSecond);
	len += Write<unsigned int>(anim->mNumChannels);

	for (unsigned int a = 0; a < anim->mNumChannels;++a) {
		const aiNodeAnim* nd = anim->mChannels[a];
		len += WriteBinaryNodeAnim(nd)+8;	
	}

	ChangeInteger(old,len);
	return len;
}

// -----------------------------------------------------------------------------------
uint32_t WriteBinaryLight(const aiLight* l)
{
	uint32_t len = 0, old = WriteMagic(ASSBIN_CHUNK_AILIGHT);

	len += Write<aiString>(l->mName);
	len += Write<unsigned int>(l->mType);

	if (l->mType != aiLightSource_DIRECTIONAL) { 
		len += Write<float>(l->mAttenuationConstant);
		len += Write<float>(l->mAttenuationLinear);
		len += Write<float>(l->mAttenuationQuadratic);
	}

	len += Write<aiVector3D>((const aiVector3D&)l->mColorDiffuse);
	len += Write<aiVector3D>((const aiVector3D&)l->mColorSpecular);
	len += Write<aiVector3D>((const aiVector3D&)l->mColorAmbient);

	if (l->mType == aiLightSource_SPOT) {
		len += Write<float>(l->mAngleInnerCone);
		len += Write<float>(l->mAngleOuterCone);
	}

	ChangeInteger(old,len);
	return len;
}

// -----------------------------------------------------------------------------------
uint32_t WriteBinaryCamera(const aiCamera* cam)
{
	uint32_t len = 0, old = WriteMagic(ASSBIN_CHUNK_AICAMERA);

	len += Write<aiString>(cam->mName);
	len += Write<aiVector3D>(cam->mPosition);
	len += Write<aiVector3D>(cam->mLookAt);
	len += Write<aiVector3D>(cam->mUp);
	len += Write<float>(cam->mHorizontalFOV);
	len += Write<float>(cam->mClipPlaneNear);
	len += Write<float>(cam->mClipPlaneFar);
	len += Write<float>(cam->mAspect);

	ChangeInteger(old,len);
	return len;
}

// -----------------------------------------------------------------------------------
uint32_t WriteBinaryScene(const aiScene* scene)
{
	uint32_t len = 0, old = WriteMagic(ASSBIN_CHUNK_AISCENE);

	// basic scene information
	len += Write<unsigned int>(scene->mFlags);
	len += Write<unsigned int>(scene->mNumMeshes);
	len += Write<unsigned int>(scene->mNumMaterials);
	len += Write<unsigned int>(scene->mNumAnimations);
	len += Write<unsigned int>(scene->mNumTextures);
	len += Write<unsigned int>(scene->mNumLights);
	len += Write<unsigned int>(scene->mNumCameras);
	
	// write node graph
	len += WriteBinaryNode(scene->mRootNode)+8;

	// write all meshes
	for (unsigned int i = 0; i < scene->mNumMeshes;++i) {
		const aiMesh* mesh = scene->mMeshes[i];
		len += WriteBinaryMesh(mesh)+8;
	}

	// write materials
	for (unsigned int i = 0; i< scene->mNumMaterials; ++i) {
		const aiMaterial* mat = scene->mMaterials[i];
		len += WriteBinaryMaterial(mat)+8;
	}

	// write all animations
	for (unsigned int i = 0; i < scene->mNumAnimations;++i) {
		const aiAnimation* anim = scene->mAnimations[i];
		len += WriteBinaryAnim(anim)+8;
	}


	// write all textures
	for (unsigned int i = 0; i < scene->mNumTextures;++i) {
		const aiTexture* mesh = scene->mTextures[i];
		len += WriteBinaryTexture(mesh)+8;
	}

	// write lights
	for (unsigned int i = 0; i < scene->mNumLights;++i) {
		const aiLight* l = scene->mLights[i];
		len += WriteBinaryLight(l)+8;
	}

	// write cameras
	for (unsigned int i = 0; i < scene->mNumCameras;++i) {
		const aiCamera* cam = scene->mCameras[i];
		len += WriteBinaryCamera(cam)+8;
	}

	ChangeInteger(old,len);
	return len;
}

// -----------------------------------------------------------------------------------
// Write a binary model dump
void WriteBinaryDump(const aiScene* scene, FILE* _out, const char* src, const char* cmd, 
	bool _shortened, bool compressed, ImportData& /*imp*/)
{
	out = _out;
	shortened = _shortened;

	time_t tt = time(NULL);
	tm* p     = gmtime(&tt);

	// header
	fprintf(out,"ASSIMP.binary-dump.%s",asctime(p));
	// == 44 bytes

	Write<unsigned int>(ASSBIN_VERSION_MAJOR);
	Write<unsigned int>(ASSBIN_VERSION_MINOR);
	Write<unsigned int>(aiGetVersionRevision());
	Write<unsigned int>(aiGetCompileFlags());
	Write<uint16_t>(shortened);
	Write<uint16_t>(compressed);
	// ==  20 bytes

	{
		char buff[256] = { 0 };
		strncpy(buff,src,256);
		buff[255] = 0;
		fwrite(buff,256,1,out);
	}

	{
		char buff[128] = { 0 };
		strncpy(buff,cmd,128);
		buff[127] = 0;
		fwrite(buff,128,1,out);
	}

	// leave 64 bytes free for future extensions
	{
		char buff[64];
		memset(buff,0xcd,64);
		fwrite(buff,64,1,out);
	}
	// == 435 bytes

	// ==== total header size: 512 bytes
	ai_assert(ftell(out)==ASSBIN_HEADER_LENGTH);

	// Up to here the data is uncompressed. For compressed files, the rest
	// is compressed using standard DEFLATE from zlib.
	WriteBinaryScene(scene);
}

// -----------------------------------------------------------------------------------
// Convert a name to standard XML format
void ConvertName(aiString& out, const aiString& in)
{
	out.length = 0;
	for (unsigned int i = 0; i < in.length; ++i)  {
		switch (in.data[i]) {
			case '<':
				out.Append("&lt;");break;
			case '>':
				out.Append("&gt;");break;
			case '&':
				out.Append("&amp;");break;
			case '\"':
				out.Append("&quot;");break;
			case '\'':
				out.Append("&apos;");break;
			default:
				out.data[out.length++] = in.data[i];
		}
	}
	out.data[out.length] = 0;
}

// -----------------------------------------------------------------------------------
// Write a single node as text dump
void WriteNode(const aiNode* node, FILE* out, unsigned int depth)
{
	char prefix[512];
	for (unsigned int i = 0; i < depth;++i)
		prefix[i] = '\t';
	prefix[depth] = '\0';

	const aiMatrix4x4& m = node->mTransformation;

	aiString name;
	ConvertName(name,node->mName);
	fprintf(out,"%s<Node name=\"%s\"> \n"
		"%s\t<Matrix4> \n"
		"%s\t\t%0 6f %0 6f %0 6f %0 6f\n"
		"%s\t\t%0 6f %0 6f %0 6f %0 6f\n"
		"%s\t\t%0 6f %0 6f %0 6f %0 6f\n"
		"%s\t\t%0 6f %0 6f %0 6f %0 6f\n"
		"%s\t</Matrix4> \n",
		prefix,name.data,prefix,
		prefix,m.a1,m.a2,m.a3,m.a4,
		prefix,m.b1,m.b2,m.b3,m.b4,
		prefix,m.c1,m.c2,m.c3,m.c4,
		prefix,m.d1,m.d2,m.d3,m.d4,prefix);

	if (node->mNumMeshes) {
		fprintf(out, "%s\t<MeshRefs num=\"%u\">\n%s\t",
			prefix,node->mNumMeshes,prefix);

		for (unsigned int i = 0; i < node->mNumMeshes;++i) {
			fprintf(out,"%u ",node->mMeshes[i]);
		}
		fprintf(out,"\n%s\t</MeshRefs>\n",prefix);
	}

	if (node->mNumChildren) {
		fprintf(out,"%s\t<NodeList num=\"%u\">\n",
			prefix,node->mNumChildren);

		for (unsigned int i = 0; i < node->mNumChildren;++i) {
			WriteNode(node->mChildren[i],out,depth+2);
		}
		fprintf(out,"%s\t</NodeList>\n",prefix);
	}
	fprintf(out,"%s</Node>\n",prefix);
}


// -------------------------------------------------------------------------------
const char* TextureTypeToString(aiTextureType in)
{
	switch (in)
	{
	case aiTextureType_NONE:
		return "n/a";
	case aiTextureType_DIFFUSE:
		return "Diffuse";
	case aiTextureType_SPECULAR:
		return "Specular";
	case aiTextureType_AMBIENT:
		return "Ambient";
	case aiTextureType_EMISSIVE:
		return "Emissive";
	case aiTextureType_OPACITY:
		return "Opacity";
	case aiTextureType_NORMALS:
		return "Normals";
	case aiTextureType_HEIGHT:
		return "Height";
	case aiTextureType_SHININESS:
		return "Shininess";
	case aiTextureType_DISPLACEMENT:
		return "Displacement";
	case aiTextureType_LIGHTMAP:
		return "Lightmap";
	case aiTextureType_REFLECTION:
		return "Reflection";
	case aiTextureType_UNKNOWN:
		return "Unknown";
	default:
		break;
	}
	ai_assert(false); 
	return  "BUG";    
}


// -----------------------------------------------------------------------------------
// Some chuncks of text will need to be encoded for XML
// http://stackoverflow.com/questions/5665231/most-efficient-way-to-escape-xml-html-in-c-string#5665377
static std::string encodeXML(const std::string& data) {
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        switch(data[pos]) {
            case '&':  buffer.append("&amp;");       break;
            case '\"': buffer.append("&quot;");      break;
            case '\'': buffer.append("&apos;");      break;
            case '<':  buffer.append("&lt;");        break;
            case '>':  buffer.append("&gt;");        break;
            default:   buffer.append(&data[pos], 1); break;
        }
    }
    return buffer;
}



// -----------------------------------------------------------------------------------
// Write a text model dump
void WriteDump(const aiScene* scene, FILE* out, const char* src, const char* cmd, bool shortened)
{
	time_t tt = ::time(NULL);
	tm* p     = ::gmtime(&tt);

	std::string c = cmd;
	std::string::size_type s; 

	// https://sourceforge.net/tracker/?func=detail&aid=3167364&group_id=226462&atid=1067632
	// -- not allowed in XML comments
	while((s = c.find("--")) != std::string::npos) {
		c[s] = '?';
	}
	aiString name;

	// write header
	fprintf(out,
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
		"<ASSIMP format_id=\"1\">\n\n"

		"<!-- XML Model dump produced by assimp dump\n"
		"  Library version: %u.%u.%u\n"
		"  Source: %s\n"
		"  Command line: %s\n"
		"  %s\n"
		"-->"
		" \n\n"
		"<Scene flags=\"%u\" postprocessing=\"%i\">\n",
		
		aiGetVersionMajor(),aiGetVersionMinor(),aiGetVersionRevision(),src,c.c_str(),asctime(p),
		scene->mFlags,
		0 /*globalImporter->GetEffectivePostProcessing()*/);

	// write the node graph
	WriteNode(scene->mRootNode, out, 0);

#if 0
		// write cameras
	for (unsigned int i = 0; i < scene->mNumCameras;++i) {
		aiCamera* cam  = scene->mCameras[i];
		ConvertName(name,cam->mName);

		// camera header
		fprintf(out,"\t<Camera parent=\"%s\">\n"
			"\t\t<Vector3 name=\"up\"        > %0 8f %0 8f %0 8f </Vector3>\n"
			"\t\t<Vector3 name=\"lookat\"    > %0 8f %0 8f %0 8f </Vector3>\n"
			"\t\t<Vector3 name=\"pos\"       > %0 8f %0 8f %0 8f </Vector3>\n"
			"\t\t<Float   name=\"fov\"       > %f </Float>\n"
			"\t\t<Float   name=\"aspect\"    > %f </Float>\n"
			"\t\t<Float   name=\"near_clip\" > %f </Float>\n"
			"\t\t<Float   name=\"far_clip\"  > %f </Float>\n"
			"\t</Camera>\n",
			name.data,
			cam->mUp.x,cam->mUp.y,cam->mUp.z,
			cam->mLookAt.x,cam->mLookAt.y,cam->mLookAt.z,
			cam->mPosition.x,cam->mPosition.y,cam->mPosition.z,
			cam->mHorizontalFOV,cam->mAspect,cam->mClipPlaneNear,cam->mClipPlaneFar,i);
	}

	// write lights
	for (unsigned int i = 0; i < scene->mNumLights;++i) {
		aiLight* l  = scene->mLights[i];
		ConvertName(name,l->mName);

		// light header
		fprintf(out,"\t<Light parent=\"%s\"> type=\"%s\"\n"
			"\t\t<Vector3 name=\"diffuse\"   > %0 8f %0 8f %0 8f </Vector3>\n"
			"\t\t<Vector3 name=\"specular\"  > %0 8f %0 8f %0 8f </Vector3>\n"
			"\t\t<Vector3 name=\"ambient\"   > %0 8f %0 8f %0 8f </Vector3>\n",
			name.data,
			(l->mType == aiLightSource_DIRECTIONAL ? "directional" :
			(l->mType == aiLightSource_POINT ? "point" : "spot" )),
			l->mColorDiffuse.r, l->mColorDiffuse.g, l->mColorDiffuse.b,
			l->mColorSpecular.r,l->mColorSpecular.g,l->mColorSpecular.b,
			l->mColorAmbient.r, l->mColorAmbient.g, l->mColorAmbient.b);

		if (l->mType != aiLightSource_DIRECTIONAL) {
			fprintf(out,
				"\t\t<Vector3 name=\"pos\"       > %0 8f %0 8f %0 8f </Vector3>\n"
				"\t\t<Float   name=\"atten_cst\" > %f </Float>\n"
				"\t\t<Float   name=\"atten_lin\" > %f </Float>\n"
				"\t\t<Float   name=\"atten_sqr\" > %f </Float>\n",
				l->mPosition.x,l->mPosition.y,l->mPosition.z,
				l->mAttenuationConstant,l->mAttenuationLinear,l->mAttenuationQuadratic);
		}

		if (l->mType != aiLightSource_POINT) {
			fprintf(out,
				"\t\t<Vector3 name=\"lookat\"    > %0 8f %0 8f %0 8f </Vector3>\n",
				l->mDirection.x,l->mDirection.y,l->mDirection.z);
		}

		if (l->mType == aiLightSource_SPOT) {
			fprintf(out,
				"\t\t<Float   name=\"cone_out\" > %f </Float>\n"
				"\t\t<Float   name=\"cone_inn\" > %f </Float>\n",
				l->mAngleOuterCone,l->mAngleInnerCone);
		}
		fprintf(out,"\t</Light>\n");
	}
#endif

	// write textures
	if (scene->mNumTextures) {
		fprintf(out,"<TextureList num=\"%u\">\n",scene->mNumTextures);
		for (unsigned int i = 0; i < scene->mNumTextures;++i) {
			aiTexture* tex  = scene->mTextures[i];
			bool compressed = (tex->mHeight == 0);

			// mesh header
			fprintf(out,"\t<Texture width=\"%i\" height=\"%i\" compressed=\"%s\"> \n",
				(compressed ? -1 : tex->mWidth),(compressed ? -1 : tex->mHeight),
				(compressed ? "true" : "false"));

			if (compressed) {
				fprintf(out,"\t\t<Data length=\"%u\"> \n",tex->mWidth);

				if (!shortened) {
					for (unsigned int n = 0; n < tex->mWidth;++n) {
						fprintf(out,"\t\t\t%2x",reinterpret_cast<uint8_t*>(tex->pcData)[n]);
						if (n && !(n % 50)) {
							fprintf(out,"\n");
						}
					}
				}
			}
			else if (!shortened){
				fprintf(out,"\t\t<Data length=\"%i\"> \n",tex->mWidth*tex->mHeight*4);

				// const unsigned int width = (unsigned int)log10((double)std::max(tex->mHeight,tex->mWidth))+1;
				for (unsigned int y = 0; y < tex->mHeight;++y) {
					for (unsigned int x = 0; x < tex->mWidth;++x) {
						aiTexel* tx = tex->pcData + y*tex->mWidth+x;
						unsigned int r = tx->r,g=tx->g,b=tx->b,a=tx->a;
						fprintf(out,"\t\t\t%2x %2x %2x %2x",r,g,b,a);

						// group by four for readibility
						if (0 == (x+y*tex->mWidth) % 4)
							fprintf(out,"\n");
					}
				}
			}
			fprintf(out,"\t\t</Data>\n\t</Texture>\n");
		}
		fprintf(out,"</TextureList>\n");
	}

	// write materials
	if (scene->mNumMaterials) {
		fprintf(out,"<MaterialList num=\"%u\">\n",scene->mNumMaterials);
		for (unsigned int i = 0; i< scene->mNumMaterials; ++i) {
			const aiMaterial* mat = scene->mMaterials[i];

			fprintf(out,"\t<Material>\n");
			fprintf(out,"\t\t<MatPropertyList  num=\"%u\">\n",mat->mNumProperties);
			for (unsigned int n = 0; n < mat->mNumProperties;++n) {

				const aiMaterialProperty* prop = mat->mProperties[n];
				const char* sz = "";
				if (prop->mType == aiPTI_Float) {
					sz = "float";
				}
				else if (prop->mType == aiPTI_Integer) {
					sz = "integer";
				}
				else if (prop->mType == aiPTI_String) {
					sz = "string";
				}
				else if (prop->mType == aiPTI_Buffer) {
					sz = "binary_buffer";
				}

				fprintf(out,"\t\t\t<MatProperty key=\"%s\" \n\t\t\ttype=\"%s\" tex_usage=\"%s\" tex_index=\"%u\"",
					prop->mKey.data, sz,
					::TextureTypeToString((aiTextureType)prop->mSemantic),prop->mIndex);

				if (prop->mType == aiPTI_Float) {
					fprintf(out," size=\"%i\">\n\t\t\t\t",
						static_cast<int>(prop->mDataLength/sizeof(float)));

					for (unsigned int p = 0; p < prop->mDataLength/sizeof(float);++p) {
						fprintf(out,"%f ",*((float*)(prop->mData+p*sizeof(float))));
					}
				}
				else if (prop->mType == aiPTI_Integer) {
					fprintf(out," size=\"%i\">\n\t\t\t\t",
						static_cast<int>(prop->mDataLength/sizeof(int)));

					for (unsigned int p = 0; p < prop->mDataLength/sizeof(int);++p) {
						fprintf(out,"%i ",*((int*)(prop->mData+p*sizeof(int))));
					}
				}
				else if (prop->mType == aiPTI_Buffer) {
					fprintf(out," size=\"%i\">\n\t\t\t\t",
						static_cast<int>(prop->mDataLength));

					for (unsigned int p = 0; p < prop->mDataLength;++p) {
						fprintf(out,"%2x ",prop->mData[p]);
						if (p && 0 == p%30) {
							fprintf(out,"\n\t\t\t\t");
						}
					}
				}
				else if (prop->mType == aiPTI_String) {
					fprintf(out,">\n\t\t\t\t\"%s\"",encodeXML(prop->mData+4).c_str() /* skip length */);
				}
				fprintf(out,"\n\t\t\t</MatProperty>\n");
			}
			fprintf(out,"\t\t</MatPropertyList>\n");
			fprintf(out,"\t</Material>\n");
		}
		fprintf(out,"</MaterialList>\n");
	}

	// write animations
	if (scene->mNumAnimations) {
		fprintf(out,"<AnimationList num=\"%u\">\n",scene->mNumAnimations);
		for (unsigned int i = 0; i < scene->mNumAnimations;++i) {
			aiAnimation* anim = scene->mAnimations[i];

			// anim header
			ConvertName(name,anim->mName);
			fprintf(out,"\t<Animation name=\"%s\" duration=\"%e\" tick_cnt=\"%e\">\n",
				name.data, anim->mDuration, anim->mTicksPerSecond);

			// write bone animation channels
			if (anim->mNumChannels) {
				fprintf(out,"\t\t<NodeAnimList num=\"%u\">\n",anim->mNumChannels);
				for (unsigned int n = 0; n < anim->mNumChannels;++n) {
					aiNodeAnim* nd = anim->mChannels[n];

					// node anim header
					ConvertName(name,nd->mNodeName);
					fprintf(out,"\t\t\t<NodeAnim node=\"%s\">\n",name.data);

					if (!shortened) {
						// write position keys
						if (nd->mNumPositionKeys) {
							fprintf(out,"\t\t\t\t<PositionKeyList num=\"%u\">\n",nd->mNumPositionKeys);
							for (unsigned int a = 0; a < nd->mNumPositionKeys;++a) {
								aiVectorKey* vc = nd->mPositionKeys+a;
								fprintf(out,"\t\t\t\t\t<PositionKey time=\"%e\">\n"
									"\t\t\t\t\t\t%0 8f %0 8f %0 8f\n\t\t\t\t\t</PositionKey>\n",
									vc->mTime,vc->mValue.x,vc->mValue.y,vc->mValue.z);
							}
							fprintf(out,"\t\t\t\t</PositionKeyList>\n");
						}

						// write scaling keys
						if (nd->mNumScalingKeys) {
							fprintf(out,"\t\t\t\t<ScalingKeyList num=\"%u\">\n",nd->mNumScalingKeys);
							for (unsigned int a = 0; a < nd->mNumScalingKeys;++a) {
								aiVectorKey* vc = nd->mScalingKeys+a;
								fprintf(out,"\t\t\t\t\t<ScalingKey time=\"%e\">\n"
									"\t\t\t\t\t\t%0 8f %0 8f %0 8f\n\t\t\t\t\t</ScalingKey>\n",
									vc->mTime,vc->mValue.x,vc->mValue.y,vc->mValue.z);
							}
							fprintf(out,"\t\t\t\t</ScalingKeyList>\n");
						}

						// write rotation keys
						if (nd->mNumRotationKeys) {
							fprintf(out,"\t\t\t\t<RotationKeyList num=\"%u\">\n",nd->mNumRotationKeys);
							for (unsigned int a = 0; a < nd->mNumRotationKeys;++a) {
								aiQuatKey* vc = nd->mRotationKeys+a;
								fprintf(out,"\t\t\t\t\t<RotationKey time=\"%e\">\n"
									"\t\t\t\t\t\t%0 8f %0 8f %0 8f %0 8f\n\t\t\t\t\t</RotationKey>\n",
									vc->mTime,vc->mValue.x,vc->mValue.y,vc->mValue.z,vc->mValue.w);
							}
							fprintf(out,"\t\t\t\t</RotationKeyList>\n");
						}
					}
					fprintf(out,"\t\t\t</NodeAnim>\n");
				}
				fprintf(out,"\t\t</NodeAnimList>\n");
			}
			fprintf(out,"\t</Animation>\n");
		}
		fprintf(out,"</AnimationList>\n");
	}

	// write meshes
	if (scene->mNumMeshes) {
		fprintf(out,"<MeshList num=\"%u\">\n",scene->mNumMeshes);
		for (unsigned int i = 0; i < scene->mNumMeshes;++i) {
			aiMesh* mesh = scene->mMeshes[i];
			// const unsigned int width = (unsigned int)log10((double)mesh->mNumVertices)+1;

			// mesh header
			fprintf(out,"\t<Mesh types=\"%s %s %s %s\" material_index=\"%u\">\n",
				(mesh->mPrimitiveTypes & aiPrimitiveType_POINT    ? "points"    : ""),
				(mesh->mPrimitiveTypes & aiPrimitiveType_LINE     ? "lines"     : ""),
				(mesh->mPrimitiveTypes & aiPrimitiveType_TRIANGLE ? "triangles" : ""),
				(mesh->mPrimitiveTypes & aiPrimitiveType_POLYGON  ? "polygons"  : ""),
				mesh->mMaterialIndex);

			// bones
			if (mesh->mNumBones) {
				fprintf(out,"\t\t<BoneList num=\"%u\">\n",mesh->mNumBones);

				for (unsigned int n = 0; n < mesh->mNumBones;++n) {
					aiBone* bone = mesh->mBones[n];

					ConvertName(name,bone->mName);
					// bone header
					fprintf(out,"\t\t\t<Bone name=\"%s\">\n"
						"\t\t\t\t<Matrix4> \n"
						"\t\t\t\t\t%0 6f %0 6f %0 6f %0 6f\n"
						"\t\t\t\t\t%0 6f %0 6f %0 6f %0 6f\n"
						"\t\t\t\t\t%0 6f %0 6f %0 6f %0 6f\n"
						"\t\t\t\t\t%0 6f %0 6f %0 6f %0 6f\n"
						"\t\t\t\t</Matrix4> \n",
						name.data,
						bone->mOffsetMatrix.a1,bone->mOffsetMatrix.a2,bone->mOffsetMatrix.a3,bone->mOffsetMatrix.a4,
						bone->mOffsetMatrix.b1,bone->mOffsetMatrix.b2,bone->mOffsetMatrix.b3,bone->mOffsetMatrix.b4,
						bone->mOffsetMatrix.c1,bone->mOffsetMatrix.c2,bone->mOffsetMatrix.c3,bone->mOffsetMatrix.c4,
						bone->mOffsetMatrix.d1,bone->mOffsetMatrix.d2,bone->mOffsetMatrix.d3,bone->mOffsetMatrix.d4);

					if (!shortened && bone->mNumWeights) {
						fprintf(out,"\t\t\t\t<WeightList num=\"%u\">\n",bone->mNumWeights);

						// bone weights
						for (unsigned int a = 0; a < bone->mNumWeights;++a) {
							aiVertexWeight* wght = bone->mWeights+a;

							fprintf(out,"\t\t\t\t\t<Weight index=\"%u\">\n\t\t\t\t\t\t%f\n\t\t\t\t\t</Weight>\n",
								wght->mVertexId,wght->mWeight);
						}
						fprintf(out,"\t\t\t\t</WeightList>\n");
					}
					fprintf(out,"\t\t\t</Bone>\n");
				}
				fprintf(out,"\t\t</BoneList>\n");
			}

			// faces
			if (!shortened && mesh->mNumFaces) {
				fprintf(out,"\t\t<FaceList num=\"%u\">\n",mesh->mNumFaces);
				for (unsigned int n = 0; n < mesh->mNumFaces; ++n) {
					aiFace& f = mesh->mFaces[n];
					fprintf(out,"\t\t\t<Face num=\"%u\">\n"
						"\t\t\t\t",f.mNumIndices);

					for (unsigned int j = 0; j < f.mNumIndices;++j)
						fprintf(out,"%u ",f.mIndices[j]);

					fprintf(out,"\n\t\t\t</Face>\n");
				}
				fprintf(out,"\t\t</FaceList>\n");
			}

			// vertex positions
			if (mesh->HasPositions()) {
				fprintf(out,"\t\t<Positions num=\"%u\" set=\"0\" num_components=\"3\"> \n",mesh->mNumVertices);
				if (!shortened) {
					for (unsigned int n = 0; n < mesh->mNumVertices; ++n) {
						fprintf(out,"\t\t%0 8f %0 8f %0 8f\n",
							mesh->mVertices[n].x,
							mesh->mVertices[n].y,
							mesh->mVertices[n].z);
					}
				}
				fprintf(out,"\t\t</Positions>\n");
			}

			// vertex normals
			if (mesh->HasNormals()) {
				fprintf(out,"\t\t<Normals num=\"%u\" set=\"0\" num_components=\"3\"> \n",mesh->mNumVertices);
				if (!shortened) {
					for (unsigned int n = 0; n < mesh->mNumVertices; ++n) {
						fprintf(out,"\t\t%0 8f %0 8f %0 8f\n",
							mesh->mNormals[n].x,
							mesh->mNormals[n].y,
							mesh->mNormals[n].z);
					}
				}
				else {
				}
				fprintf(out,"\t\t</Normals>\n");
			}

			// vertex tangents and bitangents
			if (mesh->HasTangentsAndBitangents()) {
				fprintf(out,"\t\t<Tangents num=\"%u\" set=\"0\" num_components=\"3\"> \n",mesh->mNumVertices);
				if (!shortened) {
					for (unsigned int n = 0; n < mesh->mNumVertices; ++n) {
						fprintf(out,"\t\t%0 8f %0 8f %0 8f\n",
							mesh->mTangents[n].x,
							mesh->mTangents[n].y,
							mesh->mTangents[n].z);
					}
				}
				fprintf(out,"\t\t</Tangents>\n");

				fprintf(out,"\t\t<Bitangents num=\"%u\" set=\"0\" num_components=\"3\"> \n",mesh->mNumVertices);
				if (!shortened) {
					for (unsigned int n = 0; n < mesh->mNumVertices; ++n) {
						fprintf(out,"\t\t%0 8f %0 8f %0 8f\n",
							mesh->mBitangents[n].x,
							mesh->mBitangents[n].y,
							mesh->mBitangents[n].z);
					}
				}
				fprintf(out,"\t\t</Bitangents>\n");
			}

			// texture coordinates
			for (unsigned int a = 0; a < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++a) {
				if (!mesh->mTextureCoords[a])
					break;

				fprintf(out,"\t\t<TextureCoords num=\"%u\" set=\"%u\" num_components=\"%u\"> \n",mesh->mNumVertices,
					a,mesh->mNumUVComponents[a]);
				
				if (!shortened) {
					if (mesh->mNumUVComponents[a] == 3) {
						for (unsigned int n = 0; n < mesh->mNumVertices; ++n) {
							fprintf(out,"\t\t%0 8f %0 8f %0 8f\n",
								mesh->mTextureCoords[a][n].x,
								mesh->mTextureCoords[a][n].y,
								mesh->mTextureCoords[a][n].z);
						}
					}
					else {
						for (unsigned int n = 0; n < mesh->mNumVertices; ++n) {
							fprintf(out,"\t\t%0 8f %0 8f\n",
								mesh->mTextureCoords[a][n].x,
								mesh->mTextureCoords[a][n].y);
						}
					}
				}
				fprintf(out,"\t\t</TextureCoords>\n");
			}

			// vertex colors
			for (unsigned int a = 0; a < AI_MAX_NUMBER_OF_COLOR_SETS; ++a) {
				if (!mesh->mColors[a])
					break;
				fprintf(out,"\t\t<Colors num=\"%u\" set=\"%u\" num_components=\"4\"> \n",mesh->mNumVertices,a);
				if (!shortened) {
					for (unsigned int n = 0; n < mesh->mNumVertices; ++n) {
						fprintf(out,"\t\t%0 8f %0 8f %0 8f %0 8f\n",
							mesh->mColors[a][n].r,
							mesh->mColors[a][n].g,
							mesh->mColors[a][n].b,
							mesh->mColors[a][n].a);
					}
				}
				fprintf(out,"\t\t</Colors>\n");
			}
			fprintf(out,"\t</Mesh>\n");
		}
		fprintf(out,"</MeshList>\n");
	}
	fprintf(out,"</Scene>\n</ASSIMP>");
}


// -----------------------------------------------------------------------------------
int Assimp_Dump (const char* const* params, unsigned int num)
{
	const char* fail = "assimp dump: Invalid number of arguments. "
			"See \'assimp dump --help\'\r\n";
	if (num < 1) {
		printf("%s", fail);
		return 1;
	}

	// --help
	if (!strcmp( params[0], "-h") || !strcmp( params[0], "--help") || !strcmp( params[0], "-?") ) {
		printf("%s",AICMD_MSG_DUMP_HELP);
		return 0;
	}

	// asssimp dump in out [options]
	if (num < 1) {
		printf("%s", fail);
		return 1;
	}

	std::string in  = std::string(params[0]);
	std::string out = (num > 1 ? std::string(params[1]) : std::string("-"));

	// store full command line
	std::string cmd;
	for (unsigned int i = (out[0] == '-' ? 1 : 2); i < num;++i)	{
		if (!params[i])continue;
		cmd.append(params[i]);
		cmd.append(" ");
	}

	// get import flags
	ImportData import;
	ProcessStandardArguments(import,params+1,num-1);

	bool binary = false, shortened = false,compressed=false;
	
	// process other flags
	for (unsigned int i = 1; i < num;++i)		{
		if (!params[i])continue;
		if (!strcmp( params[i], "-b") || !strcmp( params[i], "--binary")) {
			binary = true;
		}
		else if (!strcmp( params[i], "-s") || !strcmp( params[i], "--short")) {
			shortened = true;
		}
		else if (!strcmp( params[i], "-z") || !strcmp( params[i], "--compressed")) {
			compressed = true;
		}
#if 0
		else if (i > 2 || params[i][0] == '-') {
			::printf("Unknown parameter: %s\n",params[i]);
			return 10;
		}
#endif
	}

	if (out[0] == '-') {
		// take file name from input file
		std::string::size_type s = in.find_last_of('.');
		if (s == std::string::npos) {
			s = in.length();
		}

		out = in.substr(0,s);
		out.append((binary ? ".assbin" : ".assxml"));
		if (shortened && binary) {
			out.append(".regress");
		}
	}

	// import the main model
	const aiScene* scene = ImportModel(import,in);
	if (!scene) {
		printf("assimp dump: Unable to load input file %s\n",in.c_str());
		return 5;
	}

	// open the output file and build the dump
	FILE* o = ::fopen(out.c_str(),(binary ? "wb" : "wt"));
	if (!o) {
		printf("assimp dump: Unable to open output file %s\n",out.c_str());
		return 12;
	}

	if (binary) {
		WriteBinaryDump (scene,o,in.c_str(),cmd.c_str(),shortened,compressed,import);
	}
	else WriteDump (scene,o,in.c_str(),cmd.c_str(),shortened);
	fclose(o);

	if (compressed && binary) {
		CompressBinaryDump(out.c_str(),ASSBIN_HEADER_LENGTH);
	}

	printf("assimp dump: Wrote output dump %s\n",out.c_str());
	return 0;
}

