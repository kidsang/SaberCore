/*
    Beginning DirectX 11 Game Programming
    By Allen Sherrod and Wendy Jones

    Lighting Shader
*/


Texture2D colorMap : register( t0 );
SamplerState colorSampler : register( s0 );


cbuffer cbChangesEveryFrame : register( b0 )
{
    matrix worldMatrix;
};

cbuffer cbNeverChanges : register( b1 )
{
    matrix viewMatrix;
};

cbuffer cbChangeOnResize : register( b2 )
{
    matrix projMatrix;
};

cbuffer cbCameraData : register( b3 )
{
    float3 cameraPos;
};


struct VS_Input
{
    float4 pos  : POSITION;
    float2 tex0 : TEXCOORD0;
    float3 norm : NORMAL;
};

struct PS_Input
{
    float4 pos  : SV_POSITION;
    float2 tex0 : TEXCOORD0;
    float3 norm : NORMAL;
    float3 lightVec : TEXCOORD1;
    float3 viewVec : TEXCOORD2;
};


PS_Input VS_Main( VS_Input vertex )
{
    PS_Input vsOut = ( PS_Input )0;
    float4 worldPos = mul( vertex.pos, worldMatrix );
    vsOut.pos = mul( worldPos, viewMatrix );
    vsOut.pos = mul( vsOut.pos, projMatrix );

    vsOut.tex0 = vertex.tex0;
    vsOut.norm = mul( vertex.norm, (float3x3)worldMatrix );
    vsOut.norm = normalize( vsOut.norm );

    float3 lightPos = float3( 0.0f, 500.0f, 50.0f );
    vsOut.lightVec = normalize( lightPos - worldPos );

    vsOut.viewVec = normalize( cameraPos - worldPos );

    return vsOut;
}


float4 PS_Main( PS_Input frag ) : SV_TARGET
{
    float3 ambientColor = float3( 0.2f, 0.2f, 0.2f );
    float3 lightColor = float3( 0.7f, 0.7f, 0.7f );

    float3 lightVec = normalize( frag.lightVec );
    float3 normal = normalize( frag.norm );

    float diffuseTerm = clamp( dot( normal, lightVec ), 0.0f, 1.0f );
    float specularTerm = 0;

    if( diffuseTerm > 0.0f )
    {
        float3 viewVec = normalize( frag.viewVec );
        float3 halfVec = normalize( lightVec + viewVec );

        specularTerm = pow( saturate( dot( normal, halfVec ) ), 25 );
    }

    float3 finalColor = ambientColor + lightColor * diffuseTerm + lightColor * specularTerm;

    return float4( finalColor, 1.0f );
}