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
        GameObjectManager*          gameObjectManager;
        ComponentManager*           componentManager;
        GameObjectID                selfId;
        std::vector<ComponentID>    componentIds;

        Component* GetComponent(const ComponentID& id) { return componentManager->QueryComponent<Component>(id); }

    public:
        GameObject() = delete;
        GameObject(
            GameObjectManager* gameObjectManager, ComponentManager* componentManager,
            const GameObjectID& selfId
        ) :
            gameObjectManager{gameObjectManager}, componentManager{componentManager},
            selfId{selfId}
        {
            _ASSERT_EXPR(gameObjectManager != nullptr,  L"gameObjectManager��nullptr");
            _ASSERT_EXPR(componentManager != nullptr,   L"componentManager��nullptr");
            componentIds.reserve(4);
            ExpressDebugLog(L"GameObject(ID:", selfId, L")���쐬����܂����B");
        }
        GameObject& operator=(const GameObject& src);

        template<typename Arg, typename Desc>
        ComponentID AddComponent(const Desc& desc)
        {
            ComponentID id = componentManager->CreateComponent<Arg>(this, desc);
            _ASSERT_EXPR(id != ERROR_COMPONENT_ID, L"�R���|�[�l���g�̍쐬�Ɏ��s");
            componentIds.emplace_back(id);
            ExpressDebugLog(L"�I�u�W�F�N�g(", selfId, L")��", Arg::COMPONENT_NAME.c_str(), L"�R���|�[�l���g(ID:", id, L")��ǉ����܂����B");
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
            ExpressDebugLog(L"<WARNING>: �I�u�W�F�N�g(ID:", selfId, L")��", Arg::COMPONENT_NAME.c_str(), L"�R���|�[�l���g�̌����͎��s���܂����B");
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
        std::map<GameObjectID, GameObject>  objectMap;
        std::set<GameObjectID>              excludes;
        std::unique_ptr<ComponentManager>   componentManager;

        static unsigned int nextId;

    public:
        GameObjectManager() : componentManager{nullptr}
        {
            componentManager = std::make_unique<ComponentManager>();
        }
        GameObjectManager(const GameObjectManager&) = delete;
        GameObjectManager& operator=(const GameObjectManager&) = delete;
        GameObjectManager(GameObjectManager&&) noexcept = delete;
        GameObjectManager& operator=(GameObjectManager&&) noexcept = delete;
        ~GameObjectManager() {}

        GameObjectID CreateObject();

        template<typename Arg, typename Desc>
        void AttachComponent(const GameObjectID& id, const Desc& desc) { objectMap.at(id).AddComponent<Arg>(desc); }

        void Init(const GameObjectID& id);
        void Setup(const GameObjectID& id);
        void Init();
        void Setup();
        void Update(float deltaTime = 0.0f);
        void Render(float scrollX = 0.0f, float scrollY = 0.0f);
        void Deinit();

        GameObject* GetGameObjectRef(const GameObjectID& id) { return &objectMap.at(id); }
        void Exclude(const GameObjectID& id) { excludes.emplace(id); }
    };

}

#endif // !INCLUDED_INC_GAME_OBJECT_H