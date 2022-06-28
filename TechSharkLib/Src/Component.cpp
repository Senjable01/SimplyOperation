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
    // member function
    //------------------------------------------------------------------------------

    GameObject* Component::GetOwner()
    {
        return manager->GetGameObjectManager()->GetGameObject(owner);
    }

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