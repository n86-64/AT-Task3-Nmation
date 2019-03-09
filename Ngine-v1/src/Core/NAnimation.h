// File - NAnimation.h
// Discription - Holds onto animation data

#pragma once

#include "NAnimationNode.h"

struct aiAnimation;

class NAnimation 
{
public:
	NAnimation() = default;
	NAnimation(aiAnimation* animation);
	~NAnimation() = default;

	void addNode(aiNodeAnim* node); 

	float getDuration() { return durationTicks; }
	float getTickrate() { return tickRate; }

	int getAnimCount() { return animNodes.size(); }

	NAnimationNode*  getNode(int i);

private:
	std::string animationName = "NewAnim";
	float tickRate = 0.0f; // The 'tickrate' of the animation.
	float duration = 0.0f; // duration in seconds. 
	float durationTicks = 0.0f;

	std::vector<NAnimationNode> animNodes;
};