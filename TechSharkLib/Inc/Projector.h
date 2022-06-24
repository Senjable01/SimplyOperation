#ifndef INCLUDED_INC_PROJECTOR_H
#define INCLUDED_INC_PROJECTOR_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning (disable : 4458)

//------< include >-----------------------------------------------------------------------
#include <d3d11.h>
#include "../Inc/ConstantBuffer.h"
#include <functional>
#include "../Inc/Camera.h"

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
    //      Projector
    // 
    //========================================================================================
    class Projector
    {
        //UNDONE:07 シーン定数バッファ用のインターフェースを再設計
    private:
        using SceneConstantSetter = std::function<void(Camera* camera, const DirectX::XMFLOAT4& lightDirection)>;

        ID3D11Device*           device;             // (キャッシュ用)
        ID3D11DeviceContext*    immediateContext;   // (キャッシュ用)
        ID3D11Buffer*           sceneConstantBuffer;
        SceneConstantSetter     SetSceneConstantBuffer;

    public:
        Projector() : device{nullptr}, immediateContext{nullptr}, sceneConstantBuffer{nullptr} {}
        Projector(const Projector&) = delete;
        Projector& operator=(const Projector&) = delete;
        Projector(Projector&&) noexcept = delete;
        Projector& operator=(Projector&&) noexcept = delete;
        ~Projector() { Uninitialize(); }

        void Initialize(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
        void Setup(SCENE_CONSTANTS type);
        void Project(Camera* camera, const DirectX::XMFLOAT4& lightDirection);
        void Reset();
        void Uninitialize();

    };
}

#endif // !INCLUDED_INC_CAMERA_MANAGER_H