#include "NColliderAABB.h"
#include "BVAABB.h"

// Constructs a basic box with a max, min and centre.
NColliderBV_AABB::NColliderBV_AABB(NMath::Vector3 minimum, NMath::Vector3 maximum)
	:min(minimum),
	max(maximum)
{
	centre = ((maximum - minimum) / 2) + minimum;
}

bool NColliderBV_AABB::isObjectColliding(NColliderAABB& cBox)
{
	NMath::Vector3  cBoxMaxPoint = cBox.getColliderMaxPoint();
	NMath::Vector3  cBoxMinPoint = cBox.getColliderMinPoint();

	if (max.x() > cBoxMinPoint.x() && min.x() < cBoxMaxPoint.x()) 
	{
		if (max.y() > cBoxMinPoint.y() && min.y() < cBoxMaxPoint.y())
		{
			if (max.z() > cBoxMinPoint.z() && min.z() < cBoxMaxPoint.z())
			{
				return true;
			}
		}
	}

	return false;
}
