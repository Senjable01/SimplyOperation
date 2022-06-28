#ifndef INCLUDED_INC_COMPONENT_H
#define INCLUDED_INC_COMPONENT_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include "ComponentSystem.h"
#include <string>
#include <map>
#include <memory>
#include <utility>
#include "DebugTools.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //------< macro >-------------------------------------------------------------------------

    #define TSL_DEFINE_COMPONENT( CLASS ) \
    public: \
        static CLASS* TYPE; \
        static std::string COMPONENT_NAME; \
        const std::string& Name() const noexcept { return CLASS::COMPONENT_NAME; }

    #define TSL_IMPLEMENT_COMPONENT( CLASS, NAME ) \
    CLASS* CLASS::TYPE = nullptr; \
    std::string CLASS::COMPONENT_NAME = NAME

    //------< class >-------------------------------------------------------------------------

    class ComponentManager;
    class GameObject;
    class GameObjectManager;

    //========================================================================================
    // 
    //      Component
    // 
    //========================================================================================
    class Component
    {
    TSL_DEFINE_COMPONENT(Component);
    protected:
        ComponentManager*   manager;
        ComponentID         selfID;
        GameObjectID        owner;

    public:
        Component() = delete;
        Component(ComponentManager* manager, const ComponentID& selfID, const GameObjectID& owner) :
            manager{manager},
            selfID{selfID}, owner{owner}
        {
        }
        virtual ~Component() {}

        virtual void Init() = 0;
        virtual void Setup() = 0;
        virtual void Update(float/*deltaTime*/) = 0;
        virtual void Render(float/*scrollX*/, float/*scrollY*/) = 0;
        virtual void Deinit() = 0;

        virtual void Clear() = 0;

    };

    //========================================================================================
    // 
    //      ComponentManager
    // 
    //========================================================================================
    class ComponentManager
    {
    private:
        GameObjectManager* gameObjectManager;
        std::map<ComponentID, std::unique_ptr<Component>> componentMap;

        static unsigned int nextId;

    public:
        ComponentManager() = delete;
        explicit ComponentManager(GameObjectManager* gameObjectManager) : 
            gameObjectManager{gameObjectManager}
        {
            _ASSERT_EXPR(gameObjectManager, L"gameObjectManagerがnullptr");
        }
        ComponentManager(const ComponentManager&) = delete;
        ComponentManager& operator=(const ComponentManager&) = delete;
        ComponentManager(ComponentManager&&) noexcept = delete;
        ComponentManager& operator=(ComponentManager&&) noexcept = delete;
        ~ComponentManager() {}

        template<typename Arg, class... Args>
        auto CreateComponent(const GameObject& owner, Args&&... args) -> decltype(Arg::TYPE, Arg::COMPONENT_NAME, ComponentID{})
        {
            ComponentID id = ComponentManager::nextId;
            //Info C2440 --> 引数を間違っている可能性あり
            std::unique_ptr<Arg> component = std::make_unique<Arg>(this, id, owner, std::forward<Args>(args)...);
            if (component == false)
            {
                ExpressDebugLog(L"<WARNING>: ", Arg::COMPONENT_NAME, L"コンポーネントの作成に失敗しました。");
                return ComponentID{};
            }
            ComponentManager::nextId++;

            componentMap.emplace(id, component);
            
            return id;
        }
        template<typename Arg, class... Args>
        auto CreateComponent(Arg** output, const GameObjectID& owner, Args&&... args) -> decltype(Arg::TYPE, Arg::COMPONENT_NAME, ComponentID{})
        {
            ComponentID id{ComponentManager::nextId};
            //Info C2440 --> 引数を間違っている可能性あり
            std::unique_ptr<Arg> component = std::make_unique<Arg>(this, id, owner, std::forward<Args>(args)...);
            if (component == nullptr)
            {
                ExpressDebugLog(L"<WARNING>: ", Arg::COMPONENT_NAME.c_str(), L"コンポーネントの作成に失敗しました。");
                return ComponentID{};
            }
            ComponentManager::nextId++;

            if (output != nullptr)
            {
                *output = component.get();
            }
            componentMap.emplace(id, std::move(component));
            return id;
        }
        template<typename Arg>
        ComponentID CreateComponent(...)
        {
            static_assert(false, "The Template Argument is wrong or forget to define (type)::TYPE and (type)::COMPONENT_NAME.");
            return ComponentID{};
        }

        template<typename Arg>
        Arg* QueryComponent(const ComponentID& id)
        {
            auto result = componentMap.find(id);
            if (result == componentMap.end())
            {
                return nullptr;
            }

            Arg* component = dynamic_cast<Arg*>(result->second.get());
            if (component == false)
            {
                return nullptr;
            }

            return component;
        }
        template<>
        Component* QueryComponent(const ComponentID& id)
        {
            return componentMap.at(id).get();
        }

        void Destroy(const ComponentID& id)
        {
            componentMap.erase(id);
        }

        GameObjectManager* GetGameObjectManager() { return gameObjectManager; }
        
    };

}

#endif // !INCLUDED_INC_COMPONENT_H