//------< include >-----------------------------------------------------------------------
#include "GameMode.h"
#include <utility>
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI

//------< pragma >------------------------------------------------------------------------
#pragma warning (disable : 26812)

//------< namespace >---------------------------------------------------------------------
namespace
{
    #if USE_IMGUI
    std::map<int, std::string> debugResult = {
        {GameMode::RESULT::DRAW,    "Draw"},
        {GameMode::RESULT::WIN_1,   "Win01"},
        {GameMode::RESULT::WIN_2,   "Win02"},
        {GameMode::RESULT::NONE,    "None"},
    };

    #endif // USE_IMGUI

}

//========================================================================================
// 
//      GameMode
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void GameMode::Update(float deltaTime)
{
    if (nextRule != nullptr)
    {
        gameRule    = std::move(nextRule);
        nextRule    = nullptr;
    }

    #if USE_IMGUI
    ImGui::SetNextWindowPos(ImVec2(200, 100), ImGuiCond_::ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_::ImGuiCond_Once);
    ImGui::Begin("GameMode");
    if (ImGui::CollapsingHeader("Status", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Timer(In Sec) : %f", timerSec);
        std::string debugLastResult = "LastResult : " + debugResult.at(lastResult);
        ImGui::Text(debugLastResult.c_str());
    }
    (*gameRule)(this);
    ImGui::End();

    #else
    (*gameRule)(this);

    #endif // USE_IMGUI

    timerSec += deltaTime;
}

void GameMode::Clear()
{
    entrant01 = nullptr;
    entrant02 = nullptr;
    gameRule.reset(nullptr);
    nextRule.reset(nullptr);
}