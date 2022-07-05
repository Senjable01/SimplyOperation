#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Component.h"
#include "../TechSharkLib/Inc/KeyAssign.h"
#include "../TechSharkLib/Inc/Transform3D.h"
#include <array>
#include "../TechSharkLib/Inc/StaticMeshID.h"

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
    bool activeKey;
};

//========================================================================================
// 
//      ENTRANT_HAND
// 
//========================================================================================
enum class ENTRANT_HAND {
    ROCK = 0, SCISSORS, PAPER, VALUE, NONE = -1
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
    TechSharkLib::Transform3D* transform;

    struct KeyBind {
        int keyLeft     = NULL;
        int keyRight    = NULL;
        int keyUp       = NULL;
        int keyDown     = NULL;
    } keyBind;
    bool activekey;

    static std::array<TechSharkLib::StaticMeshID, static_cast<size_t>(ENTRANT_HAND::VALUE)> meshes;
    int meshNo;

    EntrantDesc description;

public:
    Entrant() = delete;
    Entrant(const TechSharkLib::ComponentID& selfId, TechSharkLib::GameObject* owner, const EntrantDesc& desc) : 
        transform{nullptr},
        keyBind{}, activekey{false},
        meshNo{static_cast<size_t>(ENTRANT_HAND::NONE)},
        description{desc},
        TechSharkLib::Component{selfId, owner}
    {
    }
    ~Entrant() override {}

    void Init() override;
    void Setup() override;
    void Update(float /*deltaTime*/) override {}
    void Render(float /*scrollX*/, float /*scrollY*/) override;
    void Deinit() override;

    int KeyInputSingle();
    const KeyBind* GetKeyBind() const { return &keyBind; }

    void SetMeshNo(ENTRANT_HAND hand);

    static void LoadMeshes();
    static void UnloadMeshes();

};