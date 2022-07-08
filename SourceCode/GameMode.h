#pragma once

//------< include >-----------------------------------------------------------------------
#include "Entrant.h"
#include "GameRule.h"
#include <memory>

//========================================================================================
// 
//      GameMode
// 
//========================================================================================
class GameMode
{
public:
    enum RESULT { DRAW = 0, WIN_1, WIN_2, NONE = -1 };
    struct Result
    {
        int result = RESULT::NONE;
        explicit operator bool() { return result != RESULT::NONE; }
    };

private:
    Entrant* entrant01;
    Entrant* entrant02;

    Strategy<GameMode> gameRule;
    Strategy<GameMode> nextRule;

    float timerSec;

    int lastResult;
    bool isFinished;

public:
    GameMode() : 
        entrant01{nullptr}, entrant02{nullptr},
        gameRule{nullptr}, nextRule{nullptr},
        timerSec{0.0f},
        lastResult{RESULT::NONE}, isFinished{false}
    {
    }

    void Update(float deltaTime);
    void Clear();

    Entrant* GetEntrant01() const { return entrant01; }
    Entrant* GetEntrant02() const { return entrant02; }
    float TimerSec() const noexcept { return timerSec; }
    int LastResult() const noexcept { return lastResult; }
    bool IsFinished() const noexcept { return isFinished; }

    void SetEntrant01(Entrant* entrant01) { this->entrant01 = entrant01; }
    void SetEntrant02(Entrant* entrant02) { this->entrant02 = entrant02; }
    void ResetTimer() { timerSec = 0.0f; }
    void SetResult(int result) { this->lastResult = result; }
    template<typename Rule>
    void SetNextRule() { nextRule = std::make_unique<Rule>(); }
    void Finish() { isFinished = true; }
};