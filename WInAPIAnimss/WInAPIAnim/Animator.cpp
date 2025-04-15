#include "Animator.h"



Animation* Animator::FindAnimation(const wstring
{

	//if (NULL == m_pAnimation.end()) // �ִϸ��̼��� ������ 
	//{
	//	return nullptr;
	//}

	//return m_pAnimation->second; // �ִϸ��̼��� ã������, �ش� �ִϸ��̼��� �����Ѵ�. 
}

void Animator::CreateAnimation(const wstring name, Texture* _texture, Vector2 _vLt, Vector2 _vSliceSize, Vector2 _vStep, UINT FrameCount)
{
	Animation* pAnim = FindAnimation(name); // �ִϸ��̼��� ã�´�.		
	if (pAnim == nullptr) // �ִϸ��̼��� ������, 
	{
		return;
	}

	pAnim = new Animation(); // �ƴϸ� ���ο� �ִϸ��̼��� �����Ѵ�. 
	pAnim->SetName(name);
	pAnim->animator = this; // �ִϸ��̼��� ������ ���� �ִϸ����͸� �� ���Ϸ� �����Ѵ�. \

	pAnim->Create(_texture, _vLt, _vSliceSize, _vStep, FrameCount, 1.0f); // �ִϸ��̼��� �����Ѵ�.
}

void Animator::Update()
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->Update();
	}
}

Animator::Animator() : m_pCurAnim(nullptr)
{
}
Animator::~Animator() 
{
}