#ifndef INCLUDED_INC_SAMPLER_STATE_H
#define INCLUDED_INC_SAMPLER_STATE_H

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
    // UNIT11 Section4.1

    //====================================================================================
    // 
    //      SamplerState
    // 
    //====================================================================================
    class SamplerState
    {
    private:
        Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[static_cast<size_t>(SAMPLER_TEXTURE_FILTER::VALUE)];
        SAMPLER_TEXTURE_FILTER state;

        explicit SamplerState() : samplerStates{nullptr}, state{SAMPLER_TEXTURE_FILTER::VALUE} {}

        void Initialize(ID3D11Device* device);

    public:
        SamplerState(const SamplerState&) = delete;
        SamplerState& operator=(const SamplerState&) = delete;
        SamplerState(SamplerState&&) noexcept = delete;
        SamplerState& operator=(SamplerState&&) noexcept = delete;
        ~SamplerState() {}

        SAMPLER_TEXTURE_FILTER State() const noexcept { return state; }
        void Settings(ID3D11DeviceContext* immediateContext);

        static SamplerState* MakeState(ID3D11Device* device);

    };
}

#endif // !INCLUDED_INC_SAMPLER_STATE_H