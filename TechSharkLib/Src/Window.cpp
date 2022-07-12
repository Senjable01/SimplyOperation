//------< include >-----------------------------------------------------------------------
#include "../Inc/Window.h"
#include <crtdbg.h>
#include <ctime>
#include "../Inc/WindowProcedure.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    namespace
    {
        LPCTSTR CLASS_NAME = L"TechSHArKLIb";
    }

    //========================================================================================
    // 
    //      Window
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

	HWND Window::Initialize(LPCTSTR caption, const LONG width, const LONG height)
	{
		_ASSERT_EXPR(0 < width * height, L"�E�B���h�E�T�C�Y���s�K�؂ł��B");

		#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		#endif

		srand(static_cast<unsigned int>(std::time(nullptr)));

		this->width = width;
		this->height = height;

		//////// �E�B���h�E���̓o�^ ////////
		// UNIT03 Section2
		{
			WNDCLASSEXW windowSettings{};
			windowSettings.cbSize			= sizeof(WNDCLASSEX);
			windowSettings.style			= CS_HREDRAW | CS_VREDRAW;
			windowSettings.lpfnWndProc		= WindowProcedure;
			windowSettings.cbClsExtra		= 0;
			windowSettings.cbWndExtra		= 0;
			windowSettings.hInstance		= GetModuleHandle(NULL);
			windowSettings.hIcon			= NULL;
			windowSettings.hCursor			= LoadCursor(NULL, IDC_ARROW);
			windowSettings.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
			windowSettings.lpszMenuName		= NULL;
			windowSettings.lpszClassName	= CLASS_NAME;
			windowSettings.hIconSm			= NULL;

			#if _DEBUG
			ATOM result = RegisterClassExW(&windowSettings);
			_ASSERT_EXPR(result, L"�E�B���h�E���̓o�^�Ɏ��s");

			#else
			RegisterClassExW(&windowSettings);

			#endif // _DEBUG
		}

		//////// �E�B���h�E�̍쐬(���T�C�Y) ////////
		// UNIT03 Section3
		RECT windowArea = {
			0L,		0L,
			width,	height
		};
		/* �N���C�A���g�̈���������ă��T�C�Y */
		AdjustWindowRect(
			&windowArea,
			WS_OVERLAPPEDWINDOW,
			FALSE
		);
		/* �E�B���h�E���쐬 */
		windowHandle = CreateWindowExW(
			0,
			CLASS_NAME,
			caption,
			WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE,
			CW_USEDEFAULT,						CW_USEDEFAULT,
			windowArea.right - windowArea.left, windowArea.bottom - windowArea.top,
			NULL,
			NULL,
			GetModuleHandle(NULL),
			NULL
		);

		//////// �E�B���h�E��\�� ////////
		// UNIT03 Section4
		ShowWindow(windowHandle, SW_SHOWDEFAULT);

		return windowHandle;

	}

	void Window::Uninitialize()
	{
		// �I������
		UnregisterClass(CLASS_NAME, GetModuleHandle(NULL));
	}

	//---------------------------------------------------------------------------------------
	// instance
	//---------------------------------------------------------------------------------------

	Window Window::instance_;

}