// File - NMaterialProperties.h
// Description - Defines the data structure for storing information on textures. 

#pragma once

#include <comdef.h>

#include <vector>
#include <memory>

#include "Helpers/Direct3D.h"
#include "Helpers/WICTextureLoader.h"

// TODO - Add this into materials to show textures.
// Store textures seperatly.
inline void NMATERIAL_RELEASE(ID3D11DeviceChild* device)
{
	if (device)
	{
		device->Release();
		device = nullptr;
	}
}

// The datatype of the property. 
enum NMaterialPropertyType 
{
	// numeric types
	PROPERTY_INT = 0,
	PROPERTY_FLOAT,

	PROPERTY_VECTOR,
	PROPERTY_COLOUR,
};

// Defines a material property. This could represent an element or an array of elements.
struct NMaterialProperty 
{
	std::string				propertyName = "NullData";
	NMaterialPropertyType   dataType;
	void*					value = nullptr; // TODO - Should we use void it is slightly dangerous. (We can providing the data is deleted.)
	size_t					dataSize = (size_t)0;
	int						elements = 0;

	// Destroy all unique data.
	~NMaterialProperty() 
	{
		if (value) 
		{
			if (elements > 1) 
			{ 
				delete[] value; 
			}
			else 
			{ 
				delete value; 
			}

			value = nullptr;
		}
	}
};

struct NMaterialTexture 
{
	std::string					textureName = "NullTexture";
	ID3D11Texture2D*			textureData = nullptr;   // The raw texture data and texture proeperty info that is then bound.
	ID3D11ShaderResourceView*	textureSRV = nullptr;    // Used as a handler to retrieve the shader resource.
	ID3D11SamplerState*			samplerState = nullptr;  // Describes how to sample the texture.

	NMaterialTexture() {}

	NMaterialTexture(std::string textureFileName, 
		ID3D11Device* renderDevice, 
		ID3D11DeviceContext* deviceContext) 
	{
		textureName = textureFileName;
		std::wstring wTemp(textureFileName.begin(), textureFileName.end());
		hr = DirectX::CreateWICTextureFromFile(renderDevice, deviceContext, wTemp.c_str(), (ID3D11Resource**)&textureData, &textureSRV);

		// Create the sampler.
		D3D11_SAMPLER_DESC   texDesc;
		ZeroMemory(&texDesc, sizeof(texDesc));
		texDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		texDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		texDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		texDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		texDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		texDesc.MinLOD = 0;
		texDesc.MaxLOD = D3D11_FLOAT32_MAX;

		hr = renderDevice->CreateSamplerState(&texDesc, &samplerState);
	}

	bool isTextureValid() { return SUCCEEDED(hr); }

	~NMaterialTexture() 
	{
		NMATERIAL_RELEASE(textureData);
		NMATERIAL_RELEASE(textureSRV);
		NMATERIAL_RELEASE(samplerState); 
	}

private:
	HRESULT hr;
};

class NMaterialProperties 
{
public:
	NMaterialProperties() = default;
	~NMaterialProperties();

	void				 setDevice(ID3D11Device* device);

	NMaterialProperty*   getProperty(int index);
	int					 getNumberOfProperties();
	void				 setNumberOfProperties();

	// TODO - Add funtions to retrieve textures from the material.


	void				AddProperty(std::string name, void* data, int elements = 1);
	void				AddTexture(std::string filePath);

private:
	// The properties read from the material. 
	std::vector<std::unique_ptr<NMaterialProperty>>   properties;
	std::vector<std::unique_ptr<NMaterialTexture>>	  textures;

	ID3D11Device*		device;
};