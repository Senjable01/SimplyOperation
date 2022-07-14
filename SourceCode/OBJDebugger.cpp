//------< include >-----------------------------------------------------------------------
#include "OBJDebugger.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI

//========================================================================================
// 
//      OBJDebugger
// 
//========================================================================================

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void OBJDebugger::Init()
{
    transform = GetOwnerRef()->SearchComponent<TechSharkLib::Transform3D>();
    _ASSERT_EXPR(transform != nullptr, L"Transform3D�R���|�[�l���g�̌����Ɏ��s");
    renderer = GetOwnerRef()->SearchComponent<TechSharkLib::StaticMeshRenderer>();
    _ASSERT_EXPR(renderer != nullptr, L"StaticMeshRenderer�R���|�[�l���g�̌����Ɏ��s");
}
void OBJDebugger::Setup()
{
    debugName = description.debugName;
}
void OBJDebugger::Update(float /*deltaTime*/)
{
    DrawDebugGUI();
}

void OBJDebugger::DrawDebugGUI()
{
    #if USE_IMGUI
    ImGui::Begin(debugName.c_str());
    transform->DrawDebugGUI();
    renderer->DrawDebugGUI();
    ImGui::End();

    #endif // USE_IMGUI
}

//------------------------------------------------------------------------------
// instance
//------------------------------------------------------------------------------

TSL_IMPLEMENT_COMPONENT(OBJDebugger, "OBJDebugger");