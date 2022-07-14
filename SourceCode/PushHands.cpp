//------< include >-----------------------------------------------------------------------
#include "PushHands.h"
#include "Config.h"
#include <algorithm>
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI
#include "RockScissorsPaper.h"
#include "DirectionBattle.h"

//========================================================================================
// 
//      PushHands
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void PushHands::Setup(GameMode* gameMode)
{
    namespace push = config::rule::push;

    periodShaking = 0.0f;
    periodNPCPush = 0.0f;

    switch (gameMode->LastResult())
    {
    case GameMode::RESULT::DRAW:
        pushRequire01 = push::BASE_PUSH_COUNT;
        pushRequire02 = push::BASE_PUSH_COUNT;
        break;

    case GameMode::RESULT::WIN_1P:
        pushRequire01 = push::BASE_PUSH_COUNT;
        pushRequire02 = push::BASE_PUSH_COUNT + push::PENALTY_PUSH_COUNT;
        break;

    case GameMode::RESULT::WIN_2P:
        pushRequire01 = push::BASE_PUSH_COUNT + push::PENALTY_PUSH_COUNT;
        pushRequire02 = push::BASE_PUSH_COUNT;
        break;

    default:
        _ASSERT_EXPR(false, L"resultの値が不適切");
        break;

    }

    gameMode->RezeroTimer();
    gameMode->NotyfyToGuide(OperateGuide::STATE::PH);
    gameMode->NotyfyToBackgrounds(GameMode::BG_NO::PH_RECEPTION);
}

void PushHands::Reception(GameMode* gameMode)
{
    namespace push = config::rule::push;
    constexpr float NEAR_ZERO = 4.5e-3f;

    const float timerSec = gameMode->TimerSec();
    if (pushRequire01 == 0 || pushRequire02 == 0 || push::END_RECEPTION_SEC < timerSec)
    {
        gameMode->RezeroTimer();
        phase = PHASE::JUDGE;
        return;
    }

    if (periodShaking + push::SHAKE_INTERVAL < timerSec)
    {
        PushMovement(gameMode->GetEntrant01Ref());
        PushMovement(gameMode->GetEntrant02Ref());
        periodShaking += push::SHAKE_INTERVAL;
    }

    CheckPush(gameMode->GetEntrant01Ref(), &pushRequire01, gameMode->TimerSec());
    CheckPush(gameMode->GetEntrant02Ref(), &pushRequire02, gameMode->TimerSec());
}
void PushHands::PushMovement(Entrant* entrant)
{
    namespace push = config::rule::push;

    DirectX::XMFLOAT3 position = entrant->FirstPosition();
    DirectX::XMFLOAT3 addPos = {
        push::SHAKE_VEC.x * static_cast<float>(std::rand() % 10) / 10,
        push::SHAKE_VEC.y * static_cast<float>(std::rand() % 10) / 10,
        push::SHAKE_VEC.z * static_cast<float>(std::rand() % 10) / 10,
    };
    addPos.x = (std::rand() % 1) ? addPos.x : -addPos.x;
    addPos.y = (std::rand() % 1) ? addPos.y : -addPos.y;
    addPos.z = (std::rand() % 1) ? addPos.z : -addPos.z;
    position = {
        position.x + addPos.x,
        position.y + addPos.y,
        position.z + addPos.z
    };
    entrant->SetPosition(position);
}
void PushHands::CheckPush(Entrant* entrant, int* require, float timerSec)
{
    namespace push = config::rule::push;

    if (entrant->IsNPC())
    {
        if (periodNPCPush + push::NPC_PUSH_INTERVAL < timerSec)
        {
            int pushNum = std::rand() % (push::NPC_MAX_PUSH_NUM + 1);
            *require = (std::max)(NULL, *require - pushNum);
            periodNPCPush += push::NPC_PUSH_INTERVAL;

        }
    }
    else
    {
        int trigger = entrant->OnlyPushedKey();
        if (trigger & (entrant->GetKeyBindRef()->left | entrant->GetKeyBindRef()->right))
        {
            *require = (std::max)(NULL, *require - 1);
        }
    }
}

void PushHands::Judge(GameMode* gameMode)
{
    /* 値を調整 */
    pushRequire01 = (std::max)(pushRequire01, 0);
    pushRequire02 = (std::max)(pushRequire02, 0);

    /* 勝敗を判定、送信 */
    gameMode->SetResult(JudgeResult());

    /* 次のフェーズへ移行 */
    gameMode->RezeroTimer();
    gameMode->NotyfyToGuide(OperateGuide::STATE::NONE);
    phase = PHASE::IDLE;
}
GameMode::RESULT PushHands::JudgeResult()
{
    GameMode::RESULT result = GameMode::RESULT::NONE;

    // 同じカウントで終了した場合 (or 同タイミングで押し切った場合)
    if (pushRequire01 == pushRequire02)
    {
        result = GameMode::RESULT::DRAW;
    }
    // 01が02よりも押していた場合 (or 先に01が押し切った場合)
    else if (pushRequire01 < pushRequire02)
    {
        result = GameMode::RESULT::WIN_1P;
    }
    // 02が01よりも押していた場合 (or 先に02が押し切った場合)
    else if (pushRequire02 < pushRequire01)
    {
        result = GameMode::RESULT::WIN_2P;
    }

    return result;
}

void PushHands::Idle(GameMode* gameMode)
{
    namespace push = config::rule::push;

    #if ACTIVE_TO_DIRECTION_BATTLE
    if (push::END_IDLE_SEC < gameMode->TimerSec())
    {
        gameMode->RezeroTimer();
        gameMode->GetEntrant01Ref()->ResetPosition();
        gameMode->GetEntrant02Ref()->ResetPosition();
        if (gameMode->LastResult() == GameMode::RESULT::DRAW)
            gameMode->SetNextRule<RockScissorsPaper>();
        else
            gameMode->SetNextRule<DirectionBattle>();
        return;
    }

    #endif // ACTIVE_TO_DIRECTION_BATTLE

    switch (gameMode->LastResult())
    {
    case GameMode::RESULT::DRAW:
        WinMovement(gameMode->GetEntrant01Ref(), gameMode->TimerSec(), false);
        WinMovement(gameMode->GetEntrant02Ref(), gameMode->TimerSec(), true);
        break;

    case GameMode::RESULT::WIN_1P:
        WinMovement(gameMode->GetEntrant01Ref(), gameMode->TimerSec(), true);
        LoseMovement(gameMode->GetEntrant02Ref(), gameMode->TimerSec(), true);
        break;

    case GameMode::RESULT::WIN_2P:
        LoseMovement(gameMode->GetEntrant01Ref(), gameMode->TimerSec(), false);
        WinMovement(gameMode->GetEntrant02Ref(), gameMode->TimerSec(), false);
        break;

    }

}
void PushHands::WinMovement(Entrant* entrant, float timerSec, bool toBack)
{
    namespace push = config::rule::push;

    TechSharkLib::Float3 position = entrant->FirstPosition();
    TechSharkLib::Float3 movement = push::WIN_VEC * timerSec;
    movement.x = toBack ? movement.x : -movement.x;
    movement.z = toBack ? movement.z : -movement.z;
    position += movement;
    entrant->SetPosition(position);
}
void PushHands::LoseMovement(Entrant* entrant, float timerSec, bool toBack)
{
    namespace push = config::rule::push;

    TechSharkLib::Float3 position = entrant->FirstPosition();
    TechSharkLib::Float3 movement = push::LOSE_VEC * timerSec;
    movement.x = toBack ? movement.x : -movement.x;
    movement.z = toBack ? movement.z : -movement.z;
    position += movement;
    entrant->SetPosition(position);
}

void PushHands::DrawDebugGUI()
{
    #if USE_IMGUI
    if (ImGui::CollapsingHeader(u8"押し合い", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text(u8"現在フェーズ : %d", static_cast<int>(phase));
        ImGui::InputInt("PushRequire01", &pushRequire01, 1, 100, ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
        ImGui::InputInt("PushRequire02", &pushRequire02, 1, 100, ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
    }

    #endif // USE_IMGUI
}