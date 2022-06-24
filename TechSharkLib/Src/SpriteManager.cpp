//------< include >-----------------------------------------------------------------------
#include "../Inc/SpriteManager.h"
#include "../Inc/Configulation.h"
#if DEBUG_MODE
#include "../Inc/DebugTools.h"

#else
#include <crtdbg.h>

#endif // DEBUG_MODE

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //====================================================================================
    // 
    //      SpriteManager
    // 
    //====================================================================================

    //--------------------------------------------------------------------------
    // member function
    //--------------------------------------------------------------------------

    void SpriteManager::Initialize(ID3D11Device* device, ID3D11DeviceContext* immediateContext)
    {
        _ASSERT_EXPR(device != nullptr, L"deviceがnullptr");
        _ASSERT_EXPR(immediateContext != nullptr, L"immediateContextがnullptr");
        this->device            = device;
        this->immediateContext  = immediateContext;
    }

    SpriteID SpriteManager::LoadSprite(const wchar_t* filePath)
    {
        SpriteID id = SpriteID{SpriteManager::nextSpriteId++};
        spriteMap.emplace(id, std::make_unique<Sprite>(device, filePath));
        return id;
    }
    SpriteBatchID SpriteManager::LoadSpriteBatch(const wchar_t* filePath, size_t maxInstance)
    {
        SpriteBatchID id = SpriteBatchID{SpriteManager::nextSpriteBatchId++};
        spriteBatchMap.emplace(id, std::make_unique<SpriteBatch>(device, filePath, maxInstance));
        return id;
    }

    void SpriteManager::Render(
        SpriteID id,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    )
    {
        spriteMap.at(id)->Render(
            immediateContext,
            posX,   posY,
            scaleX, scaleY,
            pivotX, pivotY,
            rotation,
            red, green, blue, alpha
        );
    }
    void SpriteManager::Render(
        SpriteID id,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float texelX,   float texelY, float texelW,   float texelH,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    )
    {
        spriteMap.at(id)->Render(
            immediateContext,
            posX,   posY,
            scaleX, scaleY,
            texelX, texelY, texelW, texelH,
            pivotX, pivotY,
            rotation,
            red, green, blue, alpha
        );
    }
    void SpriteManager::Begin(SpriteBatchID id)
    {
        spriteBatchMap.at(id)->Begin(immediateContext);
    }
    void SpriteManager::Render(
        SpriteBatchID id,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    )
    {
        spriteBatchMap.at(id)->Render(
            immediateContext,
            posX,   posY,
            scaleX, scaleY,
            pivotX, pivotY,
            rotation,
            red, green, blue, alpha
        );
    }
    void SpriteManager::Render(
        SpriteBatchID id,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float texelX,   float texelY, float texelW,   float texelH,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    )
    {
        spriteBatchMap.at(id)->Render(
            immediateContext,
            posX,   posY,
            scaleX, scaleY,
            texelX, texelY, texelW, texelH,
            pivotX, pivotY,
            rotation,
            red, green, blue, alpha
        );
    }
    void SpriteManager::End(SpriteBatchID id)
    {
        spriteBatchMap.at(id)->End(immediateContext);
    }

    void SpriteManager::Release(SpriteID id)
    {
        spriteMap.erase(id);
    }
    void SpriteManager::Release(SpriteBatchID id)
    {
        spriteBatchMap.erase(id);
    }

    void SpriteManager::ReleaseAll()
    {
        #if DEBUG_MODE
        size_t remainNum = spriteMap.size();
        if (remainNum)
        {
            ExpressDebugLog("<WARNING>: ", remainNum, L"個のSpriteがリリースされていませんでした。");
        }
        remainNum = spriteBatchMap.size();
        if (remainNum)
        {
            ExpressDebugLog("<WARNING>: ", remainNum, L"個のSpriteBatchがリリースされていませんでした。");
        }

        #endif // DEBUG_MODE
        spriteMap.clear();
        spriteBatchMap.clear();
    }

    //--------------------------------------------------------------------------
    // instance
    //--------------------------------------------------------------------------

    unsigned int SpriteManager::nextSpriteId        = ERROR_SPRITE_ID + 1;
    unsigned int SpriteManager::nextSpriteBatchId   = BATCH_BEGIN;

}