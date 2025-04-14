#include "Animation.h"



void Animation::Update()
{
	
	if (m_FrmTime < m_vecAnimFrame[m_icurFrm].frameTime)
	{
		++m_icurFrm;
		if (m_vecAnimFrame.size() < m_FrmTime)
		{
			m_icurFrm = 0; 
		}
		m_FrmTime = 0.f;
	}
}

void Animation::Render(HDC _DC)
{
	m_vecAnimFrame[m_pCurAnim].vSliceSize; 

	TransparentBlt(_DC,
		(int)(playerpos.x - m_vecAnimFrame[m_pCurAnim].vSliceSize.x / 2.f), 
		(int)(playerpos.y - m_vecAnimFrame[m_pCurAnim].vSliceSize.y / 2.f), 
		(int)(m_vecAnimFrame[m_pCurAnim].vSliceSize.x),
		(int)(m_vecAnimFrame[m_pCurAnim].vSliceSize.y),
		m_texture->GetDC(),
		(int)(m_vecAnimFrame[m_pCurAnim].vLT.x),
		(int)(m_vecAnimFrame[m_pCurAnim].vLT.y),
		(int)(m_vecAnimFrame[m_pCurAnim].vSliceSize.x),
		(int)(m_vecAnimFrame[m_pCurAnim].vSliceSize.y),
		RGB(255, 0, 255));
}

void Animation::Create(Texture* _texture, Vector2 _vLt, Vector2 _vSliceSize, Vector2 _vStep, UINT FrameCount, float frameTime)
{
	m_texture = _texture; 

	AnimFrame frm = {}; 
	for (UINT i = 0; i < FrameCount; ++i)
	{
		frm.frameTime = frameTime; // 프레임 시간을 설정한다. 
		frm.vSliceSize = _vSliceSize; // 자를 사이즈를 설정한다. 
		frm.vLT = _vLt + _vStep * i; // step = 자를 간격이기 때문에, 두번째 이미지는 한칸 옆이다. 

		m_vecAnimFrame.push_back(frm); // 애니메이션 프레임을 벡터에 추가한다.
	}
}

Animation::Animation() : animator(nullptr), m_texture(nullptr), m_icurFrm(0)
{
}

Animation::~Animation()
{
}
