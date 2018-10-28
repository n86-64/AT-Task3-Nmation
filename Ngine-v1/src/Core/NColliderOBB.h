// File - NColliderOBB.h
// Description - Defines an Oriented bounding box. This is a box that is able to be rotated.
// Implements the seperating axis theorum.

#pragma once

#include "Helpers/NMath_Vector.h"


constexpr int NUMBER_OF_SEPERATING_AXES_PER_BOX = 9;
constexpr int NUMBER_OF_POINTS = 8;

// Here we store the projection info for each normal.
struct NColliderOBBProjection 
{
	float min;
	float max;
};

class NColliderOBB 
{
public:
	NColliderOBB() = default;

	// Set and update the position in global space. Hence this is updated each frame.
	void setPosition(NMath::Vector3  position);
	void setSize(NMath::Vector3  newSize);

	// TODO - Add information to get position and direction.

	// Get information to perform SAT check.
	int				getaxesCount()  { return NUMBER_OF_SEPERATING_AXES_PER_BOX; }
	int				getPointCount() { return NUMBER_OF_POINTS; }
	NMath::Vector3  getPoint(int i) { return points[i]; }
	NMath::Vector3  getAxis(int i)  { return axes[i]; }

private:
	NMath::Vector3   position;
	NMath::Vector3   dimenstions;

	// The number of points and sides.
	NMath::Vector3   points[NUMBER_OF_POINTS]; // Positions in global space.
	NMath::Vector3   axes[NUMBER_OF_SEPERATING_AXES_PER_BOX];  // The normalised axes to test against in global space.
	NMath::Vector3	 edgeNormals[NUMBER_OF_SEPERATING_AXES_PER_BOX];
};