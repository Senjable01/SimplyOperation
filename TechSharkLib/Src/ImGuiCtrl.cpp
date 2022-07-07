//------< include >-----------------------------------------------------------------------
#include "../Inc/Configulation.h"

#if USE_IMGUI
#include "../Inc/ImGuiCtrl.h"
#include <crtdbg.h>

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
    //      imgui
    // 
    //========================================================================================
    namespace imgui
    {
        void Initialize(HWND windowHandle, ID3D11Device* device, ID3D11DeviceContext* immediateContext)
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::GetIO().Fonts->AddFontFromFileTTF("C:/Windows/Fonts/meiryo.ttc", 18.0f, nullptr, glyphRangesJapanese);
            ImGui_ImplWin32_Init(windowHandle);
            _ASSERT_EXPR(immediateContext, L"immediateContext‚ÌŽæ“¾‚ÉŽ¸”s");
            ImGui_ImplDX11_Init(device, immediateContext);
            ImGui::StyleColorsDark();
        }
        void ClearFrame()
        {
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
        }
        void Display()
        {
            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }
        void Uninitialize()
        {
            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();
        }
    }
}

#endif // USE_IMGUI