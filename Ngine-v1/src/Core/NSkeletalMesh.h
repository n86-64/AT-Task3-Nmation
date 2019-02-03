// File - NSkeletalMesh.h
// Description - A skeletal mesh object which combines various meshes with bones.


#pragma once
#include "NSkeletalNode.h"

class N3DMesh;

class NSkeletalMesh 
{
public:
	NSkeletalMesh() = default;
	NSkeletalMesh(aiBone* bones, int size);

	void addAnimationBone(NSkeletalBone* newBone);
	void addanimationBoneAssimp(aiBone* newBone);

	NSkeletalBone* getBoneByName(std::string name);

	NSkeletalNode* constructNode(aiNode* node, DirectX::XMMATRIX transform, int parent = -1);

	void addMesh(N3DMesh* newMesh);


	void addMeshRecursive();
	void setRootMesh();

private:
	std::string name;

	// The skeleton and mesh data.
	std::vector<N3DMesh*>						  meshes;
	std::vector<std::unique_ptr<NSkeletalBone>>   skeleton;


	std::vector<std::unique_ptr<NSkeletalNode>>   nodes;
	int skeletonSize = 0; 
};