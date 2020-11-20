//-----------------------------------------------------------------
//
// ���U���g��� (result.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "input.h"

//-----------------------------------------------------------------------------
// ���U���g��ʂ̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	int nType;//���
	int nData;
}TUTORIAL;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetVertexTextureTutorial(int nType);
//void SetResult(int nData);
#endif

