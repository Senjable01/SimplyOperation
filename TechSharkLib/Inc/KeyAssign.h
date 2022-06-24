#ifndef INCLUDED_INC_KEY_ASSIGN_H
#define INCLUDED_INC_KEY_ASSIGN_H

//------< include >---------------------------------------------------------------------------------
#include <initializer_list>
#include <bitset>
#include <string>

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //------< constant >----------------------------------------------------------------------

    static constexpr size_t MAX_KEY_BIT_NO = 32;

    //------< using >-------------------------------------------------------------------------

    using KeyBit = unsigned int;

    //========================================================================================
    // 
    //      BIT_NO
    // 
    //========================================================================================
    enum class BIT_NO : KeyBit {
        BIT_00, BIT_01, BIT_02, BIT_03, BIT_04, BIT_05, BIT_06, BIT_07,
        BIT_08, BIT_09, BIT_10, BIT_11, BIT_12, BIT_13, BIT_14, BIT_15,
        BIT_16, BIT_17, BIT_18, BIT_19, BIT_20, BIT_21, BIT_22, BIT_23,
        BIT_24, BIT_25, BIT_26, BIT_27, BIT_28, BIT_29, BIT_30, BIT_31
    };

    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------

    inline KeyBit operator<< (int one, BIT_NO shift)
    {
        return (one << static_cast<unsigned int>(shift));
    }
    inline KeyBit operator& (KeyBit src, BIT_NO dst)
    {
        return src & (1 << dst);
    }
    inline KeyBit operator| (KeyBit src, BIT_NO dst)
    {
        return src | (1 << dst);
    }
    inline KeyBit operator^ (KeyBit src, BIT_NO dst)
    {
        return src ^ (1 << dst);
    }
    inline KeyBit operator~ (BIT_NO shift)
    {
        return ~(1 << shift);
    }
    inline KeyBit operator& (BIT_NO src, BIT_NO dst)
    {
        return (1 << src) & (1 << dst);
    }
    inline KeyBit operator| (BIT_NO src, BIT_NO dst)
    {
        return (1 << src) | (1 << dst);
    }
    inline KeyBit operator^ (BIT_NO src, BIT_NO dst)
    {
        return (1 << src) ^ (1 << dst);
    }

    //========================================================================================
    // 
    //      KeyAssign
    // 
    //========================================================================================
    struct KeyAssign
    {
        unsigned int    bitNo;
        unsigned int    keyCode;

        KeyAssign() : bitNo{0}, keyCode{0} {}
        KeyAssign(unsigned int bitNo, unsigned int key) : bitNo{bitNo}, keyCode{key} {}
        KeyAssign(BIT_NO bitNo, unsigned int key) :
            bitNo{static_cast<unsigned int>(bitNo)}, keyCode{key}
        {
        }
    };

    //------< using >-------------------------------------------------------------------------

    using KeyAssignList = std::initializer_list<KeyAssign>;

    //========================================================================================
    // 
    //      KeyCodes
    // 
    //========================================================================================
    class KeyCodes
    {
    public:
        // キーボード
        static const unsigned int None;
        static const unsigned int Back;
        static const unsigned int Tab;
        static const unsigned int Enter;
        static const unsigned int Pause;
        static const unsigned int CapsLock;
        static const unsigned int Kana;
        static const unsigned int Kanji;
        static const unsigned int Escape;
        static const unsigned int ImeConvert;
        static const unsigned int ImeNoConvert;
        static const unsigned int Space;
        static const unsigned int PageUp;
        static const unsigned int PageDown;
        static const unsigned int End;
        static const unsigned int Home;
        static const unsigned int Left;
        static const unsigned int Up;
        static const unsigned int Right;
        static const unsigned int Down;
        static const unsigned int Select;
        static const unsigned int Print;
        static const unsigned int Execute;
        static const unsigned int PrintScreen;
        static const unsigned int Insert;
        static const unsigned int Delete;
        static const unsigned int Help;
        static const unsigned int D0;
        static const unsigned int D1;
        static const unsigned int D2;
        static const unsigned int D3;
        static const unsigned int D4;
        static const unsigned int D5;
        static const unsigned int D6;
        static const unsigned int D7;
        static const unsigned int D8;
        static const unsigned int D9;
        static const unsigned int A;
        static const unsigned int B;
        static const unsigned int C;
        static const unsigned int D;
        static const unsigned int E;
        static const unsigned int F;
        static const unsigned int G;
        static const unsigned int H;
        static const unsigned int I;
        static const unsigned int J;
        static const unsigned int K;
        static const unsigned int L;
        static const unsigned int M;
        static const unsigned int N;
        static const unsigned int O;
        static const unsigned int P;
        static const unsigned int Q;
        static const unsigned int R;
        static const unsigned int S;
        static const unsigned int T;
        static const unsigned int U;
        static const unsigned int V;
        static const unsigned int W;
        static const unsigned int X;
        static const unsigned int Y;
        static const unsigned int Z;
        static const unsigned int LeftWindows;
        static const unsigned int RightWindows;
        static const unsigned int Apps;
        static const unsigned int Sleep;
        static const unsigned int NumPad0;
        static const unsigned int NumPad1;
        static const unsigned int NumPad2;
        static const unsigned int NumPad3;
        static const unsigned int NumPad4;
        static const unsigned int NumPad5;
        static const unsigned int NumPad6;
        static const unsigned int NumPad7;
        static const unsigned int NumPad8;
        static const unsigned int NumPad9;
        static const unsigned int Multiply;
        static const unsigned int Add;
        static const unsigned int Separator;
        static const unsigned int Subtract;
        static const unsigned int Decimal;
        static const unsigned int Divide;
        static const unsigned int F1;
        static const unsigned int F2;
        static const unsigned int F3;
        static const unsigned int F4;
        static const unsigned int F5;
        static const unsigned int F6;
        static const unsigned int F7;
        static const unsigned int F8;
        static const unsigned int F9;
        static const unsigned int F10;
        static const unsigned int F11;
        static const unsigned int F12;
        static const unsigned int F13;
        static const unsigned int F14;
        static const unsigned int F15;
        static const unsigned int F16;
        static const unsigned int F17;
        static const unsigned int F18;
        static const unsigned int F19;
        static const unsigned int F20;
        static const unsigned int F21;
        static const unsigned int F22;
        static const unsigned int F23;
        static const unsigned int F24;
        static const unsigned int NumLock;
        static const unsigned int Scroll;
        static const unsigned int LeftShift;
        static const unsigned int RightShift;
        static const unsigned int LeftControl;
        static const unsigned int RightControl;
        static const unsigned int LeftAlt;
        static const unsigned int RightAlt;
        static const unsigned int BrowserBack;
        static const unsigned int BrowserForward;
        static const unsigned int BrowserRefresh;
        static const unsigned int BrowserStop;
        static const unsigned int BrowserSearch;
        static const unsigned int BrowserFavorites;
        static const unsigned int BrowserHome;
        static const unsigned int VolumeMute;
        static const unsigned int VolumeDown;
        static const unsigned int VolumeUp;
        static const unsigned int MediaNextTrack;
        static const unsigned int MediaPreviousTrack;
        static const unsigned int MediaStop;
        static const unsigned int MediaPlayPause;
        static const unsigned int LaunchMail;
        static const unsigned int SelectMedia;
        static const unsigned int LaunchApplication1;
        static const unsigned int LaunchApplication2;
        static const unsigned int OemSemicolon;
        static const unsigned int OemPlus;
        static const unsigned int OemComma;
        static const unsigned int OemMinus;
        static const unsigned int OemPeriod;
        static const unsigned int OemQuestion;
        static const unsigned int OemTilde;
        static const unsigned int OemOpenBrackets;
        static const unsigned int OemPipe;
        static const unsigned int OemCloseBrackets;
        static const unsigned int OemQuotes;
        static const unsigned int Oem8;
        static const unsigned int OemBackslash;
        static const unsigned int ProcessKey;
        static const unsigned int OemCopy;
        static const unsigned int OemAuto;
        static const unsigned int OemEnlW;
        static const unsigned int Attn;
        static const unsigned int Crsel;
        static const unsigned int Exsel;
        static const unsigned int EraseEof;
        static const unsigned int Play;
        static const unsigned int Zoom;
        static const unsigned int Pa1;
        static const unsigned int OemClear;

        // マウス
        static const unsigned int MouseLeft;
        static const unsigned int MouseMiddle;
        static const unsigned int MouseRight;

        // ゲームパッド
        static const unsigned int PadUp;
        static const unsigned int PadDown;
        static const unsigned int PadLeft;
        static const unsigned int PadRight;
        static const unsigned int PadA;
        static const unsigned int PadB;
        static const unsigned int PadX;
        static const unsigned int PadY;
        static const unsigned int PadLeftStick;
        static const unsigned int PadRightStick;
        static const unsigned int PadLeftShoulder;
        static const unsigned int PadRightShoulder;
        static const unsigned int PadBack;   // back / view
        static const unsigned int PadStart;  // start / menu

    };

}

#endif // !INCLUDED_INC_KEY_ASSIGN_H