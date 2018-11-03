// File - BVAABB.h
// Discription - Defines a volume based bounding box.
// This is used to generate an octree for efficent collision testing.

#pragma once


#include "Helpers/NMath_Vector.h"

class NColliderBV_AABB 
{
public:
	NColliderBV_AABB() = default;
	NColliderBV_AABB(NMath::Vector3 minimum, NMath::Vector3 maximum);

private:
	NMath::Vector3   centre = NMath::Vector3(0.0f, 0.0f, 0.0f);

	NMath::Vector3   max = NMath::Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	NMath::Vector3   min = NMath::Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
};