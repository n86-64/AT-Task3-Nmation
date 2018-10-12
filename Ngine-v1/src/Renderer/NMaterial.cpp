#include "NMaterial.h"
#include "Helpers/FileReaderBinary.h"

NMaterial::NMaterial(std::string newMaterialName)
	:materialName(newMaterialName)
{
	// TODO - Add routiene to load a material which states what shader to load.
	// Shaders to load will be determined by a file. This is provided to the system.
}

NMaterial::~NMaterial()
{
	ReleaseMaterialResources(matInput);
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

ID3D11InputLayout * NMaterial::getInputLayout()
{
	return matInput;
}

bool NMaterial::loadVertexShader(std::string name, ID3D11Device* device)
{
	HRESULT hr = S_OK;
	ReleaseMaterialResources(vertexShader);
	FileReaderBinary  file(name + ".cso");

	if (file.openFile()) 
	{
		hr = device->CreateVertexShader((void*)file.getFileData(), file.getFileSize(), nullptr, &vertexShader);
		hr = device->CreateInputLayout(shaderInput, 2, file.getFileData(), file.getFileSize(), &matInput);
		return SUCCEEDED(hr);
	}
	else 
	{
		return false;
	}
}

bool NMaterial::loadFragShader(std::string name, ID3D11Device* device)
{
	HRESULT hr = S_OK;
	ReleaseMaterialResources(fragShader);
	FileReaderBinary  file(name + ".cso");

	if (file.openFile())
	{
		hr = device->CreatePixelShader((void*)file.getFileData(), file.getFileSize(), nullptr, &fragShader);
		return SUCCEEDED(hr);
	}
	else
	{
		return false;
	}
}


void NMaterial::ReleaseMaterialResources(ID3D11DeviceChild * shaderResource)
{
	if (shaderResource) 
	{
		shaderResource->Release();
		shaderResource = nullptr;
	}
}

