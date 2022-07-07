//------< include >-----------------------------------------------------------------------
#include "../Inc/DirectXTKSound.h"
#include <crtdbg.h>

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

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void DirectXTKSound::Load(DirectX::AudioEngine* engine, const wchar_t* xwbFilePath, float volume)
    {
        for (int f = 0; f < MAX_WAVE_NUM; f++)
        {
            for (int w = 0; w < MAX_PLAY_TOGETHER; w++)
            {
                if (soundInstances[f][w])
                    soundInstances[f][w].reset(nullptr);
            }
        }
        waveBank.reset(nullptr);
        waveBank = std::make_unique<DirectX::WaveBank>(engine, xwbFilePath);

        for (auto& vol : soundVolume)
        {
            vol = volume;
        }
    }

    void DirectXTKSound::Play(int trackNo)
    {
        _ASSERT_EXPR(0 <= trackNo && trackNo < MAX_WAVE_NUM, L"trackNoが定義域外");

        // 同時再生数がMAX_PLAY_TOGETHERに達していなければ再生
        for (int w = 0; w < MAX_PLAY_TOGETHER; w++)
        {
            auto& soundInstance = soundInstances[trackNo][w];

            if (soundInstance)
            {
                DirectX::SoundState state = soundInstance->GetState();
                if (state == DirectX::SoundState::STOPPED)
                    continue;
            }

            soundInstance = waveBank->CreateInstance(trackNo);
            if (soundInstance)
            {
                soundInstance->SetVolume(soundVolume[trackNo]);
                soundInstance->Play();
                break;
            }
        }
    }
    void DirectXTKSound::Stop(int trackNo)
    {
        _ASSERT_EXPR(0 < trackNo && trackNo < MAX_WAVE_NUM, L"trackNoが定義域外");

        for (int w = 0; w < MAX_PLAY_TOGETHER; w++)
        {
            if (soundInstances[trackNo][w])
            {
                soundInstances[trackNo][w]->Stop();
            }
        }
    }

    void DirectXTKSound::SetVolume(int trackNo, float volume)
    {
        _ASSERT_EXPR(0 < trackNo && trackNo < MAX_WAVE_NUM, L"trackNoが定義域外");
        soundVolume[trackNo] = volume;
    }

}