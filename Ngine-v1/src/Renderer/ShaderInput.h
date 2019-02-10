// File - ShaderInput.h
// Description - Defines shader input types and loayouts for the renderer.

#pragma once

#include "Assimp/anim.h"
#include "Helpers/NMaths.h"
#include "Helpers/Direct3D.h"

// The Data structure for inputs to a material.
// TODO - Add support for textures and lighting. 
struct VertexInput
{
	DirectX::XMFLOAT4   pos;
	DirectX::XMFLOAT4	col;
	DirectX::XMFLOAT2	uv;
};

// Definitions for 3D projection. 
struct cBufferMatrix 
{
	DirectX::XMMATRIX    mvMatrix;
	DirectX::XMMATRIX    projMatrix;
};

struct cBufferBones 
{
	DirectX::XMMATRIX    boneOffsets;
};