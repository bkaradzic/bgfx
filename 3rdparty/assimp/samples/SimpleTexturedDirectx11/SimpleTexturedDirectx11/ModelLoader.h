#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <vector>
#include <d3d11_1.h>
#include <DirectXMath.h>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "TextureLoader.h"

using namespace DirectX;

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	bool Load(HWND hwnd, ID3D11Device* dev, ID3D11DeviceContext* devcon, std::string filename);
	void Draw(ID3D11DeviceContext* devcon);

	void Close();
private:
	ID3D11Device *dev;
	ID3D11DeviceContext *devcon;
	std::vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;
	HWND hwnd;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName, const aiScene* scene);
	string determineTextureType(const aiScene* scene, aiMaterial* mat);
	int getTextureIndex(aiString* str);
	ID3D11ShaderResourceView* getTextureFromModel(const aiScene* scene, int textureindex);
};

#endif // !MODEL_LOADER_H

