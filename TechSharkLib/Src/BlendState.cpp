//------< include >-----------------------------------------------------------------------
#include "../Inc/BlendState.h"
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
    //      BlendState
    // 
    //========================================================================================

    //--------------------------------------------------------------------------------
    // member function
    //--------------------------------------------------------------------------------

    //UNIT13 Section1
    void BlendState::Initialize(ID3D11Device* device)
    {
        HRESULT hr = S_OK;

        D3D11_BLEND_DESC blendDesc                      = {};
        blendDesc.AlphaToCoverageEnable                 = FALSE;
        blendDesc.IndependentBlendEnable                = FALSE;
        blendDesc.RenderTarget[0].BlendEnable           = TRUE;
        blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
        blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
        blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND::D3D11_BLEND_ONE;
        blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND::D3D11_BLEND_ZERO;
        blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
        hr = device->CreateBlendState(&blendDesc, blendStates[static_cast<size_t>(BLEND_STATE::ALPHA)].GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

    }

    //UNIT13 Section2
    void BlendState::SetState(ID3D11DeviceContext* immediateContext, BLEND_STATE state)
    {
        _ASSERT_EXPR(Not(state, BLEND_STATE::VALUE), L"不適切な列挙子です。");

        immediateContext->OMSetBlendState(blendStates[static_cast<size_t>(state)].Get(), nullptr, 0xffffffff);
        this->state = state;
    }

    BlendState* BlendState::MakeState(ID3D11Device* device)
    {
        _ASSERT_EXPR(device != nullptr, L"Deviceがnullptrです。");

        BlendState* blendState = new BlendState{};
        blendState->Initialize(device);
        return blendState;
    }
}