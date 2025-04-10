#include "Render.h"


void Initialize()
{
	frontBufferDC = GetDC(g_hWnd);						//������ Ŭ���̾�Ʈ ������ DeviceContext���
	backBufferDC = CreateCompatibleDC(frontBufferDC);   // ȣȯ�Ǵ� DeviceContext ����
	backBufferImageDC = CreateCompatibleBitmap(frontBufferDC, ImageWidth, ImageHeight); // �޸� ��������
	SelectObject(backBufferDC, backBufferImageDC);       // MemDC�� �޸𸮿��� ����
	// �ĸ� ���ۿ� �ĸ鿡 �ϼ��� ��Ʈ���� ����?

	Gdiplus::GdiplusStartupInput GSI;
	Gdiplus::GdiplusStartup(&GDIplusToken, &GSI, nullptr);
	backBufferGraphics = Gdiplus::Graphics::FromHDC(backBufferDC); // �ĸ� ���ۿ� ���� 
}

// ��� �ȿ� �ִ� ��� ������ �����ͼ� ���� images �� �־���´�. 
void loadImage(Gdiplus::Bitmap* ImageBIT, wchar_t* filePath, UINT ImgCount)
{
	ImageBIT = new Gdiplus::Bitmap(filePath);

	// ��� �̹����� ���� �ȿ� ���� �Ѵ�. 
	for (UINT Imgindex = 0; Imgindex < ImgCount; Imgindex++)
	{
		Images[Imgindex] = ImageBIT;
	}

}

Gdiplus::Bitmap* FindImage(Gdiplus::Bitmap* ImageBIT, vector<Gdiplus::Bitmap*> Images, UINT ImgCount)
{
	if (Images.size() == NULL) return; 

	for (UINT FindImgIndex = 0; FindImgIndex < ImgCount; FindImgIndex++)
	{
		auto findImg = find(Images.begin(), Images.end(), ImageBIT);

		if (findImg != Images.end())
		{
			cout << "Found : " << ImageBIT << "at Position " << distance(Images.begin(), findImg) << endl; 
			return ImageBIT;
		}
	}
	return;
}

// �ִϸ��̼����� �׸� �̹����� �̹����� ���̸� �޾ƿͼ�, 
// �̹����� ���� images �� ����Ǿ� ����. 
void createAnim(vector<Gdiplus::Bitmap*> Images, UINT Imgwidth, UINT imgheight)
{

}
