
struct VS_OUTPUT
{
	float4 wvpPos : SV_POSITION; 
	float2 uv : UV; 
	float4 color : COLOR; 
	float4 normal : NORMAL; 
};


float4 main(VS_OUTPUT input) : SV_POSITION
{
	return float4(input.color); 
}