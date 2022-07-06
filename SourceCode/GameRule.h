#pragma once

//------< include >-----------------------------------------------------------------------
#include "Strategy.h"
#include "Entrant.h"

//------< class >-------------------------------------------------------------------------

class GameMode;

//========================================================================================
// 
//      RockScissorsPaper
// 
//========================================================================================
class RockScissorsPaper : public Behavior<GameMode>
{
private:
    enum HAND { ROCK = 0, SCISSORS, PAPER, NUM, NONE = 0 };
    ENTRANT_HAND entrant01Hand;
    ENTRANT_HAND entrant02Hand;
    enum class PHASE { RECEPTION = 0, SHOOT, IDLE };
    PHASE phase;

    void PhaseReception(GameMode* gameMode);
    ENTRANT_HAND ShootHand(Entrant*);
    void PhaseShootHand(GameMode* gameMode);
    void PhaseIdle(GameMode* gameMode);

    void Run(GameMode*) override;

public:
    RockScissorsPaper() : 
        entrant01Hand{ENTRANT_HAND::NONE}, entrant02Hand{ENTRANT_HAND::NONE},
        phase{PHASE::RECEPTION}
    {
    }

};

//========================================================================================
// 
//      PushHands
// 
//========================================================================================
class PushHands : public Behavior<GameMode>
{
// 左右キー(スティックの傾き)で判定
private:
    int pushRequire01;
    int pushRequire02;

    enum class PHASE {
        RECEPTION = 0,
        JUDGE,
        IDLE
    } phase;
    void PhaseReception(GameMode* gameMode);
    void PhaseJudge(GameMode* gameMode);
    void PhaseIdle(GameMode* gameMode);

    void CheckPush(Entrant* entrant, int* counter);
    int JudgeResult(GameMode* gameMode);

    void Run(GameMode*) override;

public:
    PushHands() : 
        pushRequire01{0}, pushRequire02{0},
        phase{PHASE::RECEPTION}
    {
    }

    void Setup(GameMode* gameMode);

};