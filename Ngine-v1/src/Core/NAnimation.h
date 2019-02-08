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

private:
	std::string animationName = "NewAnim";
	float tickRate = 0.0f; // The 'tickrate' of the animation.
	float duration = 0.0f; // duration in seconds. 
};