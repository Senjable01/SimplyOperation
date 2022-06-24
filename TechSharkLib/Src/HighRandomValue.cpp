//------< include >-----------------------------------------------------------------------
#include "../Inc/HighRandomValue.h"
#include <climits>
#include <algorithm>

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //========================================================================================
    // 
    //      HighRandomValue
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // instance
    //------------------------------------------------------------------------------

    std::random_device HighRandomValue::seedGen;
    std::default_random_engine HighRandomValue::engine{HighRandomValue::seedGen()};

    //------------------------------------------------------------------------------
    // constructor
    //------------------------------------------------------------------------------

    HighRandomValue::HighRandomValue()
    {
    }

    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------

    template<typename Arg> Arg HighRandomValue::Generate()
    {
        return (HighRandomValue::engine());
    }
    template<> unsigned char HighRandomValue::Generate()
    {
        return (static_cast<unsigned char>(HighRandomValue::engine() % UCHAR_MAX));
    }
    template<> unsigned short HighRandomValue::Generate()
    {
        return (static_cast<unsigned short>(HighRandomValue::engine() % USHRT_MAX));
    }
    template<> unsigned int HighRandomValue::Generate()
    {
        return (static_cast<unsigned int>(HighRandomValue::engine() % UINT_MAX));
    }
    template<> unsigned long HighRandomValue::Generate()
    {
        return (static_cast<unsigned long>(HighRandomValue::engine() % ULONG_MAX));
    }
    template<> unsigned long long HighRandomValue::Generate()
    {
        return (static_cast<unsigned long long>(HighRandomValue::engine() % ULLONG_MAX));
    }

    template<typename Arg> Arg HighRandomValue::GenerateInRange(Arg min, Arg max)
    {
        return (HighRandomValue::engine());
    }
    template<> unsigned char HighRandomValue::GenerateInRange(unsigned char min, unsigned char max)
    {
        // ëÂè¨î‰ärÅAèCê≥
        unsigned char oldMin = min;
        min = (std::min)(min, max);
        max = (std::max)(oldMin, max);

        // óêêîê∂ê¨
        const unsigned char range = static_cast<unsigned char>((std::min)(max - min, UCHAR_MAX));
        return min + static_cast<unsigned char>(HighRandomValue::engine() % range);
    }
    template<> unsigned short HighRandomValue::GenerateInRange(unsigned short min, unsigned short max)
    {
        unsigned short oldMin = min;
        min = (std::min)(min, max);
        max = (std::max)(oldMin, max);

        const unsigned short range = static_cast<unsigned short>((std::min)(max - min, USHRT_MAX));
        return min + static_cast<unsigned short>(HighRandomValue::engine() % range);
    }
    template<> unsigned int HighRandomValue::GenerateInRange(unsigned int min, unsigned int max)
    {
        unsigned int oldMin = min;
        min = (std::min)(min, max);
        max = (std::max)(oldMin, max);

        const unsigned int range = (std::min)(max - min, UINT_MAX);
        return min + static_cast<unsigned int>(HighRandomValue::engine() % range);
    }
    template<> unsigned long HighRandomValue::GenerateInRange(unsigned long min, unsigned long max)
    {
        unsigned long oldMin = min;
        min = (std::min)(min, max);
        max = (std::max)(oldMin, max);

        const unsigned long range = (std::min)(max - min, ULONG_MAX);
        return min + static_cast<unsigned long>(HighRandomValue::engine() % range);
    }
    template<> unsigned long long HighRandomValue::GenerateInRange(unsigned long long min, unsigned long long max)
    {
        unsigned long long oldMin = min;
        min = (std::min)(min, max);
        max = (std::max)(oldMin, max);

        const unsigned long long range = (std::min)(max - min, ULLONG_MAX);
        return min + static_cast<unsigned long long>(HighRandomValue::engine() % range);
    }

}