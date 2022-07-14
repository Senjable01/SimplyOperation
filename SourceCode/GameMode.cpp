//------< include >-----------------------------------------------------------------------
#include "GameMode.h"
#include <utility>
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"
#include <map>
#include <string>

#endif // USE_IMGUI
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "Config.h"

//========================================================================================
// 
//      GameRule
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void GameRule::Run(GameMode* gameMode)
{
    switch (phase)
    {
    case PHASE::SETUP:
        Setup(gameMode);
        phase = PHASE::RECEPTION;
        /*fallthrough*/
    case PHASE::RECEPTION:
        Reception(gameMode);
        break;

    case PHASE::JUDGE:
        Judge(gameMode);
        phase = PHASE::IDLE;
        /*fallthrough*/
    case PHASE::IDLE:
        Idle(gameMode);
        break;
    }
}

#if USE_IMGUI
//------< namespace >---------------------------------------------------------------------
namespace
{
    std::map<GameMode::RESULT, std::string> resultNameMap = {
        {GameMode::RESULT::DRAW,    "Draw"},
        {GameMode::RESULT::WIN_1P,  "Win Player01"},
        {GameMode::RESULT::WIN_2P,  "Win Player02"},
        {GameMode::RESULT::NONE,    "None"}
    };
    bool isActive = true;
}

#endif // USE_IMGUI

//========================================================================================
// 
//      GameMode
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void GameMode::Update(float deltaTime)
{
    if (nextRule != nullptr)
    {
        gameRule = std::move(nextRule);
        nextRule.reset(nullptr);
    }

    #if USE_IMGUI
    (*gameRule)(this);

    ImGui::SetNextWindowPos(ImVec2{10.0f, 10.0f}, ImGuiCond_::ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2{300.0f, 400.0f}, ImGuiCond_::ImGuiCond_Once);
    ImGui::Begin("GameMode");
    if (ImGui::CollapsingHeader("Status", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
    {
        std::string lastResutStr = "Last Result : " + resultNameMap.at(lastResult);
        ImGui::Text("Timer(sec) : %f", timerSec);
        ImGui::Text(lastResutStr.c_str());
        if (ImGui::Button("Play / Pause")) { isActive = !isActive; }
    }
    gameRule->DrawDebugGUI();
    ImGui::End();

    if (isActive)
    {
        if (onceSkipAddSec)
        {
            onceSkipAddSec = false;
            return;
        }
        timerSec += deltaTime;
    }

    #else
    (*gameRule)(this);

    if (onceSkipAddSec)
    {
        onceSkipAddSec = false;
        return;
    }
    elapsedSec += deltaTime;

    #endif // USE_IMGUI
}
void GameMode::Render()
{
    DirectX::XMMATRIX mtrixScale    = DirectX::XMMatrixScaling(headScale.x, headScale.y, headScale.z);
    DirectX::XMMATRIX mtrixRotation = DirectX::XMMatrixRotationRollPitchYaw(headRotation.x, headRotation.y, headRotation.z);
    DirectX::XMMATRIX mtrixPosition = DirectX::XMMatrixTranslation(headPos.x, headPos.y, headPos.z);
    DirectX::XMFLOAT4X4 local = {};
    DirectX::XMStoreFloat4x4(&local, mtrixScale * mtrixRotation * mtrixPosition);
    TechSharkLib::Render(entrant02Head, local);
}
void GameMode::End()
{
    entrants.fill(nullptr);
    gameRule.reset(nullptr);
    nextRule.reset(nullptr);
    timerSec        = 0.0f;
    onceSkipAddSec  = true;
    lastResult      = RESULT::NONE;
    isFinished      = false;
    TechSharkLib::Release(entrant02Head);
}

void GameMode::Setup()
{
    namespace head = config::model::head;

    // アサーションチェック
    _ASSERT_EXPR(
        entrants.at(static_cast<size_t>(ENTRANT::_01)) != nullptr,
        L"Entrant01が未設定"
    );
    _ASSERT_EXPR(
        entrants.at(static_cast<size_t>(ENTRANT::_02)) != nullptr,
        L"Entrant02が未設定"
    );
    _ASSERT_EXPR(camera != nullptr, L"Cameraが未設定");

    // カメラ
    firstCameraFocus = camera->Focus();

    // Entrant02 Head
    entrant02Head = TechSharkLib::LoadStaticMesh(
        entrants.at(static_cast<size_t>(ENTRANT::_02))->IsNPC() ?
            L"Data/Models/Enemy_Face/Enemy_Face.obj" :
            L"Data/Models/Player_Face/Player_Face.obj",
        true
    );
    headPos             = head::POSITION;
    headScale           = head::SCALE;
    headRotation        = head::ROTATE_NORMAL_BACK;
    firstHeadRotation   = headRotation;
}