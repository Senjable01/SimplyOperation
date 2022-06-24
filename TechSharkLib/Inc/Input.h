#ifndef INCLUDED_INC_INPUT_H
#define INCLUDED_INC_INPUT_H

//------< pragma >------------------------------------------------------------------------
#pragma once
#pragma warning (disable : 4458)

//------< include >-----------------------------------------------------------------------
#include <Windows.h>
#include "../DirectXTK/Inc/Keyboard.h"
#include "../DirectXTK/Inc/GamePad.h"
#include "KeyAssign.h"
#include <map>
#include <vector>
#include <memory>

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
    //      InputState
    // 
    //========================================================================================
    struct InputState
    {
        std::vector<KeyAssign> keyBoardAssigns;
        std::vector<KeyAssign> gamePadAssigns;

        KeyBit keyTrigger;
        KeyBit keyTriggerUp;
        KeyBit keyState;
        KeyBit keyRepeat;
        KeyBit old[8];
        float leftStickX,   leftStickY;
        float rightStickX,  rightStickY;
        float leftTrigger,  rightTrigger;

        InputState() : keyTrigger{}, keyTriggerUp{}, keyState{}, keyRepeat{}, old{},
            leftStickX{0.0f}, leftStickY{0.0f},
            rightStickX{0.0f}, rightStickY{0.0f},
            leftTrigger{0.0f}, rightTrigger{0.0f}
        {
        }
    };

    //========================================================================================
    // 
    //      InputManager
    // 
    //========================================================================================
    class InputManager
    {
    private:
        static constexpr size_t MAX_GAMEPAD_NUM = 4;

        HWND windowHandle;

        std::unique_ptr<DirectX::Keyboard>  keyBoard;   // https://github.com/Microsoft/DirectXTK/wiki/Keyboard
        std::unique_ptr<DirectX::GamePad>   gamePad;    // https://github.com/Microsoft/DirectXTK/wiki/GamePad
        InputState inputStates[MAX_GAMEPAD_NUM];

        POINT mousePos;

    public:
        InputManager() : 
            windowHandle{},
            keyBoard{nullptr}, gamePad{nullptr},
            inputStates{},
            mousePos{}
        {
        }

        void Initialize(HWND windowHandle_);
        void SetAssignData(size_t gamePadNo, const KeyAssignList& keyAssignData, const KeyAssignList& padAssignData);
        void Update();

        InputState* GetInputState(size_t gamePadNo)
        {
            _ASSERT_EXPR(0 <= gamePadNo && gamePadNo < MAX_GAMEPAD_NUM, L"ゲームパッドNoの値が大きすぎるか小さすぎます。");
            return &inputStates[gamePadNo];
        }

        float MouseCursorX() { return static_cast<float>(mousePos.x); }
        float MouseCursorY() { return static_cast<float>(mousePos.y); }
        const KeyBit& keyTrigger(size_t gamePadNo) { return GetInputState(gamePadNo)->keyTrigger; }
        const KeyBit& keyTriggerUp(size_t gamePadNo) { return GetInputState(gamePadNo)->keyTriggerUp; }
        const KeyBit& keyState(size_t gamePadNo) { return GetInputState(gamePadNo)->keyState; }

    };

}

#endif // !INCLUDED_INC_INPUT_H