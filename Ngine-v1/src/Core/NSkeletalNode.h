// File - NSkeletalNode
// Discription - Represents a portion of a herarchical mesh. 

#pragma once

#include <memory>
#include <vector>

#include "Helpers/NMaths.h"
#include "NAnimationBones.h"

class NSkeletalNode 
{
public:
	NSkeletalNode() = default;

	void AddBone(NSkeletalBone* bone);
	void assignMeshes(int newMesh);

	void setMeshSize(int nMeshes) { meshIndicies.reserve(nMeshes); }

	void setModelMatrix(DirectX::XMMATRIX& mat) { modelMatrix = mat; }
	DirectX::XMMATRIX getModelMatrix() { return modelMatrix;  }

	void setParent(int pIndex) { parent = pIndex; }
	void addChildNodes(int* nodes, int count);
	void addChild(int cIndex) { children.emplace_back(cIndex); }

	std::vector<int>& getModelIndicies() { return meshIndicies; }
	std::vector<int>& getChildren() { return children; }

private:

	DirectX::XMMATRIX								modelMatrix = DirectX::XMMatrixIdentity();

	int				      							parent;
	std::vector<int>								children;

	std::vector<int>								meshIndicies;
	std::vector<std::unique_ptr<NSkeletalBone>>		bones;
};