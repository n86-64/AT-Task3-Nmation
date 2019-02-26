// File - N3DMesh.h
// Description - Describes 3D mewsh data for loading and instanciating.

#pragma once

#include <vector>
#include <string>

#include "Helpers/NMaths.h"
#include "Helpers/Direct3D.h"
#include "Renderer/ShaderInput.h"

#include "Renderer/NMaterialProperites.h"


struct aiMesh;
struct aiNode;
struct aiScene;

class NMaterial;

class N3DMesh 
{
public:
	N3DMesh(std::string name, ID3D11Device* device); 
	N3DMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, aiMesh* meshObject, const aiScene* scene);
	~N3DMesh();

	std::string getName() const;

	// Retrieve the buffers for rendering.
	ID3D11Buffer*  getVertexBuffer();
	ID3D11Buffer*  getIndexBuffer();

	int			   getIndexCount() const;

	NMaterialTexture*  getTexture();

	// Transform functions. 
	DirectX::XMMATRIX getModelMatrix() { return modelMatrix; }
	void setModelMatrix(DirectX::XMMATRIX mat) { modelMatrix = mat; }
	DirectX::XMMATRIX setModelMatrix(aiNode* node);

	void addBoneValues(int vertexID, int boneId, float weight);

	void setupMesh(ID3D11Device* device);

private:
	std::string meshName = "Null mesh";

	int arrayCount = 0;
	std::vector<VertexInput>		 verticies;
	std::vector<unsigned int>		 indicies;

	// Create the buffers for the mesh.
	void loadMesh(std::string name);

	DirectX::XMMATRIX   modelMatrix = DirectX::XMMatrixIdentity(); // The transform of the object in local space.

	NMaterial*			material;

	NMaterialTexture*    texture = nullptr;

private:
	ID3D11Buffer*		vBuffer = nullptr;
	ID3D11Buffer*		iBuffer = nullptr;
};