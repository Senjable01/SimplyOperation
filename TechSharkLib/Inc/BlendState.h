#ifndef INCLUDED_INC_BLEND_STATE_H
#define INCLUDED_INC_BLEND_STATE_H

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
    // UNIT13 Section0

    //========================================================================================
    // 
    //      BlendState
    // 
    //========================================================================================
    class BlendState
    {
    private:
        Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[static_cast<size_t>(BLEND_STATE::VALUE)];
        BLEND_STATE state;

        explicit BlendState() : blendStates{nullptr}, state{BLEND_STATE::VALUE} {}

        void Initialize(ID3D11Device* device);

    public:
        BlendState(const BlendState&) = delete;
        BlendState& operator=(const BlendState&) = delete;
        BlendState(BlendState&&) noexcept = delete;
        BlendState& operator=(BlendState&&) noexcept = delete;
        ~BlendState() {}

        BLEND_STATE State() const noexcept { return state; }
        void SetState(ID3D11DeviceContext* immediateContext, BLEND_STATE state);

        static BlendState* MakeState(ID3D11Device* device);

    };

}

#endif // !INCLUDED_INC_BLEND_STATE_H