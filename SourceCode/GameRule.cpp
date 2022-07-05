//------< include >-----------------------------------------------------------------------
#include "GameRule.h"
#include "GameMode.h"
#include "Config.h"
#include "../TechSharkLib/Inc/KeyAssign.h"

//========================================================================================
// 
//      RockScissorsPaper
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void RockScissorsPaper::Run(GameMode* gameMode)
{
    using TechSharkLib::BIT_NO;

    switch (phase)
    {
    case PHASE::RECEPTION:
        PhaseReception(gameMode);
        break;
    case PHASE::SHOOT:
        PhaseShootHand(gameMode);
        break;
    case PHASE::IDLE:
        PhaseResult(gameMode);
        break;
    }

    if (entrant01Hand == ENTRANT_HAND::NONE)
        entrant01Hand = ShootHand(gameMode->GetEntrant01());
    if (entrant02Hand == ENTRANT_HAND::NONE)
        entrant02Hand = ShootHand(gameMode->GetEntrant01());

}

void RockScissorsPaper::PhaseReception(GameMode* gameMode)
{
    if (config::gamerule::rsp::IDLE_SEC < gameMode->TimerSec())
    {
        gameMode->ResetTimer();
        phase = PHASE::SHOOT;
        return;
    }
    if (entrant01Hand == ENTRANT_HAND::NONE)
        entrant01Hand = ShootHand(gameMode->GetEntrant01());
    if (entrant02Hand == ENTRANT_HAND::NONE)
        entrant02Hand = ShootHand(gameMode->GetEntrant01());
}

ENTRANT_HAND RockScissorsPaper::ShootHand(Entrant* entrant)
{
    int singleKey = entrant->KeyInputSingle();
    auto keyBind = entrant->GetKeyBind();
    if (singleKey == keyBind->keyUp)
        return ENTRANT_HAND::ROCK;
    if (singleKey == keyBind->keyRight)
        return ENTRANT_HAND::SCISSORS;
    if (singleKey == keyBind->keyLeft)
        return ENTRANT_HAND::PAPER;
    return ENTRANT_HAND::NONE;
}

int RockScissorsPaper::PhaseShootHand(GameMode* gameMode)
{
    // 手を出していないならランダムに決める
    ENTRANT_HAND hands[] = { ENTRANT_HAND::ROCK, ENTRANT_HAND::SCISSORS, ENTRANT_HAND::PAPER };
    if (entrant01Hand == ENTRANT_HAND::NONE)
        entrant01Hand = hands[std::rand() % static_cast<int>(ENTRANT_HAND::VALUE)];
    if (entrant02Hand == ENTRANT_HAND::NONE)
        entrant02Hand = hands[std::rand() % static_cast<int>(ENTRANT_HAND::VALUE)];

    // 手をセット
    gameMode->GetEntrant01()->SetMeshNo(entrant01Hand);
    gameMode->GetEntrant02()->SetMeshNo(entrant02Hand);

    // 勝敗を決める
    int result = 0;
    if (entrant01Hand == entrant02Hand)
        result = GameMode::RESULT::DRAW;
    else if (
        (static_cast<int>(entrant01Hand) + 1) % static_cast<int>(ENTRANT_HAND::VALUE)
        <= static_cast<int>(entrant02Hand)
    )
        result = GameMode::RESULT::WIN_0;
    else
        result = GameMode::RESULT::WIN_1;

    // 次のフェーズへ
    gameMode->ResetTimer();
    phase = PHASE::IDLE;

    // 結果をリターン
    return result;
}
