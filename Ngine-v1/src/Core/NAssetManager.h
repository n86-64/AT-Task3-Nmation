// File - NAssetManager.h
// Description - An asset manager that manages imported assets. Primaraly those from assimp.

#pragma once


#include <string>
#include <vector>

#include "Renderer/ShaderInput.h"
#include "N3DMesh.h"
#include "Helpers/Direct3D.h"

// Forward Decleration.
struct aiScene;
struct aiNode;

class NAssetManager 
{
public:
	NAssetManager() = default;

	void setRenderDevice(ID3D11Device* device);

	void loadAssets(std::string name);
	N3DMesh* aquireMesh(std::string name);


private:
	void LoadMeshRecursive(const aiScene* scene);
	
	// Loading functions for various aspects of the model.
	void LoadAnimationsRecursive(const aiScene* scene);
	void LoadBonesRecursive(const aiNode* node);

private:
	ID3D11Device*							renderDevice = nullptr;

	std::vector<std::unique_ptr<N3DMesh>>   meshes;
};