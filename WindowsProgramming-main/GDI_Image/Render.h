#pragma once
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "gdiplus.h"
#include <vector>
using namespace std;

// �̹����� �̸�, �ҷ��� �̹����� �ִ� ���, �̹����� ���μ��� ���� �� �޾ƿͼ�, 
// �̹����� �ҷ��� �Լ�. �׸��� , �̹����� �ʱ�ȭ�� �Լ��� �ʿ�.
// �ҷ��� �̹����� �ִϸ��̼����� �����, ������Ʈ�� �����ؼ� ���� ���۸��� ���ؼ� ȭ�鿡 ���δ�. 


ULONG_PTR g_GDIplusToken; //������ �� �����ϴ� ��ū 
Gdiplus::GdiplusStartupInput GSI;
HWND g_hWnd;
int ImageWidth;
int ImageHeight;

enum AnimState { IDLE, WORK, ATTACK }; // �ִϸ��̼� ���� 

//���� ���۸��� DeviceContext �ڵ� 
HDC frontBufferDC;
HDC backBufferDC;

// �ĸ� ���۷� ������ �̹��� �ڵ� 
HBITMAP backBufferImageDC;
ULONG_PTR GDIplusToken;
// �׷��� ����
Gdiplus::Graphics* backBufferGraphics;


vector<Gdiplus::Bitmap*> Images; // �̹����� ������ ���� 


void Initialize();
void Update();
void Render();


void loadImage(Gdiplus::Bitmap* ImageBIT, wchar_t* filePath, UINT ImgCount); // �̹����� �ҷ����� 
Gdiplus::Bitmap* FindImage(Gdiplus::Bitmap* ImageBIT, vector< Gdiplus::Bitmap*> Images, UINT ImgCount); //���� �̹����� ã�ƿ��� 

void createAnim(wchar_t* filePath, UINT Imgwidth, UINT imgheight); //�ҷ��� �̹����� �ִϸ��̼��� ����� 
void FindAnim(Gdiplus::Graphics* Graphics, wchar_t* filePath, UINT FindANimCount);

UINT GetImgWidth(Gdiplus::Bitmap* ImageBIT)
{
	return ImageBIT->GetWidth();
}
UINT GetImgHeight(Gdiplus::Bitmap* ImageBIT)
{
	return ImageBIT->GetHeight();
}
