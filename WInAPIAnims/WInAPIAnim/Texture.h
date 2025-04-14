#pragma once
#include "Resource.h"


struct playerPos
{
	int x;
	int y;
};

class Texture : public Res 
{
private : 
	// 커널 오브젝트들을 저장하기 위한 핸들 
	// -> 로딩된 이미지를 DC를 통해서 경로 상에 있는 texture 라는 객체로 만들어 로딩해오기 위해서 필요함.
	HDC  m_hdc; 		// 텍스쳐 DC 
	HBITMAP m_hBitmap;	// 비트맵ID를 받아올 수 있도록 해주는 핸들 
	BITMAP m_BmpInfo; // 비트맵 정보를 받아올 구조체를 생성. 가로가 몇이고, 세로가 몇인지 등의 정보를 저장.
	
public : 
	void loadTexture(const wchar_t* _ImgFilePath); 
	void Render(HDC _DC); 

	UINT ImgWidth() { return m_BmpInfo.bmWidth; } // 비트맵의 가로 길이 
	UINT ImgHeight() { return m_BmpInfo.bmHeight; } // 비트맵의 세로 길이 

	HDC GetDC() { return m_hdc; } // DC를 받아온다. 
public : 
	Texture();
	~Texture();

};

