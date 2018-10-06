// File - BasicVertex.hlsl
// Description - A passthrough 3D vertex shader.

// Input to the Vertex shader
struct VS_IN
{
    float3 inVector : POSITION;
    float4 inColour : COLOR0;
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
};


// The vertex shader.
// This will simply take the input vertex and then output 
VS_OUT main(VS_IN input)
{
    VS_OUT output;

    float4 vert = float4(input.inVector, 1);

    // convert the points to 3D space.
    vert = mul(vert, mvMatrix);
    vert = mul(vert, projection);

    output.pos = vert;

    //float4x4 viewProj = mul(world, view);
    //viewProj = mul(viewProj,  projection);
    //output.pos = mul(vert, viewProj); // Vertex multiplied by the worldViewProjMatrix.

    output.outColour = input.inColour;

    return output;
}
