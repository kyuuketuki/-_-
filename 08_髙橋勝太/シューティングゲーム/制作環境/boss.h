//-----------------------------------------------------------------
//
// �{�X�̏��� (boss.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _BOSS_H_
#define _BOSS_H_

#define MAX_BOSS (256)//�G�̍ő吔
#define MAX_TYPE_BOSS (3)//�G�̎�ސ�
#define MAX_BOSS_SIZE (150)

#include "main.h"
#include "input.h"
#include "enemy.h"
#include "bullet.h"
#include "player.h"
#include "Explosion.h"
#include "sound.h"
//
//�G�̏��
//
typedef enum
{
	BOSSSTATE_NOMAL = 0,
	BOSSSTATE_DAMAGE,
	BOSSSTATE_MAX
}BOSSSTATE;

//
//�G�̍\����
//
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	int nType;//���
	bool bUse;//�g�p���Ă��邩�ǂ���
	int g_nCounterAni;
	int g_nPatternAni;
	int g_nData;
	int g_nP;
	int g_nseetAni;
	BOSSSTATE state;//���
	int nCounterState;//��ԃJ�E���^�[
	int nLife;//�̗�
}BOSS;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 Pos, int nType);
void SetBoss2(D3DXVECTOR3 Pos, int nType);
BOSS *GetBoss(void);
bool HitBoss(int nIdx, int nDamage);
int GetBossNomber(void);
#endif
