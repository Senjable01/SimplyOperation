//------< include >-----------------------------------------------------------------------
#include "Entrant.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"
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
    using TechSharkLib::Transform3D;
    using TechSharkLib::StaticMeshRenderer;

    transform = GetOwnerRef()->SearchComponent<Transform3D>();
    _ASSERT_EXPR(transform != nullptr, L"Transform3Dコンポーネントの検索に失敗");
    StaticMeshRenderer* renderer = GetOwnerRef()->SearchComponent<StaticMeshRenderer>();
    _ASSERT_EXPR(renderer == nullptr, L"StaticMeshRendererコンポーネントを取り除いてください。");

}
void Entrant::Setup()
{
    if (description.activeKey)
    {
        keyBind.keyLeft     = (1 << description.keyLeft);
        keyBind.keyRight    = (1 << description.keyRight);
        keyBind.keyUp       = (1 << description.keyUp);
        keyBind.keyDown     = (1 << description.keyDown);
    }
    activekey = description.activeKey;
    meshNo = static_cast<int>(ENTRANT_HAND::NONE);
}
void Entrant::Render(float, float)
{
    if (transform == nullptr) return;
    if (meshNo == static_cast<int>(ENTRANT_HAND::NONE)) return;
    if (meshNo == static_cast<int>(ENTRANT_HAND::VALUE)) return;

    const DirectX::XMFLOAT4X4 local = transform->Transform();
    TechSharkLib::Render(meshes.at(meshNo), local, {1.0f, 1.0f, 1.0f, 1.0f});

}
void Entrant::Deinit()
{
    description = {};
    keyBind     = {};
    meshNo      = static_cast<int>(ENTRANT_HAND::NONE);
}

int Entrant::KeyInputSingle()
{
    if (activekey)
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

    return -1;

}

void Entrant::SetMeshNo(ENTRANT_HAND hand)
{
    _ASSERT_EXPR(hand != ENTRANT_HAND::VALUE, L"handの数値が不適切");
    meshNo = static_cast<int>(hand);
}

void Entrant::LoadMeshes()
{
    meshes.at(static_cast<size_t>(ENTRANT_HAND::ROCK))      = TechSharkLib::LoadStaticMesh(L"./Data/三角化仮素材_グー/puroto_guu.obj", true);
    meshes.at(static_cast<size_t>(ENTRANT_HAND::SCISSORS))  = TechSharkLib::LoadStaticMesh(L"./Data/三角化仮素材_チョキ/puroto_choki.obj", true);
    meshes.at(static_cast<size_t>(ENTRANT_HAND::PAPER))     = TechSharkLib::LoadStaticMesh(L"./Data/三角化仮素材_パー/puroto_paa.obj", true);
}

void Entrant::UnloadMeshes()
{
    for (auto& mesh : meshes)
    {
        TechSharkLib::Release(mesh);
    }
}

//------------------------------------------------------------------------------
// instance
//------------------------------------------------------------------------------

std::array<TechSharkLib::StaticMeshID, static_cast<size_t>(ENTRANT_HAND::VALUE)> Entrant::meshes;

TSL_IMPLEMENT_COMPONENT(Entrant, "Entrant");