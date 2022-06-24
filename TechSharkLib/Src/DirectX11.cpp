//------< include >-----------------------------------------------------------------------
#include "../Inc/DirectX11.h"
#include "../Inc/MiscTools.h"

//------< pragma >-------------------------------------------------------------------
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

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

    //------------------------------------------------------------------------------
    // destructor
    //------------------------------------------------------------------------------

    Graphics::~Graphics()
    {
        #if DEBUG_MODE
        ExpressDebugLog(L"DirectX11 �f�o�b�O���(Summary)");
        debug->ReportLiveDeviceObjects(D3D11_RLDO_FLAGS::D3D11_RLDO_SUMMARY);
        LineBreakDebugLog();

        ExpressDebugLog(L"DirectX11 �f�o�b�O���(Detail)");
        debug->ReportLiveDeviceObjects(D3D11_RLDO_FLAGS::D3D11_RLDO_DETAIL);
        LineBreakDebugLog();

        ExpressDebugLog(L"<Information> ��L��\"D3D11 WARNING\"�̓f�o�b�O���ł��B�ȍ~��\"D3D11 WARNING\"���x���ł��B");
        LineBreakDebugLog();

        SafeRelease(debug);

        #endif // DEBUG_MODE
    }

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void Graphics::Initialize(HWND windowHandle, LONG width, LONG height, bool isFullscreen)
    {
        HRESULT hr = S_OK;

        //////// Device,SwapChain,ImmediateContext�̍쐬 ////////
        // UNIT4 Section1
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc      = {}; // SwapChain�̐ݒ�
            swapChainDesc.BufferCount               = 1;
            swapChainDesc.BufferDesc.Width          = static_cast<UINT>(width);
            swapChainDesc.BufferDesc.Height         = static_cast<UINT>(height);
            swapChainDesc.BufferDesc.Format         = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
            swapChainDesc.BufferDesc.RefreshRate    = DXGI_RATIONAL{60, 1};
            swapChainDesc.BufferUsage               = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow              = windowHandle;
            swapChainDesc.SampleDesc.Count          = 1;
            swapChainDesc.SampleDesc.Quality        = 0;
            swapChainDesc.Windowed                  = !isFullscreen;

            UINT createDeviceFlags = 0; // �����^�C�����C���̃t���O�w��
            #if DEBUG_MODE
            createDeviceFlags |= D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_DEBUG;

            #endif // DEBUG_MODE

            D3D_FEATURE_LEVEL featureLevels =  D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0; // FeatureLevel

            /* Device,SwapChain,ImmediateContext���쐬 */
            hr = D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr,
                createDeviceFlags,
                &featureLevels, 1,
                D3D11_SDK_VERSION,
                &swapChainDesc,
                &swapChain, &device, nullptr, &immediateContext
            );
            if (FAILED(hr))
            {
                this->Uninitialze();
                _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));
            }
        }

        #if DEBUG_MODE
        {
            hr = device->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debug));
            _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));
        }

        #endif // DEBUG_MODE

        //////// RenderTargetView�̍쐬 ////////
        // UNIT4 Section2
        {
            ID3D11Texture2D* backBuffer = nullptr; // RenderTargetView�p�̃o�b�t�@
            /* SwapChain�̃o�b�t�@���P�擾 */
            hr = swapChain->GetBuffer(
                0,
                __uuidof(ID3D11Texture2D),
                reinterpret_cast<LPVOID*>(&backBuffer)
            );
            _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

            /* RenderTargetView�̍쐬 */
            hr = device->CreateRenderTargetView(
                backBuffer,
                nullptr,
                &renderTargetView
            );
            _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

            /* �Q�Ɛ�������炷 */
            backBuffer->Release();
        }

        //////// DepthStencilView�̍쐬 ////////
        // UNIT4 Section3
        {
            D3D11_TEXTURE2D_DESC texture2dDesc  = {};   // DSV�̃o�b�t�@�̐ݒ�
            texture2dDesc.Width                 = static_cast<UINT>(width);
            texture2dDesc.Height                = static_cast<UINT>(height);
            texture2dDesc.MipLevels             = 1;
            texture2dDesc.ArraySize             = 1u;
            texture2dDesc.Format                = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
            texture2dDesc.SampleDesc            = {1, 0};
            texture2dDesc.Usage                 = D3D11_USAGE::D3D11_USAGE_DEFAULT;
            texture2dDesc.BindFlags             = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
            texture2dDesc.CPUAccessFlags        = 0;
            texture2dDesc.MiscFlags             = 0;
            ID3D11Texture2D* depthStencilBuffer = nullptr;  // DSV�̃o�b�t�@
            /* DSV�̃o�b�t�@���쐬 */
            hr = device->CreateTexture2D(
                &texture2dDesc,
                nullptr,
                &depthStencilBuffer
            );
            _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

            D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{}; // DSV�̐ݒ�
            {
                depthStencilViewDesc.Format             = texture2dDesc.Format;
                depthStencilViewDesc.ViewDimension      = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;
                depthStencilViewDesc.Texture2D.MipSlice = 0;
            }
            /* DSV���쐬 */
            hr = device->CreateDepthStencilView(
                depthStencilBuffer,
                &depthStencilViewDesc,
                &depthStencilView
            );
            _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

            depthStencilBuffer->Release();
        }

        //////// ViewPort�̐ݒ� ////////
        // UNIT4 Section4
        {
            D3D11_VIEWPORT viewport{};
            {
                viewport.TopLeftX   = 0.0f;
                viewport.TopLeftY   = 0.0f;
                viewport.Width      = static_cast<FLOAT>(width);
                viewport.Height     = static_cast<FLOAT>(height);
                viewport.MinDepth   = 0.0f;
                viewport.MaxDepth   = 1.0f;
            }
            immediateContext->RSSetViewports(1, &viewport);
            aspectRatio = viewport.Width / viewport.Height;
        }

        //////// �e��X�e�[�g���쐬 ////////
        samplerState        = SamplerState::MakeState(device);
        depthStencilState   = DepthStencilState::MakeState(device);
        blendState          = BlendState::MakeState(device);
        rasterizerState     = RasterizerState::MakeState(device);

        //////// �`��ݒ� ////////

        immediateContext->OMSetRenderTargets(
            1u,
            &renderTargetView,
            depthStencilView
        );
        samplerState->Settings(immediateContext);
        DefaultSettingStates();

    }

    void Graphics::DefaultSettingStates()
    {
        depthStencilState->SetDepthState(immediateContext, DEPTH_STATE::NONE);
        blendState->SetState(immediateContext, BLEND_STATE::ALPHA);
        rasterizerState->SetState(immediateContext, RASTERIZER_STATE::SOLID);
    }

    void Graphics::SetDepthState(DEPTH_STATE state)
    {
        depthStencilState->SetDepthState(immediateContext, state);
    }
    void Graphics::SetBlendState(BLEND_STATE state)
    {
        blendState->SetState(immediateContext, state);
    }
    void Graphics::SetRasterizerState(RASTERIZER_STATE state)
    {
        rasterizerState->SetState(immediateContext, state);
    }

    void Graphics::Uninitialze()
    {
        // UNIT04 Section5

        BOOL isFullScreen = 0;
        swapChain->GetFullscreenState(&isFullScreen, 0);
        /* �t���X�N���[����ԂȂ���� */
        if (isFullScreen)
        {
            swapChain->SetFullscreenState(FALSE, 0);
        }

        immediateContext->ClearState();

        SafeRelease(device);
        SafeRelease(immediateContext);
        SafeRelease(swapChain);
        SafeRelease(renderTargetView);
        SafeRelease(depthStencilView);

        SafeDelete(samplerState);
        SafeDelete(depthStencilState);
        SafeDelete(blendState);
        SafeDelete(rasterizerState);

    }
}