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

	scene_manager.AddScene(SCENE_TITLE, SceneTitle::Create);
	scene_manager.AddScene(SCENE_PLAY, ScenePlay::Create);
	scene_manager.AddScene(SCENE_RESULT, SceneResult::Create);

	scene_manager.SetStartScene(SCENE_TITLE);
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
	InputManager& input = InputManager::singleton();
	input.Update();
	SceneManager& scene_manager = SceneManager::singleton();
	scene_manager.UpdateActiveScene();
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
	SceneManager& scene_manager = SceneManager::singleton();
	scene_manager.RenderActiveScene();
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
