#include "Helpers/WICTextureLoader.h"
#include "NTextureManager.h"

NTextureData* NTextureManager::createTexture(std::string name)
{
	for (auto& tex : textures) 
	{
		if (name == tex.name) 
		{
			return &tex;
		}
	}

	return nullptr;
}

NTextureData* NTextureManager::createTexture(std::string name, aiTexture* newTexture)
{

	return nullptr;
}

void NTextureManager::constructTexture(std::string name)
{
	std::wstring wName(name.begin(), name.end());

	NTextureData data;

	HRESULT hr = CreateWICTextureFromFile(renderDevice, renderContext, wName.c_str(), (ID3D11Resource**)&data.textureObject, &data.sampler);

	if (SUCCEEDED(hr)) 
	{

	}
}
