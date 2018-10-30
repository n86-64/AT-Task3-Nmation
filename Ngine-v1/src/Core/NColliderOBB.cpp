#include "NPhysicsComponent.h"
#include "NColliderOBB.h"

constexpr float ELIPSION = 1e-8;

NColliderOBB::NColliderOBB()
{
	axes[0] = NMath::Vector3(1.0f, 0.0f, 0.0f);
	axes[1] = NMath::Vector3(0.0f, 1.0f, 0.0f);
	axes[2] = NMath::Vector3(0.0f, 0.0f, 1.0f);
}

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
	DirectX::XMMATRIX   tRotation; // rotate the object into our space.

	// Here we compute the orientation of the boxes. 
	tRotation = DirectX::XMMatrixSet
	(
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[0].getRawVector(), OBB.axes[0].getRawVector())), DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[0].getRawVector(), OBB.axes[1].getRawVector())), DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[0].getRawVector(), OBB.axes[2].getRawVector())), 0.0f,
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[1].getRawVector(), OBB.axes[0].getRawVector())), DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[1].getRawVector(), OBB.axes[1].getRawVector())), DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[1].getRawVector(), OBB.axes[2].getRawVector())), 0.0f,
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[2].getRawVector(), OBB.axes[0].getRawVector())), DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[2].getRawVector(), OBB.axes[1].getRawVector())), DirectX::XMVectorGetX(DirectX::XMVector3Dot(axes[2].getRawVector(), OBB.axes[2].getRawVector())), 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);
	
	DirectX::XMFLOAT3X3  Rotation;
	DirectX::XMStoreFloat3x3(&Rotation, tRotation);
	DirectX::XMFLOAT3X3  AbsRotation = Rotation;

	// provides an absolute rotation matrix.
	for (int i = 0; i < 3; i++) 
	{
		for (int j = 0; j < 3; j++) 
		{
			AbsRotation(i, j) = abs(AbsRotation(i, j));
		}
	}

	NMath::Vector3  t = OBB.position - this->position;
	t = NMath::Vector3(
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(t.getRawVector(), this->axes[0].getRawVector())),
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(t.getRawVector(), this->axes[2].getRawVector())),
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(t.getRawVector(), this->axes[2].getRawVector()))
	);
	
	for (int i = 0; i < 3; i++) 
	{
		rA = dimenstions.value(i);
		rB = (OBB.getDimenstions().value(0) * AbsRotation(i, 0)) + (OBB.getDimenstions().value(1) * AbsRotation(i, 1)) + (OBB.getDimenstions().value(2) * AbsRotation(i, 2));
		if (abs(t.value(i) > rA + rB)) { data.intersection = false; return data; }
	}

	for (int i = 0; i < 3; i++)
	{
		rA = (dimenstions.value(0) * AbsRotation(0, i)) + (dimenstions.value(1) * AbsRotation(1, i)) + (dimenstions.value(2) * AbsRotation(2, i));
		rB = OBB.getDimenstions().value(i);
		if (abs(t.value(0) * Rotation(0, i) + t.value(1) * Rotation(1,i) + t.value(2) * Rotation(2, i)) > rA + rB) { data.intersection = false; return data; }
	}

	rA = (dimenstions.value(1) * AbsRotation(2, 0)) + (dimenstions.value(2) * AbsRotation(1, 0));
	rB = (OBB.getDimenstions.value(1) * AbsRotation(0, 2)) + (dimenstions.value(2) * AbsRotation(0, 1));
	if (abs(t.value(2) * Rotation(1, 0) - t.value(1) * Rotation(2, 0)) > rA + rB) { data.intersection = false; return data; }

	rA = (dimenstions.value(1) * AbsRotation(2, 1)) + (dimenstions.value(2) * AbsRotation(1, 1));
	rB = (OBB.getDimenstions.value(0) * AbsRotation(0, 2)) + (dimenstions.value(2) * AbsRotation(0, 0));
	if (abs(t.value(2) * Rotation(1, 1) - t.value(1) * Rotation(2, 1)) > rA + rB) { data.intersection = false; return data; }

	rA = (dimenstions.value(1) * AbsRotation(2, 2)) + (dimenstions.value(2) * AbsRotation(1, 2));
	rB = (OBB.getDimenstions.value(0) * AbsRotation(0, 1)) + (dimenstions.value(1) * AbsRotation(0, 0));
	if (abs(t.value(2) * Rotation(1, 2) - t.value(1) * Rotation(2, 2)) > rA + rB) { data.intersection = false; return data; }

	rA = (dimenstions.value(0) * AbsRotation(2, 0)) + (dimenstions.value(2) * AbsRotation(0, 0));
	rB = (OBB.getDimenstions.value(1) * AbsRotation(1, 2)) + (dimenstions.value(2) * AbsRotation(1, 1));
	if (abs(t.value(0) * Rotation(2, 1) - t.value(2) * Rotation(0, 0)) > rA + rB) { data.intersection = false; return data; }


	rA = (dimenstions.value(0) * AbsRotation(2, 1)) + (dimenstions.value(2) * AbsRotation(0, 1));
	rB = (OBB.getDimenstions.value(0) * AbsRotation(1, 2)) + (dimenstions.value(2) * AbsRotation(1, 0));
	if (abs(t.value(0) * Rotation(2, 1) - t.value(2) * Rotation(0, 1)) > rA + rB) { data.intersection = false; return data; }



	rA = (dimenstions.value(0) * AbsRotation(2, 2)) + (dimenstions.value(2) * AbsRotation(0, 2));
	rB = (OBB.getDimenstions.value(0) * AbsRotation(1, 1)) + (dimenstions.value(1) * AbsRotation(1, 0));
	if (abs(t.value(0) * Rotation(2, 2) - t.value(2) * Rotation(0, 2)) > rA + rB) { data.intersection = false; return data; }




	rA = (dimenstions.value(0) * AbsRotation(1, 0)) + (dimenstions.value(1) * AbsRotation(0, 0));
	rB = (OBB.getDimenstions.value(1) * AbsRotation(2, 2)) + (dimenstions.value(2) * AbsRotation(2, 1));
	if (abs(t.value(1) * Rotation(0, 0) - t.value(0) * Rotation(1, 0)) > rA + rB) { data.intersection = false; return data; }


	rA = (dimenstions.value(0) * AbsRotation(1, 1)) + (dimenstions.value(1) * AbsRotation(0, 1));
	rB = (OBB.getDimenstions.value(0) * AbsRotation(2, 2)) + (dimenstions.value(2) * AbsRotation(2, 0));
	if (abs(t.value(1) * Rotation(0, 1) - t.value(0) * Rotation(1, 1)) > rA + rB) { data.intersection = false; return data; }


	rA = (dimenstions.value(0) * AbsRotation(1, 2)) + (dimenstions.value(1) * AbsRotation(0, 2));
	rB = (OBB.getDimenstions.value(0) * AbsRotation(2, 1)) + (dimenstions.value(1) * AbsRotation(2, 0));
	if (abs(t.value(1) * Rotation(0, 2) - t.value(0) * Rotation(1, 2)) > rA + rB) { data.intersection = false; return data; }

	data.intersection = true;
	return data;
}

