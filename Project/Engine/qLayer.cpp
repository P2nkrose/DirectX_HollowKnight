#include "pch.h"
#include "qLayer.h"

#include "qGameObject.h"

qLayer::qLayer(int _LayerIdx)
	: m_LayerIdx(_LayerIdx)
{
}

qLayer::~qLayer()
{
	Delete_Vec(m_Parents);
}

void qLayer::Begin()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->Begin();
	}
}

void qLayer::Tick()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->Tick();
	}
}

void qLayer::FinalTick()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->FinalTick();
	}
}

void qLayer::AddObject(qGameObject* _Object)//, bool _bChildMove)
{
	// 1. 오브젝트가 다른 레이어 소속인 경우
	if (-1 != _Object->GetLayerIdx())
	{
		// 기존에 소속된 레이어에서 빠져나와야 한다.
	}

	// 2. 부모 오브젝트가 있는 경우
	if (_Object->GetParent())
	{
		_Object->m_LayerIdx = m_LayerIdx;
	}
	else
	{
		m_Parents.push_back(_Object);
	}
}


