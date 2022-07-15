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
        {BIT_NO::BIT_01, TechSharkLib::KeyCodes::MouseLeft},
    };

    TechSharkLib::Float2 pos;
    TechSharkLib::Float2 pos2;

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
    start       = TechSharkLib::LoadSprite(L"Data/Images/start.png");
    exit        = TechSharkLib::LoadSprite(L"Data/Images/exit.png");
}

void SceneTitle::Setup()
{
    namespace button = config::button;

    Scene::Setup();
    TechSharkLib::SetAssignData(0, keyAssignList, {});
    toGame.Setup(
        button::START_POS.x, button::START_POS.y,
        button::SIZE.x, button::SIZE.y,
        1.0f, 0.0f, 0.0f, 0.5f
    );
    toExit.Setup(
        button::EXIT_POS.x, button::EXIT_POS.y,
        button::SIZE.x, button::SIZE.y,
        1.0f, 0.0f, 0.0f, 0.5f
    );
    TechSharkLib::Play(music::TITLE_MUSIC, true);
}

void SceneTitle::Update(float deltaTime)
{
    if (TechSharkLib::keyTrigger(0) & BIT_NO::BIT_00)
    {
        Scene::ChangeScene<SceneGameSingle>();
        TechSharkLib::Play(sound::XWB_SOUND, sound::DECISION);
        return;
    }
    if (1.0f < elapsedSec) //UNDONE:Result‚©‚çƒ{ƒ^ƒ“‚Å–ß‚Á‚Ä‚­‚é‚ÆtoGame‚ª‰Ÿ‚³‚ê‚Ä‚µ‚Ü‚¤‚±‚Æ‚Ì‘Îô
    {
        if (toGame.IsClicked(1 << BIT_NO::BIT_01))
        {
            Scene::ChangeScene<SceneGameSingle>();
            TechSharkLib::Play(sound::XWB_SOUND, sound::DECISION);
            return;
        }
        if (toExit.IsClicked(1 << BIT_NO::BIT_01))
        {
            PostQuitMessage(0);
            return;
        }
    }

    #if USE_IMGUI
    ImGui::Begin("Title");
    ImGui::Text("Home : SceneSelect");
    ImGui::SliderFloat2("pos", &pos.x, 0.0f, 1280.0f);
    ImGui::SliderFloat2("pos2", &pos2.x, 0.0f, 1280.0f);
    ImGui::End();

    #endif // USE_IMGUI

    elapsedSec += deltaTime;
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
        start,
        button::START_POS.x, button::START_POS.y,
        button::SCALE.x,    button::SCALE.y,
        0.0f, 0.0f,
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    );
    TechSharkLib::Render(
        exit,
        button::EXIT_POS.x, button::EXIT_POS.y,
        button::SCALE.x,    button::SCALE.y,
        0.0f, 0.0f,
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    );

    toGame.Render();
    toExit.Render();
}

void SceneTitle::Deinit()
{
    TechSharkLib::Stop(music::TITLE_MUSIC);
    TechSharkLib::Release(background);
    TechSharkLib::Release(start);
    TechSharkLib::Release(exit);
}