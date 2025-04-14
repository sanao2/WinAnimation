#pragma once
#include "pch.h"

class Texture;

class Animator
{
private : 
	map<wstring, Animation*> m_mapAnimation; // �ִϸ��̼��� �����ϱ� ���� �� 
	wchar_t* m_pAnimation; // ��� �ִϸ��̼��� �����ϱ� ���� ������ 
	Animation* m_pCurAnim; //���� ������� �ִϸ��̼� 

	 
public : 
	void CreateAnimation(const wstring name, Texture* _texture, Vector2 _vLt, Vector2 _vSliceSize, Vector2 _vStep, UINT FrameCount);
	Animation* FindAnimation(const wstring& _strname);
	void PlayAnimation();

	void Update(); 
	void Render(HDC _DC); 
public : 
	Animator();
	~Animator();
	
	friend class Texture;
}; 