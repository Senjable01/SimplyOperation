#ifndef INCLUDED_INC_WINDOW_PROCEDURE_H
#define INCLUDED_INC_WINDOW_PROCEDURE_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include <windows.h>

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

    LRESULT CALLBACK WindowProcedure(
        HWND windowHandle,
        UINT msg,
        WPARAM wparam, LPARAM lparam
    );
}

#endif // !INCLUDED_INC_WINDOW_PROCEDURE_H