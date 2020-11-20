//-----------------------------------------------------------------
//
// effect (effect.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "Effect.h"

//-----------------------------------------------------------------------------
// �\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	int nCounterAnimEx;						//�A�j���[�V�����J�E���^�[
	int nPatternAnimEx;						//�A�j���[�V�����p�^�[��No.
	bool bUse;								//�����̎g�p��
	D3DXVECTOR3 move;
	int nType;
	int nLife;
}EFFECT;

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;
EFFECT g_aEffect[MAX_EFFECT];							//�����̏��

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitEffect(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_pTextureEffect);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EFFECT; nCntExplosion++)
	{
		g_aEffect[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntExplosion].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntExplosion].nCounterAnimEx = 0;
		g_aEffect[nCntExplosion].nPatternAnimEx = 0;
		g_aEffect[nCntExplosion].bUse = false;
		g_aEffect[nCntExplosion].nType = 0;
		g_aEffect[nCntExplosion].nLife = 0;

	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W
		SetVertexEffect(nCntEffect);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�̃J���[�ݒ�
		/*pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 255);*/

		//���_�̏��̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock(); //�A�����b�N

	return S_OK;
}

//-----------------------------------------------------------------------------
//�@�I������
//-----------------------------------------------------------------------------
void UninitEffect(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
	//�e�N�X�`���̊J��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateEffect(void)
{
	EFFECT *pEffect;
	pEffect = &g_aEffect[0];

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++, pEffect++)
	{
		if (pEffect->bUse == true)
		{
			pEffect->pos += pEffect->move;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - EFFECT_SIZE, pEffect->pos.y + EFFECT_SIZE, 1.0f);
			pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - EFFECT_SIZE, pEffect->pos.y - EFFECT_SIZE, 1.0f);
			pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + EFFECT_SIZE, pEffect->pos.y + EFFECT_SIZE, 1.0f);
			pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + EFFECT_SIZE, pEffect->pos.y - EFFECT_SIZE, 1.0f);

			pEffect->nLife--;
			if (pEffect->nLife == 0)
			{
				pEffect->bUse = false;
			}

			pVtx += 4;
		}
	}

	g_pVtxBuffEffect->Unlock();
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawEffect(void)
{


	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	int nCntVertex = 0;

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEffect);

	//�|���S���̕`��
	for (int nCntExplosion = 0; nCntExplosion < MAX_EFFECT; nCntExplosion++)
	{
		if (g_aEffect[nCntExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//-----------------------------------------------------------------------------
// �����̐ݒ�
//-----------------------------------------------------------------------------
void SetEffect(D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 move,int nType)
{
	EFFECT *pEffect;
	pEffect = &g_aEffect[0];
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EFFECT; nCntExplosion++, pEffect++)
	{
		if (pEffect->bUse == false)
		{
			pEffect->pos = pos;

			pEffect->nLife = nLife;

			pEffect->nType = nType;

			if (nType == 0)
			{
				//���_�̃J���[�ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			}

			if (nType == 1)
			{
				//���_�̃J���[�ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			}

			if (nType == 2)
			{
				//���_�̃J���[�ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 255, 255);
			}

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - EFFECT_SIZE, pEffect->pos.y + EFFECT_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - EFFECT_SIZE, pEffect->pos.y - EFFECT_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + EFFECT_SIZE, pEffect->pos.y + EFFECT_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + EFFECT_SIZE, pEffect->pos.y - EFFECT_SIZE, 0.0f);

			pEffect->bUse = true;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//-----------------------------------------------------------------------------
// �����̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------
void SetVertexEffect(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);



	////���_���W
	//pVtx[0].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x - EXPLOSION_SIZE, g_aEffect[nIdx].pos.y + EXPLOSION_SIZE, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x - EXPLOSION_SIZE, g_aEffect[nIdx].pos.y - EXPLOSION_SIZE, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x + EXPLOSION_SIZE, g_aEffect[nIdx].pos.y + EXPLOSION_SIZE, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x + EXPLOSION_SIZE, g_aEffect[nIdx].pos.y - EXPLOSION_SIZE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
