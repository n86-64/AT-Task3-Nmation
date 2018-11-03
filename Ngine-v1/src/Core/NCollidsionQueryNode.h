// File - NCollisionQueryNode.h
// Description - A node of a collision Octree. Used to accelerate rendering of the scene.

#pragma once

#include <vector>
#include "BVAABB.h"
#include "NPhysicsComponent.h"

constexpr int CHILDNODE_COUNT = 8;
constexpr int OBJECT_COUNT_THRESHOLD = 2;

class NGameObject;

class NCollisionQueryNode 
{
public: 
	NCollisionQueryNode();
	NCollisionQueryNode(NColliderBV_AABB newBox, NCollisionQueryNode* parent);

	void setBoundingBox(NColliderBV_AABB  volumeBox);
	void generateChildNodes();

	void addObjectToNode(NPhysicsComponent* newObject);

	void clear();

private:
	// The child Nodes.
	NCollisionQueryNode* parentNode = nullptr;
	std::vector<NCollisionQueryNode>  childNodes;

	// The Node Bounding Box. Used for collision calculations.
	NColliderBV_AABB   boundingBox; 

	// The Objects associated with this node.
	std::vector<NPhysicsComponent*>   gameObjects;

	// For each node in the tree we then check the objects against eachother.
	// Providing they are not kinematic (That is they do not rispond to motion.)
};
