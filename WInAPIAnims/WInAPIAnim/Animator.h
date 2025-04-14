#pragma once
#include "pch.h"

class Texture;

class Animator
{
private : 
	map<wstring, Animation*> m_mapAnimation; // 애니메이션을 저장하기 위한 맵 
	wchar_t* m_pAnimation; // 모든 애니메이션을 저장하기 위한 포인터 
	Animation* m_pCurAnim; //현재 재생중인 애니메이션 

	 
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