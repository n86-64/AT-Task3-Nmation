// File - NSkeletalMesh.h
// Description - A skeletal mesh object which combines various meshes with bones.


#pragma once
#include "NSkeletalNode.h"

class N3DMesh;
class NAnimation; 

class aiNode;

class NSkeletalMesh
{
public:
	NSkeletalMesh() = default;
	NSkeletalMesh(aiBone* bones, int size);

	void setName(std::string newName) { name = newName; }
	std::string getName() { return name; }

	void addAnimationBone(NSkeletalBone* newBone);
	void addanimationBoneAssimp(int meshIndex, aiBone* newBone);

	// Get the skeletal mesh. 
	int			   getBoneByName(std::string name);
	NSkeletalBone* getBoneByID(int i) { return skeleton[i].get(); }
	int			   getNumberOfBones() { return skeleton.size(); }

	int constructNode(aiNode* node, DirectX::XMMATRIX transform, int parent = -1);

	void addMesh(N3DMesh* newMesh);

	NSkeletalNode* retrieveNode(int nIndex) { return nodes[nIndex].get(); }
	NSkeletalNode* retrieveNodeByName(std::string name);
	N3DMesh*	   getMesh(int mIndex) { return meshes[mIndex]; }

	void		   setupBones();

public:
	int			   getNodeIndex(std::string name);

private:
	std::string name;

	// The skeleton and mesh data.
	std::vector<N3DMesh*>						  meshes;
	std::vector<std::unique_ptr<NSkeletalBone>>   skeleton;
	int skeletonSize = 0;

	std::vector<std::unique_ptr<NSkeletalNode>>   nodes;

	NAnimation*									  animation; 
};