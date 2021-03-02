//-----------------------------------------------------------------
//
// �X�R�A�̏��� (score.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "gear.h"

//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTextureGear = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGear = NULL;//���_���
D3DXVECTOR3 g_PosGear;
GEAR g_aGear[256];
int g_nGear;//�X�R�A

///====================
//�|���S���̏���������
//====================
HRESULT InitGear(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_pTextureGear);

	//�X�R�A���Z�b�g
	g_nGear = 0;

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++)
	{
		//g_aGear[nCntEnemy].pos = D3DXVECTOR3(200.0f, 50.0f, 0.0f);
		//g_aGear[nCntEnemy].pos = D3DXVECTOR3(200.0f, 50.0f, 0.0f);
		g_aGear[nCntEnemy].nType = 0;
		g_aGear[nCntEnemy].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 256, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGear, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffGear->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < 256; nCntBullet++, pVtx += 4)
	{
		//���_���W
		//pVtx[0].pos = D3DXVECTOR3(g_aGear[nCntBullet].pos.x - GEAR_SIZE, g_aGear[nCntBullet].pos.y + GEAR_SIZE, 0);
		//pVtx[1].pos = D3DXVECTOR3(g_aGear[nCntBullet].pos.x - GEAR_SIZE, g_aGear[nCntBullet].pos.y - GEAR_SIZE, 0);
		//pVtx[2].pos = D3DXVECTOR3(g_aGear[nCntBullet].pos.x + GEAR_SIZE, g_aGear[nCntBullet].pos.y + GEAR_SIZE, 0);
		//pVtx[3].pos = D3DXVECTOR3(g_aGear[nCntBullet].pos.x + GEAR_SIZE, g_aGear[nCntBullet].pos.y - GEAR_SIZE, 0);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_���̐ݒ�(�����j���O�}��)
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffGear->Unlock();

	return S_OK;
}

//==================
//�|���S���̏I������
//==================
void UninitGear(void)
{
	//�e�N�X�`���̊J��
	for (int nCntEnemyType = 0; nCntEnemyType < 256; nCntEnemyType++)
	{
		if (g_pTextureGear != NULL)
		{
			g_pTextureGear->Release();
			g_pTextureGear = NULL;
		}
	}
	//�o�b�t�@�̊J��
	if (g_pVtxBuffGear != NULL)
	{
		g_pVtxBuffGear->Release();
		g_pVtxBuffGear = NULL;
	}
}

//==================
//�|���S���̍X�V����
//==================
void UpdateGear(void)
{
	VERTEX_2D *pVtx;
	int nNumber;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffGear->Lock(0, 0, (void**)&pVtx, 0);

	nNumber = g_nGear % 7 / 1;

	for (int nCutEnemy = 0; nCutEnemy < 1; nCutEnemy++)
	{
		pVtx[0].pos = D3DXVECTOR3((g_aGear[nCutEnemy].pos.x - GEAR_SIZE) + nCutEnemy * 10, g_aGear[nCutEnemy].pos.y + GEAR_SIZE, 0);
		pVtx[1].pos = D3DXVECTOR3((g_aGear[nCutEnemy].pos.x - GEAR_SIZE) + nCutEnemy * 10, g_aGear[nCutEnemy].pos.y - GEAR_SIZE, 0);
		pVtx[2].pos = D3DXVECTOR3((g_aGear[nCutEnemy].pos.x + GEAR_SIZE) + nCutEnemy * 10, g_aGear[nCutEnemy].pos.y + GEAR_SIZE, 0);
		pVtx[3].pos = D3DXVECTOR3((g_aGear[nCutEnemy].pos.x + GEAR_SIZE) + nCutEnemy * 10, g_aGear[nCutEnemy].pos.y - GEAR_SIZE, 0);


		//���_���̐ݒ�(�����j���O�}��)
		pVtx[0].tex = D3DXVECTOR2(0.1f*nNumber, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f*nNumber, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*(nNumber + 1), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*(nNumber + 1), 0.0f);

		//pVtx += 4;
	}
}

//==================
//�|���S���̕`�揈��
//==================
void DrawGear(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	int nCntVertex = 0;

	GEAR *pGear;
	pGear = &g_aGear[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGear, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	//�|���S���̕`��
	for (int nCntBullet = 0; nCntBullet < 256; nCntBullet++, pGear++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureGear);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntVertex, 2);
		if (g_aGear[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntVertex, 2);
		}

		nCntVertex += 4;
	}
}

//-----------------------------------------------------------------------------
// �J�E���g
//-----------------------------------------------------------------------------
void AddGear(int nValue)
{
	g_nGear = nValue;
}

//-----------------------------------------------------------------------------
// �M�A�̐ݒu
//-----------------------------------------------------------------------------
void SetGear(D3DXVECTOR3 pos, int nType)
{
	GEAR *pGear;
	pGear = &g_aGear[0];

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGear->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pGear++)
	{
		if (pGear->bUse == false)
		{

			pGear->pos = pos;

			//���_���W
			//SetVertexGear(nCntEnemy);

			pGear->nType = nType;

			pGear->bUse = true;
			break;
		}
		g_pVtxBuffGear->Unlock(); //�A�����b�N
								   //pVtx += 4;
	}
}

//-----------------------------------------------------------------------------
// �G�̏K��
//-----------------------------------------------------------------------------
GEAR*GetGear(void)
{
	return &g_aGear[0];
}

//-----------------------------------------------------------------------------
// �G�̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------
void SetVertexGear(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGear->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_aGear[nIdx].pos.x -GEAR_SIZE, g_aGear[nIdx].pos.y + GEAR_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aGear[nIdx].pos.x -GEAR_SIZE, g_aGear[nIdx].pos.y - GEAR_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aGear[nIdx].pos.x +GEAR_SIZE, g_aGear[nIdx].pos.y + GEAR_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aGear[nIdx].pos.x +GEAR_SIZE, g_aGear[nIdx].pos.y - GEAR_SIZE, 0.0f);

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGear->Unlock();
}

