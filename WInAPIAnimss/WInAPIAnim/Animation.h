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

struct Sprite  // 이미지의 좌상단 위치 자를 정보  
{
	Vector2 LeftTop;		// 좌상단 위치 
	Vector2 vSliceSize;		// 자를 사이즈 영역
	Vector2 vStep;			// 자를 간격 
	float frameTime;		// 프레임 시간
};

class Animation 
{
private : 
	wstring				 m_AnimStateName;	// 애니메이션 이름 
	wchar_t 			 current_Anim;
	Texture*			 m_texture;			// 애니메이션에 사용할 텍스쳐
	int 				 m_icurFrm;			// 현재 프레임 
	float				 m_FrmTime; 
	wchar_t				 AnimPath;			// 프레임을 
	
	std::vector<Sprite>	 m_vecAnimFrame; // 애니메이션 프레임을 저장하기 위한 벡터 
	
	void SetName(const wstring& _strName) { m_AnimStateName = _strName; } // 애니메이션 이름을 설정한다. 

public : 
	
	void Update();
	void Render(HDC _DC);
	void Create(Texture* _texture, Vector2 _vLt, Vector2 _vSliceSize, Vector2 _vStep, UINT FrameCount, float frameTime); // 애니메이션을 생성한다.
	
	const wstring& GetName() { return m_AnimStateName; } // 애니메이션 이름을 가져온다.

	Animation(); 
	~Animation();

	friend class Texture; 
};

