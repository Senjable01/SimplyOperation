//------< include >-----------------------------------------------------------------------
#include "SceneTitle.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "SceneSelect.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI
#include "Config.h"

//------< using >-------------------------------------------------------------------------
using TechSharkLib::BIT_NO;

//------< namespace >---------------------------------------------------------------------
namespace
{
    TechSharkLib::KeyAssignList keyAssignList = {
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::Home}
    };
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
    background = TechSharkLib::LoadSprite(L"Data/Images/Title.png");
}

void SceneTitle::Setup()
{
    Scene::Setup();
    TechSharkLib::SetAssignData(0, keyAssignList, {});
}

void SceneTitle::Update(float)
{
    if (TechSharkLib::keyTrigger(0) & BIT_NO::BIT_00)
    {
        Scene::ChangeScene<SceneSelect>();
        return;
    }

    #if USE_IMGUI
    ImGui::Begin("Title");
    ImGui::Text("Home : SceneSelect");
    ImGui::End();

    #endif // USE_IMGUI

}

void SceneTitle::Render()
{
    namespace back = config::background;

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
}

void SceneTitle::Deinit()
{
    TechSharkLib::Release(background);
}