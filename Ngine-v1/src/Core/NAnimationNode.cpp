#include <algorithm>
#include "Assimp/anim.h"

#include "NAnimationNode.h"

NAnimationNode::NAnimationNode(aiNodeAnim* animNode)
{
	unsigned int maxIndex = animNode->mNumPositionKeys;
	maxIndex = std::max(maxIndex, animNode->mNumRotationKeys);
	maxIndex = std::max(maxIndex, animNode->mNumScalingKeys);
	
	translation.reserve(animNode->mNumPositionKeys);
	rotation.reserve(animNode->mNumRotationKeys);
	scale.reserve(animNode->mNumScalingKeys);

	// Construct a node.
	for (int i = 0; i < maxIndex; i++) 
	{
		if (i < animNode->mNumPositionKeys) { translation.emplace_back(NAnimationKey(animNode->mPositionKeys[i])); }
		if (i < animNode->mNumRotationKeys) { rotation.emplace_back(NAnimationKey(animNode->mRotationKeys[i])); }
		if (i < animNode->mNumScalingKeys)  { scale.emplace_back(NAnimationKey(animNode->mScalingKeys[i])); }
	}
}
