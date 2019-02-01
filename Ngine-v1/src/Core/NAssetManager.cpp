#include <queue>

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
		// Load all assimp meshes as mesh collections with skeletons.
		// Treat all objects as hierarchical meshes.
		// simplifies the engine and gets it working.
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
	std::queue<aiNode*> nodes;
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

	aiNode*  currentNode;
	nodes.emplace(scene->mRootNode);

	int		 meshIndex = -1;
	N3DMesh*  newMesh = nullptr;

	while (!nodes.empty()) 
	{
		currentNode = nodes.front();
		for (int i = 0; i < currentNode->mNumMeshes; i++)
		{
			newMesh = new N3DMesh(renderDevice, scene->mMeshes[currentNode->mMeshes[i]]);
			meshes.emplace_back(newMesh);
		}

		for (int j = 0; j < currentNode->mNumChildren; j++) 
		{
			nodes.emplace(currentNode->mChildren[j]);
		}
		nodes.pop();
	}
}

void NAssetManager::LoadBonesRecursive(const aiNode* node)
{
	// Load the animation data for bones.
}