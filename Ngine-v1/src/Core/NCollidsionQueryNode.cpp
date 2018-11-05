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
	childNodes[3] = NCollisionQueryNode(NColliderBV_AABB(NMath::Vector3(boundingBox.centre.x(), boundingBox.min.y(), boundingBox.centre.z()), NMath::Vector3(boundingBox.max.x(), boundingBox.centre.y(), boundingBox.max.z())), this);
	childNodes[4] = NCollisionQueryNode(NColliderBV_AABB(NMath::Vector3(boundingBox.min.x(), boundingBox.min.y(), boundingBox.centre.z()), NMath::Vector3(boundingBox.centre.x(), boundingBox.centre.y(), boundingBox.max.z())), this);
	childNodes[5] = NCollisionQueryNode(NColliderBV_AABB(NMath::Vector3(boundingBox.min.x(), boundingBox.centre.y(), boundingBox.min.z()), NMath::Vector3(boundingBox.centre.x(), boundingBox.max.y(), boundingBox.centre.z())), this); 
	childNodes[6] = NCollisionQueryNode(NColliderBV_AABB(NMath::Vector3(boundingBox.centre.x(), boundingBox.centre.y(), boundingBox.min.z()), NMath::Vector3(boundingBox.max.x(), boundingBox.max.y(), boundingBox.centre.z())), this);
	childNodes[7] = NCollisionQueryNode(NColliderBV_AABB(NMath::Vector3(boundingBox.min.x(), boundingBox.centre.y(), boundingBox.centre.z()), NMath::Vector3(boundingBox.centre.x(), boundingBox.max.y(), boundingBox.max.z())), this);

	// Add object refrences to the child nodes.
	for (auto object : gameObjects) 
	{
		for (int i = 0; i < CHILDNODE_COUNT; i++)
		{
			if (childNodes[i].boundingBox.isObjectColliding(object->getCollider()))
			{
				childNodes[i].addObjectToNode(object);
				gameObjects.erase(gameObjects.begin());
				break;
			}
		}
	}
}

void NCollisionQueryNode::addObjectToNode(NPhysicsComponent* newObject)
{
	gameObjects.push_back(newObject);

	// TODO - Add a value so we dont subdivide too much.
	// There should be more than two objects in each node.
	if ((gameObjects.size() > OBJECT_COUNT_THRESHOLD) && (childNodes.size() == 0)) 
	{
		// Generate the next set of child nodes.
		// Passing the objects of the scene into it.
		this->generateChildNodes();
	}
	else if(childNodes.size() > 0)
	{
		addObjectToChild();
	}

	// If there are child nodes then we add an object refrence to it.
}

void NCollisionQueryNode::runCollisionTest(std::vector<NColliderCollisionData>& collisionInfo)
{
	if (childNodes.size() != 0) 
	{
		for (auto& child : childNodes) 
		{
			child.runCollisionTest(collisionInfo);
		}
	}
	else if(gameObjects.size() > 1)
	{
		NPhysicsComponent* component;
		// Here we test the objects in the node.
		for (auto object : gameObjects) 
		{
			// Here we test each of the objects.
			evaluateCollision(object, collisionInfo);
		}
	}

	return;
}

void NCollisionQueryNode::clear()
{
	gameObjects.clear();
	childNodes.clear();
}

int NCollisionQueryNode::getChildNodeCount() const
{
	return childNodes.size();
}

int NCollisionQueryNode::getGameObjectCount() const
{
	return gameObjects.size();
}

void NCollisionQueryNode::evaluateCollision(NPhysicsComponent* comp, std::vector<NColliderCollisionData>& collisionInfo)
{
	NColliderCollisionData  data;
	for (auto object : gameObjects) 
	{
		if (object != comp) 
		{
			data = comp->getOBBCollider().isObjectColliding(comp, object);
			if (data.intersection) 
			{
				data.primary = comp;
				data.secondary = object;
				collisionInfo.push_back(data);
			}
		}
	}
}

void NCollisionQueryNode::addObjectToChild()
{
	NPhysicsComponent*   comp = gameObjects[gameObjects.size() - 1];

	for (int i = 0; i < CHILDNODE_COUNT; i++) 
	{
		if (childNodes[i].boundingBox.isObjectColliding(comp->getCollider())) 
		{
			childNodes[i].addObjectToNode(comp);
			gameObjects.pop_back();
			break;
		}
	}
}
