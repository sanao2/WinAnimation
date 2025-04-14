#pragma once
#include "pch.h"


class Res 
{
private : 
	wchar_t m_strKey;			// �̹��� Ű�� 
	wchar_t m_strRelativePath;   // �̹��� ����� 
	
public:
	void SetKey(const char& _strKey) { m_strKey = _strKey;  }
	void SetRelativePath(const wchar_t& _strPath) { m_strRelativePath = _strPath; } 

	const wchar_t& GetKey() { return m_strKey; }
	const wchar_t& GetRelativePath() { return m_strRelativePath; }

	Res();
	~Res();

};