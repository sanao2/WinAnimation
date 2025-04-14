#pragma once
#include "pch.h"


class Res 
{
private : 
	wchar_t m_strKey;			// 이미지 키값 
	wchar_t m_strRelativePath;   // 이미지 상대경로 
	
public:
	void SetKey(const char& _strKey) { m_strKey = _strKey;  }
	void SetRelativePath(const wchar_t& _strPath) { m_strRelativePath = _strPath; } 

	const wchar_t& GetKey() { return m_strKey; }
	const wchar_t& GetRelativePath() { return m_strRelativePath; }

	Res();
	~Res();

};