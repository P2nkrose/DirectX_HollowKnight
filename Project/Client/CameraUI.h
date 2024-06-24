#pragma once
#include "ComponentUI.h"

class CameraUI : public ComponentUI
{
public:
	CameraUI();
	~CameraUI();

private:
	virtual void Update() override;

	void LayerCheck();



private:
	bool		m_ShowLayerCheck;
};
