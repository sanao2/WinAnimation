#include "Animator.h"



Animation* Animator::FindAnimation(const wstring
{

	//if (NULL == m_pAnimation.end()) // 애니메이션이 없으면 
	//{
	//	return nullptr;
	//}

	//return m_pAnimation->second; // 애니메이션을 찾았으면, 해당 애니메이션을 리턴한다. 
}

void Animator::CreateAnimation(const wstring name, Texture* _texture, Vector2 _vLt, Vector2 _vSliceSize, Vector2 _vStep, UINT FrameCount)
{
	Animation* pAnim = FindAnimation(name); // 애니메이션을 찾는다.		
	if (pAnim == nullptr) // 애니메이션이 없으면, 
	{
		return;
	}

	pAnim = new Animation(); // 아니면 새로운 애니메이션을 생성한다. 
	pAnim->SetName(name);
	pAnim->animator = this; // 애니메이션이 가지고 있을 애니메이터를 이 파일로 지정한다. \

	pAnim->Create(_texture, _vLt, _vSliceSize, _vStep, FrameCount, 1.0f); // 애니메이션을 생성한다.
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