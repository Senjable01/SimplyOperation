#ifndef INCLUDED_INC_DIRECTXTK_SOUND_H
#define INCLUDED_INC_DIRECTXTK_SOUND_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning (disable : 26812)

//------< include >-----------------------------------------------------------------------
#include "../DirectXTK/Inc/Audio.h"
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
    //========================================================================================
    // 
    //      DirectXTKSound
    // 
    //========================================================================================
    class DirectXTKSound
    {
    public:
        static constexpr int MAX_WAVE_NUM       = 128;  // xwbファイル一つ当たりの最大waveファイル数
        static constexpr int MAX_PLAY_TOGETHER  = 8;    // wave一つあたりの最大同時再生数

    private:
        std::unique_ptr<DirectX::WaveBank>              waveBank;
        std::unique_ptr<DirectX::SoundEffectInstance>   soundInstances[MAX_WAVE_NUM][MAX_PLAY_TOGETHER];
        
        float soundVolume[MAX_WAVE_NUM];

    public:
        DirectXTKSound() : waveBank{nullptr}, soundInstances{nullptr}, soundVolume{0.0f} {}

        void Load(DirectX::AudioEngine* engine, const wchar_t* xwbFilePath, float volume);
        
        void Play(int trackNo);
        void Stop(int trackNo);

        void SetVolume(int trackNo, float volume);
        bool IsInUse() const noexcept { return static_cast<bool>(waveBank); }

    };
}

#endif // !INCLUDED_INC_DIRECTXTK_SOUND_H