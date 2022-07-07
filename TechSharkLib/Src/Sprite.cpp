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
        //////// �����ݒ� ////////
        vertices.clear();
        vertices.reserve(vertexCapacity);
        ResourceManager& resourceManager = *(ResourceManager::GetInstance());
        HRESULT hr = S_OK;

        //////// ���_�V�F�[�_�[ + ���̓��C�A�E�g ////////
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

        //////// �摜�t�@�C���̃��[�h + ShaderResourceView ////////
        resourceManager.LoadShaderResourceView(
            device,
            filePath,
            &shaderResourceView, &texture2dDesc
        );

        //UNIT09 Section2
        //////// ���_�o�b�t�@ ////////
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

        //////// �s�N�Z���V�F�[�_�[ ////////
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
        /* ���_�o�b�t�@�̃N���A */
        vertices.clear();

        /* ���_�V�F�[�_�[��ݒ� */
        immediateContext->VSSetShader(vertexShader, nullptr, 0);

        /* �s�N�Z���V�F�[�_�[��ݒ� */
        immediateContext->PSSetShader(pixelShader, nullptr, 0);

        /* ShaderResourceView��ݒ� */
        immediateContext->PSSetShaderResources(0, 1, &shaderResourceView);
    }

    void SpriteBase::RenderFinalize(ID3D11DeviceContext* immediateContext, D3D_PRIMITIVE_TOPOLOGY primitiveTopology)
    {
        /* �o�b�t�@�[�̃`�F�b�N */
        _ASSERT_EXPR(vertices.size() <= vertexCapacity, L"Buffer is overflow.");
        _ASSERT_EXPR(vertices.empty() != true, L"Buffer is empty."); // std::memcpy�֐�����������

        /* ���_�o�b�t�@�ɒ��_�f�[�^��]�� */
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

        /* ���_�o�b�t�@�[��ݒ� */
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

        /* ���̓��C�A�E�g��ݒ� */
        immediateContext->IASetInputLayout(inputLayout);

        /* �v���~�e�B�u�g�|���W�[��ݒ� */
        immediateContext->IASetPrimitiveTopology(primitiveTopology);

        /* �`�施�߂𑗐M */
        immediateContext->Draw(static_cast<UINT>(vertices.size()), 0);
    }

    // UNIT15 (����)

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
        /* �`��O���� */
        RenderInitialize(immediateContext);

        //////// ���_�f�[�^���쐬 ////////

        /* ���݂�ViewPort�̃T�C�Y���擾 */
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
        // PrimitiveTopology�ɏ�����������(TRIANGLESTRIP)

        /* ���_�f�[�^ */
        DirectX::XMFLOAT2 afterVertices[4] = {                  // �l���̍��W
            { posX - pivotX * scaleX,                           posY - pivotY * scaleY },
            { posX - pivotX * scaleX + TextureWidth() * scaleX, posY - pivotY * scaleY },
            { posX - pivotX * scaleX,                           posY - pivotY * scaleY + TextureHeight() * scaleY },
            { posX - pivotX * scaleX + TextureWidth() * scaleX, posY - pivotY * scaleY + TextureHeight() * scaleY }
        };
        //UNIT11 Section3
        DirectX::XMFLOAT2 afterUv[4] = {                        // �l����UV���W
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {0.0f, 1.0f},
            {1.0f, 1.0f}
        };
        DirectX::XMFLOAT4 color = {red, green, blue, alpha};    // �F���

        for (DirectX::XMFLOAT2& vertex : afterVertices)
        {
            // Z����]
            ZRotation2D(&vertex, {posX, posY}, rotation);
            // �X�N���[�����W --> NDC
            vertex = ConvertScreenToNDC(vertex, viewport.Width, viewport.Height);
        }

        //////// ���_�f�[�^��o�^ ////////
        for (int i = 0; i < 4; i++)
        {
            StoreVertexBehind(afterVertices[i], color, afterUv[i]);
        }

        //////// �`�� ////////
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
        // PrimitiveTopology�ɏ�����������(TRIANGLELIST)

        /* ���_�f�[�^ */
        DirectX::XMFLOAT2 baseAfterVertices[4] = {                  // �l���̍��W
            { posX - pivotX * scaleX,                           posY - pivotY * scaleY },
            { posX - pivotX * scaleX + TextureWidth() * scaleX, posY - pivotY * scaleY },
            { posX - pivotX * scaleX,                           posY - pivotY * scaleY + TextureHeight() * scaleY },
            { posX - pivotX * scaleX + TextureWidth() * scaleX, posY - pivotY * scaleY + TextureHeight() * scaleY }
        };
        //UNIT11 Section3
        DirectX::XMFLOAT2 baseAfterUVs[4] = {                        // �l����UV���W
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {0.0f, 1.0f},
            {1.0f, 1.0f}
        };
        DirectX::XMFLOAT4 color = {red, green, blue, alpha};    // �F���

        for (DirectX::XMFLOAT2& vertex : baseAfterVertices)
        {
            // Z����]
            ZRotation2D(&vertex, {posX, posY}, rotation);
            // �X�N���[�����W --> NDC
            vertex = ConvertScreenToNDC(vertex, viewport.Width, viewport.Height);
        }

        /* ���_�f�[�^��o�^ */
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
        if (IsZeroVertex()) return; // �`�悷�钸�_��(�|���S��)��0�Ȃ烊�^�[��
        RenderFinalize(immediateContext, D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

}