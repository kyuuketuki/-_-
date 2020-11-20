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

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
bool g_bPause;

//�������
int g_nCount = 0;

//--------------
//����������
//--------------
HRESULT InitGame()
{
	g_nCount = 0;
	g_bPause = false;

	//�w�i�̏���������
	//InitBG();
	InitMovebg();

	//�|���S���̏���������
	InitPlayer();

	//�G�̏���������
	InitEnemy();

	InitBoss();

	//�e�̏���������
	InitBullet();

	//�����̏���������
	InitExplosion();

	InitAppeared();

	InitEffect();

	//�G�L�����̕\��
	for (int nCount = 0; nCount < 5; nCount++)
	{

		SetEnemy(D3DXVECTOR3(200.0f * (nCount + 1), 100.0f, 0.0f), 0);
		SetEnemy(D3DXVECTOR3(200.0f * (nCount + 1), 200.0f, 0.0f), 1);
		SetEnemy(D3DXVECTOR3(200.0f * (nCount + 1), 300.0f, 0.0f), 2);
	}

	//SetBoss(D3DXVECTOR3(200.0f, 300.0f, 0.0f), 0);
	//SetBoss(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), 0);

	//�X�R�A����������
	InitScore();

	for (int nCount = 0; nCount < 8; nCount++)
	{
		SetScore(D3DXVECTOR3(1400 + 50.0f * (nCount + 1), 50.0f, 0.0f), 0);
	}

	// �|�[�Y���j���[�̏���������
	InitPause();

	//�T�E���h�Đ�
	PlaySound(SOUND_LABEL_BGM002);
	//PlaySound(SOUND_LABEL_SE_EXPLOSION);

	return E_NOTIMPL;
}

//----------------
//�I������
//----------------
void UninitGame(void)
{
	//Direct�f�o�C�X�̊J��
	//UninitBG();
	UninitMovebg();

	//�|���S���̏I������
	UninitPlayer();

	//�e�̏I������
	UninitBullet();

	//�G�̏I������
	UninitEnemy();

	UninitBoss();

	//�����̏I������
	UninitExplosion();

	UninitAppeared();

	UninitEffect();

	//�X�R�A�̏I������
	UninitScore();

	//�T�E���h��~
	StopSound();

	// �|�[�Y���j���[�̏I������
	UninitPause();
}

//--------------------
//�X�V����
//--------------------
void UpdatetGame(void)
{
	//�|�[�Y�{�^�����������Ƃ�
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;

	}

	if (g_bPause == true)
	{
		UpdatePause();
	}
	else
	{
		//�w�i�̍X�V����
		//UpdateBG();
		UpdateMovebg();

		//�|���S���̍X�V����
		UpdatePlayer();

		//�e�̍X�V����
		UpdateBullet();

		//�G�̍X�V����
		UpdateEnemy();

		//�{�X�̍X�V����
		UpdateBoss();

		//�����̍X�V����
		UpdateExplosion();

		UpdateAppeared();

		UpdateEffect();

		//�X�R�A�̍X�V����
		UpdateScore();

		int nA = rand() % 1000;
		int nB = rand() % 500;
		int nCnt = rand() % 150;

		//�G�L�����̕\��
		if (nCnt == 1 || nCnt == 2 || nCnt == 3)
		{
			if (g_nCount <= 10)
			{
				g_nCount++;

				if (nCnt == 1)
				{
					SetAppeared(D3DXVECTOR3(nA, nB, 0.0f),50,6);
					SetEnemy(D3DXVECTOR3(nA, nB, 0.0f), 0);
				}

				if (nCnt == 2)
				{
					SetAppeared(D3DXVECTOR3(nA, nB, 0.0f),50,6);
					SetEnemy(D3DXVECTOR3(nA, nB, 0.0f), 1);
				}

				if (nCnt == 3)
				{
					SetAppeared(D3DXVECTOR3(nA, nB, 0.0f),50,6);
					SetEnemy(D3DXVECTOR3(nA, nB, 0.0f), 2);
				}
			}
		}
	}

	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		//��ʐ؂�ւ�
		//SetMode(MODE_RESULT);
	}
}

//--------------------
//�`�揈��
//--------------------
void DrawGame(void)
{

	//�e�̕`�揈��
	DrawBullet();
	DrawEffect();
	
	DrawAppeared();

	//�|���S���̕`�揈��
	DrawPlayer();

	//�G�̕`�揈��
	DrawEnemy();

	DrawBoss();

	//���j�̕`�揈��
	DrawExplosion();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�w�i�̕`�揈��
	DrawMovebg();

	// �|�[�Y�̕`�揈��
	if (g_bPause == true)
	{
		DrawPause();
	}
}

