//------< include >-----------------------------------------------------------------------
#include "SceneResultSingle.h"
#include "SceneGameSingle.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "SceneSelect.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"
#include <string>

#endif // USE_IMGUI

//------< using >-------------------------------------------------------------------------
using TechSharkLib::BIT_NO;

//------< namespace >---------------------------------------------------------------------
namespace
{
    TechSharkLib::KeyAssignList keyAssignList = {
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Home}
    };
    #if USE_IMGUI
    std::map<config::rule::RESULT, std::string> resultNameMap = {
        {config::rule::RESULT::DRAW,    "DRAW"},
        {config::rule::RESULT::WIN_1P,  "Win Entrant01"},
        {config::rule::RESULT::WIN_2P,  "Win Entrant02"},
        {config::rule::RESULT::NONE,    "None"}
    };

    #endif // USE_IMGUI

}

//========================================================================================
// 
//      SceneResultSingle
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void SceneResultSingle::Init()
{

}

void SceneResultSingle::Setup()
{
    Scene::Setup();
    TechSharkLib::SetAssignData(0, keyAssignList, {});
}

void SceneResultSingle::Update(float/*deltaTime*/)
{
    if (TechSharkLib::keyTrigger(0) & BIT_NO::BIT_00)
    {
        Scene::ChangeScene<SceneSelect>();
        return;
    }

    #if USE_IMGUI
    ImGui::Begin("ResultSingle");
    ImGui::Text(resultNameMap.at(result).c_str());
    ImGui::End();

    #endif // USE_IMGUI

}

void SceneResultSingle::Render()
{

}

void SceneResultSingle::Deinit()
{

}