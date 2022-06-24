#include "static_mesh.hlsli"

VS_OUT main(float4 position : POSITION, float4 normal : NORMAL, float2 uv : UV_COORD)
{
    VS_OUT vout;
    /* ���[���h���W -> �X�N���[�����W */
    vout.position = mul(position, mul(world, view_projection));

    normal.w = 0;
    float4 N = normalize(mul(normal, world)); // �@���x�N�g��(���K���ς�)
    float4 L = normalize(-light_direction); // ���C�g�x�N�g��(���̋t�x�N�g��)(�@���Ƃ̓��ςɓs��������)

    /* �@���ƃ��C�g�x�N�g���̓��ςɂ���ĐF������ */
    vout.color.rgb = material_color.rgb * max(0, dot(L, N));
    /* �A���t�@�l�͈�� */
    vout.color.a = material_color.a;
    
    vout.uv = uv;
    
    return vout;
}