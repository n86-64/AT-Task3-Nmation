// File - NTextureManager.h
// Discription - A basic texture class and manager which keeps textures together.

#pragma once

#include <vector>
#include <string>

#include <Assimp/texture.h>

#include "Helpers/Direct3D.h"


struct NTextureData 
{
	std::string				name = "null";
	ID3D11Texture2D*		textureObject = nullptr;
	ID3D11SamplerState*		sampler = nullptr;
};


class NTextureManager 
{
public:
	NTextureManager() = default;

	void assignRenderDevice(ID3D11Device*  device) { renderDevice = device; }

	NTextureData*  createTexture(std::string name);
	NTextureData*  createTexture(std::string name, aiTexture* newTexture); // Create texture from assimp texture, instead of searching for texture.

private:
	void constructTexture(std::string name);

	std::vector<NTextureData>	textures;
	ID3D11Device*			renderDevice = nullptr;
};