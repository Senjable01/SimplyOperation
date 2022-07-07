//------< include >-----------------------------------------------------------------------
#include "../Inc/AudioManager.h"

#if _M_X64
#if _DEBUG
#pragma comment (lib, "TechSharkLib/DirectXTK/Lib/x64/Debug/DirectXTKAudioWin8.lib")
#else
#pragma comment (lib, "TechSharkLib/DirectXTK/Lib/x64/Release/DirectXTKAudioWin8.lib")
#endif

#else
#if _DEBUG
#pragma comment (lib, "TechSharkLib/DirectXTK/Lib/x86/Debug/DirectXTKAudioWin8.lib")
#else
#pragma comment (lib, "TechSharkLib/DirectXTK/Lib/x86/Release/DirectXTKAudioWin8.lib")
#endif

#endif

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
    //      AudioManager
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void AudioManager::Initialize()
    {
        DirectX::AUDIO_ENGINE_FLAGS flags = DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_Default;
        #if _DEBUG
        flags |= DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_Debug;

        #endif // _DEBUG
        audioEngine = std::make_unique<DirectX::AudioEngine>(flags);
    }
    void AudioManager::Update(float deltaTime)
    {
        for (auto& music : musics)
        {
            music.Update(deltaTime);
        }
    }
    void AudioManager::Uninitialize()
    {
        for (auto& music : musics)
        {
            music.Stop();
            music.Unload();
        }

        if (audioEngine)
        {
            audioEngine.reset(nullptr);
        }
    }

    void AudioManager::LoadMusic(size_t index, const wchar_t* waveFilePath, float volume)
    {
        GetMusicRef(index)->Load(audioEngine.get(), waveFilePath, volume);
    }
    void AudioManager::LoadSound(size_t index, const wchar_t* xwbFilePath, float volume)
    {
        GetSoundRef(index)->Load(audioEngine.get(), xwbFilePath, volume);
    }

}