//------< include >-----------------------------------------------------------------------
#include "Obj3DDebugger.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI

//========================================================================================
// 
//      Obj3DDebbger
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void Obj3DDebugger::Init()
{
    using TechSharkLib::Transform3D;
    using TechSharkLib::StaticMeshRenderer;

    transform = GetOwnerRef()->SearchComponent<Transform3D>();
    _ASSERT_EXPR(transform != nullptr, L"Transform3D�R���|�[�l���g�̌����Ɏ��s");
    renderer = GetOwnerRef()->SearchComponent<StaticMeshRenderer>();
    _ASSERT_EXPR(renderer != nullptr, L"StaticMeshRenderer�R���|�[�l���g�̌����Ɏ��s");
}

void Obj3DDebugger::Setup()
{
    name = description.name;
}

void Obj3DDebugger::Update(float /*deltaTime*/)
{
    #if USE_IMGUI
    ImGui::Begin(name.c_str());
    transform->DrawDebugGUI();
    renderer->DrawDebugGUI();
    ImGui::End();

    #endif // USE_IMGUI

}

//----------------------------------------------------------------------------------------
// instance
//----------------------------------------------------------------------------------------

TSL_IMPLEMENT_COMPONENT(Obj3DDebugger, "Obj3DDebugger");