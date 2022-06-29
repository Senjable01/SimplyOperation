#pragma once

//------< include >-----------------------------------------------------------------------
#include "Entrant.h"

//========================================================================================
// 
//      RockScissorsPaper
// 
//========================================================================================
class RockScissorsPaper
{
private:
    enum HAND : unsigned char {
        ROCK        = (1 << 0),
        SCISSORS    = (1 << 1),
        PAPER       = (1 << 2)
    };

    struct Character
    {
        enum class TYPE {
            PLAYER = 0,
            NON_PLAYER
        } type;
        HAND hand;
    };

    Character chara[2];

    int Shoot();
    int Push();
    int Result();

public:
    RockScissorsPaper() : chara{} {}
    ~RockScissorsPaper() {}

    void RegisterPlayer(Entrant* entrant);
    void Setup(Character::TYPE enemyType);
    // Œ‹‰Ê‚ð•Ô‚·(0 : –¢Œˆ’… / 1 ~ : Œˆ’…)
    int Fight();

};