#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Vector.h"
#include "../TechSharkLib/Inc/Component.h"
#include "../TechSharkLib/Inc/Transform3D.h"
#include <map>
#include "../TechSharkLib/Inc/StaticMeshID.h"
#include <array>
#include <utility>
#include <string>

//========================================================================================
// 
//      EntrantDesc
// 
//========================================================================================
struct EntrantDesc
{
    int keyLeft;
    int keyRight;
    int keyUp;
    int keyDown;
    bool activeLeftStick;
    TechSharkLib::Float2 leftStickLeft;
    TechSharkLib::Float2 leftStickRight;
    TechSharkLib::Float2 leftStickUp;
    TechSharkLib::Float2 leftStickDown;
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
    static constexpr int DIRECTION_NONE     = -1;
    static constexpr int DIRECTION_LEFT     = 0;
    static constexpr int DIRECTION_RIGHT    = 1;
    static constexpr int DIRECTION_UP       = 2;
    static constexpr int DIRECTION_DOWN     = 3;
private:
    TechSharkLib::Transform3D* transform;

    int keyLeft;
    int keyRight;
    int keyUp;
    int keyDown;
    bool activeLeftStick;
    TechSharkLib::Float2 leftStickLeft;
    TechSharkLib::Float2 leftStickRight;
    TechSharkLib::Float2 leftStickUp;
    TechSharkLib::Float2 leftStickDown;
    int direction;
    static std::map<int, TechSharkLib::StaticMeshID> meshIdMap;
    int meshNo;

    EntrantDesc description;

    void Init() override;
    void Setup() override;
    void Update(float /*deltaTime*/) override;
    void Render(float /*scrollX*/, float /*scrollY*/) override;
    void Deinit() override;

public:
    Entrant() = delete;
    Entrant(const TechSharkLib::ComponentID& selfId, TechSharkLib::GameObject* owner, const EntrantDesc& desc) : 
        transform{nullptr},
        keyLeft{0}, keyRight{0}, keyUp{0}, keyDown{0},
        activeLeftStick{false}, leftStickLeft{}, leftStickRight{}, leftStickUp{}, leftStickDown{},
        direction{0},
        meshNo{DIRECTION_NONE},
        description{desc},
        TechSharkLib::Component{selfId, owner}
    {
    }

    int Direction() const noexcept { return direction; }
    void SetMesh(int meshNo);

    static void Initialize(const std::array<std::pair<int, std::wstring>, 4>& objFilePathes);
    static void Finalize();
};