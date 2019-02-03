#pragma once

// File - NMaths.h
// Discription - Brings all of the Math headers together in one.

#include "NMath_Colour.h"
#include "NMath_Vector.h"

#include <Assimp/matrix4x4.h>

// Helper functions
inline DirectX::XMMATRIX convertToMatrix(aiMatrix4x4* mat)
{
	return DirectX::XMMATRIX
	(
		mat->a1, mat->a2, mat->a3, mat->a4,
		mat->b1, mat->b2, mat->b3, mat->b4,
		mat->c1, mat->c2, mat->c3, mat->c4,
		mat->d1, mat->d2, mat->d3, mat->d4
	);
}