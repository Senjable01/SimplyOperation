//------< include >-----------------------------------------------------------------------
#include "GameMode.h"
#include "Config.h"
#include <crtdbg.h>

void GameMode::Run(float deltaTime)
{
    GameRule* nextGameRule = gameRule->Run(deltaTime);
    if (nextGameRule)
    {
        gameRule->End();
        gameRule = nextGameRule;
        gameRule->Start();
    }
}

//========================================================================================
// 
//      RockScissorsPaper
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void RockScissorsPaper::Start()
{
}
GameRule* RockScissorsPaper::Run(float deltaTime)
{
    switch (state)
    {
    case PHASE::RECEPTION:
        /* じゃんけん受付 */
        for (int i = 0; i < static_cast<int>(ENTRANT_ID::NUM); i++)
        {
            if (entrantHands[i] == HAND::NUM)
            {
                entrantHands[i] = Reception(entrants[i]);
            }
        }
        receptionTimer += deltaTime;
        if (config::gamerule::rsp::RECEPTION_SEC < receptionTimer)
        {
            receptionTimer = 0.0f;
            state = PHASE::JUDGE;
        }
        break;

    case PHASE::JUDGE:
        /* じゃんけん結果 */
        for (int i = 0; i < static_cast<int>(ENTRANT_ID::NUM); i++)
        {
            // 手を出していないなら勝手に決定
            if (entrantHands[i] == HAND::NUM)
            {
                entrantHands[i] = (std::rand() % HAND::NUM);
            }
            entrants[i]->SetMesh(entrantHands[i]);
        }
        GAME_RESULT result = JudgeResult();

        state = PHASE::IDLE;
        break;

    case PHASE::IDLE:
        receptionTimer += deltaTime;
        if (config::gamerule::rsp::IDLE_SEC < receptionTimer)
        {
            receptionTimer = 0.0f;
            // return
        }
        break;

    }

    return nullptr;
}
void RockScissorsPaper::End()
{
    for (auto& entrant : entrants)
    {
        entrant->SetMesh(Entrant::DIRECTION_NONE);
    }
    for (auto& hand : entrantHands)
    {
        hand = HAND::NUM;
    }

}

int RockScissorsPaper::Reception(Entrant* entrant)
{
    int direction = entrant->Direction();
    if (direction == Entrant::DIRECTION_DOWN || Entrant::DIRECTION_NONE)
    {
        return Entrant::DIRECTION_NONE;
    }
    
    return direction;
}

GAME_RESULT RockScissorsPaper::JudgeResult()
{
    int entrant0Hand = entrantHands[static_cast<size_t>(ENTRANT_ID::NO_0)];
    int entrant1Hand = entrantHands[static_cast<size_t>(ENTRANT_ID::NO_1)];

    if (entrant0Hand == entrant1Hand)
    {
        return GAME_RESULT::DRAW;
    }
    else if ((entrant0Hand + 1) % HAND::NUM == entrant1Hand)
    {
        return GAME_RESULT::NO_0_WIN;
    }
    else
    {
        return GAME_RESULT::NO_1_WIN;
    }
}

void RockScissorsPaper::SetEntraint(ENTRANT_ID no, Entrant* entraint)
{
    _ASSERT_EXPR(no != ENTRANT_ID::NUM, L"noが不適切");
    entrants[static_cast<size_t>(no)] = entraint;
}