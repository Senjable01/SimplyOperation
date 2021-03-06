//------< include >-----------------------------------------------------------------------
#include "../Inc/Transform3D.h"
#include "../Inc/Configulation.h"
#if USE_IMGUI
#include "../Inc/ImGuiCtrl.h"

#endif // USE_IMGUI

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

    void Transform3D::DrawDebugGUI()
    {
        #if USE_IMGUI
        if (ImGui::CollapsingHeader("Transform3D"))
        {
            ImGui::InputFloat3("position", &position.x);
            ImGui::InputFloat3("scale", &scale.x);
            ImGui::SliderFloat3("rotation", &rotation.x, -DirectX::XM_PI, DirectX::XM_PI);
        }

        #endif // USE_IMGUI
    }

    void Transform3D::CalcTransform()
    {
        DirectX::XMMATRIX mtrixScale    = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
        DirectX::XMMATRIX mtrixRotation = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
        DirectX::XMMATRIX mtrixPosition = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
        DirectX::XMStoreFloat4x4(&transform, mtrixScale * mtrixRotation * mtrixPosition);
    }
    DirectX::XMFLOAT4X4 Transform3D::CalcTransform(
        const DirectX::XMFLOAT3& addPosition,
        const DirectX::XMFLOAT3& addScale,
        const DirectX::XMFLOAT3& addRotation
    )
    {
        DirectX::XMMATRIX mtrixScale    = DirectX::XMMatrixScaling(scale.x + addScale.x, scale.y + addScale.y, scale.z + addScale.y);
        DirectX::XMMATRIX mtrixRotation = DirectX::XMMatrixRotationRollPitchYaw(rotation.x + addRotation.x, rotation.y + addRotation.y, rotation.z + addRotation.z);
        DirectX::XMMATRIX mtrixPosition = DirectX::XMMatrixTranslation(position.x + addPosition.x, position.y + addPosition.y, position.z + addPosition.z);
        DirectX::XMFLOAT4X4 transform = {};
        DirectX::XMStoreFloat4x4(&transform, mtrixScale * mtrixRotation * mtrixPosition);
        return transform;
    }

    //------------------------------------------------------------------------------
    // instance
    //------------------------------------------------------------------------------

    TSL_IMPLEMENT_COMPONENT(Transform3D, "Transform3D");

}