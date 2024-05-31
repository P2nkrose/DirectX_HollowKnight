#include "pch.h"
#include "qPlayerScript.h"

qPlayerScript::qPlayerScript()
	: m_Speed(500.f)
{
}

qPlayerScript::~qPlayerScript()
{
}

void qPlayerScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::LEFT))
	{
		vPos.x -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		vPos.x += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::UP))
	{
		vPos.y += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		vPos.y -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::Z))
	{
		MeshRender()->GetMaterial()->SetScalarParam(INT_0, 1);
	}
	else
	{
		MeshRender()->GetMaterial()->SetScalarParam(INT_0, 0);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		//DrawDebugRect(Transform()->GetWorldMat(), Vec4(1.f, 0.4f, 0.6f, 1.f), 3.f, true);
		DrawDebugCircle(Transform()->GetRelativePos(), 100.f, Vec4(0.4f, 1.f, 0.6f, 1.f), 5.f, false);
	}


	Transform()->SetRelativePos(vPos);
}
