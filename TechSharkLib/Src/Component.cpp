//------< include >-----------------------------------------------------------------------
#include "../Inc/Component.h"
#include "../Inc/GameObject.h"

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
    //      Component
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // instance
    //------------------------------------------------------------------------------

    TSL_IMPLEMENT_COMPONENT(Component, "Component");

    //========================================================================================
    // 
    //      ComponentManager
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // instance
    //------------------------------------------------------------------------------

    unsigned int ComponentManager::nextId = ERROR_COMPONENT_ID + 1;

}