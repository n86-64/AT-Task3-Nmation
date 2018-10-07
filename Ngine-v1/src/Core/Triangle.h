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
	void Update() override;
	void Render(NRenderer* renderer) override;

	bool SetupBuffers(ID3D11Device* device);

	ID3D11Buffer* getVertexBuffer();
	ID3D11Buffer* getIndexBuffer(); 

private:
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
	unsigned int indicies[3] = 
	{
		0, 1, 2
	};

	VertexInput  verticies[3] = 
	{
		{ DirectX::XMFLOAT4(-0.5f, -0.5f, 0.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{ DirectX::XMFLOAT4(0.0f,  0.5f, 0.0f, 1.0f),  DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{ DirectX::XMFLOAT4(0.0f,  0.5f, 0.0f, 1.0f),  DirectX::XMFLOAT4(0.0f, 0.0f, .0f, 1.0f)}
	};
};