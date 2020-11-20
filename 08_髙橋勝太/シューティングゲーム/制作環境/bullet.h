//-----------------------------------------------------------------
//
// �e�̏��� (��ullet.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _BULLET_H_
#define _BULLET_H_

#pragma once
#include "tutorial.h"
#include "game.h"
#include "enemy.h"
#include "Explosion.h"

//-----------------------------------------------------------------------------
// �}�N����`
//---------------------------------------------------------------------------
#define MOVE_BULLET (5)				//�e�̑��x
#define BULLET_SIZE (10)			//�e�̑傫��
#define MAX_BULLET (1024)			//�e�̏��

typedef enum
{
	BULLET_PLAYR = 0,
	BULLET_ENEMY,
	BULLET_BOSS,
	BULLET_MAX
}BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	int nLife;			//����
	bool bUse;			//�e�̎g�p��
	int nType;
}BULLET;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife,int nType);
void SetVertexBullet(int nIdx);
BULLET *GetBullet(void);
#endif _BULLET_H_