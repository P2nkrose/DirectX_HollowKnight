#include "pch.h"
#include "qLevelMgr.h"

#include "qLevel.h"
#include "qLayer.h"
#include "qGameObject.h"
#include "components.h"

#include "qAssetMgr.h"
#include "assets.h"

#include "qPlayerScript.h"
#include "qCameraMoveScript.h"

#include "qCollisionMgr.h"

qLevelMgr::qLevelMgr()
	: m_CurLevel(nullptr)
{

}


qLevelMgr::~qLevelMgr()
{
	if (nullptr != m_CurLevel)
		delete m_CurLevel;
}


qGameObject* qLevelMgr::FindObjectByName(const wstring& _Name)
{
	if (m_CurLevel)
	{
		return m_CurLevel->FindObjectByName(_Name);
	}

	return nullptr;
}




void qLevelMgr::Init()
{
	// Material
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<qMaterial> pDebugShapeMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl");

	Ptr<qTexture> pTexture = qAssetMgr::GetInst()->Load<qTexture>(L"PlayerTex", L"texture\\Character.png");


	pAlphaBlendMtrl->SetTexParam(TEX_0, pTexture);
	
	// Level 생성
	m_CurLevel = new qLevel;

	m_CurLevel->GetLayer(0)->SetName(L"Default");
	m_CurLevel->GetLayer(1)->SetName(L"Background");
	m_CurLevel->GetLayer(2)->SetName(L"Tile");
	m_CurLevel->GetLayer(3)->SetName(L"Player");
	m_CurLevel->GetLayer(4)->SetName(L"Monster");
	m_CurLevel->GetLayer(5)->SetName(L"PlayerProjectile");		// 플레이어 투사체
	m_CurLevel->GetLayer(6)->SetName(L"MonsterProjectile");		// 몬스터 투사체


	// 카메라 오브젝트
	qGameObject* CamObj = new qGameObject;
	CamObj->SetName(L"MainCamera");
	CamObj->AddComponent(new qTransform);
	CamObj->AddComponent(new qCamera);
	CamObj->AddComponent(new qCameraMoveScript);

	// 우선순위를 0 : Main Camera로 설정
	CamObj->Camera()->SetPriority(0);

	// 카메라 레이어 설정 (31번 레이어 제외 모든 레이어를 촬영)
	// 31번 UI임
	CamObj->Camera()->SetLayerAll();
	CamObj->Camera()->SetLayer(31, false);
	CamObj->Camera()->SetFar(100000.f);
	CamObj->Camera()->SetProjType(ORTHOGRAPHIC);
	//CamObj->Camera()->SetProjType(PERSPECTIVE);

	m_CurLevel->AddObject(0, CamObj);


	// ------------------------------------------------

	qGameObject* pObject = nullptr;


	// 광원 오브젝트 추가
	pObject = new qGameObject;
	pObject->SetName(L"PointLight 1");
	pObject->AddComponent(new qTransform);
	pObject->AddComponent(new qLight2D);
	
	pObject->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pObject->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pObject->Light2D()->SetRadius(500.f);
	pObject->Transform()->SetRelativePos(Vec3(-300.f, 0.f, 100.f));

	m_CurLevel->AddObject(0, pObject);



	//pObject = new qGameObject;
	//pObject->SetName(L"PointLight 2");
	//pObject->AddComponent(new qTransform);
	//pObject->AddComponent(new qLight2D);
	//
	//pObject->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	//pObject->Light2D()->SetLightColor(Vec3(0.2f, 0.2f, 0.8f));
	//pObject->Light2D()->SetRadius(500.f);
	//pObject->Transform()->SetRelativePos(Vec3(300.f, 0.f, 100.f));
	//
	//m_CurLevel->AddObject(0, pObject);




	// 플레이어 오브젝트
	pObject = new qGameObject;
	pObject->SetName(L"Player");
	pObject->AddComponent(new qTransform);
	pObject->AddComponent(new qMeshRender);
	pObject->AddComponent(new qCollider2D);
	pObject->AddComponent(new qFlipBookComponent);
	pObject->AddComponent(new qPlayerScript);

	pObject->Transform()->SetRelativePos(0.f, 0.0f, 100.f);
	pObject->Transform()->SetRelativeScale(200.f, 200.f, 1.f);

	pObject->Collider2D()->SetIndependentScale(false);
	pObject->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pObject->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	
	pObject->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pObject->MeshRender()->SetMaterial(pMtrl);
	pObject->FlipBookComponent()->AddFlipBook(5, qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Link_MoveDown"));
	pObject->FlipBookComponent()->Play(5, 10, true);

	m_CurLevel->AddObject(3, pObject);
	


	// ======================================================

	// Child 오브젝트
	//qGameObject* pChild = new qGameObject;
	//pChild->SetName(L"Child");

	//pChild->AddComponent(new qTransform);
	//pChild->AddComponent(new qMeshRender);
	//pChild->AddComponent(new qCollider2D);

	//pChild->Transform()->SetRelativePos(400.f, 0.f, 0.f);
	//pChild->Transform()->SetRelativeScale(100.f, 100.f, 1.f);
	//pChild->Transform()->SetIndependentScale(true);

	//pChild->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	//pChild->Collider2D()->SetScale(Vec3(1.2f, 1.2f, 1.f));

	//pChild->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	//pChild->MeshRender()->SetMaterial(pMtrl);

	//pObject->AddChild(pChild);

	// ======================================================




	//// Monster Object
	//qGameObject* pMonster = new qGameObject;
	//pMonster->SetName(L"Monster");
	//
	//pMonster->AddComponent(new qTransform);
	//pMonster->AddComponent(new qMeshRender);
	//pMonster->AddComponent(new qCollider2D);
	//
	//pMonster->Transform()->SetRelativePos(-400.f, 0.f, 100.f);
	//pMonster->Transform()->SetRelativeScale(150.f, 150.f, 1.f);
	//
	//pMonster->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	//pMonster->Collider2D()->SetScale(Vec3(1.2f, 1.2f, 1.f));
	//
	//pMonster->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	//pMonster->MeshRender()->SetMaterial(pMtrl);
	//
	//m_CurLevel->AddObject(4, pMonster);



	// TileMap Object
	qGameObject* pTileMapObj = new qGameObject;
	pTileMapObj->SetName(L"TileMap");

	pTileMapObj->AddComponent(new qTransform);
	pTileMapObj->AddComponent(new qTileMap);

	pTileMapObj->Transform()->SetRelativePos(Vec3(-500.f, 250.f, 500.f));

	pTileMapObj->TileMap()->SetRowCol(4, 4);
	pTileMapObj->TileMap()->SetTileSize(Vec2(64.f, 64.f));

	Ptr<qTexture> pTileAtlas = qAssetMgr::GetInst()->Load<qTexture>(L"TileAtlasTex", L"texture\\TILE.bmp");
	pTileMapObj->TileMap()->SetAtlasTexture(pTileAtlas);
	pTileMapObj->TileMap()->SetAtlasTileSize(Vec2(64.f, 64.f));


	m_CurLevel->AddObject(2, pTileMapObj);





	// 충돌 지정
	qCollisionMgr::GetInst()->CollisionCheck(3, 4);		// Player vs Monster
	qCollisionMgr::GetInst()->CollisionCheck(5, 4);		// Player Projectile vs Monster


	pMtrl->Save(L"material\\std2d.mtrl");
	
	// 레벨 시작
	//m_CurLevel->Begin();
}

void qLevelMgr::Progress()
{
	if (m_CurLevel->GetState() == LEVEL_STATE::PLAY)
	{
		m_CurLevel->Tick();
	}

	m_CurLevel->ClearObject();
	m_CurLevel->FinalTick();
}

