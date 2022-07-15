//------< include >-----------------------------------------------------------------------
#include "../Inc/Input.h"
#include "../Inc/Configulation.h"
#if DEBUG_MODE
#include "../Inc/DebugTools.h"

#endif // DEBUG_MODE
#include <cmath>

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
    //      InputManager
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void InputManager::Initialize(HWND windowHandle_)
    {
        windowHandle = windowHandle_;

        keyBoard    = std::make_unique<DirectX::Keyboard>();
        gamePad     = std::make_unique<DirectX::GamePad>();
        for (auto& inputState : inputStates)
        {
            inputState = {};
        }
        mousePos    = {0, 0};
    }

    void InputManager::SetAssignData(size_t gamePadNo, const KeyAssignList& keyAssignData, const KeyAssignList& padAssignData)
    {
        //////// キーボードのキーアサイン ////////

        /* 初期設定 */
        std::vector<KeyAssign>& keyBoardAssigns = GetInputState(gamePadNo)->keyBoardAssigns;
        keyBoardAssigns.clear();
        keyBoardAssigns.reserve(keyAssignData.size());
        size_t registerNum = 0;

        /* 登録 */
        for (auto itr = keyAssignData.begin(), end = keyAssignData.end(); itr != end; itr++)
        {
            if (MAX_KEY_BIT_NO <= itr->bitNo)
            {
                #if DEBUG_MODE
                ExpressDebugLog(L"<WARNING> キーアサインで指定されたbitNoがオーバーフローしています。最大値まで縮小します。");

                #endif // DEBUG_MODE
                keyBoardAssigns.emplace_back(static_cast<unsigned int>(MAX_KEY_BIT_NO - 1), itr->keyCode);
            }
            else
            {
                keyBoardAssigns.emplace_back(*itr);
            }
        }

        //////// ゲームパッドのキーアサイン ////////

        /* 初期設定 */
        std::vector<KeyAssign>& padAssigns = GetInputState(gamePadNo)->gamePadAssigns;
        padAssigns.clear();
        padAssigns.reserve(padAssignData.size());
        registerNum = 0;

        /* 登録 */
        for (auto itr = padAssignData.begin(), end = padAssignData.end(); itr != end; itr++)
        {
            if (MAX_KEY_BIT_NO <= itr->bitNo)
            {
                #if DEBUG_MODE
                ExpressDebugLog(L"<WARNING> キーアサインで指定されたbitNoがオーバーフローしています。最大値まで縮小します。");

                #endif // DEBUG_MODE
                padAssigns.emplace_back(static_cast<unsigned int>(MAX_KEY_BIT_NO - 1), itr->keyCode);
            }
            else
            {
                padAssigns.emplace_back(*itr);
            }
        }
    }

    void InputManager::Update()
    {
        //////// インプットの状態を取得 ////////
        DirectX::Keyboard::State keyBoard = this->keyBoard->GetState();
        DirectX::GamePad::State gamePads[MAX_GAMEPAD_NUM] = {};
        for (int i = 0; i < MAX_GAMEPAD_NUM; i++)
        {
            gamePads[i] = this->gamePad->GetState(i);
        }

        //////// 入力状態を更新 ////////
        for (int i = 0; i < MAX_GAMEPAD_NUM; i++)
        {
            InputState& inputState      = inputStates[i];
            KeyBit      oldKeyState     = inputState.keyState; // 前フレームの状態
            inputState.keyState = 0;

            /* マウス / キーボードの入力状態 */
            for (auto itr = inputState.keyBoardAssigns.begin(), end = inputState.keyBoardAssigns.end(); itr != end; itr++)
            {
                // マウス
                if (itr->keyCode == VK_LBUTTON || itr->keyCode == VK_MBUTTON || itr->keyCode == VK_RBUTTON)
                {
                    if (GetAsyncKeyState(itr->keyCode) < 0)
                    {
                        inputState.keyState |= (1 << itr->bitNo);
                    }
                }
                // キーボード
                else
                {
                    if (keyBoard.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(itr->keyCode)))
                    {
                        inputState.keyState |= (1 << itr->bitNo);
                    }
                }
            }

            /* ゲームパッドの入力状態 */
            if (gamePads[i].IsConnected())
            {
                union Buttons {
                    DirectX::GamePad::Buttons buttons;
                    bool isKeyDown[sizeof(DirectX::GamePad::Buttons) / sizeof(bool)];
                } buttons;

                for (auto itr = inputState.gamePadAssigns.begin(), end = inputState.gamePadAssigns.end(); itr != end; itr++)
                {
                    buttons.buttons = gamePads[i].buttons;

                    // ボタン
                    if (KeyCodes::PadA <= itr->keyCode)
                    {
                        if (buttons.isKeyDown[itr->keyCode - KeyCodes::PadA])
                        {
                            inputState.keyState |= (1 << itr->bitNo);
                        }
                    }
                    // Dパッド
                    else
                    {
                        if (buttons.isKeyDown[itr->keyCode])
                        {
                            inputState.keyState |= (1 << itr->bitNo);
                        }
                    }
                }

                auto SafeGetParameter = [](const float stick) -> float {
                    if (std::isnan(stick))
                    {
                        return 0.0f;
                    }
                    else
                    {
                        return stick;
                    }
                };

                // ジョイスティック
                inputState.leftStickX   = SafeGetParameter(gamePads[i].thumbSticks.leftX);
                inputState.leftStickY   = SafeGetParameter(gamePads[i].thumbSticks.leftY);
                inputState.rightStickX  = SafeGetParameter(gamePads[i].thumbSticks.rightX);
                inputState.rightStickY  = SafeGetParameter(gamePads[i].thumbSticks.rightY);
                // ジョイスティックのパラメーターをチェック
                if (std::isnan(inputState.leftStickX))  inputState.leftStickX   = 0.0f;
                if (std::isnan(inputState.leftStickY))  inputState.leftStickY   = 0.0f;
                if (std::isnan(inputState.rightStickX)) inputState.rightStickX  = 0.0f;
                if (std::isnan(inputState.rightStickY)) inputState.rightStickY  = 0.0f;

                // トリガー
                inputState.leftTrigger  = SafeGetParameter(gamePads[i].triggers.left);
                inputState.rightTrigger = SafeGetParameter(gamePads[i].triggers.right);
            }

            /* ステート以外を更新 */
            inputState.keyTrigger   = (~oldKeyState) & inputState.keyState;
            inputState.keyTriggerUp = oldKeyState & (~inputState.keyState);

            //UNDONE:05 キーのリピート

        }

        //////// マウスカーソル ////////
        GetCursorPos(&mousePos);
        ScreenToClient(windowHandle, &mousePos);

    }
}