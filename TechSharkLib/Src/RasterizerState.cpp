//------< include >-----------------------------------------------------------------------
#include "../Inc/RasterizerState.h"
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
    //      RasterizerState
    // 
    //========================================================================================

    //--------------------------------------------------------------------------------
    // member function
    //--------------------------------------------------------------------------------

    //UNIT18 Section1
    void RasterizerState::Initialize(ID3D11Device* device)
    {
        HRESULT hr = S_OK;

        D3D11_RASTERIZER_DESC rasterizerDesc    = {};
        rasterizerDesc.FillMode                 = D3D11_FILL_MODE::D3D11_FILL_SOLID;
        rasterizerDesc.CullMode                 = D3D11_CULL_MODE::D3D11_CULL_BACK;
        rasterizerDesc.FrontCounterClockwise    = FALSE;
        rasterizerDesc.DepthBias                = 0;
        rasterizerDesc.DepthBiasClamp           = 0.0f;
        rasterizerDesc.SlopeScaledDepthBias     = 0.0f;
        rasterizerDesc.DepthClipEnable          = TRUE;
        rasterizerDesc.ScissorEnable            = FALSE;
        rasterizerDesc.MultisampleEnable        = FALSE;
        rasterizerDesc.AntialiasedLineEnable    = FALSE;
        hr = device->CreateRasterizerState(&rasterizerDesc, rasterizerStates[static_cast<size_t>(RASTERIZER_STATE::SOLID_CULLING)].GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        rasterizerDesc.FillMode                 = D3D11_FILL_MODE::D3D11_FILL_SOLID;
        rasterizerDesc.CullMode                 = D3D11_CULL_MODE::D3D11_CULL_NONE;
        rasterizerDesc.AntialiasedLineEnable    = TRUE;
        hr = device->CreateRasterizerState(&rasterizerDesc, rasterizerStates[static_cast<size_t>(RASTERIZER_STATE::SOLID)].GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        rasterizerDesc.FillMode                 = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
        rasterizerDesc.CullMode                 = D3D11_CULL_MODE::D3D11_CULL_BACK;
        rasterizerDesc.AntialiasedLineEnable    = TRUE;
        hr = device->CreateRasterizerState(&rasterizerDesc, rasterizerStates[static_cast<size_t>(RASTERIZER_STATE::WIREFRAME_CULLING)].GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        rasterizerDesc.FillMode                 = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
        rasterizerDesc.CullMode                 = D3D11_CULL_MODE::D3D11_CULL_NONE;
        rasterizerDesc.AntialiasedLineEnable    = TRUE;
        hr = device->CreateRasterizerState(&rasterizerDesc, rasterizerStates[static_cast<size_t>(RASTERIZER_STATE::WIREFRAME)].GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));
    }

    //UNIT18 Section2
    void RasterizerState::SetState(ID3D11DeviceContext* immediateContext, RASTERIZER_STATE state)
    {
        _ASSERT_EXPR(Not(state, RASTERIZER_STATE::VALUE), L"不適切な列挙子です。");

        immediateContext->RSSetState(rasterizerStates[static_cast<size_t>(state)].Get());
        this->state = state;
    }

    RasterizerState* RasterizerState::MakeState(ID3D11Device* device)
    {
        _ASSERT_EXPR(device != nullptr, L"Deviceがnullptrです。");

        RasterizerState* rasterizerState = new RasterizerState{};
        rasterizerState->Initialize(device);
        return rasterizerState;
    }
}