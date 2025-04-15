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

	vector<T> FramAnim; 					 // �ִϸ��̼��� �����ϱ� ���� ����  
	T* m_pAnimation;					     // ��� �ִϸ��̼��� �����ϱ� ���� ������ 
	Animation* m_pCurAnim;					 //���� ������� �ִϸ��̼� 

	 
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