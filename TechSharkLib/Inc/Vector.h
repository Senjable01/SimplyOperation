#ifndef INCLUDED_INC_VECTOR_H
#define INCLUDED_INC_VECTOR_H

//------< include >-----------------------------------------------------------------------
#include <DirectXMath.h>

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //========================================================================================
    // 
    //      Float2
    // 
    //========================================================================================
    struct Float2 : public DirectX::XMFLOAT2
    {
        Float2() : DirectX::XMFLOAT2{0.0f, 0.0f} {}
        Float2(int x, int y) : DirectX::XMFLOAT2{static_cast<float>(x), static_cast<float>(y)} {}
        Float2(float x, float y) : DirectX::XMFLOAT2{x, y} {}
        Float2(const Float2& src) : DirectX::XMFLOAT2{src.x, src.y} {}
        Float2(const DirectX::XMFLOAT2& src) : DirectX::XMFLOAT2{src} {}
        explicit Float2(const DirectX::XMVECTOR& src) { DirectX::XMStoreFloat2(this, src); }
        Float2& operator=(const Float2& src);
        Float2& operator=(const DirectX::XMFLOAT2& src);
        Float2& operator=(const DirectX::XMVECTOR& src);

        Float2& operator+=(const Float2& f);
        Float2& operator-=(const Float2& f);
        Float2& operator*=(int n);
        Float2& operator*=(float n);
        Float2& operator/=(int n);
        Float2& operator/=(float n);

        Float2 operator+() const;
        Float2 operator-() const;

        Float2 operator+(const Float2& f);
        Float2 operator-(const Float2& f);
        Float2 operator*(int n);
        Float2 operator*(float n);
        friend Float2 operator*(const Float2& f, int n);
        friend Float2 operator*(const Float2& f, float n);
        friend Float2 operator*(int n, const Float2& f);
        friend Float2 operator*(float n, const Float2& f);
        Float2 operator/(int n);
        Float2 operator/(float n);
        friend Float2 operator/(const Float2& f, int n);
        friend Float2 operator/(const Float2& f, float n);

        bool operator==(const Float2& f) const;
        bool operator!=(const Float2& f) const;

    };

    //========================================================================================
    // 
    //      Float3
    // 
    //========================================================================================
    struct Float3 : public DirectX::XMFLOAT3
    {
        Float3() : DirectX::XMFLOAT3{0.0f, 0.0f, 0.0f} {}
        Float3(int x, int y, int z) : DirectX::XMFLOAT3{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) } {}
        Float3(float x, float y, float z) : DirectX::XMFLOAT3{x, y, z} {}
        Float3(const Float3& src) : DirectX::XMFLOAT3{src.x, src.y, src.z} {}
        Float3(const DirectX::XMFLOAT3& src) : DirectX::XMFLOAT3{src.x, src.y, src.z} {}
        explicit Float3(const DirectX::XMVECTOR& src) { DirectX::XMStoreFloat3(this, src); }
        Float3& operator=(const Float3& src);
        Float3& operator=(const DirectX::XMFLOAT3& src);
        Float3& operator=(const DirectX::XMVECTOR& src);

        Float3& operator+=(const Float3& f);
        Float3& operator-=(const Float3& f);
        Float3& operator*=(int n);
        Float3& operator*=(float n);
        Float3& operator/=(int n);
        Float3& operator/=(float n);

        Float3 operator+() const;
        Float3 operator-() const;

        Float3 operator+(const Float3& f);
        Float3 operator-(const Float3& f);
        Float3 operator*(int n);
        Float3 operator*(float n);
        friend Float3 operator*(const Float3& f, int n);
        friend Float3 operator*(const Float3& f, float n);
        friend Float3 operator*(int n, const Float3& f);
        friend Float3 operator*(float n, const Float3& f);
        Float3 operator/(int n);
        Float3 operator/(float n);
        friend Float3 operator/(const Float3& f, int n);
        friend Float3 operator/(const Float3& f, float n);

        bool operator==(const Float3& f) const;
        bool operator!=(const Float3& f) const;

    };

    //========================================================================================
    // 
    //      Float4
    // 
    //========================================================================================
    struct Float4 : public DirectX::XMFLOAT4
    {
        Float4() : DirectX::XMFLOAT4{0.0f, 0.0f, 0.0f, 0.0f} {}
        Float4(int x, int y, int z, int w) : DirectX::XMFLOAT4{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w) } {}
        Float4(float x, float y, float z, float w) : DirectX::XMFLOAT4{x, y, z, w} {}
        Float4(const Float4& src) : DirectX::XMFLOAT4{src.x, src.y, src.z, src.w} {}
        Float4(const DirectX::XMFLOAT4& src) : DirectX::XMFLOAT4{src.x, src.y, src.z, src.w} {}
        explicit Float4(const DirectX::XMVECTOR& src) { DirectX::XMStoreFloat4(this, src); }
        Float4& operator=(const Float4& src);
        Float4& operator=(const DirectX::XMFLOAT4& src);
        Float4& operator=(const DirectX::XMVECTOR& src);

        Float4& operator+=(const Float4& f);
        Float4& operator-=(const Float4& f);
        Float4& operator*=(int n);
        Float4& operator*=(float n);
        Float4& operator/=(int n);
        Float4& operator/=(float n);

        Float4 operator+() const;
        Float4 operator-() const;

        Float4 operator+(const Float4& f);
        Float4 operator-(const Float4& f);
        Float4 operator*(int n);
        Float4 operator*(float n);
        friend Float4 operator*(const Float4& f, int n);
        friend Float4 operator*(const Float4& f, float n);
        friend Float4 operator*(int n, const Float4& f);
        friend Float4 operator*(float n, const Float4& f);
        Float4 operator/(int n);
        Float4 operator/(float n);
        friend Float4 operator/(const Float4& f, int n);
        friend Float4 operator/(const Float4& f, float n);

        bool operator==(const Float4& f) const;
        bool operator!=(const Float4& f) const;

    };
}

#endif // !INCLUDED_INC_VECTOR_H