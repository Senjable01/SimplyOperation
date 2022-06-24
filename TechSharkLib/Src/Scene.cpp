//------< include >-----------------------------------------------------------------------
#include "../Inc/Scene.h"
#include "../Inc/Window.h"
#include "../Inc/TechSharkLib.h"
#include "../Inc/Configulation.h"
#if USE_IMGUI
#include "../Inc/ImGuiCtrl.h"

#endif // USE_IMGUI

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

    //--------------------------------------------------------------------------
    // member fucntion
    //--------------------------------------------------------------------------

    void Scene::Setup()
    {
        nextScene = nullptr;
    }

    std::unique_ptr<Scene>&& Scene::Run()
    {
        Window& window = *(Window::Instance());

        this->Init();
        this->Setup();

        while (window.MessageLoop())
        {
            #if USE_IMGUI
            imgui::ClearFrame();

            #endif // USE_IMGUI

            UpdateInputState();

            this->Update(window.GetTimer()->DeltaTime());
            ClearView();
            this->Render();

            #if USE_IMGUI
            imgui::Display();

            #endif // USE_IMGUI

            Present();

            if (nextScene != nullptr)
                break;

        }

        this->Deinit();
        ResetProjector();

        return std::move(nextScene);
    }

    //========================================================================================
    // 
    //      SceneManager
    // 
    //========================================================================================

    //--------------------------------------------------------------------------
    // instance
    //--------------------------------------------------------------------------

    SceneManager SceneManager::instance_;

}