//------< include >-----------------------------------------------------------------------
#include "SceneResultSingle.h"
#include "../TechSharkLib/Inc/KeyAssign.h"
#include "SceneGameSingle.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "SceneTitle.h"
//#include "SceneSelect.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"
#include <string>

#endif // USE_IMGUI
//#include "Config.h"

//------< using >-------------------------------------------------------------------------
using TechSharkLib::BIT_NO;

//------< namespace >---------------------------------------------------------------------
namespace
{
    TechSharkLib::KeyAssignList keyAssignList = {
        {BIT_NO::BIT_00, TechSharkLib::KeyCodes::MouseLeft}
    };
    #if USE_IMGUI
    std::map<config::rule::RESULT, std::string> resultNameMap = {
        {config::rule::RESULT::DRAW,    "DRAW"},
        {config::rule::RESULT::WIN_1P,  "Win Entrant01"},
        {config::rule::RESULT::WIN_2P,  "Win Entrant02"},
        {config::rule::RESULT::NONE,    "None"}
    };

    #endif // USE_IMGUI

}

//========================================================================================
// 
//      SceneResultSingle
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void SceneResultSingle::Init()
{
    _ASSERT_EXPR(result != RESULT::NONE && result != RESULT::DRAW, L"ゲームの最終結果が不適切");

    backResult = TechSharkLib::LoadSprite(
        result == RESULT::WIN_1P ? 
        L"./Data/Images/YOU_WIN.png" : 
        L"./Data/Images/YOU_LOSE.png"
    );
}

void SceneResultSingle::Setup()
{
    Scene::Setup();
    TechSharkLib::SetAssignData(0, keyAssignList, {});

    rotateZPerSec = config::background::ROTATE_Z_PER_SEC;
    toTitle.Setup(300.0f, 100.0f, 128.0f, 64.0f, 1.0f, 0.4f, 0.4f, 0.5f);
}

void SceneResultSingle::Update(float deltaTime)
{
    if (toTitle.IsClicked(1 << BIT_NO::BIT_00))
    {
        Scene::ChangeScene<SceneTitle>();
        return;
    }

    rotationZ += rotateZPerSec * deltaTime;
    if (DirectX::XM_PIDIV2 < rotationZ)
    {
        rotateZPerSec   = -rotateZPerSec;
        rotationZ       = DirectX::XM_PIDIV2 - FLT_EPSILON;
    }
    else if (rotationZ < -DirectX::XM_PIDIV2)
    {
        rotateZPerSec   = -rotateZPerSec;
        rotationZ       = -DirectX::XM_PIDIV2 + FLT_EPSILON;
    }

    #if USE_IMGUI
    ImGui::Begin("ResultSingle");
    ImGui::Text(resultNameMap.at(result).c_str());
    ImGui::End();

    #endif // USE_IMGUI

}

void SceneResultSingle::Render()
{
    namespace back = config::background;

    TechSharkLib::SetDepthState(TechSharkLib::DEPTH_STATE::NONE);
    TechSharkLib::SetRasterizerState(TechSharkLib::RASTERIZER_STATE::SOLID);

    TechSharkLib::Render(
        backResult, back::POSITION.x, back::POSITION.y,
        back::SCALE.x, back::SCALE.y,
        back::PIVOT.x, back::PIVOT.y,
        rotationZ,
        back::COLOR.x, back::COLOR.y, back::COLOR.z, back::COLOR.w
    );

    toTitle.Render();

}

void SceneResultSingle::Deinit()
{
    TechSharkLib::Release(backResult);
}