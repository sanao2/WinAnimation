#pragma once
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "gdiplus.h"
#include <vector>
using namespace std;

// 이미지의 이름, 불러올 이미지가 있는 경로, 이미지의 가로세로 길이 를 받아와서, 
// 이미지를 불러올 함수. 그리고 , 이미지를 초기화할 함수가 필요.
// 불러온 이미지는 애니메이션으로 만들고, 오브젝트에 적용해서 더블 버퍼링을 통해서 화면에 보인다. 


ULONG_PTR g_GDIplusToken; //종료할 때 전달하는 토큰 
Gdiplus::GdiplusStartupInput GSI;
HWND g_hWnd;
int ImageWidth;
int ImageHeight;

enum AnimState { IDLE, WORK, ATTACK }; // 애니메이션 상태 

//더블 버퍼링용 DeviceContext 핸들 
HDC frontBufferDC;
HDC backBufferDC;

// 후면 버퍼로 연결할 이미지 핸들 
HBITMAP backBufferImageDC;
ULONG_PTR GDIplusToken;
// 그래픽 버퍼
Gdiplus::Graphics* backBufferGraphics;


vector<Gdiplus::Bitmap*> Images; // 이미지를 관리할 벡터 


void Initialize();
void Update();
void Render();


void loadImage(Gdiplus::Bitmap* ImageBIT, wchar_t* filePath, UINT ImgCount); // 이미지를 불러오기 
Gdiplus::Bitmap* FindImage(Gdiplus::Bitmap* ImageBIT, vector< Gdiplus::Bitmap*> Images, UINT ImgCount); //만들어낸 이미지를 찾아오기 

void createAnim(wchar_t* filePath, UINT Imgwidth, UINT imgheight); //불러온 이미지로 애니메이션을 만들기 
void FindAnim(Gdiplus::Graphics* Graphics, wchar_t* filePath, UINT FindANimCount);

UINT GetImgWidth(Gdiplus::Bitmap* ImageBIT)
{
	return ImageBIT->GetWidth();
}
UINT GetImgHeight(Gdiplus::Bitmap* ImageBIT)
{
	return ImageBIT->GetHeight();
}
