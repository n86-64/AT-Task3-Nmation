// File - BasicVertex.hlsl
// Description - A passthrough 3D vertex shader with vertex skinning capibilitues.

// Input to the Vertex shader
struct VS_IN
{
	float4 inVector : POSITION;
	float4 inColour : COLOR0;
	float2 inUV     : TEXCOORD0;
};


// 3D world matracies values.
cbuffer MVPConstants : register(b0)
{
	matrix mvMatrix;  // The model-view matrix. (model Matrix (psoition in the world) * view matrix (The cameras location))
	matrix projection;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float4 outColour : COLOR0;
	float2 outUV : TEXCOORD0;
};

// Skeleton data for bones. 
cbuffer SkeletonBones : register(b1) 
{
	matrix boneOffsets;
}

// The vertex shader.
// This will simply take the input vertex and then output 
VS_OUT main(VS_IN input)
{
	VS_OUT output;

	float4 vert = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// convert the points to 3D space.
	vert = mul(input.inVector, mvMatrix);
	vert = mul(vert, projection);

	output.pos = vert;
	output.outColour = input.inColour;
	output.outUV = input.inUV;

	return output;
}
