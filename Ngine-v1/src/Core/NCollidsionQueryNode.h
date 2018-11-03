// File - NCollisionQueryNode.h
// Description - A node of a collision Octree. Used to accelerate rendering of the scene.

#pragma once

#include <vector>
#include "BVAABB.h"
#include "NPhysicsComponent.h"

constexpr int CHILDNODE_COUNT = 8;

class NGameObject;


class NCollisionQueryNode 
{
public: 
	NCollisionQueryNode() = default;

	void setBoundingBox(NColliderBV_AABB  volumeBox);
	bool objectCollideWithNode(NPhysicsComponent* a);


private:
	// The child Nodes.
	NCollisionQueryNode* ChildNodes[CHILDNODE_COUNT];

	// The Node Bounding Box. Used for collision calculations.
	NColliderBV_AABB   boundingBox; 

	// The Objects associated with this node.
	std::vector<NPhysicsComponent*>   gameObjects;

	// For each node in the tree we then check the objects against eachother.
	// Providing they are not kinematic (That is they do not rispond to motion.)
};
