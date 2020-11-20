//-----------------------------------------------------------------
//
// game (game.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "game.h"
#include "player.h"
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "sound.h"
#include "score.h"
#include "movebg.h"
#include "boss.h"
#include "effect.h"
#include "result.h"
#include "pause.h"
#include "fade.h"
#include "appeared.h"

//--------------
//����������
//--------------
HRESULT InitTutorial()
{
	//�w�i�̏���������
	InitBG();
	InitMovebg();

	//�|���S���̏���������
	InitPlayer();

	InitBoss();

	//�e�̏���������
	InitBullet();
	InitEffect();

	//�X�R�A����������
	InitScore();

	for (int nCount = 0; nCount < 8; nCount++)
	{
		SetScore(D3DXVECTOR3(1400 + 50.0f * (nCount + 1), 50.0f, 0.0f), 0);
	}

	return E_NOTIMPL;
}

//----------------
//�I������
//----------------
void UninitTutorial(void)
{
	//Direct�f�o�C�X�̊J��
	UninitBG();
	UninitMovebg();

	//�|���S���̏I������
	UninitPlayer();

	//�e�̏I������
	UninitBullet();
	UninitEffect();

	//�X�R�A�̏I������
	UninitScore();
}

//--------------------
//�X�V����
//--------------------
void UpdateTutorial(void)
{
	//�w�i�̍X�V����
	UpdateBG();
	UpdateMovebg();

	//�|���S���̍X�V����
	UpdatePlayer();

	//�e�̍X�V����
	UpdateBullet();
	UpdateEffect();

	//�X�R�A�̍X�V����
	UpdateScore();

	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		//��ʐ؂�ւ�
		SetMode(MODE_GAME);
	}
}

//--------------------
//�`�揈��
//--------------------
void DrawTutorial(void)
{

	//�e�̕`�揈��
	DrawBullet();
	DrawEffect();

	//�|���S���̕`�揈��
	DrawPlayer();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�w�i�̕`�揈��
	DrawMovebg();
	DrawBG();
}

