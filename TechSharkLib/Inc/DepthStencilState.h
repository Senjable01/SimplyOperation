#ifndef INCLUDED_INC_DEPTH_STENCIL_STATE_H
#define INCLUDED_INC_DEPTH_STENCIL_STATE_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning(disable : 4458)

//------< include >-----------------------------------------------------------------------
#include <d3d11.h>
#include <wrl.h>
#include "GraphicsStateEnum.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //UNIT12 Section0

    //========================================================================================
    // 
    //      DepthStencilState
    // 
    //========================================================================================
    class DepthStencilState
    {
    private:
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[static_cast<size_t>(DEPTH_STATE::VALUE)];
        DEPTH_STATE depthState;

        explicit DepthStencilState() : depthStencilStates{nullptr}, depthState{DEPTH_STATE::VALUE} {}

        void Initialize(ID3D11Device* device);

    public:
        DepthStencilState(const DepthStencilState&) = delete;
        DepthStencilState& operator=(const DepthStencilState&) = delete;
        DepthStencilState(DepthStencilState&&) noexcept = delete;
        DepthStencilState& operator=(DepthStencilState&&) noexcept = delete;
        ~DepthStencilState() {}

        DEPTH_STATE DepthState() const noexcept { return depthState; }
        void SetDepthState(ID3D11DeviceContext* immediateContext, DEPTH_STATE depthState);

        static DepthStencilState* MakeState(ID3D11Device* device);

    };
}

#endif // !INCLUDED_INC_DEPTH_STENCIL_STATE_H