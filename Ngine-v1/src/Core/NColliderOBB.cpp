#include "NPhysicsComponent.h"
#include "NColliderOBB.h"

constexpr float ELIPSION = 1e-8;

void NColliderOBB::setPosition(NMath::Vector3 position)
{
	// Here we will set the position of the collider points.
	// Position is equal to the centre.

	// Here we need to reset the points.
}

void NColliderOBB::setSize(NMath::Vector3 newSize)
{
	// Here we will resize the box and recalculate the points.

}

NColliderCollisionData NColliderOBB::isObjectColliding(NPhysicsComponent* thisComp, NPhysicsComponent* b)
{
	NColliderCollisionData   data;
	NColliderOBB&  OBB = b->getOBBCollider();
	
	// Here we perform the check.
	float rA, rB; // Distances to edge on each axis.
	DirectX::XMMATRIX   rotation, AbsRotation;

	// Here we compute the orientation of the boxes. 
	rotation = DirectX::XMMatrixSet
	(
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[0].getRawVector(), OBB.axes[0].getRawVector())), DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[0].getRawVector(), OBB.axes[1].getRawVector())), DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[0].getRawVector(), OBB.axes[2].getRawVector())), 0.0f,
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[1].getRawVector(), OBB.axes[0].getRawVector())), DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[1].getRawVector(), OBB.axes[1].getRawVector())), DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[1].getRawVector(), OBB.axes[2].getRawVector())), 0.0f,
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[2].getRawVector(), OBB.axes[0].getRawVector())), DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[2].getRawVector(), OBB.axes[1].getRawVector())), DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[2].getRawVector(), OBB.axes[2].getRawVector())), 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);
	
	DirectX::XMFLOAT3X3  matricies;
	DirectX::XMStoreFloat3x3(&matricies, rotation);

	// Transforms the object into local space.
	matricies._11 = abs(matricies._11) + ELIPSION;
	matricies._12 = abs(matricies._12) + ELIPSION;
	matricies._13 = abs(matricies._13) + ELIPSION;
	matricies._21 = abs(matricies._21) + ELIPSION;
	matricies._22 = abs(matricies._22) + ELIPSION;
	matricies._23 = abs(matricies._23) + ELIPSION;
	matricies._31 = abs(matricies._31) + ELIPSION;
	matricies._32 = abs(matricies._32) + ELIPSION;
	matricies._33 = abs(matricies._33) + ELIPSION;

	NMath::Vector3  t = OBB.position - this->position;
	t = NMath::Vector3(
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(t.getRawVector(), this->axes[0].getRawVector())),
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(t.getRawVector(), this->axes[2].getRawVector())),
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(t.getRawVector(), this->axes[2].getRawVector()))
	);



	
	return data;
}

