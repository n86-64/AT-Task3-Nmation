// File - N3DMesh.h
// Description - Describes 3D mewsh data for loading and instanciating.

#pragma once

#include <vector>
#include <string>

#include "Helpers/NMaths.h"
#include "Helpers/Direct3D.h"
#include "Renderer/ShaderInput.h"


struct aiMesh;
struct aiNode;

class N3DMesh 
{
public:
	N3DMesh(std::string name, ID3D11Device* device); 
	N3DMesh(ID3D11Device* device, aiMesh* meshObject);
	~N3DMesh();

	std::string getName() const;

	// Retrieve the buffers for rendering.
	ID3D11Buffer*  getVertexBuffer();
	ID3D11Buffer*  getIndexBuffer();

	int			   getIndexCount() const;

	// Transform functions. 
	DirectX::XMMATRIX getModelMatrix() { return modelMatrix; }
	void setModelMatrix(DirectX::XMMATRIX mat) { modelMatrix = mat; }
	DirectX::XMMATRIX setModelMatrix(aiNode* node);

	void assignParent(N3DMesh* newParent) { parent = newParent; }
	void addChildren(N3DMesh* children, int size);

private:
	std::string meshName = "Null mesh";

	int arrayCount = 0;
	std::vector<VertexInput>		 verticies;
	std::vector<unsigned int>		 indicies;

	// Create the buffers for the mesh.
	void loadMesh(std::string name);
	void setupMesh(ID3D11Device* device); 

	DirectX::XMMATRIX   modelMatrix = DirectX::XMMatrixIdentity(); // The transform of the object in local space.

	// Transform info.
	N3DMesh*					parent;
	N3DMesh**					children;

private:
	ID3D11Buffer*		vBuffer = nullptr;
	ID3D11Buffer*		iBuffer = nullptr;
};