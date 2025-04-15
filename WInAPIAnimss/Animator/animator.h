#pragma once
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "gdiplus.lib")


namespace Anim
{
	HWND g_hWnd;
	int W_width;
	int W_height;

	// ���ۿ� DeviceContext �޾ƴ� �ڵ� 
	HDC FrontBufferDC;
	HDC BackBufferDC;

	// ����ۿ� �׸� ��Ʈ�� �ڵ� 
	HBITMAP BackBufferBitmapDC;
	ULONG_PTR GdiPlusToken;  // GDI+ �� ������ �� ������ �ڵ� �� 
	Gdiplus::Graphics* BackBufferGraphics;

	Gdiplus::Bitmap* bitmapFrame;
	

		// �ִϸ��̼ǿ� �ʿ��� �̹��� ������ ��ο��� �̹��� ������ �޾ƿͼ� �ε�.
		// �ε��ؼ� �ҷ��� �̹����� ���������� �����ϰ�, 
		// ���������� ��ȸ�Ͽ� �ҷ��� ������ �̹������� ���������� �ݺ��� ��½�Ų��. 
		// 
		// �ҷ��ͼ� ����ϱ� ���ؼ��� �̹����� �̸�, ���� ������ ����, �׸��� ���� ��ġ�� ��ġ�� ��ǥ�� �ʿ��ϴ�. 

	//// �ִϸ��̼� ���� 
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