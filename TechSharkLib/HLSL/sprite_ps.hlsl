#include "sprite.hlsli"

Texture2D diffuse_map : register(t0); // �e�N�X�`��
SamplerState diffuse_map_sampler_state : register(s0); // �e�N�X�`���T���v���[

float4 main(VS_OUT pin) : SV_TARGET
{
    return diffuse_map.Sample(diffuse_map_sampler_state, pin.uv) * pin.color;
}