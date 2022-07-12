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
#include "GameMode.h"
#include "GameRule.h"
#include "Entrant.h"
#include "Config.h"
#include "Recipe.h"
#include <thread>

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
    int     loadNum             = 0;

    TechSharkLib::KeyAssignList keyAssignList = {
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Home},
        config::key::left0,
        config::key::right0,
        config::key::up0,
        config::key::down0,
        config::key::left1,
        config::key::right1,
        config::key::up1,
        config::key::down1,
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
    Entrant::LoadMeshes();
}

void SceneGameSingle::Setup()
{
    Scene::Setup();
    TechSharkLib::SetDisplayFrameRate(true);
    TechSharkLib::SetAssignData(0, keyAssignList, {});

    camera = {};

    camera.LookAt({0.0f, 0.0f, -10.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    camera.CalcAndSetPerspectiveMatrix(TechSharkLib::ToRadian(30.0f), TechSharkLib::AspectRatio(), 0.1f, 100.0f);
    
    std::thread th(CreateGameObjects, &objManager, &gameMode);
    th.join();
    //CreateGameObjects(&objManager, &gameMode);
    lightDirection = Float4{ 0.0f, 0.0f, 10.0f, 1.0f };

    TechSharkLib::SetProjector(TechSharkLib::SCENE_CONSTANTS::DEFAULT);

    gameMode.SetNextRule<RockScissorsPaper>();

    loadNum++;
}

void SceneGameSingle::CreateGameObjects(TechSharkLib::GameObjectManager* objManager, GameMode* gameMode)
{
    recipe::CreateMesh(
        objManager,
        L"./Data/Models/Haikei/Haikei.obj",
        {0.0f, 0.0f, 24.0f}, {0.1f, 0.1f, 0.1f}, {0.0f, 0.0f, 0.0f},
        "Haikei"
    );

    recipe::CreateEntrant01(objManager, gameMode);
    recipe::CreateEntrant02(objManager, gameMode, true);
    recipe::CreateControllerGuide(objManager, {-3.5f, -0.0f, 0.0f});
}

void SceneGameSingle::Update(float deltaTime)
{
    if (TechSharkLib::keyTrigger(0) & BIT_NO::BIT_00)
    {
        Scene::ChangeScene<SceneGameSingle>();
        return;
    }

    objManager.Update(deltaTime);
    gameMode.Update(deltaTime);
    if (gameMode.IsFinished())
    {
        Scene::ChangeScene<SceneResultSingle>(gameMode.LastResult());
    }

    #if USE_IMGUI
    ImGui::Begin("GameSingle");
    ImGui::Text(u8"ロード数 %d", loadNum);
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
    TechSharkLib::SetRasterizerState(TechSharkLib::RASTERIZER_STATE::SOLID);
    TechSharkLib::Project(&camera, lightDirection);

    objManager.Render();
}

void SceneGameSingle::Deinit()
{
    objManager.Deinit();

    TechSharkLib::SetDisplayFrameRate(false);

    gameMode.Clear();
    Entrant::UnloadMeshes();
}