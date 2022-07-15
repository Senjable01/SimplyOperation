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
        TechSharkLib::SetVolume(sound::XWB_VOICE, sound::PH_LOSE01, 1.0f);
        TechSharkLib::SetVolume(sound::XWB_VOICE, sound::DB_RECEPTION, 2.0f);
        TechSharkLib::SetVolume(sound::XWB_VOICE, sound::DB_JUDGE, 1.0f);
        TechSharkLib::SetVolume(sound::XWB_VOICE, sound::WIN01, 2.0f);
    }
}