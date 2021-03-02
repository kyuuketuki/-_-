#pragma once

//-----------------------------------------------------------------
//
// �X�R�A�̏��� (score.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------


#ifndef _GEAR_H_
#define _GEAR_H_

#include "main.h"
#include "game.h"

#define  GEAR_SIZE (70)

//-----------------------------------------------------------------------------
// �\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;
	int nType;
	bool bUse;
}GEAR;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitGear(void);
void UninitGear(void);
void UpdateGear(void);
void DrawGear(void);
void AddGear(int nValue);
void SetGear(D3DXVECTOR3 pos, int nType);
void SetVertexGear(int nIdx);

GEAR*GetGear(void);

#endif
