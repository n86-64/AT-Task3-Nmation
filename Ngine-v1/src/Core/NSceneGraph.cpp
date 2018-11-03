#include "NSceneGraph.h"

void NSceneGraph::generateGraph(std::vector<NPhysicsComponent*>& sceneContents)
{
	// Generate the scene graph here. 
	root.setBoundingBox(retrieveMinimalSceneBox(sceneContents));
	
	// Add the objects to the nodes. 
	for (auto object : sceneContents) 
	{
		root.addObjectToNode(object);
	}
}

NColliderBV_AABB NSceneGraph::retrieveMinimalSceneBox(std::vector<NPhysicsComponent*>&  sceneContents)
{
	NMath::Vector3    min = NMath::Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	NMath::Vector3    max = NMath::Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

	float minMag = min.getMagnitude();
	float maxMag = max.getMagnitude();

	NMath::Vector3 pMin;
	NMath::Vector3 pMax;

	// Get the minimum sized box for all objects in the scene. 
	for (int i = 0; i < sceneContents.size(); i++) 
	{
		pMin = (sceneContents[i])->getCollider().getColliderMinPoint();
		pMax = (sceneContents[i])->getCollider().getColliderMaxPoint();

		if (minMag > pMin.getMagnitude() || minMag == INFINITY) 
		{
			min = pMin;
			minMag = pMin.getMagnitude();
		}
		
		if (maxMag < pMax.getMagnitude() || maxMag == INFINITY)
		{
			max = pMax;
			maxMag = pMax.getMagnitude();
		}
	}

	return NColliderBV_AABB(min, max);
}
