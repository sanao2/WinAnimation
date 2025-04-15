#include "Texture.h"
#pragma comment(lib, "Msimg32.lib")


void Texture::loadTexture(const wchar_t* _ImgFilePath)
{
	// � �̹����� ����� �� �𸣱� ������, � ����� ���� �� �𸣱� ������ �����ؾ� �Ѵ�.
	// �ش� ��ο� �ִ� �̹����� ���̵� �޾ƿͼ� �ε��Ѵ�. 

	if (nullptr == m_hBitmap)// �̹��� ���������, 
	{
		// �̹��� �ε� ����
		std::cout << "Image Load Failed" << std::endl;
		return;
	}

	// ��Ʈ�ʰ� ������ DC�� ����. 
	HDC HbitmapImg = CreateCompatibleDC(m_hdc); // DC�� �����Ѵ�.
		
	m_hBitmap = (HBITMAP)LoadImage(nullptr,
		_ImgFilePath,
		IMAGE_BITMAP,
		0,0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	
	// ���� ���� ���� 
	GetObject(m_hBitmap, sizeof(BITMAP), &m_BmpInfo); // ��Ʈ�� ������ �޾ƿ´�. 

}

void Texture::Render(HDC _DC)
{
	int width = ImgWidth(); 
	int height = ImgHeight();

	// ���߿� �÷��̾� ������Ʈ�� ��ġ�� �˷��־�� �Ѵ�. 
	playerPos playerpos = { 0, 0 };
	// Renderer::BeginDraw()
	//PatBlt(���� ����DC, 0, 0, ���� ���� ���α���, ���� ���� ���α���, BLACKNESS);

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

	//BitBlt(���� ����DC, 0, 0, ���� ���� ���α���, ���� ���� ���α���, �ĸ����, 0, 0, SRCCOPY);
}

Texture::Texture() : m_hBitmap(0), m_hdc(0)
{
}

Texture::~Texture()
{
}
