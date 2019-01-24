//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"

#include "SceneManager.h"
#include "SoundManager.h"

#include "DemoScene.h"
#include "SceneTitle.h"
#include "ScenePlay.h"
#include "SceneResult.h"


// <Game�N���X> ****************************************************************

// �����o�֐��̒�` ========================================================
//------------------------------------------------------------------
//! @brief �f�t�H���g�R���X�g���N�^
//!
//! @param[in] �Ȃ�
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
//! @brief �f�X�g���N�^
//------------------------------------------------------------------
Game::~Game()
{

}



//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Game::Initialize(void)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}



//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Game::Update(void)
{
	InputManager::singleton().Update();
	SceneManager::singleton().UpdateActiveScene();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Game::Render(void)
{
	SceneManager::singleton().RenderActiveScene();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Game::Finalize(void)
{

}
