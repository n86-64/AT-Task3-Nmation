// File - NMaterial.h
// Description - Defines a collection of shaders that collectivly define a "material"

#pragma once

#include <string>
#include "Helpers/Direct3D.h"
#include "Helpers/NMaths.h"

// The Data structure for inputs to a material.
// TODO - Add support for textures and lighting. 
struct VertexInput 
{
	DirectX::XMFLOAT4   pos;
	DirectX::XMFLOAT4	col;
};

class NMaterial 
{
public:
	NMaterial(std::string newMaterialName);
	~NMaterial();

	// Retrieve the shaders for the Direct3D pipeline. 
	ID3D11VertexShader*  getVertexShader();
	ID3D11PixelShader*   getFragmentShader();

	bool loadVertexShader(std::string name, ID3D11Device* device);
	bool loadFragShader(std::string name, ID3D11Device* device);

private:
	std::string  materialName;

	void ReleaseMaterialResources(ID3D11DeviceChild*  shaderResource);

	// Depricated.
	std::string vertexShaderName;
	std::string fragShaderName;

	// Shaders
	ID3D11VertexShader*   vertexShader = nullptr;
	ID3D11PixelShader*    fragShader = nullptr;

	// Materials dont define input layout as this will be constant for all materials.
	// Hence why define it per class.

};