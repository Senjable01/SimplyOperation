#ifndef INCLUDED_INC_TEXTURE_DATA_H
#define INCLUDED_INC_TEXTURE_DATA_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
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

    constexpr unsigned int ERROR_SPRITE_ID  = 0u;
    constexpr unsigned int BATCH_BEGIN      = ~0u / 2;

    //------< class >-------------------------------------------------------------------------

    TSL_CREATE_ENTITY_ID(SpriteID, unsigned int, ERROR_SPRITE_ID);
    TSL_CREATE_ENTITY_ID(SpriteBatchID, unsigned int, ERROR_SPRITE_ID);

}

#endif // !INCLUDED_INC_TEXTURE_DATA_H