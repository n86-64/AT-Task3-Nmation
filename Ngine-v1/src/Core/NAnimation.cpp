#include "Assimp/anim.h"

#include "NAnimation.h"

NAnimation::NAnimation(aiAnimation* animation)
{
	animationName = animation->mName.C_Str();
	tickRate = animation->mTicksPerSecond;
	duration = animation->mDuration / tickRate;

	// TODO - Load the animation nodes. 
	for (int i = 0; i < animation->mNumChannels; i++) 
	{
		addNode(animation->mChannels[i]);
	}
}

void NAnimation::addNode(aiNodeAnim* node)
{
	animNodes.emplace_back(NAnimationNode(node));
}

NAnimationNode* NAnimation::getNode(int i)
{
	return &animNodes[i];
}
