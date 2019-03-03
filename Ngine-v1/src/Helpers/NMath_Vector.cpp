#include "NMath_Vector.h"

NMath::Vector3::Vector3()
	:vector(DirectX::XMVectorSet(0.0f,0.0f,0.0f,1.0f))
{
}

NMath::Vector3::Vector3(float x, float y, float z)
	: vector(DirectX::XMVectorSet(x, y, z, 1.0f))
{
}

NMath::Vector3::Vector3(DirectX::XMVECTOR newVector)
	:vector(newVector)
{

}

NMath::Vector3::Vector3(aiVector3D newVector):
	vector(DirectX::XMVectorSet(newVector.x, newVector.y, newVector.z, 1.0f))
{
}

NMath::Vector3::Vector3(aiQuaternion newVector):
	vector(DirectX::XMVectorSet(newVector.x, newVector.y, newVector.z, newVector.w))
{
	
}

float NMath::Vector3::x()
{
	return DirectX::XMVectorGetX(vector);
}

float NMath::Vector3::y()
{
	return DirectX::XMVectorGetY(vector);
}

float NMath::Vector3::z()
{
	return DirectX::XMVectorGetZ(vector);
}

float NMath::Vector3::w()
{
	return DirectX::XMVectorGetW(vector);
}

void NMath::Vector3::setVectorValues(float x, float y, float z)
{
	vector = DirectX::XMVectorSet(x, y, z, 1.0f);
}

void NMath::Vector3::setX(float x)
{
	vector = DirectX::XMVectorSetX(vector,x);
}

void NMath::Vector3::setY(float y)
{
	vector = DirectX::XMVectorSetY(vector, y);
}

void NMath::Vector3::setZ(float z)
{
	vector = DirectX::XMVectorSetZ(vector, z);
}

DirectX::XMFLOAT4 NMath::Vector3::getRawVectorAsFloat()
{
	DirectX::XMFLOAT4 vec;
	vec.x = DirectX::XMVectorGetX(vector);
	vec.y = DirectX::XMVectorGetY(vector);
	vec.z = DirectX::XMVectorGetZ(vector);
	vec.w = DirectX::XMVectorGetW(vector);

	return vec;
}

DirectX::XMVECTOR NMath::Vector3::getRawVector() const
{
	return vector;
}

NMath::Vector3 NMath::Vector3::operator+(NMath::Vector3 vec)
{
	// Adds the vectors together so that w = 1.
	return NMath::Vector3(this->x() + vec.x(), this->y() + vec.y(), this->z() + vec.z());
}

NMath::Vector3 NMath::Vector3::operator-(NMath::Vector3 vec)
{
	return NMath::Vector3(this->x() - vec.x(), this->y() - vec.y(), this->z() - vec.z());
}

NMath::Vector3 NMath::Vector3::operator*(NMath::Vector3 vec)
{
	return NMath::Vector3(DirectX::XMVectorMultiply(this->vector, vec.getRawVector()));
}

NMath::Vector3 NMath::Vector3::operator/(float scalier)
{
	return NMath::Vector3(this->x() / scalier, this->y() /scalier, this->z() / scalier);
}

NMath::Vector3 NMath::Vector3::operator*(float scalier)
{
	return NMath::Vector3(this->x() * scalier, this->y() * scalier, this->z() * scalier);
}
