//------< include >-----------------------------------------------------------------------
#include "../Inc/FrameStatus.h"
#include <sstream>

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    namespace
    {
        int             frames      = 0;
        float           elapsedSec  = 0.0f;
        constexpr float ONE_SECOND  = 1.0f;
    }

    //------< function >----------------------------------------------------------------------

    FrameStatusResult CalcFrameState(const HighResolutionTimer& hrTimer)
    {
        FrameStatusResult result{};

        frames++;

        if (ONE_SECOND < hrTimer.TimeStamp() - elapsedSec)
        {
            result.framePerSeconds = static_cast<float>(frames);
            result.elapsedSecond = true;

            frames = 0;
            elapsedSec += ONE_SECOND;
        }

        return result;
    }

    void DisplayFrameStateToWindowText(HWND windowHandle, float fps)
    {
        std::ostringstream outs;
        outs.precision(6);
        outs << "FPS : " << fps << " / " << "Frame Time : " << (1000.0f / fps) << " (ms)";
        SetWindowTextA(windowHandle, outs.str().c_str());
    }

}