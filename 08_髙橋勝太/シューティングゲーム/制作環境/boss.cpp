//-----------------------------------------------------------------
//
// boss (boss.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "boss.h"
#include "sound.h"
#include "score.h"
#include "bullet.h"
#include "fade.h"
#include "appeared.h"

//------------------------------
//�O���[�o���ϐ�
//-------------------------------
LPDIRECT3DTEXTURE9 g_apTextureBoss[3] = {};//�e�N�X�`���փ|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;//���_�o�b�t�@�ւ̃|�C���^
BOSS g_aBoss[256];//�G�̏��
D3DXVECTOR3 g_posBoss;
D3DXVECTOR3 g_rotBoss;
D3DXVECTOR3 g_moveBoss;
float g_fLengthBoss;//�Ίp���̒���
float g_fAngleBoss;//�Ίp���̊p�x
int g_nDataBoss = 1;//�N���A����

//---------------------------------------
//����������
//----------------------------------------
HRESULT InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/01.png", &g_apTextureBoss[0]);

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++)
	{
		g_aBoss[nCntEnemy].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntEnemy].nType = 0;
		g_aBoss[nCntEnemy].bUse = false;
		g_aBoss[nCntEnemy].state = BOSSSTATE_NOMAL;
		g_aBoss[nCntEnemy].nCounterState = 0;
		g_aBoss[nCntEnemy].nLife = 300;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 256,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBoss,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntEnemy].Pos.x - MAX_BOSS_SIZE, g_aBoss[nCntEnemy].Pos.y + MAX_BOSS_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntEnemy].Pos.x - MAX_BOSS_SIZE, g_aBoss[nCntEnemy].Pos.y - MAX_BOSS_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntEnemy].Pos.x + MAX_BOSS_SIZE, g_aBoss[nCntEnemy].Pos.y + MAX_BOSS_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntEnemy].Pos.x + MAX_BOSS_SIZE, g_aBoss[nCntEnemy].Pos.y - MAX_BOSS_SIZE, 0.0f);

		////rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 0.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBoss->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void UninitBoss(void)
{
	//�e�N�X�`���̊J��
	for (int nCount = 0; nCount < MAX_TYPE_ENEMY; nCount++)
	{
		if (g_apTextureBoss[nCount] != NULL)
		{
			g_apTextureBoss[nCount]->Release();
			g_apTextureBoss[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateBoss(void)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒���
	g_fLengthBoss = sqrtf(MAX_BOSS_SIZE * MAX_BOSS_SIZE + MAX_BOSS_SIZE * MAX_BOSS_SIZE);

	//�Ίp���̊p�x
	g_fAngleBoss = atan2f(MAX_BOSS_SIZE, MAX_BOSS_SIZE);

	//�G�A�j���[�V����
	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++)
	{
		if (g_aBoss[nCntEnemy].bUse == true)
		{
			g_aBoss[nCntEnemy].g_nCounterAni++;

			if ((g_aBoss[nCntEnemy].g_nCounterAni % 5) == 0)
			{
				g_aBoss[nCntEnemy].g_nPatternAni++;

				g_aBoss[nCntEnemy].g_nseetAni = (g_aBoss[nCntEnemy].g_nseetAni + 1) % 10;

				//�G�̃A�j���[�V����
				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.125f*g_aBoss[nCntEnemy].g_nseetAni, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + 0.125f*g_aBoss[nCntEnemy].g_nseetAni, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.125f + 0.125f*g_aBoss[nCntEnemy].g_nseetAni, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f*g_aBoss[nCntEnemy].g_nseetAni, 0.0f);

				//�e�̔���
				//SetBullet(D3DXVECTOR3(g_aBoss[nCntEnemy].Pos.x, g_aBoss[nCntEnemy].Pos.y + 50, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 300, 1);

			}

			int nCntBullet = rand() % 2;
			int nCntBullet2 = rand() % 3;

			if(nCntBullet == 1)
			{
				D3DXVECTOR3 move;
				D3DXVECTOR3 Pos;

				float fAngle;
				int nLife;

				//Pos = g_aBoss->Pos;
				nLife = 200;
				//fAngle = (float)(rand() % 157 - 78) / 100.0f;
				fAngle = (float)(rand() % 628 - 314) / 100.0f;
				move.x = sinf(fAngle)*2.5f;
				move.y = cosf(fAngle)*2.5f;
				//move.x = sinf(D3DX_PI)*3.5;
				//move.y = -cosf(D3DX_PI)*3.5;

				//SetEffect(Pos,nLife,move);

				//�e�̔���
				//SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x, g_aEnemy[nCntEnemy].Pos.y + 50, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 300, 1);
				SetBullet(g_aBoss[nCntEnemy].Pos, move, nLife, 1);
			}

			if (nCntBullet2 == 1)
			{
				if (g_aBoss[nCntEnemy].nLife <= 200)
				{
					D3DXVECTOR3 move;
					D3DXVECTOR3 Pos;

					float fAngle;
					int nLife;

					//Pos = g_aBoss->Pos;
					nLife = 500;
					//fAngle = (float)(rand() % 157 - 78) / 100.0f;
					fAngle = (float)(rand() % 628 - 314) / 100.0f;
					move.x = sinf(fAngle)*1.0f;
					move.y = cosf(fAngle)*1.0f;
					//move.x = sinf(D3DX_PI)*3.5;
					//move.y = -cosf(D3DX_PI)*3.5;

					//SetEffect(Pos,nLife,move);

					//�e�̔���
					//SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x, g_aEnemy[nCntEnemy].Pos.y + 50, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 300, 1);
					SetBullet(g_aBoss[nCntEnemy].Pos, move, nLife, 2);
				}
			}

			if (g_aBoss[nCntEnemy].nLife <= 150)
			{
				//��ʐ؂�ւ�
				//SetFade(FADE_OUT, MODE_RESULT);
				int nA = rand() % 1500;
				int nB = rand() % 1000;
				int nC = rand() % 200;
				int nCnt = rand() % 30;

				if (nCnt == 1)
				{
					SetAppeared(D3DXVECTOR3(nA, nB, 0.0f), 100, 30);
				}
			}

			//�G�̈ʒu�f�[�^
			pVtx[0].pos.x = g_aBoss[nCntEnemy].Pos.x + sinf(g_rotBoss.z - g_fAngleBoss) * g_fLengthBoss;
			pVtx[0].pos.y = g_aBoss[nCntEnemy].Pos.y + cosf(g_rotBoss.z - g_fAngleBoss) * g_fLengthBoss;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aBoss[nCntEnemy].Pos.x - sinf(g_rotBoss.z + g_fAngleBoss) * g_fLengthBoss;
			pVtx[1].pos.y = g_aBoss[nCntEnemy].Pos.y - cosf(g_rotBoss.z + g_fAngleBoss) * g_fLengthBoss;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aBoss[nCntEnemy].Pos.x + sinf(g_rotBoss.z + g_fAngleBoss) * g_fLengthBoss;
			pVtx[2].pos.y = g_aBoss[nCntEnemy].Pos.y + cosf(g_rotBoss.z + g_fAngleBoss) * g_fLengthBoss;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aBoss[nCntEnemy].Pos.x - sinf(g_rotBoss.z - g_fAngleBoss) * g_fLengthBoss;
			pVtx[3].pos.y = g_aBoss[nCntEnemy].Pos.y - cosf(g_rotBoss.z - g_fAngleBoss) * g_fLengthBoss;
			pVtx[3].pos.z = 0.0f;



			switch (g_aBoss[nCntEnemy].state)
			{
			case ENEMYSTATE_DAMAGE:
				g_aBoss[nCntEnemy].nCounterState--;
				if (g_aBoss[nCntEnemy].nCounterState <= 0)
				{
					g_aBoss[nCntEnemy].state = BOSSSTATE_NOMAL;

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;

			}
		}
		pVtx += 4;//4���_���Ƃ��炷
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBoss->Unlock();
}

//==================
//�{�X�̕`�揈��
//==================
void DrawBoss(void)
{
	BOSS *pBoss;

	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pBoss = &g_aBoss[0];

	//�|���S���̕`��
	for (int nCutBoss = 0; nCutBoss < 256; nCutBoss++, pBoss++)
	{
		pDevice->SetTexture(0, g_apTextureBoss[pBoss->nType]);

		if (pBoss->bUse == true)//�e���g�p���Ă��邩�ǂ���
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutBoss * 4, 2);
		}
	}
}

void SetBoss(D3DXVECTOR3 Pos, int nType)
{
	BOSS *pBoss;

	VERTEX_2D *pVtx;

	pBoss = &g_aBoss[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pBoss++)
	{
		if (pBoss->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			//�ʒu�ݒ�
			g_aBoss[nCntEnemy].Pos = Pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntEnemy].Pos.x - MAX_BOSS_SIZE, g_aBoss[nCntEnemy].Pos.y + MAX_BOSS_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntEnemy].Pos.x - MAX_BOSS_SIZE, g_aBoss[nCntEnemy].Pos.y - MAX_BOSS_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntEnemy].Pos.x + MAX_BOSS_SIZE, g_aBoss[nCntEnemy].Pos.y + MAX_BOSS_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntEnemy].Pos.x + MAX_BOSS_SIZE, g_aBoss[nCntEnemy].Pos.y - MAX_BOSS_SIZE, 0.0f);

			pBoss->nType = nType;

			//�e�̎g�p
			pBoss->bUse = true;

			break;
		}

		pVtx += 4;//4���_���Ƃ��炷

	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBoss->Unlock();

}

//----------------------------
//�{�X���̎擾
//----------------------------
BOSS *GetBoss(void)
{
	return &g_aBoss[0];
}

//----------------------------
//�{�X��������
//----------------------------
bool HitBoss(int nIdx, int nDamage)
{
	BOSS *pBoss;
	pBoss = &g_aBoss[nIdx];
	VERTEX_2D *pVtx;

	g_aBoss[nIdx].nLife -= nDamage;

	if (g_aBoss[nIdx].nLife <= 0)
	{
		PlaySound(SOUND_LABEL_SE_EXPLOSION);

		AddScore(10000);

		//�G�̐�
		g_nDataBoss--;

		g_aBoss[nIdx].bUse = false;

		//�����̍X�V����
		//UpdateExplosion();

		SetExplosion(pBoss->Pos);

		if (g_nDataBoss == 0)
		{
			//�{�X�̏o��
			//SetBoss(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), 0);

			//��ʐ؂�ւ�
			SetFade(FADE_OUT, MODE_RESULT);
		}

		return true;
	
	}
	else
	{
		AddScore(10);

		g_aBoss[nIdx].state = BOSSSTATE_DAMAGE;
		g_aBoss[nIdx].nCounterState = 10; //�_���[�W��Ԃ̎���

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nIdx * 4;

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBoss->Unlock();
	}
	return false;
}

//�N���A�������擾
int GetBossNomber(void)
{
	return g_nDataBoss;
}
