#include "NMath_Vector.h"

NMath::Vector3::Vector3()
	:vector(DirectX::XMVectorSet(0.0f,0.0f,0.0f,1.0f))
{
}

NMath::Vector3::Vector3(float x, float y, float z)
	: vector(DirectX::XMVectorSet(x, y, z, 1.0f))
{
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

void NMath::Vector3::setz(float z)
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

DirectX::XMVECTOR NMath::Vector3::getRawVector()
{
	return vector;
}
