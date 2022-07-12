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
    bool isSecondEntrant;
};

//========================================================================================
// 
//      ENTRANT_HAND
// 
//========================================================================================
enum class ENTRANT_HAND {
    ROCK = 0, SCISSORS, PAPER,
    FINGER_1P, FINGER_2P,
    VALUE,
    HAND_VALUE = 3,
    NONE = -1
};

//========================================================================================
// 
//      Entrant
// 
//========================================================================================
class Entrant : public TechSharkLib::Component
{
TSL_DEFINE_COMPONENT(Entrant);
public:
    enum DIRECTION : int {LEFT, UP, RIGHT, DOWN, DIRECTION_NUM, NONE = -1};

private:
    TechSharkLib::Transform3D* transform;

    struct KeyBind {
        int keyLeft     = NULL;
        int keyRight    = NULL;
        int keyUp       = NULL;
        int keyDown     = NULL;
    } keyBind;
    bool activeKey;

    static std::array<TechSharkLib::StaticMeshID, static_cast<size_t>(ENTRANT_HAND::VALUE)> meshes;
    int meshNo;
    enum TYPE : int {PC = 0, NPC, VALUE};
    static std::array<TechSharkLib::StaticMeshID, static_cast<size_t>(TYPE::VALUE)> heads;
    bool isSecondEntrant;

    DirectX::XMFLOAT3 rotations[DIRECTION::DIRECTION_NUM];
    int direction;

    EntrantDesc description;

public:
    Entrant() = delete;
    Entrant(const TechSharkLib::ComponentID& selfId, TechSharkLib::GameObject* owner, const EntrantDesc& desc) : 
        transform{nullptr},
        keyBind{}, activeKey{false},
        meshNo{static_cast<int>(ENTRANT_HAND::NONE)},
        isSecondEntrant{false},
        rotations{}, direction{DIRECTION::NONE},
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
    int KeyInput();
    bool IsActiveKey() const noexcept { return activeKey; }
    const KeyBind* GetKeyBind() const { return &keyBind; }

    void SetMeshNo(ENTRANT_HAND hand);
    void SetDirection(int direction) { this->direction = direction; }

    static void LoadMeshes();
    static void UnloadMeshes();

};