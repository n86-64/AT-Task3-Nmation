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

struct NColliderCollisionData 
{
	NPhysicsComponent*   primary;
	NPhysicsComponent*   secondary;
	bool intersection = false;
	NMath::Vector3 mtv = NMath::Vector3(0.0f, 0.0f, 0.0f); // Minimum translation vector. (Use for physics calculations.)
};

class NColliderOBB 
{
public:
	NColliderOBB();

	// Set and update the position in global space. Hence this is updated each frame.
	void setPosition(NMath::Vector3  pos);
	void setSize(NMath::Vector3  newSize);

	void SetRotation(NMath::Vector3 objectOrientation);

	NColliderCollisionData isObjectColliding(NPhysicsComponent* thisComp, NPhysicsComponent* b);
	// TODO - Add information to get position and direction.

	NMath::Vector3  getAxes(int i) { return axes[i]; }
	NMath::Vector3  getDimenstions() { return dimenstions; }

	// Get information to perform SAT check.

private:
	NMath::Vector3   position; // The centre point of the box.
	NMath::Vector3   dimenstions = NMath::Vector3(1.0f, 1.0f, 1.0f); // The dimenstions of the box (Defines the width of the box on each axis.)
	NMath::Vector3   axes[NUMBER_OF_AXES];  // the axes values for the forward vectors.
	
	const NMath::Vector3   forward = NMath::Vector3(1.0f, 0.0f, 0.0f);
	const NMath::Vector3   up = NMath::Vector3(0.0f, 1.0f, 0.0f);
	const NMath::Vector3   right = NMath::Vector3(0.0f, 0.0f, 1.0f);

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