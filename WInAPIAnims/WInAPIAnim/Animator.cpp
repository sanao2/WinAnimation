#include "Animator.h"
#include "Animation.h"



void Animator::CreateAnimation(const wstring name, Texture* _texture, Vector2 _vLt, Vector2 _vSliceSize, Vector2 _vStep, UINT FrameCount)
{  
	Animation* pAnim = FindAnimation(name); // �ִϸ��̼��� ã�´�.		
	if (nullptr == pAnim) // �ִϸ��̼��� ������, 
	{
		return; 
	}

	pAnim = new Animation(); // �ƴϸ� ���ο� �ִϸ��̼��� �����Ѵ�. 
	pAnim->SetName(name); 
	pAnim->animator = this; // �ִϸ��̼��� ������ ���� �ִϸ����͸� �� ���Ϸ� �����Ѵ�. \

	pAnim->Create(_texture, _vLt, _vSliceSize, _vStep, FrameCount, 1.0f); // �ִϸ��̼��� �����Ѵ�.
}

Animation* Animator::FindAnimation(const wstring& _strname)
{
	map<wstring, Animation*> :: iterator iter = m_mapAnimation.find(_strname); // �ִϸ��̼��� ã�´�. 
	if (iter == m_mapAnimation.end()) // �ִϸ��̼��� ������ 
	{
		return nullptr;
	}

	return iter->second; // �ִϸ��̼��� ã������, �ش� �ִϸ��̼��� �����Ѵ�. 
}

void Animator::Update()
{
	if (nullptr == m_pCurAnim)
	{
		m_pCurAnim->Update();
	}
}

Animator::Animator() : m_pCurAnim(nullptr)
{
}
