//------< include >-----------------------------------------------------------------------
#include "SceneSelect.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "SceneGameSingle.h"
#include "../TechSharkLib/Inc/Configulation.h"
#if USE_IMGUI
#include "../TechSharkLib/Inc/ImGuiCtrl.h"

#endif // USE_IMGUI

//TODO:01 �e�V�[�����쐬
// �X�e�[�W�I���A�Q�[��(vsNPC)�A���U���g(vsNPC)�ȂǁA�K�v�ȃV�[�����쐬����B
// �ЂƂ܂��L�[�őJ�ڂł���悤�ɂ���B
// Title.h / Title.cpp �����TechSharkLib�AImGui�͕ҏW���Ȃ����ƁB

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
//      SceneSelect
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void SceneSelect::Init()
{

}

void SceneSelect::Setup()
{
    Scene::Setup();
    TechSharkLib::SetAssignData(0, keyAssignList, {});
}

void SceneSelect::Update(float/*deltaTime*/)
{
    if (TechSharkLib::keyTrigger(0) & BIT_NO::BIT_00)
    {
        Scene::ChangeScene<SceneGameSingle>();
        return;
    }

    #if USE_IMGUI
    ImGui::Begin("Select");
    ImGui::End();

    #endif // USE_IMGUI

}

void SceneSelect::Render()
{

}

void SceneSelect::Deinit()
{

}