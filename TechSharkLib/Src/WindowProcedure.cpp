//------< include >-----------------------------------------------------------------------
#include "../Inc/WindowProcedure.h"
#include "../Inc/Configulation.h"
#if USE_IMGUI
#include "../Inc/ImGuiCtrl.h"

#endif // USE_IMGUI
#include "../DirectXTK/Inc/Keyboard.h"
#include "../Inc/Window.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //------< function >------------------------------------------------------------------
    // UNIT03 Section0
    // UNIT03 Section1

    LRESULT CALLBACK WindowProcedure(
        HWND windowHandle,
        UINT msg,
        WPARAM wparam, LPARAM lparam
    )
    {
        #if USE_IMGUI
        if (ImGui_ImplWin32_WndProcHandler(windowHandle, msg, wparam, lparam)) { return true; }

        #endif
        using DirectX::Keyboard;

        switch (msg)
        {
        case WM_PAINT:
        {
            PAINTSTRUCT ps{};
            BeginPaint(windowHandle, &ps);
            EndPaint(windowHandle, &ps);
        }
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_CREATE:
            break;

        case WM_ACTIVATEAPP:
            Keyboard::ProcessMessage(msg, wparam, lparam);
            break;
        case WM_KEYDOWN:
            if (wparam == VK_ESCAPE) // Escキーが押されたとき？
            {
                PostMessage(windowHandle, WM_CLOSE, 0, 0);
                break;
            }

        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
            Keyboard::ProcessMessage(msg, wparam, lparam);
            break;
        
        case WM_MENUCHAR:
            // https://github.com/Microsoft/DirectXTK/wiki/Keyboard
            // A menu is active and the user presses a key that does not correspond
            // to any mnemonic or accelerator key. Ignore so we don't produce an error beep.
            // メニューがアクティブな状態で、ニモニックキーやアクセラレータキーに対応していないキーを押した場合
            // ニモニックキーまたはアクセラレータキーに対応していないキーを押した場合。エラービープを出さないように無視する。
            return MAKELRESULT(0, MNC_CLOSE);

        case WM_ENTERSIZEMOVE:
            Window::Instance()->GetTimer()->Stop();
            break;

        case WM_EXITSIZEMOVE:
            Window::Instance()->GetTimer()->Start();
            break;

        default:
            return DefWindowProc(windowHandle, msg, wparam, lparam);

        }

        return 0;

    }
}