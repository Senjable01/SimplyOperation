#ifndef INCLUDED_INC_STATIC_MESH_ID_H
#define INCLUDED_INC_STATIC_MESH_ID_H

#include "EntityID.h"

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
    
    constexpr unsigned int ERROR_STATIC_MESH_ID = 0;

    TSL_CREATE_ENTITY_ID(StaticMeshID, unsigned int, ERROR_STATIC_MESH_ID);

}

#endif // !INCLUDED_INC_STATIC_MESH_ID_H