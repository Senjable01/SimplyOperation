//------< include >-----------------------------------------------------------------------
#include "SceneTitle.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "SceneSelect.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI
#include "../TechSharkLib/Inc/Transform3D.h"

//------< using >-------------------------------------------------------------------------
using TechSharkLib::BIT_NO;

//------< namespace >---------------------------------------------------------------------
namespace
{
    TechSharkLib::KeyAssignList keyAssignList = {
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Home}
    };
}

//========================================================================================
// 
//      SceneTitle
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void SceneTitle::Init()
{
}

void SceneTitle::Setup()
{
    Scene::Setup();
    TechSharkLib::SetAssignData(0, keyAssignList, {});

    TechSharkLib::GameObject* obj = nullptr;
    objManager.CreateObject(&obj);
    TechSharkLib::Transform3D* transform = nullptr;
    obj->AddComponent<TechSharkLib::Transform3D>(&transform, TechSharkLib::Transform3DDesc{});
}

void SceneTitle::Update(float)
{
    if (TechSharkLib::keyTrigger(0) & BIT_NO::BIT_00)
    {
        Scene::ChangeScene<SceneSelect>();
        return;
    }

    #if USE_IMGUI
    ImGui::Begin("Title");
    ImGui::Text("Home : SceneSelect");
    ImGui::End();

    #endif // USE_IMGUI

}

void SceneTitle::Render()
{

}

void SceneTitle::Deinit()
{

}