#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Component.h"

//========================================================================================
// 
//      Entrant
// 
//========================================================================================
class Entrant : public TechSharkLib::Component
{
private:
    enum class TYPE {
        PLAYER = 0,
        NPC
    };
    enum class HAND {
        ROCK        = (1 << 0),
        SCISSORS    = (1 << 1),
        PAPER       = (1 << 2)
    };

    TYPE type;


};