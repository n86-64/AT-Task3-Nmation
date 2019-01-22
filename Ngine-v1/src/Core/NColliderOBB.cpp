#include "NPhysicsComponent.h"
#include "NColliderOBB.h"

constexpr float EPSILON = 0.000000001f;

NColliderOBB::NColliderOBB()
{
	axes[0] = forward;
	axes[1] = up;
	axes[2] = right;
}

void NColliderOBB::setPosition(NMath::Vector3 pos)
{
	// Here we will set the position of the collider points.
	// Position is equal to the centre.

	// Here we need to reset the points.
	this->position = pos;
}

void NColliderOBB::setSize(NMath::Vector3 newSize)
{
	// Here we will resize the box and recalculate the points.
	dimenstions = newSize;
}

void NColliderOBB::SetRotation(NMath::Vector3 objectOrientation)
{
	axes[0] = DirectX::XMVector3Rotate(forward.getRawVector(), objectOrientation.getRawVector());
	axes[1] = DirectX::XMVector3Rotate(up.getRawVector(), objectOrientation.getRawVector());
	axes[2] = DirectX::XMVector3Rotate(right.getRawVector(), objectOrientation.getRawVector());
}

NColliderCollisionData NColliderOBB::isObjectColliding(NPhysicsComponent* thisComp, NPhysicsComponent* b)
{
	NColliderCollisionData   data;
	NColliderOBB&  OBB = b->getOBBCollider();
	
	// Here we perform the check.
	float rA, rB; // Distances to edge on each axis.
	float T = INFINITY; // the distance along a perticular axis.
	float mag = 0.0f;
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
			AbsRotation(i, j) = abs(AbsRotation(i, j)) + EPSILON;
		}
	}

	NMath::Vector3  t = OBB.position - this->position;
	t = NMath::Vector3(
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(t.getRawVector(), this->axes[0].getRawVector())),
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(t.getRawVector(), this->axes[1].getRawVector())),
		DirectX::XMVectorGetX(DirectX::XMVector3Dot(t.getRawVector(), this->axes[2].getRawVector()))
	);
	
	for (int i = 0; i < 3; i++) 
	{
		rA = dimenstions.value(i);
		rB = (OBB.getDimenstions().value(0) * AbsRotation(i, 0)) + (OBB.getDimenstions().value(1) * AbsRotation(i, 1)) + (OBB.getDimenstions().value(2) * AbsRotation(i, 2));
		if (abs(t.value(i) > rA + rB)) { data.intersection = false; return data; }
		else { mag = t.value(i); }

		if (mag < T) 
		{
			data.mtv = axes[i];
			T = mag;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		// Its failing here.
		rA = (dimenstions.value(0) * AbsRotation(0, i)) + (dimenstions.value(1) * AbsRotation(1, i)) + (dimenstions.value(2) * AbsRotation(2, i));
		rB = OBB.getDimenstions().value(i);
		if (abs(t.value(0) * Rotation(0, i) + t.value(1) * Rotation(1,i) + t.value(2) * Rotation(2, i)) > rA + rB) { data.intersection = false; return data; }
		else { mag = t.value(0) * Rotation(0, i) + t.value(1) * Rotation(1, i) + t.value(2) * Rotation(2, i); }

		if (mag < T)
		{
			data.mtv = axes[i];
			T = mag;
		}
	}

	rA = (dimenstions.value(1) * AbsRotation(2, 0)) + (dimenstions.value(2) * AbsRotation(1, 0));
	rB = (OBB.getDimenstions().value(1) * AbsRotation(0, 2)) + (dimenstions.value(2) * AbsRotation(0, 1));
	if (abs(t.value(2) * Rotation(1, 0) - t.value(1) * Rotation(2, 0)) > rA + rB) { data.intersection = false; return data; }
	else { mag = t.value(2) * Rotation(1, 0) - t.value(1) * Rotation(2, 0); }

	if (mag < T)
	{
		data.mtv = axes[0];
		T = mag;
	}

	rA = (dimenstions.value(1) * AbsRotation(2, 1)) + (dimenstions.value(2) * AbsRotation(1, 1));
	rB = (OBB.getDimenstions().value(0) * AbsRotation(0, 2)) + (dimenstions.value(2) * AbsRotation(0, 0));
	if (abs(t.value(2) * Rotation(1, 1) - t.value(1) * Rotation(2, 1)) > rA + rB) { data.intersection = false; return data; }
	else { mag = t.value(2) * Rotation(1, 1) - t.value(1) * Rotation(2, 1); }

	if (mag < T)
	{
		data.mtv = axes[1];
		T = mag;
	}

	rA = (dimenstions.value(1) * AbsRotation(2, 2)) + (dimenstions.value(2) * AbsRotation(1, 2));
	rB = (OBB.getDimenstions().value(0) * AbsRotation(0, 1)) + (dimenstions.value(1) * AbsRotation(0, 0));
	if (abs(t.value(2) * Rotation(1, 2) - t.value(1) * Rotation(2, 2)) > rA + rB) { data.intersection = false; return data; }
	else { mag = t.value(2) * Rotation(1, 2) - t.value(1) * Rotation(2, 2); }

	if (mag < T)
	{
		data.mtv = axes[2];
		T = mag;
	}

	rA = (dimenstions.value(0) * AbsRotation(2, 0)) + (dimenstions.value(2) * AbsRotation(0, 0));
	rB = (OBB.getDimenstions().value(1) * AbsRotation(1, 2)) + (dimenstions.value(2) * AbsRotation(1, 1));
	if (abs(t.value(0) * Rotation(2, 1) - t.value(2) * Rotation(0, 0)) > rA + rB) { data.intersection = false; return data; }
	else { mag = t.value(0) * Rotation(2, 1) - t.value(2) * Rotation(0, 0); }

	if (mag < T)
	{
		data.mtv = axes[0];
		T = mag;
	}

	rA = (dimenstions.value(0) * AbsRotation(2, 1)) + (dimenstions.value(2) * AbsRotation(0, 1));
	rB = (OBB.getDimenstions().value(0) * AbsRotation(1, 2)) + (dimenstions.value(2) * AbsRotation(1, 0));
	if (abs(t.value(0) * Rotation(2, 1) - t.value(2) * Rotation(0, 1)) > rA + rB) { data.intersection = false; return data; }
	else { mag = t.value(0) * Rotation(2, 1) - t.value(2) * Rotation(0, 1); }

	if (mag < T)
	{
		data.mtv = axes[1];
		T = mag;
	}

	rA = (dimenstions.value(0) * AbsRotation(2, 2)) + (dimenstions.value(2) * AbsRotation(0, 2));
	rB = (OBB.getDimenstions().value(0) * AbsRotation(1, 1)) + (dimenstions.value(1) * AbsRotation(1, 0));
	if (abs(t.value(0) * Rotation(2, 2) - t.value(2) * Rotation(0, 2)) > rA + rB) { data.intersection = false; return data; }
	else { mag = t.value(0) * Rotation(2, 2) - t.value(2) * Rotation(0, 2); }

	if (mag < T)
	{
		data.mtv = axes[2];
		T = mag;
	}

	rA = (dimenstions.value(0) * AbsRotation(1, 0)) + (dimenstions.value(1) * AbsRotation(0, 0));
	rB = (OBB.getDimenstions().value(1) * AbsRotation(2, 2)) + (dimenstions.value(2) * AbsRotation(2, 1));
	if (abs(t.value(1) * Rotation(0, 0) - t.value(0) * Rotation(1, 0)) > rA + rB) { data.intersection = false; return data; }
	else { mag = t.value(1) * Rotation(0, 0) - t.value(0) * Rotation(1, 0); }

	if (mag < T)
	{
		data.mtv = axes[0];
		T = mag;
	}

	rA = (dimenstions.value(0) * AbsRotation(1, 1)) + (dimenstions.value(1) * AbsRotation(0, 1));
	rB = (OBB.getDimenstions().value(0) * AbsRotation(2, 2)) + (dimenstions.value(2) * AbsRotation(2, 0));
	if (abs(t.value(1) * Rotation(0, 1) - t.value(0) * Rotation(1, 1)) > rA + rB) { data.intersection = false; return data; }
	else { mag = t.value(1) * Rotation(0, 1) - t.value(0) * Rotation(1, 1); }

	if (mag < T)
	{
		data.mtv = axes[1];
		T = mag;
	}

	rA = (dimenstions.value(0) * AbsRotation(1, 2)) + (dimenstions.value(1) * AbsRotation(0, 2));
	rB = (OBB.getDimenstions().value(0) * AbsRotation(2, 1)) + (dimenstions.value(1) * AbsRotation(2, 0));
	if (abs(t.value(1) * Rotation(0, 2) - t.value(0) * Rotation(1, 2)) > rA + rB) { data.intersection = false; return data; }
	else { mag = t.value(1) * Rotation(0, 2) - t.value(0) * Rotation(1, 2); }

	if (mag < T)
	{
		data.mtv = axes[2];
		T = mag;
	}


    data.intersection = true;
	data.mtv = data.mtv * T;


	return data;
}

