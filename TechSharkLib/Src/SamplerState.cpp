//------< include >-----------------------------------------------------------------------
#include "../Inc/SamplerState.h"
#include "../Inc/DebugTools.h"

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
    //      SamplerState
    // 
    //========================================================================================

    //--------------------------------------------------------------------------------
    // member function
    //--------------------------------------------------------------------------------

    // UINT11 Section4.2
    void SamplerState::Initialize(ID3D11Device* device)
    {
        HRESULT hr = S_OK;

        D3D11_SAMPLER_DESC samplerDesc  = {};
        /* Point Filter */
        samplerDesc.Filter              = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
        samplerDesc.AddressU            = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV            = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW            = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.MipLODBias          = 0.0f;
        samplerDesc.MaxAnisotropy       = 16;
        samplerDesc.ComparisonFunc      = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
        samplerDesc.BorderColor[0]      = 0.0f;
        samplerDesc.BorderColor[1]      = 0.0f;
        samplerDesc.BorderColor[2]      = 0.0f;
        samplerDesc.BorderColor[3]      = 0.0f;
        samplerDesc.MinLOD              = 0.0f;
        samplerDesc.MaxLOD              = D3D11_FLOAT32_MAX;
        hr = device->CreateSamplerState(
            &samplerDesc,
            samplerStates[static_cast<size_t>(SAMPLER_TEXTURE_FILTER::POINT_FILTER)].GetAddressOf()
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        /* Liner Filter */
        samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        hr = device->CreateSamplerState(
            &samplerDesc,
            samplerStates[static_cast<size_t>(SAMPLER_TEXTURE_FILTER::LINER_FILTER)].GetAddressOf()
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        /* Anisotropic Filters */
        samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
        hr = device->CreateSamplerState(
            &samplerDesc,
            samplerStates[static_cast<size_t>(SAMPLER_TEXTURE_FILTER::ANISOTROPIC_FILTER)].GetAddressOf()
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

    }

    void SamplerState::Settings(ID3D11DeviceContext* immediateContext)
    {
        immediateContext->PSSetSamplers(
            static_cast<UINT>(SAMPLER_TEXTURE_FILTER::POINT_FILTER),
            1, samplerStates[static_cast<size_t>(SAMPLER_TEXTURE_FILTER::POINT_FILTER)].GetAddressOf()
        );
        immediateContext->PSSetSamplers(
            static_cast<UINT>(SAMPLER_TEXTURE_FILTER::LINER_FILTER),
            1, samplerStates[static_cast<size_t>(SAMPLER_TEXTURE_FILTER::LINER_FILTER)].GetAddressOf()
        );
        immediateContext->PSSetSamplers(
            static_cast<UINT>(SAMPLER_TEXTURE_FILTER::ANISOTROPIC_FILTER),
            1, samplerStates[static_cast<size_t>(SAMPLER_TEXTURE_FILTER::ANISOTROPIC_FILTER)].GetAddressOf()
        );
    }

    SamplerState* SamplerState::MakeState(ID3D11Device* device)
    {
        _ASSERT_EXPR(device != nullptr, L"Device‚ªnullptr‚Å‚·B");

        SamplerState* samplerState = new SamplerState{};
        samplerState->Initialize(device);
        return samplerState;
    }
}