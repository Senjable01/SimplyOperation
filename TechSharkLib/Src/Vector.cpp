//------< include >-----------------------------------------------------------------------
#include "../Inc/Vector.h"
#include "../Inc/Arithmetic.h"

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

    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------

    Float2& Float2::operator=(const Float2& src)
    {
        this->x = src.x, this->y = src.y;
        return *this;
    }
    Float2& Float2::operator=(const DirectX::XMFLOAT2& src)
    {
        this->x = src.x, this->y = src.y;
        return *this;
    }
    Float2& Float2::operator=(const DirectX::XMVECTOR& src)
    {
        DirectX::XMStoreFloat2(this, src);
        return *this;
    }

    Float2& Float2::operator+=(const Float2& src)
    {
        x += src.x, y += src.y;
        return *this;
    }
    Float2& Float2::operator-=(const Float2& src)
    {
        x -= src.x, y -= src.y;
        return *this;
    }
    Float2& Float2::operator*=(int n)
    {
        x *= n, y *= n;
        return *this;
    }
    Float2& Float2::operator*=(float n)
    {
        x *= n, y *= n;
        return *this;
    }
    Float2& Float2::operator/=(int n)
    {
        x /= n, y /= n;
        return *this;
    }
    Float2& Float2::operator/=(float n)
    {
        x /= n, y /= n;
        return *this;
    }

    Float2 Float2::operator+() const
    {
        return Float2{x, y};
    }
    Float2 Float2::operator-() const
    {
        return Float2{-x, -y};
    }

    Float2 Float2::operator+(const Float2& f)
    {
        return Float2{x + f.x, y + f.y};
    }
    Float2 Float2::operator-(const Float2& f)
    {
        return Float2{x - f.x, y - f.y};
    }
    Float2 Float2::operator*(int n)
    {
        return Float2{x * n, y * n};
    }
    Float2 Float2::operator*(float n)
    {
        return Float2{x * n, y * n};
    }
    Float2 operator*(const Float2& f, int n)
    {
        return Float2{f.x * n, f.y * n};
    }
    Float2 operator*(const Float2& f, float n)
    {
        return Float2{f.x * n, f.y * n};
    }
    Float2 operator*(int n, const Float2& f)
    {
        return Float2{n * f.x, n * f.y};
    }
    Float2 operator*(float n, const Float2& f)
    {
        return Float2{n * f.x, n * f.y};
    }
    Float2 Float2::operator/(int n)
    {
        return Float2{x / n, y / n};
    }
    Float2 Float2::operator/(float n)
    {
        return Float2{x / n, y / n};
    }
    Float2 operator/(const Float2& f, int n)
    {
        return Float2{f.x / n, f.y / n};
    }
    Float2 operator/(const Float2& f, float n)
    {
        return Float2{f.x / n, f.y / n};
    }

    bool Float2::operator==(const Float2& f) const
    {
        if (!NearlyEqual(this->x, f.x))
            return false;
        if (!NearlyEqual(this->y, f.y))
            return false;
        return true;
    }
    bool Float2::operator!=(const Float2& f) const
    {
        if (NearlyEqual(this->x, f.x))
            return false;
        if (NearlyEqual(this->y, f.y))
            return false;
        return true;
    }

    //========================================================================================
    // 
    //      Float3
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------

    Float3& Float3::operator=(const Float3& src)
    {
        this->x = src.x, this->y = src.y, this->z = src.z;
        return *this;
    }
    Float3& Float3::operator=(const DirectX::XMFLOAT3& src)
    {
        this->x = src.x, this->y = src.y, this->z = src.z;
        return *this;
    }
    Float3& Float3::operator=(const DirectX::XMVECTOR& src)
    {
        DirectX::XMStoreFloat3(this, src);
        return *this;
    }

    Float3& Float3::operator+=(const Float3& f)
    {
        this->x += f.x, this->y += f.y, this->z += f.z;
        return *this;
    }
    Float3& Float3::operator-=(const Float3& f)
    {
        this->x -= f.x, this->y -= f.y, this->z -= f.z;
        return *this;
    }
    Float3& Float3::operator*=(int n)
    {
        this->x *= n, this->y *= n, this->z *= n;
        return *this;
    }
    Float3& Float3::operator*=(float n)
    {
        this->x *= n, this->y *= n, this->z *= n;
        return *this;
    }
    Float3& Float3::operator/=(int n)
    {
        this->x /= n, this->y /= n, this->z /= n;
        return *this;
    }
    Float3& Float3::operator/=(float n)
    {
        this->x /= n, this->y /= n, this->z /= n;
        return *this;
    }

    Float3 Float3::operator+() const
    {
        return Float3{x, y, z};
    }
    Float3 Float3::operator-() const
    {
        return Float3{-x, -y, -z};
    }

    Float3 Float3::operator+(const Float3& f)
    {
        return Float3{x + f.x, y + f.y, z + f.z};
    }
    Float3 Float3::operator-(const Float3& f)
    {
        return Float3{x - f.x, y - f.y, z - f.z};
    }
    Float3 Float3::operator*(int n)
    {
        return Float3{x * n, y * n, z * n};
    }
    Float3 Float3::operator*(float n)
    {
        return Float3{x * n, y * n, z * n};
    }
    Float3 operator*(const Float3& f, int n)
    {
        return Float3{f.x * n, f.y * n, f.z * n};
    }
    Float3 operator*(const Float3& f, float n)
    {
        return Float3{f.x * n, f.y * n, f.z * n};
    }
    Float3 operator*(int n, const Float3& f)
    {
        return Float3{n * f.x, n * f.y, n * f.z};
    }
    Float3 operator*(float n, const Float3& f)
    {
        return Float3{n * f.x, n * f.y, n * f.z};
    }
    Float3 Float3::operator/(int n)
    {
        return Float3{x / n, y / n, z / n};
    }
    Float3 Float3::operator/(float n)
    {
        return Float3{x / n, y / n, z / n};
    }
    Float3 operator/(const Float3& f, int n)
    {
        return Float3{n / f.x, n / f.y, n / f.z};
    }
    Float3 operator/(const Float3& f, float n)
    {
        return Float3{n / f.x, n / f.y, n / f.z};
    }

    bool Float3::operator==(const Float3& f) const
    {
        if (!NearlyEqual(this->x, f.x))
            return false;
        if (!NearlyEqual(this->y, f.y))
            return false;
        if (!NearlyEqual(this->z, f.z))
            return false;
        return true;
    }
    bool Float3::operator!=(const Float3& f) const
    {
        if (NearlyEqual(this->x, f.x))
            return false;
        if (NearlyEqual(this->y, f.y))
            return false;
        if (NearlyEqual(this->z, f.z))
            return false;
        return true;
    }

    //========================================================================================
    // 
    //      Float4
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------

    Float4& Float4::operator=(const Float4& src)
    {
        this->x = src.x, this->y = src.y, this->z = src.z, this->w = src.w;
        return *this;
    }

    Float4& Float4::operator=(const DirectX::XMFLOAT4& src)
    {
        this->x = src.x, this->y = src.y, this->z = src.z, this->w = src.w;
        return *this;
    }

    Float4& Float4::operator=(const DirectX::XMVECTOR& src)
    {
        DirectX::XMStoreFloat4(this, src);
        return *this;
    }

    Float4& Float4::operator+=(const Float4& f)
    {
        this->x += f.x, this->y += f.y, this->z += f.z, this->w += f.w;
        return *this;
    }
    Float4& Float4::operator-=(const Float4& f)
    {
        this->x -= f.x, this->y -= f.y, this->z -= f.z, this->w -= f.w;
        return *this;
    }
    Float4& Float4::operator*=(int n)
    {
        this->x *= n, this->y *= n, this->z *= n, this->w *= n;
        return *this;
    }
    Float4& Float4::operator*=(float n)
    {
        this->x *= n, this->y *= n, this->z *= n, this->w *= n;
        return *this;
    }
    Float4& Float4::operator/=(int n)
    {
        this->x /= n, this->y /= n, this->z /= n, this->w /= n;
        return *this;
    }
    Float4& Float4::operator/=(float n)
    {
        this->x /= n, this->y /= n, this->z /= n, this->w /= n;
        return *this;
    }

    Float4 Float4::operator+() const
    {
        return Float4{x, y, z, w};
    }
    Float4 Float4::operator-() const
    {
        return Float4{-x, -y, -z, -w};
    }

    Float4 Float4::operator+(const Float4& f)
    {
        return Float4{x + f.x, y + f.y, z + f.z, w + f.w};
    }
    Float4 Float4::operator-(const Float4& f)
    {
        return Float4{x - f.x, y - f.y, z - f.z, w - f.w};
    }
    Float4 Float4::operator*(int n)
    {
        return Float4{x * n, y * n, z * n, w * n};
    }
    Float4 Float4::operator*(float n)
    {
        return Float4{x * n, y * n, z * n, w * n};
    }
    Float4 operator*(const Float4& f, int n)
    {
        return Float4{f.x * n, f.y * n, f.z * n, f.w * n};
    }
    Float4 operator*(const Float4& f, float n)
    {
        return Float4{f.x * n, f.y * n, f.z * n, f.w * n};
    }
    Float4 operator*(int n, const Float4& f)
    {
        return Float4{n * f.x, n * f.y, n * f.z, n * f.w};
    }
    Float4 operator*(float n, const Float4& f)
    {
        return Float4{ n * f.x, n * f.y, n * f.z, n * f.w };
    }
    Float4 Float4::operator/(int n)
    {
        return Float4{x / n, y / n, z / n, w / n};
    }
    Float4 Float4::operator/(float n)
    {
        return Float4{x / n, y / n, z / n, w / n};
    }
    Float4 operator/(const Float4& f, int n)
    {
        return Float4{f.x / n, f.y / n, f.z / n, f.w / n};
    }
    Float4 operator/(const Float4& f, float n)
    {
        return Float4{f.x / n, f.y / n, f.z / n, f.w / n};
    }

    bool Float4::operator==(const Float4& f) const
    {
        if (!NearlyEqual(this->x, f.x))
            return false;
        if (!NearlyEqual(this->y, f.y))
            return false;
        if (!NearlyEqual(this->z, f.z))
            return false;
        if (!NearlyEqual(this->w, f.w))
            return false;
        return true;
    }
    bool Float4::operator!=(const Float4& f) const
    {
        if (NearlyEqual(this->x, f.x))
            return false;
        if (NearlyEqual(this->y, f.y))
            return false;
        if (NearlyEqual(this->z, f.z))
            return false;
        if (NearlyEqual(this->w, f.w))
            return false;
        return true;
    }

}