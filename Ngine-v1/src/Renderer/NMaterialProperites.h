// File - NMaterialProperties.h
// Description - Defines the data structure for storing information on textures. 

#pragma once

#include <vector>
#include <memory>

#include "Helpers/Direct3D.h"

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

	~NMaterialTexture() 
	{
		NMATERIAL_RELEASE(textureData);
		NMATERIAL_RELEASE(textureSRV);
		NMATERIAL_RELEASE(samplerState); 
	}
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