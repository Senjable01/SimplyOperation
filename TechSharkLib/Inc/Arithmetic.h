#ifndef INCLUDED_INC_ARITHMETIC_H
#define INCLUDED_INC_ARITHMETIC_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include "Vector.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //------< constant >----------------------------------------------------------------------

    constexpr float THRESHOLD = 2.0e-3f;
    constexpr int MAX_INT_NUM = ~(1 << 31);
    constexpr float NEAR_ZERO = 1.0e-3f;

    //------< function >----------------------------------------------------------------------

    template<typename Arg> inline constexpr Arg Calculate(Arg n)
    {
        return n;
    }

    inline constexpr float ToRadian(float f)
    {
        return DirectX::XMConvertToRadians(f);
    }
    inline constexpr float ToDegree(float f)
    {
        return DirectX::XMConvertToDegrees(f);
    }

    inline bool NearlyEqual(float src, float dst, float threshold = THRESHOLD)
    {
        return (dst - threshold < src && src < dst + threshold);
    }

    int Clamp(int input, int low, int high);
    unsigned int Clamp(unsigned int input, unsigned int low, unsigned int high);
    float Clamp(float input, float low, float high);

    inline float SquaredLength(float x, float y)
    {
        return (x * x + y * y);
    }
    inline float SquaredLength(const Float2& f2)
    {
        return (f2.x * f2.x + f2.y * f2.y);
    }
    inline float SquaredLength(float x, float y, float z)
    {
        return (x * x + y * y + z * z);
    }
    inline float SquaredLength(const Float3& f3)
    {
        return (f3.x * f3.x + f3.y * f3.y + f3.z * f3.z);
    }
    float Length(float x, float y);
    float Length(const Float2& f2);
    float Length(float x, float y, float z);
    float Length(const Float3& f3);

    Float2 Normalize(float x, float y);
    Float2 Normalize(const Float2& f2);
    Float3 Normalize(float x, float y, float z);
    Float3 Normalize(const Float3& f3);

    // v1とv2の内積
    inline float DotProduct(float v1x, float v1y, float v2x, float v2y)
    {
        return (v1x * v2x + v1y * v2y);
    }
    // v1とv2の内積
    inline float DotProduct(const Float2& v1, const Float2& v2)
    {
        return (v1.x * v2.x + v1.y * v2.y);
    }
    // v1とv2の内積
    inline float DotProduct(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z)
    {
        return (v1x * v2x + v1y * v2y + v1z * v2z);
    }
    // v1とv2の内積
    inline float DotProduct(const Float3& v1, const Float3& v2)
    {
        return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
    }
    // 内積の角度(0 ~ Pi)
    float DotProductRadian(float dotProduct);
    // 内積の角度(0 ~ Pi)
    float DotProductRadian(float v1x, float v1y, float v2x, float v2y);
    // 内積の角度(0 ~ Pi)
    float DotProductRadian(const Float2& v1, const Float2& v2);
    // 内積の角度(0 ~ Pi)
    float DotProductRadian(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z);
    // 内積の角度(0 ~ Pi)
    float DotProductRadian(const Float3& v1, const Float3& v2);

    // v1からv2へ対する射影ベクトル
    Float2 Projection(float v1x, float v1y, float v2x, float v2y);
    // v1からv2へ対する射影ベクトル
    Float2 Projection(const Float2& v1, const Float2& v2);
    // v1からv2へ対する射影ベクトル
    Float3 Projection(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z);
    // v1からv2へ対する射影ベクトル
    Float3 Projection(const Float3& v1, const Float3& v2);

    // v1からv2へ対する外積(Z値)
    inline float CrossProductZ2D(float v1x, float v1y, float v2x, float v2y)
    {
        return (v1x * v2y - v2x * v1y);
    }
    // v1からv2へ対する外積(Z値)
    inline float CrossProductZ2D(const Float2& v1, const Float2& v2)
    {
        return (v1.x * v2.y - v2.x * v1.y);
    }
    // v1からv2へ対する外積
    inline Float3 CrossProduct(float v1x, float v1y, float v2x, float v2y)
    {
        return Float3{0.0f, 0.0f, CrossProductZ2D(v1x, v1y, v2x, v2y)};
    }
    // v1からv2へ対する外積
    inline Float3 CrossProduct(const Float2& v1, const Float2& v2)
    {
        return Float3{0.0f, 0.0f, CrossProductZ2D(v1.x, v1.y, v2.x, v2.y)};
    }

    Float2 ZRotation2D(float posX, float posY, float centerX, float centerY, float rotation/*radian*/);
    Float2 ZRotation2D(const Float2& pos, const Float2& center, float rotation/*radian*/);
    DirectX::XMFLOAT2 ZRotation2D(const DirectX::XMFLOAT2& pos, const DirectX::XMFLOAT2& center, float rotation/*radian*/);
    void ZRotation2D(Float2* pos, const Float2& center, float rotation/*radian*/);
    void ZRotation2D(DirectX::XMFLOAT2* pos, const DirectX::XMFLOAT2& center, float rotation/*radian*/);
        
    inline DirectX::XMFLOAT2 ConvertScreenToNDC(const DirectX::XMFLOAT2& screen, float viewportW, float viewportH)
    {
        return DirectX::XMFLOAT2{
            2.0f * screen.x / viewportW - 1.0f,
            1.0f - 2.0f * screen.y / viewportH
        };
    }
}

#endif // !INCLUDED_INC_ARITHMETIC_H