#ifndef MESH_H
#define MESH_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

#include <vector>
#include <d3d11_1.h>
#include <DirectXMath.h>
using namespace DirectX;

struct VERTEX {
	FLOAT X, Y, Z;
	XMFLOAT2 texcoord;
};

struct Texture {
	string type;
	string path;
	ID3D11ShaderResourceView *texture;
};

class Mesh {
public:
	vector<VERTEX> vertices;
	vector<UINT> indices;
	vector<Texture> textures;
	ID3D11Device *dev;

	Mesh(ID3D11Device *dev, vector<VERTEX> vertices, vector<UINT> indices, vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		this->dev = dev;

		this->setupMesh(dev);
	}

	void Draw(ID3D11DeviceContext *devcon)
	{
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;

		devcon->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
		devcon->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		devcon->PSSetShaderResources(0, 1, &textures[0].texture);

		devcon->DrawIndexed(indices.size(), 0, 0);
	}

	void Close()
	{
		VertexBuffer->Release();
		IndexBuffer->Release();
	}
private:
	/*  Render data  */
	ID3D11Buffer *VertexBuffer, *IndexBuffer;

	/*  Functions    */
	// Initializes all the buffer objects/arrays
	bool setupMesh(ID3D11Device *dev)
	{
		HRESULT hr;

		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(VERTEX) * vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &vertices[0];

		hr = dev->CreateBuffer(&vbd, &initData, &VertexBuffer);
		if (FAILED(hr))
			return false;

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT) * indices.size();
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;

		initData.pSysMem = &indices[0];

		hr = dev->CreateBuffer(&ibd, &initData, &IndexBuffer);
		if (FAILED(hr))
			return false;
	}
};

#endif
