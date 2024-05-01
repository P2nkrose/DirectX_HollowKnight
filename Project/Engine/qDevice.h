#pragma once

// DirectX 관련 기능을 담당
// GPU 제어

class qDevice : public qSingleton<qDevice>
{
	SINGLE(qDevice);
	

public:
	int Init(HWND _hWnd, UINT _Width, UINT _Height);


private:
	HWND						m_hWnd;
	Vec2						m_vResolution;

	ID3D11Device*				m_Device;
	ID3D11DeviceContext*		m_Context;

	IDXGISwapChain*				m_SwapChain;

	ID3D11Texture2D*			m_RTTex;
	ID3D11Texture2D*			m_DSTex;

	ID3D11RenderTargetView*		m_RTView;
	ID3D11DepthStencilView*		m_DSView;

	ID3D11BlendState*			m_BSState;
	ID3D11DepthStencilState*	m_DSState;
	ID3D11SamplerState*			m_Sampler;
	ID3D11RasterizerState*		m_RSState;
};

