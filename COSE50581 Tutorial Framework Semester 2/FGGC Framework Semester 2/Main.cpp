#include "Application.h"

void GameLoopDelay(float frameStartTime)
{
	//  calculate time elapsed from start of processing current frame
	float frameProcessingTime, currentFrameTime;

	currentFrameTime = GetTickCount();

	frameProcessingTime = currentFrameTime - frameStartTime;

	if (frameProcessingTime < 16.67f)
	{
		//  delay so that time interval between adjacent frames is equal to preset value
		Sleep(16.67f - frameProcessingTime);
	}
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	Application * theApp = new Application();

	if (FAILED(theApp->Initialise(hInstance, nCmdShow)))
	{
		return -1;
	}

    // Main message loop
    MSG msg = {0};

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
			bool handled = false;

			if (msg.message >= WM_KEYFIRST && msg.message <= WM_KEYLAST)
			{
				handled = theApp->HandleKeyboard(msg);
			}
			else if (WM_QUIT == msg.message)
				break;

			if (!handled)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
        else
        {
			float frameStartTime = GetTickCount();

			if (GetAsyncKeyState(VK_ESCAPE))
			{
				break;
			}

			theApp->Update();
            theApp->Draw();

			GameLoopDelay(frameStartTime);
        }
    }

	delete theApp;
	theApp = nullptr;

    return (int) msg.wParam;
}