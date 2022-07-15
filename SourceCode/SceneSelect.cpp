//------< include >-----------------------------------------------------------------------
#include "SceneSelect.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "SceneGameSingle.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI
#include "Audio.h"

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
    TechSharkLib::Play(music::TITLE_MUSIC, true);
}

void SceneSelect::Update(float/*deltaTime*/)
{
    if (TechSharkLib::keyTrigger(0) & BIT_NO::BIT_00)
    {
        Scene::ChangeScene<SceneGameSingle>();
        TechSharkLib::Play(sound::XWB_SOUND, sound::DECISION);
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
    TechSharkLib::Stop(music::TITLE_MUSIC);
}