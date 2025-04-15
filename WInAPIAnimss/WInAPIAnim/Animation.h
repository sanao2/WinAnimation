#pragma once
#include "pch.h"
#include "Animator.h"
#include <vector>
using namespace std; 

class Texture; 

enum MotionState
{
	IDLE,
	WALK,
	ATTACK
}motionState;

const char* motionPath()
{
	switch (motionState)
	{
	case  IDLE:
		
		break;
	case WALK:
		return "..\Resource\RUN.txt";
		break;
	case ATTACK:
		break;
	}
}

struct Sprite  // �̹����� �»�� ��ġ �ڸ� ����  
{
	Vector2 LeftTop;		// �»�� ��ġ 
	Vector2 vSliceSize;		// �ڸ� ������ ����
	Vector2 vStep;			// �ڸ� ���� 
	float frameTime;		// ������ �ð�
};

class Animation 
{
private : 
	wstring				 m_AnimStateName;	// �ִϸ��̼� �̸� 
	wchar_t 			 current_Anim;
	Texture*			 m_texture;			// �ִϸ��̼ǿ� ����� �ؽ���
	int 				 m_icurFrm;			// ���� ������ 
	float				 m_FrmTime; 
	wchar_t				 AnimPath;			// �������� 
	
	std::vector<Sprite>	 m_vecAnimFrame; // �ִϸ��̼� �������� �����ϱ� ���� ���� 
	
	void SetName(const wstring& _strName) { m_AnimStateName = _strName; } // �ִϸ��̼� �̸��� �����Ѵ�. 

public : 
	
	void Update();
	void Render(HDC _DC);
	void Create(Texture* _texture, Vector2 _vLt, Vector2 _vSliceSize, Vector2 _vStep, UINT FrameCount, float frameTime); // �ִϸ��̼��� �����Ѵ�.
	
	const wstring& GetName() { return m_AnimStateName; } // �ִϸ��̼� �̸��� �����´�.

	Animation(); 
	~Animation();

	friend class Texture; 
};

