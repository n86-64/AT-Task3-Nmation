// File - BasicVertex.hlsl
// Description - A passthrough 3D vertex shader with vertex skinning capibilitues.

// Input to the Vertex shader
struct VS_IN
{
	float4 inVector : POSITION;
	float4 normal   : NORMAL;
	float4 inColour : COLOR0;
	float2 inUV     : TEXCOORD0;
    uint4  bIndex   : BLENDINDICES;
    float4 bWeights : BLENDWEIGHT;
};


// 3D world matracies values.
cbuffer MVPConstants : register(b0)
{
	matrix mvMatrix;  // The model-view matrix. (model Matrix (psoition in the world) * view matrix (The cameras location))
	matrix projection;
};

cbuffer bufferBones : register(b1)
{
	matrix boneOffset[200]; // Obtains the transform for the bones.
};


struct VS_OUT
{
	float4 pos : SV_POSITION;
	float4 normal   : NORMAL;
	float4 outColour : COLOR0;
	float2 outUV : TEXCOORD0;
};


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
	output.normal = input.normal;

	return output;
}
