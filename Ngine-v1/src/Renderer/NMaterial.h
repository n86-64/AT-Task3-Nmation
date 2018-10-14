// File - NMaterial.h
// Description - Defines a collection of shaders that collectivly define a "material"

#pragma once

#include <string>
#include <map>
#include "Helpers/Direct3D.h"

const int NMAT_SHADER_TYPE_COUNT = 3;

enum NMaterialShaderTypes 
{
	SHADER_TYPE_VERTEX = 0,
	SHADER_TYPE_FRAG = 1,
	SHADER_TYPE_GEOMETRY = 2
};

// TODO - Decouple so that shaders and material properties are seperate.
class NMaterial 
{
public:
	// Constructs the shader from a file.
	NMaterial(std::string newMaterialName, ID3D11Device* device);
	~NMaterial();

	// Retrieve the shaders for the Direct3D pipeline. 
	ID3D11VertexShader*  getVertexShader();
	ID3D11PixelShader*   getFragmentShader();
	ID3D11GeometryShader* getGeometryShader();
	ID3D11InputLayout*   getInputLayout();

	std::string getShaderName() const; 
	bool materialLoaded() const;

private:
	std::string  materialName;

	bool loadShaders(std::string name, NMaterialShaderTypes shaderType, ID3D11Device* device);
	void ReleaseMaterialResources(ID3D11DeviceChild*  shaderResource);

	bool shadersLoaded = false;

	bool loadVertexShader(std::string name, ID3D11Device* device);
	bool loadFragShader(std::string name, ID3D11Device* device);
	bool loadGeometryShader(std::string name, ID3D11Device* device);

	// Shaders
	ID3D11VertexShader*		 vertexShader = nullptr;
	ID3D11PixelShader*		 fragShader = nullptr;
	ID3D11GeometryShader*	 geometryShader = nullptr;

	// Materials dont define input layout as this will be constant for all materials.
	// Hence why define it per class.
		// Definition for shader input layout
	// Impliment custom input layouts on the
	D3D11_INPUT_ELEMENT_DESC  shaderInput[2] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	ID3D11InputLayout*    matInput = nullptr;
};