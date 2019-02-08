#include "Assimp/anim.h"

#include "NAnimation.h"

NAnimation::NAnimation(aiAnimation* animation)
{
	animationName = animation->mName.C_Str();
	tickRate = animation->mTicksPerSecond;
	duration = animation->mDuration / tickRate;

	// TODO - Load the animation nodes. 
	
}

void NAnimation::addNode(aiNodeAnim* node)
{
	animNodes.emplace_back(NAnimationNode(node));
}
