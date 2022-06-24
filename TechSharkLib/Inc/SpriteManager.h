#ifndef INCLUDED_INC_TEXTURE_MANAGER_H
#define INCLUDED_INC_TEXTURE_MANAGER_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning (disable : 4458)

//------< include >-----------------------------------------------------------------------
#include "Sprite.h"
#include "SpriteID.h"
#include <map>
#include <memory>
#include <set>

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
    class SpriteManager
    {
    private:
        ID3D11Device*           device;             // device(キャッシュ用)
        ID3D11DeviceContext*    immediateContext;   // immediateContext(キャッシュ用)

        std::map<SpriteID, std::unique_ptr<Sprite>> spriteMap;
        std::map<SpriteBatchID, std::unique_ptr<SpriteBatch>> spriteBatchMap;

        static unsigned int nextSpriteId;
        static unsigned int nextSpriteBatchId;

    public:
        SpriteManager() : 
            device{nullptr}, immediateContext{nullptr}
        {
        }
        SpriteManager(const SpriteManager&) = delete;
        SpriteManager& operator=(const SpriteManager&) = delete;
        SpriteManager(SpriteManager&&) noexcept = delete;
        SpriteManager& operator=(SpriteManager&&) noexcept = delete;
        ~SpriteManager() { ReleaseAll(); }

        void Initialize(ID3D11Device* device, ID3D11DeviceContext* immediateContext);

        SpriteID LoadSprite(const wchar_t* filePath);
        SpriteBatchID LoadSpriteBatch(const wchar_t* filePath, size_t maxInstance);

        void Render(
            SpriteID id,
            float posX,     float posY,
            float scaleX,   float scaleY,
            float pivotX,   float pivotY,
            float rotation/*radian*/,
            float red, float green, float blue, float alpha
        );
        void Render(
            SpriteID id,
            float posX,     float posY,
            float scaleX,   float scaleY,
            float texelX,   float texelY, float texelW,   float texelH,
            float pivotX,   float pivotY,
            float rotation/*radian*/,
            float red, float green, float blue, float alpha
        );
        void Begin(SpriteBatchID id);
        void Render(
            SpriteBatchID id,
            float posX,     float posY,
            float scaleX,   float scaleY,
            float pivotX,   float pivotY,
            float rotation/*radian*/,
            float red, float green, float blue, float alpha
        );
        void Render(
            SpriteBatchID id,
            float posX,     float posY,
            float scaleX,   float scaleY,
            float texelX,   float texelY, float texelW,   float texelH,
            float pivotX,   float pivotY,
            float rotation/*radian*/,
            float red, float green, float blue, float alpha
        );
        void End(SpriteBatchID id);

        void Release(SpriteID id);
        void Release(SpriteBatchID);
        void ReleaseAll();
    };
}

#endif // !INCLUDED_INC_TEXTURE_MANAGER_H