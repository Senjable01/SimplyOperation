#ifndef INCLUDED_INC_DEBUG_TOOLS_H
#define INCLUDED_INC_DEBUG_TOOLS_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include <windows.h>
#include <crtdbg.h>
#include "StringTool.h"
#include "Configulation.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //------< function >----------------------------------------------------------------------

    inline LPWSTR ResultTrace(HRESULT hr)
    {
        LPWSTR msg = {0};
        FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&msg), 0, NULL);
        return msg;
    }

    template<typename Arg> inline bool Not(Arg src, Arg dst)
    {
        return (static_cast<size_t>(src) ^ static_cast<size_t>(dst));
    }

    template<typename... Args> void DisplayMessageBox(const wchar_t* caption, Args&&... args)
    {
        TechSharkLib::string::WideStringMaker message;
        message.Input(std::forward<Args>(args)...);
        MessageBox(NULL, message.Output().c_str(), caption, MB_OK);
    }

    //========================================================================================
    // 
    //      DebugLogMaker
    // 
    //========================================================================================
    class DebugLogMaker
    {
    private:
        TechSharkLib::string::WideStringMaker log;

    public:
        DebugLogMaker() : log{} {}
        DebugLogMaker(const DebugLogMaker&) = delete;
        DebugLogMaker& operator=(const DebugLogMaker&) = delete;
        DebugLogMaker(DebugLogMaker&&) noexcept = delete;
        DebugLogMaker& operator=(DebugLogMaker&&) noexcept = delete;

        template<typename... Args> void InputLog(Args&&... args)
        {
            log.Input(std::forward<Args>(args)...);
            log.LineBreak();
        }
        void OutputLog(bool blankRow)
        {
            if (blankRow)
            {
                log.LineBreak();
            }
            OutputDebugString(log.Output().c_str());
        }
        template<typename... Args> void ExpressLog(bool blankRow, Args&&... args)
        {
            InputLog(std::forward<Args>(args)...);
            OutputLog(blankRow);
        }

        static DebugLogMaker debugLogMakerMacrosUse;

    };

    #if DEBUG_MODE
    #define ExpressDebugLog(...) \
    TechSharkLib::DebugLogMaker::debugLogMakerMacrosUse.ExpressLog(false, L"<DebugLog>: ", __VA_ARGS__, " -> ", __FILEW__ , L", " , __LINE__ , L"行目")
    #define LineBreakDebugLog() \
    TechSharkLib::DebugLogMaker::debugLogMakerMacrosUse.ExpressLog(false, " ", " ")
    #define DISPLAY_MESSAGE_BOX(TITLE, ...) \
    TechSharkLib::DisplayMessageBox(TITLE, __VA_ARGS__)

    #else
    #define ExpressDebugLog(...)
    #define LineBreakDebugLog()
    #define DISPLAY_MESSAGE_BOX(TITLE, ...)

    #endif // DEBUG_MODE
}

#endif // !INCLUDED_INC_DEBUG_TOOLS_H