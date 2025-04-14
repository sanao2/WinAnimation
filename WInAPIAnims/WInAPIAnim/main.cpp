#include <windows.h>
#include <stdio.h>
#include <iostream>

#pragma("MSVCRTD.lib",lib) 


namespace WinAPI
{
	LPCTSTR szClassName = TEXT("윈도우 클래스 이름");
	
	
	// 윈도우 창 핸들 
	HWND g_hWnd;

	// 윈도우 창 해상도 
	int W_width = 1024;
	int W_height = 768;

	
	// 콘솔 초기화
	void InitConsole()
	{		AllocConsole();
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		SetConsoleTitle(L"윈도우 메시지 콘솔 로그");
		printf("콘솔 로그 시작...\n\n");
	}

	void UninitConsole()
	{
		// 표준 출력 스트림 닫기
		fclose(stdout);
		// 콘솔 해제
		FreeConsole();
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nCmdShow)
	{
		InitConsole();  // 콘솔 출력 초기화

		char szPath[MAX_PATH] = { 0, };
		::GetCurrentDirectoryA(MAX_PATH, szPath);
		printf("Current Directory: %s\n", szPath);
		
		WNDCLASS wc = { 0 };
		wc.lpfnWndProc = WndProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = szClassName;
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);	// 기본 커서 모양
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// 기본 아이콘 모양
		RegisterClass(&wc);

		// 원하는 크기가 조정되어 리턴
		RECT rcClient = { 0, 0, (LONG)W_width, (LONG)W_height };
		AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

		ShowWindow(g_hWnd, nCmdShow);

		MSG msg;
		while (true)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			
		}
			

		UninitConsole();  // 콘솔 출력 해제
		return (int)msg.wParam; 
	}

}

