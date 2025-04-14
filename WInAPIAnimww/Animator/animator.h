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
	

		// 애니메이션에 필요한 이미지 파일의 경로에서 이미지 파일을 받아와서 로딩.
		// 로딩해서 불러온 이미지를 순차적으로 저장하고, 
		// 순차적으로 순회하여 불러와 저장한 이미지들을 순차적으로 반복해 출력시킨다. 
		// 
		// 불러와서 출력하기 위해서는 이미지의 이름, 가로 세로의 길이, 그리고 새로 배치할 위치의 좌표가 필요하다. 

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
	//void AnimRender(int width, int height, UINT FrameCount);
	void DrawImage(int x, int y, Gdiplus::Bitmap* bitmap, int srcX, int srcY, int srcwidth, int srcheight);

}