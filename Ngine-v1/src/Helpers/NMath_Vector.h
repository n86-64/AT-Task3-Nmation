#pragma once

// File - NMath_Vector.h
// Discription - Defines a set of vector types which can be used.

#include <DirectXMath.h>
#include "Assimp/vector3.h"
#include "Assimp/quaternion.h"

namespace NMath 
{
	// A 3 dimenstional vector.
	class Vector3
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(DirectX::XMVECTOR newVector);
		Vector3(aiVector3D newVector);
		Vector3(aiQuaternion newVector);

		float x();
		float y();
		float z();
		float w();

		void setVectorValues(float x, float y, float z);
		void setX(float x);
		void setY(float y);
		void setZ(float z);

		DirectX::XMFLOAT4  getRawVectorAsFloat();
		DirectX::XMVECTOR  getRawVector() const;

		// TODO - Add operator overloads for performing vector operations.
		NMath::Vector3 operator+(NMath::Vector3 vec);
		NMath::Vector3 operator-(NMath::Vector3 vec);
		NMath::Vector3 operator*(NMath::Vector3 vec);
		NMath::Vector3 operator/(float scalier);
		NMath::Vector3 operator*(float scalier);

		float getMagnitude() { return DirectX::XMVectorGetX(DirectX::XMVector3Length(vector)); }
		NMath::Vector3 normalise() { return DirectX::XMVector3Normalize(vector); }
		

		// public vector constants.
		float value(int i) { return DirectX::XMVectorGetByIndex(vector, i); }


	private:
		DirectX::XMVECTOR  vector;
	};
}