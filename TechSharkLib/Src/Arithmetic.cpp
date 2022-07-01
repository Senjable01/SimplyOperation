//------< include >---------------------------------------------------------------------- -
#include "../Inc/Arithmetic.h"
#include <utility>
#include <cmath>

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //------< function >----------------------------------------------------------------------

    template<typename Arg> inline Arg Clamp(Arg input, Arg low, Arg high)
    {
        Arg oldLow = low;
        low     = (std::min)(low, high);
        high    = (std::max)(high, oldLow);

        return (std::max)(
            (std::min)(input, high), low
        );
    }
    int Clamp(int input, int low, int high)
    {
        return Clamp<int>(input, low, high);
    }
    unsigned int Clamp(unsigned int input, unsigned int low, unsigned int high)
    {
        return Clamp<unsigned int>(input, low, high);
    }
    float Clamp(float input, float low, float high)
    {
        return Clamp<float>(input, low, high);
    }


    float Length(float x, float y)
    {
        return std::hypotf(x, y);
    }
    float Length(const Float2& f2)
    {
        return std::hypotf(f2.x, f2.y);
    }
    float Length(float x, float y, float z)
    {
        return std::hypotf(std::hypotf(x, y), z);
    }
    float Length(const Float3& f3)
    {
        return std::hypotf(std::hypotf(f3.x, f3.y), f3.z);
    }

    Float2 Normalize(float x, float y)
    {
        return Float2{x, y} / Length(x, y);
    }
    Float2 Normalize(const Float2& f2)
    {
        return f2 / Length(f2);
    }
    Float3 Normalize(float x, float y, float z)
    {
        return Float3{x, y, z} / Length(x, y);
    }
    Float3 Normalize(const Float3& f3)
    {
        return f3 / Length(f3);
    }

    float DotProductRadian(float dotProduct)
    {
        return std::acosf(dotProduct);
    }
    float DotProductRadian(float v1x, float v1y, float v2x, float v2y)
    {
        return std::acosf(DotProduct(v1x, v1y, v2x, v2y));
    }
    float DotProductRadian(const Float2& v1, const Float2& v2)
    {
        return std::acosf(DotProduct(v1, v2));
    }
    float DotProductRadian(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z)
    {
        return std::acosf(DotProduct(v1x, v1y, v1z, v2x, v2y, v2z));
    }
    float DotProductRadian(const Float3& v1, const Float3& v2)
    {
        return std::acosf(DotProduct(v1, v2));
    }

    Float2 Projection(float v1x, float v1y, float v2x, float v2y)
    {
        return DotProduct(v1x, v1y, v2x, v2y) / SquaredLength(v2x, v2y) * Float2{v2x, v2y};
    }
    Float2 Projection(const Float2& v1, const Float2& v2)
    {
        return DotProduct(v1.x, v1.y, v2.x, v2.y) / SquaredLength(v2.x, v2.y) * v2;
    }
    Float3 Projection(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z)
    {
        return DotProduct(v1x, v1y, v1z, v2x, v2y, v2z) / SquaredLength(v2x, v2y, v2z) * Float3{v2x, v2y, v2z};
    }
    Float3 Projection(const Float3& v1, const Float3& v2)
    {
        return DotProduct(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z) / SquaredLength(v2.x, v2.y, v2.z) * v2;
    }

    Float2 ZRotation2D(float posX, float posY, float centerX, float centerY, float rotation/*radian*/)
    {
        const float relativeX   = posX - centerX;
        const float relativeY   = posY - centerY;
        const float cosine      = std::cosf(rotation);
        const float sine        = std::sinf(rotation);

        return Float2{
            relativeX * std::cosf(rotation) - relativeY * std::sinf(rotation) + centerX,
            relativeY * std::cosf(rotation) + relativeX * std::sinf(rotation) + centerY
        };
    }
    Float2 ZRotation2D(const Float2& pos, const Float2& center, float rotation/*radian*/)
    {
        const float relativeX   = pos.x - center.x;
        const float relativeY   = pos.y - center.y;
        const float cosine      = std::cosf(rotation);
        const float sine        = std::sinf(rotation);

        return Float2{
            relativeX * std::cosf(rotation) - relativeY * std::sinf(rotation) + center.x,
            relativeY * std::cosf(rotation) + relativeX * std::sinf(rotation) + center.y
        };
    }
    DirectX::XMFLOAT2 ZRotation2D(const DirectX::XMFLOAT2& pos, const DirectX::XMFLOAT2& center, float rotation/*radian*/)
    {
        const float relativeX   = pos.x - center.x;
        const float relativeY   = pos.y - center.y;
        const float cosine      = std::cosf(rotation);
        const float sine        = std::sinf(rotation);

        return DirectX::XMFLOAT2{
            relativeX * std::cosf(rotation) - relativeY * std::sinf(rotation) + center.x,
            relativeY * std::cosf(rotation) + relativeX * std::sinf(rotation) + center.y
        };
    }
    void ZRotation2D(Float2* pos, const Float2& center, float rotation/*radian*/)
    {
        const float relativeX   = pos->x - center.x;
        const float relativeY   = pos->y - center.y;
        const float cosine      = std::cosf(rotation);
        const float sine        = std::sinf(rotation);

        pos->x = relativeX * cosine - relativeY * sine + center.x;
        pos->y = relativeY * cosine + relativeX * sine + center.y;
    }
    void ZRotation2D(DirectX::XMFLOAT2* pos, const DirectX::XMFLOAT2& center, float rotation/*radian*/)
    {
        const float relativeX   = pos->x - center.x;
        const float relativeY   = pos->y - center.y;
        const float cosine      = std::cosf(rotation);
        const float sine        = std::sinf(rotation);

        pos->x = relativeX * cosine - relativeY * sine + center.x;
        pos->y = relativeY * cosine + relativeX * sine + center.y;
    }
}