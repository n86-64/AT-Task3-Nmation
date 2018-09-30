#pragma once

// File - NMath_Colour.h
// Discription - Defines a wrapper for storing colour data. USed in clearing the screen. 

#include <DirectXColors.h>

namespace NMath 
{
	class Colour 
	{
	public:
		Colour(float r, float g, float b, float a);

		// get colour values.
		float r();
		float g();
		float b();
		float a();

		float* getColourArray();

		void setColourValues(float r, float g, float b, float a);

	private:
		DirectX::XMVECTORF32 colours;
	};
}