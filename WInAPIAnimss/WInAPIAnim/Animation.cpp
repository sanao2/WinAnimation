#include "Animation.h"



void Animation::nitialize()
{
	Gdiplus::GdiplusStartup(&g_GdiPlusToken, &gsi, nullptr);
	Gdiplus::Graphics* g_pBackBufferGraphics = Gdiplus::Graphics::FromHDC(backBufferDC);

}
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
	m_vecAnimFrame[current_Anim].vSliceSize; 

	TransparentBlt(_DC,
		(int)(playerpos.x - m_vecAnimFrame[current_Anim].vSliceSize.x / 2.f), 
		(int)(playerpos.y - m_vecAnimFrame[current_Anim].vSliceSize.y / 2.f), 
		(int)(m_vecAnimFrame[current_Anim].vSliceSize.x),
		(int)(m_vecAnimFrame[current_Anim].vSliceSize.y),
		m_texture->GetDC(),
		(int)(m_vecAnimFrame[current_Anim].vLT.x),
		(int)(m_vecAnimFrame[current_Anim].vLT.y),
		(int)(m_vecAnimFrame[current_Anim].vSliceSize.x),
		(int)(m_vecAnimFrame[current_Anim].vSliceSize.y),
		RGB(255, 0, 255));
}

void Animation::Create(Texture* _texture, Vector2 _vLt, Vector2 _vSliceSize, Vector2 _vStep, UINT FrameCount, float frameTime)
{
	m_texture = _texture; 

	AnimFrame frm = {}; 
	for (UINT i = 0; i < FrameCount; ++i)
	{
		frm.frameTime = frameTime; // ������ �ð��� �����Ѵ�. 
		frm.vSliceSize = _vSliceSize; // �ڸ� ����� �����Ѵ�. 
		frm.LeftTop = _vLt + _vStep * i; // step = �ڸ� �����̱� ������, �ι�° �̹����� ��ĭ ���̴�. 

		m_vecAnimFrame.push_back(frm); // �ִϸ��̼� �������� ���Ϳ� �߰��Ѵ�.
	}
}

Animation::Animation() : current_Anim(nullptr) , m_texture(nullptr), m_icurFrm(0)
{
}

Animation::~Animation()
{
}
