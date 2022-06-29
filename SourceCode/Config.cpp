//------< include >-----------------------------------------------------------------------
#include "Config.h"

namespace config
{
    namespace key
    {
        using TechSharkLib::BIT_NO;
        using TechSharkLib::KeyCodes;

        TechSharkLib::KeyAssign rock0       = { BIT_NO::BIT_11, KeyCodes::A };
        TechSharkLib::KeyAssign scissors0   = { BIT_NO::BIT_12, KeyCodes::W };
        TechSharkLib::KeyAssign paper0      = { BIT_NO::BIT_13, KeyCodes::D };
        TechSharkLib::KeyAssign rock1       = { BIT_NO::BIT_14, KeyCodes::Left };
        TechSharkLib::KeyAssign scissors1   = { BIT_NO::BIT_15, KeyCodes::Up };
        TechSharkLib::KeyAssign paper1      = { BIT_NO::BIT_16, KeyCodes::Right };
    }
}