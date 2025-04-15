#include "PathMgr.h"

void PathMgr::intializePath()
{
	// 현재 작업하는 디렉토리 경로를 받아온다. 
	GetCurrentDirectory(255, m_szContentPath);
	// 상위 폴더로 한번 나가야 한다. 
 
	int len = wcslen(m_szContentPath);

	for (int i = len - 1; i <= 0; )
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}
	wcscat_s(m_szContentPath, 255, L"\\Resource\\");
	// 현재 경로를 이어준다. 

	SetWindowText(g_hWnd, m_szContentPath);
}