//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneManager.h
//!
//! @brief  シーン管理クラスのヘッダファイル
//!
//! @date   2018/11/14
//!
//! 
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once

#include "Singleton.h"
#include "Define.h"

// 定数の定義 ==============================================================
enum SceneID
{
	SCENE_NONE = -1,
	SCENE_DEMO,
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_RESULT,

	NUM_SCENES
};




// クラスの宣言 ============================================================
class Scene;




// クラスの定義 ============================================================

// <シーン管理> ------------------------------------------------------
class SceneManager extends Singleton<SceneManager>
{
	// エイリアス宣言
	using FactoryMethod = Scene*(*)();


	// データメンバの宣言
private:
	Scene*        m_active_scene;     // 活動中のシーン
	SceneID       m_next_scene_id;    // 変更予定のシーンのID
	FactoryMethod m_scene_factory_methods[NUM_SCENES];    // 各シーンのファクトリメソッド


// メンバ関数の宣言
private:
	friend class Singleton<SceneManager>;
	// コンストラクタ
	SceneManager();

public:
	// デストラクタ
	virtual ~SceneManager();

public:
	// 操作
	void AddScene(SceneID scene_id, FactoryMethod factory_method);    // シーンの追加
	void SetStartScene(SceneID scene_id);    // 開始シーンの設定

	void UpdateActiveScene();    // 活動中のシーンの更新
	void RenderActiveScene();    // 活動中のシーンの描画

	void RequestScene(SceneID scene_id);    // シーン変更の要求


private:
	// 内部実装
	void ChangeScene(SceneID scene_id);    // シーン変更


	// 複製の禁止
	SceneManager(const SceneManager&) = delete;               // コピーコンストラクタの削除
	SceneManager& operator=(const SceneManager&) = delete;    // 代入演算子の削除
	SceneManager(SceneManager&&) = delete;                    // ムーブコンストラクタの削除
	SceneManager& operator=(SceneManager&&) = delete;         // ムーブ代入演算子の削除
};



// マクロの定義
//#define TheSceneManager SceneManager::GetInstance()