#pragma once
#include "pch.h"

class PathMgr
{
private : 
	HWND g_hWnd;
	wchar_t* m_szContentPath; 

public : 
	void intializePath(); 
	const wchar_t* GetContentPath() { return m_szContentPath; }


};

