#ifndef INCLUDED_INC_DIRECTXTK_MUSIC_H
#define INCLUDED_INC_DIRECTXTK_MUSIC_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning (disable : 26812)

//------< include >-----------------------------------------------------------------------
#include "../DirectXTK/Inc/Audio.h"
#include <memory>
#include <algorithm>

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
    //      DirectXTKMusic
    // 
    //========================================================================================
    class DirectXTKMusic
    {
    private:
        std::unique_ptr<DirectX::SoundEffect>           music;
        std::unique_ptr<DirectX::SoundEffectInstance>   musicInstance;
        float baseVolume;
        float currentVolume;
        float fadeVolume;
        float addPerSec;
        float pitch;
        float pan;

    public:
        DirectXTKMusic() : 
            music{nullptr}, musicInstance{nullptr},
            baseVolume{0.5f}, currentVolume{0.0f}, fadeVolume{0.0f},
            addPerSec{0.0f}, pitch{0.0f}, pan{0.0f}
        {
        }

        void Load(DirectX::AudioEngine* engine, const wchar_t* waveFilePath, float volume);
        void Update(float deltaTime);
        void Unload();

        void Play(bool isLoop);
        void Stop();
        void Pause();
        void Resume();
        void Fade(float sec, float volume);

        float Volume() const noexcept { return currentVolume; }
        void SetVolume(float volume)
        {
            if (!musicInstance) return;
            currentVolume = volume;
            musicInstance->SetVolume(volume);
        }
        DirectX::SoundState State()
        {
            if (music->IsInUse() == false)
                return DirectX::SoundState::STOPPED;
            return musicInstance->GetState();
        }
        bool IsLoop() { return musicInstance->IsLooped(); }
        float Pan() const noexcept { return pan; }
        float AdjustPan(float addPan);
        float Pitch() const noexcept { return pitch; }
        float AdjustPitch(float addPitch);
        const WAVEFORMATEX* GetFormat() { return music->GetFormat(); }
        bool IsInUse()
        {
            if (!music) return false;
            return music->IsInUse();
        }

    };
}

#endif // !INCLUDED_INC_DIRECTXTK_MUSIC_H