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
    class Camera // �����_���Œ肵�Ă��܂��Γ����Ȃ�
    {
    private:
        DirectX::XMFLOAT4 eye;          // ���_(�J�����̈ʒu)
        DirectX::XMFLOAT4 focus;        // �����_
        DirectX::XMFLOAT4 up;           // �����
        DirectX::XMFLOAT4 front;        // �O����
        DirectX::XMFLOAT4 right;        // �E����

        DirectX::XMFLOAT4X4 view;       // �r���[�s��
        DirectX::XMFLOAT4X4 projection; // �v���W�F�N�V����(���e)�s��

        // ���_�A�����_�A���������r���[�s����v�Z
        DirectX::XMMATRIX CalcViewMatrix(const DirectX::XMFLOAT4& eye, const DirectX::XMFLOAT4& focus, const DirectX::XMFLOAT4& up);
        // ��p�A��ʔ䗦�A�N���b�v��������v���W�F�N�V�����s����v�Z
        DirectX::XMMATRIX CalcPerspectiveMatrix(float fovY, float aspect, float nearZ, float farZ);
        // �J�����̃p�����[�^�[���X�V����B
        void UpdateCamaraParameter(const DirectX::XMFLOAT4& eye, const DirectX::XMFLOAT4& focus, const DirectX::XMMATRIX& viewMatrix);

    public:
        Camera() : view{}, projection{}, eye{}, focus{}, up{}, front{}, right{} {}

        // �r���[�s����X�V���A���̎w������֌����B
        void LookAt(const DirectX::XMFLOAT3& eye, const DirectX::XMFLOAT3& focus, const DirectX::XMFLOAT3& up, DirectX::XMFLOAT4X4* pView = nullptr);
        // �r���[�s����X�V���A���̎w������֌����B
        void LookAt(const DirectX::XMFLOAT4& eye, const DirectX::XMFLOAT4& focus, const DirectX::XMFLOAT4& up, DirectX::XMFLOAT4X4* pView = nullptr);
        // �p�[�Z�N�e�B�u�v���W�F�N�V����(�������e)�s����v�Z���Đݒ肷��B
        void CalcAndSetPerspectiveMatrix(float fovY, float aspect, float nearZ, float farZ, DirectX::XMFLOAT4X4* pProjection = nullptr);
        // �r���[�E�v���W�F�N�V�����ϊ��s����v�Z���ĕԂ��B
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