//-----------------------------------------------------------------
//
// bullhet (bullet.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "bullet.h"
#include "Explosion.h"
#include "score.h"
#include "sound.h"
#include "enemy.h"
#include "player.h"
#include "game.h"
#include "fade.h"
#include "boss.h"
#include "effect.h"
#include "result.h"
#include "tutorial.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureBullet[3] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
BULLET g_aBullet[MAX_BULLET];//�e�̏��


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitBullet(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\10.png", &g_pTextureBullet[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\10.png", &g_pTextureBullet[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\10.png", &g_pTextureBullet[2]);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 10;
		g_aBullet[nCntBullet].nType = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W
		SetVertexBullet(nCntBullet);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		////���_�̃J���[�ݒ�
		//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 0);
		//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 0);
		//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 0);
		//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 255, 255, 255);

		//���_�̏��̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock(); //�A�����b�N

	return S_OK;
}

//-----------------------------------------------------------------------------
//�@�I������
//-----------------------------------------------------------------------------
void UninitBullet(void)
{
	for (int nCount = 0; nCount < MAX_TYPE_ENEMY; nCount++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureBullet != NULL)
		{
			g_pTextureBullet[nCount]->Release();
			g_pTextureBullet[nCount] = NULL;
		}
	}

	//�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateBullet(void)
{
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{

		if (pBullet->bUse == true)
		{
			D3DXVECTOR3 move;
			move.x = sinf(D3DX_PI)*4.5;
			move.y = -cosf(D3DX_PI)*4.5;
			SetEffect(pBullet->pos, 2, move, pBullet->nType);

			//�ʒu�̍X�V
			pBullet->pos.x += pBullet->move.x;
			pBullet->pos.y += pBullet->move.y;

			//�ʒu�̍X�V
			pBullet->pos.x += pBullet->move.x;
			pBullet->pos.y += pBullet->move.y;

			//���_���W
			SetVertexBullet(nCntBullet);

			//�����`�F�b�N
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife == 0)
			{
				//SetExplosion(pBullet->pos);
				g_aBullet[nCntBullet].bUse = false;
			}

			//��ʊO�`�F�b�N
			if (pBullet->pos.y < -10)
			{
				pBullet->bUse = false;
			}

			//SetEffect(pBullet->pos,5);

			//�G�Ƃ̓����蔻��
			ENEMY *pEnemy;
			pEnemy = GetEnemy();

			PLAYER *pPlayer;
			pPlayer = GetPlayer();

			//�v���C���[�����蔻��
			if (g_aBullet[nCntBullet].nType == 1 || g_aBullet[nCntBullet].nType == 2)
			{
				if (pPlayer->bUse == true)
				{
					if (pBullet->pos.y > pPlayer->Pos.y - 15 && pBullet->pos.y < pPlayer->Pos.y + 15 &&
						pBullet->pos.x > pPlayer->Pos.x - 15 && pBullet->pos.x < pPlayer->Pos.x + 15)
					{
						//������
						SetExplosion(pPlayer->Pos);

						//�v���C���[����
						pPlayer->bUse = false;

						//��ʐ؂�ւ�
						SetFade(FADE_OUT, MODE_RESULT);
					}
				}
			}

			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				if (g_aBullet[nCntBullet].nType == 0)
				{
					if (pEnemy->bUse == true)
					{
						if (pBullet->pos.y > pEnemy->Pos.y - MAX_ENEMY_SIZE && pBullet->pos.y < pEnemy->Pos.y + MAX_ENEMY_SIZE &&
							pBullet->pos.x > pEnemy->Pos.x - MAX_ENEMY_SIZE && pBullet->pos.x < pEnemy->Pos.x + MAX_ENEMY_SIZE)
						{
							//������
							//SetExplosion(pEnemy->Pos);

							//�T�E���h
							//PlaySound(SOUND_LABEL_SE_EXPLOSION);

							//�X�R�A���Z
							//AddScore(100);

							//�e������
							pBullet->bUse = false;

							HitEnemy(nCntEnemy, 1);

							//��ʐ؂�ւ�
							//SetFade(FADE_OUT, MODE_RESULT);
						}
					}
				}
			}

			//�G�Ƃ̓����蔻��
			BOSS *pBoss;
			pBoss = GetBoss();

			for (int nCntEnemy = 0; nCntEnemy < MAX_BOSS; nCntEnemy++, pBoss++)
			{
				if (g_aBullet[nCntBullet].nType == 0)
				{
					if (pBoss->bUse == true)
					{
						if (pBullet->pos.y > pBoss->Pos.y - MAX_BOSS_SIZE && pBullet->pos.y < pBoss->Pos.y + MAX_BOSS_SIZE &&
							pBullet->pos.x > pBoss->Pos.x - MAX_BOSS_SIZE && pBullet->pos.x < pBoss->Pos.x + MAX_BOSS_SIZE)
						{
							//������
							SetExplosion(pBoss->Pos);

							HitBoss(nCntEnemy, 1);

							PlaySound(SOUND_LABEL_SE_EXPLOSION);

							//�X�R�A���Z
							AddScore(100);

							//�e������
							pBullet->bUse = false;
						}
					}
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawBullet(void)
{
	BULLET *pBullet;

	//VERTEX_2D *pVtx;

	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pBullet = &g_aBullet[0];

	//�|���S���̕`��
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBullet[pBullet->nType]);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBullet[pBullet[nCntBullet].nType]);

		if (pBullet[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

//-----------------------------------------------------------------------------
// �e�̐ݒ�
//-----------------------------------------------------------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType)
{
	BULLET *pBullet;

	VERTEX_2D *pVtx;

	pBullet = &g_aBullet[0];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			//�ʒu
			pBullet->pos = pos;

			//���_���W
			SetVertexBullet(nCntBullet);

			//�ړ���
			pBullet->move = move;

			//����
			pBullet->nLife = nLife;

			pBullet->nType = nType;

			pBullet->bUse = true;

			break;
		}
		pVtx += 4;//4���_���Ƃ��炷
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//-----------------------------------------------------------------------------
// �e�̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------
void SetVertexBullet(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZE, g_aBullet[nIdx].pos.y + BULLET_SIZE, 1.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZE, g_aBullet[nIdx].pos.y - BULLET_SIZE, 1.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZE, g_aBullet[nIdx].pos.y + BULLET_SIZE, 1.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZE, g_aBullet[nIdx].pos.y - BULLET_SIZE, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//-------------------------------
//�e�̏��擾
//-------------------------------
BULLET * GetBullet(void)
{
	return &g_aBullet[0];
}