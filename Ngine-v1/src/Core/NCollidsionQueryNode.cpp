#include "NCollidsionQueryNode.h"

NCollisionQueryNode::NCollisionQueryNode()
{
}

NCollisionQueryNode::NCollisionQueryNode(NColliderBV_AABB newBox, NCollisionQueryNode* parent)
	:boundingBox(newBox),
	parentNode(parent)
{
}

void NCollisionQueryNode::setBoundingBox(NColliderBV_AABB volumeBox)
{
	boundingBox = volumeBox;
}

void NCollisionQueryNode::generateChildNodes()
{
	// Generate Some Child Nodes.
	childNodes.resize(CHILDNODE_COUNT);
	childNodes[0] = NCollisionQueryNode(NColliderBV_AABB(boundingBox.centre,  boundingBox.max), this);
	childNodes[1] = NCollisionQueryNode(NColliderBV_AABB(boundingBox.min,  boundingBox.centre), this);


	childNodes[2] = NCollisionQueryNode(NColliderBV_AABB(NMath::Vector3(boundingBox.centre.x(), boundingBox.min.y(), boundingBox.min.z()),  NMath::Vector3(boundingBox.max.x(), boundingBox.centre.y(), boundingBox.centre.z())), this);
	childNodes[3] = NCollisionQueryNode(NColliderBV_AABB(NMath::Vector3(boundingBox.centre.x(), boundingBox.min.y(), boundingBox.min.z()), NMath::Vector3(boundingBox.max.x(), boundingBox.centre.y(), boundingBox.centre.z())), this);
	childNodes[4] = NCollisionQueryNode(NColliderBV_AABB(NMath::Vector3(boundingBox.centre.x(), boundingBox.min.y(), boundingBox.min.z()), NMath::Vector3(boundingBox.max.x(), boundingBox.centre.y(), boundingBox.centre.z())), this);
	childNodes[5] = NCollisionQueryNode(NColliderBV_AABB(NMath::Vector3(boundingBox.centre.x(), boundingBox.min.y(), boundingBox.min.z()), NMath::Vector3(boundingBox.max.x(), boundingBox.centre.y(), boundingBox.centre.z())), this);
	childNodes[6] = NCollisionQueryNode(NColliderBV_AABB(NMath::Vector3(boundingBox.centre.x(), boundingBox.min.y(), boundingBox.min.z()), NMath::Vector3(boundingBox.max.x(), boundingBox.centre.y(), boundingBox.centre.z())), this);
	childNodes[7] = NCollisionQueryNode(NColliderBV_AABB(NMath::Vector3(boundingBox.centre.x(), boundingBox.min.y(), boundingBox.min.z()), NMath::Vector3(boundingBox.max.x(), boundingBox.centre.y(), boundingBox.centre.z())), this);
}

void NCollisionQueryNode::addObjectToNode(NPhysicsComponent * newObject)
{
	gameObjects.push_back(newObject);

	// TODO - Add a value so we dont subdivide too much.
	// There should be more than two objects in each node.
	if (gameObjects.size() > OBJECT_COUNT_THRESHOLD) 
	{
		// Generate the next set of child nodes.
		// Passing the objects of the scene into it.
		this->generateChildNodes();
	}
}
