//------< include >-----------------------------------------------------------------------
#include "Entrant.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"

//------< using >-------------------------------------------------------------------------

using TechSharkLib::StaticMeshID;

//========================================================================================
// 
//      Entrant
// 
//========================================================================================

//------------------------------------------------------------------------------
// member fuctions
//------------------------------------------------------------------------------

void Entrant::Initialize(const std::array<std::pair<int, std::wstring>, 4>& objFilePathes)
{
    for (auto& objFile : objFilePathes)
    {
        StaticMeshID id = TechSharkLib::LoadStaticMesh(objFile.second.c_str(), true);
        Entrant::meshIdMap.emplace(objFile.first, id);
    }
    _ASSERT_EXPR(Entrant::meshIdMap.size() == objFilePathes.size(), L"ロードしたOBJファイルの数が不足");
}

void Entrant::Init()
{
    transform = GetOwnerRef()->SearchComponent<TechSharkLib::Transform3D>();
    _ASSERT_EXPR(transform != nullptr, L"Transform3Dコンポーネントは未発見");
    using TechSharkLib::StaticMeshRenderer;
    StaticMeshRenderer* renderer = GetOwnerRef()->SearchComponent<StaticMeshRenderer>();
    _ASSERT_EXPR(renderer == nullptr, L"StaticMeshRendererコンポーネントは不要");
}

void Entrant::Setup()
{
    keyLeft         = description.keyLeft;
    keyRight        = description.keyRight;
    keyUp           = description.keyUp;
    keyDown         = description.keyDown;
    activeLeftStick = description.activeLeftStick;
    leftStickLeft   = description.leftStickLeft;
    leftStickRight  = description.leftStickRight;
    leftStickUp     = description.leftStickUp;
    leftStickDown   = description.leftStickDown;
}

void Entrant::Update(float)
{
    direction = 0;
    const int keyTrigger = TechSharkLib::keyTrigger(0);
    if (activeLeftStick)
    {
        //TODO:ジョイスティック操作
    }
    else if (!(keyTrigger ^ keyLeft))
        direction = DIRECTION_LEFT;
    else if (!(keyTrigger ^ keyRight))
        direction = DIRECTION_RIGHT;
    else if (!(keyTrigger ^ keyUp))
        direction = DIRECTION_UP;
    else if (!(keyTrigger ^ keyDown))
        direction = DIRECTION_DOWN;

}

void Entrant::Render(float, float)
{
    if (transform == nullptr) return;
    if (meshNo == DIRECTION_NONE) return;

    const DirectX::XMFLOAT4X4 local = transform->Transform();
    TechSharkLib::Render(Entrant::meshIdMap.at(meshNo), local, {1.0f, 1.0f, 1.0f, 1.0f});
}

void Entrant::Deinit()
{
    keyLeft         = 0;
    keyRight        = 0;
    keyUp           = 0;
    keyDown         = 0;
    activeLeftStick = false;
    leftStickLeft   = TechSharkLib::Float2{};
    leftStickRight  = TechSharkLib::Float2{};
    leftStickUp     = TechSharkLib::Float2{};
    leftStickDown   = TechSharkLib::Float2{};
    direction      = 0;
    meshNo          = DIRECTION_NONE;
    description     = {};
}

void Entrant::SetMesh(int meshNo)
{
    _ASSERT_EXPR(DIRECTION_NONE < meshNo, L"meshNoが不適切");
    _ASSERT_EXPR(meshNo <= DIRECTION_DOWN, L"meshNoが不適切");
    this->meshNo = meshNo;
}

void Entrant::Finalize()
{
    for (auto& meshId : Entrant::meshIdMap)
    {
        TechSharkLib::Release(meshId.second);
    }
    Entrant::meshIdMap.clear();
}