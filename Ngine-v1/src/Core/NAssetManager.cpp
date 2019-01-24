#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

#include "NAssetManager.h"

void NAssetManager::setRenderDevice(ID3D11Device * device)
{
	renderDevice = device;
}

void NAssetManager::loadAssets(std::string name)
{
	std::string path = "resources/" + name;
	Assimp::Importer fileLoader;

	const aiScene* sceneObject = fileLoader.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate | 
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
		);

	if (!sceneObject) 
	{
		// Return reporting an error in the process.
		OutputDebugString("ERROR - Failed to load Model.");
		return;
	}
	else 
	{
		// Start the Loading process.
		// If skeletal mesh we will load as a skeletal mesh.
		LoadMeshRecursive(sceneObject);
	}

	
}

N3DMesh* NAssetManager::aquireMesh(std::string name)
{
	for (int i = 0; i < meshes.size(); i++)
	{
		if (meshes[i]->getName() == name) 
		{
			return meshes[i].get();
		}
	}

	return nullptr;
}

void NAssetManager::LoadMeshRecursive(const aiScene* scene)
{
	if (!scene->HasMeshes()) 
	{
		return;
	}
	else 
	{
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			meshes.emplace_back(new N3DMesh(renderDevice, scene->mMeshes[i]));
		}
	}

	aiNode*  currentNode = scene->mRootNode;
	int		 meshIndex = -1;
	N3DMesh*  newMesh = nullptr;

	for (int i = 0; i < currentNode->mNumMeshes; i++) 
	{
		newMesh = new N3DMesh(renderDevice, scene->mMeshes[currentNode->mMeshes[i]]);
		meshes.emplace_back(newMesh);
	}
}
