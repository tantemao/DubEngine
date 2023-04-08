
cbuffer TransformBuffer : register(b0)
{
	matrix world;
	matrix wvp;
	float3 viewPosition;
}

cbuffer LightBuffer : register(b1)
{
	float3 lightDirection;
	float4 lightAmbient;
	float4 lightDiffuse;
	float4 lightSpecular;
}

Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD2;
	float2 diffuse: TEXCOORD1;
};


VS_OUTPUT vertexMain(
	float4 Position: POSITION0,
	float2 TexCoord : TEXCOORD0,
	float2 diffuse : TEXCOORD1,
	float3 Normal : NORMAL0)
{
	VS_OUTPUT Output;

	// calculate light vector
	float3 N = normalize(Normal);
	float3 L = normalize(mLightPos - Position.xyz);

	// Calculate diffuse component
	diffuse = max(dot(N, L), 0);

	// Shading offset
	float offset = 0.1f;

	//Subtract the offset and clamp the texture to 0
	diffuse = clamp(diffuse + offset, 0, 1);

	Output.Position = mul(Position, mWorldViewProj);
	Output.diffuse = diffuse;
	Output.TexCoord = TexCoord;
	return(Output);
}

sampler2D tex0 : register(s0);
sampler1D diffuseRamp : register(s2);

float4 pixelMain(
	float2 TexCoord:  	TEXCOORD0,
	float2 diffuseIn : TEXCOORD1
) : COLOR0
{
	float4 color = float4(1,1,1,1);
	float4 diffuse = float4(0.8f, 0.8f, 0.8f, 1.0f);
	// Step functions from textures
	diffuseIn = tex1D(diffuseRamp, diffuseIn).x;



	color = (diffuse * diffuseIn);
	float4 col = tex2D(tex0, TexCoord);
	col *= 2;
	return(color * col);

}