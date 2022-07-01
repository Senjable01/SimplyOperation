#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/KeyAssign.h"

namespace config
{
    namespace key
    {
        extern TechSharkLib::KeyAssign rock0;
        extern TechSharkLib::KeyAssign scissors0;
        extern TechSharkLib::KeyAssign paper0;
        extern TechSharkLib::KeyAssign rock1;
        extern TechSharkLib::KeyAssign scissors1;
        extern TechSharkLib::KeyAssign paper1;
    }

    namespace gamerule
    {
        namespace rsp // rock-scissors-paper
        {
            constexpr float RECEPTION_SEC   = 5.0f;
            constexpr float IDLE_SEC        = 0.5f;
        }
    }
}