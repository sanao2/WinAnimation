#pragma once
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "gdiplus.lib")


namespace Anim
{
	HWND g_hWnd;
	int W_width;
	int W_height;

	// 버퍼용 DeviceContext 받아는 핸들 
	HDC FrontBufferDC;
	HDC BackBufferDC;

	// 백버퍼에 그릴 비트맵 핸들 
	HBITMAP BackBufferBitmapDC;
	ULONG_PTR GdiPlusToken;  // GDI+ 를 종료할 때 전달할 핸들 값 
	Gdiplus::Graphics* BackBufferGraphics;

	Gdiplus::Bitmap* bitmapFrame;
	
	//// 애니메이션 관리 
	enum Charactor
	{
		IDLE,
		WOLK,
		ATTACK
	};
	
	void Initialize();
	void Realese();

	void LoadBitMap(wchar_t fileName, wchar_t* filepath, UINT _FrameCount);
	void CreateAnimInit(Charactor FrameName, wchar_t* filepath);
	void AnimRender(int width, int height, UINT FrameCount);
}