//------< include >-----------------------------------------------------------------------
#include "../Inc/Transform3D.h"

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
    //      Transform3D
    // 
    //====================================================================================

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void Transform3D::Setup()
    {
        position    = description.position;
        scale       = description.scale;
        rotation    = description.rotation;
        CalcTransform();
    }
    void Transform3D::Update(float)
    {
        CalcTransform();
    }
    void Transform3D::Deinit()
    {
        position    = {0.0f, 0.0f, 0.0f};
        scale       = {0.0f, 0.0f, 0.0f};
        rotation    = {0.0f, 0.0f, 0.0f};
        description = {};
    }

    void Transform3D::CalcTransform()
    {
        DirectX::XMMATRIX mtrixScale    = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
        DirectX::XMMATRIX mtrixRotation = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
        DirectX::XMMATRIX mtrixPosition = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
        DirectX::XMStoreFloat4x4(&transform, mtrixScale * mtrixRotation * mtrixPosition);
    }

    //------------------------------------------------------------------------------
    // instance
    //------------------------------------------------------------------------------

    TSL_IMPLEMENT_COMPONENT(Transform3D, "Transform3D");

}