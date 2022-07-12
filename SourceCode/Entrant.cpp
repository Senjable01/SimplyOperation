//------< include >-----------------------------------------------------------------------
#include "Entrant.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "Utility.h"

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
    using TechSharkLib::Transform3D;
    using TechSharkLib::StaticMeshRenderer;

    transform = GetOwnerRef()->SearchComponent<Transform3D>();
    _ASSERT_EXPR(transform != nullptr, L"Transform3Dコンポーネントの検索に失敗");
    StaticMeshRenderer* renderer = GetOwnerRef()->SearchComponent<StaticMeshRenderer>();
    _ASSERT_EXPR(renderer == nullptr, L"StaticMeshRendererコンポーネントを取り除いてください。");

}
void Entrant::Setup()
{
    firstPosition = transform->Position();

    if (description.activeKey)
    {
        keyBind.keyLeft     = (1 << description.keyLeft);
        keyBind.keyRight    = (1 << description.keyRight);
        keyBind.keyUp       = (1 << description.keyUp);
        keyBind.keyDown     = (1 << description.keyDown);
    }
    activeKey       = description.activeKey;
    meshNo          = static_cast<int>(ENTRANT_HAND::NONE);
    isSecondEntrant = description.isSecondEntrant;

    rotations[UP] = { 0.0f, 0.0f, 0.0f };
    rotations[RIGHT] = { 0.0f, 0.0f, -DirectX::XM_PIDIV2 };
    rotations[DOWN] = { 0.0f, 0.0f, DirectX::XM_PI };
    rotations[LEFT] = { 0.0f, 0.0f, DirectX::XM_PIDIV2 };
}
void Entrant::Render(float, float)
{
    if (transform == nullptr) return;

    if (isSecondEntrant)
    {
        DirectX::XMFLOAT4X4 transform = util::CalcTransform(
            { 1.0f, 1.0f, 1.0f },
            { 0.0f, DirectX::XM_PI, 0.0f },
            { 0.0f, 0.0f, 2.0f }
        );
        TechSharkLib::Render(
            heads.at(static_cast<size_t>(activeKey ? TYPE::PC : TYPE::NPC)),
            transform, { 1.0f, 1.0f, 1.0f, 1.0f }
        );
    }

    if (meshNo == static_cast<int>(ENTRANT_HAND::NONE)) return;
    if (meshNo == static_cast<int>(ENTRANT_HAND::VALUE)) return;
    //if (meshNo == static_cast<int>(ENTRANT_HAND::HAND_VALUE)) return;

    if (meshNo == static_cast<int>(ENTRANT_HAND::FINGER_1P) || meshNo == static_cast<int>(ENTRANT_HAND::FINGER_2P))
    {
        DirectX::XMFLOAT4X4 local = {};
        if (isSecondEntrant)
        {
            DirectX::XMFLOAT3 rotation = {
                rotations[direction].x,
                rotations[direction].y + DirectX::XM_PI,
                rotations[direction].z + DirectX::XM_PI
            };
            local = util::CalcTransform(
                { 0.05f, 0.05f, 0.05f },
                rotation,
                transform->Position()
            );
        }
        else
        {
            local = util::CalcTransform(
                { 0.05f, 0.05f, 0.05f },
                rotations[direction],
                transform->Position()
            );
        }
        TechSharkLib::Render(meshes.at(meshNo), local, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    else
    {
        DirectX::XMFLOAT4X4 local = {};
        if (isSecondEntrant)
        {
            DirectX::XMFLOAT3 rotation =  transform->Rotation();
            rotation.y += DirectX::XM_PI;
            local = util::CalcTransform(
                transform->Scale(),
                rotation,
                transform->Position()
            );
        }
        else
        {
            local = transform->Transform();
        }
        //const DirectX::XMFLOAT4X4 local = transform->Transform();
        TechSharkLib::Render(meshes.at(meshNo), local, {1.0f, 1.0f, 1.0f, 1.0f});
    }

}
void Entrant::Deinit()
{
    description = {};
    keyBind     = {};
    meshNo      = static_cast<int>(ENTRANT_HAND::NONE);
}

int Entrant::KeyInputSingle()
{
    if (activeKey)
    {
        auto CheckTrigger = [inputTrigger = TechSharkLib::keyTrigger(0)](int key) -> bool {
            return !(inputTrigger ^ key);
        };

        if (CheckTrigger(keyBind.keyLeft))
            return keyBind.keyLeft;
        if (CheckTrigger(keyBind.keyRight))
            return keyBind.keyRight;
        if (CheckTrigger(keyBind.keyUp))
            return keyBind.keyUp;
        if (CheckTrigger(keyBind.keyDown))
            return keyBind.keyDown;
    }

    return NULL;
}

int Entrant::KeyInput()
{
    int trigger = NULL;

    if (activeKey)
    {
        auto CheckTrigger = [inputTrigger = TechSharkLib::keyTrigger(0)](int key, int* trigger) -> void {
            *trigger |= inputTrigger & key;
        };
        CheckTrigger(keyBind.keyLeft, &trigger);
        CheckTrigger(keyBind.keyRight, &trigger);
        CheckTrigger(keyBind.keyUp, &trigger);
        CheckTrigger(keyBind.keyDown, &trigger);
    }

    return trigger;
}

void Entrant::SetMeshNo(ENTRANT_HAND hand)
{
    _ASSERT_EXPR(hand != ENTRANT_HAND::VALUE, L"handの数値が不適切");
    meshNo = static_cast<int>(hand);
}

void Entrant::LoadMeshes()
{
    meshes.at(static_cast<size_t>(ENTRANT_HAND::ROCK))      = TechSharkLib::LoadStaticMesh(L"./Data/Models/puroto_guu/puroto_guu.obj", true);
    meshes.at(static_cast<size_t>(ENTRANT_HAND::SCISSORS))  = TechSharkLib::LoadStaticMesh(L"./Data/Models/puroto_choki/puroto_choki.obj", true);
    meshes.at(static_cast<size_t>(ENTRANT_HAND::PAPER))     = TechSharkLib::LoadStaticMesh(L"./Data/Models/puroto_paa/puroto_paa.obj", true);
    meshes.at(static_cast<size_t>(ENTRANT_HAND::FINGER_1P)) = TechSharkLib::LoadStaticMesh(L"./Data/Models/Hand_yubisasi_A/Hand_yubisasi_A.obj", true);
    meshes.at(static_cast<size_t>(ENTRANT_HAND::FINGER_2P)) = TechSharkLib::LoadStaticMesh(L"./Data/Models/Hand_yubisasi_B/Hand_yubisasi_B.obj", true);
    
    heads.at(static_cast<size_t>(Entrant::TYPE::PC))        = TechSharkLib::LoadStaticMesh(L"./Data/Models/Player_Face/Player_Face.obj", true);
    heads.at(static_cast<size_t>(Entrant::TYPE::NPC))       = TechSharkLib::LoadStaticMesh(L"./Data/Models/Enemy_Face/Enemy_Face.obj", true);
}

void Entrant::UnloadMeshes()
{
    for (auto& mesh : meshes)
    {
        TechSharkLib::Release(mesh);
    }
    for (auto& mesh : heads)
    {
        TechSharkLib::Release(mesh);
    }
}

//------------------------------------------------------------------------------
// instance
//------------------------------------------------------------------------------

std::array<TechSharkLib::StaticMeshID, static_cast<size_t>(ENTRANT_HAND::VALUE)> Entrant::meshes;
std::array<TechSharkLib::StaticMeshID, static_cast<size_t>(Entrant::TYPE::VALUE)> Entrant::heads;

TSL_IMPLEMENT_COMPONENT(Entrant, "Entrant");