#include "sprite.hlsli"
VS_OUT main(float4 position : POSITION, float4 color : COLOR, float2 uv : UV_COORD)
{
    VS_OUT vout;
    vout.position   = position;
    vout.color      = color;
    vout.uv         = uv;

    return vout;
}