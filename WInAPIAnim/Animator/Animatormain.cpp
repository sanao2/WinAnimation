#include <iostream>
#include "animator.h"
#include <windows.h>
#include <stdio.h>
#include <gdiplus.h>

namespace Anim
{
	// 이미지 파일의 이름, 경로, x,y 길이를 받아와서 애니메이션으로 만들어서 출력한다. 

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
		// 후면 버퍼와 후면에 완성된 비트맵을 연결?

		Gdiplus::GdiplusStartupInput GSI;
		Gdiplus::GdiplusStartup(&GdiPlusToken, &GSI, nullptr);
		BackBufferGraphics = Gdiplus::Graphics::FromHDC(BackBufferDC); // 후면 버퍼와 연결 
	}

	// 애니메이션에 리소스 추가하기 
	void CreateAnimInit(Charactor FrameName, wchar_t* filepath)
	{
		for (int FrameIndex = 0; FrameIndex < 10; ++FrameIndex)
		{
			bitmapFrame[FrameIndex] = filepath;
		}
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

	// 이미지 로드 
	void LoadBitMap(wchar_t fileName, wchar_t* filepath, UINT _FrameCount)
	{
		// 경로와 비트맵을 받아서 생성한다.
		// 순회해서 가져와서 프레임에 넣는다. 

		// 프레임 용 버퍼 
		wchar_t FrameBuffer[250] = { 0, };

		Gdiplus::Bitmap* BitmapFilePath = new Gdiplus::Bitmap(filepath);

		for (int frameindex = 0; frameindex < _FrameCount; ++frameindex)
		{
			swprintf(FrameBuffer, filepath, frameindex);
			bitmapFrame[frameindex] = BitmapFilePath;
		}
	}

	// 이미지를 프레임 당 순회하여 출력한다. 
	void AnimRender(int width, int height, UINT FrameCount)
	{
		
		// Renderer::beginDraw()
		PatBlt(BackBufferDC, 0, 0, W_width, W_height, BLACKNESS);
				
		
		// Render() 순회 하여서 출력한다. 
		for (UINT FrameIndex = 0; FrameIndex < FrameCount; ++FrameIndex)
		{
			BackBufferGraphics->DrawImage(bitmapFrame[FrameIndex], 0, 0, width, height);
		}

		// Renderer::EndDraw()
		BitBlt(FrontBufferDC, 0, 0, W_width, W_height, BackBufferDC, 0, 0, SRCCOPY);
		

	}


}
