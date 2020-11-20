//-----------------------------------------------------------------
//
// �����w�i�̏��� (movebg.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------


#ifndef _MOVEBG_H_
#define _MOVEBG_H_

#include "main.h"
#include "input.h"


typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	int nType;//���
	bool bUse;
	int nCounterAnim;						//�A�j���[�V�����J�E���^�[
	int nPatternAnim;						//�A�j���[�V�����p�^�[��No.
	int nseetAni;
}TITLE;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitMovebg(void);
void UninitMovebg(void);
void UpdateMovebg(void);
void DrawMovebg(void);
void SetVertexTextureMovebg(int nType);
#endif
