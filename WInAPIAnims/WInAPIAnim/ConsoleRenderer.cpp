#include "ConsoleRenderer.h"


namespace ConsoleRender
{
    HANDLE hConsoleHandle;                      // �ʱ� ȭ�� �ܼ��� �ڵ�

    int nScreenWidth = ScreenWidth;             // �ܼ�â�� �ʺ�
    int nScreenHeight = ScreenHeight;           // �ܼ�â�� ����
    int nScreenBufferSize = 0;                  // �ܼ�â�� ��ũ������ ũ��
    int nScreenBufferIndex = 0;                 // �ܼ�â�� ����� ��ũ�������� �ε���

	HANDLE hScreenBuffer[2];                    // �ܼ�â�� ����� ��ũ�������� �ڵ�

    void ScreenInit() // Ŀ�� ������ ���� 
    {
        // ���� ȭ��ũ�⿡ �´� ȭ�� �ֽܼ�ũ������ 2���� �����.    
        hConsoleHandle   =  GetStdHandle(STD_OUTPUT_HANDLE);
        hScreenBuffer[0] =  CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        hScreenBuffer[1] =  CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

        // �⺻ �ܼ�,������ �ֽܼ�ũ�� ��� Ŀ�� �Ⱥ��̰� ����
        CONSOLE_CURSOR_INFO cursorInfo = { 0, };
        cursorInfo.bVisible = FALSE;
        cursorInfo.dwSize = 1; // Ŀ���� ũ�⸦ ���� (1~100 ���̸� ����)
        SetConsoleCursorInfo(hConsoleHandle, &cursorInfo);
        SetConsoleCursorInfo(hScreenBuffer[0], &cursorInfo);
        SetConsoleCursorInfo(hScreenBuffer[1], &cursorInfo);

        //�⺻ �ܼ��� ȭ�� ũ�� ������ ��´�.
        CONSOLE_SCREEN_BUFFER_INFO Info; // �ʱ� ȭ�� �ܼ��� ȭ�� ����
        GetConsoleScreenBufferInfo(hConsoleHandle, &Info);

        nScreenHeight = Info.srWindow.Bottom - Info.srWindow.Top + 1;
        nScreenWidth = Info.srWindow.Right - Info.srWindow.Left + 1;
        nScreenBufferSize = nScreenWidth * nScreenHeight;
    }

    void ScreenFlipping()
    {
        // ���� �ܼ��� ����� ��ũ�������� Handle�� �����Ͽ� ȭ�鿡 �����ش�.
        SetConsoleActiveScreenBuffer(hScreenBuffer[nScreenBufferIndex]);

        // ������ ����� ��ũ�� ������ �ε����� �������� �غ��Ѵ�.
        nScreenBufferIndex++;
        nScreenBufferIndex = nScreenBufferIndex % 2;  // 0,1,0,1,0,1,0,1....
    }

    void ScreenClear()
    {
        COORD Coor = { 0, 0 };
        DWORD dw;
        FillConsoleOutputCharacter(hScreenBuffer[nScreenBufferIndex], ' ', nScreenBufferSize, Coor, &dw);
    }

    
    void ScreenRelease()
    {
        CloseHandle(hScreenBuffer[0]);
        CloseHandle(hScreenBuffer[1]);
    }

    /*
        FOREGROUND_BLUE	�ؽ�Ʈ ���� �Ķ����� ���Ե˴ϴ�.
        COMMON_LVB_LEADING_BYTE	���� ����Ʈ�Դϴ�.

        https://learn.microsoft.com/ko-kr/windows/console/console-screen-buffers#character-attributes
    */


    bool ScreenDrawChar(int x, int y, char ch, WORD attr)
    {
        COORD	cdPos;
        BOOL	bRval = FALSE;
        DWORD	dwCharsWritten;
        cdPos.X = x;
        cdPos.Y = y;
       
        bRval = FillConsoleOutputCharacterA(hScreenBuffer[nScreenBufferIndex], ch, 1, cdPos, &dwCharsWritten);
        if (bRval == false) OutputDebugStringA("Error, FillConsoleOutputCharacter()\n");

        bRval = FillConsoleOutputAttribute(hScreenBuffer[nScreenBufferIndex], attr, 1, cdPos, &dwCharsWritten);
        if (bRval == false) OutputDebugStringA("Error, FillConsoleOutputAttribute()\n");
        return bRval;
    }
	bool ScreenDrawChar(int x, int y, wchar_t ch, WORD attr)
	{
		COORD	cdPos;
		BOOL	bRval = FALSE;
		DWORD	dwCharsWritten;
		cdPos.X = x;
		cdPos.Y = y;

		bRval = FillConsoleOutputCharacterW(hScreenBuffer[nScreenBufferIndex], ch, 1, cdPos, &dwCharsWritten);
		if (bRval == false) OutputDebugStringA("Error, FillConsoleOutputCharacter()\n");

		bRval = FillConsoleOutputAttribute(hScreenBuffer[nScreenBufferIndex], attr, 1, cdPos, &dwCharsWritten);
		if (bRval == false) OutputDebugStringA("Error, FillConsoleOutputAttribute()\n");
		return bRval;
	}


    bool ScreenDrawString(int x, int y, const char* pStr, WORD attr)
    {
        COORD	cdPos;
        BOOL	bRval = FALSE;
        DWORD	dwCharsWritten;
        cdPos.X = x;
        cdPos.Y = y;

        DWORD nNumberOfBytesToWrite = (DWORD)strlen(pStr);
		//Ư�� ��ġ�� ���ڿ��� ����Ѵ�.
        WriteConsoleOutputCharacterA(hScreenBuffer[nScreenBufferIndex], pStr, nNumberOfBytesToWrite, cdPos, &dwCharsWritten);
        bRval = FillConsoleOutputAttribute(hScreenBuffer[nScreenBufferIndex], attr, nNumberOfBytesToWrite, cdPos, &dwCharsWritten);
        if (bRval == false) OutputDebugStringA("Error, FillConsoleOutputAttribute()\n");
        return bRval;
    }

	bool ScreenDrawString(int x, int y, const wchar_t* pStr, WORD attr)
	{
		COORD	cdPos;
		BOOL	bRval = FALSE;
		DWORD	dwCharsWritten;
		cdPos.X = x;
		cdPos.Y = y;
    
		DWORD nNumberOfBytesToWrite = (DWORD)wcslen(pStr);
		//Ư�� ��ġ�� ���ڿ��� ����Ѵ�.
		WriteConsoleOutputCharacterW(hScreenBuffer[nScreenBufferIndex], pStr, nNumberOfBytesToWrite, cdPos, &dwCharsWritten);
        bRval = FillConsoleOutputAttribute(hScreenBuffer[nScreenBufferIndex], attr, nNumberOfBytesToWrite * 2, cdPos, &dwCharsWritten);
        if (bRval == false) OutputDebugStringA("Error, FillConsoleOutputAttribute()\n");
		return bRval;
	}

    bool ScreenSetAttributes(WORD attr)
    {
        COORD	cdPos;
        bool	bRval = FALSE;
        DWORD	dwCharsWritten;
        //	int x,y;	

        cdPos.X = 0;
        cdPos.Y = 0;
        bRval = FillConsoleOutputAttribute(hScreenBuffer[nScreenBufferIndex], attr, nScreenBufferSize, cdPos, &dwCharsWritten);
        if (bRval == false)
        {
            OutputDebugStringA("Error, FillConsoleOutputCharacter()\n");
            return bRval;
        }

        return bRval;
    }


    /*int ScreenWidth()
    {
        return nScreenWidth;
    }
    int ScreenHeight()
    {
        return nScreenHeight;
    }*/

};



