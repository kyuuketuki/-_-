//-----------------------------------------------------------------
//
// �����w�i�̏��� (movebg.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "movebg.h"
#include "input.h"
#include "fade.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_PATTERN			(4)										// �A�j���[�V�����p�^�[��No.�̍ő吔
#define TITLELOGO_X			(1920.0f)								// �^�C�g�����S��
#define TITLELOGO_Y			(1080.0f)								// �^�C�g�����S�̍���
#define HEIGHT_Y			(1080.0f * -1.0f)						// �^�C�g�����S�̏������SY���W
#define MOVE_MOVEBGLOGO		(2.0f)									// �^�C�g�����S�̈ړ���
#define MOVE_MOVEBGLOGO2	(5.0f)									// �^�C�g�����S�̈ړ���

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMovebg = NULL;
LPDIRECT3DTEXTURE9 g_pTextureMovebg[4] = {};
D3DXVECTOR3 g_posMovebgLogo;						// �^�C�g�����S�̒��S���W
D3DXVECTOR3 g_posMovebgLogo2;
D3DXVECTOR3 g_posMovebgLogo3;
D3DXVECTOR3 g_posMovebgLogo4;
float g_nCntMovebg;									// �J�E���g

//-----------------------------------------------------------------
// �^�C�g���̏���������
//-----------------------------------------------------------------
HRESULT InitMovebg(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	//// �ϐ��̏�����
	g_posMovebgLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, HEIGHT_Y, 0.0f);
	//g_posMovebgLogo2 = D3DXVECTOR3(SCREEN_WIDTH / 2, HEIGHT_Y, 0.0f);
	g_posMovebgLogo3 = D3DXVECTOR3(SCREEN_WIDTH / 2, HEIGHT_Y, 0.0f);
	//g_posMovebgLogo4 = D3DXVECTOR3(SCREEN_WIDTH / 2, HEIGHT_Y, 0.0f);
	g_nCntMovebg = 0;

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &g_pTextureMovebg[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &g_pTextureMovebg[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &g_pTextureMovebg[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &g_pTextureMovebg[3]);
	


	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_PATTERN, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffMovebg,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMovebg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_PATTERN; nCntTitle++)
	{
		// ���_���W�̐ݒ�
		SetVertexTextureMovebg(nCntTitle);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���̍X�V
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMovebg->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �^�C�g���̏I������
//-----------------------------------------------------------------
void UninitMovebg(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMovebg != NULL)
	{
		g_pVtxBuffMovebg->Release();
		g_pVtxBuffMovebg = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < MAX_PATTERN; nCntTexture++)
	{
		if (g_pTextureMovebg[nCntTexture] != NULL)
		{
			g_pTextureMovebg[nCntTexture]->Release();
			g_pTextureMovebg[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �^�C�g���̍X�V����
//-----------------------------------------------------------------
void UpdateMovebg(void)
{
	// �t�F�[�h���̎擾
	//int nFade = GetFade();

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMovebg->Lock(0, 0, (void**)&pVtx, 0);

	// �^�C�g�����S�̈ʒu�X�V
	pVtx[0].pos = D3DXVECTOR3(g_posMovebgLogo.x - (TITLELOGO_X), g_posMovebgLogo.y + (TITLELOGO_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posMovebgLogo.x - (TITLELOGO_X), g_posMovebgLogo.y - (TITLELOGO_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posMovebgLogo.x + (TITLELOGO_X), g_posMovebgLogo.y + (TITLELOGO_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posMovebgLogo.x + (TITLELOGO_X), g_posMovebgLogo.y - (TITLELOGO_Y / 2), 0.0f);

	pVtx[4].pos = D3DXVECTOR3(g_posMovebgLogo2.x - (TITLELOGO_X), g_posMovebgLogo2.y + (TITLELOGO_Y / 2), 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_posMovebgLogo2.x - (TITLELOGO_X), g_posMovebgLogo2.y - (TITLELOGO_Y / 2), 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_posMovebgLogo2.x + (TITLELOGO_X), g_posMovebgLogo2.y + (TITLELOGO_Y / 2), 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_posMovebgLogo2.x + (TITLELOGO_X), g_posMovebgLogo2.y - (TITLELOGO_Y / 2), 0.0f);

	// �^�C�g�����S�̈ʒu�X�V
	pVtx[8].pos = D3DXVECTOR3(g_posMovebgLogo3.x - (TITLELOGO_X), g_posMovebgLogo3.y + (TITLELOGO_Y / 2), 0.0f);
	pVtx[9].pos = D3DXVECTOR3(g_posMovebgLogo3.x - (TITLELOGO_X), g_posMovebgLogo3.y - (TITLELOGO_Y / 2), 0.0f);
	pVtx[10].pos = D3DXVECTOR3(g_posMovebgLogo3.x + (TITLELOGO_X), g_posMovebgLogo3.y + (TITLELOGO_Y / 2), 0.0f);
	pVtx[11].pos = D3DXVECTOR3(g_posMovebgLogo3.x + (TITLELOGO_X), g_posMovebgLogo3.y - (TITLELOGO_Y / 2), 0.0f);

	pVtx[12].pos = D3DXVECTOR3(g_posMovebgLogo4.x - (TITLELOGO_X), g_posMovebgLogo4.y + (TITLELOGO_Y / 2), 0.0f);
	pVtx[13].pos = D3DXVECTOR3(g_posMovebgLogo4.x - (TITLELOGO_X), g_posMovebgLogo4.y - (TITLELOGO_Y / 2), 0.0f);
	pVtx[14].pos = D3DXVECTOR3(g_posMovebgLogo4.x + (TITLELOGO_X), g_posMovebgLogo4.y + (TITLELOGO_Y / 2), 0.0f);
	pVtx[15].pos = D3DXVECTOR3(g_posMovebgLogo4.x + (TITLELOGO_X), g_posMovebgLogo4.y - (TITLELOGO_Y / 2), 0.0f);


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMovebg->Unlock();

	// �X�V����
	if ((g_posMovebgLogo.y - SCREEN_HEIGHT) <= SCREEN_HEIGHT/2)
	{
		g_posMovebgLogo.y += MOVE_MOVEBGLOGO;
	}

	else if ((g_posMovebgLogo.y - SCREEN_HEIGHT) >= SCREEN_HEIGHT / 2)
	{
		g_posMovebgLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, -SCREEN_HEIGHT/2, 0.0f);
	}

	if ((g_posMovebgLogo2.y - SCREEN_HEIGHT) <= SCREEN_HEIGHT / 2)
	{
		g_posMovebgLogo2.y += MOVE_MOVEBGLOGO;
	}

	else if ((g_posMovebgLogo2.y - SCREEN_HEIGHT) >= SCREEN_HEIGHT / 2)
	{
		g_posMovebgLogo2 = D3DXVECTOR3(SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, 0.0f);
	}

	// �X�V����
	if ((g_posMovebgLogo3.y - SCREEN_HEIGHT) <= SCREEN_HEIGHT / 2)
	{
		g_posMovebgLogo3.y += MOVE_MOVEBGLOGO2;
	}

	else if ((g_posMovebgLogo3.y - SCREEN_HEIGHT) >= SCREEN_HEIGHT / 2)
	{
		g_posMovebgLogo3 = D3DXVECTOR3(SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, 0.0f);
	}

	if ((g_posMovebgLogo4.y - SCREEN_HEIGHT) <= SCREEN_HEIGHT / 2)
	{
		g_posMovebgLogo4.y += MOVE_MOVEBGLOGO2;
	}

	else if ((g_posMovebgLogo4.y - SCREEN_HEIGHT) >= SCREEN_HEIGHT / 2)
	{
		g_posMovebgLogo4 = D3DXVECTOR3(SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, 0.0f);
	}
}

//-----------------------------------------------------------------
// �^�C�g���̕`�揈��
//-----------------------------------------------------------------
void DrawMovebg(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMovebg, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntTexture = 0; nCntTexture < MAX_PATTERN; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTextureMovebg[nCntTexture]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}
}

//-----------------------------------------------------------------
// �^�C�g����ʂɓ\��e�N�X�`���̎w��
//-----------------------------------------------------------------
void SetVertexTextureMovebg(int nCntTitle)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMovebg->Lock(0, 0, (void**)&pVtx, 0);

	if (nCntTitle == 0)
	{
		pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	}
	else if (nCntTitle == 1)
	{
		pVtx[4].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	}

	else if (nCntTitle == 2)
	{
		pVtx[8].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	}

	else if (nCntTitle == 3)
	{
		pVtx[12].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[13].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[14].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pVtx[15].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMovebg->Unlock();
}