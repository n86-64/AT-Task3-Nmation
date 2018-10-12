#include "NMath_Colour.h"

NMath::Colour::Colour(float r, float g, float b, float a)
{
	setColourValues(r, g, b, a);
}

float NMath::Colour::r()
{
	return colours.f[0];
}

float NMath::Colour::g()
{
	return colours.f[1];
}

float NMath::Colour::b()
{
	return colours.f[2];
}

float NMath::Colour::a()
{
	return colours.f[3];
}

float* NMath::Colour::getColourArray()
{
	return colours.f;
}

void NMath::Colour::setColourValues(float r, float g, float b, float a)
{
	colours.f[0] = r;
	colours.f[1] = g;
	colours.f[2] = b;
	colours.f[3] = a;
}
