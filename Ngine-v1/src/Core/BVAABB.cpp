#include "BVAABB.h"

// Constructs a basic box with a max, min and centre.
NColliderBV_AABB::NColliderBV_AABB(NMath::Vector3 minimum, NMath::Vector3 maximum)
	:min(minimum),
	max(maximum),
	centre(((maximum - minimum) /2) + minimum)
{
}
