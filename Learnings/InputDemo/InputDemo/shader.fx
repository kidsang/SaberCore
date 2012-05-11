cbuffer cbChangesPerFrame : register(b0)
{
	float4 col;
}

struct VS_Input
{
	float4 pos : POSITION;
	float2 tex0 : TEXCOORD0;
};

struct PS_Input
{
	float4 pos : SV_POSITION;
	float2 tex0 : TEXCOORD0;
};

PS_Input VS_Main(VS_Input vertex)
{
	return vertex;
}

float4 PS_Main(PS_Input frag) : SV_TARGET
{
	return col;
}