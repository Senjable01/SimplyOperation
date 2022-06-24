//------< include >-----------------------------------------------------------------------
#include "../Inc/TechSharkLib.h"
#include "../Inc/Window.h"
#include "../Inc/DirectX11.h"
#include "../Inc/SpriteManager.h"
#include "../Inc/StaticMeshManager.h"
#include "../Inc/Projector.h"
#include "../Inc/Input.h"
#include "../Inc/ResourceManager.h"
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
    //      Manager
    // 
    //========================================================================================
    static struct
    {
        Window*             window              = nullptr; // (キャッシュ用)
        Graphics            graphics            = {};
        SpriteManager       spriteManager       = {};
        StaticMeshManager   staticMeshManager   = {};
        Projector           projector           = {};
        InputManager        inputManager        = {};
        ResourceManager*    resourceManager     = nullptr; // (キャッシュ用)

    } manager;

    //------< function >----------------------------------------------------------------------

    /* System */
    void Initialize(const wchar_t* caption, int width, int height, bool isFullscreen)
    {
        manager.window          = Window::Instance();
        manager.resourceManager = ResourceManager::GetInstance();
        HWND windowHandle       = manager.window->Initialize(caption, static_cast<LONG>(width), static_cast<LONG>(height));
        manager.graphics.Initialize(windowHandle, static_cast<LONG>(width), static_cast<LONG>(height), isFullscreen);
        manager.spriteManager.Initialize(manager.graphics.GetDevice(), manager.graphics.GetContext());
        manager.staticMeshManager.Initialize(manager.graphics.GetDevice(), manager.graphics.GetContext());
        manager.projector.Initialize(manager.graphics.GetDevice(), manager.graphics.GetContext());
        manager.inputManager.Initialize(windowHandle);
        #if USE_IMGUI
        imgui::Initialize(windowHandle, manager.graphics.GetDevice(), manager.graphics.GetContext());

        #endif // USE_IMGUI
    }
    void Uninitialize()
    {
        #if USE_IMGUI
        imgui::Uninitialize();

        #endif // USE_IMGUI
        manager.spriteManager.ReleaseAll();
        manager.staticMeshManager.ReleaseAll();
        manager.projector.Uninitialize();
        manager.resourceManager->Clear();
        manager.graphics.Uninitialze();
        manager.window->Uninitialize();
    }

    /* Window */
    float WindowWidth()
    {
        return static_cast<float>(manager.window->Width());
    }
    float WindowHeight()
    {
        return static_cast<float>(manager.window->Height());
    }
    void SetDisplayFrameRate(bool displayFrameRate)
    {
        manager.window->SetDisplayFrameRate(displayFrameRate);
    }

    /* Graphics */
    float AspectRatio()
    {
        return manager.graphics.AspectRatio();
    }
    void ClearView(float red, float green, float blue, float alpha)
    {
        manager.graphics.ClearView(red, green, blue, alpha);
    }
    void Present()
    {
        manager.graphics.Present();
    }
    void SetDepthState(DEPTH_STATE state)
    {
        manager.graphics.SetDepthState(state);
    }
    void SetBlendState(BLEND_STATE state)
    {
        manager.graphics.SetBlendState(state);
    }
    void SetRasterizerState(RASTERIZER_STATE state)
    {
        manager.graphics.SetRasterizerState(state);
    }

    /* Sprite */
    SpriteID LoadSprite(const wchar_t* filePath)
    {
        return manager.spriteManager.LoadSprite(filePath);
    }
    void Render(
        const SpriteID& id,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    )
    {
        manager.graphics.SetDepthState(DEPTH_STATE::NONE);
        manager.spriteManager.Render(
            id, posX, posY, scaleX, scaleY, pivotX, pivotY, rotation, red, blue, green, alpha
        );
    }
    void Render(
        const SpriteID& id,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float texelX,   float texelY, float texelW, float texelH,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    )
    {
        manager.spriteManager.Render(
            id, posX, posY, scaleX, scaleY, texelX, texelY, texelW, texelH, pivotX, pivotY, rotation, red, green, blue, alpha
        );
    }
    void Release(const SpriteID& id)
    {
        manager.spriteManager.Release(id);
    }

    /* SpriteBatch */
    SpriteBatchID LoadSpriteBatch(const wchar_t* filePath, size_t maxInstance)
    {
        return manager.spriteManager.LoadSpriteBatch(filePath, maxInstance);
    }
    void Begin(const SpriteBatchID& id)
    {
        manager.spriteManager.Begin(id);
    }
    void Render(
        const SpriteBatchID& id,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    )
    {
        manager.spriteManager.Render(
            id, posX, posY, scaleX, scaleY, pivotX, pivotY, rotation, red, blue, green, alpha
        );
    }
    void Render(
        const SpriteBatchID& id,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float texelX,   float texelY, float texelW, float texelH,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    )
    {
        manager.spriteManager.Render(
            id, posX, posY, scaleX, scaleY, texelX, texelY, texelW, texelH, pivotX, pivotY, rotation, red, green, blue, alpha
        );
    }
    void End(const SpriteBatchID& id)
    {
        manager.graphics.SetDepthState(DEPTH_STATE::NONE);
        manager.spriteManager.End(id);
    }
    void Release(const SpriteBatchID& id)
    {
        manager.spriteManager.Release(id);
    }

    /* StaticMesh */
    StaticMeshID LoadStaticMesh(const wchar_t* filePath, bool flipVCoord)
    {
        return manager.staticMeshManager.Load(filePath, flipVCoord);
    }
    void Render(const StaticMeshID& id, const DirectX::XMFLOAT4X4& world, const DirectX::XMFLOAT4& materialColor)
    {
        manager.graphics.SetDepthState(DEPTH_STATE::TEST_AND_WRITE);
        manager.staticMeshManager.Render(id, world, materialColor);
    }
    void Release(const StaticMeshID& id)
    {
        manager.staticMeshManager.Release(id);
    }

    /* Projector */
    void SetProjector(SCENE_CONSTANTS type)
    {
        manager.projector.Setup(type);
    }
    void Project(Camera* camera, const DirectX::XMFLOAT4& lightDirection)
    {
        manager.projector.Project(camera, lightDirection);
    }
    void ResetProjector()
    {
        manager.projector.Reset();
    }

    /* Input */
    void SetAssignData(size_t gamePadNo, const KeyAssignList& keyAssignData, const KeyAssignList& padAssignData)
    {
        manager.inputManager.SetAssignData(gamePadNo, keyAssignData, padAssignData);
    }
    void UpdateInputState()
    {
        manager.inputManager.Update();
    }
    float MouseCursorX()
    {
        return manager.inputManager.MouseCursorX();
    }
    float MouseCursorY()
    {
        return manager.inputManager.MouseCursorY();
    }
    const KeyBit& keyTrigger(size_t gamePadNo)
    {
        return manager.inputManager.keyTrigger(gamePadNo);
    }
    const KeyBit& keyTriggerUp(size_t gamePadNo)
    {
        return manager.inputManager.keyTriggerUp(gamePadNo);
    }
    const KeyBit& keyState(size_t gamePadNo)
    {
        return manager.inputManager.keyState(gamePadNo);
    }

}