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

/** @file  Info.cpp
 *  @brief Implementation of the 'assimp info' utility  */

#include "Main.h"

const char* AICMD_MSG_INFO_HELP_E =
"assimp info <file> [-r]\n"
"\tPrint basic structure of a 3D model\n"
"\t-r,--raw: No postprocessing, do a raw import\n";


// -----------------------------------------------------------------------------------
unsigned int CountNodes(const aiNode* root)
{
	unsigned int i = 0;
	for (unsigned int a = 0; a < root->mNumChildren; ++a ) {
		i += CountNodes(root->mChildren[a]);
	}
	return 1+i;
}

// -----------------------------------------------------------------------------------
unsigned int GetMaxDepth(const aiNode* root)
{
	unsigned int cnt = 0;
	for (unsigned int i = 0; i < root->mNumChildren; ++i ) {
		cnt = std::max(cnt,GetMaxDepth(root->mChildren[i]));
	}
	return cnt+1;
}

// -----------------------------------------------------------------------------------
unsigned int CountVertices(const aiScene* scene)
{
	unsigned int cnt = 0;
	for(unsigned int i = 0; i < scene->mNumMeshes; ++i) {
		cnt += scene->mMeshes[i]->mNumVertices;
	}
	return cnt;
}

// -----------------------------------------------------------------------------------
unsigned int CountFaces(const aiScene* scene)
{
	unsigned int cnt = 0;
	for(unsigned int i = 0; i < scene->mNumMeshes; ++i) {
		cnt += scene->mMeshes[i]->mNumFaces;
	}
	return cnt;
}

// -----------------------------------------------------------------------------------
unsigned int CountBones(const aiScene* scene)
{
	unsigned int cnt = 0;
	for(unsigned int i = 0; i < scene->mNumMeshes; ++i) {
		cnt += scene->mMeshes[i]->mNumBones;
	}
	return cnt;
}

// -----------------------------------------------------------------------------------
unsigned int CountAnimChannels(const aiScene* scene)
{
	unsigned int cnt = 0;
	for(unsigned int i = 0; i < scene->mNumAnimations; ++i) {
		cnt += scene->mAnimations[i]->mNumChannels;
	}
	return cnt;
}

// -----------------------------------------------------------------------------------
unsigned int GetAvgFacePerMesh(const aiScene* scene) {
	return (scene->mNumMeshes != 0) ? static_cast<unsigned int>(CountFaces(scene)/scene->mNumMeshes) : 0;
}

// -----------------------------------------------------------------------------------
unsigned int GetAvgVertsPerMesh(const aiScene* scene) {
	return (scene->mNumMeshes != 0) ? static_cast<unsigned int>(CountVertices(scene)/scene->mNumMeshes) : 0;
}

// -----------------------------------------------------------------------------------
void FindSpecialPoints(const aiScene* scene,const aiNode* root,aiVector3D special_points[3],const aiMatrix4x4& mat=aiMatrix4x4())
{
	// XXX that could be greatly simplified by using code from code/ProcessHelper.h
	// XXX I just don't want to include it here.
	const aiMatrix4x4 trafo = root->mTransformation*mat;
	for(unsigned int i = 0; i < root->mNumMeshes; ++i) {
		const aiMesh* mesh = scene->mMeshes[root->mMeshes[i]];

		for(unsigned int a = 0; a < mesh->mNumVertices; ++a) {
			aiVector3D v = trafo*mesh->mVertices[a];

			special_points[0].x = std::min(special_points[0].x,v.x);
			special_points[0].y = std::min(special_points[0].y,v.y);
			special_points[0].z = std::min(special_points[0].z,v.z);

			special_points[1].x = std::max(special_points[1].x,v.x);
			special_points[1].y = std::max(special_points[1].y,v.y);
			special_points[1].z = std::max(special_points[1].z,v.z);
		}
	}

	for(unsigned int i = 0; i < root->mNumChildren; ++i) {
		FindSpecialPoints(scene,root->mChildren[i],special_points,trafo);
	}
}

// -----------------------------------------------------------------------------------
void FindSpecialPoints(const aiScene* scene,aiVector3D special_points[3])
{
	special_points[0] = aiVector3D(1e10,1e10,1e10);
	special_points[1] = aiVector3D(-1e10,-1e10,-1e10);

	FindSpecialPoints(scene,scene->mRootNode,special_points);
	special_points[2] = (special_points[0]+special_points[1])*(ai_real)0.5;
}

// -----------------------------------------------------------------------------------
std::string FindPTypes(const aiScene* scene)
{
	bool haveit[4] = {0};
	for(unsigned int i = 0; i < scene->mNumMeshes; ++i) {
		const unsigned int pt = scene->mMeshes[i]->mPrimitiveTypes;
		if (pt & aiPrimitiveType_POINT) {
			haveit[0]=true;
		}
		if (pt & aiPrimitiveType_LINE) {
			haveit[1]=true;
		}
		if (pt & aiPrimitiveType_TRIANGLE) {
			haveit[2]=true;
		}
		if (pt & aiPrimitiveType_POLYGON) {
			haveit[3]=true;
		}
	}
	return (haveit[0]?std::string("points"):"")+(haveit[1]?"lines":"")+
		(haveit[2]?"triangles":"")+(haveit[3]?"n-polygons":"");
}

// -----------------------------------------------------------------------------------
void PrintHierarchy(const aiNode* root, unsigned int maxnest, unsigned int maxline,
					unsigned int cline, unsigned int cnest=0)
{
	if (cline++ >= maxline || cnest >= maxnest) {
		return;
	}

	for(unsigned int i = 0; i < cnest; ++i) {
		printf("-- ");
	}
	printf("\'%s\', meshes: %u\n",root->mName.data,root->mNumMeshes);
	for (unsigned int i = 0; i < root->mNumChildren; ++i ) {
		PrintHierarchy(root->mChildren[i],maxnest,maxline,cline,cnest+1);
		if(i == root->mNumChildren-1) {
			for(unsigned int i = 0; i < cnest; ++i) {
				printf("   ");
			}
			printf("<--\n");
		}
	}
}

// -----------------------------------------------------------------------------------
// Implementation of the assimp info utility to print basic file info
int Assimp_Info (const char* const* params, unsigned int num)
{
	if (num < 1) {
		printf("assimp info: Invalid number of arguments. "
			"See \'assimp info --help\'\n");
		return 1;
	}

	// --help
	if (!strcmp( params[0],"-h")||!strcmp( params[0],"--help")||!strcmp( params[0],"-?") ) {
		printf("%s",AICMD_MSG_INFO_HELP_E);
		return 0;
	}

	// asssimp info <file> [-r]
	if (num < 1) {
		printf("assimp info: Invalid number of arguments. "
			"See \'assimp info --help\'\n");
		return 1;
	}

	const std::string in  = std::string(params[0]);

	// do maximum post-processing unless -r was specified
	ImportData import;
	import.ppFlags = num>1&&(!strcmp(params[1],"--raw")||!strcmp(params[1],"-r")) ? 0
		: aiProcessPreset_TargetRealtime_MaxQuality;

	// import the main model
	const aiScene* scene = ImportModel(import,in);
	if (!scene) {
		printf("assimp info: Unable to load input file %s\n",
			in.c_str());
		return 5;
	}

	aiMemoryInfo mem;
	globalImporter->GetMemoryRequirements(mem);


	static const char* format_string =
		"Memory consumption: %i B\n"
		"Nodes:              %i\n"
		"Maximum depth       %i\n"
		"Meshes:             %i\n"
		"Animations:         %i\n"
		"Textures (embed.):  %i\n"
		"Materials:          %i\n"
		"Cameras:            %i\n"
		"Lights:             %i\n"
		"Vertices:           %i\n"
		"Faces:              %i\n"
		"Bones:              %i\n"
		"Animation Channels: %i\n"
		"Primitive Types:    %s\n"
		"Average faces/mesh  %i\n"
		"Average verts/mesh  %i\n"
		"Minimum point      (%f %f %f)\n"
		"Maximum point      (%f %f %f)\n"
		"Center point       (%f %f %f)\n"

		;

	aiVector3D special_points[3];
	FindSpecialPoints(scene,special_points);
	printf(format_string,
		mem.total,
		CountNodes(scene->mRootNode),
		GetMaxDepth(scene->mRootNode),
		scene->mNumMeshes,
		scene->mNumAnimations,
		scene->mNumTextures,
		scene->mNumMaterials,
		scene->mNumCameras,
		scene->mNumLights,
		CountVertices(scene),
		CountFaces(scene),
		CountBones(scene),
		CountAnimChannels(scene),
		FindPTypes(scene).c_str(),
		GetAvgFacePerMesh(scene),
		GetAvgVertsPerMesh(scene),
		special_points[0][0],special_points[0][1],special_points[0][2],
		special_points[1][0],special_points[1][1],special_points[1][2],
		special_points[2][0],special_points[2][1],special_points[2][2]
		)
	;
	unsigned int total=0;
	for(unsigned int i = 0;i < scene->mNumMaterials; ++i) {
		aiString name;
		if (AI_SUCCESS==aiGetMaterialString(scene->mMaterials[i],AI_MATKEY_NAME,&name)) {
			printf("%s\n    \'%s\'",(total++?"":"\nNamed Materials:" ),name.data);
		}
	}
	if(total) {
		printf("\n");
	}

	total=0;
	for(unsigned int i = 0;i < scene->mNumMaterials; ++i) {
		aiString name;
		static const aiTextureType types[] = {
			aiTextureType_NONE,
			aiTextureType_DIFFUSE,
			aiTextureType_SPECULAR,
			aiTextureType_AMBIENT,
			aiTextureType_EMISSIVE,
			aiTextureType_HEIGHT,
			aiTextureType_NORMALS,
			aiTextureType_SHININESS,
			aiTextureType_OPACITY,
			aiTextureType_DISPLACEMENT,
			aiTextureType_LIGHTMAP,
			aiTextureType_REFLECTION,
			aiTextureType_UNKNOWN
		};
		for(unsigned int type = 0; type < sizeof(types)/sizeof(types[0]); ++type) {
			for(unsigned int idx = 0;AI_SUCCESS==aiGetMaterialString(scene->mMaterials[i],
				AI_MATKEY_TEXTURE(types[type],idx),&name); ++idx) {
				printf("%s\n    \'%s\'",(total++?"":"\nTexture Refs:" ),name.data);
			}
		}
	}
	if(total) {
		printf("\n");
	}

	total=0;
	for(unsigned int i = 0;i < scene->mNumAnimations; ++i) {
		if (scene->mAnimations[i]->mName.length) {
			printf("%s\n     \'%s\'",(total++?"":"\nNamed Animations:" ),scene->mAnimations[i]->mName.data);
		}
	}
	if(total) {
		printf("\n");
	}

	printf("\nNode hierarchy:\n");
	unsigned int cline=0;
	PrintHierarchy(scene->mRootNode,20,1000,cline);

	printf("\n");
	return 0;
}
