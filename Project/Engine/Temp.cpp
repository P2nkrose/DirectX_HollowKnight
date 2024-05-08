#include "pch.h"
#include "Temp.h"

#include "qDevice.h"
#include "qPathMgr.h"
#include "qKeyMgr.h"
#include "qTimeMgr.h"

// Vertex Buffer 버텍스 버퍼
ID3D11Buffer* g_VB = nullptr;
Vtx g_Vtx[3] = {};



// 버텍스 쉐이더 (Vertex Shader) 제작
ID3DBlob*			g_VSBlob = nullptr;
ID3D11VertexShader* g_VS = nullptr;

// 픽셀 쉐이더 (Pixel Shader) 제작
ID3DBlob*			g_PSBlob = nullptr;
ID3D11PixelShader*	g_PS = nullptr;

ID3DBlob*			g_ErrBlob = nullptr;

// 레이아웃 (InputLayout)
ID3D11InputLayout*	g_Layout = nullptr;

int TempInit()
{
	// 버텍스 버퍼 생성
	g_Vtx[0].vPos = Vec3(0.f, 1.f, 0.f);
	g_Vtx[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	g_Vtx[1].vPos = Vec3(1.f, -1.f, 0.f);
	g_Vtx[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	g_Vtx[2].vPos = Vec3(-1.f, -1.f, 0.f);
	g_Vtx[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);


	D3D11_BUFFER_DESC tVtxBufferDesc = {};

	tVtxBufferDesc.ByteWidth = sizeof(Vtx) * 3;				// 버텍스버퍼데스크의 크기
	tVtxBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 버텍스버퍼의 용도

	// Vertex Buffer가 생성된 이후에도 데이터 쓰기가 가능하도록 설정
	tVtxBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tVtxBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	tVtxBufferDesc.MiscFlags = 0;
	tVtxBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = g_Vtx;

	if (FAILED(DEVICE->CreateBuffer(&tVtxBufferDesc, &tSub, &g_VB)))
	{
		MessageBox(nullptr, L"VertexBuffer 생성 실패", L"Temp 초기화 실패", MB_OK);
		return E_FAIL;
	}


	// ===================
	//  Vertex Shader 생성
	// ===================
	wstring strShaderPath = qPathMgr::GetInst()->GetContentPath();


	HRESULT hr = D3DCompileFromFile((strShaderPath + L"shader\\test.fx").c_str()
								    , nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
								    , "VS_Test", "vs_5_0", D3DCOMPILE_DEBUG, 0, &g_VSBlob, &g_ErrBlob);


	if (FAILED(hr))
	{
		if (nullptr != g_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)g_ErrBlob->GetBufferPointer(), "쉐이더 컴파일 실패", MB_OK);
		}
		else
		{
			errno_t err = GetLastError();
			WCHAR szErrMsg[255] = {};
			swprintf_s(szErrMsg, 255, L"Error Code : %d", err);
			MessageBox(nullptr, szErrMsg, L"쉐이더 컴파일 실패", MB_OK);
		}

		return E_FAIL;
	}

	DEVICE->CreateVertexShader(g_VSBlob->GetBufferPointer()
							 , g_VSBlob->GetBufferSize()
							 , nullptr, &g_VS);


	// ===================
	//  Pixel Shader 생성
	// ===================

	hr = D3DCompileFromFile((strShaderPath + L"shader\\test.fx").c_str()
		, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "PS_Test", "ps_5_0", D3DCOMPILE_DEBUG, 0, &g_PSBlob, &g_ErrBlob);

	if (FAILED(hr))
	{
		if (nullptr != g_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)g_ErrBlob->GetBufferPointer(), "쉐이더 컴파일 실패", MB_OK);
		}
		else
		{
			errno_t err = GetLastError();
			wchar_t szErrMsg[255] = {};
			swprintf_s(szErrMsg, 255, L"Error Code : %d", err);
			MessageBox(nullptr, szErrMsg, L"쉐이더 컴파일 실패", MB_OK);
		}

		return E_FAIL;
	}

	DEVICE->CreatePixelShader(g_PSBlob->GetBufferPointer()
		, g_PSBlob->GetBufferSize(), nullptr, &g_PS);


	// ===================
	//     Layout 생성
	// ===================
	D3D11_INPUT_ELEMENT_DESC Element[2] = {};

	Element[0].AlignedByteOffset = 0;						
	Element[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	Element[0].InputSlot = 0;
	Element[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Element[0].InstanceDataStepRate = 0;
	Element[0].SemanticName = "POSITION";
	Element[0].SemanticIndex = 0;

	Element[1].AlignedByteOffset = 12;							
	Element[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	Element[1].InputSlot = 0;
	Element[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Element[1].InstanceDataStepRate = 0;
	Element[1].SemanticName = "COLOR";
	Element[1].SemanticIndex = 0;

	

	DEVICE->CreateInputLayout(Element, 2, g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize(), &g_Layout);
	 
	return S_OK;
}

void TempTick()
{
	float dt = qTimeMgr::GetInst()->GetDeltaTime();

	if (qKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::PRESSED)
	{
		for (int i = 0; i < 3; ++i)
		{
			g_Vtx[i].vPos.x -= dt * 1.f;
		}
	}

	if (qKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::PRESSED)
	{
		for (int i = 0; i < 3; ++i)
		{
			g_Vtx[i].vPos.x += dt * 1.f;
		}
	}

	// 전역변수에 있는 정점 데이터를 버텍스버퍼로 쓰기
	D3D11_MAPPED_SUBRESOURCE tMapSub = {};
	CONTEXT->Map(g_VB, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tMapSub);

	memcpy(tMapSub.pData, g_Vtx, sizeof(Vtx) * 3);

	CONTEXT->Unmap(g_VB, 0);
}

void TempRender()
{
	UINT stride = sizeof(Vtx);
	UINT offset = 0;
	CONTEXT->IASetVertexBuffers(0, 1, &g_VB, &stride, &offset);
	CONTEXT->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	// 3개의 점을 하나의 삼각형으로 해석
	CONTEXT->IASetInputLayout(g_Layout);

	CONTEXT->VSSetShader(g_VS, nullptr, 0);
	CONTEXT->PSSetShader(g_PS, nullptr, 0);

	CONTEXT->Draw(3, 0);
}

void TempRelease()
{
	g_VB->Release();
	g_VSBlob->Release();
	g_VS->Release();

	g_PSBlob->Release();
	g_PS->Release();

	g_Layout->Release();

	if (nullptr != g_ErrBlob)
		g_ErrBlob->Release();
}

