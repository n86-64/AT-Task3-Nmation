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
		LoadAnimationsRecursive(sceneObject);
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

void NAssetManager::createNodes(aiNode* node, DirectX::XMMATRIX transform, NSkeletalMesh* mesh)
{

}

void NAssetManager::LoadMeshRecursive(const aiScene* scene)
{
	//std::queue<aiNode*> nodes;
	if (!scene->HasMeshes()) 
	{
		return;
	}
	else 
	{
		if (scene->mNumMeshes == 1 &&
			!scene->mMeshes[0]->HasBones())
		{
				meshes.emplace_back(new N3DMesh(renderDevice, scene->mMeshes[0]));
				return;
		}
	}

	// Its a skeletal mesh so it should be handled diffrently.
	NSkeletalMesh* skeletalMesh = new NSkeletalMesh();
	int parent = -1;
	DirectX::XMMATRIX model = DirectX::XMMatrixIdentity();

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		skeletalMesh->addMesh(new N3DMesh(renderDevice, scene->mMeshes[i]));
	}

	skeletalMesh->constructNode(scene->mRootNode, model, parent);

	// Assign the skeletal mesh to the list.
	skeletalMeshes.emplace_back(std::unique_ptr<NSkeletalMesh>(skeletalMesh));
}

void NAssetManager::LoadAnimationsRecursive(const aiScene* scene)
{
	// Here we add the animation data.
	for (int i = 0; i < scene->mNumAnimations; i++) 
	{
		
	}
}

void NAssetManager::LoadBones(const aiMesh* node, NSkeletalMesh* mesh)
{
	// Load the animation data for bones.
	for (int i = 0; i < node->mNumBones; i++) 
	{
		mesh->addanimationBoneAssimp(node->mBones[i]);
	}
}
