//------< include >-----------------------------------------------------------------------
#include "OperateGuide.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "Utility.h"

//========================================================================================
// 
//      OperateGuide
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void OperateGuide::Init()
{
    using TechSharkLib::Transform3D;
    using TechSharkLib::StaticMeshRenderer;

    transform = GetOwnerRef()->SearchComponent<Transform3D>();
    _ASSERT_EXPR(transform != nullptr, L"Transform3D�R���|�[�l���g�̌����Ɏ��s");
    #if _DEBUG
    StaticMeshRenderer* renderer = GetOwnerRef()->SearchComponent<StaticMeshRenderer>();
    _ASSERT_EXPR(renderer == nullptr, L"StaticMeshRenderer�R���|�[�l���g����菜���Ă��������B");

    #endif // _DEBUG
}
void OperateGuide::Setup()
{
    currentLean     = static_cast<int>(DIRECTION::NONE);
    currentState    = STATE::NONE;
    guideObserver   = {};
    timerSec        = 0.0f;
    _ASSERT_EXPR(description.defaultCamera != nullptr, L"�f�t�H���g�̃J���������ݒ�");
    camera          = *description.defaultCamera;
}
void OperateGuide::Update(float deltaTime)
{
    namespace guide = config::guide;
    if (guide::LEAN_INTERVAL < timerSec)
    {
        // �X���̏�Ԃ���i�߂�
        currentLean = (currentLean + 1) % static_cast<int>(DIRECTION::NUM);

        // �X���̏�Ԃ��X�L�b�v����
        if (currentState == STATE::RSP && currentLean == static_cast<int>(DIRECTION::DOWN))
        {
            currentLean = static_cast<int>(DIRECTION::LEFT);
        }
        if (currentState == STATE::PH)
        {
            if (static_cast<int>(DIRECTION::UP) <= currentLean)
            {
                currentLean = static_cast<int>(DIRECTION::LEFT);
            }
        }

        // timerSec�����Z�b�g
        timerSec = 0.0f;
    }

    timerSec += (currentState == STATE::PH) ? 
        deltaTime * 4 :
        deltaTime * 1;

    STATE nextState = guideObserver.State();
    if (currentState != nextState)
    {
        currentState = nextState;
        timerSec = 0.0f;
    }
}
void OperateGuide::Render(float /*scrollX*/, float /*scrollY*/)
{
    TechSharkLib::Project(&camera, description.lightDirection);
    TechSharkLib::SetDepthState(TechSharkLib::DEPTH_STATE::NONE);
    switch (guideObserver.State())
    {
    case STATE::NONE:
        NoneRendering();
        break;

    case STATE::RSP:
        RSPRendering();
        break;

    case STATE::PH:
        PHRendering();
        break;

    case STATE::DB:
        DBRendering();
        break;
    }
    TechSharkLib::Project(description.defaultCamera, description.lightDirection);
    TechSharkLib::SetDepthState(TechSharkLib::DEPTH_STATE::TEST_AND_WRITE);
}

void OperateGuide::NoneRendering()
{
    // ���{�^��
    AllowButtonRendering(DIRECTION::LEFT,   false);
    AllowButtonRendering(DIRECTION::UP,     false);
    AllowButtonRendering(DIRECTION::RIGHT,  false);
    AllowButtonRendering(DIRECTION::DOWN,   false);
}
void OperateGuide::RSPRendering()
{
    // ���{�^��
    AllowButtonRendering(DIRECTION::LEFT,   true);
    AllowButtonRendering(DIRECTION::UP,     true);
    AllowButtonRendering(DIRECTION::RIGHT,  true);
    AllowButtonRendering(DIRECTION::DOWN,   false);

}
void OperateGuide::PHRendering()
{
    // ���{�^��
    AllowButtonRendering(DIRECTION::LEFT,   true);
    AllowButtonRendering(DIRECTION::UP,     false);
    AllowButtonRendering(DIRECTION::RIGHT,  true);
    AllowButtonRendering(DIRECTION::DOWN,   false);
}
void OperateGuide::DBRendering()
{
    // ���{�^��
    AllowButtonRendering(DIRECTION::LEFT,   true);
    AllowButtonRendering(DIRECTION::UP,     true);
    AllowButtonRendering(DIRECTION::RIGHT,  true);
    AllowButtonRendering(DIRECTION::DOWN,   true);
}
void OperateGuide::AllowButtonRendering(DIRECTION direction, bool isActive)
{
    int index = static_cast<int>(direction);
    _ASSERT_EXPR(index != static_cast<int>(DIRECTION::NONE), L"index���͈͊O");

    TechSharkLib::Float3 position = description.relativePositions[index] + transform->Position();
    DirectX::XMFLOAT4X4 local = util::CalcTransform(
        description.scales[index],
        description.buttonRotations[index],
        position
    );
    DirectX::XMFLOAT4 color = {};
    if (isActive)
    {
        color = (index != currentLean) ?
            config::guide::ACTIVE_COLOR :
            config::guide::SELECT_COLOR;
    }
    else
    {
        color = config::guide::DISABLE_COLOR;
    }
    TechSharkLib::Render(OperateGuide::meshes.at(MESH::ALLOW), local, color);
}

void OperateGuide::LoadMeshes()
{
    meshes.clear();
    meshes.emplace(MESH::STICK, TechSharkLib::LoadStaticMesh(L"Data/Models/Stick_1/Stick_1.obj", true));
    meshes.emplace(MESH::ALLOW, TechSharkLib::LoadStaticMesh(L"Data/Models/Arrow_button/Arrow_button.obj", true));
    meshes.emplace(MESH::LEAN,  TechSharkLib::LoadStaticMesh(L"Data/Models/Stick_2/Stick_2.obj", true));
}
void OperateGuide::ReleaseMeshes()
{
    for (auto& mesh : meshes)
    {
        TechSharkLib::Release(mesh.second);
    }
}

//------------------------------------------------------------------------------
// instance
//------------------------------------------------------------------------------

TSL_IMPLEMENT_COMPONENT(OperateGuide, "OperateGuide");
std::map<OperateGuide::MESH, TechSharkLib::StaticMeshID> OperateGuide::meshes;