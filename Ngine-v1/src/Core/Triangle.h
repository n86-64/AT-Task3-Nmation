// File - Triangle.h
// Description - Defines a basic 3D triangle.

#pragma once

#include "NGameObject.h"

#include "Renderer/ShaderInput.h"
#include "Helpers/Direct3D.h"

class NMaterial;

class Triangle : public NGameObject 
{
public:
	Triangle(NMaterial*  material);
	~Triangle();

	// Inherited via NGameObject
	void Update(GameStateData& input) override;
	void Render(NRenderer* renderer) override;

	bool SetupBuffers(ID3D11Device* device);

	ID3D11Buffer* getVertexBuffer();
	ID3D11Buffer* getIndexBuffer(); 

	NMaterial*   getMaterial();

	int getIndexCount() { return ARRAYSIZE(indicies); }

private:
	float    timeTotal = 0.0f;


	void createObjectDiscriptors(); // Creates a vertex and index buffer for the object.

	// The object material.
	NMaterial*   mat;

	// The buffers. 
	ID3D11Buffer*  vertexBuffer = nullptr;
	ID3D11Buffer*  indexBuffer = nullptr;

	// Our buffer and buffer data discriptors.
	D3D11_BUFFER_DESC  vertexBufferDesc = { 0 };
	D3D11_BUFFER_DESC  indexBufferDesc = { 0 };
	D3D11_SUBRESOURCE_DATA vdata = { 0 };
	D3D11_SUBRESOURCE_DATA idata = { 0 };

	// The data itself.
	unsigned int indicies[36] = 
	{
			3,1,0,
			2,1,3,

			0,5,4,
			1,5,0,

			3,4,7,
			0,4,3,

			1,6,5,
			2,6,1,

			2,7,6,
			3,7,2,

			6,4,5,
			7,4,6,
	};

	VertexInput  verticies[8] = 
	{
		{ DirectX::XMFLOAT4(-1.0f,  1.0f, -1.0f , 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
		{ DirectX::XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
		{ DirectX::XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
		{ DirectX::XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
		{ DirectX::XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
		{ DirectX::XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
		{ DirectX::XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
		{ DirectX::XMFLOAT4(-1.0f, -1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
	};
};