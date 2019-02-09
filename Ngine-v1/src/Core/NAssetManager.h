// File - NAssetManager.h
// Description - An asset manager that manages imported assets. Primaraly those from assimp.

#pragma once


#include <string>
#include <vector>

#include "NAnimation.h"
#include "Renderer/ShaderInput.h"
#include "N3DMesh.h"
#include "Helpers/Direct3D.h"
#include "NSkeletalMesh.h"

struct aiScene;
struct aiNode;

class NAssetManager 
{
public:
	NAssetManager() = default;

	void setRenderDevice(ID3D11Device* device);

	void loadAssets(std::string name);
	N3DMesh* aquireMesh(std::string name);

	NSkeletalMesh* aquireSkeletalMesh(std::string name);

private:
	void createNodes(aiNode* node, DirectX::XMMATRIX transform, NSkeletalMesh* mesh);

	void LoadMeshRecursive(const aiScene* scene, std::string name);
	
	// Loading functions for various aspects of the model.
	void LoadAnimationsRecursive(const aiScene* scene);
	void LoadBones(const aiMesh* node, NSkeletalMesh* mesh);



private:
	ID3D11Device*							renderDevice = nullptr;

	std::vector<std::unique_ptr<N3DMesh>>		  meshes;
	std::vector<std::unique_ptr<NSkeletalMesh>>   skeletalMeshes;
	std::vector<std::unique_ptr<NAnimation>>	  animations;

};
