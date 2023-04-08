// Description: Simple shader that does transform.
cbuffer TransformBuffer : register(b0)
{
	matrix world;
	matrix vp;
	float3 viewPosition;
	float3 forces;
	float currentLayer;
	float maxLength;
}

cbuffer LightBuffer : register(b1)
{
	float3 lightDirection;
	float4 lightAmbient;
	float4 lightDiffuse;
	float4 lightSpecular;
}

cbuffer FurBuffer : register(b2)
{
	int width;
	int height;
	float furLength[64];
}

Texture2D diffuseMap : register(t0);
Texture2D furMap : register(t1);

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
	float4 diff : COLOR;
	float3 worldNormal : NORMAL;
	float3 dirToLight : TEXCOORD0;
	float3 dirToView : TEXCOORD1;
	float2 texCoord : TEXCOORD2;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	float3 localPosition = input.position + input.normal * currentLayer * maxLength;
	output.position = mul(float4(localPosition, 1.0f), world);
	output.position.xyz += (forces * pow(currentLayer, 3));
	output.position = mul(output.position, vp);
	
	float3 worldNorm = normalize(mul(input.normal, (float3x3)world));
	output.diff = dot(worldNorm, -lightDirection);
	output.diff.a = 1.0f;

	output.worldNormal = mul(input.normal, (float3x3)world);
	output.dirToLight = -lightDirection;
	output.dirToView = normalize(viewPosition - mul(float4(localPosition, 1.0f), world).xyz);
	output.texCoord = input.texCoord;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 n = normalize(input.worldNormal);
	
	float3 light = normalize(input.dirToLight);
	float3 view = normalize(input.dirToView);
	
	float4 ambient = lightAmbient;
	
	float d = saturate(dot(light, n));
	float4 diffuse = d * lightDiffuse;
	
	float3 r = reflect(-light, n);
	float base = saturate(dot(r, view));
	float s = pow(base, 10);
	float4 specular = s * lightSpecular;
	
	float4 diffuseMapColor = diffuseMap.Sample(textureSampler, input.texCoord);
	float4 furMapColor = furMap.Sample(textureSampler, input.texCoord);
	float shadow = lerp(0.8, 1, currentLayer);
	int x = input.texCoord.x * width;
	int y = input.texCoord.y * height;
	int index = x + (width * y) % 64;
	
	float4 finalColor = (ambient + diffuse) * diffuseMapColor * shadow * input.diff;

	if (currentLayer > furMapColor.r) { furMapColor.a = 0.0f; }
	if (currentLayer == 0) { finalColor.a = 1.0f; }
	else { finalColor.r = furMapColor.a * furLength[index]; }
	
	return finalColor;
}