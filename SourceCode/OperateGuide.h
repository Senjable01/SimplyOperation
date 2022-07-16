#ifndef INCLUDED_OPERATE_GUIDE_H
#define INCLUDED_OPERATE_GUIDE_H

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/StaticMeshID.h"
#include "../TechSharkLib/Inc/Vector.h"
#include "../TechSharkLib/Inc/Camera.h"
#include "Config.h"
#include "../TechSharkLib/Inc/Component.h"
#include "../TechSharkLib/Inc/Transform3D.h"
#include "Observer.h"
#include <map>

//========================================================================================
// 
//      OperateGuideDesc
// 
//========================================================================================
struct OperateGuideDesc
{
    TechSharkLib::Float3 relativePositions[static_cast<size_t>(config::guide::DIRECTION::WAY4)];
    TechSharkLib::Float3 scales[static_cast<size_t>(config::guide::DIRECTION::WAY4)];
    TechSharkLib::Float3 buttonRotations[static_cast<size_t>(config::guide::DIRECTION::WAY4)];
    TechSharkLib::Float3 stickRotations[static_cast<size_t>(config::guide::DIRECTION::WAY4)];

    TechSharkLib::Camera*   defaultCamera;
    TechSharkLib::Float4    lightDirection;
};

//========================================================================================
// 
//      GuideState
// 
//========================================================================================
class GuideObserver : public Observer<config::guide::STATE>
{
private:
    using STATE = config::guide::STATE;
    STATE state;

public:
    GuideObserver() : state{STATE::NONE}, Observer<STATE>{} {}

    void OnNotify(const STATE& report) override { state = report; }
    STATE State() const noexcept { return state; }

};

//========================================================================================
// 
//      OperateGuide
// 
//========================================================================================
class OperateGuide : public TechSharkLib::Component
{
TSL_DEFINE_COMPONENT(OperateGuide);
public:
    using STATE     = config::guide::STATE;

private:
    using DIRECTION = config::guide::DIRECTION;
    using MESH      = config::guide::MESH;

    TechSharkLib::Transform3D* transform;

    int             currentLean;
    STATE           currentState;
    GuideObserver   guideObserver;
    float           timerSec;

    TechSharkLib::Camera camera;

    OperateGuideDesc description;

    void NoneRendering();
    void RSPRendering();
    void PHRendering();
    void DBRendering();
    void AllowButtonRendering(DIRECTION direction, bool isActive);
    void RockRendering();
    void ScissorsRendering();
    void PaperRendering();

    static std::map<MESH, TechSharkLib::StaticMeshID>   meshes;

public:
    OperateGuide() = delete;
    OperateGuide(const TechSharkLib::ComponentID& selfId, TechSharkLib::GameObject* owner, const OperateGuideDesc& desc) : 
        transform{nullptr},
        currentLean{static_cast<int>(DIRECTION::NONE)},
        currentState{STATE::NONE}, guideObserver{},
        timerSec{0.0f},
        camera{},
        description{desc},
        TechSharkLib::Component{selfId, owner}
    {
    }

    void Init() override;
    void Setup() override;
    void Update(float deltaTime) override;
    void Render(float /*scrollX*/, float /*scrollY*/) override;
    void Deinit() override {}

    void DrawDebugGUI() override {}

    GuideObserver* GetGuideObserverRef() { return &guideObserver; }

    static void LoadMeshes();
    static void ReleaseMeshes();
};

#endif // !INCLUDED_OPERATE_GUIDE_H