#ifndef INCLUDED_PUSH_HANDS_H
#define INCLUDED_PUSH_HANDS_H

//------< include >-----------------------------------------------------------------------
#include "GameMode.h"

//========================================================================================
// 
//      PushHands
// 
//========================================================================================
class PushHands final : public GameRule
{
private:
    int pushRequire01;
    int pushRequire02;

    float periodShaking;
    float periodNPCPush; // NPC‚ª‰Ÿ‚·ŽüŠú‚Å‚ ‚é‚©

    void Setup(GameMode* gameMode) override;
    void Reception(GameMode* gameMode) override;
    void Judge(GameMode* gameMode) override;
    void Idle(GameMode* gameMode) override;

    void PushMovement(Entrant* entrant);
    void CheckPush(Entrant* entrant, int* require, float timerSec);
    GameMode::RESULT JudgeResult();
    void WinMovement(Entrant* entrant, float timerSec, bool toBack);
    void LoseMovement(Entrant* entrant, float timerSec, bool toBack);

public:
    PushHands() : 
        pushRequire01{INT_MAX}, pushRequire02{INT_MAX},
        periodShaking{0.0f}, periodNPCPush{ 0.0f },
        GameRule{}
    {
    }

    void DrawDebugGUI() override;

};

#endif // !INCLUDED_PUSH_HANDS_H