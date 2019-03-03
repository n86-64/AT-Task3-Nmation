// File - NAnimationNode.h
// Discription - Discribes the animation of a node in the object.

#pragma once

#include "Helpers/NMaths.h"
#include <vector>

#include "Assimp/anim.h"

struct NAnimationKey 
{
	NAnimationKey() {};
	NAnimationKey(aiVectorKey& key) { time = key.mTime; value = NMath::Vector3(key.mValue); }
	NAnimationKey(aiQuatKey& key) { time = key.mTime; value = NMath::Vector3(key.mValue); }

	float time;
	NMath::Vector3 value;
};


class NAnimationNode 
{
public:
	NAnimationNode() = default;
	NAnimationNode(aiNodeAnim* animNode);


	std::string name;

	std::vector<NAnimationKey>  translation;
	std::vector<NAnimationKey>  rotation;
	std::vector<NAnimationKey>  scale;

private:
	std::string nodeAffected = "";

	//std::vector<NAnimationKey>  translation;
	//std::vector<NAnimationKey>  rotation;
	//std::vector<NAnimationKey>  scale;
};