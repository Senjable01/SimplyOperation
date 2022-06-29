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

    GameObject& GameObject::operator=(const GameObject& src)
    {
        gameObjectManager   = src.gameObjectManager;
        componentManager    = src.componentManager;

        componentIds.clear();
        const size_t size = src.componentIds.size();
        componentIds.reserve(size);
        for (size_t i = 0; i < size; i++)
        {
            /* �R���|�[�l���gID���R�s�[ */
            ComponentID id = src.componentIds.at(i);
            componentIds.emplace_back(id);
            /* owner�����g�ֈڂ� */
            Component* component = componentManager->QueryComponent<Component>(id);
            _ASSERT_EXPR(component, L"�R���|�[�l���g�̎��񂹂Ɏ��s");
            component->ChangeOwner(this);
        }

        return *this;
    }

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
            componentManager->Destroy(id);
        }
        componentIds.clear();
    }

    //========================================================================================
    // 
    //      GameObjectManager
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    GameObjectID GameObjectManager::CreateObject()
    {
        GameObjectID id{GameObjectManager::nextId};
        objectMap.emplace(id, GameObject{this, componentManager.get(), id});
        ExpressDebugLog(L"GameObject(ID:", id, L")���쐬���܂����B");
        GameObjectManager::nextId++;
        return id;
    }

    void GameObjectManager::Init(const GameObjectID& id)
    {
        objectMap.at(id).Init();
    }
    void GameObjectManager::Setup(const GameObjectID& id)
    {
        objectMap.at(id).Setup();
    }
    void GameObjectManager::Init()
    {
        ExpressDebugLog(L"<WARNING>: �ʂ�GameObject�����������邱�Ƃ𐄏����܂��B��ɍ쐬����ꍇ�͕K�����������ĉ������B");
        for (auto& obj : objectMap)
        {
            obj.second.Init();
        }
    }
    void GameObjectManager::Setup()
    {
        ExpressDebugLog(L"<WARNING>: �ʂ�GameObject��ݒ肷�邱�Ƃ𐄏����܂��B��ɍ쐬����ꍇ�͕K���ݒ肵�ĉ������B");
        for (auto& obj : objectMap)
        {
            obj.second.Setup();
        }
    }
    void GameObjectManager::Update(float deltaTime)
    {
        for (auto& obj : objectMap)
        {
            obj.second.Update(deltaTime);
        }

        for (auto itr = excludes.cbegin(), end = excludes.cend(); itr != end;)
        {
            auto find = objectMap.find(*itr);
            if (find == objectMap.end())
            {
                itr++;
                continue;
            }
            find->second.Deinit();
            objectMap.erase(find);
            ExpressDebugLog(L"GameObject(ID:", *itr, L")���폜���܂����B");
            itr = excludes.erase(itr);
        }
        _ASSERT_EXPR(excludes.empty(), L"���폜��GameObject���m�F");

    }
    void GameObjectManager::Render(float scrollX, float scrollY)
    {
        for (auto& obj : objectMap)
        {
            obj.second.Render(scrollX, scrollY);
        }
    }
    void GameObjectManager::Deinit()
    {
        for (auto& obj : objectMap)
        {
            obj.second.Deinit();
        }
        objectMap.clear();
    }

    //------------------------------------------------------------------------------
    // instance
    //------------------------------------------------------------------------------

    unsigned int GameObjectManager::nextId = ERROR_OBJECT_ID + 1;

}