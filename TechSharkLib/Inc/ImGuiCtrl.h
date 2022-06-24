#ifndef INCLUDED_IMGUI_H
#define INCLUDED_IMGUI_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include "Configulation.h"
#if USE_IMGUI
#include <windows.h>
#include <d3d11.h>
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"

#endif

#if USE_IMGUI
//------< extern >------------------------------------------------------------------------
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern ImWchar glyphRangesJapanese[]; //ref: imgui_ja_gryph_ranges.cpp

#endif

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    #if USE_IMGUI
    //========================================================================================
    // 
    //      imgui
    // 
    //========================================================================================
    namespace imgui
    {
        void Initialize(HWND windowHandle, ID3D11Device* device, ID3D11DeviceContext* immediateContext);
        void ClearFrame();
        void Display();
        void Uninitialize();
    }

    #endif // USE_IMGUI
}

#endif // !INCLUDED_IMGUI_H