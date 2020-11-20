//-----------------------------------------------------------------
//
// �G�̏��� (enemy.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------


#ifndef _ENEMY_H_
#define _ENEMY_H_

#define MAX_ENEMY (256)//�G�̍ő吔
#define MAX_TYPE_ENEMY (3)//�G�̎�ސ�
#define MAX_ENEMY_SIZE (30)

#include "main.h"
#include "input.h"
#include "enemy.h"
#include "bullet.h"
#include "player.h"
#include "Explosion.h"
#include "sound.h"
//----------------------------------
//�G�̏��
//----------------------------------
typedef enum
{
	ENEMYSTATE_NOMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_MAX
}ENEMYSTATE;

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
	ENEMYSTATE state;//���
	int nCounterState;//��ԃJ�E���^�[
	int nLife;//�̗�
}ENEMY;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 Pos, int nType);
ENEMY *GetEnemy(void);
bool HitEnemy(int nIdx, int nDamage);
int GetEnemyNomber(void);
#endif
