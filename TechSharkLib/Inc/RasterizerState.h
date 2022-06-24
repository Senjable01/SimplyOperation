#ifndef INCLUDED_RASTERIZER_STATE_H
#define INCLUDED_RASTERIZER_STATE_H

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
    //UNIT18 Section0

    //========================================================================================
    // 
    //      RasterizerState
    // 
    //========================================================================================
    class RasterizerState
    {
    private:
        Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[static_cast<size_t>(RASTERIZER_STATE::VALUE)];
        RASTERIZER_STATE state;

        explicit RasterizerState() :
            rasterizerStates{nullptr}, state{RASTERIZER_STATE::VALUE}
        {
        }

        void Initialize(ID3D11Device* device);

    public:
        RasterizerState& operator=(const RasterizerState&) = delete;
        RasterizerState(RasterizerState&&) noexcept = delete;
        RasterizerState& operator=(RasterizerState&&) noexcept = delete;
        ~RasterizerState() {}

        RASTERIZER_STATE State() const noexcept { return state; }
        void SetState(ID3D11DeviceContext* immediateContext, RASTERIZER_STATE state);

        static RasterizerState* MakeState(ID3D11Device* device);
    };
}

#endif // INCLUDED_RASTERIZER_STATE_H