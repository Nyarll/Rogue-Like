//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   日付
//!
//! @author 制作者名
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"

#include "SceneManager.h"

#include "SceneTitle.h"
#include "ScenePlay.h"
#include "SceneResult.h"


// <Gameクラス> ****************************************************************

// メンバ関数の定義 ========================================================
//------------------------------------------------------------------
//! @brief デフォルトコンストラクタ
//!
//! @param[in] なし
//------------------------------------------------------------------
Game::Game()
{
	SceneManager& scene_manager = SceneManager::singleton();

	scene_manager.AddScene(SCENE_TITLE, SceneTitle::Create);
	scene_manager.AddScene(SCENE_PLAY, ScenePlay::Create);
	scene_manager.AddScene(SCENE_RESULT, SceneResult::Create);

	scene_manager.SetStartScene(SCENE_TITLE);
}



//------------------------------------------------------------------
//! @brief デストラクタ
//------------------------------------------------------------------
Game::~Game()
{

}



//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::Initialize(void)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}



//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::Update(void)
{
	InputManager& input = InputManager::singleton();
	input.Update();
	SceneManager& scene_manager = SceneManager::singleton();
	scene_manager.UpdateActiveScene();
}



//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::Render(void)
{
	SceneManager& scene_manager = SceneManager::singleton();
	scene_manager.RenderActiveScene();
}



//----------------------------------------------------------------------
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::Finalize(void)
{

}
