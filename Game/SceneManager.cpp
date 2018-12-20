//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneManager.cpp
//!
//! @brief  シーン管理クラスのソースファイル
//!
//! @date   2018/11/14
//!
//! @author S.Takaki
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "SceneManager.h"

#include <cassert>

#include "Scene.h"




// <SceneManagerクラス> ********************************************************

// メンバ関数の定義 ========================================================
//----------------------------------------------------------------------
//! @brief デフォルトコンストラクタ
//!
//! @param[in] なし
//----------------------------------------------------------------------
SceneManager::SceneManager()
{
	m_active_scene = nullptr;
	m_next_scene_id = SCENE_NONE;

	for (int i = 0; i < NUM_SCENES; i++)
	{
		m_scene_factory_methods[i] = nullptr;
	}
}



//----------------------------------------------------------------------
//! @brief デストラクタ
//----------------------------------------------------------------------
SceneManager::~SceneManager()
{
	delete m_active_scene;
}


//----------------------------------------------------------------------
//! @brief シーンの追加
//!
//! @param[in] scene_id       登録するシーンのID
//! @param[in] factory_method 登録するシーンの生成用関数
//!
//! @return なし
//----------------------------------------------------------------------
void SceneManager::AddScene(SceneID scene_id, FactoryMethod factory_method)
{
	assert(scene_id >= 0 && scene_id < NUM_SCENES && "シーンIDが不正です。");
	assert(factory_method && "生成用関数が指定されていません。");

	m_scene_factory_methods[scene_id] = factory_method;
}



//----------------------------------------------------------------------
//! @brief 開始シーンの設定
//!
//! @param[in] scene_id 開始シーンのID
//!
//! @return なし
//----------------------------------------------------------------------
void SceneManager::SetStartScene(SceneID scene_id)
{
	assert(scene_id >= 0 && scene_id < NUM_SCENES && "シーンIDが不正です。");

	ChangeScene(scene_id);
}



//----------------------------------------------------------------------
//! @brief 活動中のシーンの更新
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void SceneManager::UpdateActiveScene()
{
	assert(m_active_scene && "活動中のシーンがありません。");

	// シーンの変更（要求があった場合)
	if (m_next_scene_id != SCENE_NONE)
	{
		ChangeScene(m_next_scene_id);
		m_next_scene_id = SCENE_NONE;
	}


	// 活動中のシーンの更新
	m_active_scene->Update();
}



//----------------------------------------------------------------------
//! @brief 活動中のシーンの描画
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void SceneManager::RenderActiveScene()
{
	assert(m_active_scene && "活動中のシーンがありません。");

	// 活動中のシーンの描画
	m_active_scene->Render();
}



//----------------------------------------------------------------------
//! @brief シーン変更の要求
//!        ※実際にはUpdate時に変更される
//!
//! @param[in] scene_id 変更を要求するシーンのID
//!
//! @return なし
//----------------------------------------------------------------------
void SceneManager::RequestScene(SceneID scene_id)
{
	assert(scene_id >= 0 && scene_id < NUM_SCENES && "シーンIDが不正です。");

	m_next_scene_id = scene_id;
}



//----------------------------------------------------------------------
//! @brief シーン変更
//!
//! @param[in] scene_id 変更したいシーンのID
//!
//! @return なし
//----------------------------------------------------------------------
void SceneManager::ChangeScene(SceneID scene_id)
{
	assert(scene_id >= 0 && scene_id < NUM_SCENES && "シーンIDが不正です。");
	assert(m_scene_factory_methods[scene_id] && "生成用関数が登録されていません。");

	// 活動中のシーンの削除
	if (m_active_scene != nullptr)
	{
		m_active_scene->Finalize();
		delete m_active_scene;
		m_active_scene = nullptr;
	}


	// 新しいシーンの生成
	m_active_scene = m_scene_factory_methods[scene_id]();
	m_active_scene->Initialize();
}
