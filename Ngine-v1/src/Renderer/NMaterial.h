// File - NMaterial.h
// Description - Defines a collection of shaders that collectivly define a "material"

#pragma once

#include <string>
#include "Helpers/Direct3D.h"

class NMaterial 
{
public:
	NMaterial(std::string newMaterialName);
	~NMaterial();

	ID3D11VertexShader*  getVertexShader();
	ID3D11PixelShader*   getFragmentShader();

	bool loadVertexShader(std::string name);
	bool loadFragShader(std::string name);

private:
	std::string  materialName;

	void ReleaseMaterialResources(ID3D11DeviceChild*  shaderResource);

	void loadShaders(std::string  shaderName, ID3D11DeviceChild* shaderObject);

	// Shaders
	ID3D11VertexShader*   vertexShader = nullptr;
	ID3D11PixelShader*    fragShader = nullptr;
};