#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/KeyAssign.h"
#include "../TechSharkLib/Inc/Vector.h"

//------< macro >-------------------------------------------------------------------------

#define ACTIVE_BOTH_NPCS_PUSH_HANDS 1

namespace config
{
    namespace key
    {
        extern TechSharkLib::KeyAssign up1;
        extern TechSharkLib::KeyAssign right1;
        extern TechSharkLib::KeyAssign left1;
        extern TechSharkLib::KeyAssign down1;
        extern TechSharkLib::KeyAssign up2;
        extern TechSharkLib::KeyAssign right2;
        extern TechSharkLib::KeyAssign left2;
        extern TechSharkLib::KeyAssign down2;
    }

    namespace background
    {
        extern const TechSharkLib::Float2 POSITION;
        extern const TechSharkLib::Float2 SCALE;
        extern const TechSharkLib::Float2 TEXEL_SIZE;
        extern const TechSharkLib::Float2 PIVOT;
        extern const TechSharkLib::Float4 COLOR;
        enum class GAME_BG_NO : unsigned int {
            RSP_FIRST = 1,  // さいしょはグー
            RSP_RECEPTION,  // じゃんけん
            RSP_JUDGE,      // ポン！
            PH_RECEPTION,   // 抗え！
            DB_RECEPTION,   // あっちむいて
            DB_JUDGE        // ほい！
        };

        constexpr float ROTATE_Z_PER_SEC = DirectX::XMConvertToRadians(150.0f); // (リザルト画面用パラメーター)
    }

    namespace model
    {
        namespace button // Arrow Button
        {
            extern const TechSharkLib::Float3 SCALE;
            extern const TechSharkLib::Float3 ROTATE_LEFT;
            extern const TechSharkLib::Float3 ROTATE_RIGHT;
            extern const TechSharkLib::Float3 ROTATE_UP;
            extern const TechSharkLib::Float3 ROTATE_DOWN;
        }

        namespace stick
        {
            extern const TechSharkLib::Float3 SCALE;
            extern const TechSharkLib::Float3 ROTATE_NORMAL;
            extern const TechSharkLib::Float3 ROTATE_UP;
            extern const TechSharkLib::Float3 ROTATE_RIGHT;
            extern const TechSharkLib::Float3 ROTATE_DOWN;
            extern const TechSharkLib::Float3 ROTATE_LEFT;
        }

        namespace hand
        {
            extern const TechSharkLib::Float3 SCALE;
            extern const TechSharkLib::Float3 ROTATE_FRONT;    // Player01(手前)の回転度
            extern const TechSharkLib::Float3 ROTATE_BACK;     // Player02(奥)の回転度
        }

        namespace finger
        {
            extern const TechSharkLib::Float3 SCALE;
            extern const TechSharkLib::Float3 ROTATE_UP_FRONT;
            extern const TechSharkLib::Float3 ROTATE_RIGHT_FRONT;
            extern const TechSharkLib::Float3 ROTATE_DOWN_FRONT;
            extern const TechSharkLib::Float3 ROTATE_LEFT_FRONT;
            extern const TechSharkLib::Float3 ROTATE_UP_BACK;       // Player02から見て上
            extern const TechSharkLib::Float3 ROTATE_RIGHT_BACK;    // Player02から見て右(01から見て左)
            extern const TechSharkLib::Float3 ROTATE_DOWN_BACK;     // Player02から見て上
            extern const TechSharkLib::Float3 ROTATE_LEFT_BACK;     // Player02から見て左(01から見て右)
        }

        namespace head
        {
            extern const TechSharkLib::Float3 POSITION;
            extern const TechSharkLib::Float3 SCALE;
            extern const TechSharkLib::Float3 ROTATE_NORMAL_BACK;
            extern const TechSharkLib::Float3 ROTATE_UP_BACK;       // Player02から見て上
            extern const TechSharkLib::Float3 ROTATE_RIGHT_BACK;    // Player02から見て右(01から見て左)
            extern const TechSharkLib::Float3 ROTATE_DOWN_BACK;     // Player02から見て上
            extern const TechSharkLib::Float3 ROTATE_LEFT_BACK;     // Player02から見て左(01から見て右)
        }

    }

    namespace entrant
    {
        enum TYPE_FLAG : unsigned int
        {
            NONE    = 0,
            IS_NPC  = (1 << 0),
            IS_2ND  = (1 << 1)
        };

        enum class MESH : int
        {
            ROCK = 0,
            SCISSORS,
            PAPER,
            FINGER_1P,
            FINGER_2P,
            NUM
        };

        enum class STATE : int
        {
            ROCK = 0,
            SCISSORS,
            PAPER,
            LEFT,
            RIGHT,
            UP,
            DOWN,
            STATE_NUM,
            HAND_NUM = 3,
            NONE = -1
        };

        extern const TechSharkLib::Float3 BEGIN_POS_FRONT;
        extern const TechSharkLib::Float3 BEGIN_POS_BACK;
        extern const TechSharkLib::Float4 CAMERA_LOOK_LEFT;     // focus
        extern const TechSharkLib::Float4 CAMERA_LOOK_RIGHT;    // focus
        extern const TechSharkLib::Float4 CAMERA_LOOK_UP;       // focus
        extern const TechSharkLib::Float4 CAMERA_LOOK_DOWN;     // focus
    }

    namespace rule
    {
        enum class PHASE : int
        {
            SETUP = 0,
            RECEPTION,
            JUDGE,
            IDLE
        };

        enum class RESULT : int
        {
            DRAW = 0,
            WIN_1P,
            WIN_2P,
            NONE = -1
        };

        namespace rsp // Rock Scissors Paper
        {
            constexpr float BEGIN_RECEPTION_SEC = 4.0f;
            constexpr float RECEPTION_TIME      = 3.0f;
            constexpr float END_RECEPTION_SEC   = BEGIN_RECEPTION_SEC + RECEPTION_TIME;
            constexpr float END_IDLE_SEC        = 0.5f;
        }

        namespace push // Push Hands
        {
            constexpr int   BASE_PUSH_COUNT     = 50;
            constexpr int   PENALTY_PUSH_COUNT  = 35;
            constexpr float SHAKE_INTERVAL      = 1.0f / 50;
            constexpr float NPC_PUSH_INTERVAL   = 0.2f;
            constexpr int   NPC_MAX_PUSH_NUM    = 3;
            constexpr float END_RECEPTION_SEC   = 4.0f;
            constexpr float END_IDLE_SEC        = 1.5f;
            extern const TechSharkLib::Float3 SHAKE_VEC;
            extern const TechSharkLib::Float3 WIN_VEC;
            extern const TechSharkLib::Float3 LOSE_VEC;
        }

        namespace direction // Direction Battle
        {
            constexpr float END_RECEPTION_SEC   = 2.5f;
            constexpr float END_IDLE_SEC        = 2.5f;
        }
    }

    namespace guide
    {
        enum class DIRECTION : int { LEFT = 0, RIGHT, UP, DOWN, NONE, NUM, WAY4 = 4 };
        enum class MESH : int { STICK, ALLOW, LEAN };
        enum class STATE : int {
            RSP,    // Rock Scissors Paper
            PH,     // Push Hands
            DB,     // Direction Battle
            NONE
        };

        constexpr float LEAN_INTERVAL = 0.35f;

        extern const TechSharkLib::Float4 DISABLE_COLOR;
        extern const TechSharkLib::Float4 ACTIVE_COLOR;
        extern const TechSharkLib::Float4 SELECT_COLOR;

    }
}

//------< macro >-------------------------------------------------------------------------

#define ACTIVE_TO_PUSH_HAND (1)
#define ACTIVE_TO_DIRECTION_BATTLE (1)