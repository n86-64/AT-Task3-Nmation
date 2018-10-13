#pragma once

// File - NMath_Vector.h
// Discription - Defines a set of vector types which can be used.

#include <DirectXMath.h>

namespace NMath 
{
	// A 3 dimenstional vector.
	class Vector3
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);

		float x();
		float y();
		float z();

		void setVectorValues(float x, float y, float z);
		void setX(float x);
		void setY(float y);
		void setZ(float z);

		DirectX::XMFLOAT4  getRawVectorAsFloat();
		DirectX::XMVECTOR  getRawVector();

		// TODO - Add operator overloads for performing vector operations.
		NMath::Vector3 operator+(NMath::Vector3 vec);
		NMath::Vector3 operator-(NMath::Vector3 vec);

		// public vector constants.



	private:
		DirectX::XMVECTOR  vector;
	};
}