//------< include >-----------------------------------------------------------------------
#include "SceneSelect.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "SceneGameSingle.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI

//TODO:01 各シーンを作成
// ステージ選択、ゲーム(vsNPC)、リザルト(vsNPC)など、必要なシーンを作成する。
// ひとまずキーで遷移できるようにする。
// Title.h / Title.cpp およびTechSharkLib、ImGuiは編集しないこと。

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
//      SceneSelect
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void SceneSelect::Init()
{

}

void SceneSelect::Setup()
{
    Scene::Setup();
    TechSharkLib::SetAssignData(0, keyAssignList, {});
}

void SceneSelect::Update(float/*deltaTime*/)
{
    if (TechSharkLib::keyTrigger(0) & BIT_NO::BIT_00)
    {
        Scene::ChangeScene<SceneGameSingle>();
        return;
    }

    #if USE_IMGUI
    ImGui::Begin("Select");
    ImGui::End();

    #endif // USE_IMGUI

}

void SceneSelect::Render()
{

}

void SceneSelect::Deinit()
{

}