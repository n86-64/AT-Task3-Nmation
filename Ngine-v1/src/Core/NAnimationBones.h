// File - NAnimationBones.h
// Description - Defines a basic bone object.

#pragma once


#include <string>

#include "Helpers/NMaths.h"

struct aiBone;

struct NSkeletalBoneWeight 
{
	int vIndex = -1;
	float weight = 0.0f;
};


class NSkeletalBone 
{
public:
	NSkeletalBone() = default;
	~NSkeletalBone();
	NSkeletalBone(aiBone& animBone); // Construct a bone given from assimp.

	// TODO - Add copy constructor for copy and deletion of bones.
	std::string getName() { return name; }

	DirectX::XMMATRIX   getBoneTransform() { return offsetMatrix; }
	void				setBoneTransform(DirectX::XMMATRIX boneTransform) { offsetMatrix = boneTransform; };
	
private:
	std::string name;

	// Bone data.
	NSkeletalBoneWeight*	weights = nullptr;
	int						weightCount = 0;
	DirectX::XMMATRIX		offsetMatrix = DirectX::XMMatrixIdentity();
};