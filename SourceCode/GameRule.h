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

    void Run(GameMode*) override;
    void PhaseReception(GameMode* gameMode);
    ENTRANT_HAND ShootHand(Entrant*);
    void PhaseShootHand(GameMode* gameMode);
    void PhaseResult(GameMode* gameMode);

public:
    RockScissorsPaper() : 
        entrant01Hand{ENTRANT_HAND::NONE}, entrant02Hand{ENTRANT_HAND::NONE},
        phase{PHASE::RECEPTION}
    {
    }

};