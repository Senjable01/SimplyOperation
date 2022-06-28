//------< include >-----------------------------------------------------------------------
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
    //      GameObject
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void GameObject::Init()
    {
        for (auto& id : componentIds)
        {
            GetComponent(id)->Init();
        }
    }
    void GameObject::Setup()
    {
        for (auto& id : componentIds)
        {
            GetComponent(id)->Setup();
        }
    }
    void GameObject::Update(float deltaTime)
    {
        for (auto& id : componentIds)
        {
            GetComponent(id)->Update(deltaTime);
        }
    }
    void GameObject::Render(float scrollX, float scrollY)
    {
        for (auto& id : componentIds)
        {
            GetComponent(id)->Render(scrollX, scrollY);
        }
    }
    void GameObject::Deinit()
    {
        for (auto& id : componentIds)
        {
            GetComponent(id)->Deinit();
        }
    }

    //========================================================================================
    // 
    //      GameObjectManager
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void GameObjectManager::Init()
    {
        for (auto& obj : objectMap)
        {
            obj.second->Init();
        }
    }
    void GameObjectManager::Setup()
    {
        for (auto& obj : objectMap)
        {
            obj.second->Setup();
        }
    }
    void GameObjectManager::Update(float deltaTime)
    {
        for (auto& obj : objectMap)
        {
            obj.second->Update(deltaTime);
        }

        for (auto& remove : excludes)
        {
            auto find = objectMap.find(remove);
            if (find != objectMap.end())
            {
                objectMap.erase(find);
            }
        }
        excludes.clear();
    }
    void GameObjectManager::Render(float scrollX, float scrollY)
    {
        for (auto& obj : objectMap)
        {
            obj.second->Render(scrollX, scrollY);
        }
    }
    void GameObjectManager::Deinit()
    {
        for (auto& obj : objectMap)
        {
            obj.second->Deinit();
        }
    }

    //------------------------------------------------------------------------------
    // instance
    //------------------------------------------------------------------------------

    unsigned int GameObjectManager::nextId = ERROR_OBJECT_ID + 1;

}