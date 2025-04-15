#pragma once
#include "pch.h"
#include "Animation.h"
#include "Texture.h"
#include <string>

enum MotionState
{
	IDLE,
	WALK,
	ATTACK
};

class Texture;
class Animation; 

template<typename T> 
class Animator
{
private : 

	vector<T> FramAnim; 					 // 애니메이션을 저장하기 위한 벡터  
	T* m_pAnimation;					     // 모든 애니메이션을 저장하기 위한 포인터 
	Animation* m_pCurAnim;					 //현재 재생중인 애니메이션 

	 
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
	friend class Animation; 
}; 