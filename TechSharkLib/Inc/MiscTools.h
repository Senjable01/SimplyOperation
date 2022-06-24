#ifndef INCLUDED_MISC_TOOLS_H
#define INCLUDED_MISC_TOOLS_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    template<typename Arg> inline void SafeRelease(Arg*& comObj)
    {
        if (comObj != nullptr)
        {
            comObj->Release();
            comObj = nullptr;
        }
    }

    template<typename Arg> inline void SafeDelete(Arg*& p)
    {
        if (p != nullptr)
        {
            delete p;
            p = nullptr;
        }
    }

    template<typename Arg> inline void SafeDeleteArray(Arg*& arr)
    {
        if (arr != nullptr)
        {
            delete[] arr;
            arr = nullptr;
        }
    }
}

//------< macro >-------------------------------------------------------------------------

#define DISALLOW_COPY_AND_ASSIGN( CLASSNAME ) \
CLASSNAME(const CLASSNAME&) = delete; \
CLASSNAME& operator=(const CLASSNAME&) = delete; \

#define DISALLOW_COPY_ASSIGN_AND_MOVE( CLASSNAME ) \
CLASSNAME(const CLASSNAME&) = delete; \
CLASSNAME& operator=(const CLASSNAME&) = delete; \
CLASSNAME(CLASSNAME&&) noexcept = delete; \
CLASSNAME& operator=(CLASSNAME&&) noexcept = delete

#endif // !INCLUDED_MISC_TOOLS_H