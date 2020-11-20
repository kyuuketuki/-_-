//-----------------------------------------------------------------
//
// �v���C���[�̏��� (player.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _PLYER_H_
#define _PLYER_H_

#include "game.h"
#include "input.h"
#include "enemy.h"
#include "bullet.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define MOVE_NUMBER (2)

typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	bool bUse;//�g�p���Ă��邩�ǂ���
	int nLife;//�̗�
}PLAYER;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
#endif

