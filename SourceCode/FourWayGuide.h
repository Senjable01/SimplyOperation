#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Component.h"
#include <string>
#include "../TechSharkLib/Inc/Vector.h"
#include "../TechSharkLib/Inc/Transform3D.h"
#include "../TechSharkLib/Inc/StaticMeshID.h"

//========================================================================================
// 
//      FourWayGuideDesc
// 
//========================================================================================
struct FourWayGuideDesc
{
    std::wstring stickObjPath;
    std::wstring allowObjPath;
    std::wstring leanStickObjPath;

    TechSharkLib::Float3 posBase;
    TechSharkLib::Float3 scaleBase;
    TechSharkLib::Float3 rotationBase;

    TechSharkLib::Float3 relativePosLeft;
    TechSharkLib::Float3 scaleLeft;
    TechSharkLib::Float3 rotationLeft;

    TechSharkLib::Float3 relativePosRight;
    TechSharkLib::Float3 scaleRight;
    TechSharkLib::Float3 rotationRight;

    TechSharkLib::Float3 relativePosUp;
    TechSharkLib::Float3 scaleUp;
    TechSharkLib::Float3 rotationUp;

    TechSharkLib::Float3 relativePosDown;
    TechSharkLib::Float3 scaleDown;
    TechSharkLib::Float3 rotationDown;

    TechSharkLib::Float3 stickLeanLeftRotation;
    TechSharkLib::Float3 stickLeanRightRotation;
    TechSharkLib::Float3 stickLeanUpRotation;
    TechSharkLib::Float3 stickLeanDownRotation;
};

//========================================================================================
// 
//      FourWayGuide
// 
//========================================================================================
class FourWayGuide : public TechSharkLib::Component
{
TSL_DEFINE_COMPONENT(FourWayGuide);
private:
    TechSharkLib::Transform3D* transform;

    enum DIRECTION : int { LEFT, RIGHT, UP, DOWN, NORMAl, NUM };
    enum MESH_TYPE : int { STICK, ALLOW, LEAN, VALUE };
    TechSharkLib::StaticMeshID meshIds[MESH_TYPE::VALUE];
    int currentLean;
    float timer;
    TechSharkLib::StaticMeshID meshes[DIRECTION::NUM];
    TechSharkLib::Float3 positions[DIRECTION::NUM];
    TechSharkLib::Float3 scales[DIRECTION::NUM];
    TechSharkLib::Float3 rotations[DIRECTION::NUM];
    TechSharkLib::Float3 leanStickRotations[DIRECTION::NUM - 1];

    FourWayGuideDesc description;

    DirectX::XMFLOAT4X4 CalcTransform(int stick);

public:
    FourWayGuide() = delete;
    FourWayGuide(const TechSharkLib::ComponentID& selfId, TechSharkLib::GameObject* owner, const FourWayGuideDesc& desc) : 
        transform{nullptr},
        meshes{}, positions{}, scales{}, rotations{}, leanStickRotations{}, meshIds{}, currentLean{DIRECTION::NORMAl}, timer{0.0f},
        description{desc},
        TechSharkLib::Component{selfId, owner}
    {
    }

    void Init() override;
    void Setup() override;
    void Update(float deltaTime) override;
    void Render(float, float) override;
    void Deinit() override;

};