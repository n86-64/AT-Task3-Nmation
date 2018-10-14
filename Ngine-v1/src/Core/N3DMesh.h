// File - N3DMesh.h
// Description - Describes 3D mewsh data for loading and instanciating.

#pragma once

#include <vector>
#include <string>

#include "Helpers/NMaths.h"
#include "Helpers/Direct3D.h"
#include "Renderer/ShaderInput.h"

class N3DMesh 
{
public:
	N3DMesh(std::string name, ID3D11Device* device); 

	std::string getName() const;

	// Retrieve the buffers for rendering.
	ID3D11Buffer*  getVertexBuffer();
	ID3D11Buffer*  getIndexBuffer();

private:
	std::string meshName = "Null mesh";

	int arrayCount = 0;
	std::vector<VertexInput>		 verticies;
	std::vector<unsigned int>		 indicies;

	// Create the buffers for the mesh.
	void loadMesh(std::string name);
	void setupMesh(ID3D11Device* device); 

private:
	ID3D11Buffer*		vBuffer = nullptr;
	ID3D11Buffer*		iBuffer = nullptr;
};