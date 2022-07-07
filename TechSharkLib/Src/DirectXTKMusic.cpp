//------< include >-----------------------------------------------------------------------
#include "../Inc/DirectXTKMusic.h"
#include <cfloat>
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

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void DirectXTKMusic::Load(DirectX::AudioEngine* engine, const wchar_t* waveFilePath, float volume)
    {
        if (musicInstance)
            musicInstance.reset(nullptr);
        music.reset(nullptr);
        music = std::make_unique<DirectX::SoundEffect>(engine, waveFilePath);
        baseVolume      = volume;
        currentVolume   = volume;
    }
    void DirectXTKMusic::Update(float deltaTime)
    {
        // ポーズ中、停止中ならリターン
        if (IsInUse() && State() != DirectX::SoundState::PLAYING)
            return;

        // addPerSecがゼロならリターン
        if (-FLT_EPSILON < addPerSec && addPerSec < FLT_EPSILON)
            return;

        // フェードイン
        if (0.0f < addPerSec)
        {
            currentVolume += addPerSec * deltaTime;
            if (fadeVolume < currentVolume)
            {
                currentVolume = fadeVolume;
                addPerSec = 0.0f;
            }
            SetVolume(currentVolume);
        }

        // フェードアウト
        if (addPerSec < 0.0f)
        {
            currentVolume += addPerSec * deltaTime;
            if (currentVolume < fadeVolume)
            {
                currentVolume = fadeVolume;
                addPerSec = 0.0f;
            }
            SetVolume(currentVolume);

            // ボリュームがゼロ以下なら停止
            if (currentVolume < FLT_EPSILON)
            {
                Stop();
            }

        }

    }
    void DirectXTKMusic::Unload()
    {
        if (musicInstance)
            musicInstance.reset(nullptr);
        if (music)
            music.reset(nullptr);
    }

    void DirectXTKMusic::Play(bool isLoop)
    {
        if (!music) return;
        musicInstance   = music->CreateInstance();
        currentVolume   = baseVolume;
        fadeVolume      = currentVolume;
        addPerSec       = 0.0f;
        pitch           = 0.0f;
        pan             = 0.0f;
        musicInstance->SetVolume(currentVolume);
        musicInstance->Play(isLoop); //UNDONE:Play前にボリュームを調整することはできる？
    }
    void DirectXTKMusic::Stop()
    {
        if (!musicInstance) return;
        musicInstance->Stop();
    }
    void DirectXTKMusic::Pause()
    {
        if (!musicInstance) return;
        musicInstance->Pause();
    }
    void DirectXTKMusic::Resume()
    {
        if (!musicInstance) return;
        musicInstance->Resume();
    }
    void DirectXTKMusic::Fade(float sec, float volume)
    {
        fadeVolume = volume;
        addPerSec = (fadeVolume - currentVolume) / sec;
    }

    float DirectXTKMusic::AdjustPan(float addPan)
    {
        pan = (std::max)((std::min)(pan + addPan, 1.0f), -1.0f);
        musicInstance->SetPan(pan);
        return pan;
    }
    float DirectXTKMusic::AdjustPitch(float addPitch)
    {
        pitch = (std::max)((std::min)(pitch + addPitch, 1.0f), -1.0f);
        musicInstance->SetPitch(pitch);
        return pitch;
    }

}