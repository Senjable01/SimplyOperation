//------< include >-----------------------------------------------------------------------
#include "Entrant.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"

//========================================================================================
// 
//      Entrant
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void Entrant::Init()
{
    transform = GetOwnerRef()->SearchComponent<TechSharkLib::Transform3D>();
    _ASSERT_EXPR(transform != nullptr, L"Transform3Dコンポーネントの検索に失敗");
    renderer = GetOwnerRef()->SearchComponent<TechSharkLib::StaticMeshRenderer>();
    _ASSERT_EXPR(renderer != nullptr, L"StaticMeshRendererコンポーネントの検索に失敗");
}
void Entrant::Setup()
{
    firstPosition   = transform->Position();
    typeFlags       = description.typeFlags;
    keyBind         = {};
    if (IsNPC() == false)
    {
        keyBind.left    = (1 << description.keyLeft->bitNo);
        keyBind.right   = (1 << description.keyRight->bitNo);
        keyBind.up      = (1 << description.keyUp->bitNo);
        keyBind.down    = (1 << description.keyDown->bitNo);
    }
    onlyPushedKey   = NULL;
    state           = STATE::NONE;
    renderer->SetRenderablity(false);
}
void Entrant::Update(float /*deltaTime*/)
{
    onlyPushedKey = NULL;
    if (IsNPC()) return;

    auto OnlyKeyDown = [trigger = TechSharkLib::keyTrigger(0)](const int key) -> bool {
        return (trigger ^ key) == false;
    };
    if (OnlyKeyDown(keyBind.left))
    {
        onlyPushedKey = keyBind.left;
    }
    else if (OnlyKeyDown(keyBind.right))
    {
        onlyPushedKey = keyBind.right;
    }
    else if (OnlyKeyDown(keyBind.up))
    {
        onlyPushedKey = keyBind.up;
    }
    else if (OnlyKeyDown(keyBind.down))
    {
        onlyPushedKey = keyBind.down;
    }
}

void Entrant::SetMesh(STATE state)
{
    _ASSERT_EXPR(state != STATE::STATE_NUM, L"stateの値が不適切");
    this->state = state;
    if (state == STATE::NONE)
    {
        renderer->SetRenderablity(false);
    }
    else
    {
        namespace hand      = config::model::hand;
        namespace finger    = config::model::finger;
        switch (state)
        {
        case STATE::ROCK:
            transform->SetScale(hand::SCALE);
            transform->SetRotation(IsNPC() ? hand::ROTATE_BACK : hand::ROTATE_FRONT);
            renderer->SetMeshID(Entrant::meshes.at(static_cast<size_t>(IsSecondPlayer() ? MESH::ROCK_2P : MESH::ROCK_1P)));
            break;

        case STATE::SCISSORS:
            transform->SetScale(hand::SCALE);
            transform->SetRotation(IsNPC() ? hand::ROTATE_BACK : hand::ROTATE_FRONT);
            renderer->SetMeshID(Entrant::meshes.at(static_cast<size_t>(IsSecondPlayer() ? MESH::SCISSORS_2P : MESH::SCISSORS_1P)));
            break;

        case STATE::PAPER:
            transform->SetScale(hand::SCALE);
            transform->SetRotation(IsNPC() ? hand::ROTATE_BACK : hand::ROTATE_FRONT);
            renderer->SetMeshID(Entrant::meshes.at(static_cast<size_t>(IsSecondPlayer() ? MESH::PAPER_2P : MESH::PAPER_1P)));
            break;

        case STATE::UP:
            transform->SetScale(finger::SCALE);
            transform->SetRotation(IsNPC() ? finger::ROTATE_UP_BACK : finger::ROTATE_UP_FRONT);
            renderer->SetMeshID(Entrant::meshes.at(static_cast<size_t>(IsSecondPlayer() ? MESH::FINGER_2P : MESH::FINGER_1P)));
            break;

        case STATE::RIGHT:
            transform->SetScale(finger::SCALE);
            transform->SetRotation(IsNPC() ? finger::ROTATE_LEFT_BACK /*左右反転*/ : finger::ROTATE_RIGHT_FRONT);
            renderer->SetMeshID(Entrant::meshes.at(static_cast<size_t>(IsSecondPlayer() ? MESH::FINGER_2P : MESH::FINGER_1P)));
            break;

        case STATE::DOWN:
            transform->SetScale(finger::SCALE);
            transform->SetRotation(IsNPC() ? finger::ROTATE_DOWN_BACK : finger::ROTATE_DOWN_FRONT);
            renderer->SetMeshID(Entrant::meshes.at(static_cast<size_t>(IsSecondPlayer() ? MESH::FINGER_2P : MESH::FINGER_1P)));
            break;

        case STATE::LEFT:
            transform->SetScale(finger::SCALE);
            transform->SetRotation(IsNPC() ? finger::ROTATE_RIGHT_BACK /*左右反転*/ : finger::ROTATE_LEFT_FRONT);
            renderer->SetMeshID(Entrant::meshes.at(static_cast<size_t>(IsSecondPlayer() ? MESH::FINGER_2P : MESH::FINGER_1P)));
            break;

        }
        renderer->SetRenderablity(true);
    }
}

void Entrant::LoadMeshes()
{
    meshes.at(static_cast<size_t>(MESH::ROCK_1P))       = TechSharkLib::LoadStaticMesh(L"./Data/Models/Hand_guu_A/Hand_guu_A.obj", true);
    meshes.at(static_cast<size_t>(MESH::ROCK_2P))       = TechSharkLib::LoadStaticMesh(L"./Data/Models/Hand_guu_B/Hand_guu_B.obj", true);
    meshes.at(static_cast<size_t>(MESH::SCISSORS_1P))   = TechSharkLib::LoadStaticMesh(L"./Data/Models/Hand_choki_A/Hand_choki_A.obj", true);
    meshes.at(static_cast<size_t>(MESH::SCISSORS_2P))   = TechSharkLib::LoadStaticMesh(L"./Data/Models/Hand_choki_B/Hand_choki_B.obj", true);
    meshes.at(static_cast<size_t>(MESH::PAPER_1P))      = TechSharkLib::LoadStaticMesh(L"./Data/Models/Hand_paa_A/Hand_paa_A.obj", true);
    meshes.at(static_cast<size_t>(MESH::PAPER_2P))      = TechSharkLib::LoadStaticMesh(L"./Data/Models/Hand_paa_B/Hand_paa_B.obj", true);
    meshes.at(static_cast<size_t>(MESH::FINGER_1P))     = TechSharkLib::LoadStaticMesh(L"./Data/Models/Hand_yubisasi_A/Hand_yubisasi_A.obj", true);
    meshes.at(static_cast<size_t>(MESH::FINGER_2P))     = TechSharkLib::LoadStaticMesh(L"./Data/Models/Hand_yubisasi_B/Hand_yubisasi_B.obj", true);
}
void Entrant::ReleaseMeshes()
{
    for (auto& mesh : meshes)
    {
        TechSharkLib::Release(mesh);
    }
}

//------------------------------------------------------------------------------
// instance
//------------------------------------------------------------------------------

TSL_IMPLEMENT_COMPONENT(Entrant, "Entrant");
std::array<TechSharkLib::StaticMeshID, static_cast<size_t>(Entrant::MESH::NUM)> Entrant::meshes;