#include <Assimp/mesh.h>

#include "NSkeletalMesh.h"

NSkeletalMesh::NSkeletalMesh(aiBone * bones, int size)
{
	skeletonSize += size;
	for (int i = 0; i < size; i++) 
	{
		addanimationBoneAssimp(&(bones[i]));
	}
}

void NSkeletalMesh::addAnimationBone(NSkeletalBone* newBone)
{
	skeleton.emplace_back(newBone);
	skeletonSize++;
}

void NSkeletalMesh::addanimationBoneAssimp(aiBone* newBone)
{
	// Add a new bone.
	skeleton.emplace_back(std::make_unique<NSkeletalBone>(*newBone));
}

NSkeletalBone* NSkeletalMesh::getBoneByName(std::string name)
{
	for (int i = 0; i < skeleton.size(); i++)
	{
		if (skeleton[i]->getName() == name) 
		{
			return skeleton[i].get();
		}
	}
}

void NSkeletalMesh::addMesh(N3DMesh * newMesh)
{
	meshes.emplace_back(newMesh);
}
