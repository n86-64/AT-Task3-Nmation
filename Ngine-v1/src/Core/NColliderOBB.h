// File - NColliderOBB.h
// Description - Defines an Oriented bounding box. This is a box that is able to be rotated.
// Implements the seperating axis theorum.

#pragma once

#include "Helpers/NMath_Vector.h"


constexpr int NUMBER_OF_SEPERATING_AXES_PER_BOX = 9;
constexpr int NUMBER_OF_POINTS = 8;

constexpr int NUMBER_OF_AXES = 3; 


class NPhysicsComponent;

// Here we store the projection info for each normal.
struct NColliderOBBProjection 
{
	float min;
	float max;
};

struct NColliderOBBCollision 
{
	bool intersection;
	NMath::Vector3 mtv; // Minimum translation vector. (Use for physics calculations.)
};

class NColliderOBB 
{
public:
	NColliderOBB() = default;

	// Set and update the position in global space. Hence this is updated each frame.
	void setPosition(NMath::Vector3  position);
	void setSize(NMath::Vector3  newSize);

	NColliderOBBCollision isObjectColliding(NPhysicsComponent* a, NPhysicsComponent* b);
	// TODO - Add information to get position and direction.

	// Get information to perform SAT check.

private:
	NMath::Vector3   position; // The centre point of the box.
	NMath::Vector3   dimenstions; // The dimenstions of the box (Defines the width of the box on each axis.)
	NMath::Vector3   axes[NUMBER_OF_AXES];  // the axes values for the forward vectors.
	
#pragma region DEPRECATED_STUFF
	NMath::Vector3	 edgeNormals[NUMBER_OF_SEPERATING_AXES_PER_BOX];
	NMath::Vector3   points[NUMBER_OF_POINTS]; // Positions in global space.

	// Unit points for the box. (May not be needed.)
	NMath::Vector3   colliderLocalVeritcies[8]
	{
		{ NMath::Vector3(-1.0f,  1.0f, -1.0f) },
		{ NMath::Vector3(1.0f,  1.0f, -1.0f) },
		{ NMath::Vector3(1.0f,  1.0f,  1.0f) },
		{ NMath::Vector3(-1.0f,  1.0f,  1.0f) },
		{ NMath::Vector3(-1.0f, -1.0f, -1.0f) },
		{ NMath::Vector3(1.0f, -1.0f, -1.0f)},
		{ NMath::Vector3(1.0f, -1.0f,  1.0f) },
		{ NMath::Vector3(-1.0f, -1.0f, 1.0f) },
	};

	void calculateEdges();
#pragma endregion

};