//-----------------------------------------------------------------
//
// ���j�̏��� (explosion.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------


#pragma once
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#pragma once
#include "game.h"

//-----------------------------------------------------------------------------
// �}�N����`
//---------------------------------------------------------------------------		
#define EXPLOSION_SIZE (50)			//�����̑傫��
#define MAX_EXPLOSION (256)			//�����̏��

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);
void SetVertexExplosion(int nIdx);


#endif _EXPLOSION_H_

