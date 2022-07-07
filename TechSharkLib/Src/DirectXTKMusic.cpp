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
        // �|�[�Y���A��~���Ȃ烊�^�[��
        if (IsInUse() && State() != DirectX::SoundState::PLAYING)
            return;

        // addPerSec���[���Ȃ烊�^�[��
        if (-FLT_EPSILON < addPerSec && addPerSec < FLT_EPSILON)
            return;

        // �t�F�[�h�C��
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

        // �t�F�[�h�A�E�g
        if (addPerSec < 0.0f)
        {
            currentVolume += addPerSec * deltaTime;
            if (currentVolume < fadeVolume)
            {
                currentVolume = fadeVolume;
                addPerSec = 0.0f;
            }
            SetVolume(currentVolume);

            // �{�����[�����[���ȉ��Ȃ��~
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
        musicInstance->Play(isLoop); //UNDONE:Play�O�Ƀ{�����[���𒲐����邱�Ƃ͂ł���H
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