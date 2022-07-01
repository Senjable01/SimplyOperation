#ifndef INCLUDED_INC_STATIC_MESH_RENDERER_H
#define INCLUDED_INC_STATIC_MESH_RENDERER_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning( disable : 4458 )

//------< include >-----------------------------------------------------------------------
#include "Component.h"
#include "StaticMeshID.h"
#include <DirectXMath.h>

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
    //      StaticMeshRendererDesc
    // 
    //========================================================================================
    struct StaticMeshRendererDesc
    {
        std::wstring        objFilePath;
        bool                flipVCoord;
        DirectX::XMFLOAT4   materialColor;

        StaticMeshRendererDesc() : objFilePath{}, flipVCoord{false}, materialColor{0.0f, 0.0f, 0.0f, 1.0f} {}
        StaticMeshRendererDesc(const wchar_t* objFilePath, bool reverseVCoord, const DirectX::XMFLOAT4& materialColor) :
            objFilePath{objFilePath}, flipVCoord{reverseVCoord}, materialColor{materialColor}
        {
        }
    };

    //------< class >-------------------------------------------------------------------------

    class Transform3D;

    //========================================================================================
    // 
    //      StaticMeshRenderer
    // 
    //========================================================================================
    class StaticMeshRenderer : public Component
    {
    TSL_DEFINE_COMPONENT(StaticMeshRenderer);
    private:
        Transform3D*            transform;

        StaticMeshID            meshId;
        DirectX::XMFLOAT4       materialColor;

        StaticMeshRendererDesc  description;

    public:
        StaticMeshRenderer() = delete;
        StaticMeshRenderer(const ComponentID& selfId, GameObject* owner, const StaticMeshRendererDesc& desc) : 
            transform{nullptr},
            meshId{}, materialColor{0.0f, 0.0f, 0.0f, 1.0f},
            description{desc},
            Component{selfId, owner}
        {
        }
        ~StaticMeshRenderer() override;

        void Init() override;
        void Setup() override;
        void Update(float) override {};
        void Render(float, float) override;
        void Deinit() override;

        const StaticMeshID& MeshID() const noexcept { return meshId; }
        const DirectX::XMFLOAT4& MaterialColor() const noexcept { return materialColor; }

        void SetMeshID(const StaticMeshID& meshId) { this->meshId = meshId; }
        void ReloadMesh(const wchar_t* objFilePath);
        void SetMaterialColor(float red, float green, float blue, float alpha)
        {
            materialColor.x = red;
            materialColor.y = green;
            materialColor.z = blue;
            materialColor.w = alpha;
        }

    };

}

#endif // !INCLUDED_INC_STATIC_MESH_RENDERER_H