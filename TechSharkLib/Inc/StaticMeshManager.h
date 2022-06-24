#ifndef INCLUDED_INC_STATIC_MESH_MANAGER_H
#define INCLUDED_INC_STATIC_MESH_MANAGER_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning (disable : 4458)

//------< include >-----------------------------------------------------------------------
#include <d3d11.h>
#include <map>
#include "../Inc/StaticMeshID.h"
#include <memory>
#include "../Inc/StaticMesh.h"

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
    //      StaticMeshManager
    // 
    //========================================================================================
    class StaticMeshManager
    {
    private:
        ID3D11Device*           device;             // device(キャッシュ用)
        ID3D11DeviceContext*    immediateContext;   // immediateContext(キャッシュ用)

        std::map<StaticMeshID, std::unique_ptr<StaticMesh>> staticMeshMap;

        static unsigned int nextId;

    public:
        StaticMeshManager() : device{nullptr}, immediateContext{nullptr} {}
        StaticMeshManager(const StaticMeshManager&) = delete;
        StaticMeshManager& operator=(const StaticMeshManager&) = delete;
        StaticMeshManager(StaticMeshManager&&) noexcept = delete;
        StaticMeshManager& operator=(StaticMeshManager&&) noexcept = delete;
        ~StaticMeshManager() { ReleaseAll(); }

        void Initialize(ID3D11Device* device, ID3D11DeviceContext* immediateContext);

        StaticMeshID Load(const wchar_t* filePath, bool flipVCoord);
        void Render(const StaticMeshID& id, const DirectX::XMFLOAT4X4& world, const DirectX::XMFLOAT4& materialColor);
        void Release(const StaticMeshID& id);

        void ReleaseAll();

    };

}

#endif // !INCLUDED_INC_STATIC_MESH_MANAGER_H