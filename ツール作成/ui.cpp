//-----------------------------------------------------------------
//
// �^�C�g���̏��� (titile.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "ui.h"
#include "input.h"
#include "fade.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_UI			(3)										// �ő吔
#define HEIGHT_Y		(500.0f * -1.0f)					// ���S�̏������SY���W
#define UILOGO_X		(450.0f)							// ���S��
#define UILOGO_Y		(100.0f)							// ���S�̍���
#define GRAR_X			(200.0f)							// ���S��
#define GRAR_Y			(250.0f)							// ���S�̍���
#define ITEM_X			(600.0f)							// ���S��
#define ITEM_Y			(100.0f)							// ���S�̍���

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL;
LPDIRECT3DTEXTURE9 g_pTextureUi[MAX_UI] = {};
D3DXVECTOR3 g_posUiLogo;						// �^�C�g�����S�̒��S���W
D3DXVECTOR3 g_posUiGear;						// �^�C�g�����S�̒��S���W
D3DXVECTOR3 g_posUiItem;						// �^�C�g�����S�̒��S���W


//-----------------------------------------------------------------
// �^�C�g���̏���������
//-----------------------------------------------------------------
HRESULT InitUi(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	//g_posUiLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 0.0f);
	g_posUiLogo = D3DXVECTOR3(250.0f, 50.0f, 0.0f);
	g_posUiGear = D3DXVECTOR3(100.0f, 900.0f, 0.0f);
	g_posUiItem = D3DXVECTOR3(1800.0f, 50.0f, 0.0f);

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/timer.jpg", &g_pTextureUi[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�M�A.jpg", &g_pTextureUi[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/item.jpg", &g_pTextureUi[2]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_UI, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffUi,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		// ���_���W�̐ݒ�
		SetVertexUi(nCntUi);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�			
		pVtx[0].col = D3DCOLOR_RGBA(255, 255,255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255,255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255,255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255,255, 255);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���̍X�V
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUi->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �^�C�g���̏I������
//-----------------------------------------------------------------
void UninitUi(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffUi != NULL)
	{
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < MAX_UI; nCntTexture++)
	{
		if (g_pTextureUi[nCntTexture] != NULL)
		{
			g_pTextureUi[nCntTexture]->Release();
			g_pTextureUi[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �^�C�g���̍X�V����
//-----------------------------------------------------------------
void UpdateUi(void)
{

}

//-----------------------------------------------------------------
// �^�C�g���̕`�揈��
//-----------------------------------------------------------------
void DrawUi(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntTexture = 0; nCntTexture < MAX_UI; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTextureUi[nCntTexture]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}
}

//-----------------------------------------------------------------
// �^�C�g����ʂɓ\��e�N�X�`���̎w��
//-----------------------------------------------------------------
void SetVertexUi(int nCntUi)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	if (nCntUi == 0)
	{
		pVtx[0].pos = D3DXVECTOR3(g_posUiLogo.x - (UILOGO_X / 2), g_posUiLogo.y + (UILOGO_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posUiLogo.x - (UILOGO_X / 2), g_posUiLogo.y - (UILOGO_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posUiLogo.x + (UILOGO_X / 2), g_posUiLogo.y + (UILOGO_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posUiLogo.x + (UILOGO_X / 2), g_posUiLogo.y - (UILOGO_Y / 2), 0.0f);
	}

	if (nCntUi == 1)
	{
		pVtx[4].pos = D3DXVECTOR3(g_posUiGear.x - (GRAR_X / 2), g_posUiGear.y + (GRAR_Y / 2), 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_posUiGear.x - (GRAR_X / 2), g_posUiGear.y - (GRAR_Y / 2), 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_posUiGear.x + (GRAR_X / 2), g_posUiGear.y + (GRAR_Y / 2), 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_posUiGear.x + (GRAR_X / 2), g_posUiGear.y - (GRAR_Y / 2), 0.0f);
	}

	if (nCntUi == 2)
	{
		pVtx[8].pos = D3DXVECTOR3(g_posUiItem.x - (ITEM_X / 2), g_posUiItem.y + (ITEM_Y / 2), 0.0f);
		pVtx[9].pos = D3DXVECTOR3(g_posUiItem.x - (ITEM_X / 2), g_posUiItem.y - (ITEM_Y / 2), 0.0f);
		pVtx[10].pos = D3DXVECTOR3(g_posUiItem.x + (ITEM_X / 2), g_posUiItem.y + (ITEM_Y / 2), 0.0f);
		pVtx[11].pos = D3DXVECTOR3(g_posUiItem.x + (ITEM_X / 2), g_posUiItem.y - (ITEM_Y / 2), 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUi->Unlock();
}