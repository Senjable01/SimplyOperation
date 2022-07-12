//------< include >-----------------------------------------------------------------------
#include "FourWayGuide.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "Utility.h"

//========================================================================================
// 
//      ControllerGuide
// 
//========================================================================================

//------------------------------------------------------------------------------
// constructor
//------------------------------------------------------------------------------

void FourWayGuide::Init()
{
    using TechSharkLib::Transform3D;
    using TechSharkLib::StaticMeshRenderer;

    transform = GetOwnerRef()->SearchComponent<Transform3D>();
    _ASSERT_EXPR(transform != nullptr, L"Transform3Dコンポーネントの検索に失敗");
    StaticMeshRenderer* renderer = GetOwnerRef()->SearchComponent<StaticMeshRenderer>();
    _ASSERT_EXPR(renderer == nullptr, L"StaticMeshRendererコンポーネントを取り除いてください。");

    meshIds[MESH_TYPE::STICK]   = TechSharkLib::LoadStaticMesh(description.stickObjPath.c_str(), true);
    meshIds[MESH_TYPE::ALLOW]   = TechSharkLib::LoadStaticMesh(description.allowObjPath.c_str(), true);
    meshIds[MESH_TYPE::LEAN]    = TechSharkLib::LoadStaticMesh(description.leanStickObjPath.c_str(), true);

}
void FourWayGuide::Setup()
{
    positions[DIRECTION::NORMAl]    = description.posBase;
    positions[DIRECTION::LEFT]      = positions[DIRECTION::NORMAl] + description.relativePosLeft;
    positions[DIRECTION::RIGHT]     = positions[DIRECTION::NORMAl] + description.relativePosRight;
    positions[DIRECTION::UP]        = positions[DIRECTION::NORMAl] + description.relativePosUp;
    positions[DIRECTION::DOWN]      = positions[DIRECTION::NORMAl] + description.relativePosDown;
    scales[DIRECTION::NORMAl]       = description.scaleBase;
    scales[DIRECTION::LEFT]         = description.scaleLeft;
    scales[DIRECTION::RIGHT]        = description.scaleRight;
    scales[DIRECTION::UP]           = description.scaleUp;
    scales[DIRECTION::DOWN]         = description.scaleDown;
    rotations[DIRECTION::NORMAl]    = description.rotationBase;
    rotations[DIRECTION::LEFT]      = description.rotationLeft;
    rotations[DIRECTION::RIGHT]     = description.rotationRight;
    rotations[DIRECTION::UP]        = description.rotationUp;
    rotations[DIRECTION::DOWN]      = description.rotationDown;

    leanStickRotations[DIRECTION::LEFT]     = description.stickLeanLeftRotation;
    leanStickRotations[DIRECTION::RIGHT]    = description.stickLeanRightRotation;
    leanStickRotations[DIRECTION::UP]       = description.stickLeanUpRotation;
    leanStickRotations[DIRECTION::DOWN]     = description.stickLeanDownRotation;

    currentLean = DIRECTION::NORMAl;

    transform->SetPosition(positions[DIRECTION::NORMAl]);
}
void FourWayGuide::Update(float deltaTime)
{
    timer += deltaTime;
    currentLean = static_cast<int>(timer / 1.0f) % DIRECTION::NUM;
}
void FourWayGuide::Render(float /*scrollX*/, float /*scrollY*/)
{
    {
        DirectX::XMFLOAT4X4 transform = util::CalcTransform(
            scales[DIRECTION::NORMAl], rotations[currentLean], positions[DIRECTION::NORMAl]
        );
        if (currentLean == DIRECTION::NORMAl)
        {
            TechSharkLib::Render(meshIds[MESH_TYPE::STICK], transform, { 1.0f, 1.0f, 1.0f, 1.0f });
        }
        else
        {
            TechSharkLib::Render(meshIds[MESH_TYPE::LEAN], transform, { 1.0f, 1.0f, 1.0f, 1.0f });
        }
    }

    for (int i = 0; i < DIRECTION::NUM - 1; i++)
    {
        DirectX::XMFLOAT4X4 transform = CalcTransform(i);
        TechSharkLib::Render(meshIds[MESH_TYPE::ALLOW], transform, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
}
void FourWayGuide::Deinit()
{
    for (int i = 0; i < DIRECTION::NUM; i++)
    {
        TechSharkLib::Release(meshes[i]);
    }
}

DirectX::XMFLOAT4X4 FourWayGuide::CalcTransform(int stick)
{
    DirectX::XMMATRIX mtrixScale    = DirectX::XMMatrixScaling(scales[stick].x, scales[stick].y, scales[stick].z);
    DirectX::XMMATRIX mtrixRotation = DirectX::XMMatrixRotationRollPitchYaw(rotations[stick].x, rotations[stick].y, rotations[stick].z);
    DirectX::XMMATRIX mtrixPosition = DirectX::XMMatrixTranslation(positions[stick].x, positions[stick].y, positions[stick].z);
    DirectX::XMFLOAT4X4 transform = {};
    DirectX::XMStoreFloat4x4(&transform, mtrixScale * mtrixRotation * mtrixPosition);
    return transform;
}

//------------------------------------------------------------------------------
// instance
//------------------------------------------------------------------------------

TSL_IMPLEMENT_COMPONENT(FourWayGuide, "ControllerGuide");