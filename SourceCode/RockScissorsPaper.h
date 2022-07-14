#ifndef INCLUDED_ROCK_SCISSORS_PAPER_H
#define INCLUDED_ROCK_SCISSORS_PAPER_H

//------< include >-----------------------------------------------------------------------
#include "GameMode.h"

//========================================================================================
// 
//      RockScissorsPaper
// 
//========================================================================================
class RockScissorsPaper final : public GameRule
{
private:
    Entrant::STATE entrant01Hand;
    Entrant::STATE entrant02Hand;

    void Setup(GameMode* gameMode) override;
    void Reception(GameMode* gameMode) override;
    void Judge(GameMode* gameMode) override;
    void Idle(GameMode* gameMode) override;

    void ShootHandByInput(Entrant* entrant, Entrant::STATE* hand);
    void ShootHandByRandom(Entrant::STATE* hand);
    GameMode::RESULT JudgeResult();

public:
    explicit RockScissorsPaper() : 
        entrant01Hand{Entrant::STATE::NONE}, entrant02Hand{Entrant::STATE::NONE},
        GameRule{}
    {
    }

    void DrawDebugGUI() override;

};

#endif // !INCLUDED_ROCK_SCISSORS_PAPER_H