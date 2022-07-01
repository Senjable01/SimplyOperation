#pragma once

//------< include >-----------------------------------------------------------------------
#include "Entrant.h"

//------< using >-------------------------------------------------------------------------

namespace TechSharkLib
{
    class ComponentManager;
}

//========================================================================================
// 
//      GameRule
// 
//========================================================================================
class GameRule
{
public:
    virtual void Start() = 0;
    virtual GameRule* Run(float /*deltaTime*/) = 0;
    virtual void End() = 0;
};

//========================================================================================
// 
//      GameMode
// 
//========================================================================================
class GameMode
{
private:
    GameRule* gameRule;

public:
    GameMode(GameRule* gameRule) : gameRule{ gameRule } { this->gameRule->Start(); }
    ~GameMode() { gameRule->End(); }

    void Run(float deltaTime);

};

//========================================================================================
// 
//      ENTRANT_ID
// 
//========================================================================================
enum class ENTRANT_ID {
    NO_0, NO_1,
    NUM
};

//========================================================================================
// 
//      GAME_RESULT
// 
//========================================================================================
enum class GAME_RESULT : int {
    NO_0_WIN,
    NO_1_WIN,
    DRAW
};

//========================================================================================
// 
//      RockScissorsPaper
// 
//========================================================================================
class RockScissorsPaper : public GameRule
{
private:
    Entrant* entrants[static_cast<size_t>(ENTRANT_ID::NUM)];
    enum HAND : int {
        ROCK = 0, SCISSORS, PAPER, NUM
    };
    int entrantHands[static_cast<size_t>(ENTRANT_ID::NUM)];
    enum PHASE : int {RECEPTION = 0, JUDGE, IDLE};
    int state;
    float receptionTimer;

    void Start() override;
    GameRule* Run(float /*deltaTime*/) override;
    void End() override;

    int Reception(Entrant* entrant);
    GAME_RESULT JudgeResult();

public:
    RockScissorsPaper() = delete;
    RockScissorsPaper() :
        entrants{nullptr}, entrantHands{HAND::NUM},
        state{PHASE::RECEPTION}, receptionTimer{0.0f}
    {
    }

    void SetEntraint(ENTRANT_ID no, Entrant* entraint);
};

//------< variable >---------------------------------------------------------------------

namespace rule
{

}