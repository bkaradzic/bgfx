#include "ModelLoader.h"

ModelLoader::ModelLoader()
{
}


ModelLoader::~ModelLoader()
{
}

bool ModelLoader::Load(HWND hwnd, ID3D11Device * dev, ID3D11DeviceContext * devcon, std::string filename)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(filename,
		aiProcess_Triangulate |
		aiProcess_ConvertToLeftHanded);

	if (pScene == NULL)
		return false;

	this->directory = filename.substr(0, filename.find_last_of('/'));

	this->dev = dev;
	this->hwnd = hwnd;

	processNode(pScene->mRootNode, pScene);

	return true;
}

void ModelLoader::Draw(ID3D11DeviceContext * devcon)
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(devcon);
	}
}

string textype;

Mesh ModelLoader::processMesh(aiMesh * mesh, const aiScene * scene)
{
	// Data to fill
	vector<VERTEX> vertices;
	vector<UINT> indices;
	vector<Texture> textures;

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

		if (textype.empty()) textype = determineTextureType(scene, mat);
	}

	// Walk through each of the mesh's vertices
	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		VERTEX vertex;

		vertex.X = mesh->mVertices[i].x;
		vertex.Y = mesh->mVertices[i].y;
		vertex.Z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.texcoord.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.texcoord.y = (float)mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	}

	return Mesh(dev, vertices, indices, textures);
}

vector<Texture> ModelLoader::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName, const aiScene * scene)
{
	vector<Texture> textures;
	for (UINT i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (UINT j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.c_str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // If texture hasn't been loaded already, load it
			HRESULT hr;
			Texture texture;
			if (textype == "embedded compressed texture")
			{
				int textureindex = getTextureIndex(&str);
				texture.texture = getTextureFromModel(scene, textureindex);
			}
			else
			{
				string filename = string(str.C_Str());
				filename = directory + '/' + filename;
				wstring filenamews = wstring(filename.begin(), filename.end());
				hr = CreateWICTextureFromFile(dev, devcon, filenamews.c_str(), nullptr, &texture.texture);
				if (FAILED(hr))
					MessageBox(hwnd, "Texture couldn't be loaded", "Error!", MB_ICONERROR | MB_OK);
			}
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			this->textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

void ModelLoader::Close()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Close();
	}

	dev->Release();
}

void ModelLoader::processNode(aiNode * node, const aiScene * scene)
{
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(this->processMesh(mesh, scene));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

string ModelLoader::determineTextureType(const aiScene * scene, aiMaterial * mat)
{
	aiString textypeStr;
	mat->GetTexture(aiTextureType_DIFFUSE, 0, &textypeStr);
	string textypeteststr = textypeStr.C_Str();
	if (textypeteststr == "*0" || textypeteststr == "*1" || textypeteststr == "*2" || textypeteststr == "*3" || textypeteststr == "*4" || textypeteststr == "*5")
	{
		if (scene->mTextures[0]->mHeight == 0)
		{
			return "embedded compressed texture";
		}
		else
		{
			return "embedded non-compressed texture";
		}
	}
	if (textypeteststr.find('.') != string::npos)
	{
		return "textures are on disk";
	}
}

int ModelLoader::getTextureIndex(aiString * str)
{
	string tistr;
	tistr = str->C_Str();
	tistr = tistr.substr(1);
	return stoi(tistr);
}

ID3D11ShaderResourceView * ModelLoader::getTextureFromModel(const aiScene * scene, int textureindex)
{
	HRESULT hr;
	ID3D11ShaderResourceView *texture;

	int* size = reinterpret_cast<int*>(&scene->mTextures[textureindex]->mWidth);

	hr = CreateWICTextureFromMemory(dev, devcon, reinterpret_cast<unsigned char*>(scene->mTextures[textureindex]->pcData), *size, nullptr, &texture);
	if (FAILED(hr))
		MessageBox(hwnd, "Texture couldn't be created from memory!", "Error!", MB_ICONERROR | MB_OK);

	return texture;
}
