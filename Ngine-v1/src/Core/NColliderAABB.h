// File - NColliderAABB.h
// Description - Defines a basic AABB collider with corrisponding collision tests. 

#pragma once

#include "Helpers/NMaths.h"

class NColliderAABB 
{
public:
	NColliderAABB() = default;
	~NColliderAABB() = default;

	void setPosition(NMath::Vector3  pos) { position = pos; };

	NMath::Vector3   getColliderDimenstions() const; 
	void setColliderDimenstions(NMath::Vector3  dim); 

	// Used for the Bounding Volume.
	NMath::Vector3   getColliderMinPoint();
	NMath::Vector3   getColliderMaxPoint();

private:
	NMath::Vector3    position;
	NMath::Vector3    dimenstions = NMath::Vector3(1.0f, 1.0f, 1.0f);
	
	// Depricate.
	NMath::Vector3    minPoint;
	NMath::Vector3    maxPoint;
};