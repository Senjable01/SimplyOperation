#ifndef INCLUDED_INC_WINDOW_H
#define INCLUDED_INC_WINDOW_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning (disable : 4458)

//------< include >-----------------------------------------------------------------------
#include <windows.h>
#include "HighResolutionTimer.h"
#include "FrameStatus.h"
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
    //========================================================================================
    // 
    //      Window
    // 
    //========================================================================================
    class Window
    {
    private:
        HWND windowHandle;
        LONG width;
        LONG height;
        HighResolutionTimer hrTimer;
        bool displayFrameRate;

        Window() : windowHandle{}, width{0L}, height{0L}, hrTimer{}, displayFrameRate{false}
        {
        }

        static Window instance_;

    public:
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) noexcept = delete;
        Window& operator=(Window&&) noexcept = delete;
        ~Window() {}

        HWND Initialize(LPCTSTR caption = L"TechSharkLib", const LONG width = 1280L, const LONG height = 720L);
        bool MessageLoop();
        void Uninitialize();

        //HWND WindowHandle() const noexcept { return windowHandle; }
        CONST LONG Width() const noexcept { return width; }
        CONST LONG Height() const noexcept { return height; }
        HighResolutionTimer* GetTimer() noexcept { return &hrTimer; }

        //UNDONE:02 フレームレート表示についてのインターフェースを完全に切り離す。
        void SetDisplayFrameRate(bool displayFrameRate) { this->displayFrameRate = displayFrameRate; }

        static Window* Instance() { return &instance_; }

    };

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    inline bool Window::MessageLoop()
    {
        // UNIT02 Section0
        // UNIT02 Section2

        MSG msg;
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        #if FIXED_LENGTH_FRAME
        //フレームレート用
        while (!hrTimer.Tick()); // ---> フレームレート制限がきたらtrueになるまでループする？

        #else
        hrTimer.Tick();

        #endif // 0

        /* フレームレートを表示 */
        if (displayFrameRate)
        {
            FrameStatusResult frameStatus = CalcFrameState(hrTimer);
            if (frameStatus == true)
            {
                DisplayFrameStateToWindowText(windowHandle, frameStatus.framePerSeconds);
            }
        }

        return true;

    }
}

#endif // !INCLUDED_INC_WINDOW_H