#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Component.h"
#include <string>
#include "../TechSharkLib/Inc/Transform3D.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"
#include <vector>

//========================================================================================
// 
//      Obj3DDebuggerDesc
// 
//========================================================================================
struct Obj3DDebuggerDesc
{
    std::string name;
};

//========================================================================================
// 
//      Obj3DDebugger
// 
//========================================================================================
class Obj3DDebugger : public TechSharkLib::Component
{
TSL_DEFINE_COMPONENT(Obj3DDebugger);
private:
    TechSharkLib::Transform3D*          transform;
    TechSharkLib::StaticMeshRenderer*   renderer;

    std::string name;

    Obj3DDebuggerDesc description;

public:
    Obj3DDebugger() = delete;
    Obj3DDebugger(const TechSharkLib::ComponentID& selfId, TechSharkLib::GameObject* owner, const Obj3DDebuggerDesc& desc) : 
        transform{nullptr}, renderer{nullptr},
        description{desc},
        TechSharkLib::Component{selfId, owner}
    {
    }
    ~Obj3DDebugger() override {}

    void Init() override;
    void Setup() override;
    void Update(float /*deltaTime*/) override;
    void Render(float /*scrollX*/, float /*scrollY*/) override {}
    void Deinit() override {}

};