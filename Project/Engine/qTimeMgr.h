#pragma once


class qTimeMgr : public qSingleton<qTimeMgr>
{
	SINGLE(qTimeMgr)
private:
	// LARGE_INTEGER - 8 ����Ʈ ���� ���
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	UINT			m_FPS;

	float			m_DeltaTime;	// ������ ���� �ð�( 1 ������ �����ϴµ� �ɸ��� �ð� )
	float			m_Time;			// ���α׷��� ���� ���ķ� ����� �ð�

public:
	void Init();
	void Tick();

public:
	float GetDeltaTime() { return m_DeltaTime; }
	float GetTime() { return m_Time; }
	UINT GetFPS() { return m_FPS; }
};
