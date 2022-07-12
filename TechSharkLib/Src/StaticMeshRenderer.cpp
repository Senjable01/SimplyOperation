//------< include >-----------------------------------------------------------------------
#include "../Inc/StaticMeshRenderer.h"
#include "../Inc/GameObject.h"
#include "../Inc/Transform3D.h"
#include "../Inc/TechSharkLib.h"
#include "../Inc/Configulation.h"
#if USE_IMGUI
#include "../Inc/ImGuiCtrl.h"

#endif // USE_IMGUI

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
    //      StaticMeshRenderer
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // destructor
    //------------------------------------------------------------------------------

    StaticMeshRenderer::~StaticMeshRenderer()
    {
        TechSharkLib::Release(meshId);
    }

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void StaticMeshRenderer::Init()
    {
        transform = GetOwnerRef()->SearchComponent<Transform3D>();
        _ASSERT_EXPR(transform != nullptr, L"Transform3Dコンポーネントの検索に失敗");
    }
    void StaticMeshRenderer::Setup()
    {
        meshId = TechSharkLib::LoadStaticMesh(description.objFilePath.c_str(), description.flipVCoord);
        materialColor = description.materialColor;
    }
    void StaticMeshRenderer::Render(float, float)
    {
        if (transform == nullptr) return;

        const DirectX::XMFLOAT4X4 local = transform->Transform();
        TechSharkLib::Render(meshId, local, materialColor);
    }
    void StaticMeshRenderer::Deinit()
    {
        transform       = nullptr;
        TechSharkLib::Release(meshId);
        materialColor   = {0.0f, 0.0f, 0.0f, 1.0f};
        description     = {};
    }

    void StaticMeshRenderer::DrawDebugGUI()
    {
        if (ImGui::CollapsingHeader("StaticMeshRenderer"))
        {
            ImGui::ColorEdit4("materialColor", &materialColor.x);
        }
    }

    //------------------------------------------------------------------------------
    // instance
    //------------------------------------------------------------------------------

    TSL_IMPLEMENT_COMPONENT(StaticMeshRenderer, "StaticMeshRenderer");

}