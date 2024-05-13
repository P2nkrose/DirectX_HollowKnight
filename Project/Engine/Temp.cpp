#include "pch.h"
#include "Temp.h"

#include "qDevice.h"
#include "qPathMgr.h"
#include "qKeyMgr.h"
#include "qTimeMgr.h"
#include "qAssetMgr.h"

#include "qEntity.h"
#include "qMesh.h"
#include "qConstBuffer.h"
#include "qGraphicShader.h"

tTransform g_ObjTrans = {};



int TempInit()
{
	g_ObjTrans.Scale = Vec4(1.2f, 1.2f, 1.2f, 1.f);

	

	return S_OK;
}

void TempTick()
{
	float dt = qTimeMgr::GetInst()->GetDeltaTime();

	if (qKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::PRESSED)
	{
		g_ObjTrans.Pos.x -= dt * 1.f;
	}

	if (qKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::PRESSED)
	{
		g_ObjTrans.Pos.x += dt * 1.f;
	}

	if (qKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::PRESSED)
	{
		g_ObjTrans.Pos.y += dt * 1.f;
	}

	if (qKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::PRESSED)
	{
		g_ObjTrans.Pos.y -= dt * 1.f;
	}

	qConstBuffer* pTransformCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pTransformCB->SetData(&g_ObjTrans);
}

void TempRender()
{
	qConstBuffer* pTransformCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pTransformCB->Binding();

	qMesh* pRectMesh = qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh");
	qGraphicShader* pShader = qAssetMgr::GetInst()->FindAsset<qGraphicShader>(L"TestShader");


	pShader->Binding();
	pRectMesh->render();
}

void TempRelease()
{

}

