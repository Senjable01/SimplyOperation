#ifndef INCLUDED_INC_RESOURCE_MANAGER_H
#define INCLUDED_INC_RESOURCE_MANAGER_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include <map>
#include <wrl.h> // https://github.com/Microsoft/DirectXTK/wiki/ComPtr
#include <d3d11.h>
#include <utility>

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
    class ResourceManager
    {
    private:
        template<typename Arg>
        class ComPackage
        {
        private:
            Arg* comPtr;
            size_t referenceCount;

            void SafeReleaseAll() //UNDONE:04 ComPtrクラスに置き換えてSafeReleaseAll関数を改良する。
            {
                if (comPtr != nullptr)
                {
                    ULONG refNum = comPtr->Release();
                    while (refNum != 0)
                        refNum = comPtr->Release();
                    comPtr = nullptr;
                }
            }

        public:
            explicit ComPackage(Arg* comPtr) : comPtr{comPtr}, referenceCount{1}
            {
                _ASSERT_EXPR(comPtr != nullptr, L"comPtrがnullptr");
            }
            ComPackage(const ComPackage<Arg>&) = delete;
            const ComPackage<Arg>& operator=(const ComPackage<Arg>&) = delete;
            ComPackage(ComPackage<Arg>&& src) noexcept : comPtr{src.comPtr}, referenceCount{src.referenceCount}
            {
                src.comPtr          = nullptr;
                src.referenceCount  = 0;
            }
            const ComPackage<Arg>& operator=(ComPackage<Arg>&& src) noexcept
            {
                comPtr              = src.comPtr;
                referenceCount      = src.referenceCount;
                src.comPtr          = nullptr;
                src.referenceCount  = 0;
                return (*this);
            }
            ~ComPackage()
            {
                SafeReleaseAll();
                referenceCount = 0;
            }

            Arg* GetRef()
            {
                _ASSERT_EXPR(comPtr != nullptr, L"comPtrはnullptr");
                referenceCount++;
                return comPtr;
            }
            size_t ReleaseRef()
            {
                referenceCount--;
                if (referenceCount == 0)
                {
                    SafeReleaseAll();
                }
                return referenceCount;
            }
            size_t ReferenceCount() const noexcept { return referenceCount; }

            bool operator==(Arg* src) { return comPtr == src; }
            bool operator!=(Arg* src) { return comPtr != src; }

        };

        std::map<const wchar_t*, ComPackage<ID3D11VertexShader>>        vertexShaderMap;
        std::map<const wchar_t*, ComPackage<ID3D11InputLayout>>         inputLayoutMap;
        std::map<const wchar_t*, ComPackage<ID3D11ShaderResourceView>>  shaderResourceViewMap;
        std::map<const wchar_t*, ComPackage<ID3D11PixelShader>>         pixelShaderMap;

        ResourceManager() {}
        ~ResourceManager()
        {
            Clear();
        }

        static ResourceManager instance_;

    public:
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
        ResourceManager(ResourceManager&&) noexcept = delete;
        ResourceManager& operator=(ResourceManager&&) noexcept = delete;

        void LoadShaderResourceView(
            ID3D11Device* device,
            const wchar_t* resourcePath,
            ID3D11ShaderResourceView** outShaderResourceView, D3D11_TEXTURE2D_DESC* outTexture2dDesc
        );
        void CreateShaderResourceView(
            ID3D11Device*   device,
            const wchar_t*  name,
            DWORD value, UINT textureWidth,
            ID3D11ShaderResourceView** outShaderResourceView
        );
        void LoadVertexShaderAndInputLayout(
            ID3D11Device* device,
            const D3D11_INPUT_ELEMENT_DESC* inputElementDesc, UINT elementNum, const wchar_t* vertexShaderPath,
            ID3D11VertexShader** outVertexShader, ID3D11InputLayout** outInputLayout
        );
        void LoadPixelShader(
            ID3D11Device* device,
            const wchar_t* pixelShaderPath,
            ID3D11PixelShader** outPixelShader
        );

        void ReleaseShaderResourceView(ID3D11ShaderResourceView* shaderResourceView);
        void ReleaseVertexShaderAndInputLayout(ID3D11VertexShader* vertexShader, ID3D11InputLayout* inputLayout);
        void ReleasePixelShader(ID3D11PixelShader* pixelShader);

        void Clear();

        static ResourceManager* GetInstance() { return &instance_; }

    };

}

#endif // !INCLUDED_INC_RESOURCE_MANAGER_H