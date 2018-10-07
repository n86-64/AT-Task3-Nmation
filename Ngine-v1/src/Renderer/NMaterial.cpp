#include "NMaterial.h"

NMaterial::NMaterial(std::string newMaterialName)
	:materialName(newMaterialName)
{
	// TODO - Add routiene to load a material which states what shader to load.
	// Shaders to load will be determined by a file. This is provided to the system.
}

NMaterial::~NMaterial()
{
	ReleaseMaterialResources(vertexShader);
	ReleaseMaterialResources(fragShader); 
}

ID3D11VertexShader* NMaterial::getVertexShader()
{
	return vertexShader;
}

ID3D11PixelShader* NMaterial::getFragmentShader()
{
	return fragShader;
}

bool NMaterial::loadVertexShader(std::string name)
{
	ReleaseMaterialResources(vertexShader);
	loadShaders(name, vertexShader);
	return vertexShader;
}

bool NMaterial::loadFragShader(std::string name)
{
	ReleaseMaterialResources(fragShader);
	loadShaders(name, fragShader);
	return fragShader;
}

void NMaterial::ReleaseMaterialResources(ID3D11DeviceChild * shaderResource)
{
	if (shaderResource) 
	{
		shaderResource->Release();
		shaderResource = nullptr;
	}
}

void NMaterial::loadShaders(std::string shaderName, ID3D11DeviceChild * shaderObject)
{

}

