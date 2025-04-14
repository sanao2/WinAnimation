#include "Time.h"
#include <windows.h>

namespace Time
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER prevCounter;
	LARGE_INTEGER currentCounter;
	LARGE_INTEGER intialCounter;
	float deltaTime;

	void InitTime()
	{
		QueryPerformanceFrequency(&frequency);	// ���� Ÿ�̸Ӱ� 1�� ���� ������ų�� �ִ� TickCount ��
		QueryPerformanceCounter(&intialCounter);  // �ʱ� TickCount ��
		prevCounter = intialCounter;
	}

	void UpdateTime()
	{
		QueryPerformanceCounter(&currentCounter); // ���� TickCount ��
		deltaTime = static_cast<float>(currentCounter.QuadPart - prevCounter.QuadPart) /
			static_cast<float>(frequency.QuadPart);  // ī�������̸� �ð� �ʴ����� ��ȯ

		prevCounter = currentCounter;
	}

	float GetDeltaTime()
	{
		return deltaTime;
	}
	float GetTotalTime()
	{
		return static_cast<float>(currentCounter.QuadPart - intialCounter.QuadPart) /
			static_cast<float>(frequency.QuadPart);  // ī�������̸� �ð� �ʴ����� ��ȯ
	}
}