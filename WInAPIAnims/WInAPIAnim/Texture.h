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
	// Ŀ�� ������Ʈ���� �����ϱ� ���� �ڵ� 
	// -> �ε��� �̹����� DC�� ���ؼ� ��� �� �ִ� texture ��� ��ü�� ����� �ε��ؿ��� ���ؼ� �ʿ���.
	HDC  m_hdc; 		// �ؽ��� DC 
	HBITMAP m_hBitmap;	// ��Ʈ��ID�� �޾ƿ� �� �ֵ��� ���ִ� �ڵ� 
	BITMAP m_BmpInfo; // ��Ʈ�� ������ �޾ƿ� ����ü�� ����. ���ΰ� ���̰�, ���ΰ� ������ ���� ������ ����.
	
public : 
	void loadTexture(const wchar_t* _ImgFilePath); 
	void Render(HDC _DC); 

	UINT ImgWidth() { return m_BmpInfo.bmWidth; } // ��Ʈ���� ���� ���� 
	UINT ImgHeight() { return m_BmpInfo.bmHeight; } // ��Ʈ���� ���� ���� 

	HDC GetDC() { return m_hdc; } // DC�� �޾ƿ´�. 
public : 
	Texture();
	~Texture();

};

