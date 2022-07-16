//------< include >-----------------------------------------------------------------------
#include "SceneTitle.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "SceneGameSingle.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI
#include "Config.h"
#include "Audio.h"

//------< using >-------------------------------------------------------------------------
using TechSharkLib::BIT_NO;

//------< namespace >---------------------------------------------------------------------
namespace
{
    TechSharkLib::KeyAssignList keyAssignList = {
        #if DEBUG_MODE
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Home},

        #endif // DEBUG_MODE
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Enter},
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Space},
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::W},
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::A},
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::S},
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::D},
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Up},
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Left},
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Right},
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Down},
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::MouseLeft},
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::MouseRight},
    };

    TechSharkLib::Float2 pos;
    TechSharkLib::Float2 scale = {1.0f, 1.0f};

}

//========================================================================================
// 
//      SceneTitle
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void SceneTitle::Init()
{
    background  = TechSharkLib::LoadSprite(L"Data/Images/Title.png");
    specialThanks = TechSharkLib::LoadSprite(L"Data/Images/HIMAWARI.png");
}

void SceneTitle::Setup()
{
    namespace button = config::button;

    Scene::Setup();
    TechSharkLib::SetAssignData(0, keyAssignList, {});
    TechSharkLib::Play(music::TITLE_MUSIC, true);
}

void SceneTitle::Update(float /*deltaTime*/)
{
    if (TechSharkLib::keyTrigger(0) & BIT_NO::BIT_00)
    {
        Scene::ChangeScene<SceneGameSingle>();
        TechSharkLib::Play(sound::XWB_SOUND, sound::DECISION);
        return;
    }

    #if USE_IMGUI
    ImGui::Begin("Title");
    ImGui::Text("Home : SceneSelect");
    ImGui::SliderFloat2("pos", &pos.x, 0.0f, 1280.0f);
    ImGui::SliderFloat2("pos2", &scale.x, 0.0f, 1.0f);
    ImGui::End();

    #endif // USE_IMGUI
}

void SceneTitle::Render()
{
    namespace back      = config::background;
    namespace button    = config::button;

    TechSharkLib::SetDepthState(TechSharkLib::DEPTH_STATE::NONE);
    TechSharkLib::SetRasterizerState(TechSharkLib::RASTERIZER_STATE::SOLID);

    TechSharkLib::Render(
        background,
        back::POSITION.x, back::POSITION.y,
        back::SCALE.x, back::SCALE.y,
        back::PIVOT.x, back::PIVOT.y,
        0.0f,
        back::COLOR.x, back::COLOR.y, back::COLOR.z, back::COLOR.w
    );
    TechSharkLib::Render(
        specialThanks,
        0.0f, 670.0f,
        0.3f, 0.3f,
        0.0f, 0.0f,
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    );
}

void SceneTitle::Deinit()
{
    TechSharkLib::Stop(music::TITLE_MUSIC);
    TechSharkLib::Release(background);
    TechSharkLib::Release(specialThanks);
}