#include "Render.h"


void Initialize()
{
	frontBufferDC = GetDC(g_hWnd);						//윈도우 클라이언트 영역의 DeviceContext얻기
	backBufferDC = CreateCompatibleDC(frontBufferDC);   // 호환되는 DeviceContext 생성
	backBufferImageDC = CreateCompatibleBitmap(frontBufferDC, ImageWidth, ImageHeight); // 메모리 영역생성
	SelectObject(backBufferDC, backBufferImageDC);       // MemDC의 메모리영역 지정
	// 후면 버퍼와 후면에 완성된 비트맵을 연결?

	Gdiplus::GdiplusStartupInput GSI;
	Gdiplus::GdiplusStartup(&GDIplusToken, &GSI, nullptr);
	backBufferGraphics = Gdiplus::Graphics::FromHDC(backBufferDC); // 후면 버퍼와 연결 
}

// 경로 안에 있는 모든 파일을 가져와서 벡터 images 에 넣어놓는다. 
void loadImage(Gdiplus::Bitmap* ImageBIT, wchar_t* filePath, UINT ImgCount)
{
	ImageBIT = new Gdiplus::Bitmap(filePath);

	// 모든 이미지를 벡터 안에 저장 한다. 
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

// 애니메이션으로 그릴 이미지와 이미지의 길이를 받아와서, 
// 이미지는 벡터 images 에 저장되어 있음. 
void createAnim(vector<Gdiplus::Bitmap*> Images, UINT Imgwidth, UINT imgheight)
{

}
