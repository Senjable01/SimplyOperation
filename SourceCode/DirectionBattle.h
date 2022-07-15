#ifndef INCLUDED_DIRECTION_BATTLE_H
#define INCLUDED_DIRECTION_BATTLE_H

//------< include >-----------------------------------------------------------------------
#include "GameMode.h"
#include <map>
#include "../TechSharkLib/Inc/Vector.h"
#include <functional>

//========================================================================================
// 
//      DirectionBattle
// 
//========================================================================================
class DirectionBattle final : public GameRule
{
private:
    Entrant::STATE entrant01Direction;
    Entrant::STATE entrant02Direction;
    enum class ROLE : std::uint8_t {
        ATK_DEF = 0,    // 1P ... ATK / 2P ... DEF
        DEF_ATK         // 1P ... DEF / 2P ... DEF
    };
    ROLE roleFlag;
    std::function<void()> MoveCamera;
    float cameraMoveSec;

    void Setup(GameMode* gameMode) override;
    void Reception(GameMode* gameMode) override;
    void Judge(GameMode* gameMode) override;
    void Idle(GameMode* gameMode) override;

    void PointByInput(Entrant* entrant, Entrant::STATE* hand);    // インプットで指を指す
    void PointByRandom(Entrant::STATE* direction);                          // 乱数で指を指す
    GameMode::RESULT JudgeResult();

    static std::map<Entrant::STATE, TechSharkLib::Float4> cameraFocuses;
    static std::map<Entrant::STATE, TechSharkLib::Float3> headRotations;

public:
    DirectionBattle() : 
        entrant01Direction{Entrant::STATE::NONE},
        entrant02Direction{Entrant::STATE::NONE},
        roleFlag{},
        MoveCamera{nullptr}, cameraMoveSec{0.0f},
        GameRule{}
    {
    }

    void DrawDebugGUI() override;

};

#endif // !INCLUDED_DIRECTION_BATTLE_H