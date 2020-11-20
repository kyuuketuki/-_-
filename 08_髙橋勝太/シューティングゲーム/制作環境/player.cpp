//-----------------------------------------------------------------
//
// �v���C���[�̏��� (player.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "player.h"
#include "bullet.h"
#include "sound.h"
#include "effect.h"
#include "tutorial.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define PLAYER_X		(30)									// ���S����[�܂ł܂ł̒���(x)
#define PLAYER_Y		(30)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		//�e�N�X�`��
int g_nCounterAnim;									//�A�j���[�V�����J�E���^�[
int g_nPatternAnim;									//�A�j���[�V�����p�^�[��No.
int g_nPatternAnim2;								//�A�j���[�V�����p�^�[��No.
D3DXVECTOR3 g_rotPlayer;							//
float g_fLengthPlayer;								//�Ίp���̒���
float g_fAnglePlayer;								//�Ίp���̊p�x
D3DXVECTOR3 g_movePlayer;							//�ړ���
PLAYER g_Player;									//�|���S���̈ʒu

//-----------------------------------------------------------------------------
// �|���S���̏���������
//-----------------------------------------------------------------------------
HRESULT InitPlayer(void)
{

	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player.png", &g_pTexturePlayer);

	g_Player.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.bUse = true;
	g_Player.nLife = 0;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̈ʒu
	g_Player.Pos = D3DXVECTOR3(1000, 800, 0.0f);

	g_rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�Ίp���̒���
	g_fLengthPlayer = sqrtf(PLAYER_X * PLAYER_X + PLAYER_Y * PLAYER_Y);

	//�Ίp���̊p�x
	g_fAnglePlayer = atan2f(PLAYER_X, PLAYER_Y);

	//���_�̍��W
	pVtx[0].pos.x = (g_Player.Pos.x - sinf(g_fAnglePlayer) * g_fLengthPlayer);
	pVtx[0].pos.y = (g_Player.Pos.y + cosf(g_fAnglePlayer) * g_fLengthPlayer);
	pVtx[0].pos.z = (g_Player.Pos.z = 0.0f);

	pVtx[1].pos.x = (g_Player.Pos.x - sinf(g_fAnglePlayer) * g_fLengthPlayer);
	pVtx[1].pos.y = (g_Player.Pos.y - cosf(g_fAnglePlayer) * g_fLengthPlayer);
	pVtx[1].pos.z = (g_Player.Pos.z = 0.0f);

	pVtx[2].pos.x = (g_Player.Pos.x + sinf(g_fAnglePlayer) * g_fLengthPlayer);
	pVtx[2].pos.y = (g_Player.Pos.y + cosf(g_fAnglePlayer) * g_fLengthPlayer);
	pVtx[2].pos.z = (g_Player.Pos.z = 0.0f);

	pVtx[3].pos.x = (g_Player.Pos.x + sinf(g_fAnglePlayer) * g_fLengthPlayer);
	pVtx[3].pos.y = (g_Player.Pos.y - cosf(g_fAnglePlayer) * g_fLengthPlayer);
	pVtx[3].pos.z = (g_Player.Pos.z = 0.0f);

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

	//���_�̏��̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);



	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// �|���S���̏I������
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{

	//�o�b�t�@�̊J��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
	//�e�N�X�`���̊J��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//-----------------------------------------------------------------------------
// �|���S���̍X�V����
//-----------------------------------------------------------------------------
void UpdatePlayer(void)
{

	VERTEX_2D *pVtx;

	BULLET *pBullet;
	pBullet = GetBullet();

	//g_nCounterAnim++;									//�A�j���[�V�����J�E���^�[�X�V
	//if ((g_nCounterAnim % 10) == 0)
	//{
	//	g_nPatternAnim = (g_nPatternAnim + 1) % 8;		//�A�j���[�V�����p�^�[��No.�X�V
	//}

	////�e�N�X�`�����W
	//pVtx[0].tex = D3DXVECTOR2(0.0f + (0.125f * g_nPatternAnim), 1.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.0f + (0.125f * g_nPatternAnim), 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.125f + (0.125f * g_nPatternAnim), 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(0.125f + (0.125f * g_nPatternAnim), 0.0f);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̈ʒu���X�V
	if (g_Player.bUse == true)
	{
		//A���������Ƃ�
		if (GetKeyboardPress(DIK_A) == true)
		{
			//W���������Ƃ�
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_Player.Pos.x -= sinf(D3DX_PI) * MOVE_NUMBER;
				g_Player.Pos.y -= cosf(D3DX_PI) * MOVE_NUMBER;
			}
			//A��S���������Ƃ�
			else if (GetKeyboardPress(DIK_S) == true)
			{
				g_Player.Pos.x += sinf(-D3DX_PI) * MOVE_NUMBER;
				g_Player.Pos.y += cosf(D3DX_PI) * MOVE_NUMBER;
			}
			//A���������Ƃ�
			else
			{
				g_Player.Pos.x -= MOVE_NUMBER;
				g_Player.Pos.y += 0;
				g_Player.Pos.z += 0.0f;
			}

		}

		//D���������Ƃ�
		if (GetKeyboardPress(DIK_D) == true)
		{
			//D��W���������Ƃ�
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_Player.Pos.x += sinf(D3DX_PI) * MOVE_NUMBER;
				g_Player.Pos.y -= cosf(D3DX_PI) * MOVE_NUMBER;
			}
			//D��S���������Ƃ�
			else if (GetKeyboardPress(DIK_S) == true)
			{
				g_Player.Pos.x += sinf(D3DX_PI) * MOVE_NUMBER;
				g_Player.Pos.y += cosf(D3DX_PI) * MOVE_NUMBER;
			}
			//D���������Ƃ�
			else
			{
				g_Player.Pos.x -= -MOVE_NUMBER;
				g_Player.Pos.y -= 0;
				g_Player.Pos.z += 0.0f;
			}
		}

		//W���������Ƃ�
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_Player.Pos.y -= MOVE_NUMBER;
		}

		//S���������Ƃ�
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_Player.Pos.y += MOVE_NUMBER;
		}

		//��󍶂��������Ƃ�
		if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_rotPlayer.z -= 0.1f;
			if (g_rotPlayer.z > D3DX_PI)
			{
				g_rotPlayer.z -= D3DX_PI * 2.0f;
			}

			g_movePlayer.z -= (g_fAnglePlayer) * 0.01f;
		}

		//���E���������Ƃ�
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_rotPlayer.z += 0.1f;
			if (g_rotPlayer.z > D3DX_PI)
			{
				g_rotPlayer.z -= D3DX_PI * 2.0f;
			}
			g_movePlayer.z += (g_fAnglePlayer) * 0.01f;
		}

		//A���������Ƃ��̉�����
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_movePlayer.x -= sinf(g_fAnglePlayer) * 1;
		}

		//D���������Ƃ��̉�����
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_movePlayer.x += sinf(g_fAnglePlayer) * 1;
		}

		//W���������Ƃ��̉�����
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_movePlayer.y -= cosf(g_fAnglePlayer) * 1;
		}

		//S���������Ƃ��̉�����
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_movePlayer.y += cosf(g_fAnglePlayer) * 1;
		}

		//�e�̔���
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			
			PlaySound(SOUND_LABEL_SE_SHOT);
			SetBullet(g_Player.Pos, D3DXVECTOR3(0.0f, -7.0f, 0.0f), 300, 0);

			for (int nCntBullet = 0; nCntBullet < 1; nCntBullet++)
			{
				D3DXVECTOR3 move;
				D3DXVECTOR3 Pos;
				float fAngle;
				int nLife;
				Pos = g_Player.Pos;
				nLife = 200;
				fAngle = (float)(275) / 100.0f;
				move.x = sinf(fAngle)*7.0f;
				move.y = cosf(fAngle)*7.0f;

				//�e�̔���
				SetBullet(g_Player.Pos, move, nLife, 0);
			}

			for (int nCntBullet = 0; nCntBullet < 1; nCntBullet++)
			{
				D3DXVECTOR3 move;
				D3DXVECTOR3 Pos;
				float fAngle;
				int nLife;
				Pos = g_Player.Pos;
				nLife = 200;
				fAngle = (float)(-275) / 100.0f;
				move.x = sinf(fAngle)*7.0f;
				move.y = cosf(fAngle)*7.0f;

				//�e�̔���
				SetBullet(g_Player.Pos, move, nLife, 0);
			}

		}

		//�ړ�����
		if (g_Player.Pos.x <= 0)
		{
			g_Player.Pos.x = PLAYER_X / 2;
		}

		if (g_Player.Pos.x >= SCREEN_WIDTH)
		{
			g_Player.Pos.x = SCREEN_WIDTH - PLAYER_X / 2;
		}

		if (g_Player.Pos.y <= 0)
		{
			g_Player.Pos.y = PLAYER_Y / 2;
		}

		if (g_Player.Pos.y >= SCREEN_HEIGHT)
		{
			g_Player.Pos.y = SCREEN_HEIGHT - PLAYER_Y / 2;
		}

		//�ʒu�X�V
		g_Player.Pos.x += g_movePlayer.x;
		g_Player.Pos.y += g_movePlayer.y;
		g_rotPlayer.z += g_movePlayer.z;

		//�ړ��ʂ̌���
		g_movePlayer.x += (0 - g_movePlayer.x) * 0.2f;
		g_movePlayer.y += (0 - g_movePlayer.y) * 0.2f;
		g_movePlayer.z += (0 - g_movePlayer.z) * 0.5f;

		//���_�̍��W
		pVtx[0].pos.x = (g_Player.Pos.x - sinf(g_fAnglePlayer + g_rotPlayer.z) * g_fLengthPlayer);
		pVtx[0].pos.y = (g_Player.Pos.y + cosf(g_fAnglePlayer + g_rotPlayer.z) * g_fLengthPlayer);
		pVtx[0].pos.z = (g_Player.Pos.z = 0.0f);

		pVtx[1].pos.x = (g_Player.Pos.x - sinf(g_fAnglePlayer - g_rotPlayer.z) * g_fLengthPlayer);
		pVtx[1].pos.y = (g_Player.Pos.y - cosf(g_fAnglePlayer - g_rotPlayer.z) * g_fLengthPlayer);
		pVtx[1].pos.z = (g_Player.Pos.z = 0.0f);

		pVtx[2].pos.x = (g_Player.Pos.x + sinf(g_fAnglePlayer - g_rotPlayer.z) * g_fLengthPlayer);
		pVtx[2].pos.y = (g_Player.Pos.y + cosf(g_fAnglePlayer - g_rotPlayer.z) * g_fLengthPlayer);
		pVtx[2].pos.z = (g_Player.Pos.z = 0.0f);

		pVtx[3].pos.x = (g_Player.Pos.x + sinf(g_fAnglePlayer + g_rotPlayer.z) * g_fLengthPlayer);
		pVtx[3].pos.y = (g_Player.Pos.y - cosf(g_fAnglePlayer + g_rotPlayer.z) * g_fLengthPlayer);
		pVtx[3].pos.z = (g_Player.Pos.z = 0.0f);
	}

	g_pVtxBuffPlayer->Unlock(); //�A�����b�N
}
//-----------------------------------------------------------------------------
// �|���S���̕`�揈��
//-----------------------------------------------------------------------------
void DrawPlayer(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	if (g_Player.bUse == true)//�e���g�p���Ă��邩�ǂ���
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

}

PLAYER * GetPlayer(void)
{
	return &g_Player;
}