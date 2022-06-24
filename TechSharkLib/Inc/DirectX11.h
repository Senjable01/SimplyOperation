#ifndef INCLUDED_INC_DIRECTX11_H
#define INCLUDED_INC_DIRECTX11_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include <d3d11.h>
#include <wrl.h>
#include "DebugTools.h"
#include "SamplerState.h"
#include "DepthStencilState.h"
#include "BlendState.h"
#include "RasterizerState.h"

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
    //      Graphics
    // 
    //========================================================================================
    class Graphics
    {
    private:
        // UNIT4 Section0
        ID3D11Device*           device;
        ID3D11DeviceContext*    immediateContext;
        IDXGISwapChain*         swapChain;
        ID3D11RenderTargetView* renderTargetView;
        ID3D11DepthStencilView* depthStencilView;
        #if DEBUG_MODE
        ID3D11Debug*            debug;

        #endif // DEBUG_MODE
        float                   aspectRatio;

        SamplerState*       samplerState;
        DepthStencilState*  depthStencilState;
        BlendState*         blendState;
        RasterizerState*    rasterizerState;


        static Graphics instance_;

    public:
        Graphics() :
            device{nullptr},
            immediateContext{nullptr},
            swapChain{nullptr},
            renderTargetView{nullptr},
            depthStencilView{nullptr},
            #if DEBUG_MODE
            debug{nullptr},

            #endif // DEBUG_MODE
            aspectRatio{0.0f},
            samplerState{nullptr},
            depthStencilState{nullptr},
            blendState{nullptr},
            rasterizerState{nullptr}
        {
        }
        Graphics(const Graphics&) = delete;
        Graphics& operator=(const Graphics&) = delete;
        Graphics(Graphics&&) noexcept = delete;
        Graphics& operator=(Graphics&&) noexcept = delete;
        ~Graphics();

        void Initialize(HWND windowHandle, LONG width, LONG height, bool isFullscreen = false);
        void DefaultSettingStates();
        void ClearView(float red, float green, float blue, float alpha);
        void Present(UINT syncInterval = 0u, UINT flags = 0u);
        void Uninitialze();

        ID3D11Device* GetDevice() { return device; }
        ID3D11DeviceContext* GetContext() { return immediateContext; }
        float AspectRatio() const noexcept { return aspectRatio; }

        void SetDepthState(DEPTH_STATE state);
        void SetBlendState(BLEND_STATE state);
        void SetRasterizerState(RASTERIZER_STATE state);

    };

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    // UNIT05

    inline void Graphics::ClearView(float red, float green, float blue, float alpha)
    {
        FLOAT backColor[] = {red, green, blue, alpha}; // 背景色
        /* RenderTargetViewのクリア */
        immediateContext->ClearRenderTargetView(
            renderTargetView,
            backColor
        );
        /* DSVのクリア */
        immediateContext->ClearDepthStencilView(
            depthStencilView,
            D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL,
            1.0f, static_cast<UINT8>(0)
        );
    }

    inline void Graphics::Present(UINT syncInterval, UINT flags)
    {
        HRESULT hr = {S_OK};
        hr = swapChain->Present(syncInterval, flags);
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));
    }
}

#endif // !INCLUDED_INC_DIRECTX11_H