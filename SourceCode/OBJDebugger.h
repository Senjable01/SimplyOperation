#ifndef INCLUDED_OBJ_DEBUGGER_H
#define INCLUDED_OBJ_DEBUGGER_H

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Component.h"
#include "../TechSharkLib/Inc/Transform3D.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"
#include <string>

//========================================================================================
// 
//      OBJDebuggerDesc
// 
//========================================================================================
struct OBJDebuggerDesc
{
    std::string debugName;
};

//========================================================================================
// 
//      OBJDebugger
// 
//========================================================================================
class OBJDebugger : public TechSharkLib::Component
{
TSL_DEFINE_COMPONENT(OBJDebugger);
private:
    TechSharkLib::Transform3D*          transform;
    TechSharkLib::StaticMeshRenderer*   renderer;

    std::string debugName;

    OBJDebuggerDesc description;

public:
    OBJDebugger() = delete;
    OBJDebugger(const TechSharkLib::ComponentID& selfId, TechSharkLib::GameObject* owner, const OBJDebuggerDesc& desc) : 
        transform{nullptr}, renderer{nullptr},
        debugName{},
        description{desc},
        TechSharkLib::Component{selfId, owner}
    {
    }
    ~OBJDebugger() override {}

    void Init() override;
    void Setup() override;
    void Update(float /*deltaTime*/) override;
    void Render(float /*scrollX*/, float /*scrollY*/) override {}
    void Deinit() {}

    void DrawDebugGUI() override;

};

#endif // !INCLUDED_OBJ_DEBUGGER_H