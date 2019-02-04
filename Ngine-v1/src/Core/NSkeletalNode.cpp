#include "NSkeletalNode.h"

void NSkeletalNode::AddBone(NSkeletalBone* bone)
{
	bones.emplace_back(bone);
}

void NSkeletalNode::assignMeshes(int newMesh)
{
	meshIndicies.emplace_back(newMesh);
}

void NSkeletalNode::addChildNodes(int* nodes, int count)
{
	children.reserve(count);
	for (int i = 0; i < count; i++) 
	{
		children.emplace_back(nodes[i]);
	}
}
