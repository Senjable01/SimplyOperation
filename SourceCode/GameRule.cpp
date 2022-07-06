//------< include >-----------------------------------------------------------------------
#include "GameRule.h"
#include "GameMode.h"
#include "Config.h"
#include "../TechSharkLib/Inc/KeyAssign.h"
#include <algorithm>
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI

//------< namespace >---------------------------------------------------------------------
namespace
{
    #if USE_IMGUI
    std::map<ENTRANT_HAND, std::string> debugHandName = {
        {ENTRANT_HAND::ROCK,        "Rock"},
        {ENTRANT_HAND::SCISSORS,    "Scissors"},
        {ENTRANT_HAND::PAPER,       "Paper"},
        {ENTRANT_HAND::VALUE,       "VALUE"},
        {ENTRANT_HAND::NONE,        "None"},
    };
    #endif // USE_IMGUI

}

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
        PhaseIdle(gameMode);
        break;
    }

    #if USE_IMGUI
    DrawDebugGUI(gameMode);

    #endif // USE_IMGUI

}

void RockScissorsPaper::PhaseReception(GameMode* gameMode)
{
    if (config::gamerule::rsp::RECEPTION_SEC < gameMode->TimerSec())
    {
        gameMode->ResetTimer();
        phase = PHASE::SHOOT;
        return;
    }
    if (entrant01Hand == ENTRANT_HAND::NONE)
        entrant01Hand = ShootHand(gameMode->GetEntrant01());
    if (entrant02Hand == ENTRANT_HAND::NONE)
        entrant02Hand = ShootHand(gameMode->GetEntrant02());
}

ENTRANT_HAND RockScissorsPaper::ShootHand(Entrant* entrant)
{
    int singleKey = entrant->KeyInputSingle();
    auto keyBind = entrant->GetKeyBind();
    if (singleKey == NULL)
        return ENTRANT_HAND::NONE;
    if (singleKey == keyBind->keyUp)
        return ENTRANT_HAND::SCISSORS;
    if (singleKey == keyBind->keyRight)
        return ENTRANT_HAND::PAPER;
    if (singleKey == keyBind->keyLeft)
        return ENTRANT_HAND::ROCK;
    return ENTRANT_HAND::NONE;
}

void RockScissorsPaper::PhaseShootHand(GameMode* gameMode)
{
    // ����o���Ă��Ȃ��Ȃ烉���_���Ɍ��߂�
    ENTRANT_HAND hands[] = { ENTRANT_HAND::ROCK, ENTRANT_HAND::SCISSORS, ENTRANT_HAND::PAPER };
    if (entrant01Hand == ENTRANT_HAND::NONE)
        entrant01Hand = hands[std::rand() % static_cast<int>(ENTRANT_HAND::VALUE)];
    if (entrant02Hand == ENTRANT_HAND::NONE)
        entrant02Hand = hands[std::rand() % static_cast<int>(ENTRANT_HAND::VALUE)];

    // ����Z�b�g
    gameMode->GetEntrant01()->SetMeshNo(entrant01Hand);
    gameMode->GetEntrant02()->SetMeshNo(entrant02Hand);

    // ���s�����߂�
    int result = GameMode::RESULT::NONE;
    if (entrant01Hand == entrant02Hand)
        result = GameMode::RESULT::DRAW;
    else if (
        (static_cast<int>(entrant01Hand) + 1) % static_cast<int>(ENTRANT_HAND::VALUE)
        <= static_cast<int>(entrant02Hand)
    )
        result = GameMode::RESULT::WIN_1;
    else
        result = GameMode::RESULT::WIN_2;

    // ���̃t�F�[�Y��
    gameMode->ResetTimer();
    phase = PHASE::IDLE;

    // ���ʂ����^�[��
    gameMode->SetResult(result);
}

void RockScissorsPaper::PhaseIdle(GameMode* gameMode)
{
    //TODO:���������ւ̑J�ڂ𖳌�����
    #if 1
    if (config::gamerule::rsp::IDLE_SEC < gameMode->TimerSec())
    {
        gameMode->ResetTimer();
        gameMode->SetGameRule<PushHands>();
        return;
    }

    #endif // 0

}

void RockScissorsPaper::DrawDebugGUI(GameMode* gameMode)
{
    #if USE_IMGUI
    if (ImGui::CollapsingHeader("RockScissorsPaper", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Current Phase : %d", static_cast<int>(phase));
        ImGui::Text("Timer(In Second) : %f", gameMode->TimerSec());
        std::string hand01 = "Entrant01 : " + debugHandName.at(entrant01Hand);
        ImGui::Text(hand01.c_str());
        std::string hand02 = "Entrant02 : " + debugHandName.at(entrant02Hand);
        ImGui::Text(hand02.c_str());
    }

    #endif // USE_IMGUI
}

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
    bool isPlayer01 = gameMode->GetEntrant01()->IsActiveKey();
    bool isPlayer02 = gameMode->GetEntrant02()->IsActiveKey();
    _ASSERT_EXPR(isPlayer01 == true || isPlayer02 == true, L"�ǂ��炩�Е����v���C���[�ł���K�v������܂��B");

    namespace push_hands = config::gamerule::push_hands;

    /* �K�v�ȃv�b�V�������v�Z */
    switch (gameMode->LastResult())
    {
    case GameMode::RESULT::DRAW:
        pushRequire01 = push_hands::BASE_PUSH_COUNT;
        pushRequire02 = push_hands::BASE_PUSH_COUNT;
        break;

    case GameMode::RESULT::WIN_1:
        pushRequire01 = push_hands::BASE_PUSH_COUNT;
        pushRequire02 = push_hands::BASE_PUSH_COUNT + push_hands::PENALTY_PUSH_COUNT;
        break;

    case GameMode::RESULT::WIN_2:
        pushRequire01 = push_hands::BASE_PUSH_COUNT + push_hands::PENALTY_PUSH_COUNT;
        pushRequire02 = push_hands::BASE_PUSH_COUNT;
        break;

    default:
        _ASSERT_EXPR(false, L"result�̒l���s�K��");
        break;

    }

}

void PushHands::Run(GameMode* gameMode)
{
    switch (phase)
    {
    case PHASE::SETUP:
        Setup(gameMode);
        phase = PHASE::RECEPTION;
        /*fallthrough*/
    case PHASE::RECEPTION:
        PhaseReception(gameMode);
        break;
    case PHASE::JUDGE:
        PhaseJudge(gameMode);
        break;
    case PHASE::IDLE:
        PhaseIdle(gameMode);
        break;
    }

    DrawDebugGUI(gameMode);
}

void PushHands::PhaseReception(GameMode* gameMode)
{
    CheckPush(gameMode->GetEntrant01(), &pushRequire01);
    CheckPush(gameMode->GetEntrant02(), &pushRequire02);
    
    if (
        pushRequire01 == 0 || pushRequire02 == 0 ||
        config::gamerule::push_hands::RECEPTION_SEC < gameMode->TimerSec()
    )
    {
        gameMode->ResetTimer();
        phase = PHASE::JUDGE;
        return;
    }
}
void PushHands::CheckPush(Entrant* entrant, int* counter)
{
    int trigger = entrant->KeyInput();
    if (trigger & (entrant->GetKeyBind()->keyLeft | entrant->GetKeyBind()->keyRight))
    {
        (*counter)--;
    }
}

void PushHands::PhaseJudge(GameMode* gameMode)
{
    /* �l�𒲐� */
    pushRequire01 = (std::max)(pushRequire01, 0);
    pushRequire02 = (std::max)(pushRequire02, 0);

    /* ���s�𔻒� */
    int result = GameMode::RESULT::NONE;
    
    gameMode->SetResult(result);

    /* �J�ڂ̏��� */
    gameMode->ResetTimer();
    phase = PHASE::IDLE;
}
int PushHands::JudgeResult(GameMode* gameMode)
{
    int result = GameMode::RESULT::NONE;

    // ���^�C�~���O�ŉ����؂����ꍇ
    if (pushRequire01 == pushRequire02)
    {
        result = GameMode::RESULT::DRAW;
    }
    // ���01�������؂����ꍇ
    else if (pushRequire01 == 0 && pushRequire01 < pushRequire02)
    {
        result = GameMode::RESULT::WIN_1;
    }
    // ���02�������؂����ꍇ
    else if (pushRequire02 == 0 && pushRequire02 < pushRequire01)
    {
        result = GameMode::RESULT::WIN_2;
    }
    // �ǂ�������Ԑ؂�̏ꍇ
    else
    {
        bool isPlayer01 = gameMode->GetEntrant01()->IsActiveKey();
        bool isPlayer02 = gameMode->GetEntrant02()->IsActiveKey();

        // 01���v���C���[�̏ꍇ
        if (isPlayer01 == false && isPlayer02 == true)
        {
            result = GameMode::RESULT::WIN_2;
        }
        // 02���v���C���[�̏ꍇ
        else if (isPlayer01 == false && isPlayer02 == true)
        {
            result = GameMode::RESULT::WIN_1;
        }
        // �����Ƃ�NPC�̏ꍇ
        else if (isPlayer01 == false && isPlayer02 == false)
        {
            result = GameMode::RESULT::DRAW;
        }
        // �����Ƃ��v���C���[�̏ꍇ
        else /*if (isPlayer01 == true && isPlayer02)*/
        {
            // �����ꍇ
            if (pushRequire01 == pushRequire02)
            {
                result = GameMode::RESULT::DRAW;
            }
            // 01�������Ă����ꍇ
            else if (pushRequire01 < pushRequire02)
            {
                result = GameMode::RESULT::WIN_1;
            }
            // 02�������Ă����ꍇ
            else if (pushRequire02 < pushRequire01)
            {
                result = GameMode::RESULT::WIN_2;
            }
        }
    }

    return result;
}

void PushHands::PhaseIdle(GameMode* gameMode)
{
    //TODO:�����������Ăق��ւ̑J�ڂ𖳌�����
    #if 0
    if (config::gamerule::push_hands::IDLE_SEC < gameMode->TimerSec())
    {
        gameMode->ResetTimer();
        gameMode->SetGameRule<PushHands>();
        return;
    }

    #endif // 0

}

void PushHands::DrawDebugGUI(GameMode* gameMode)
{
    #if USE_IMGUI
    if (ImGui::CollapsingHeader("PushHands", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Current Phase : %d", static_cast<int>(phase));
        ImGui::Text("Timer(In Second) : %f", gameMode->TimerSec());
        ImGui::InputInt("PushRequire01", &pushRequire01, 1, 100, ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
        ImGui::InputInt("PushRequire02", &pushRequire02, 1, 100, ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
    }
    #endif // USE_IMGUI
}