#include "pch.h"
#include "qEngine.h"

#include "qDevice.h"
#include "qPathMgr.h"
#include "qKeyMgr.h"
#include "qTimeMgr.h"
#include "Temp.h"

qEngine::qEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
{
}

qEngine::~qEngine()
{
	TempRelease();
}

int qEngine::Init(HWND _wnd, POINT _ptResolution)
{
	m_hWnd = _wnd;
	m_ptResolution = _ptResolution;
	ChangeWindowScale(_ptResolution.x, _ptResolution.y);

	if (FAILED(qDevice::GetInst()->Init(m_hWnd, m_ptResolution.x, m_ptResolution.y)))
	{
		MessageBox(nullptr, L"��ġ �ʱ�ȭ ����", L"CDevice �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// Manager �ʱ�ȭ
	qPathMgr::GetInst()->Init();
	qKeyMgr::GetInst()->Init();
	qTimeMgr::GetInst()->Init();


	if (FAILED(TempInit()))
	{
		MessageBox(nullptr, L"TempInit ����", L"qEngine �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void qEngine::Progress()
{
	// Manager
	qKeyMgr::GetInst()->Tick();
	qTimeMgr::GetInst()->Tick();

	TempTick();
	
	// Render
	qDevice::GetInst()->Clear();

	TempRender();

	qDevice::GetInst()->Present();
}


void qEngine::ChangeWindowScale(UINT _Width, UINT _Height)
{
	bool bMenu = false;
	if (GetMenu(m_hWnd))
		bMenu = true;

	RECT rt = { 0, 0, _Width, _Height };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, bMenu);
	SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}