// File - NSkeletalMesh.h
// Description - A skeletal mesh object which combines various meshes with bones.


#pragma once

#include <memory>
#include <vector>

#include "NSkeletalMesh.h"

class N3DMesh;

class NSkeletalMesh 
{
public:
	NSkeletalMesh() = default;

private:
	// The skeleton and mesh data.
	std::vector<N3DMesh*>						  meshes;
	std::vector<std::unique_ptr<NSkeletalMesh>> skeleton;
};