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

    //========================================================================================
    // 
    //      Component
    // 
    //========================================================================================
    class Component
    {
    TSL_DEFINE_COMPONENT(Component);
    private:
        ComponentID selfId;
        GameObject* owner;

    public:
        Component() = delete;
        Component(const ComponentID& selfId, GameObject* owner) :
            selfId{selfId}, owner{owner}
        {
            _ASSERT_EXPR(owner != nullptr, L"ownerがnullptr");
        }
        virtual ~Component() {}

        virtual void Init()     = 0;
        virtual void Setup()    = 0;
        virtual void Update(float /*deltaTime*/) = 0;
        virtual void Render(float /*scrollX*/, float /*scrollY*/) = 0;
        virtual void Deinit()   = 0;

        virtual void DrawDebugGUI() = 0;

        void ChangeOwner(GameObject* nextOwner) { owner = nextOwner; }

        const ComponentID& SelfID() const noexcept { return selfId; }
        GameObject* GetOwnerRef() { return owner; }

    };

    //========================================================================================
    // 
    //      ComponentManager
    // 
    //========================================================================================
    class ComponentManager
    {
    private:
        std::map<ComponentID, std::unique_ptr<Component>> componentMap;

        static unsigned int nextId;

    public:
        ComponentManager() {}
        ComponentManager(const ComponentManager&) = delete;
        ComponentManager& operator=(const ComponentManager&) = delete;
        ComponentManager(ComponentManager&&) noexcept = delete;
        ComponentManager& operator=(ComponentManager&&) noexcept = delete;
        ~ComponentManager() {}

        template<typename Arg, typename Desc>
        auto CreateComponent(GameObject* owner, const Desc& description) -> decltype(Arg::TYPE, Arg::COMPONENT_NAME, ComponentID{})
        {
            ComponentID id{ComponentManager::nextId};
            std::unique_ptr<Arg> component = std::make_unique<Arg>(id, owner, description);
            if (!component)
            {
                ExpressDebugLog(L"<WARNING>: ", Arg::COMPONENT_NAME.c_str(), L"コンポーネントの作成に失敗しました。");
                return ComponentID{};
            }

            ComponentManager::nextId++;
            componentMap.emplace(id, std::move(component));

            return id;
        }
        //template<typename Arg, typename NonDesc> // 型がコンポーネントか調べるだけならいらないかも？
        //ComponentID CreateComponent(GameObject*, const NonDesc&)
        //{
        //    static_assert(false, "The Template Argument is wrong or forget to define (type)::TYPE and (type)::COMPONENT_NAME.");
        //    return ComponentID{};
        //}

        template<typename Arg>
        Arg* QueryComponent(const ComponentID& id)
        {
            auto result = componentMap.find(id);
            if (result == componentMap.end())
            {
                return nullptr;
            }

            Arg* component = dynamic_cast<Arg*>(result->second.get());
            if (!component)
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
            ExpressDebugLog(L"コンポーネント(ID:", id, L")を削除しました。");
        }

    };

}

#endif // !INCLUDED_INC_COMPONENT_H