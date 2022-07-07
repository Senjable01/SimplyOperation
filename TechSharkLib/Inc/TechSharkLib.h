#ifndef INCLUDED_TECH_SHARK_LIB_H
#define INCLUDED_TECH_SHARK_LIB_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include "Configulation.h"
#if DEBUG_MODE
#include "DebugTools.h"

#endif // DEBUG_MODE
#if USE_IMGUI
#include "ImGuiCtrl.h"

#endif // USE_IMGUI
#include "GraphicsStateEnum.h"
#include "SpriteID.h"
#include "StaticMeshID.h"
#include "../Inc/ConstantBuffer.h"
#include "../Inc/Camera.h"
#include "KeyAssign.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //------< function >----------------------------------------------------------------------

    /* System */
    void Initialize(const wchar_t* caption, int width, int height, bool isFullscreen = false);
    void Uninitialize();

    /* Window */
    float WindowWidth();
    float WindowHeight();
    void SetDisplayFrameRate(bool displayFrameRate);

    /* Graphics */
    float AspectRatio();
    void ClearView(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 0.0f);
    void Present();
    void SetDepthState(DEPTH_STATE state);
    void SetBlendState(BLEND_STATE state);
    void SetRasterizerState(RASTERIZER_STATE state);

    /* Sprite */
    SpriteID LoadSprite(const wchar_t* filePath);
    void Render(
        const SpriteID& id,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    );
    void Render(
        const SpriteID& id,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float texelX,   float texelY, float texelW, float texelH,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    );
    void Release(const SpriteID& id);

    /* SpriteBatch */
    SpriteBatchID LoadSpriteBatch(const wchar_t* filePath, size_t maxInstance);
    void Begin(const SpriteBatchID& id);
    void Render(
        const SpriteBatchID& id,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    );
    void Render(
        const SpriteBatchID& id,
        float posX,     float posY,
        float scaleX,   float scaleY,
        float texelX,   float texelY, float texelW, float texelH,
        float pivotX,   float pivotY,
        float rotation/*radian*/,
        float red, float green, float blue, float alpha
    );
    void End(const SpriteBatchID& id);
    void Release(const SpriteBatchID& id);

    /* StaticMesh */
    StaticMeshID LoadStaticMesh(const wchar_t* filePath, bool flipVCoord = true);
    void Render(const StaticMeshID& id, const DirectX::XMFLOAT4X4& world, const DirectX::XMFLOAT4& materialColor = {1.0f, 1.0f, 1.0f, 1.0f});
    void Release(const StaticMeshID& id);

    /* Projector */
    void SetProjector(SCENE_CONSTANTS type = SCENE_CONSTANTS::DEFAULT);
    void Project(Camera* camera, const DirectX::XMFLOAT4& lightDirection);
    void ResetProjector();

    /* Input */
    void SetAssignData(size_t gamePadNo, const KeyAssignList& keyAssignData, const KeyAssignList& padAssignData);
    void UpdateInputState();
    float MouseCursorX();
    float MouseCursorY();
    const KeyBit& keyTrigger(size_t gamePadNo);
    const KeyBit& keyTriggerUp(size_t gamePadNo);
    const KeyBit& keyState(size_t gamePadNo);

    /* Audio */
    //UNDONE:09 音楽用、サウンド用のIDを用意する。
    void UpdateAudio(float deltaTime);
    void LoadMusic(int musicNo, const wchar_t* waveFilePath, float volume);
    void Play(int musicNo, bool isLoop);
    void Stop(int musicNo);
    void Pause(int musicNo);
    void Resume(int musicNo);
    void Fade(int musicNo, float sec, float volume);
    float Volume(int musicNo);
    void SetVolume(int musicNo, float volume);
    // DirectX::SoundState State(int musicNo);
    bool IsLoop(int musicNo);
    float Pan(int musicNo);
    float AdjustPan(int musicNo, float addPan);
    float Pitch(int musicNo);
    float AdjustPitch(int musicNo, float addPitch);
    bool IsInUse(int musicNo);
    void Release(int musicNo);
    void LoadSound(int soundNo, const wchar_t* xwbFilePath, float volume);
    void Play(int xwbNo, int trackNo);
    void Stop(int xwbNo, int trackNo);
    void SetVolume(int xwbNo, int trackNo, float volume);

}

#endif // !INCLUDED_TECH_SHARK_LIB_H