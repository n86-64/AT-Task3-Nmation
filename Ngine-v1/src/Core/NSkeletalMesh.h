// File - NSkeletalMesh.h
// Description - A skeletal mesh object which combines various meshes with bones.


#pragma once

#include <memory>
#include <vector>

#include "NanimationBones.h"

class N3DMesh;

class NSkeletalMesh 
{
public:
	NSkeletalMesh() = default;

	void addAnimationBone(NSkeletalBone* newBone);
	void addanimationBoneAssimp(aiBone* newBone);

private:


	// The skeleton and mesh data.
	std::vector<N3DMesh*>						  meshes;
	std::vector<std::unique_ptr<NSkeletalBone>> skeleton;
};