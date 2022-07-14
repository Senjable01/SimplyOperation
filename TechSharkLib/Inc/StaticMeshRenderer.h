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
        StaticMeshID        staticMeshId;
        DirectX::XMFLOAT4   materialColor;

        StaticMeshRendererDesc() : staticMeshId{}, materialColor{0.0f, 0.0f, 0.0f, 1.0f} {}
        StaticMeshRendererDesc(const StaticMeshID& staticMeshId, const DirectX::XMFLOAT4& materialColor) :
            staticMeshId{staticMeshId}, materialColor{materialColor}
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
        bool                    isRenderable;

        StaticMeshRendererDesc  description;

    public:
        StaticMeshRenderer() = delete;
        StaticMeshRenderer(const ComponentID& selfId, GameObject* owner, const StaticMeshRendererDesc& desc) : 
            transform{nullptr},
            meshId{}, materialColor{0.0f, 0.0f, 0.0f, 1.0f}, isRenderable{true},
            description{desc},
            Component{selfId, owner}
        {
        }
        ~StaticMeshRenderer() override {}

        void Init() override;
        void Setup() override;
        void Update(float) override {};
        void Render(float, float) override;
        void Deinit() override;

        void DrawDebugGUI() override;

        const StaticMeshID& MeshID() const noexcept { return meshId; }
        const DirectX::XMFLOAT4& MaterialColor() const noexcept { return materialColor; }
        bool IsRenderable() const noexcept { return isRenderable; }

        void SetMeshID(const StaticMeshID& meshId) { this->meshId = meshId; }
        void SetMaterialColor(float red, float green, float blue, float alpha)
        {
            materialColor.x = red;
            materialColor.y = green;
            materialColor.z = blue;
            materialColor.w = alpha;
        }
        void SetRenderablity(bool isAvailable) { this->isRenderable = isAvailable; }

    };

}

#endif // !INCLUDED_INC_STATIC_MESH_RENDERER_H