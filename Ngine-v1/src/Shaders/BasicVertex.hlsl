// File - BasicVertex.hlsl
// Description - A passthrough 3D vertex shader.

// Input to the Vertex shader
struct VS_IN
{
    float4 inVector : POSITION;
    float4 inColour : COLOR0;
};


// 3D world matracies values.
cbuffer MVPConstants
{
    float4x4 view;
    float4x4 projection;
    float4x4 world;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 outColour : COLOR0;
};


// The vertex shader.
// This will simply take the input vertex and then output 
VS_OUT main(VS_IN input)
{
    VS_OUT output;

    float4x4 viewProj = mul(projection, view);
    viewProj = mul(viewProj, world);
    output.pos = mul(viewProj, input.inVector);

    output.outColour = float4(1.0f, 1.0f, 0.0f, 1.0f);

    return output;
}
