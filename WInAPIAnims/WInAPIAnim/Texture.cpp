#include "Texture.h"
#pragma comment(lib, "Msimg32.lib")


void Texture::loadTexture(const wchar_t* _ImgFilePath)
{
	// 어떤 이미지를 사용할 지 모르기 떄문에, 어떤 사이즈를 가질 지 모르기 때문에 주의해야 한다.
	// 해당 경로에 있는 이미지의 아이디를 받아와서 로딩한다. 

	if (nullptr == m_hBitmap)// 이미지 비어있으면, 
	{
		// 이미지 로딩 실패
		std::cout << "Image Load Failed" << std::endl;
		return;
	}

	// 비트맵과 연결할 DC를 생성. 
	HDC HbitmapImg = CreateCompatibleDC(m_hdc); // DC를 생성한다.
		
	m_hBitmap = (HBITMAP)LoadImage(nullptr,
		_ImgFilePath,
		IMAGE_BITMAP,
		0,0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	
	// 가로 세로 길이 
	GetObject(m_hBitmap, sizeof(BITMAP), &m_BmpInfo); // 비트맵 정보를 받아온다. 

}

void Texture::Render(HDC _DC)
{
	int width = ImgWidth(); 
	int height = ImgHeight();

	// 나중에 플레이어 오브젝트의 위치를 알려주어야 한다. 
	playerPos playerpos = { 0, 0 };
	// Renderer::BeginDraw()
	//PatBlt(전면 버퍼DC, 0, 0, 전면 버퍼 가로길이, 전면 버퍼 세로길이, BLACKNESS);

	BitBlt(_DC,
		int(playerpos.x - (float)(width / 2)),
		int(playerpos.y - (float)(height / 2)),
		width, height,
		GetDC(),
		0, 0,
		SRCCOPY);

	/*TransparentBlt(_DC,
		int(playerpos.x - (float)(width / 2)),
		int(playerpos.y - (float)(height / 2)),
		width, height,
		GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255));*/

	//BitBlt(전면 버퍼DC, 0, 0, 전면 버퍼 가로길이, 전면 버퍼 세로길이, 후면버퍼, 0, 0, SRCCOPY);
}

Texture::Texture() : m_hBitmap(0), m_hdc(0)
{
}

Texture::~Texture()
{
}
