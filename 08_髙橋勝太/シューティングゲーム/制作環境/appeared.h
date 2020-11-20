//-----------------------------------------------------------------
//
// ���j�̏��� (explosion.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------


#pragma once
#ifndef _APPEARED_H_
#define _APPEARED_H_

#pragma once
#include "game.h"

//-----------------------------------------------------------------------------
// �}�N����`
//---------------------------------------------------------------------------		
#define APPEARED_SIZE (0)			//�����̑傫��
#define MAX_APPEARED (256)			//�����̏��

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitAppeared(void);
void UninitAppeared(void);
void UpdateAppeared(void);
void DrawAppeared(void);
void SetAppeared(D3DXVECTOR3 pos, int size, int nCut);
void SetVertexAppeared(int nIdx);


#endif _EXPLOSION_H_

#pragma once
