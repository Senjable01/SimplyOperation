#ifndef INCLUDED_INC_CAMERA_H
#define INCLUDED_INC_CAMERA_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning (disable : 4458)

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
    //      Camera
    // 
    //========================================================================================
    class Camera // 注視点を固定してしまえば動かない
    {
    private:
        DirectX::XMFLOAT4 eye;          // 視点(カメラの位置)
        DirectX::XMFLOAT4 focus;        // 注視点
        DirectX::XMFLOAT4 up;           // 上方向
        DirectX::XMFLOAT4 front;        // 前方向
        DirectX::XMFLOAT4 right;        // 右方向

        DirectX::XMFLOAT4X4 view;       // ビュー行列
        DirectX::XMFLOAT4X4 projection; // プロジェクション(投影)行列

        // 視点、注視点、上方向からビュー行列を計算
        DirectX::XMMATRIX CalcViewMatrix(const DirectX::XMFLOAT4& eye, const DirectX::XMFLOAT4& focus, const DirectX::XMFLOAT4& up);
        // 画角、画面比率、クリップ距離からプロジェクション行列を計算
        DirectX::XMMATRIX CalcPerspectiveMatrix(float fovY, float aspect, float nearZ, float farZ);
        // カメラのパラメーターを更新する。
        void UpdateCamaraParameter(const DirectX::XMFLOAT4& eye, const DirectX::XMFLOAT4& focus, const DirectX::XMMATRIX& viewMatrix);

    public:
        Camera() : view{}, projection{}, eye{}, focus{}, up{}, front{}, right{} {}

        // ビュー行列を更新し、その指定方向へ向く。
        void LookAt(const DirectX::XMFLOAT3& eye, const DirectX::XMFLOAT3& focus, const DirectX::XMFLOAT3& up, DirectX::XMFLOAT4X4* pView = nullptr);
        // ビュー行列を更新し、その指定方向へ向く。
        void LookAt(const DirectX::XMFLOAT4& eye, const DirectX::XMFLOAT4& focus, const DirectX::XMFLOAT4& up, DirectX::XMFLOAT4X4* pView = nullptr);
        // パーセクティブプロジェクション(透視投影)行列を計算して設定する。
        void CalcAndSetPerspectiveMatrix(float fovY, float aspect, float nearZ, float farZ, DirectX::XMFLOAT4X4* pProjection = nullptr);
        // ビュー・プロジェクション変換行列を計算して返す。
        DirectX::XMFLOAT4X4 CalcViewProjection() const;

        void DrawDebugGUI();

        const DirectX::XMFLOAT4& Eye() const noexcept { return eye; }
        const DirectX::XMFLOAT4& Focus() const noexcept { return focus; }
        const DirectX::XMFLOAT4& Up() const noexcept { return up; }
        const DirectX::XMFLOAT4& Front() const noexcept { return front; }
        const DirectX::XMFLOAT4& Right() const noexcept { return right; }
        const DirectX::XMFLOAT4X4& View() const noexcept { return view; }
        const DirectX::XMFLOAT4X4& Projection() const noexcept { return projection; }

        void SetEye(const DirectX::XMFLOAT4& eye) { this->eye = eye; }
        void SetFocus(const DirectX::XMFLOAT4& focus) { this->focus = focus; }
        void SetUp(const DirectX::XMFLOAT4& up) { this->up = up; }

    };
}

#endif // !INCLUDED_INC_CAMERA_H