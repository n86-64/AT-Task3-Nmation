#include "BVAABB.h"

// Constructs a basic 
NColliderBV_AABB::NColliderBV_AABB(NMath::Vector3 minimum, NMath::Vector3 maximum)
	:min(minimum),
	max(maximum),
	centre((maximum - minimum) /2)
{
}
