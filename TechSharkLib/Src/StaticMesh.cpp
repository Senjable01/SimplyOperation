//------< include >-----------------------------------------------------------------------
#include "../Inc/StaticMesh.h"
#include <fstream>
#include <cwchar>
#include "../Inc/BinaryData.h"
#include "../Inc/StringTool.h"
#include "../Inc/ResourceManager.h"
#include "../Inc/DummyTexture.h"
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
    //      StaticMesh
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // constructor / destructor
    //------------------------------------------------------------------------------

    StaticMesh::StaticMesh(ID3D11Device* device, const wchar_t* objFilePath, bool flipVCoord) :
        vertexBuffer{nullptr},
        indexBuffer{nullptr},
        vertexShader{nullptr},
        pixelShader{nullptr},
        inputLayout{nullptr},
        objConstantBuffer{nullptr}
    {
        //////// OBJファイルを解析 ////////
        std::vector<Vertex3D> vertices;
        std::vector<std::uint32_t> indices;

        ObjFileParser(objFilePath, flipVCoord, &vertices, &indices, &subsets, &materialData);

        HRESULT hr{S_OK};

        //////// SRVを作成 ////////
        //HACK:02 リリース時に法線マップが描画されることがある。
        auto LoadSRV = [&hr, &device, texture2dDesc = D3D11_TEXTURE2D_DESC{}, this](
                const std::wstring& texPath, ID3D11ShaderResourceView** srv
            ) mutable -> void {
                ResourceManager::GetInstance()->LoadShaderResourceView(
                    device, 
                    texPath.c_str(),
                    srv, &texture2dDesc
                );
        };

        if (materialData.empty())
        {
            //////// ダミーのマテリアルを作成 ////////
            //UNIT26 Section1
            for (const MeshSubset& subset : subsets)
            {
                Material dummyMaterial = {};
                dummyMaterial.name = subset.useMtl;
                CreateDummyColorMap(device, &dummyMaterial.textureSRV, 16);
                CreateDummyNormalMap(device, &dummyMaterial.normalMapSRV, 16);
                materialData.emplace_back(dummyMaterial);
            }
        }
        else
        {
            //UNIT22 Section2
            for (auto& material : materialData)
            {
                if (0 < material.texturePath.size())
                    LoadSRV(material.texturePath, &material.textureSRV);
                else
                    CreateDummyColorMap(device, &material.textureSRV, 16);
                if (0 < material.normalMapPath.size())
                    LoadSRV(material.normalMapPath, &material.normalMapSRV);
                else
                    CreateDummyColorMap(device, &material.normalMapSRV, 16);
            }
        }

        //////// シェーダーを作成 ////////
        BinaryData vsData{"Shaders/static_mesh_vs.cso"};
        hr = device->CreateVertexShader(
            vsData.Data(), vsData.Size(),
            nullptr,
            &vertexShader
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));
        BinaryData psData{"Shaders/static_mesh_ps.cso"};
        hr = device->CreatePixelShader(
            psData.Data(), psData.Size(),
            nullptr,
            &pixelShader
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        //////// 入力レイアウトを作成 ////////
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
                "NORMAL",
                0,
                DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,
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
        hr = device->CreateInputLayout(
            inputElementDesc, _countof(inputElementDesc),
            vsData.Data(), vsData.Size(),
            &inputLayout
        );
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        //////// 頂点バッファの作成 ////////
        D3D11_BUFFER_DESC bufferDesc{};
        {
            bufferDesc.ByteWidth              = static_cast<UINT>(sizeof(Vertex3D) * vertices.size());
            bufferDesc.Usage                  = D3D11_USAGE::D3D11_USAGE_DEFAULT;
            bufferDesc.BindFlags              = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
            bufferDesc.CPUAccessFlags         = 0;
            bufferDesc.MiscFlags              = 0;
            bufferDesc.StructureByteStride    = 0;
        }
        D3D11_SUBRESOURCE_DATA subResourceData{};
        {
            subResourceData.pSysMem             = vertices.data();
            subResourceData.SysMemPitch         = 0;
            subResourceData.SysMemSlicePitch    = 0;
        }
        hr = device->CreateBuffer(&bufferDesc, &subResourceData, &vertexBuffer);
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        bufferDesc = {};
        {
            bufferDesc.ByteWidth              = static_cast<UINT>(sizeof(std::uint32_t) * indices.size());
            bufferDesc.Usage                  = D3D11_USAGE::D3D11_USAGE_DEFAULT;
            bufferDesc.BindFlags              = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
            bufferDesc.CPUAccessFlags         = 0;
            bufferDesc.MiscFlags              = 0;
            bufferDesc.StructureByteStride    = 0;
        }
        subResourceData = {};
        {
            subResourceData.pSysMem             = indices.data();
            subResourceData.SysMemPitch         = 0;
            subResourceData.SysMemSlicePitch    = 0;
        }
        hr = device->CreateBuffer(&bufferDesc, &subResourceData, &indexBuffer);
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));

        //////// コンスタントバッファを作成 ////////
        bufferDesc = {};
        {
            bufferDesc.ByteWidth              = static_cast<UINT>(sizeof(ObjectConstants));
            bufferDesc.Usage                  = D3D11_USAGE::D3D11_USAGE_DEFAULT;
            bufferDesc.BindFlags              = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
        }
        hr = device->CreateBuffer(&bufferDesc, nullptr, &objConstantBuffer);
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));
    }

    StaticMesh::~StaticMesh()
    {
        SafeRelease(vertexBuffer);
        SafeRelease(indexBuffer);
        SafeRelease(vertexShader);
        SafeRelease(pixelShader);
        SafeRelease(inputLayout);
        SafeRelease(objConstantBuffer);
    }

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void StaticMesh::ObjFileParser(
        const wchar_t* filePath,            bool flipVCoord,
        std::vector<Vertex3D>* vertices,    std::vector<std::uint32_t>* indices,
        std::vector<MeshSubset>* subsets,   std::vector<Material>* materialData
    )
    {
        size_t currentIndex = 0;
        vertices->reserve(16);
        indices->reserve(16);

        std::vector<DirectX::XMFLOAT3> positions;
        std::vector<DirectX::XMFLOAT3> normals;
        std::vector<DirectX::XMFLOAT2> uvCoords;
        positions.reserve(16);
        normals.reserve(16);
        uvCoords.reserve(16);

        //UNIT21 Section1
        std::vector<std::wstring> mtlFilePathes;
        mtlFilePathes.reserve(4);

        //UNIT22 Section1
        subsets->reserve(16);
        materialData->reserve(16);

        std::wifstream fin = {};
        fin.open(filePath);
        _ASSERT_EXPR(fin.is_open() && fin, L"OBJファイルのロードに失敗");

        //UNIT20 Section1
        wchar_t command[256];
        while (fin)
        {
            fin >> command;
            // std::wcscmp関数 ... 辞書的比較(https://runebook.dev/ja/docs/cpp/string/wide/wcscmp)
            if (std::wcscmp(command, L"v") == 0)
            {
                float x = 0.0f, y = 0.0f, z = 0.0f;
                fin >> x >> y >> z;
                positions.emplace_back(x, y, z);
                fin.ignore(1024, L'\n'); // 最大1024字を改行まで切り捨てる(https://cpprefjp.github.io/reference/istream/basic_istream/ignore.html)
            }
            else if (std::wcscmp(command, L"vt") == 0)
            {
                float u = 0.0f, v = 0.0f;
                fin >> u >> v;
                uvCoords.emplace_back(u, flipVCoord ? 1.0f - v : v);
                fin.ignore(1024, L'\n');
            }
            else if (std::wcscmp(command, L"vn") == 0)
            {
                float u = 0.0f, v = 0.0f, w = 0.0f;
                fin >> u >> v >> w;
                normals.emplace_back(u, v, w);
                fin.ignore(1024, L'\n');
            }
            else if (std::wcscmp(command, L"f") == 0)
            {
                for (size_t i = 0; i < 3; i++)
                {
                    Vertex3D vertex;
                    size_t iVertex  = 0;
                    size_t iUv   = 0;
                    size_t iNormal  = 0;

                    fin >> iVertex;
                    vertex.position = positions.at(iVertex - 1);
                    if (fin.peek() == L'/') // 一文字先が'/'
                    {
                        fin.ignore(1);
                        if (fin.peek() != L'/')
                        {
                            fin >> iUv;
                            vertex.uv = uvCoords.at(iUv - 1);
                        }
                        if (fin.peek() == L'/')
                        {
                            fin.ignore(1);
                            fin >> iNormal;
                            vertex.normal = normals.at(iNormal - 1);
                        }
                    }
                    vertices->emplace_back(vertex);
                    indices->emplace_back(static_cast<std::uint32_t>(currentIndex));
                    currentIndex++;
                }
                fin.ignore(1024, L'\n');
            }
            //UNIT21 Section1
            else if (std::wcscmp(command, L"mtllib") == 0)
            {
                wchar_t mtllib[256];
                fin >> mtllib;
                mtlFilePathes.emplace_back(mtllib);
            }
            //UNIT22 Section1(2)
            else if (std::wcscmp(command, L"usemtl") == 0)
            {
                wchar_t usemtl[256];
                fin >> usemtl;
                subsets->emplace_back(usemtl, static_cast<std::uint32_t>(indices->size()), 0);
            }
            else
            {
                fin.ignore(1024, L'\n');
            }
        }
        fin.close();

        //UNIT22 Section1(3)
        auto latestSubset = subsets->rbegin();
        latestSubset->indexCount = static_cast<std::uint32_t>(indices->size()) - latestSubset->startIndex;
        for (auto rItr = subsets->rbegin() + 1, rEnd = subsets->rend(); rItr != rEnd; rItr++)
        {
            rItr->indexCount = (rItr - 1)->startIndex - rItr->startIndex;
        }

        //UNIT21 Section2
        std::wstring mtlFilePath = string::ReplaceFileName(filePath, mtlFilePathes.front());
        fin.open(mtlFilePath.c_str());
        if (fin.is_open() && fin)
        {
            while (fin)
            {
                fin >> command;

                //UNIT22 Section1(4)
                if (std::wcscmp(command, L"newmtl") == 0)
                {
                    fin.ignore();
                    wchar_t mtlName[256];
                    fin >> mtlName;
                    materialData->emplace_back(mtlName);
                }
                else if (std::wcscmp(command, L"map_Kd") == 0)
                {
                    fin.ignore();
                    wchar_t mapKb[256];
                    fin >> mapKb;
                    materialData->rbegin()->texturePath = string::ReplaceFileName(filePath, mapKb);
                    fin.ignore(1024, L'\n');
                }
                //UNIT25 Section1(2)
                else if (std::wcscmp(command, L"map_bump") == 0 || std::wcscmp(command, L"bump") == 0)
                {
                    fin.ignore();
                    wchar_t mapNormal[256];
                    fin >> mapNormal;
                    materialData->rbegin()->normalMapPath = string::ReplaceFileName(filePath, mapNormal);
                    fin.ignore(1024, L'\n');
                }
                else if (std::wcscmp(command, L"Ka") == 0)
                {
                    float r = 0.0f, g = 0.0f, b = 0.0f;
                    fin >> r >> g >> b;
                    materialData->rbegin()->lightKa = DirectX::XMFLOAT4{r, g, b, 1.0f};
                    fin.ignore(1024, L'\n');
                }
                else if (std::wcscmp(command, L"Kd") == 0)
                {
                    float r = 0.0f, g = 0.0f, b = 0.0f;
                    fin >> r >> g >> b;
                    materialData->rbegin()->lightKd = DirectX::XMFLOAT4{r, g, b, 1.0f};
                    fin.ignore(1024, L'\n');
                }
                else if (std::wcscmp(command, L"Ks") == 0)
                {
                    float r = 0.0f, g = 0.0f, b = 0.0f;
                    fin >> r >> g >> b;
                    materialData->rbegin()->lightKs = DirectX::XMFLOAT4{r, g, b, 1.0f};
                    fin.ignore(1024, L'\n');
                }
                else
                {
                    fin.ignore(1024, L'\n');
                }
            }
            fin.close();
        }
        else
        {
            ExpressDebugLog(L"<INFORMATION>", filePath, L"の情報からMTLファイルは見つかりませんでした。");
        }
    }

    void StaticMesh::Render(
        ID3D11DeviceContext* immediateContext,
        const DirectX::XMFLOAT4X4& world, const DirectX::XMFLOAT4& materialColor
    )
    {
        std::uint32_t stride = sizeof(Vertex3D);
        std::uint32_t offset = 0;

        //////// 入力アセンブラを設定 ////////
        immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        immediateContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
        immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        immediateContext->IASetInputLayout(inputLayout);

        //////// シェーダーを設定 ////////
        immediateContext->VSSetShader(vertexShader, nullptr, 0);
        immediateContext->PSSetShader(pixelShader, nullptr, 0);
        //UNIT22 Section3
        for (const Material& material : materialData)
        {
            immediateContext->PSSetShaderResources(0, 1, &material.textureSRV);
            immediateContext->PSSetShaderResources(1, 1, &material.normalMapSRV);

            //////// コンスタントバッファを設定 ////////
            SetObjectConstantBuffer(immediateContext, &objConstantBuffer, world, materialColor);

            for (const MeshSubset& subset : subsets)
            {
                if (material.name != subset.useMtl)
                    continue;

                //////// 描画命令 ////////
                immediateContext->DrawIndexed(subset.indexCount, subset.startIndex, 0);
            }
        }

    }
}