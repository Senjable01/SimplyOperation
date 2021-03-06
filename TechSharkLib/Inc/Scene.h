#ifndef INCLUDED_INC_SCENE_H
#define INCLUDED_INC_SCENE_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include <memory>
#include <utility>

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
    //      Scene
    // 
    //========================================================================================
    class Scene
    {
    private:
        std::unique_ptr<Scene> nextScene;

    protected:
        virtual void Init() = 0;
        virtual void Setup();
        virtual void Update(float) = 0;
        virtual void Render() = 0;
        virtual void Deinit() = 0;

    public:
        Scene() : nextScene{nullptr} {}
        virtual ~Scene() {}

        std::unique_ptr<Scene>&& Run();

        template<typename Arg, typename... Args> void ChangeScene(Args&&... args)
        {
            _ASSERT_EXPR(nextScene == nullptr, L"シーン遷移前に既に呼び出されています。");
            nextScene = std::make_unique<Arg>(std::forward<Args>(args)...); // 次のシーンを作成
        }

    };

    //========================================================================================
    // 
    //      SceneManager
    // 
    //========================================================================================
    class SceneManager
    {
    private:
        std::unique_ptr<Scene> currentScene;
        SceneManager() : currentScene{nullptr} {}

        static SceneManager instance_;

    public:
        SceneManager(const SceneManager&) = delete;
        SceneManager& operator=(const SceneManager&) = delete;
        SceneManager(SceneManager&&) noexcept = delete;
        SceneManager& operator=(SceneManager&&) noexcept = delete;

        template<typename Arg, typename... Args> void Execute(Args&&... args)
        {
            _ASSERT_EXPR(currentScene == nullptr, L"ゲーム内に既に呼び出されています。");
            currentScene = std::make_unique<Arg>(std::forward<Args>(args)...);
            while (currentScene != nullptr)
            {
                currentScene = std::move(currentScene->Run());
            }
        }

        Scene* CurrentScene() { return currentScene.get(); }
        static SceneManager* GetInstance() { return &instance_; }
    };
}

#endif // !INCLUDED_INC_SCENE_H