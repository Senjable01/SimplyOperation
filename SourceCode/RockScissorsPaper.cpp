//------< include >-----------------------------------------------------------------------
#include "RockScissorsPaper.h"
#include "Config.h"
#include "PushHands.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"
#include <map>
#include <string>

#endif // USE_IMGUI

#if USE_IMGUI
//------< namespace >---------------------------------------------------------------------
namespace
{
    std::map<Entrant::STATE, std::string> stateNameMap = {
        {Entrant::STATE::ROCK,      "Rock"},
        {Entrant::STATE::SCISSORS,  "Scissors"},
        {Entrant::STATE::PAPER,     "Paper"},
        {Entrant::STATE::NONE,      "None"},
    };
}

#endif // USE_IMGUI

//========================================================================================
// 
//      RockScissorsPaper
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void RockScissorsPaper::Setup(GameMode* gameMode)
{
    entrant01Hand = Entrant::STATE::NONE;
    entrant02Hand = Entrant::STATE::NONE;
    gameMode->GetEntrant01Ref()->SetMesh(Entrant::STATE::NONE);
    gameMode->GetEntrant02Ref()->SetMesh(Entrant::STATE::NONE);
    gameMode->NotyfyToObserver(OperateGuide::STATE::NONE);
}

void RockScissorsPaper::Reception(GameMode* gameMode)
{
    namespace rsp = config::rule::rsp;

    if (rsp::END_RECEPTION_SEC < gameMode->TimerSec())
    {
        gameMode->RezeroTimer();
        phase = PHASE::JUDGE;
        return;
    }

    if (rsp::BEGIN_RECEPTION_SEC < gameMode->TimerSec())
    {
        // 時間内なら手は変更可能
        ShootHandByInput(gameMode->GetEntrant01Ref(), &entrant01Hand);
        ShootHandByInput(gameMode->GetEntrant02Ref(), &entrant02Hand);
        gameMode->NotyfyToObserver(OperateGuide::STATE::RSP);
    }

}
void RockScissorsPaper::ShootHandByInput(Entrant* entrant, Entrant::STATE* hand)
{
    if (entrant->IsNPC())
    {
        return;
    }

    const int onlyPushedKey = entrant->OnlyPushedKey();
    const auto& keyBind = *(entrant->GetKeyBindRef());
    if (onlyPushedKey == NULL)
    {
        return;
    }
    else if (onlyPushedKey == keyBind.left)
    {
        *hand = Entrant::STATE::ROCK;
    }
    else if (onlyPushedKey == keyBind.up)
    {
        *hand = Entrant::STATE::SCISSORS;
    }
    else if (onlyPushedKey == keyBind.right)
    {
        *hand = Entrant::STATE::PAPER;
    }
}

void RockScissorsPaper::Judge(GameMode* gameMode)
{
    // 手が決まっていなければ勝手に決定
    if (entrant01Hand == Entrant::STATE::NONE)
    {
        ShootHandByRandom(&entrant01Hand);
    }
    if (entrant02Hand == Entrant::STATE::NONE)
    {
        #if DEBUG_MODE
        entrant02Hand = Entrant::STATE::ROCK;
        #else
        ShootHandByRandom(&entrant02Hand);
        #endif // DEBUG_MODE

    }

    // アサーションチェック
    _ASSERT_EXPR(
        static_cast<int>(Entrant::STATE::ROCK) <= static_cast<int>(entrant01Hand) &&
        static_cast<int>(entrant01Hand) <= static_cast<int>(Entrant::STATE::PAPER),
        L"Entrant01が決定した手が不適切"
    );
    _ASSERT_EXPR(
        static_cast<int>(Entrant::STATE::ROCK) <= static_cast<int>(entrant02Hand) &&
        static_cast<int>(entrant02Hand) <= static_cast<int>(Entrant::STATE::PAPER),
        L"Entrant01が決定した手が不適切"
    );

    // 勝敗を判定、送信
    gameMode->SetResult(JudgeResult());

    // メッシュを通知
    gameMode->GetEntrant01Ref()->SetMesh(entrant01Hand);
    gameMode->GetEntrant02Ref()->SetMesh(entrant02Hand);

    // 次のフェーズへ移行
    gameMode->RezeroTimer();
    gameMode->NotyfyToObserver(OperateGuide::STATE::NONE);
    phase = PHASE::IDLE;

}
void RockScissorsPaper::ShootHandByRandom(Entrant::STATE* hand)
{
    Entrant::STATE hands[] = { Entrant::STATE::ROCK, Entrant::STATE::SCISSORS, Entrant::STATE::PAPER };
    const int size = sizeof(hands) / sizeof(hands[0]);
    *hand = hands[std::rand() % size];
}
GameMode::RESULT RockScissorsPaper::JudgeResult()
{
    const int hand01 = static_cast<int>(entrant01Hand);
    const int hand02 = static_cast<int>(entrant02Hand);

    if (hand01 == hand02)
    {
        return GameMode::RESULT::DRAW;
    }
    else if ((hand01 + 1) % static_cast<int>(Entrant::STATE::HAND_NUM) == hand02)
    {
        return GameMode::RESULT::WIN_1P;
    }
    else
    {
        return GameMode::RESULT::WIN_2P;
    }
}

void RockScissorsPaper::Idle(GameMode* gameMode)
{
    namespace rsp = config::rule::rsp;

    #if ACTIVE_TO_PUSH_HAND
    if (rsp::END_IDLE_SEC < gameMode->TimerSec())
    {
        gameMode->RezeroTimer();
        gameMode->SetNextRule<PushHands>();
        return;
    }

    #endif // ACTIVE_TO_PUSH_HAND

}

void RockScissorsPaper::DrawDebugGUI()
{
    #if USE_IMGUI
    if (ImGui::CollapsingHeader(u8"じゃんけん", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
    {
        std::string hand01 = "Entrant01 : " + stateNameMap.at(entrant01Hand);
        std::string hand02 = "Entrant02 : " + stateNameMap.at(entrant02Hand);
        ImGui::Text(u8"現在フェーズ : %d", static_cast<int>(phase));
        ImGui::Text(hand01.c_str());
        ImGui::Text(hand02.c_str());
    }

    #endif // USE_IMGUI
}