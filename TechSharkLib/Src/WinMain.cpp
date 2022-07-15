//------< include >-----------------------------------------------------------------------
#include <Windows.h>
#include "../Inc/Window.h"
#include "../Inc/TechSharkLib.h"
#include "../Inc/Scene.h"
#include "../Inc/Configulation.h"
#include BEGIN_SCENE_PATH
#include "../../SourceCode/Audio.h"

//------< pragma >------------------------------------------------------------------------
#pragma warning (disable : 4100)

// UNIT01 WindowsAPI
int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR cmdLine, _In_ int cmdShow)
{
    TechSharkLib::Initialize(L"‚¶‚á‚ñ‚Ù‚¢", 1280, 720);
    audio::LoadAudios();
    TechSharkLib::SceneManager::GetInstance()->Execute<BEGIN_SCENE_NAME>();
    TechSharkLib::Uninitialize();
    return 0;
}