// File - BasicPixel.hlsl
// Description - A passthrough 3D vertex shader.


// Textures and SamplerState.
Texture2D		matTex : register(t0);
SamplerState	matState : register(s0);

// Input from the vertex shader
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 outColour : COLOR0;
	float2 outUV : TEXCOORD0;
};

// The Pixel shader. just returns the input colour.
float4 main(PS_IN input) : SV_TARGET
{
    float4 outCol = input.outColour;
    return outCol;
}
