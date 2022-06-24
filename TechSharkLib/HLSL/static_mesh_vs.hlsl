#include "static_mesh.hlsli"

VS_OUT main(float4 position : POSITION, float4 normal : NORMAL, float2 uv : UV_COORD)
{
    VS_OUT vout;
    /* ワールド座標 -> スクリーン座標 */
    vout.position = mul(position, mul(world, view_projection));

    normal.w = 0;
    float4 N = normalize(mul(normal, world)); // 法線ベクトル(正規化済み)
    float4 L = normalize(-light_direction); // ライトベクトル(光の逆ベクトル)(法線との内積に都合がいい)

    /* 法線とライトベクトルの内積によって色を決定 */
    vout.color.rgb = material_color.rgb * max(0, dot(L, N));
    /* アルファ値は一定 */
    vout.color.a = material_color.a;
    
    vout.uv = uv;
    
    return vout;
}