//------< include >-----------------------------------------------------------------------
#include "../Inc/DepthStencilState.h"
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
    //      DepthStencilState
    // 
    //========================================================================================

    //--------------------------------------------------------------------------------
    // member function
    //--------------------------------------------------------------------------------

    //UNIT12 Section1
    void DepthStencilState::Initialize(ID3D11Device* device)
    {
        HRESULT hr = S_OK;

        /* DepthTest: OFF | DepthWrite: OFF */
        D3D11_DEPTH_STENCIL_DESC depthStencilDesc   = {};
        depthStencilDesc.DepthEnable                = FALSE;
        depthStencilDesc.DepthWriteMask             = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
        depthStencilDesc.DepthFunc                  = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
        depthStencilDesc.StencilEnable              = FALSE;
        depthStencilDesc.StencilReadMask            = D3D11_DEFAULT_STENCIL_READ_MASK;
        depthStencilDesc.StencilWriteMask           = D3D11_DEFAULT_STENCIL_WRITE_MASK;
        depthStencilDesc.FrontFace                  = {
            D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP,
            D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP,
            D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP,
            D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS
        };
        depthStencilDesc.BackFace                   = {
            D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP,
            D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP,
            D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP,
            D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS
        };
        hr = device->CreateDepthStencilState(
            &depthStencilDesc,
            &depthStencilStates[static_cast<size_t>(DEPTH_STATE::NONE)]
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        /* DepthTest: ON | DepthWrite: OFF */
        depthStencilDesc.DepthEnable    = TRUE;
        depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
        hr = device->CreateDepthStencilState(
            &depthStencilDesc,
            &depthStencilStates[static_cast<size_t>(DEPTH_STATE::TEST)]
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        /* DepthTest: OFF | DepthWrite: ON */
        depthStencilDesc.DepthEnable    = FALSE;
        depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
        hr = device->CreateDepthStencilState(
            &depthStencilDesc,
            &depthStencilStates[static_cast<size_t>(DEPTH_STATE::WRITE)]
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        /* DepthTest: ON | DepthWrite: ON */
        depthStencilDesc.DepthEnable    = TRUE;
        depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
        hr = device->CreateDepthStencilState(
            &depthStencilDesc,
            &depthStencilStates[static_cast<size_t>(DEPTH_STATE::TEST_AND_WRITE)]
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));
    }

    //UNIT12 Section2
    void DepthStencilState::SetDepthState(ID3D11DeviceContext* immediateContext, DEPTH_STATE depthState)
    {
        _ASSERT_EXPR(Not(depthState, DEPTH_STATE::VALUE), L"不適切な列挙子です。");

        immediateContext->OMSetDepthStencilState(depthStencilStates[static_cast<size_t>(depthState)].Get(), 1);
        this->depthState = depthState;
    }

    DepthStencilState* DepthStencilState::MakeState(ID3D11Device* device)
    {
        _ASSERT_EXPR(device != nullptr, L"Deviceがnullptrです。");

        DepthStencilState* depthStencilState = new DepthStencilState{};
        depthStencilState->Initialize(device);
        return depthStencilState;
    }
}