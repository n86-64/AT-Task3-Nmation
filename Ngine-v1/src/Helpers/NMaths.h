#pragma once

// File - NMaths.h
// Discription - Defines all math classes.

#include <DirectXMath.h>

// TODO - In thefuture consider a better wrapper. 

namespace NMath 
{
#ifdef _WIN32
	using NVector = DirectX::XMVECTOR;
#else 
	// ITS A UNIX SYSTEM!!!
#endif
};