#include "PathMgr.h"

void PathMgr::intializePath()
{
	// ���� �۾��ϴ� ���丮 ��θ� �޾ƿ´�. 
	GetCurrentDirectory(255, m_szContentPath);
	// ���� ������ �ѹ� ������ �Ѵ�. 
 
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
	// ���� ��θ� �̾��ش�. 

	SetWindowText(g_hWnd, m_szContentPath);
}