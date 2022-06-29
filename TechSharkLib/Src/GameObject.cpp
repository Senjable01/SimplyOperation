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
            /* コンポーネントIDをコピー */
            ComponentID id = src.componentIds.at(i);
            componentIds.emplace_back(id);
            /* ownerを自身へ移す */
            Component* component = componentManager->QueryComponent<Component>(id);
            _ASSERT_EXPR(component, L"コンポーネントの取り寄せに失敗");
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
        ExpressDebugLog(L"GameObject(ID:", id, L")を作成しました。");
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
        ExpressDebugLog(L"<WARNING>: 個別にGameObjectを初期化することを推奨します。後に作成する場合は必ず初期化して下さい。");
        for (auto& obj : objectMap)
        {
            obj.second.Init();
        }
    }
    void GameObjectManager::Setup()
    {
        ExpressDebugLog(L"<WARNING>: 個別にGameObjectを設定することを推奨します。後に作成する場合は必ず設定して下さい。");
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
            ExpressDebugLog(L"GameObject(ID:", *itr, L")を削除しました。");
            itr = excludes.erase(itr);
        }
        _ASSERT_EXPR(excludes.empty(), L"未削除のGameObjectを確認");

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