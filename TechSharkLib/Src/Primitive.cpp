//------< include >-----------------------------------------------------------------------
#include "../Inc/Primitive.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

#include "../Inc/DebugTools.h"
#include "../Inc/BinaryData.h"
#include "../Inc/Arithmetic.h"
#include "../Inc/MiscTools.h"

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
    //      PrimitiveVertex2D
    // 
    //========================================================================================
    struct Vertex
    {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT4 color;

        Vertex() : position{0.0f, 0.0f, 0.0f}, color{0.0f, 0.0f, 0.0f, 0.0f} {}
        Vertex(
            const DirectX::XMFLOAT2& position,
            const DirectX::XMFLOAT4& color
        ) :
            position{position.x, position.y, 0.0f}, color{color}
        {
        }
        Vertex(
            const DirectX::XMFLOAT3& position,
            const DirectX::XMFLOAT4& color
        ) :
            position{position}, color{color}
        {
        }
    };

    //========================================================================================
    // 
    //      Primitive
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // constructor / destructor
    //------------------------------------------------------------------------------

    //UNIT09 Section0

    Primitive::Primitive(ID3D11Device* device, size_t vertexNum) :
        vertexShader{nullptr}, pixelShader{nullptr},
        inputLayout{nullptr},
        vertexBuffer{nullptr}
    {
        HRESULT hr = S_OK;

        /* 頂点シェーダー */
        //UNIT07 Section1
        BinaryData vsData = {"Shaders/primitive_vs.cso"};
        hr = device->CreateVertexShader(
            vsData.Data(), vsData.Size(),
            nullptr,
            &vertexShader
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        /* 入力レイアウト */
        //UNIT07 Section2
        D3D11_INPUT_ELEMENT_DESC inputElementDesc[] // 入力スロットの設定
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
            }
        };
        hr = device->CreateInputLayout(
            inputElementDesc, _countof(inputElementDesc),
            vsData.Data(), vsData.Size(),
            &inputLayout
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        /* 頂点バッファ */
        //UNIT07 Section3
        //UNIT09 Section1
        D3D11_BUFFER_DESC vertexBufferDesc          = {};
        {
            vertexBufferDesc.ByteWidth              = static_cast<UINT>(sizeof(Vertex) * vertexNum);
            vertexBufferDesc.Usage                  = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
            vertexBufferDesc.BindFlags              = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
            vertexBufferDesc.CPUAccessFlags         = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
            vertexBufferDesc.MiscFlags              = 0;
            vertexBufferDesc.StructureByteStride    = 0;
        }
        Vertex* vertexData = new Vertex[vertexNum]{};
        D3D11_SUBRESOURCE_DATA vertexBufferSubResourceData = {};
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

        /* ピクセルシェーダー */
        //UNIT07 Section4
        BinaryData psData = {"Shaders/primitive_ps.cso"};
        hr = device->CreatePixelShader(
            psData.Data(), psData.Size(),
            nullptr,
            &pixelShader
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

    }

    Primitive::~Primitive()
    {
        SafeRelease(vertexShader);
        SafeRelease(pixelShader);
        SafeRelease(inputLayout);
        SafeRelease(vertexBuffer);
    }

    //========================================================================================
    // 
    //      PrimitiveRect
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void PrimitiveRect::Render(
        ID3D11DeviceContext* immediateContext,
        float posX,     float posY,
        float width,    float height,
        float pivotX,   float pivotY,
        float rotation,
        float red, float green, float blue, float alpha
    )
    {
        if (NearlyEqual(width, 0.0f) || NearlyEqual(height, 0.0f))
            return;
        if (alpha < NEAR_ZERO)
            return;

        //UNIT08

        /* 頂点シェーダーを設定 */
        immediateContext->VSSetShader(vertexShader, nullptr, 0);

        /* ピクセルシェーダーを設定 */
        immediateContext->PSSetShader(pixelShader, nullptr, 0);

        /* 頂点データを作成 */
        //UNIT09 Section2
        D3D11_VIEWPORT viewport = {};
        UINT viewPortAmount     = 1;
        immediateContext->RSGetViewports(&viewPortAmount, &viewport);
        DirectX::XMFLOAT2 afterVertices[VERTEX_NUM] = { // 四隅の座標
            { posX - pivotX,            posY - pivotY },
            { posX - pivotX + width,    posY - pivotY },
            { posX - pivotX,            posY - pivotY + height },
            { posX - pivotX + width,    posY - pivotY + height }
        };

        DirectX::XMFLOAT4 color = {red, green, blue, alpha};    // 色情報

        for (DirectX::XMFLOAT2& vertex : afterVertices)
        {
            // Z軸回転
            ZRotation2D(&vertex, {posX, posY}, rotation);
            // スクリーン座標 --> NDC
            vertex = ConvertScreenToNDC(vertex, viewport.Width, viewport.Height);
        }

        /* 頂点バッファに頂点データを転写 */
        HRESULT hr = S_OK;
        D3D11_MAPPED_SUBRESOURCE mappedSubResource = {};
        hr = immediateContext->Map(
            vertexBuffer,
            0,
            D3D11_MAP::D3D11_MAP_WRITE_DISCARD,
            0,
            &mappedSubResource
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));
        Vertex* vertexData{ reinterpret_cast<Vertex*>(mappedSubResource.pData) };
        if (vertexData)
        {
            vertexData[0] = {afterVertices[0], color};
            vertexData[1] = {afterVertices[1], color};
            vertexData[2] = {afterVertices[2], color};
            vertexData[3] = {afterVertices[3], color};
        }
        immediateContext->Unmap(vertexBuffer, 0);

        /* 頂点バッファを設定 */
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

        /* 入力レイアウトを設定 */
        immediateContext->IASetInputLayout(inputLayout);

        /* プリミティブトポロジーを設定 */
        immediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

        /* 描画命令を送信 */
        immediateContext->Draw(VERTEX_NUM, 0);
    }

}