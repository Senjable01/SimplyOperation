//------< include >-----------------------------------------------------------------------
#include "SceneGameSingle.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "../TechSharkLib/Inc/Arithmetic.h"
#include "../TechSharkLib/Inc/Transform3D.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"
#include "SceneResultSingle.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI
#include "Config.h"
#include "Recipe.h"
#include "Entrant.h"
#include "RockScissorsPaper.h"
#include "OperateGuide.h"

//------< using >-------------------------------------------------------------------------
using TechSharkLib::SpriteID;
using TechSharkLib::SpriteBatchID;
using TechSharkLib::BIT_NO;
using TechSharkLib::StaticMeshID;
using TechSharkLib::Float3;
using TechSharkLib::Float4;
using TechSharkLib::GameObject;
using TechSharkLib::Transform3D;
using TechSharkLib::StaticMeshRenderer;

//------< namespace >---------------------------------------------------------------------
namespace
{
    TechSharkLib::KeyAssignList keyAssignList = {
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Home},
        config::key::left1,
        config::key::right1,
        config::key::up1,
        config::key::down1,
        config::key::left2,
        config::key::right2,
        config::key::up2,
        config::key::down2,
    };

}

//========================================================================================
// 
//      SceneGameSingle
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void SceneGameSingle::Init()
{
    using BG_NO = config::background::GAME_BG_NO;
    backgrounds.AddBackground(static_cast<Backgrounds::No>(BG_NO::RSP_FIRST),        L"Data/Images/1_saisyo_ha_Gu.png");
    backgrounds.AddBackground(static_cast<Backgrounds::No>(BG_NO::RSP_RECEPTION),    L"Data/Images/2_JANKEN.png");
    backgrounds.AddBackground(static_cast<Backgrounds::No>(BG_NO::RSP_JUDGE),        L"Data/Images/3_PON.png");
    backgrounds.AddBackground(static_cast<Backgrounds::No>(BG_NO::PH_RECEPTION),     L"Data/Images/4_Aragae.png");
    backgrounds.AddBackground(static_cast<Backgrounds::No>(BG_NO::DB_RECEPTION),     L"Data/Images/5_Atti_muite.png");
    backgrounds.AddBackground(static_cast<Backgrounds::No>(BG_NO::DB_JUDGE),         L"Data/Images/6_Hoi.png");
}

void SceneGameSingle::Setup()
{
    /* シーン */
    Scene::Setup();

    /* ウィンドウ */
    TechSharkLib::SetDisplayFrameRate(true);

    /* 描画関連 */
    camera = {};
    camera.LookAt({0.0f, 0.0f, -10.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    camera.CalcAndSetPerspectiveMatrix(TechSharkLib::ToRadian(30.0f), TechSharkLib::AspectRatio(), 0.1f, 100.0f);
    lightDirection = Float4{ 0.0f, 0.0f, 10.0f, 1.0f };
    TechSharkLib::SetProjector(TechSharkLib::SCENE_CONSTANTS::DEFAULT);

    /* 一般 */
    TechSharkLib::SetAssignData(0, keyAssignList, {});
    recipe::CreateEntrant01(&objManager, &gameMode);
    recipe::CreateEntrant02(&objManager, &gameMode, true);
    recipe::CreateGuide(&objManager, &gameMode, &camera, lightDirection);
    Entrant::LoadMeshes();
    OperateGuide::LoadMeshes();
    gameMode.SetCamera(&camera);
    gameMode.Start<RockScissorsPaper>();
    gameMode.AddBackgroundsObserver(backgrounds.GetObserverRef());
}

void SceneGameSingle::Update(float deltaTime)
{
    if (TechSharkLib::keyTrigger(0) & BIT_NO::BIT_00)
    {
        Scene::ChangeScene<SceneGameSingle>();
        return;
    }

    if (gameMode.IsFinished())
    {
        Scene::ChangeScene<SceneResultSingle>(gameMode.LastResult());
        return;
    }

    objManager.Update(deltaTime);
    gameMode.Update(deltaTime);
    backgrounds.Update();

    #if USE_IMGUI
    ImGui::Begin("GameSingle");
    if (ImGui::Button(u8"リロード"))
    {
        Scene::ChangeScene<SceneGameSingle>();
        ImGui::End();
        return;
    }
    ImGui::SameLine();
    ImGui::Text(" / Home");
    ImGui::NewLine();
    camera.DrawDebugGUI();
    if (ImGui::CollapsingHeader("3D"))
    {
        ImGui::SliderFloat3("light", &lightDirection.x, -20.0f, 20.0f);
    }
    ImGui::End();

    #endif // USE_IMGUI

}

void SceneGameSingle::Render()
{
    TechSharkLib::SetDepthState(TechSharkLib::DEPTH_STATE::NONE);
    TechSharkLib::SetRasterizerState(TechSharkLib::RASTERIZER_STATE::SOLID);
    backgrounds.Render();

    TechSharkLib::SetDepthState(TechSharkLib::DEPTH_STATE::TEST_AND_WRITE);
    TechSharkLib::Project(&camera, lightDirection);

    gameMode.Render();
    objManager.Render();
}

void SceneGameSingle::Deinit()
{
    backgrounds.Deinit();
    gameMode.End();
    objManager.Deinit();
    Entrant::ReleaseMeshes();
    OperateGuide::ReleaseMeshes();

    TechSharkLib::SetDisplayFrameRate(false);
}