#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Component.h"
#include "../TechSharkLib/Inc/KeyAssign.h"

//========================================================================================
// 
//      EntrantDesc
// 
//========================================================================================
struct EntrantDesc
{
    TechSharkLib::BIT_NO keyLeft;
    TechSharkLib::BIT_NO keyRight;
    TechSharkLib::BIT_NO keyUp;
    TechSharkLib::BIT_NO keyDown;
};

//========================================================================================
// 
//      Entrant
// 
//========================================================================================
class Entrant : public TechSharkLib::Component
{
TSL_DEFINE_COMPONENT(Entrant);
private:
    EntrantDesc description;

    int keyLeft;
    int keyRight;
    int keyUp;
    int keyDown;

public:
    Entrant() = delete;
    Entrant(const TechSharkLib::ComponentID& selfId, TechSharkLib::GameObject* owner, const EntrantDesc& desc) : 
        keyLeft{NULL}, keyRight{NULL}, keyUp{NULL}, keyDown{NULL},
        description{desc},
        TechSharkLib::Component{selfId, owner}
    {
    }
    ~Entrant() override {}

    void Init() override {}
    void Setup() override;
    void Update(float /*deltaTime*/) override {}
    void Render(float /*scrollX*/, float /*scrollY*/) override {}
    void Deinit() override;

    int KeyInput();

};