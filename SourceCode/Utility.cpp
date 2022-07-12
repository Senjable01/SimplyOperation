//------< include >-----------------------------------------------------------------------
#include "Utility.h"

namespace util
{
    DirectX::XMFLOAT4X4 CalcTransform(
        const DirectX::XMFLOAT3& scale,
        const DirectX::XMFLOAT3& rotation,
        const DirectX::XMFLOAT3& position
    )
    {
        DirectX::XMMATRIX mtrixScale = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
        DirectX::XMMATRIX mtrixRotation = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
        DirectX::XMMATRIX mtrixPosition = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
        DirectX::XMFLOAT4X4 transform = {};
        DirectX::XMStoreFloat4x4(&transform, mtrixScale * mtrixRotation * mtrixPosition);
        return transform;
    }
}