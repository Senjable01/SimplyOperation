//------< include >-----------------------------------------------------------------------
#include "../Inc/Sprite.h"
#include "../Inc/ResourceManager.h"
#include "../Inc/MiscTools.h"
#include "../Inc/DebugTools.h"
#include "../Inc/Arithmetic.h"

//UNIT10

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
    //      SpriteBase
    // 
    //========================================================================================

    // UNIT09 Section0

    //--------------------------------------------------------------------------
    // constructor / destructor
    //--------------------------------------------------------------------------
    
    // UNIT07 Section0

    SpriteBase::SpriteBase(ID3D11Device* device, const wchar_t* filePath, size_t vertexCapacity) : 
        vertexShader{nullptr}, pixelShader{nullptr},
        inputLayout{nullptr},
        vertexBuffer{nullptr},
        shaderResourceView{nullptr}, texture2dDesc{},
        vertexCapacity{vertexCapacity}
    {
        //////// 初期設定 ////////
        vertices.clear();
        vertices.reserve(vertexCapacity);
        ResourceManager& resourceManager = *(ResourceManager::GetInstance());
        HRESULT hr = S_OK;

        //////// 頂点シェーダー + 入力レイアウト ////////
        D3D11_INPUT_ELEMENT_DESC inputElementDesc[]
        {
            {
                "POSITION",
                0,
                DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,
                0,
                D3D11_APPEND_ALIGNED_ELEMENT,
                D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
                0
            },
            {
                "COLOR",
                0,
                DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
                0,
                D3D11_APPEND_ALIGNED_ELEMENT,
                D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
                0
            },
            {
                "UV_COORD",
                0,
                DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
                0,
                D3D11_APPEND_ALIGNED_ELEMENT,
                D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
                0
            }
        };
        resourceManager.LoadVertexShaderAndInputLayout(
            device,
            inputElementDesc, _countof(inputElementDesc),
            L"Shaders/sprite_vs.cso",
            &vertexShader, &inputLayout
        );

        //////// 画像ファイルのロード + ShaderResourceView ////////
        resourceManager.LoadShaderResourceView(
            device,
            filePath,
            &shaderResourceView, &texture2dDesc
        );

        //UNIT09 Section2
        //////// 頂点バッファ ////////
        D3D11_BUFFER_DESC vertexBufferDesc{};
        {
            vertexBufferDesc.ByteWidth              = static_cast<UINT>(sizeof(Vertex) * vertexCapacity);
            vertexBufferDesc.Usage                  = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
            vertexBufferDesc.BindFlags              = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
            vertexBufferDesc.CPUAccessFlags         = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
            vertexBufferDesc.MiscFlags              = 0;
            vertexBufferDesc.StructureByteStride    = 0;
        }
        Vertex* vertexData = new Vertex[vertexCapacity];
        D3D11_SUBRESOURCE_DATA vertexBufferSubResourceData  = {};
        {
            vertexBufferSubResourceData.pSysMem             = vertexData;
            vertexBufferSubResourceData.SysMemPitch         = 0;
            vertexBufferSubResourceData.SysMemSlicePitch    = 0;
        }
        hr = device->CreateBuffer(
            &vertexBufferDesc,
            &vertexBufferSubResourceData,
            &vertexBuffer
        );
        delete[] vertexData;
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        //////// ピクセルシェーダー ////////
        resourceManager.LoadPixelShader(
            device,
            L"Shaders/sprite_ps.cso",
            &pixelShader
        );

    }

    SpriteBase::~SpriteBase()
    {
        ResourceManager& resourceManager = *(ResourceManager::GetInstance());
        resourceManager.ReleaseVertexShaderAndInputLayout(vertexShader, inputLayout);
        resourceManager.ReleaseShaderResourceView(shaderResourceView);
        SafeRelease(vertexBuffer);
        resourceManager.ReleasePixelShader(pixelShader);
    }

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void SpriteBase::RenderInitialize(ID3D11DeviceContext* immediateContext)
    {
        /* 頂点バッファのクリア */
        vertices.clear();

        /* 頂点シェーダーを設定 */
        immediateContext->VSSetShader(vertexShader, nullptr, 0);

        /* ピクセルシェーダーを設定 */
        immediateContext->PSSetShader(pixelShader, nullptr, 0);

        /* ShaderResourceViewを設定 */
        immediateContext->PSSetShaderResources(0, 1, &shaderResourceView);
    }

    void SpriteBase::RenderFinalize(ID3D11DeviceContext* immediateContext, D3D_PRIMITIVE_TOPOLOGY primitiveTopology)
    {
        /* バッファーのチェック */
        _ASSERT_EXPR(vertices.size() <= vertexCapacity, L"Buffer is overflow.");
        _ASSERT_EXPR(vertices.empty() != true, L"Buffer is empty."); // std::memcpy関数が動く条件

        /* 頂点バッファに頂点データを転写 */
        HRESULT hr = S_OK;
        D3D11_MAPPED_SUBRESOURCE mappedSubResource = {};
        hr = immediateContext->Map(
            vertexBuffer,
            0u,
            D3D11_MAP::D3D11_MAP_WRITE_DISCARD,
            0u,
            &mappedSubResource
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        Vertex* vertexData{reinterpret_cast<Vertex*>(mappedSubResource.pData)};
        if (vertexData)
        {
            //std::memcpy function https://rinatz.github.io/cpp-book/ch12-04-byte-array-manipulations/
            std::memcpy(vertexData, &(vertices.front()), vertices.size() * sizeof(Vertex));
            //memcpy_s(vertexData, vertexCapacity * sizeof(Vertex2D), &(vertices.at(0)), vertices.size() * sizeof(Vertex2D));
        }
        immediateContext->Unmap(vertexBuffer, 0);

        /* 頂点バッファーを設定 */
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

        /* 入力レイアウトを設定 */
        immediateContext->IASetInputLayout(inputLayout);

        /* プリミティブトポロジーを設定 */
        immediateContext->IASetPrimitiveTopology(primitiveTopology);

        /* 描画命令を送信 */
        immediateContext->Draw(static_cast<UINT>(vertices.size()), 0);
    }

    // UNIT15 (消滅)

    //========================================================================================
    // 
    //      Sprite
    // 
    //========================================================================================

    //--------------------------------------------------------------------------
    // member function
    //--------------------------------------------------------------------------

    void Sprite::Render(
        ID3D11DeviceContext* immediateContext,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    )
    {
        /* 描画前準備 */
        RenderInitialize(immediateContext);

        //////// 頂点データを作成 ////////

        /* 現在のViewPortのサイズを取得 */
        D3D11_VIEWPORT viewport = {};
        UINT viewPortAmount     = 1;
        immediateContext->RSGetViewports(&viewPortAmount, &viewport);

        // (0) *----* (1)
        //     |   /|
        //     |  / |
        //     | /  |
        //     |/   |
        // (2) *----* (3)
        //
        // PrimitiveTopologyに準拠した順番(TRIANGLESTRIP)

        /* 頂点データ */
        DirectX::XMFLOAT2 afterVertices[4] = {                  // 四隅の座標
            { posX - pivotX * scaleX,                           posY - pivotY * scaleY },
            { posX - pivotX * scaleX + TextureWidth() * scaleX, posY - pivotY * scaleY },
            { posX - pivotX * scaleX,                           posY - pivotY * scaleY + TextureHeight() * scaleY },
            { posX - pivotX * scaleX + TextureWidth() * scaleX, posY - pivotY * scaleY + TextureHeight() * scaleY }
        };
        //UNIT11 Section3
        DirectX::XMFLOAT2 afterUv[4] = {                        // 四隅のUV座標
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {0.0f, 1.0f},
            {1.0f, 1.0f}
        };
        DirectX::XMFLOAT4 color = {red, green, blue, alpha};    // 色情報

        for (DirectX::XMFLOAT2& vertex : afterVertices)
        {
            // Z軸回転
            ZRotation2D(&vertex, {posX, posY}, rotation);
            // スクリーン座標 --> NDC
            vertex = ConvertScreenToNDC(vertex, viewport.Width, viewport.Height);
        }

        //////// 頂点データを登録 ////////
        for (int i = 0; i < 4; i++)
        {
            StoreVertexBehind(afterVertices[i], color, afterUv[i]);
        }

        //////// 描画 ////////
        RenderFinalize(immediateContext, D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    }

    void Sprite::Render(
        ID3D11DeviceContext* immediateContext,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float texelX,   float texelY, float texelW, float texelH,
        float pivotX,   float pivotY,
        float rotation,
        float red, float green, float blue, float alpha
    )
    {
        RenderInitialize(immediateContext);

        D3D11_VIEWPORT viewport = {};
        UINT viewPortAmount     = 1;
        immediateContext->RSGetViewports(&viewPortAmount, &viewport);

        DirectX::XMFLOAT2 afterVertices[4] = {
            { posX - pivotX * scaleX,                   posY - pivotY * scaleY },
            { posX - pivotX * scaleX + texelW * scaleX, posY - pivotY * scaleY },
            { posX - pivotX * scaleX,                   posY - pivotY * scaleY + texelH * scaleY },
            { posX - pivotX * scaleX + texelW * scaleX, posY - pivotY * scaleY + texelH * scaleY }
        };

        const float texWidth = static_cast<float>(TextureWidth());
        const float texHeight = static_cast<float>(TextureHeight());
        DirectX::XMFLOAT2 afterUv[4] = {
            { texelX / texWidth,            texelY / texHeight },
            { (texelX + texelW) / texWidth, texelY / texHeight },
            { texelX / texWidth,            (texelY + texelH) / texHeight },
            { (texelX + texelW) / texWidth, (texelY + texelH) / texHeight }
        };

        DirectX::XMFLOAT4 color = {red, green, blue, alpha};

        for (DirectX::XMFLOAT2& vertex : afterVertices)
        {
            ZRotation2D(&vertex, {posX, posY}, rotation);
            vertex = ConvertScreenToNDC(vertex, viewport.Width, viewport.Height);
        }

        for (int i = 0; i < 4; i++)
        {
            StoreVertexBehind(afterVertices[i], color, afterUv[i]);
        }

        RenderFinalize(immediateContext, D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    }

    //========================================================================================
    // 
    //      SpriteBatch
    // 
    //========================================================================================

    //--------------------------------------------------------------------------
    // member function
    //--------------------------------------------------------------------------

    void SpriteBatch::Begin(ID3D11DeviceContext* immediateContext)
    {
        RenderInitialize(immediateContext);
    }
    void SpriteBatch::Render(
        ID3D11DeviceContext* immediateContext,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    )
    {
        D3D11_VIEWPORT viewport = {};
        UINT viewPortAmount     = 1;
        immediateContext->RSGetViewports(&viewPortAmount, &viewport);

        // (0) *----* (1)     *----* (4)
        //     |   /|         |   /|
        //     |  / |         |  / |
        //     | /  |         | /  |
        //     |/   |         |/   |
        // (2) *----*     (3) *----* (5)
        //
        // PrimitiveTopologyに準拠した順番(TRIANGLELIST)

        /* 頂点データ */
        DirectX::XMFLOAT2 baseAfterVertices[4] = {                  // 四隅の座標
            { posX - pivotX * scaleX,                           posY - pivotY * scaleY },
            { posX - pivotX * scaleX + TextureWidth() * scaleX, posY - pivotY * scaleY },
            { posX - pivotX * scaleX,                           posY - pivotY * scaleY + TextureHeight() * scaleY },
            { posX - pivotX * scaleX + TextureWidth() * scaleX, posY - pivotY * scaleY + TextureHeight() * scaleY }
        };
        //UNIT11 Section3
        DirectX::XMFLOAT2 baseAfterUVs[4] = {                        // 四隅のUV座標
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {0.0f, 1.0f},
            {1.0f, 1.0f}
        };
        DirectX::XMFLOAT4 color = {red, green, blue, alpha};    // 色情報

        for (DirectX::XMFLOAT2& vertex : baseAfterVertices)
        {
            // Z軸回転
            ZRotation2D(&vertex, {posX, posY}, rotation);
            // スクリーン座標 --> NDC
            vertex = ConvertScreenToNDC(vertex, viewport.Width, viewport.Height);
        }

        /* 頂点データを登録 */
        StoreVertexBehind(baseAfterVertices[0], color, baseAfterUVs[0]);
        StoreVertexBehind(baseAfterVertices[1], color, baseAfterUVs[1]);
        StoreVertexBehind(baseAfterVertices[2], color, baseAfterUVs[2]);
        StoreVertexBehind(baseAfterVertices[2], color, baseAfterUVs[2]);
        StoreVertexBehind(baseAfterVertices[1], color, baseAfterUVs[1]);
        StoreVertexBehind(baseAfterVertices[3], color, baseAfterUVs[3]);
    }
    void SpriteBatch::Render(
        ID3D11DeviceContext* immediateContext,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float texelX,   float texelY, float texelW, float texelH,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    )
    {
        D3D11_VIEWPORT viewport = {};
        UINT viewPortAmount     = 1;
        immediateContext->RSGetViewports(&viewPortAmount, &viewport);

        DirectX::XMFLOAT2 baseAfterVertices[4] = {
            { posX - pivotX * scaleX,                   posY - pivotY * scaleY },
            { posX - pivotX * scaleX + texelW * scaleX, posY - pivotY * scaleY },
            { posX - pivotX * scaleX,                   posY - pivotY * scaleY + texelH * scaleY },
            { posX - pivotX * scaleX + texelW * scaleX, posY - pivotY * scaleY + texelH * scaleY }
        };
        const float texWidth    = static_cast<float>(TextureWidth());
        const float texHeight   = static_cast<float>(TextureHeight());
        DirectX::XMFLOAT2 baseAfterUVs[4] = {
            { texelX / texWidth,            texelY / texHeight },
            { (texelX + texelW) / texWidth, texelY / texHeight },
            { texelX / texWidth,            (texelY + texelH) / texHeight },
            { (texelX + texelW) / texWidth, (texelY + texelH) / texHeight }
        };
        DirectX::XMFLOAT4 color = { red, green, blue, alpha };

        for (DirectX::XMFLOAT2& vertex : baseAfterVertices)
        {
            ZRotation2D(&vertex, { posX, posY }, rotation);
            vertex = ConvertScreenToNDC(vertex, viewport.Width, viewport.Height);
        }

        StoreVertexBehind(baseAfterVertices[0], color, baseAfterUVs[0]);
        StoreVertexBehind(baseAfterVertices[1], color, baseAfterUVs[1]);
        StoreVertexBehind(baseAfterVertices[2], color, baseAfterUVs[2]);
        StoreVertexBehind(baseAfterVertices[2], color, baseAfterUVs[2]);
        StoreVertexBehind(baseAfterVertices[1], color, baseAfterUVs[1]);
        StoreVertexBehind(baseAfterVertices[3], color, baseAfterUVs[3]);
    }
    void SpriteBatch::End(ID3D11DeviceContext* immediateContext)
    {
        if (IsZeroVertex()) return; // 描画する頂点数(ポリゴン)が0ならリターン
        RenderFinalize(immediateContext, D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

}