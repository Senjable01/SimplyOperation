#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/KeyAssign.h"

namespace config
{
    namespace key
    {
        extern TechSharkLib::KeyAssign up0;
        extern TechSharkLib::KeyAssign right0;
        extern TechSharkLib::KeyAssign left0;
        extern TechSharkLib::KeyAssign down0;
        extern TechSharkLib::KeyAssign up1;
        extern TechSharkLib::KeyAssign right1;
        extern TechSharkLib::KeyAssign left1;
        extern TechSharkLib::KeyAssign down1;
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