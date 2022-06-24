//------< include >-----------------------------------------------------------------------
#include "../Inc/ResourceManager.h"
#include "../Inc/BinaryData.h"
#include "../DirectXTK/Inc/WICTextureLoader.h"
#if _M_X64
#if _DEBUG
#pragma comment (lib, "TechSharkLib/DirectXTK/Lib/x64/Debug/DirectXTK.lib")
#else
#pragma comment (lib, "TechSharkLib/DirectXTK/Lib/x64/Release/DirectXTK.lib")
#endif

#else
#if _DEBUG
#pragma comment (lib, "TechSharkLib/DirectXTK/Lib/x86/Debug/DirectXTK.lib")
#else
#pragma comment (lib, "TechSharkLib/DirectXTK/Lib/x86/Release/DirectXTK.lib")
#endif

#endif
#include "../Inc/DebugTools.h"
#include <vector>

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
    //      ResourceManager
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void ResourceManager::LoadVertexShaderAndInputLayout(
        ID3D11Device* device,
        const D3D11_INPUT_ELEMENT_DESC* inputElementDesc, UINT elementNum, const wchar_t* vertexShaderPath,
        ID3D11VertexShader** outVertexShader, ID3D11InputLayout** outInputLayout
    )
    {
        HRESULT hr = S_OK;

        /* 頂点シェーダー + 入力レイアウト */
        auto loadedVS = vertexShaderMap.find(vertexShaderPath);
        if (loadedVS != vertexShaderMap.end())
        {
            (*outVertexShader) = loadedVS->second.GetRef();
            (*outInputLayout)  = inputLayoutMap.at(vertexShaderPath).GetRef();
        }
        else
        {
            BinaryData vsData = {vertexShaderPath};
            hr = device->CreateVertexShader(
                vsData.Data(), vsData.Size(),
                nullptr,
                outVertexShader
            );
            _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

            hr = device->CreateInputLayout(
                inputElementDesc, elementNum,
                vsData.Data(), vsData.Size(),
                outInputLayout
            );
            _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

            vertexShaderMap.emplace(vertexShaderPath, *outVertexShader);
            inputLayoutMap.emplace(vertexShaderPath, *outInputLayout);
        }
        
    }
    void ResourceManager::LoadShaderResourceView(
        ID3D11Device* device,
        const wchar_t* resourcePath,
        ID3D11ShaderResourceView** outShaderResourceView, D3D11_TEXTURE2D_DESC* outTexture2dDesc
    )
    {
        HRESULT hr = S_OK;

        /* 画像ファイルのロード + ShaderResourceView */
        //UNIT11 Section1
        ID3D11Resource* resource = nullptr;
        //UNIT16
        auto loadedSRV = shaderResourceViewMap.find(resourcePath);
        if (loadedSRV != shaderResourceViewMap.end())
        {
            (*outShaderResourceView) = loadedSRV->second.GetRef();
            (*outShaderResourceView)->GetResource(&resource);
            (*outShaderResourceView)->AddRef();
        }
        else
        {
            hr = DirectX::CreateWICTextureFromFile(
                device,
                resourcePath,
                &resource,
                outShaderResourceView
            );
            _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));
            shaderResourceViewMap.emplace(resourcePath, *outShaderResourceView);
        }
        /* テクスチャ情報 */
        ID3D11Texture2D* texture2d = {};
        hr = resource->QueryInterface<ID3D11Texture2D>(&texture2d);
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));
        texture2d->GetDesc(outTexture2dDesc);

        resource->Release();
        texture2d->Release();
    }
    void ResourceManager::CreateShaderResourceView(
        ID3D11Device*   device,
        const wchar_t*  name,
        DWORD value, UINT textureWidth,
        ID3D11ShaderResourceView** outShaderResourceView
    )
    {
        auto loadedSRV = shaderResourceViewMap.find(name);
        if (loadedSRV != shaderResourceViewMap.end())
        {
            (*outShaderResourceView) = loadedSRV->second.GetRef();
        }
        else
        {
            HRESULT hr = S_OK;

            D3D11_TEXTURE2D_DESC texture2dDesc  = {};
            texture2dDesc.Width                 = textureWidth;
            texture2dDesc.Height                = textureWidth;
            texture2dDesc.MipLevels             = 1;
            texture2dDesc.ArraySize             = 1;
            texture2dDesc.Format                = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
            texture2dDesc.SampleDesc            = {1, 0};
            texture2dDesc.Usage                 = D3D11_USAGE::D3D11_USAGE_DEFAULT;
            texture2dDesc.BindFlags             = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
            texture2dDesc.CPUAccessFlags        = 0;
            texture2dDesc.MiscFlags             = 0;

            size_t texelNum = static_cast<size_t>(textureWidth) * static_cast<size_t>(textureWidth);
            std::vector<DWORD> sysMem(texelNum, value); // texelNum個のサイズで構築し、全ての値をvalueで初期化

            D3D11_SUBRESOURCE_DATA subresourceData = {};
            subresourceData.pSysMem     = sysMem.data();
            subresourceData.SysMemPitch = sizeof(DWORD) * textureWidth;

            Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2d = nullptr;
            hr = device->CreateTexture2D(
                &texture2dDesc, &subresourceData,
                texture2d.GetAddressOf()
            );
            _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

            D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
            shaderResourceViewDesc.Format               = texture2dDesc.Format;
            shaderResourceViewDesc.ViewDimension        = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;
            shaderResourceViewDesc.Texture2D.MipLevels  = 1;
            hr = device->CreateShaderResourceView(
                texture2d.Get(),
                &shaderResourceViewDesc,
                outShaderResourceView
            );
            _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

            shaderResourceViewMap.emplace(name, *outShaderResourceView);
        }
    }
    void ResourceManager::LoadPixelShader(
        ID3D11Device* device,
        const wchar_t* pixelShaderPath,
        ID3D11PixelShader** outPixelShader
    )
    {
        HRESULT hr = S_OK;

        /* ピクセルシェーダー */
        auto loadedPixelShader = pixelShaderMap.find(pixelShaderPath);
        if (loadedPixelShader != pixelShaderMap.end())
        {
            (*outPixelShader) = loadedPixelShader->second.GetRef();
        }
        else
        {
            BinaryData psData{pixelShaderPath};
            hr = device->CreatePixelShader(
                psData.Data(), psData.Size(),
                nullptr,
                outPixelShader
            );
            _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

            pixelShaderMap.emplace(pixelShaderPath, *outPixelShader);
        }
    }

    void ResourceManager::ReleaseVertexShaderAndInputLayout(ID3D11VertexShader* vertexShader, ID3D11InputLayout* inputLayout)
    {
        if (vertexShader == nullptr || inputLayout == nullptr)
        {
            return;
        }

        for (auto itr = vertexShaderMap.begin(), end = vertexShaderMap.end(); itr != end; itr++)
        {
            if (itr->second != vertexShader)
            {
                continue;
            }

            size_t refCountVS = itr->second.ReleaseRef();
            #if _DEBUG
            size_t refCountIL = inputLayoutMap.at(itr->first).ReleaseRef();
            _ASSERT_EXPR(refCountVS == refCountIL, L"頂点シェーダーと入力レイアウトの参照数が不一致");

            #else
            inputLayoutMap.at(itr->first).ReleaseRef();

            #endif // _DEBUG

            if (refCountVS == 0)
            {
                auto itrIL = inputLayoutMap.find(itr->first);
                _ASSERT_EXPR(itrIL != inputLayoutMap.end(), L"イテレーターitrILが無効値");
                vertexShaderMap.erase(itr);
                inputLayoutMap.erase(itrIL);
            }
            break;
        }
    }
    void ResourceManager::ReleaseShaderResourceView(ID3D11ShaderResourceView* shaderResourceView)
    {
        if (shaderResourceView == nullptr)
        {
            return;
        }

        for (auto itr = shaderResourceViewMap.begin(), end = shaderResourceViewMap.end(); itr != end; itr++)
        {
            if (itr->second != shaderResourceView)
            {
                continue;
            }

            size_t refCount = itr->second.ReleaseRef();
            if (refCount == 0)
            {
                shaderResourceViewMap.erase(itr);
            }
            break;
        }
    }
    void ResourceManager::ReleasePixelShader(ID3D11PixelShader* pixelShader)
    {
        if (pixelShader == nullptr)
        {
            return;
        }

        for (auto itr = pixelShaderMap.begin(), end = pixelShaderMap.end(); itr != end; itr++)
        {
            if (itr->second != pixelShader)
            {
                continue;
            }

            size_t refCount = itr->second.ReleaseRef();
            if (refCount == 0)
            {
                pixelShaderMap.erase(itr);
            }
            break;
        }
    }

    void ResourceManager::Clear()
    {
        vertexShaderMap.clear();
        inputLayoutMap.clear();
        shaderResourceViewMap.clear();
        pixelShaderMap.clear();
    }

    //------------------------------------------------------------------------------
    // instance
    //------------------------------------------------------------------------------

    ResourceManager ResourceManager::instance_;
}