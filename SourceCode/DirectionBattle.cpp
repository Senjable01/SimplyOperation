//------< include >-----------------------------------------------------------------------
#include "DirectionBattle.h"
#include "Config.h"
#include "RockScissorsPaper.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"
#include <string>

#endif // USE_IMGUI
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "Audio.h"

#if USE_IMGUI
//------< namespace >---------------------------------------------------------------------
namespace
{
    std::map<Entrant::STATE, std::string> directionNameMap = {
        {Entrant::STATE::LEFT,  "Left"},
        {Entrant::STATE::RIGHT, "Right"},
        {Entrant::STATE::UP,    "Up"},
        {Entrant::STATE::DOWN,  "Down"},
        {Entrant::STATE::NONE,  "None"}
    };
}

#endif // USE_IMGUI

//========================================================================================
// 
//      DirectionBattle
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void DirectionBattle::Setup(GameMode* gameMode)
{
    entrant01Direction = Entrant::STATE::NONE;
    entrant02Direction = Entrant::STATE::NONE;
    GameMode::RESULT lastResult = gameMode->LastResult();
    _ASSERT_EXPR(
        lastResult != GameMode::RESULT::NONE && lastResult != GameMode::RESULT::DRAW,
        L"押し合いの勝敗結果が不適切"
    );
    roleFlag = (lastResult == GameMode::RESULT::WIN_1P) ? ROLE::ATK_DEF : ROLE::DEF_ATK;
    MoveCamera      = nullptr;
    cameraMoveSec   = config::rule::direction::MOVE_CAMERA_SEC;
    gameMode->GetEntrant01Ref()->SetMesh(Entrant::STATE::NONE);
    gameMode->GetEntrant02Ref()->SetMesh(Entrant::STATE::NONE);
    gameMode->RezeroTimer();
    gameMode->NotyfyToGuide(OperateGuide::STATE::DB);
    gameMode->NotyfyToBackgrounds(GameMode::BG_NO::DB_RECEPTION);
    TechSharkLib::Play(sound::XWB_VOICE, sound::DB_RECEPTION);
}

void DirectionBattle::Reception(GameMode* gameMode)
{
    namespace dir = config::rule::direction;

    if (dir::END_RECEPTION_SEC < gameMode->TimerSec())
    {
        gameMode->RezeroTimer();
        phase = PHASE::JUDGE;
        return;
    }

    PointByInput(gameMode->GetEntrant01Ref(), &entrant01Direction);
    PointByInput(gameMode->GetEntrant02Ref(), &entrant02Direction);

}
void DirectionBattle::PointByInput(Entrant* entrant, Entrant::STATE* direction)
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
        *direction = Entrant::STATE::LEFT;
    }
    else if (onlyPushedKey == keyBind.up)
    {
        *direction = Entrant::STATE::UP;
    }
    else if (onlyPushedKey == keyBind.right)
    {
        *direction = Entrant::STATE::RIGHT;
    }
    else if (onlyPushedKey == keyBind.down)
    {
        *direction = Entrant::STATE::DOWN;
    }
}

void DirectionBattle::Judge(GameMode* gameMode)
{
    // 方向が決まっていなければ勝手に決定
    if (entrant01Direction == Entrant::STATE::NONE)
    {
        PointByRandom(&entrant01Direction);
    }
    if (entrant02Direction == Entrant::STATE::NONE)
    {
        #if DEBUG_MODE
        entrant02Direction = Entrant::STATE::RIGHT;
        #else
        PointByRandom(&entrant02Direction);
        #endif // DEBUG_MODE
    }

    // アサーションチェック
    _ASSERT_EXPR(
        static_cast<int>(Entrant::STATE::LEFT) <= static_cast<int>(entrant01Direction) ||
        static_cast<int>(entrant01Direction) <= static_cast<int>(Entrant::STATE::DOWN),
        L"Entrant01の方向が不適切"
    );
    _ASSERT_EXPR(
        static_cast<int>(Entrant::STATE::LEFT) <= static_cast<int>(entrant02Direction) ||
        static_cast<int>(entrant02Direction) <= static_cast<int>(Entrant::STATE::DOWN),
        L"Entrant01の方向が不適切"
    );

    // 勝敗を判定、送信
    gameMode->SetResult(JudgeResult());

    // メッシュを通知
    if (roleFlag == ROLE::ATK_DEF)
    {
        gameMode->GetEntrant01Ref()->SetMesh(entrant01Direction);
        gameMode->SetEntrant02HeadRotation(DirectionBattle::headRotations.at(entrant02Direction));
    }
    else
    {
        TechSharkLib::Float4 cameraFocus        = gameMode->FirstCameraFocus();
        TechSharkLib::Float4 movedCameraFocus   = DirectionBattle::cameraFocuses.at(entrant01Direction);
        TechSharkLib::Float4 moveSec            = (movedCameraFocus - cameraFocus) / cameraMoveSec;
        moveSec.w = cameraFocus.w;
        MoveCamera = [cameraFocus, moveSec, movedCameraFocus, gameMode]() -> void {
            TechSharkLib::Float4 after = cameraFocus;
            float timerSec = gameMode->TimerSec();
            // x
            after.x += moveSec.x * timerSec;
            if (0.0f < moveSec.x)
                after.x = (std::min)(after.x, movedCameraFocus.x);
            else
                after.x = (std::max)(after.x, movedCameraFocus.x);
            // y
            after.y += moveSec.y * timerSec;
            if (0.0f < moveSec.y)
                after.y = (std::min)(after.y, movedCameraFocus.y);
            else
                after.y = (std::max)(after.y, movedCameraFocus.y);
            // z
            after.z += moveSec.z * timerSec;
            if (0.0f < moveSec.z)
                after.z = (std::min)(after.z, movedCameraFocus.z);
            else
                after.z = (std::max)(after.z, movedCameraFocus.z);

            gameMode->SetCameraFocus(after);

        };
        gameMode->GetEntrant02Ref()->SetMesh(entrant02Direction);
    }

    // 次のフェーズへ移行
    gameMode->RezeroTimer();
    gameMode->NotyfyToGuide(OperateGuide::STATE::NONE);
    gameMode->NotyfyToBackgrounds(GameMode::BG_NO::DB_JUDGE);
    TechSharkLib::Play(sound::XWB_VOICE, sound::DB_JUDGE);
    phase = PHASE::IDLE;

}
void DirectionBattle::PointByRandom(Entrant::STATE* direction)
{
    Entrant::STATE directions[] = { Entrant::STATE::LEFT, Entrant::STATE::UP, Entrant::STATE::RIGHT, Entrant::STATE::DOWN };
    const int size = sizeof(directions) / sizeof(directions[0]);
    *direction = directions[std::rand() % size];
}
GameMode::RESULT DirectionBattle::JudgeResult()
{
    if (entrant01Direction != entrant02Direction)
    {
        return GameMode::RESULT::DRAW;
    }

    return (roleFlag == ROLE::ATK_DEF) ? GameMode::RESULT::WIN_1P : GameMode::RESULT::WIN_2P;
}

void DirectionBattle::Idle(GameMode* gameMode)
{
    namespace dir = config::rule::direction;
    
    if (dir::END_IDLE_SEC < gameMode->TimerSec())
    {
        entrant01Direction = Entrant::STATE::NONE;
        entrant02Direction = Entrant::STATE::NONE;
        MoveCamera = nullptr;
        gameMode->GetEntrant01Ref()->SetMesh(Entrant::STATE::NONE);
        gameMode->GetEntrant02Ref()->SetMesh(Entrant::STATE::NONE);
        gameMode->ResetCameraFocus();
        gameMode->ResetEntrant02HeadRotation();

        if (gameMode->LastResult() == GameMode::RESULT::DRAW)
        {
            gameMode->RezeroTimer();
            gameMode->SetNextRule<RockScissorsPaper>();
        }
        else
        {
            gameMode->FinishGame();
        }
    }

    if (MoveCamera)
        MoveCamera();
}

void DirectionBattle::DrawDebugGUI()
{
    #if USE_IMGUI
    if (ImGui::CollapsingHeader(u8"あっち向いてほい", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
    {
        std::string direction01 = "Entrant01 Direction : " + directionNameMap.at(entrant01Direction);
        std::string direction02 = "Entrant02 Direction : " + directionNameMap.at(entrant02Direction);
        ImGui::Text(u8"現在フェーズ : %d", static_cast<int>(phase));
        ImGui::Text(direction01.c_str());
        ImGui::Text(direction02.c_str());
        ImGui::Text(roleFlag == ROLE::ATK_DEF ? u8"1P 攻め / 2P 守り" : u8"1P 守り / 2P 攻め");
    }

    #endif // USE_IMGUI
}

//------------------------------------------------------------------------------
// instance
//------------------------------------------------------------------------------

std::map<Entrant::STATE, TechSharkLib::Float4> DirectionBattle::cameraFocuses = {
    {Entrant::STATE::LEFT,  config::entrant::CAMERA_LOOK_LEFT},
    {Entrant::STATE::RIGHT, config::entrant::CAMERA_LOOK_RIGHT},
    {Entrant::STATE::UP,    config::entrant::CAMERA_LOOK_UP},
    {Entrant::STATE::DOWN,  config::entrant::CAMERA_LOOK_DOWN}
};
std::map<Entrant::STATE, TechSharkLib::Float3> DirectionBattle::headRotations = {
    {Entrant::STATE::LEFT,  config::model::head::ROTATE_RIGHT_BACK},    // 左右反転
    {Entrant::STATE::RIGHT, config::model::head::ROTATE_LEFT_BACK},     // 左右反転
    {Entrant::STATE::UP,    config::model::head::ROTATE_UP_BACK},
    {Entrant::STATE::DOWN,  config::model::head::ROTATE_DOWN_BACK}
};