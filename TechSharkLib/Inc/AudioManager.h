#ifndef INCLUDED_INC_AUDIO_MANAGER_H
#define INCLUDED_INC_AUDIO_MANAGER_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include "DirectXTKMusic.h"
#include "DirectXTKSound.h"
#include <array>

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
    //      AudioManagee
    // 
    //========================================================================================
    class AudioManager
    {
    public:
        static constexpr int MAX_MUSIC_NUM  = 32; // �ő剹�y��
        static constexpr int MAX_XWB_NUM    = 16; // �ő�xwb�t�@�C����

    private:
        std::unique_ptr<DirectX::AudioEngine>       audioEngine;
        std::array<DirectXTKMusic, MAX_MUSIC_NUM>   musics;
        std::array<DirectXTKSound, MAX_XWB_NUM>     sounds;

    public:
        AudioManager() : audioEngine{nullptr}, musics{}, sounds{} {}

        // DirectX�̏����ݒ��Ɏ��s���邱��
        void Initialize();
        void Update(float deltaTime);
        void Uninitialize();

        void LoadMusic(size_t index, const wchar_t* waveFilePath, float volume);
        void LoadSound(size_t index, const wchar_t* xwbFilePath, float volume);

        DirectXTKMusic* GetMusicRef(size_t index) { return &(musics.at(index)); }
        DirectXTKSound* GetSoundRef(size_t index) { return &(sounds.at(index)); }

    };
}

#endif // !INCLUDED_INC_AUDIO_MANAGER_H