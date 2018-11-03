// File - NSceneGraph.h
// Discription - Stores the spacial data structure for performing collisions. 

#pragma once

#include <memory>
#include "NCollidsionQueryNode.h"

class NSceneGraph 
{
public:
	NSceneGraph() = default;

	// Generate the scene graph from the objects in the scene. 
	void generateGraph(std::vector<NPhysicsComponent*>&  sceneContents);

private:
	NColliderBV_AABB retrieveMinimalSceneBox(std::vector<NPhysicsComponent*>&  sceneContents);

private:
	NCollisionQueryNode  root; // Root node for the scene. Set based on the 
};


// Idea for Octree optimisation:

// Generate Octree to one level.
// If NumberOfObject in a Node > 2
//   Subdivide()
// else 
//   Stop and perform checks.
//
// This should be done when generating each node. 

