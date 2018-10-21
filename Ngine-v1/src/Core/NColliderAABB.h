// File - NColliderAABB.h
// Description - Defines a basic AABB collider with corrisponding collision tests. 

#pragma once

#include "Helpers/NMaths.h"

class NColliderAABB 
{
public:
	NColliderAABB() = default;
	~NColliderAABB() = default;

	NMath::Vector3   getColliderDimenstions() const; 
	void setColliderDimenstions(NMath::Vector3  dim); 

	// Depricate.
	NMath::Vector3   getColliderMinPoint() const;
	NMath::Vector3   getColliderMaxPoint() const;


private:
	NMath::Vector3    dimenstions = NMath::Vector3(1.0f, 1.0f, 1.0f);
	
	// Depricate.
	NMath::Vector3    minPoint;
	NMath::Vector3    maxPoint;
};