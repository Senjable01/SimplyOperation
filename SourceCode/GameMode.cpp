//------< include >-----------------------------------------------------------------------
#include "GameMode.h"
#include <utility>

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
        gameRule = std::move(nextRule);
        nextRule = nullptr;
    }

    (*gameRule)(this);

    timerSec += deltaTime;
}

void GameMode::Clear()
{
    entrant01 = nullptr;
    entrant02 = nullptr;
    gameRule.reset(nullptr);
    nextRule.reset(nullptr);
}