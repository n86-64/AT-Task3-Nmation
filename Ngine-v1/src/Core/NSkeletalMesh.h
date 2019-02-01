// File - NSkeletalMesh.h
// Description - A skeletal mesh object which combines various meshes with bones.


#pragma once

#include <memory>
#include <vector>

#include "NAnimationBones.h"

class N3DMesh;

class NSkeletalMesh 
{
public:
	NSkeletalMesh() = default;
	NSkeletalMesh(aiBone* bones, int size);

	void addAnimationBone(NSkeletalBone* newBone);
	void addanimationBoneAssimp(aiBone* newBone);

	NSkeletalBone* getBoneByName(std::string name);

	void addMesh(N3DMesh* newMesh);
	void setRootMesh();

private:
	std::string name;

	// The skeleton and mesh data.
	std::vector<N3DMesh*>						  meshes;
	std::vector<std::unique_ptr<NSkeletalBone>> skeleton;

	int skeletonSize = 0; 
};