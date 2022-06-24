#ifndef INCLUDED_INC_CONFIGULATION_H
#define INCLUDED_INC_CONFIGULATION_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< macro >-------------------------------------------------------------------------

// デバッグ機能(0: OFF, 1: ON)
#define DEBUG_MODE (_DEBUG | 1)

// ImGui(0: OFF, 1: ON)
#define USE_IMGUI (1)

// 固定長フレーム(0: 無制限, 1 ~ : FIXED_LENGTH_FRAMEフレームで固定 )
#define FIXED_LENGTH_FRAME (0)

#define BEGIN_SCENE_PATH "../../SourceCode/SceneTitle.h"
#define BEGIN_SCENE_NAME SceneTitle

#endif // !INCLUDED_INC_CONFIGULATION_H