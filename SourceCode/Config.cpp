//------< include >-----------------------------------------------------------------------
#include "Config.h"

namespace rad
{
    constexpr float DEG_0   = 0.0f;
    constexpr float DEG_30  = DirectX::XM_PIDIV2 / 3;
    constexpr float DEG_90  = DirectX::XM_PIDIV2;
    constexpr float DEG_120 = DEG_30 + DEG_90;
    constexpr float DEG_180 = DirectX::XM_PI;
}

namespace config
{
    namespace key
    {
        using TechSharkLib::BIT_NO;
        using TechSharkLib::KeyCodes;

        TechSharkLib::KeyAssign up1     = { BIT_NO::BIT_11, KeyCodes::W };
        TechSharkLib::KeyAssign right1  = { BIT_NO::BIT_12, KeyCodes::D };
        TechSharkLib::KeyAssign left1   = { BIT_NO::BIT_13, KeyCodes::A };
        TechSharkLib::KeyAssign down1   = { BIT_NO::BIT_14, KeyCodes::S };
        TechSharkLib::KeyAssign up2     = { BIT_NO::BIT_11, KeyCodes::Up };
        TechSharkLib::KeyAssign right2  = { BIT_NO::BIT_12, KeyCodes::Right };
        TechSharkLib::KeyAssign left2   = { BIT_NO::BIT_13, KeyCodes::Left };
        TechSharkLib::KeyAssign down2   = { BIT_NO::BIT_14, KeyCodes::Down };
    }

    namespace background
    {
        const TechSharkLib::Float2 SCREEN_SIZE  = {1280.0f, 720.0f};
        const TechSharkLib::Float2 POSITION     = SCREEN_SIZE / 2;
        const TechSharkLib::Float2 SCALE        = {0.5f, 0.5f};
        const TechSharkLib::Float2 TEXEL_SIZE   = {2560.0f, 1440.0f};
        const TechSharkLib::Float2 PIVOT        = TEXEL_SIZE / 2;
        const TechSharkLib::Float4 COLOR        = {1.0f, 1.0f, 1.0f, 1.0f};

        const TechSharkLib::Float2 UI_POS       = {160.0f, 90.0f};
        const TechSharkLib::Float2 UI_SCALE     = SCALE / 4;
    }

    namespace model
    {
        namespace button
        {
            const TechSharkLib::Float3 SCALE        = {0.025f, 0.025f, 0.025f};
            const TechSharkLib::Float3 ROTATE_LEFT  = {rad::DEG_0, rad::DEG_90, -rad::DEG_90};
            const TechSharkLib::Float3 ROTATE_RIGHT = {rad::DEG_0, -rad::DEG_90, rad::DEG_90};
            const TechSharkLib::Float3 ROTATE_UP    = {rad::DEG_90, rad::DEG_180, rad::DEG_0};
            const TechSharkLib::Float3 ROTATE_DOWN  = {-rad::DEG_90, rad::DEG_0, rad::DEG_0};
        }

        namespace stick
        {
            const TechSharkLib::Float3 SCALE            = {0.2f, 0.2f, 0.2f};
            const TechSharkLib::Float3 ROTATE_NORMAL    = {-rad::DEG_90, rad::DEG_0, rad::DEG_0};
            const TechSharkLib::Float3 ROTATE_UP        = {rad::DEG_0, -rad::DEG_90, rad::DEG_90};
            const TechSharkLib::Float3 ROTATE_RIGHT     = {-rad::DEG_90, rad::DEG_0, rad::DEG_0};
            const TechSharkLib::Float3 ROTATE_DOWN      = {rad::DEG_0, rad::DEG_90, -rad::DEG_90};
            const TechSharkLib::Float3 ROTATE_LEFT      = {rad::DEG_90, rad::DEG_180, rad::DEG_0};
        }

        namespace hand
        {
            const TechSharkLib::Float3 SCALE            = {0.2f, 0.2f, 0.2f};
            const TechSharkLib::Float3 ROTATE_FRONT     = {rad::DEG_0, rad::DEG_180, rad::DEG_0};
            const TechSharkLib::Float3 ROTATE_BACK      = {rad::DEG_0, rad::DEG_0, rad::DEG_0};
        }

        namespace finger
        {
            const TechSharkLib::Float3 SCALE                = {0.24f, 0.24f, 0.24f};
            const TechSharkLib::Float3 ROTATE_UP_FRONT      = {rad::DEG_0, rad::DEG_0, rad::DEG_0};
            const TechSharkLib::Float3 ROTATE_RIGHT_FRONT   = {rad::DEG_0, rad::DEG_0, -rad::DEG_90};
            const TechSharkLib::Float3 ROTATE_DOWN_FRONT    = {rad::DEG_0, rad::DEG_0, -rad::DEG_180};
            const TechSharkLib::Float3 ROTATE_LEFT_FRONT    = {rad::DEG_180, rad::DEG_0, rad::DEG_90};
            const TechSharkLib::Float3 ROTATE_UP_BACK       = {rad::DEG_0, rad::DEG_180, rad::DEG_0};
            const TechSharkLib::Float3 ROTATE_RIGHT_BACK    = {rad::DEG_0, rad::DEG_180, -rad::DEG_90};
            const TechSharkLib::Float3 ROTATE_DOWN_BACK     = {rad::DEG_0, rad::DEG_180, -rad::DEG_180};
            const TechSharkLib::Float3 ROTATE_LEFT_BACK     = {rad::DEG_180, rad::DEG_180, rad::DEG_90};
        }

        namespace head
        {
            const TechSharkLib::Float3 POSITION             = {0.0f, 0.0f, 2.0f};
            const TechSharkLib::Float3 SCALE                = {1.2f, 1.2f, 1.2f};
            const TechSharkLib::Float3 ROTATE_NORMAL_BACK   = {rad::DEG_0, rad::DEG_180, rad::DEG_0};
            const TechSharkLib::Float3 ROTATE_UP_BACK       = {-rad::DEG_30, rad::DEG_180, rad::DEG_0};
            const TechSharkLib::Float3 ROTATE_RIGHT_BACK    = {rad::DEG_0, -rad::DEG_120, rad::DEG_0};
            const TechSharkLib::Float3 ROTATE_DOWN_BACK     = {rad::DEG_30, -rad::DEG_180, rad::DEG_0};
            const TechSharkLib::Float3 ROTATE_LEFT_BACK     = {rad::DEG_0, rad::DEG_120, rad::DEG_0};
        }

        namespace stage
        {
            const TechSharkLib::Float3 POSITION = {0.0f, 0.0f, 0.0f};
            const TechSharkLib::Float3 SCALE    = {0.5f, 0.5f, 0.5f};
            const TechSharkLib::Float3 ROTATION = {0.0f, rad::DEG_180 , 0.0f};
        }

    }

    namespace entrant
    {
        const TechSharkLib::Float3 BEGIN_POS_FRONT      = {-0.5f, -1.7f, -1.0f};
        const TechSharkLib::Float3 BEGIN_POS_BACK       = {0.5f, -1.2f, 1.0f};
        const TechSharkLib::Float4 CAMERA_LOOK_LEFT     = {-2.0f, 0.0f, 0.0f, 1.0f};
        const TechSharkLib::Float4 CAMERA_LOOK_RIGHT    = { 2.0f, 0.0f, 0.0f, 1.0f};
        const TechSharkLib::Float4 CAMERA_LOOK_UP       = {0.0f, 2.0f, 0.0f, 1.0f};
        const TechSharkLib::Float4 CAMERA_LOOK_DOWN     = {0.0f, -2.0f, 0.0f, 1.0f};
    }

    namespace rule
    {
        namespace push
        {
            const TechSharkLib::Float3 SHAKE_VEC    = {0.04f, 0.04f, 0.04f};
            const TechSharkLib::Float3 WIN_VEC      = {2.5f, 0.0f, 2.5f};
            const TechSharkLib::Float3 LOSE_VEC     = {3.0f, 0.0f, 3.0f};
        }
    }

    namespace guide
    {
        const TechSharkLib::Float4 DISABLE_COLOR    = {0.6f, 0.6f, 0.6f, 0.5f};
        const TechSharkLib::Float4 ACTIVE_COLOR     = {1.0f, 1.0f, 1.0f, 1.0f};
        const TechSharkLib::Float4 SELECT_COLOR     = {1.0f, 0.1f, 0.1f, 1.0f};
    }

}