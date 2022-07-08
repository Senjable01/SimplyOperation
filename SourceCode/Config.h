#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/KeyAssign.h"

//------< macro >-------------------------------------------------------------------------

#define ACTIVE_BOTH_NPCS_PUSH_HANDS 1

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

        namespace push_hands
        {
            constexpr int   BASE_PUSH_COUNT     = 50;
            constexpr int   PENALTY_PUSH_COUNT  = 10;
            constexpr float RECEPTION_SEC       = 10.0f;
            constexpr float IDLE_SEC            = 1.5f;
        }

        namespace direction_battle
        {
            constexpr float RECEPTION_SEC   = 2.5f;
            constexpr float IDLE_SEC        = 2.5f;
        }

    }
}