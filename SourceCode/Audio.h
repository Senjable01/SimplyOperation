#ifndef INCLUDED_AUDIO_H
#define INCLUDED_AUDIO_H

namespace audio
{
    void LoadAudios();
}

namespace music
{
    constexpr int TITLE_MUSIC   = 0;
    constexpr int GAME          = 1;
}

namespace sound
{
    constexpr int XWB_SOUND = 0;
    constexpr int XWB_VOICE = 1;

    constexpr int DECISION  = 0;
    constexpr int RAP       = 1;
    constexpr int EXPLOSIVE = 2;

    constexpr int RSP_PREPARE   = 0; // 最初はグー
    constexpr int RSP_RECEPTION = 1; // じゃんけん
    constexpr int RSP_JUDGE     = 2; // ポン！
    constexpr int PH_RECEPTION  = 3; // (押し合い)
    constexpr int PH_WIN01      = 4; // (押し合い ... Entrant01 Win)
    constexpr int PH_LOSE01     = 5; // (押し合い ... Entrant01 Lose)
    constexpr int DB_RECEPTION  = 6; // あっち向いて
    constexpr int DB_JUDGE      = 7; // ホイ！
    constexpr int WIN01         = 8; // (最終 ... Entrant01 Win)
    constexpr int LOSE01        = 9; // (最終 ... Entrant01 Lose)
}

#endif // !INCLUDED_AUDIO_H