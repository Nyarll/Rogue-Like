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
#include "SoundManager.h"

#include "DemoScene.h"
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
	SoundManager& sound_manager = SoundManager::singleton();

	scene_manager.AddScene(SCENE_DEMO, DemoScene::Create);
	scene_manager.AddScene(SCENE_TITLE, SceneTitle::Create);
	scene_manager.AddScene(SCENE_PLAY, ScenePlay::Create);
	scene_manager.AddScene(SCENE_RESULT, SceneResult::Create);

	scene_manager.SetStartScene(SCENE_DEMO);

	sound_manager.SoundRegister(GameBGM, "Resources/Sound/bgm/Dungeon.mp3");
	sound_manager.SoundRegister(AttackSE, "Resources/Sound/se/Attack.wav");
	sound_manager.SoundRegister(FloorChange, "Resources/Sound/se/FloorChange.wav");
	sound_manager.SoundRegister(TitleBGM, "Resources/Sound/bgm/TitleBGM.mp3");
	sound_manager.SoundRegister(Demo, "Resources/Sound/se/LogoSound.wav");
	sound_manager.SoundRegister(Decision, "Resources/Sound/se/Decision.wav");
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
	InputManager::singleton().Update();
	SceneManager::singleton().UpdateActiveScene();
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
	SceneManager::singleton().RenderActiveScene();
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
