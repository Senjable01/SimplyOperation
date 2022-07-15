//------< include >-----------------------------------------------------------------------
#include "Audio.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"

namespace audio
{
    void LoadAudios()
    {
        TechSharkLib::LoadMusic(music::TITLE_MUSIC, L"Data/Musics/Erosion_Cloud.wav", 0.5f);
        TechSharkLib::LoadMusic(music::GAME, L"Data/Musics/Compete.wav", 0.5f);
        TechSharkLib::LoadSound(sound::XWB_SOUND, L"Data/Sounds/Sounds.xwb", 0.5f);
        TechSharkLib::LoadSound(sound::XWB_VOICE, L"Data/Voices/Voices.xwb", 0.5f);
    }
}