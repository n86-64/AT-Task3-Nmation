#include "NColliderAABB.h"

NMath::Vector3 NColliderAABB::getColliderDimenstions() const
{
	return dimenstions;
}

void NColliderAABB::setColliderDimenstions(NMath::Vector3 dim)
{
	dimenstions = dim; 
}

NMath::Vector3 NColliderAABB::getColliderMinPoint()
{
	return position - dimenstions;
}

NMath::Vector3 NColliderAABB::getColliderMaxPoint()
{
	return position + dimenstions;
}
