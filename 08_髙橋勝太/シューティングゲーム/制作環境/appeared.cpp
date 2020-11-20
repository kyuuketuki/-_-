//-----------------------------------------------------------------
//
// explosion (explosion.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "appeared.h"

//-----------------------------------------------------------------------------
// �\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	int nCounterAnimEx;						//�A�j���[�V�����J�E���^�[
	int nPatternAnimEx;						//�A�j���[�V�����p�^�[��No.
	bool bUse;								//�����̎g�p��
	int nCut;
}APPEARED;

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureAppeared = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAppeared = NULL;
APPEARED g_Appeared[MAX_APPEARED];							//�����̏��
int g_nAPPEARED_SIZE;//�T�C�Y�ύX

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitAppeared(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\02.png", &g_pTextureAppeared);

	for (int nCntExplosion = 0; nCntExplosion < MAX_APPEARED; nCntExplosion++)
	{
		g_Appeared[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Appeared[nCntExplosion].nCounterAnimEx = 0;
		g_Appeared[nCntExplosion].nPatternAnimEx = 0;
		g_Appeared[nCntExplosion].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_APPEARED, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffAppeared, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffAppeared->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_APPEARED; nCntExplosion++)
	{
		//���_���W
		SetVertexAppeared(nCntExplosion);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�̃J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);

		//���_�̏��̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.125f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f, 0.125f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 0.0f);

		pVtx += 4;
	}
	g_pVtxBuffAppeared->Unlock(); //�A�����b�N

	return S_OK;
}

//-----------------------------------------------------------------------------
//�@�I������
//-----------------------------------------------------------------------------
void UninitAppeared(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffAppeared != NULL)
	{
		g_pVtxBuffAppeared->Release();
		g_pVtxBuffAppeared = NULL;
	}
	//�e�N�X�`���̊J��
	if (g_pVtxBuffAppeared != NULL)
	{
		g_pVtxBuffAppeared->Release();
		g_pVtxBuffAppeared = NULL;
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateAppeared(void)
{
	APPEARED *pAppeared;
	pAppeared = &g_Appeared[0];

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffAppeared->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_APPEARED; nCntBullet++, pAppeared++)
	{
		if (pAppeared->bUse == true)
		{

			pAppeared->nCounterAnimEx++;//�A�j���[�V�����J�E���^�[�X�V
			if ((pAppeared->nCounterAnimEx % pAppeared->nCut) == 0)
			{
				pAppeared->nPatternAnimEx = (pAppeared->nPatternAnimEx + 1) % 8;//�A�j���[�V�����p�^�[��No.�X�V
			}

			//���_���W
			SetVertexAppeared(nCntBullet);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.125f * pAppeared->nPatternAnimEx), 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f + (0.125f * pAppeared->nPatternAnimEx), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.125f + (0.125f * pAppeared->nPatternAnimEx), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f + (0.125f * pAppeared->nPatternAnimEx), 0.0f);

			if (pAppeared->nPatternAnimEx == 7)
			{
				pAppeared->bUse = false;
				pAppeared->nPatternAnimEx = 0;
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffAppeared->Unlock();
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawAppeared(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	int nCntVertex = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffAppeared, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureAppeared);

	//�|���S���̕`��
	for (int nCntExplosion = 0; nCntExplosion < MAX_APPEARED; nCntExplosion++)
	{
		if (g_Appeared[nCntExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
}

//-----------------------------------------------------------------------------
// �����̐ݒ�
//-----------------------------------------------------------------------------
void SetAppeared(D3DXVECTOR3 pos,int size,int nCut)
{
	APPEARED *pAppeared;
	pAppeared = &g_Appeared[0];

	for (int nCntExplosion = 0; nCntExplosion < MAX_APPEARED; nCntExplosion++, pAppeared++)
	{
		if (pAppeared->bUse == false)
		{
			pAppeared->pos = pos;

			pAppeared->nCut = nCut;

			g_nAPPEARED_SIZE = size;

			//���_���W
			SetVertexAppeared(nCntExplosion);

			pAppeared->bUse = true;
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// �����̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------
void SetVertexAppeared(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffAppeared->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_Appeared[nIdx].pos.x - (APPEARED_SIZE + g_nAPPEARED_SIZE), g_Appeared[nIdx].pos.y + (APPEARED_SIZE + g_nAPPEARED_SIZE), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Appeared[nIdx].pos.x - (APPEARED_SIZE + g_nAPPEARED_SIZE), g_Appeared[nIdx].pos.y - (APPEARED_SIZE + g_nAPPEARED_SIZE), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Appeared[nIdx].pos.x + (APPEARED_SIZE + g_nAPPEARED_SIZE), g_Appeared[nIdx].pos.y + (APPEARED_SIZE + g_nAPPEARED_SIZE), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Appeared[nIdx].pos.x + (APPEARED_SIZE + g_nAPPEARED_SIZE), g_Appeared[nIdx].pos.y - (APPEARED_SIZE + g_nAPPEARED_SIZE), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffAppeared->Unlock();
}
