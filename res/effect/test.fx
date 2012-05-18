/*
    Beginning DirectX 11 Game Programming
    By Allen Sherrod and Wendy Jones

    Color Inversion Shader
*/


Texture2D colorMap : register( t0 );
SamplerState colorSampler : register( s0 );

struct VS_Input
{
    float4 pos  : POSITION;
    float2 tex0 : TEXCOORD0;
	float4 norm : NORMAL;
};

struct PS_Input
{
    float4 pos  : SV_POSITION;
    float2 tex0 : TEXCOORD0;
	float4 norm : NORMAL;
};


PS_Input VS_Main( VS_Input vertex )
{
    PS_Input vsOut = ( PS_Input )0;

    return vsOut;
}


float4 PS_Main( PS_Input frag ) : SV_TARGET
{
    return float4(1, 0, 0, 1);
}

technique11 TestTechnique
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
    }
}