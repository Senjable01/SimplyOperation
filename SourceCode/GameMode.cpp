//------< include >-----------------------------------------------------------------------
#include "GameMode.h"
#include <utility>
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI

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
    ImGui::Begin("GameMode");
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