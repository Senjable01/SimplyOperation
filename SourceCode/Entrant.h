#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Component.h"

//------< class >-------------------------------------------------------------------------

class RockScissorsPaper;

//========================================================================================
// 
//      EntrantDesc
// 
//========================================================================================
enum class ENTRANT_TYPE {
    PLAYER = 0,
    NPC
};

//========================================================================================
// 
//      EntrantDesc
// 
//========================================================================================
struct EntrantDesc
{
    ENTRANT_TYPE type;
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
    enum class HAND {
        ROCK        = (1 << 0),
        SCISSORS    = (1 << 1),
        PAPER       = (1 << 2)
    };

    ENTRANT_TYPE    type;
    int             hand;

    EntrantDesc     description;

    void Init() override {};
    void Setup() override;
    void Update(float) override;
    void Render(float, float) override {}
    void Deinit() override;

public:
    Entrant() = delete;
    Entrant(
        const TechSharkLib::ComponentID& selfId, TechSharkLib::GameObject* owner,
        const EntrantDesc& desc
    ) : 
        type{}, hand{0}, description{desc},
        TechSharkLib::Component{selfId, owner}
    {
    }
    ~Entrant() override {}

    // グー/チョキ/パー/(None)を出す。制限時間内ならばgameRuleが呼び出す。
    int Shoot();
    int Push();

};