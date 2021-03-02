
#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------
//
// game (game.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include<stdio.h>
#include "main.h"
#include "camera.h"
#include "light.h"
#include"model.h"
#include "xinput.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "stdio.h"
#include "object.h"
#include "billboard.h"
#include "effect.h"
#include "ui.h"
#include "meshfield.h"
#include "bullet.h"
#include "pause.h"
#include "bg.h"
#include "car.h"
#include "score.h"
#include "gamepad.h"
#include "timer.h"
#include "fade.h"
#include "gear.h"
#include "item.h"

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
bool g_bPause;						//�|�[�Y��Ԕ���
int g_PlayerChange = 0;				//�������Ă���v���C���[
int g_nDataTime = 0;				//�������
int g_nDataTime2 = 0;				//�������
int g_nDataItem = 0;				//�������
int g_nDataItem2 = 0;				//�������
FAILDATE FailDate[MAX_OBJECT];
int g_nObjectDate = 0;
int g_nItemDate = 0;

//--------------
//����������
//--------------
HRESULT InitGame()
{
	g_bPause = false;

	InitPause();

	InitBG();

	InitScore();

	InitGear();

	InitMeshfield();

	InitWall();

	InitBillboard();

	InitBullet();

	InitShadow();

	InitPlayer();

	InitCar();

	InitObject();

	InitItem();

	InitCamera();

	Initlight();

	InitEffect();

	InitUi();

	InitTimer();

	//�M�A�̕\��
	SetGear(D3DXVECTOR3(100, SCREEN_HEIGHT - 150.0f, 0.0f), 0);

	//�X�R�A�̕\��
	for (int nCount = 0; nCount < 8; nCount++)
	{
		SetScore(D3DXVECTOR3(1600 + 70.0f * (nCount + 1), 50.0f, 0.0f), 0);
	}

	//�^�C���̕\��
	//��
	for (int nCount = 0; nCount < 2; nCount++)
	{
		SetTimer(D3DXVECTOR3(90 + 50.0f * (nCount + 1), 50.0f, 0.0f), 0);
	}
	//�b
	for (int nCount = 0; nCount < 2; nCount++)
	{
		SetTimer(D3DXVECTOR3(250 + 50.0f * (nCount + 1), 50.0f, 0.0f), 0);
	}

	//�t�B�[���h�̐ݒ�
	SetField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),  0.0f, 0.0f);	//����

	//�A�C�e��
	/*SetItem(D3DXVECTOR3(760.4, 0.0f, -472.4), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(2212.4, 0.0f, -292.3), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(2212.4, 0.0f, 379.4), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(4130.6, 0.0f, 906.2), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(4130.6, 0.0f, 3930.0), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(-824.8, 0.0f, 3929.8), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(-3093.5, 0.0f, 3341.8), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(-3668.0, 0.0f, 2295.0), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(-3668.0, 0.0f, 754.7), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(-2382.2, 0.0f, -773.9), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(-1554.5, 0.0f, -2155.2), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(-2300.6, 0.0f, -2957.9), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(-1580.6, 0.0f, -3627.3), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(-847.3, 0.0f, -2968.8), D3DXVECTOR3(0.0f, 0, 0.0f), 0);
	SetItem(D3DXVECTOR3(4029.8, 0.0f, -3801.2), D3DXVECTOR3(0.0f, 0, 0.0f), 0);*/

	return E_NOTIMPL;
}

//----------------
//�I������
//----------------
void UninitGame(void)
{
	UninitBG();

	UninitScore();

	UninitGear();

	UninitMeshfield();

	UninitWall();

	UninitBillboard();

	UninitBullet();

	UninitShadow();

	UninitPlayer();

	UninitCar();

	UninitObject();

	UninitItem();

	UninitCamera();

	Uninitlight();

	UninitEffect();

	UninitUi();

	UninitTimer();

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
		UpdateMeshfield();

		UpdateScore();

		UpdateGear();

		UpdateBullet();

		UpdateWall();

		UpdateBillboard();

		UpdateShadow();

		//�v���C���[�̐؂�ւ�
		if (g_PlayerChange == 1)
		{
			UpdatePlayer();
		}

		//�v���C���[�̐؂�ւ�
		if (g_PlayerChange == 0)
		{
			UpdateCar();
		}

		UpdateObject();

		UpdateItem();

		UpdateCamera();

		Updatelight();

		UpdateEffect();

		UpdateUi();

		UpdateBG();

		UpdateTimer();

		AddTimer(1);

		//�v���C���[�𓮂���
		if (GetKeyboardTrigger(DIK_2) == true)
		{
			g_PlayerChange = 1;
		}

		//�Ԃ��𓮂���
		if (GetKeyboardTrigger(DIK_1) == true)
		{
			g_PlayerChange = 0;
		}

		PLAYER *player;
		player = GetModel();

		//SetWater(D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z));
		
		//�v���C���[�̈ʒu�ɃI�u�W�F�N�g�𐶐�
		if (GetKeyboardTrigger(DIK_G) == true)
		{
			SetOject(D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z), D3DXVECTOR3(0.0f, g_nDataTime2, 0.0f), g_nDataTime);

			//txt�t�@�C���ɏ�������
			FailObject();

			//G�{�^���������񐔂��J�E���g
			g_nObjectDate += 1;
		}

		//�v���C���[�̈ʒu�ɃA�C�e���𐶐�
		if (GetKeyboardTrigger(DIK_T) == true)
		{
			SetItem(D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z), D3DXVECTOR3(0.0f, g_nDataItem2, 0.0f), g_nDataItem);

			//txt�t�@�C���ɏ�������
			FailItem();

			//T�{�^���������񐔂��J�E���g
			g_nItemDate += 1;
		}

		//�ŐV�̃I�u�W�F�N�g������
		if (g_nObjectDate >= 1)
		{
			if (GetKeyboardTrigger(DIK_H) == true)
			{
				//H�{�^���������񐔂��J�E���g
				//�����󂯓n��
				g_nObjectDate -= 1;

				//txt�t�@�C���ɏ�������
				FailObject();
			}
		}

		//�ŐV�̃I�u�W�F�N�g������
		if (g_nItemDate >= 1)
		{
			if (GetKeyboardTrigger(DIK_Y) == true)
			{
				//H�{�^���������񐔂��J�E���g
				//�����󂯓n��
				g_nItemDate -= 1;

				//txt�t�@�C���ɏ�������
				FailItem();
			}
		}

		//�I�u�W�F�N�g�̃^�C�v��ς���
		if (GetKeyboardTrigger(DIK_UP) == true)
		{
			g_nDataTime += 1;
		}

		if (GetKeyboardTrigger(DIK_DOWN) == true)
		{
			g_nDataTime -= 1;
		}

		//�I�u�W�F�N�g�^�C�v�̏�����̏ꍇ0�ɖ߂�
		if (g_nDataTime > GetobjectType() - 1.0f)
		{
			g_nDataTime = 0.0f;
		}
		//�I�u�W�F�N�g�^�C�v�̏�����̏ꍇMAX�ɖ߂�
		if (g_nDataTime == -1.0f)
		{
			g_nDataTime = GetobjectType() - 1.0f;
		}

		//�A�C�e���̃^�C�v��ς���
		if (GetKeyboardTrigger(DIK_UP) == true)
		{
			g_nDataTime += 1;
		}

		if (GetKeyboardTrigger(DIK_DOWN) == true)
		{
			g_nDataTime -= 1;
		}

		//�A�C�e���^�C�v�̏�����̏ꍇ0�ɖ߂�
		if (g_nDataTime > GetitemType() - 1.0f)
		{
			g_nDataTime = 0.0f;
		}
		//�A�C�e���^�C�v�̏�����̏ꍇMAX�ɖ߂�
		if (g_nDataTime == -1.0f)
		{
			g_nDataTime = GetitemType() - 1.0f;
		}

		//�I�u�W�F�N�g�̌�����ς���
		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{
			g_nDataTime2 += 1.57f;
		}

		if (GetKeyboardTrigger(DIK_LEFT) == true)
		{
			g_nDataTime2 -= 1.0f;
		}
	}

	//if (GetKeyboardPress(DIK_N) == true)
	//{
	//	//��ʐ؂�ւ�
	//	SetMode(MODE_RESULT);
	//}
}

//--------------------
//�`�揈��
//--------------------
void DrawGame(void)
{
	SetCamera();

	//DrawBG();

	DrawMeshfield();

	DrawObject();

	DrawItem();

	DrawWall();

	DrawBillboard();

	DrawShadow();

	DrawBullet();

	DrawPlayer();

	DrawCar();

	DrawEffect();

	DrawUi();

	DrawTimer();

	DrawScore();

	DrawGear();

	// �|�[�Y�̕`�揈��
	if (g_bPause == true)
	{
		DrawPause();
	}
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
int GetGame(void)
{
	return g_PlayerChange;
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
int GetItem(void)
{
	return g_nDataTime;
}

//---------------------------------------------
//�����o��
//---------------------------------------------
int FailObject()
{
	PLAYER *player;
	player = GetModel();

	FILE *fp;

	//�ufprintfExample.txt�v�̃t�@�C�����������݃��[�h�i"w"�j�ŊJ��
	fp = fopen("SetObject.txt", "w");

	//�I�u�W�F�N�g�̈ʒu���L��
	FailDate[g_nObjectDate].X = player->pos.x;
	FailDate[g_nObjectDate].Z = player->pos.z;
	FailDate[g_nObjectDate].Rot = g_nDataTime2;
	FailDate[g_nObjectDate].Type = g_nDataTime;

	for (int nCnt = 0; nCnt < g_nObjectDate + 1; nCnt++)
	{
		//�utxt�v�ɏ�������
		fprintf(fp, "SetOject(D3DXVECTOR3(%.1f\, 0.0f, %.1f\), D3DXVECTOR3(0.0f, %d\, 0.0f), %d\);\n", FailDate[nCnt].X, FailDate[nCnt].Z, FailDate[nCnt].Rot, FailDate[nCnt].Type);
	}

	//�utxt�v�̃t�@�C�������
	fclose(fp);

	return 0;
}

int FailItem()
{
	PLAYER *player;
	player = GetModel();

	FILE *fp;

	//�ufprintfExample.txt�v�̃t�@�C�����������݃��[�h�i"w"�j�ŊJ��
	fp = fopen("SetItem.txt", "w");

	//�I�u�W�F�N�g�̈ʒu���L��
	FailDate[g_nItemDate].X = player->pos.x;
	FailDate[g_nItemDate].Z = player->pos.z;
	FailDate[g_nItemDate].Rot = g_nDataItem2;
	FailDate[g_nItemDate].Type = g_nDataItem;

	for (int nCnt = 0; nCnt < g_nItemDate + 1; nCnt++)
	{
		//�utxt�v�ɏ�������
		fprintf(fp, "SetItem(D3DXVECTOR3(%.1f\, 0.0f, %.1f\), D3DXVECTOR3(0.0f, %d\, 0.0f), %d\);\n", FailDate[nCnt].X, FailDate[nCnt].Z, FailDate[nCnt].Rot, FailDate[nCnt].Type);
	}

	//�utxt�v�̃t�@�C�������
	fclose(fp);

	return 0;
}

