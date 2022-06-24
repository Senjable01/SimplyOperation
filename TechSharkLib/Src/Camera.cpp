//------< include >-----------------------------------------------------------------------
#include "../Inc/Camera.h"
#include <crtdbg.h>
#include "../Inc/Configulation.h"
#if USE_IMGUI
#include "../Inc/ImGuiCtrl.h"

#endif // DEBUG_MODE

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    DirectX::XMMATRIX Camera::CalcViewMatrix(const DirectX::XMFLOAT4& eye, const DirectX::XMFLOAT4& focus, const DirectX::XMFLOAT4& up)
    {
        DirectX::XMVECTOR eyeVec    = DirectX::XMLoadFloat4(&eye);
        DirectX::XMVECTOR focusVec  = DirectX::XMLoadFloat4(&focus);
        DirectX::XMVECTOR upVec     = DirectX::XMLoadFloat4(&up);
        return DirectX::XMMatrixLookAtLH(eyeVec, focusVec, upVec);
    }
    DirectX::XMMATRIX Camera::CalcPerspectiveMatrix(float fovY, float aspect, float nearZ, float farZ)
    {
        return DirectX::XMMatrixPerspectiveFovLH(fovY, aspect, nearZ, farZ);
    }

    void Camera::UpdateCamaraParameter(const DirectX::XMFLOAT4& eye, const DirectX::XMFLOAT4& focus, const DirectX::XMMATRIX& viewMatrix)
    {
        /* 視点、注視点を保存 */
        this->eye   = eye;
        this->focus = focus;

        /* ビュー行列の逆行列 = ワールド行列 */
        DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixInverse(nullptr, viewMatrix);
        DirectX::XMFLOAT4X4 world = {};
        DirectX::XMStoreFloat4x4(&world, worldMatrix);

        /* ワールド行列からカメラの方向を抽出 */
        this->right = { world._11, world._12, world._13, world._14 };
        this->up    = { world._21, world._22, world._23, world._24 };
        this->front = { world._31, world._32, world._33, world._34 };

    }

    void Camera::LookAt(const DirectX::XMFLOAT3& eye, const DirectX::XMFLOAT3& focus, const DirectX::XMFLOAT3& up, DirectX::XMFLOAT4X4* pView)
    {
        LookAt({eye.x, eye.y, eye.z, 1.0f}, {focus.x, focus.y, focus.z, 1.0f}, {up.x, up.y, up.z, 0.0f}, pView);
    }
    void Camera::LookAt(const DirectX::XMFLOAT4& eye, const DirectX::XMFLOAT4& focus, const DirectX::XMFLOAT4& up, DirectX::XMFLOAT4X4* pView)
    {
        DirectX::XMMATRIX viewMatrix = CalcViewMatrix(eye, focus, up);
        UpdateCamaraParameter(eye, focus, viewMatrix);
        DirectX::XMStoreFloat4x4(&view, viewMatrix);
        if (pView != nullptr)
        {
            *pView = view;
        }
    }

    void Camera::CalcAndSetPerspectiveMatrix(float fovY, float aspect, float nearZ, float farZ, DirectX::XMFLOAT4X4* pProjection)
    {
        DirectX::XMMATRIX perspectiveMatrix = CalcPerspectiveMatrix(fovY, aspect, nearZ, farZ);
        DirectX::XMStoreFloat4x4(&projection, perspectiveMatrix);
        if (pProjection != nullptr)
        {
            *pProjection = projection;
        }
    }
    
    DirectX::XMFLOAT4X4 Camera::CalcViewProjection() const
    {
        DirectX::XMFLOAT4X4 viewProjection = {};
        DirectX::XMStoreFloat4x4(
            &viewProjection,
            DirectX::XMLoadFloat4x4(&view) * DirectX::XMLoadFloat4x4(&projection)
        );
        return viewProjection;
    }

    void Camera::DrawDebugGUI()
    {
        #if DEBUG_MODE
        if (ImGui::CollapsingHeader("Camera"))
        {
            ImGui::SliderFloat3("eye",  &eye.x, -10.0f, 10.0f);
            ImGui::SliderFloat3("focus",&focus.x, -10.0f, 10.0f);
            ImGui::InputFloat3("up",    &up.x,      "%.3f", ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
            ImGui::InputFloat3("front", &front.x,   "%.3f", ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
            ImGui::InputFloat3("right", &right.x,   "%.3f", ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
        }

        /* ビュー行列を更新 */
        DirectX::XMVECTOR eyeVec        = DirectX::XMLoadFloat4(&eye);
        DirectX::XMVECTOR focusVec      = DirectX::XMLoadFloat4(&focus);
        DirectX::XMVECTOR upVec         = DirectX::XMLoadFloat4(&up);
        DirectX::XMMATRIX viewMatrix    = DirectX::XMMatrixLookAtLH(eyeVec, focusVec, upVec);
        DirectX::XMStoreFloat4x4(&view, viewMatrix);
        /* カメラの方向を更新 */
        DirectX::XMMATRIX worldMatrix   = DirectX::XMMatrixInverse(nullptr, viewMatrix);
        DirectX::XMFLOAT4X4 world       = {};
        DirectX::XMStoreFloat4x4(&world, worldMatrix);
        // 行列作成時に単位ベクトル化している。
        this->right = { world._11, world._12, world._13, world._14 };
        this->up    = { world._21, world._22, world._23, world._24 };
        this->front = { world._31, world._32, world._33, world._34 };

        #endif // DEBUG_MODE

    }

}