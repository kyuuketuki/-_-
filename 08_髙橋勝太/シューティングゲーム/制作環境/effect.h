//-----------------------------------------------------------------
//
// �G�t�F�N�g�̏��� (effect.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_
#pragma once
#include "game.h"
#include "main.h"

//-----------------------------------------------------------------------------
// �}�N����`
//---------------------------------------------------------------------------		
#define EFFECT_SIZE (40)			//�G�t�F�N�g�̑傫��
#define MAX_EFFECT (4096)			//�G�t�F�N�g�̏��

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 move, int nType);
void SetVertexEffect(int nIdx);

#endif _EXPLOSION_H_
