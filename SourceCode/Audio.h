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

    constexpr int RSP_PREPARE   = 0; // �ŏ��̓O�[
    constexpr int RSP_RECEPTION = 1; // ����񂯂�
    constexpr int RSP_JUDGE     = 2; // �|���I
    constexpr int PH_RECEPTION  = 3; // (��������)
    constexpr int PH_WIN01      = 4; // (�������� ... Entrant01 Win)
    constexpr int PH_LOSE01     = 5; // (�������� ... Entrant01 Lose)
    constexpr int DB_RECEPTION  = 6; // ������������
    constexpr int DB_JUDGE      = 7; // �z�C�I
    constexpr int WIN01         = 8; // (�ŏI ... Entrant01 Win)
    constexpr int LOSE01        = 9; // (�ŏI ... Entrant01 Lose)
}

#endif // !INCLUDED_AUDIO_H