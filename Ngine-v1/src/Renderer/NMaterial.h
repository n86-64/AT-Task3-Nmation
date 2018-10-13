// File - NMaterial.h
// Description - Defines a collection of shaders that collectivly define a "material"

#pragma once

#include <string>
#include <map>
#include "Helpers/Direct3D.h"

const int NMAT_SHADER_TYPE_COUNT = 3;

class NMaterial 
{
public:
	NMaterial(std::string newMaterialName);
	~NMaterial();

	// Retrieve the shaders for the Direct3D pipeline. 
	ID3D11VertexShader*  getVertexShader();
	ID3D11PixelShader*   getFragmentShader();
	ID3D11GeometryShader* getGeometryShader();
	ID3D11InputLayout*   getInputLayout();

	bool loadVertexShader(std::string name, ID3D11Device* device);
	bool loadFragShader(std::string name, ID3D11Device* device);

	bool createInputLayout(ID3D11Device* device);

	bool loadShaders();

	std::string getShaderName() const; 

private:
	std::string  materialName;

	void ReleaseMaterialResources(ID3D11DeviceChild*  shaderResource);
	void ReleaseShaders();

	// Shaders
	ID3D11VertexShader*   vertexShader = nullptr;
	ID3D11PixelShader*    fragShader = nullptr;

	// Materials dont define input layout as this will be constant for all materials.
	// Hence why define it per class.
		// Definition for shader input layout
	D3D11_INPUT_ELEMENT_DESC  shaderInput[2] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	ID3D11InputLayout*    matInput = nullptr;

	// Shaders stored in an array.
	ID3D11DeviceChild*    materialShaders[NMAT_SHADER_TYPE_COUNT] = {nullptr, nullptr, nullptr};
};