#ifndef INCLUDED_INC_HIGH_RANDOM_VALUE_H
#define INCLUDED_INC_HIGH_RANDOM_VALUE_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include <random>

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
    class HighRandomValue
    {
    private:
        static std::random_device   seedGen;
        static std::mt19937         engine; // Mersenne Twister

    public:
        HighRandomValue();

        template<typename Arg>
        [[deprecated("This Template is not specialized.")]] Arg Generate();
        template<> unsigned char Generate();
        template<> unsigned short Generate();
        template<> unsigned int Generate();
        template<> unsigned long Generate();
        template<> unsigned long long Generate();

        template<typename Arg>
        [[deprecated("This Template is not specialized.")]] Arg GenerateInRange(Arg min, Arg max);
        template<> unsigned char GenerateInRange(unsigned char min, unsigned char max);
        template<> unsigned short GenerateInRange(unsigned short min, unsigned short max);
        template<> unsigned int GenerateInRange(unsigned int min, unsigned int max);
        template<> unsigned long GenerateInRange(unsigned long min, unsigned long max);
        template<> unsigned long long GenerateInRange(unsigned long long min, unsigned long long max);

    };
}

#endif // !INCLUDED_INC_HIGH_RANDOM_VALUE_H