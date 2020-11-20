//-----------------------------------------------------------------
//
// enemy (enemy.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//--------------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------------
#include "enemy.h"
#include "sound.h"
#include "score.h"
#include "bullet.h"
#include "fade.h"
#include "boss.h"
#include "effect.h"
#include "bullet.h"
#include "appeared.h"

//----------------------------------------------
//�O���[�o���ϐ�
//----------------------------------------------
LPDIRECT3DTEXTURE9 g_apTextureEnemy[3] = {};//�e�N�X�`���փ|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;//���_�o�b�t�@�ւ̃|�C���^
ENEMY g_aEnemy[256];//�G�̏��
D3DXVECTOR3 g_posEnemy;
D3DXVECTOR3 g_rotEnemy;
D3DXVECTOR3 g_moveEnemy;
float g_fLengthEnemy;//�Ίp���̒���
float g_fAngleEnemy;//�Ίp���̊p�x
int g_nData = 26;//�N���A����
int g_nTime = 0;

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�N���A����������
	g_nData = 26;

	g_nTime++;

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy001.png", &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy002.png", &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy003.png", &g_apTextureEnemy[2]);

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 6;
	}
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 256,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y + MAX_ENEMY_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y - MAX_ENEMY_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y + MAX_ENEMY_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y - MAX_ENEMY_SIZE, 0.0f);

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
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//�@�I������
//-----------------------------------------------------------------------------
void UninitEnemy(void)
{
	//�e�N�X�`���̊J��
	for (int nCount = 0; nCount < MAX_TYPE_ENEMY; nCount++)
	{
		if (g_apTextureEnemy[nCount] != NULL)
		{
			g_apTextureEnemy[nCount]->Release();
			g_apTextureEnemy[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateEnemy(void)
{
	VERTEX_2D *pVtx;

	ENEMY *pEnemy;

	pEnemy = &g_aEnemy[0];

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒���
	g_fLengthEnemy = sqrtf(MAX_ENEMY_SIZE * MAX_ENEMY_SIZE + MAX_ENEMY_SIZE * MAX_ENEMY_SIZE);

	//�Ίp���̊p�x
	g_fAngleEnemy = atan2f(MAX_ENEMY_SIZE, MAX_ENEMY_SIZE);

	//�G�A�j���[�V����
	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].g_nCounterAni++;

			if ((g_aEnemy[nCntEnemy].g_nCounterAni % 80) == 0)
			{
				g_aEnemy[nCntEnemy].g_nPatternAni++;

				g_aEnemy[nCntEnemy].g_nseetAni = (g_aEnemy[nCntEnemy].g_nseetAni + 1) % 10;

				//�G�̃A�j���[�V����
				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f*g_aEnemy[nCntEnemy].g_nseetAni, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + 0.5f*g_aEnemy[nCntEnemy].g_nseetAni, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f + 0.5f*g_aEnemy[nCntEnemy].g_nseetAni, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f*g_aEnemy[nCntEnemy].g_nseetAni, 0.0f);
			}

			g_aEnemy[nCntEnemy].Pos.x += 2;
			g_aEnemy[nCntEnemy].Pos.z += 0.0f;

			if (g_aEnemy[nCntEnemy].Pos.x >= SCREEN_WIDTH)
			{
				g_aEnemy[nCntEnemy].Pos.x *= -1;
				g_aEnemy[nCntEnemy].Pos.y += 100;
				g_aEnemy[nCntEnemy].Pos.x *= 0.0f;
			}
			else if (g_aEnemy[nCntEnemy].Pos.x <= 0)
			{
				g_aEnemy[nCntEnemy].Pos.y += 100;
				g_aEnemy[nCntEnemy].Pos.y += 0.0f;
			}

			int nCnt = rand() % 50;
			if (nCnt == 1)
			{
				//�e�̔���
				SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x, g_aEnemy[nCntEnemy].Pos.y + 50, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 300, 1);
			}

			//for (int nCntEnemy = 0; nCntEnemy < 7; nCntEnemy++)
			//{
			//	/*D3DXVECTOR3 move;
			//	D3DXVECTOR3 Pos;
			//	float fAngle;


			//	int nLife;

			//	Pos = pEnemy->Pos;
			//	nLife = 50;
			//	fAngle = (float)(rand() % 157 - 78) / 100.0f;
			//	fAngle = (float)(rand() % 628 - 314) / 100.0f;
			//	move.x = sinf(fAngle)*3.5f;
			//	move.y = cosf(fAngle)*3.5f;

			//	move.x = sinf(D3DX_PI)*3.5;
			//	move.y = -cosf(D3DX_PI)*3.5;

			//	SetEffect(Pos,nLife,move);


			//	SetBullet(g_aEnemy[nCntEnemy].Pos, move, nLife, 1);*/
			//}
			

			//�G�̈ʒu�f�[�^
			pVtx[0].pos.x = g_aEnemy[nCntEnemy].Pos.x + sinf(g_rotEnemy.z - g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].Pos.y + cosf(g_rotEnemy.z - g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEnemy[nCntEnemy].Pos.x - sinf(g_rotEnemy.z + g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].Pos.y - cosf(g_rotEnemy.z + g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEnemy[nCntEnemy].Pos.x + sinf(g_rotEnemy.z + g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].Pos.y + cosf(g_rotEnemy.z + g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEnemy[nCntEnemy].Pos.x - sinf(g_rotEnemy.z - g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].Pos.y - cosf(g_rotEnemy.z - g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[3].pos.z = 0.0f;

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
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
	g_pVtxBuffEnemy->Unlock();
}

//-------------------------------------------------
//�G�̕`�揈��
//-------------------------------------------------
void DrawEnemy(void)
{
	ENEMY *pEnemy;

	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pEnemy = &g_aEnemy[0];

	//�|���S���̕`��
	for (int nCutEnemy = 0; nCutEnemy < 256; nCutEnemy++, pEnemy++)
	{
		pDevice->SetTexture(0, g_apTextureEnemy[pEnemy->nType]);

		if (pEnemy->bUse == true)//�e���g�p���Ă��邩�ǂ���
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutEnemy * 4, 2);
		}
	}
}

//-----------------------------------------------
//�G�̏o��
//-----------------------------------------------
void SetEnemy(D3DXVECTOR3 Pos, int nType)
{
	ENEMY *pEnemy;

	VERTEX_2D *pVtx;

	pEnemy = &g_aEnemy[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pEnemy++)
	{

		if (pEnemy->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			//�ʒu�ݒ�
			g_aEnemy[nCntEnemy].Pos = Pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y + MAX_ENEMY_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y - MAX_ENEMY_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y + MAX_ENEMY_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y - MAX_ENEMY_SIZE, 0.0f);

			pEnemy->nType = nType;

			//�e�̎g�p
			pEnemy->bUse = true;

			break;
		}

		pVtx += 4;//4���_���Ƃ��炷

	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();

}

//-----------------------------------------------
//�G���̎擾
//-----------------------------------------------
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}

bool HitEnemy(int nIdx, int nDamage)
{
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[nIdx];
	VERTEX_2D *pVtx;
	BULLET *pBullet;
	pBullet = GetBullet();

	g_aEnemy[nIdx].nLife -= nDamage;

	//�G�̃��C�t0�ȉ��̏ꍇ
	if (g_aEnemy[nIdx].nLife <= 0)
	{
		//�T�E���h
		PlaySound(SOUND_LABEL_SE_EXPLOSION);

		//�X�R�A���Z
		AddScore(100);

		//�G�̐�
		g_nTime++;
		g_nData--;

		//�G������
		g_aEnemy[nIdx].bUse = false;

		//�e������
		pBullet->bUse = false;

		//�����̍X�V����
		UpdateExplosion();

		//�G�̏ꏊ�ɔ��j
		SetExplosion(pEnemy->Pos);

		if (g_nData == 0)
		{
			//�{�X�̏o��
			SetAppeared(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), 300,30);
			SetBoss(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), 0);
			//��ʐ؂�ւ�
			//SetFade(FADE_OUT, MODE_RESULT);
		}

		return true;
	}
	else
	{

		AddScore(10);

		g_aEnemy[nIdx].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nIdx].nCounterState = 10;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
  		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nIdx * 4;

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();
	}

	return false;
}

//�N���A�������擾
int GetEnemyNomber(void)
{
	return g_nData;
}
