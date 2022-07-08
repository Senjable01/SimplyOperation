//------< include >-----------------------------------------------------------------------
#include "SceneResultSingle.h"
#include "SceneGameSingle.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "SceneSelect.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI
#include "GameMode.h"

//------< pragma >------------------------------------------------------------------------
#pragma warning ( disable : 26812 )

//------< using >-------------------------------------------------------------------------
using TechSharkLib::BIT_NO;

//------< namespace >---------------------------------------------------------------------
namespace
{
    TechSharkLib::KeyAssignList keyAssignList = {
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Home}
    };

    #if USE_IMGUI
    std::map<int, std::string> debugResult = {
        { GameMode::RESULT::DRAW, "Draw" },
        { GameMode::RESULT::WIN_1, "Win 01" },
        { GameMode::RESULT::WIN_2, "Win 02" }
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
    std::string str = "Result : " + debugResult.at(result);
    ImGui::Text(str.c_str());
    ImGui::End();

    #endif // USE_IMGUI

}

void SceneResultSingle::Render()
{

}

void SceneResultSingle::Deinit()
{

}