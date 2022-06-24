#ifndef INCLUDED_INC_FRAME_STATUS_H
#define INCLUDED_INC_FRAME_STATUS_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include <Windows.h>
#include "HighResolutionTimer.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //====================================================================================
    // 
    //      FrameStatus
    // 
    //====================================================================================
    struct FrameStatusResult
    {
        bool elapsedSecond;     // ‘O‰ñ‚©‚çˆê•bŠÔŒo‰ß‚µ‚½‚©
        float framePerSeconds;

        FrameStatusResult() : elapsedSecond{false}, framePerSeconds{0.0f} {}
        FrameStatusResult(bool elapsedSecond, float framePerSeconds) :
            elapsedSecond{elapsedSecond},
            framePerSeconds{framePerSeconds}
        {
        }
        
        operator bool() { return elapsedSecond; }

    };

    //------< function >----------------------------------------------------------------------

    FrameStatusResult CalcFrameState(const HighResolutionTimer& hrTimer);
    void DisplayFrameStateToWindowText(HWND windowHandle, float fps);

}

#endif // !INCLUDED_INC_FRAME_STATUS_H