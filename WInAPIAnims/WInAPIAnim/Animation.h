#pragma once
#include "pch.h"

class Animator; 
class Texture; 

struct AnimFrame // �̹����� �»�� ��ġ �ڸ� ����  
{
	Vector2 vLT;		// �»�� ��ġ 
	Vector2 vSliceSize; // �ڸ� ������ ����
	Vector2 vStep;		// �ڸ� ���� 
	float frameTime;	// ������ �ð�
};

class Animation
{
private : 
	wstring			  m_strName; // �ִϸ��̼� �̸� 
	Animator*		  animator; // �ִϸ��̼��� ����ϱ� ���� �ִϸ�����
	Texture*		  m_texture; // �ִϸ��̼ǿ� ����� �ؽ���
	int 			  m_icurFrm; 
	float			  m_FrmTime; 
	vector<AnimFrame> m_vecAnimFrame; // �ִϸ��̼� �������� �����ϱ� ���� ���� 

	void SetName(const wstring& _strName) { m_strName = _strName; } // �ִϸ��̼� �̸��� �����Ѵ�. 

public : 
	void Update();
	void Render(HDC _DC);
	void Create(Texture* _texture, Vector2 _vLt, Vector2 _vSliceSize, Vector2 _vStep, UINT FrameCount, float frameTime); // �ִϸ��̼��� �����Ѵ�.
	
	const wstring& GetName() { return m_strName; } // �ִϸ��̼� �̸��� �����´�.

	Animation(); 
	~Animation();

	friend class Animator; 
	friend class Texture; 
};

