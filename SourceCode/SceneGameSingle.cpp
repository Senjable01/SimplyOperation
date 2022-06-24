//------< include >-----------------------------------------------------------------------
#include "SceneGameSingle.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "../TechSharkLib/Inc/Arithmetic.h"
#include "SceneResultSingle.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI

//------< using >-------------------------------------------------------------------------
using TechSharkLib::SpriteID;
using TechSharkLib::SpriteBatchID;
using TechSharkLib::BIT_NO;
using TechSharkLib::StaticMeshID;
using TechSharkLib::Float3;

namespace
{
    SpriteID       backID       = {};
    SpriteID       brickID      = {};
    SpriteBatchID  brickBID     = {};

    int     brickColumn         = 1;
    int     brickRow            = 1;
    bool    drawBrickByBatch    = false;
    int     loadNum             = 0;

    constexpr int   MAX_COLUMN  = 32;
    constexpr int   MAX_ROW     = 18;
    constexpr float BRICK_SCALE = 0.1f;
    constexpr float BRICK_W     = 400.0f * BRICK_SCALE;
    constexpr float BRICK_H     = 400.0f * BRICK_SCALE;

    enum HAND { ROCK = 0, SCISSORS, PAPER, NUM };
    StaticMeshID staticMeshes[HAND::NUM]    = {};
    int meshIndex                           = ROCK;

    Float3 scale    = {0.5f, 0.5f, 0.5f};
    Float3 rotation = {};
    Float3 position = {};

    TechSharkLib::KeyAssignList keyAssignList = {
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Home}
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
    backID      = TechSharkLib::LoadSprite(L"./Data/back.png");
    brickID     = TechSharkLib::LoadSprite(L"./Data/test_brick.jpg");
    brickBID    = TechSharkLib::LoadSpriteBatch(L"./Data/test_brick.jpg", MAX_COLUMN * MAX_ROW);

    staticMeshes[HAND::ROCK]        = TechSharkLib::LoadStaticMesh(L"./Data/éOäpâªâºëfçﬁ_ÉOÅ[/puroto_guu.obj", true);
    staticMeshes[HAND::SCISSORS]    = TechSharkLib::LoadStaticMesh(L"./Data/éOäpâªâºëfçﬁ_É`ÉáÉL/puroto_choki.obj", true);
    staticMeshes[HAND::PAPER]       = TechSharkLib::LoadStaticMesh(L"./Data/éOäpâªâºëfçﬁ_ÉpÅ[/puroto_paa.obj", true);
}

void SceneGameSingle::Setup()
{
    Scene::Setup();
    TechSharkLib::SetDisplayFrameRate(true);
    TechSharkLib::SetAssignData(0, keyAssignList, {});

    camera.LookAt({1.0f, 1.0f, -10.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    camera.CalcAndSetPerspectiveMatrix(TechSharkLib::ToRadian(30.0f), TechSharkLib::AspectRatio(), 0.1f, 100.0f);
    TechSharkLib::SetProjector(TechSharkLib::SCENE_CONSTANTS::DEFAULT);

    loadNum++;
}

void SceneGameSingle::Update(float/*deltaTime*/)
{
    if (TechSharkLib::keyTrigger(0) & BIT_NO::BIT_00)
    {
        Scene::ChangeScene<SceneResultSingle>();
        return;
    }

    #if USE_IMGUI
    ImGui::Begin("GameSingle");
    ImGui::Text("Load Num %d", loadNum);
    if (ImGui::Button("Reload"))
    {
        Scene::ChangeScene<SceneGameSingle>();
        ImGui::End();
        return;
    }
    ImGui::SameLine();
    ImGui::Text(" / Home");
    ImGui::NewLine();
    if (ImGui::CollapsingHeader("2D"))
    {
        ImGui::Checkbox("DrawBrickByBatch", &drawBrickByBatch);
        ImGui::SliderInt("column", &brickColumn, 0, MAX_COLUMN);
        ImGui::SliderInt("row", &brickRow, 0, MAX_ROW);
    }
    camera.DrawDebugGUI();
    if (ImGui::CollapsingHeader("3D"))
    {
        ImGui::SliderInt("OBJ Type", &meshIndex, ROCK, PAPER);
        ImGui::SliderFloat3("light", &lightDirection.x, -20.0f, 20.0f);
        ImGui::SliderFloat3("position", &position.x, -50.0f, 50.0f);
        ImGui::InputFloat3("scale", &scale.x);
        ImGui::SliderFloat3("rotation", &rotation.x, TechSharkLib::ToRadian(-180.0f), TechSharkLib::ToRadian(180.0f));
    }
    ImGui::End();

    #endif // USE_IMGUI

}

void SceneGameSingle::Render()
{
    TechSharkLib::SetRasterizerState(TechSharkLib::RASTERIZER_STATE::SOLID/*_CULLING*/);
    TechSharkLib::Render(backID, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

    if (drawBrickByBatch)
    {
        TechSharkLib::Begin(brickBID);
        for (int r = 0; r < brickRow; r++)
        {
            for (int c = 0; c < brickColumn; c++)
            {
                TechSharkLib::Render(
                    brickBID,
                    BRICK_W * c, BRICK_H * r,
                    BRICK_SCALE, BRICK_SCALE,
                    0.0f, 0.0f, 0.0f,
                    1.0f, 1.0f, 1.0f, 1.0f
                );
            }
        }
        TechSharkLib::End(brickBID);
    }
    else
    {
        for (int r = 0; r < brickRow; r++)
        {
            for (int c = 0; c < brickColumn; c++)
            {
                TechSharkLib::Render(
                    brickID,
                    BRICK_W * c, BRICK_H * r,
                    BRICK_SCALE, BRICK_SCALE,
                    0.0f, 0.0f, 0.0f,
                    1.0f, 1.0f, 1.0f, 1.0f
                );
            }
        }
    }

    TechSharkLib::SetRasterizerState(TechSharkLib::RASTERIZER_STATE::SOLID/*_CULLING*/);
    TechSharkLib::Project(&camera, lightDirection);
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
    DirectX::XMFLOAT4X4 world = {};
    DirectX::XMStoreFloat4x4(&world, S * R * T);
    TechSharkLib::Render(staticMeshes[meshIndex], world);
}

void SceneGameSingle::Deinit()
{
    brickColumn         = 1;
    brickRow            = 1;
    drawBrickByBatch    = false;

    TechSharkLib::Release(backID);
    TechSharkLib::Release(brickID);
    TechSharkLib::Release(brickBID);
    for (auto& mesh : staticMeshes)
    {
        TechSharkLib::Release(mesh);
    }
    meshIndex   = HAND::ROCK;
    scale       = Float3{0.5f, 0.5f, 0.5f};
    rotation    = Float3{};
    position    = Float3{};

    TechSharkLib::SetDisplayFrameRate(false);
}