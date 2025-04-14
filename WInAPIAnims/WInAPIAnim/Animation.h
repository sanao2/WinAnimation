#pragma once
#include "pch.h"

class Animator; 
class Texture; 

struct AnimFrame // 이미지의 좌상단 위치 자를 정보  
{
	Vector2 vLT;		// 좌상단 위치 
	Vector2 vSliceSize; // 자를 사이즈 영역
	Vector2 vStep;		// 자를 간격 
	float frameTime;	// 프레임 시간
};

class Animation
{
private : 
	wstring			  m_strName; // 애니메이션 이름 
	Animator*		  animator; // 애니메이션을 재생하기 위한 애니메이터
	Texture*		  m_texture; // 애니메이션에 사용할 텍스쳐
	int 			  m_icurFrm; 
	float			  m_FrmTime; 
	vector<AnimFrame> m_vecAnimFrame; // 애니메이션 프레임을 저장하기 위한 벡터 

	void SetName(const wstring& _strName) { m_strName = _strName; } // 애니메이션 이름을 설정한다. 

public : 
	void Update();
	void Render(HDC _DC);
	void Create(Texture* _texture, Vector2 _vLt, Vector2 _vSliceSize, Vector2 _vStep, UINT FrameCount, float frameTime); // 애니메이션을 생성한다.
	
	const wstring& GetName() { return m_strName; } // 애니메이션 이름을 가져온다.

	Animation(); 
	~Animation();

	friend class Animator; 
	friend class Texture; 
};

