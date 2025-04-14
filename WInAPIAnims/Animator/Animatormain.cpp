#include <iostream>
#include "animator.h"
#include <windows.h>
#include <stdio.h>
#include <gdiplus.h>
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
	{
		AllocConsole();
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

namespace Anim
{
	// 이미지 파일의 이름, 경로, x,y 길이를 받아와서 애니메이션으로 만들어서 출력한다. 

	float FrameTime = 0.0f; 

	UINT Width() {

		UINT width = BackBufferGraphics->GetWidth();
		return width;
	}
	UINT Height() {

		UINT height = BackBufferGraphics->GetHeight();
		return height;
	}

	// GDI+ 초기화 
	void Initialize()
	{
		
		FrontBufferDC = GetDC(g_hWnd);						//윈도우 클라이언트 영역의 DeviceContext얻기
		BackBufferDC = CreateCompatibleDC(FrontBufferDC);   // 호환되는 DeviceContext 생성
		BackBufferBitmapDC = CreateCompatibleBitmap(FrontBufferDC, W_width, W_height); // 메모리 영역생성
		SelectObject(BackBufferDC, BackBufferBitmapDC);       // MemDC의 메모리영역 지정
		// 후면 버퍼와 후면에 완성된 비트맵을 연결

		Gdiplus::GdiplusStartupInput GSI;
		Gdiplus::GdiplusStartup(&GdiPlusToken, &GSI, nullptr);
		BackBufferGraphics = Gdiplus::Graphics::FromHDC(BackBufferDC); // 후면 버퍼와 연결 
	}
	
	
	//해제 
	void Realese()
	{		

		for (UINT DeleteIndex = 0; DeleteIndex < 10; ++DeleteIndex)
		{
			delete bitmapFrame[DeleteIndex];
			
		}
		delete[] bitmapFrame;
		DeleteObject(BackBufferBitmapDC);
		DeleteDC(BackBufferDC);
		ReleaseDC(g_hWnd, FrontBufferDC);

		delete BackBufferGraphics;

		Gdiplus::GdiplusShutdown(GdiPlusToken);
	}

	// 애니메이션에 리소스 추가하기 
	void CreateAnimInit(Charactor FrameName, wchar_t* filepath)
	{
		Gdiplus::Rect rect = {}; 

		for (int FrameIndex = 0; FrameIndex < 10; ++FrameIndex)
		{
			bitmapFrame[FrameIndex] = filepath;
		}
	}

	void DrawImage(int x, int y, Gdiplus::Bitmap* bitmap, int srcX, int srcY, int srcwidth, int srcheight)
	{
		Gdiplus::Rect srcRect(srcX, srcY, srcwidth, srcheight); // 소스의 영역
		Gdiplus::Rect destRect(x, y, srcRect.Width, srcRect.Height); // 화면에 그릴 영역
		BackBufferGraphics->DrawImage(bitmap, destRect, srcRect.X, srcRect.Y,
			srcRect.Width, srcRect.Height, Gdiplus::UnitPixel);
		// 소스의 일부분만을 그린다. 

	};

	// 이미지 로드 
	void LoadBitMap(wchar_t fileName, wchar_t* filepath, UINT _FrameCount)
	{
		// 경로와 비트맵을 받아서 생성한다.
		// 순회해서 가져와서 프레임에 넣는다. 

		// 프레임 용 버퍼 
		char FrameBuffer[250] = { 0, };

		Gdiplus::Bitmap* ImageBitmap = new Gdiplus::Bitmap(filepath);

		for (int frameindex = 0; frameindex < _FrameCount; ++frameindex)
		{
		
			sprintf(FrameBuffer, filepath, frameindex);
			bitmapFrame[frameindex] = ImageBitmap;
		}
	}

	//// 이미지를 프레임 당 순회하여 출력한다. 
	//void AnimRender(int width, int height, UINT FrameCount)
	//{
	//	
	//	// Renderer::beginDraw()
	//	PatBlt(BackBufferDC, 0, 0, W_width, W_height, BLACKNESS);
	//			
	//	
	//	// Render() 순회 하여서 출력한다. 
	//	for (UINT FrameIndex = 0; FrameIndex < FrameCount; ++FrameIndex)
	//	{
	//		BackBufferGraphics->DrawImage(bitmapFrame[FrameIndex], 0, 0, width, height);
	//	}

	//	// Renderer::EndDraw()
	//	BitBlt(FrontBufferDC, 0, 0, W_width, W_height, BackBufferDC, 0, 0, SRCCOPY);
	//	

	//}



}
