#pragma once

//------< include >-----------------------------------------------------------------------
#include "Entrant.h"
#include "GameRule.h"

//========================================================================================
// 
//      GameMode
// 
//========================================================================================
class GameMode
{
public:
    enum RESULT { DRAW = 0, WIN_0, WIN_1 };

private:
    Entrant* entrant01;
    Entrant* entrant02;

    Strategy<GameMode> gameRule;
    Strategy<GameMode> nextRule;

    float timerSec;

public:
    GameMode() : 
        entrant01{nullptr}, entrant02{nullptr},
        gameRule{nullptr}, nextRule{nullptr},
        timerSec{0.0f}
    {
    }

    void Update(float deltaTime);
    void Clear();

    Entrant* GetEntrant01() const { return entrant01; }
    Entrant* GetEntrant02() const { return entrant02; }
    float TimerSec() const noexcept { return timerSec; }

    void SetEntrant01(Entrant* entrant01) { this->entrant01 = entrant01; }
    void SetEntrant02(Entrant* entrant02) { this->entrant02 = entrant02; }
    void ResetTimer() { timerSec = 0.0f; }
    void SetResult(int result)
    {
        //UNDONE: ƒŠƒUƒ‹ƒg‚ðŽó‚¯Žæ‚é
    }
    template<typename Rule>
    void SetGameRule() { nextRule = std::make_unique<Rule>(); }

};