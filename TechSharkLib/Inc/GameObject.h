#ifndef INCLUDED_INC_GAME_OBJECT_H
#define INCLUDED_INC_GAME_OBJECT_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include "Component.h"
#include <vector>
#include <map>
#include <set>
#include <memory>

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //------< class >-------------------------------------------------------------------------

    class GameObjectManager;

    //========================================================================================
    // 
    //      GameObject
    // 
    //========================================================================================
    class GameObject
    {
    private:
        GameObjectManager*  gameObjectManager;
        ComponentManager*   componentManager;
        GameObjectID        selfID;
        std::vector<ComponentID> componentIds;

        Component* GetComponent(const ComponentID& id)
        {
            return componentManager->QueryComponent<Component>(id);
        }

    public:
        GameObject() = delete;
        GameObject(
            GameObjectManager* gameObjectManager, ComponentManager* componentManager,
            const GameObjectID& selfID
        ) : 
            gameObjectManager{gameObjectManager}, componentManager{componentManager},
            selfID{selfID}
        {
        }

        template<typename Arg, class... Args>
        ComponentID AddComponent(Args&&... args)
        {
            ComponentID id = componentManager->CreateComponent<Arg>(selfID, std::forward<Args>(args)...);
            _ASSERT_EXPR(id != ERROR_COMPONENT_ID, L"コンポーネントの作成に失敗");
            componentIds.emplace_back(id);
            ExpressDebugLog(L"オブジェクト(", this, L")に", Arg::COMPONENT_NAME.c_str(), L"コンポーネント(ID:", id, L")を追加しました。");
            return id;
        }
        template<typename Arg, class... Args>
        ComponentID AddComponent(Arg** output, Args&&... args)
        {
            ComponentID id = componentManager->CreateComponent<Arg>(output, selfID, std::forward<Args>(args)...);
            _ASSERT_EXPR(id != ERROR_COMPONENT_ID, L"コンポーネントの作成に失敗");
            componentIds.emplace_back(id);
            ExpressDebugLog(L"オブジェクト(", this, L")に", Arg::COMPONENT_NAME.c_str(), L"コンポーネント(ID:", id, L")を追加しました。");
            return id;
        }

        template<typename Arg>
        Arg* SearchComponent()
        {
            for (auto& id : componentIds)
            {
                Arg* component = componentManager->QueryComponent<Arg>(id);
                if (!component)
                {
                    continue;
                }

                return component;
            }
            ExpressDebugLog(L"<WARNING>: オブジェクト(", this, L")の", Arg::COMPONENT_NAME.c_str(), L"コンポーネントの検索は失敗しました。");
            return nullptr;
        }

        void Init();
        void Setup();
        void Update(float deltaTime);
        void Render(float scrollX, float scrollY);
        void Deinit();
        
    };

    //========================================================================================
    // 
    //      GameObjectManager
    // 
    //========================================================================================
    class GameObjectManager
    {
    private:
        std::map<GameObjectID, std::unique_ptr<GameObject>>  objectMap;
        std::set<GameObjectID>              excludes;
        std::unique_ptr<ComponentManager>   componentManager;

        static unsigned int nextId;

    public:
        GameObjectManager() : componentManager{nullptr}
        {
            componentManager = std::make_unique<ComponentManager>(this);
        }
        GameObjectManager(const GameObjectManager&) = delete;
        GameObjectManager& operator=(const GameObjectManager&) = delete;
        GameObjectManager(GameObjectManager&&) noexcept = delete;
        GameObjectManager& operator=(GameObjectManager&&) noexcept = delete;
        ~GameObjectManager() {}

        GameObjectID CreateObject(GameObject** output = nullptr)
        {
            GameObjectID id{GameObjectManager::nextId};
            std::unique_ptr<GameObject> object = std::make_unique<GameObject>(this, componentManager.get(), id);
            if (object == nullptr)
            {
                ExpressDebugLog(L"<WARNING>: GameObjectの作成に失敗しました。");
                _ASSERT_EXPR(false, L"GameObjectの作成に失敗");
                return GameObjectID{};
            }
            GameObjectManager::nextId++;

            if (output != nullptr)
            {
                *output = object.get();
            }
            objectMap.emplace(id, std::move(object));
            return id;
        }

        [[deprecated("個別に初期化することを推奨します。")]] void Init();
        [[deprecated("個別に設定することを推奨します。")]] void Setup();
        void Update(float deltaTime = 0.0f);
        void Render(float scrollX = 0.0f, float scrollY = 0.0f);
        void Deinit();

        GameObject* GetGameObject(const GameObjectID& id) { return objectMap.at(id).get(); }
        void Exclude(const GameObjectID& id) { excludes.emplace(id); }

    };

}

#endif // !INCLUDED_INC_GAME_OBJECT_H