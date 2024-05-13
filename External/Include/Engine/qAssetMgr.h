#pragma once

class qAsset;

class qAssetMgr : public qSingleton<qAssetMgr>
{
	SINGLE(qAssetMgr);

public:
	void Init();

	qAsset* FindAsset(ASSET_TYPE _Type, const wstring& _Key);
	//void AddAsset(const wstring& _Key, qAsset* _Asset);

	template<typename T>
	T* FindAsset(const wstring& _Key);

	template<typename T>
	void AddAsset(const wstring& _Key, T* _Asset);

private:
	map<wstring, qAsset*> m_mapAsset[(UINT)ASSET_TYPE::END];
};

template<typename T>
T* qAssetMgr::FindAsset(const wstring& _Key)
{
	ASSET_TYPE Type = GetAssetType<T>();

	map<wstring, qAsset*>::iterator iter = m_mapAsset[(UINT)Type].find(_Key);

	if (iter == m_mapAsset[(UINT)Type].end())
		return nullptr;

	return (T*)iter->second;
}


template<typename T>
void qAssetMgr::AddAsset(const wstring& _Key, T* _Asset)
{
	ASSET_TYPE Type = GetAssetType<T>();

	assert(!FindAsset(Type, _Key));

	m_mapAsset[(UINT)Type].insert(make_pair(_Key, _Asset));
}

