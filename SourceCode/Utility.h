#ifndef INCLUDED_UTILITY_H
#define INCLUDED_UTILITY_H

//------< include >-----------------------------------------------------------------------
#include <DirectXMath.h>

namespace util
{
    DirectX::XMFLOAT4X4 CalcTransform(
        const DirectX::XMFLOAT3& scale,
        const DirectX::XMFLOAT3& rotation,
        const DirectX::XMFLOAT3& position
    );
}

#endif // !INCLUDED_UTILITY_H