#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "Msimg32.lib")	

LPCTSTR g_title = TEXT("������ Ÿ��Ʋ�ٿ� ǥ���� ���ڿ�");
LPCTSTR g_szClassName = TEXT("������ Ŭ���� �̸�");

int g_width = 1024;
int g_height = 768;

HWND g_hWnd;
HDC g_FrontBufferDC;    // �ո� DC
HDC g_BackBufferDC;    // �޸� DC
HBITMAP g_BackBufferBitmap;

// �ܼ� �ʱ�ȭ
void InitConsole()
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	SetConsoleTitle(L"������ �޽��� �ܼ� �α�");
	printf("�ܼ� �α� ����...\n\n");
}

void UninitConsole()
{
	// ǥ�� ��� ��Ʈ�� �ݱ�
	fclose(stdout);
	// �ܼ� ����
	FreeConsole();
}

// WIN32 API ���� ���� ���� ���� �޼����� ����ϴ� �Լ�
void PrintLastErrorMessage()
{
	DWORD errorCode = GetLastError();
	LPVOID lpMsgBuf;

	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // �⺻ ���
		(LPSTR)&lpMsgBuf,
		0,
		NULL);

	if (lpMsgBuf)
	{
		printf("���� �ڵ�: %lu\n���� �޽���: %s\n", errorCode, (char*)lpMsgBuf);
		LocalFree(lpMsgBuf); // �Ҵ�� ���� ����
	}
	else
	{
		printf("���� �ڵ�: %lu (�޽����� ã�� �� ����)\n", errorCode);
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	InitConsole();  // �ܼ� ��� �ʱ�ȭ

	char szPath[MAX_PATH] = { 0, };
	::GetCurrentDirectoryA(MAX_PATH, szPath);
	printf("Current Directory: %s\n", szPath);

	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = g_szClassName;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	// �⺻ Ŀ�� ���
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// �⺻ ������ ���
	RegisterClass(&wc);

	// ���ϴ� ũ�Ⱑ �����Ǿ� ����
	RECT rcClient = { 0, 0, (LONG)g_width, (LONG)g_height };
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	//����
	HWND hwnd = CreateWindow(
		g_szClassName,
		g_title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	////////Renderer::Initialize
	g_FrontBufferDC = GetDC(hwnd); //������ Ŭ���̾�Ʈ ������ DeviceContext���
	g_BackBufferDC = CreateCompatibleDC(g_FrontBufferDC); // ȣȯ�Ǵ� DeviceContext ����
	g_BackBufferBitmap = CreateCompatibleBitmap(g_FrontBufferDC, g_width, g_height); // �޸� ��������
	SelectObject(g_BackBufferDC, g_BackBufferBitmap); // MemDC�� �޸𸮿��� ����

	// DeviceContext ������ HBitmap ����
	HDC hImageDC = CreateCompatibleDC(g_FrontBufferDC); // ȣȯ�Ǵ� DeviceContext ����
	HBITMAP hImageBitmap = (HBITMAP)LoadImage(
		NULL,                    // �ν��Ͻ� �ڵ� (�����̹Ƿ� NULL)
		L"../Resource/elf24.bmp",          // BMP ���� ���
		IMAGE_BITMAP,            // ��Ʈ�� �ε�
		0, 0,                    // ũ�� �ڵ� (���� ũ��)
		LR_LOADFROMFILE        // �ܺ� ���Ͽ��� �ε�
	);	
	BITMAP bmpInfo; // ���ο� ũ�� ������ �ִ�.
	GetObject(hImageBitmap, sizeof(BITMAP), &bmpInfo);


	if (!hImageBitmap)
		PrintLastErrorMessage();

	SelectObject(hImageDC, hImageBitmap); 


	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Renderer::BeginDraw()
		PatBlt(g_BackBufferDC, 0, 0, g_width, g_height, BLACKNESS);

		// Render()
		// ��ü �̹��� �״�� �����ϱ�
		BitBlt(g_BackBufferDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, hImageDC, 0, 0, SRCCOPY);

		//Ư�� �÷�(�÷�Ű)�� �����ϰ� �׸���
		TransparentBlt(g_BackBufferDC, bmpInfo.bmWidth, 0, bmpInfo.bmWidth, bmpInfo.bmHeight,
			hImageDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, 
			RGB(255,255,255));	// Msimg32.lib ��ũ �ʿ�

		// Renderer::EndDraw()
		BitBlt(g_FrontBufferDC, 0, 0, g_width, g_height, g_BackBufferDC, 0, 0, SRCCOPY);
	}

	DeleteObject(hImageBitmap);
	DeleteDC(hImageDC);

	// Renderer::Uninitialize
	DeleteObject(g_BackBufferBitmap);
	DeleteDC(g_BackBufferDC);
	ReleaseDC(hwnd, g_FrontBufferDC);
	//////////////////////////////////////////////////////////////////////////

	UninitConsole();  // �ܼ� ��� ����
	return (int)msg.wParam;
}
