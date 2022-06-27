#ifndef INCLUDED_INC_TRANSFORM_H
#define INCLUDED_INC_TRANSFORM_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning( disable : 4458 )

//------< include >-----------------------------------------------------------------------
#include "Component.h"
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
    //====================================================================================
    // 
    //      TransformDesc
    // 
    //====================================================================================
    struct Transform3DDesc
    {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT3 scale;
        DirectX::XMFLOAT3 rotation;

        Transform3DDesc() : 
            position{0.0f, 0.0f, 0.0f}, scale{0.0f, 0.0f, 0.0f}, rotation{0.0f, 0.0f, 0.0f}
        {
        }
        Transform3DDesc(
            float posX,     float posY,     float posZ,
            float scaleX,   float scaleY,   float scaleZ,
            float rotateX,  float rotateY,  float rotateZ
        ) : 
            position{posX, posY, posZ}, scale{scaleX, scaleY, scaleZ}, rotation{rotateX, rotateY, rotateZ}
        {
        }
        Transform3DDesc(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& scale, const DirectX::XMFLOAT3& rotation) : 
            position{position}, scale{scale}, rotation{rotation}
        {
        }
    };

    //====================================================================================
    // 
    //      Transform
    // 
    //====================================================================================
    class Transform3D : public Component
    {
    TSL_DEFINE_COMPONENT(Transform3D);
    private:
        DirectX::XMFLOAT3   position;
        DirectX::XMFLOAT3   scale;
        DirectX::XMFLOAT3   rotation;
        DirectX::XMFLOAT4X4 transform;

        const Transform3DDesc description;

    public:
        Transform3D() = delete;
        Transform3D(ComponentManager* manager, const ComponentID& self, const GameObjectID& owner, const Transform3DDesc& desc) :
            position{0.0f, 0.0f, 0.0f}, scale{0.0f, 0.0f, 0.0f}, rotation{0.0f, 0.0f, 0.0f}, transform{},
            description{desc},
            Component{manager, self, owner}
        {
        }
        ~Transform3D() override {}

        void Init() override {};
        void Setup() override;
        void Update(float) override;
        void Render(float, float) override {}
        void Deinit() override {}

        void CalcTransform();
        void Clear() override;

        const DirectX::XMFLOAT3& Position() const noexcept { return position; }
        const DirectX::XMFLOAT3& Scale() const noexcept { return scale; }
        const DirectX::XMFLOAT3& Rotation() const noexcept { return rotation; }
        const DirectX::XMFLOAT4X4 Transform() const noexcept { return transform; }

        void SetPosition(float x, float y, float z) { position.x = x, position.y = y, position.z = z; }
        void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }
        void SetScale(float x, float y, float z) { scale.x = x, scale.y = y, scale.z = z; }
        void SetScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; }
        void SetRotation(float x, float y, float z) { rotation.x = x, rotation.y = y, rotation.z = z; }
        void SetRotation(const DirectX::XMFLOAT3& rotation) { this->rotation = rotation; }

    };
}

#endif // !INCLUDED_INC_TRANSFORM_3D_H