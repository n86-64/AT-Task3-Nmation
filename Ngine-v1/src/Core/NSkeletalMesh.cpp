#include <Assimp/mesh.h>
#include <Assimp/scene.h>

#include "NSkeletalMesh.h"
#include "N3DMesh.h"

NSkeletalMesh::NSkeletalMesh(aiBone * bones, int size)
{
	//skeletonSize += size;
	//for (int i = 0; i < size; i++) 
	//{
	//	addanimationBoneAssimp(&(bones[i]));
	//}
}

void NSkeletalMesh::addAnimationBone(NSkeletalBone* newBone)
{
	skeleton.emplace_back(newBone);
	skeletonSize++;
}

void NSkeletalMesh::addanimationBoneAssimp(int meshIndex, aiBone* newBone)
{
	int boneIndex = getBoneByName(newBone->mName.C_Str());
	if (boneIndex == -1) 
	{
		skeleton.emplace_back(std::make_unique<NSkeletalBone>(*newBone));
		boneIndex = skeleton.size() - 1;
	}

	// Add a new bone.
	for (int i = 0; i < newBone->mNumWeights; i++) 
	{
		meshes[meshIndex]->addBoneValues(newBone->mWeights[i].mVertexId, boneIndex, newBone->mWeights[i].mWeight);
	}
}

int NSkeletalMesh::getBoneByName(std::string name)
{
	for (int i = 0; i < skeleton.size(); i++)
	{
		if (skeleton[i]->getName() == name) 
		{
			return i;
		}
	}

	return -1;
}

int NSkeletalMesh::constructNode(aiNode* node, DirectX::XMMATRIX transform, int parent)
{
	DirectX::XMMATRIX model = transform * convertToMatrix(&node->mTransformation);

	NSkeletalNode* newNode = new NSkeletalNode();
	newNode->setParent(parent);
	newNode->setModelMatrix(model);

	newNode->setMeshSize(node->mNumMeshes);
	for (int i = 0; i < node->mNumMeshes; i++) 
	{
		newNode->assignMeshes(node->mMeshes[i]);
	}

	nodes.emplace_back(newNode);
	int index = nodes.size() - 1;

	if (parent != -1) 
	{ 
		nodes[parent]->addChild(index); 
	}

	for (int j = 0; j < node->mNumChildren; j++) 
	{
		constructNode(node->mChildren[j], model, index);
	}

	return index;
}

void NSkeletalMesh::addMesh(N3DMesh* newMesh)
{
	meshes.emplace_back(newMesh);
}
