//------< include >-----------------------------------------------------------------------
#include "Config.h"

namespace config
{
    namespace key
    {
        using TechSharkLib::BIT_NO;
        using TechSharkLib::KeyCodes;

        TechSharkLib::KeyAssign up0     = { BIT_NO::BIT_11, KeyCodes::W };
        TechSharkLib::KeyAssign right0  = { BIT_NO::BIT_12, KeyCodes::D };
        TechSharkLib::KeyAssign left0   = { BIT_NO::BIT_13, KeyCodes::A };
        TechSharkLib::KeyAssign down0   = { BIT_NO::BIT_14, KeyCodes::S };
        TechSharkLib::KeyAssign up1     = { BIT_NO::BIT_15, KeyCodes::Up };
        TechSharkLib::KeyAssign right1  = { BIT_NO::BIT_16, KeyCodes::Right };
        TechSharkLib::KeyAssign left1   = { BIT_NO::BIT_17, KeyCodes::Left };
        TechSharkLib::KeyAssign down1   = { BIT_NO::BIT_18, KeyCodes::Down };
    }
}