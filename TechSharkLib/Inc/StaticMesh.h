#ifndef INCLUDED_INC_STATIC_MESH_H
#define INCLUDED_INC_STATIC_MESH_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning (disable : 4458)

//------< include >-----------------------------------------------------------------------
#include <DirectXMath.h>
#include <d3d11.h>
#include <cstdint>
#include "../Inc/ConstantBuffer.h"
#include <string>
#include <wrl.h>
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
    //UNIT20 Section0
    //========================================================================================
    // 
    //      StaticMesh
    // 
    //========================================================================================
    class StaticMesh
    {
    private:
        struct Vertex3D
        {
            DirectX::XMFLOAT3 position;
            DirectX::XMFLOAT3 normal;
            DirectX::XMFLOAT2 uv;

            Vertex3D() : position{0.0f, 0.0f, 0.0f}, normal{0.0f, 0.0f, 0.0f}, uv{0.0f, 0.0f} {}
            Vertex3D(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& normal, const DirectX::XMFLOAT2& uv) :
                position{position}, normal{normal}, uv{uv}
            {
            }
        };

        ID3D11Buffer* vertexBuffer;
        ID3D11Buffer* indexBuffer;

        ID3D11VertexShader* vertexShader;
        ID3D11PixelShader* pixelShader;
        ID3D11InputLayout* inputLayout;
        ID3D11Buffer* objConstantBuffer;

        //UNIT22 Section1(0)
        struct MeshSubset
        {
            std::wstring useMtl;        // 使用するマテリアル
            std::uint32_t startIndex;   // 先頭?とする頂点バッファのインデックス
            std::uint32_t indexCount;   // 先頭から何番目か？

            MeshSubset() : useMtl{}, startIndex{0}, indexCount{0} {}
            MeshSubset(wchar_t useMtl[], std::uint32_t startIndex, std::uint32_t indexCount) :
                useMtl{useMtl}, startIndex{startIndex}, indexCount{indexCount}
            {
            }
        };
        std::vector<MeshSubset> subsets;
        struct Material
        {
            std::wstring        name;
            DirectX::XMFLOAT4   lightKa; // アンビエント(環境光)
            DirectX::XMFLOAT4   lightKd; // ディフューズ（拡散反射光）
            DirectX::XMFLOAT4   lightKs; // スペキュラー（鏡面反射光）
            //UNIT25 Section0
            //UNIT25 Section1(1)
            std::wstring texturePath;
            std::wstring normalMapPath;
            ID3D11ShaderResourceView* textureSRV;
            ID3D11ShaderResourceView* normalMapSRV;

            Material() :
                name{},
                lightKa{0.2f, 0.2f, 0.2f, 1.0f}, lightKd{0.8f, 0.8f, 0.8f, 1.0f}, lightKs{1.0f, 1.0f, 1.0f, 1.0f},
                texturePath{}, textureSRV{nullptr}, normalMapPath{}, normalMapSRV{nullptr}
            {
            }
            explicit Material(wchar_t name[]) :
                name{name},
                lightKa{0.2f, 0.2f, 0.2f, 1.0f}, lightKd{0.8f, 0.8f, 0.8f, 1.0f}, lightKs{1.0f, 1.0f, 1.0f, 1.0f},
                texturePath{}, textureSRV{nullptr}, normalMapPath{}, normalMapSRV{nullptr}
            {
            }
        };
        std::vector<Material> materialData;

        void ObjFileParser(
            const wchar_t* filePath,            bool flipVCoord,
            std::vector<Vertex3D>* vertices,    std::vector<std::uint32_t>* indices,
            std::vector<MeshSubset>* subsets,   std::vector<Material>* materialData
        );

    public:
        StaticMesh(ID3D11Device* device, const wchar_t* objFilePath, bool flipVCoord);
        virtual ~StaticMesh();

        void Render(
            ID3D11DeviceContext* immediateContext,
            const DirectX::XMFLOAT4X4& world, const DirectX::XMFLOAT4& materialColor
        );

    };
}

#endif // !INCLUDED_INC_STATIC_MESH_H