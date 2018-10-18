#include "NMaterial.h"
#include "Helpers/FileReaderBinary.h"

#include "Helpers/JSONFileReader.h"

NMaterial::NMaterial(std::string newMaterialName, ID3D11Device* device)
{
	// Here we parse a file for creating the shader.
	// Utalise my JSONFileParser here :).
	// Here we will design a material file.
	JSONFileReader  matFile;
	matFile.setFilePath("resources/materials/" + newMaterialName + ".nmat"); // Open up the material file.

	if (matFile.parseFile()) 
	{
		std::string propertyName;
		for (auto file : matFile.getFileBuffer().members()) 
		{
			propertyName = file.name();

			if (propertyName == "Name") { materialName = file.value().as_string(); }
			else if (propertyName == "Shaders") 
			{
				for (auto shaders : file.value().array_range()) 
				{
					// Load the specified shader from the file.
					std::string test = shaders["Name"].as_string(); 
					shadersLoaded = loadShaders(shaders["Name"].as_string(), (NMaterialShaderTypes)shaders["Type"].as_int(), device);
				}
			}
		}
	}
}

NMaterial::~NMaterial()
{
	NMATERIAL_RELEASE(vertexShader);
	NMATERIAL_RELEASE(fragShader);
	NMATERIAL_RELEASE(geometryShader);
}

ID3D11VertexShader* NMaterial::getVertexShader()
{
	return vertexShader;
}

ID3D11PixelShader* NMaterial::getFragmentShader()
{
	return fragShader;
}

ID3D11GeometryShader* NMaterial::getGeometryShader()
{
	return geometryShader;
}

ID3D11InputLayout* NMaterial::getInputLayout()
{
	return matInput;
}

bool NMaterial::loadVertexShader(std::string name, ID3D11Device* device)
{
	HRESULT hr = S_OK;
	ReleaseMaterialResources(vertexShader);
	FileReaderBinary  file(name);

	if (file.openFile()) 
	{
		hr = device->CreateVertexShader((void*)file.getFileData(), file.getFileSize(), nullptr,  &vertexShader);
		hr = device->CreateInputLayout(shaderInput, 3, file.getFileData(), file.getFileSize(), &matInput);
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
	FileReaderBinary  file(name);

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

bool NMaterial::loadGeometryShader(std::string name, ID3D11Device* device)
{
	// TODO - Add support for geometry shaders in the future. 
	return false;
}

std::string NMaterial::getShaderName() const
{
	return materialName;
}

bool NMaterial::materialLoaded() const
{
	return shadersLoaded;
}

bool NMaterial::loadShaders(std::string name, NMaterialShaderTypes shaderType, ID3D11Device* device)
{
	bool result = false;
	HRESULT hr = S_OK;

	switch (shaderType) 
	{
	case SHADER_TYPE_VERTEX:
		result = loadVertexShader(name, device);
		break;
	case SHADER_TYPE_FRAG:
		result = loadFragShader(name, device);
		break;
	case SHADER_TYPE_GEOMETRY:
		result = loadFragShader(name, device);
		break;
	default:
		return false;
	}

	return result;
}

void NMaterial::ReleaseMaterialResources(ID3D11DeviceChild * shaderResource)
{
	if (shaderResource) 
	{
		shaderResource->Release();
		shaderResource = nullptr;
	}
}
