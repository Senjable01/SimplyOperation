#ifndef INCLUDED_INC_CONSTANT_BUFFER_H
#define INCLUDED_INC_CONSTANT_BUFFER_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include <DirectXMath.h>
#include <d3d11.h>

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //------< constant >----------------------------------------------------------------------

    constexpr UINT REGISTER_OBJECT_CONSTANT = 0;
    constexpr UINT REGISTER_SCENE_CONSTANT  = 1;

    //------< function >----------------------------------------------------------------------

    void SetObjectConstantBuffer(
        ID3D11DeviceContext* immediateContext,
        ID3D11Buffer** objConstantBuffer,
        const DirectX::XMFLOAT4X4& world,
        const DirectX::XMFLOAT4& materialColor
    );
    void SetObjectConstantBuffer(
        ID3D11DeviceContext* immediateContext,
        ID3D11Buffer** objConstantBuffer,
        const DirectX::XMFLOAT4X4& world,
        const DirectX::XMFLOAT4& materialColor, const DirectX::XMFLOAT4& colorFactor
    );

    void SetSceneConstantBuffer(
        ID3D11DeviceContext* immediateContext,
        ID3D11Buffer** sceneConstantBuffer,
        const DirectX::XMFLOAT4X4& viewProjection,
        const DirectX::XMFLOAT4& lightDirection
    );
    void SetSpecularSceneConstantBuffer(
        ID3D11DeviceContext* immediateContext,
        ID3D11Buffer** sceneConstantBuffer,
        const DirectX::XMFLOAT4X4& viewProjection,
        const DirectX::XMFLOAT4& lightDirection,
        const DirectX::XMFLOAT4& cameraEye
    );

    //========================================================================================
    // 
    //      ObjectConstants
    // 
    //========================================================================================
    struct ObjectConstants
    {
        DirectX::XMFLOAT4X4 world;          // ワールド行列
        DirectX::XMFLOAT4 materialColor;    // マテリアルカラー

        ObjectConstants() : world{}, materialColor{0.0f, 0.0f, 0.0f, 0.0f} {}
        ObjectConstants(const DirectX::XMFLOAT4X4& world, const DirectX::XMFLOAT4& materialColor) :
            world{world}, materialColor{materialColor}
        {
        }
    };

    //====================================================================================
    // 
    //      SceneConstants
    // 
    //====================================================================================
    struct SceneConstants
    {
        DirectX::XMFLOAT4X4 viewProjection; // ビュー・プロジェクション変換行列
        DirectX::XMFLOAT4   lightDirection; // ライトの向き(VSのlight_direction)

        SceneConstants() : viewProjection{}, lightDirection{} {}
        SceneConstants(const DirectX::XMFLOAT4X4& viewProjection, const DirectX::XMFLOAT4& lightDirection) :
            viewProjection{viewProjection}, lightDirection{lightDirection}
        {
        }
    };

    //========================================================================================
    // 
    //      SpecularSceneConstants
    // 
    //========================================================================================
    //UNIT24 Section0(1)
    struct SpecularSceneConstants
    {
        DirectX::XMFLOAT4X4 viewProjection;
        DirectX::XMFLOAT4   lightDirection;
        DirectX::XMFLOAT4   cameraPosition;

        SpecularSceneConstants() : viewProjection{}, lightDirection{}, cameraPosition{} {}
        SpecularSceneConstants(
            const DirectX::XMFLOAT4X4& viewProjection,
            const DirectX::XMFLOAT4& lightDirection,
            const DirectX::XMFLOAT4& cameraPosition
        ) :
            viewProjection{viewProjection}, lightDirection{lightDirection}, cameraPosition{cameraPosition}
        {
        }
    };

    //========================================================================================
    // 
    //      SCENE_CONSTANTS
    // 
    //========================================================================================
    enum class SCENE_CONSTANTS {
        DEFAULT = 0,
        SPECULAR_DIFFUSE,
    };

}

#endif // !INCLUDED_INC_CONSTANT_BUFFER_H