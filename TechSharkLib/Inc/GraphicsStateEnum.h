#ifndef INCLUDED_INC_GRAPHICS_STATE_ENUM_H
#define INCLUDED_INC_GRAPHICS_STATE_ENUM_H

//------< pragma >------------------------------------------------------------------------
#pragma once

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
    //      SAMPLER_TEXTURE_FILTER
    // 
    //========================================================================================
    enum class SAMPLER_TEXTURE_FILTER : unsigned int {
        POINT_FILTER        = 0u,
        LINER_FILTER,
        ANISOTROPIC_FILTER,

        VALUE
    };

    //========================================================================================
    // 
    //      DEPTH_STATE
    // 
    //========================================================================================
    enum class DEPTH_STATE : unsigned int {
        NONE            = 0u,
        TEST,
        WRITE,
        TEST_AND_WRITE,

        VALUE
    };

    //========================================================================================
    // 
    //      BLEND_STATE
    // 
    //========================================================================================
    enum class BLEND_STATE : unsigned int {
        ALPHA = 0u,
        ADD,

        VALUE
    };

    //========================================================================================
    // 
    //      RASTERIZER_STATE
    // 
    //========================================================================================
    enum class RASTERIZER_STATE : size_t {
        SOLID_CULLING = 0u,
        SOLID,
        WIREFRAME_CULLING,
        WIREFRAME,

        VALUE,
    };
}

#endif // !INCLUDED_INC_GRAPHICS_STATE_ENUM_H