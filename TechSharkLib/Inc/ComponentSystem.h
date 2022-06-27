#ifndef INCLUDED_INC_COMPONENT_SYSTEM
#define INCLUDED_INC_COMPONENT_SYSTEM

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include "../Inc/EntityID.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //------< constant >----------------------------------------------------------------------

    constexpr unsigned int ERROR_COMPONENT_ID = 0;
    constexpr unsigned int ERROR_OBJECT_ID = 0;

    //------< class >-------------------------------------------------------------------------

    TSL_CREATE_ENTITY_ID(ComponentID, unsigned int, ERROR_COMPONENT_ID);
    TSL_CREATE_ENTITY_ID(GameObjectID, unsigned int, ERROR_OBJECT_ID);

}

#endif // !INCLUDED_INC_COMPONENT_SYSTEM