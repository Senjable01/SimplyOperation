#ifndef INCLUDED_INC_SPRITE_H
#define INCLUDED_INC_SPRITE_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning( disable : 4458 )

//------< include >-----------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include "SpriteID.h"
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
    //UNIT11_0

    //========================================================================================
    // 
    //      SpriteBase
    // 
    //========================================================================================
    class SpriteBase
    {
    private:
        struct Vertex
        {
            DirectX::XMFLOAT3 position;
            DirectX::XMFLOAT4 color;
            DirectX::XMFLOAT2 uv;

            Vertex() : position{0.0f, 0.0f, 0.0f}, color{0.0f, 0.0f, 0.0f, 0.0f}, uv{0.0f, 0.0f} {}
            Vertex(
                const DirectX::XMFLOAT3& position,
                const DirectX::XMFLOAT4& color,
                const DirectX::XMFLOAT2& uv
            ) :
                position{position}, color{color}, uv{uv}
            {
            }
        };

        ID3D11VertexShader*         vertexShader;
        ID3D11PixelShader*          pixelShader;
        ID3D11InputLayout*          inputLayout;
        ID3D11Buffer*               vertexBuffer;
        ID3D11ShaderResourceView*   shaderResourceView;
        D3D11_TEXTURE2D_DESC        texture2dDesc;

        std::vector<Vertex>         vertices;       // Store vertex information.
        const size_t                vertexCapacity; // Maximum amount of vertex information that can be stored.

    protected:
        void RenderInitialize(ID3D11DeviceContext* immediateContext);
        void RenderFinalize(ID3D11DeviceContext* immediateContext, D3D_PRIMITIVE_TOPOLOGY primitiveTopology);

        void StoreVertexBehind(
            const DirectX::XMFLOAT2& position,
            const DirectX::XMFLOAT4& color,
            const DirectX::XMFLOAT2& uv
        )
        {
            vertices.emplace_back(DirectX::XMFLOAT3{position.x, position.y, 0.0f}, color, uv);
        }
        void StoreVertexBehind(
            const DirectX::XMFLOAT3& position,
            const DirectX::XMFLOAT4& color,
            const DirectX::XMFLOAT2& uv
        )
        {
            vertices.emplace_back(position, color, uv);
        }

    public:
        SpriteBase(ID3D11Device* device, const wchar_t* filePath, size_t vertexCapacity);
        virtual ~SpriteBase();

        virtual void Render(
            ID3D11DeviceContext* immediateContext,
            float posX,     float posY,
            float scaleX,   float scaleY,
            float pivotX,   float pivotY,
            float rotation/*radian*/,
            float red, float green, float blue, float alpha
        ) = 0;
        virtual void Render(
            ID3D11DeviceContext* immediateContext,
            float posX,     float posY,
            float scaleX,   float scaleY,
            float texelX,   float texelY, float texelW, float texelH,
            float pivotX,   float pivotY,
            float rotation/*radian*/,
            float red, float green, float blue, float alpha
        ) = 0;

        float TextureWidth() const noexcept { return static_cast<float>(texture2dDesc.Width); }
        float TextureHeight() const noexcept { return static_cast<float>(texture2dDesc.Height); }

    };

    //========================================================================================
    // 
    //      Sprite
    // 
    //========================================================================================
    class Sprite : public SpriteBase
    {
    private:
        static constexpr size_t VERTEX_NUM = 4;

    public:
        Sprite() = delete;
        Sprite(ID3D11Device* device, const wchar_t* filePath) : SpriteBase{device, filePath, VERTEX_NUM} {}
        ~Sprite() override {}

        void Render(
            ID3D11DeviceContext* immediateContext,
            float posX,     float posY,
            float scaleX,   float scaleY,
            float pivotX,   float pivotY,
            float rotation/*radian*/,
            float red, float green, float blue, float alpha
        ) override;
        void Render(
            ID3D11DeviceContext* immediateContext,
            float posX,     float posY,
            float scaleX,   float scaleY,
            float texelX,   float texelY, float texelW, float texelH,
            float pivotX,   float pivotY,
            float rotation/*radian*/,
            float red, float green, float blue, float alpha
        ) override;

    };

    //========================================================================================
    // 
    //      SpriteBatch
    // 
    //========================================================================================
    class SpriteBatch : public SpriteBase
    {
    private:
        const size_t maxInstace;
        static constexpr size_t VERTEX_NUM = 6;

    public:
        SpriteBatch() = delete;
        SpriteBatch(ID3D11Device* device, const wchar_t* filePath, size_t maxInstance) : 
            maxInstace{maxInstance}, SpriteBase{device, filePath, VERTEX_NUM * maxInstance}
        {
        }

        void Begin(ID3D11DeviceContext* immediateContext);
        void Render(
            ID3D11DeviceContext* immediateContext,
            float posX, float posY,
            float scaleX, float scaleY,
            float pivotX, float pivotY,
            float rotation/*radian*/,
            float red, float green, float blue, float alpha
        ) override;
        void Render(
            ID3D11DeviceContext* immediateContext,
            float posX,     float posY,
            float scaleX,   float scaleY,
            float texelX,   float texelY, float texelW, float texelH,
            float pivotX,   float pivotY,
            float rotation/*radian*/,
            float red, float green, float blue, float alpha
        ) override;
        void End(ID3D11DeviceContext* immediateContext);

    };

}

#endif // !INCLUDED_INC_SPRITE_H