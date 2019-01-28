#include "NAnimationBones.h"

NSkeletalBone::~NSkeletalBone()
{
	if (weights) 
	{
		delete[] weights;
		weights = nullptr;
	}
}

NSkeletalBone::NSkeletalBone(const aiBone& animBone)
{
	// Construct from aiBone.
	name = animBone.mName.C_Str();
	weights = new NSkeletalBoneWeight[animBone.mNumWeights];
	
	for (int i = 0; i < animBone.mNumWeights; i++) 
	{
		weights[i].vIndex = animBone.mWeights[i].mVertexId;
		weights[i].weight = animBone.mWeights[i].mWeight;
	}

	// Load the offset matrix.
	offsetMatrix = DirectX::XMMATRIX
	(
		animBone.mOffsetMatrix.a1, animBone.mOffsetMatrix.a2, animBone.mOffsetMatrix.a3, animBone.mOffsetMatrix.a4,
		animBone.mOffsetMatrix.b1, animBone.mOffsetMatrix.b2, animBone.mOffsetMatrix.b3, animBone.mOffsetMatrix.b4,
		animBone.mOffsetMatrix.c1, animBone.mOffsetMatrix.c2, animBone.mOffsetMatrix.c3, animBone.mOffsetMatrix.c4,
		animBone.mOffsetMatrix.d1, animBone.mOffsetMatrix.d2, animBone.mOffsetMatrix.d3, animBone.mOffsetMatrix.d4
	);
}
