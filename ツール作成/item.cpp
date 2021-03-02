//==============================================================================
//
// 3D���f���̕`��kitem.cpp�l
// AUTHOR : TAKAHASHI SHOTA
//
//==============================================================================
#include "item.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "math.h"
#include "game.h"
#include "effect.h"
#include "car.h"
#include "score.h"
#include "fade.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_ITEM_TYPE		(1)								// �^�C�v��

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPD3DXMESH g_pMeshItem[MAX_ITEM_TYPE] = {};				// ���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatItem[MAX_ITEM_TYPE] = {};		// �}�e���A��(�ގ����)�ւ̃|�C���^
DWORD g_nNumMatItem = 10;									// �}�e���A���̐�
ITEM item[MAX_ITEM];
int g_nCnyDateItem;
int g_nDateItemNumberItem = 0;
int g_nDateItemNumberItem2 = 0;
int MaxItem = 0;
int MaxItemType = 0;
int nItemScoe = 0;

//==============================================================================
// ����������
//==============================================================================
HRESULT InitItem(void)
{
	//�N���A�����̏�����
	nItemScoe = 0;

	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	//�O���[�o���ϐ��ɋL��������
	MaxItem = MAX_ITEM;
	MaxItemType = MAX_ITEM_TYPE;

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/baloon01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatItem[0], NULL, &g_nNumMatItem, &g_pMeshItem[0]);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// ���_�����擾
		item[nCntItem].nNumVtx = g_pMeshItem[item[nCntItem].nType]->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
		item[nCntItem].sizeFVF = D3DXGetFVFVertexSize(g_pMeshItem[item[nCntItem].nType]->GetFVF());

		// �ϐ��̏�����
		item[nCntItem].pos = D3DXVECTOR3(0.0f, -500.0f, 0.0f);
		item[nCntItem].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		item[nCntItem].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		item[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		item[nCntItem].bUse = false;
		item[nCntItem].nType = 0;
	}
	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitItem(void)
{
	// ���b�V���̔j��
	if (g_pMeshItem[0] != NULL)
	{
		g_pMeshItem[0]->Release();
		g_pMeshItem[0] = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < MAX_ITEM_TYPE; nCntTexture++)
	{
		// �}�e���A���̔j��
		if (g_pBuffMatItem[nCntTexture] != NULL)
		{
			g_pBuffMatItem[nCntTexture]->Release();
			g_pBuffMatItem[nCntTexture] = NULL;
		}
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateItem(void)
{

	if (GetKeyboardTrigger(DIK_Y) == true)
	{
		item[g_nDateItemNumberItem - g_nDateItemNumberItem2].bUse = false;
		g_nDateItemNumberItem2 += 1;
	}

	if (GetKeyboardTrigger(DIK_T) == true)
	{
		g_nDateItemNumberItem2 = 0;
	}

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// ���_�����擾
		item[nCntItem].nNumVtx = g_pMeshItem[item[nCntItem].nType]->GetNumVertices();
		//item[nCntItem].nNumVtx = g_pMeshItem[item[0].nType]->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
		item[nCntItem].sizeFVF = D3DXGetFVFVertexSize(g_pMeshItem[item[nCntItem].nType]->GetFVF());

		// ���_�o�b�t�@�����b�N
		g_pMeshItem[item[nCntItem].nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&item[nCntItem].pVtxBuff);

		// ���_���W�̔�r
		for (int nCntVtx = 0; nCntVtx < item[nCntItem].nNumVtx; nCntVtx++)
		{
			item[nCntItem].vtx = *(D3DXVECTOR3*)item[nCntItem].pVtxBuff;	// ���_���W�̑��

			// �e���W�̍ő�l�̔�r
			if (item[nCntItem].vtxMaxItem.x < item[nCntItem].vtx.x)
			{
				item[nCntItem].vtxMaxItem.x = item[nCntItem].vtx.x;
			}
			if (item[nCntItem].vtxMaxItem.y < item[nCntItem].vtx.y)
			{
				item[nCntItem].vtxMaxItem.y = item[nCntItem].vtx.y;
			}
			if (item[nCntItem].vtxMaxItem.z < item[nCntItem].vtx.z)
			{
				item[nCntItem].vtxMaxItem.z = item[nCntItem].vtx.z;
			}

			// �e���W�̍ŏ��l�̔�r
			if (item[nCntItem].vtxMinItem.x > item[nCntItem].vtx.x)
			{
				item[nCntItem].vtxMinItem.x = item[nCntItem].vtx.x;
			}
			if (item[nCntItem].vtxMinItem.y > item[nCntItem].vtx.y)
			{
				item[nCntItem].vtxMinItem.y = item[nCntItem].vtx.y;
			}
			if (item[nCntItem].vtxMinItem.z > item[nCntItem].vtx.z)
			{
				item[nCntItem].vtxMinItem.z = item[nCntItem].vtx.z;
			}

			item[nCntItem].pVtxBuff += item[nCntItem].sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}
		// ���_�o�b�t�@���A�����b�N
		g_pMeshItem[item[nCntItem].nType]->UnlockVertexBuffer();
	}

	//�N���A�����ɒB������
	if (nItemScoe == 15)
	{
		//SetFade(FADE_OUT, MODE_RESULT);
		SetFade(FADE_OUT, MODE_RANKING);
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawItem(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&item[nCntItem].mtxWorld);

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, item[nCntItem].rot.y, item[nCntItem].rot.x, item[nCntItem].rot.z);
		D3DXMatrixMultiply(&item[nCntItem].mtxWorld, &item[nCntItem].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, item[nCntItem].pos.x, item[nCntItem].pos.y, item[nCntItem].pos.z);
		D3DXMatrixMultiply(&item[nCntItem].mtxWorld, &item[nCntItem].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &item[nCntItem].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		//pMat = (D3DXMATERIAL*)g_pBuffMatItem[0]->GetBufferPointer();

		pMat = (D3DXMATERIAL*)g_pBuffMatItem[item[nCntItem].nType]->GetBufferPointer();

		//�g�p����Ă���Ƃ�
		if (item[nCntItem].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatItem; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
				//pDevice->SetTexture(0, NULL);

				// ���f��(�p�[�c)�̕`��
				g_pMeshItem[item[nCntItem].nType]->DrawSubset(nCntMat);

				// �ۑ����Ă����}�e���A����߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//==============================================================================
// �O�ς𗘗p���������蔻��
//==============================================================================
bool CollisionVecItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
{
	// ���[�J���ϐ��錾
	bool bLand = false;
	D3DXVECTOR3 aVec[COLLISION_PARTS];	// ��`���_���画��Ώۂւ̃x�N�g��
	float fPlayerVec[COLLISION_PARTS];	// �e�ʂ̃x�N�g���Ƃ̔���i�{�|�j
	D3DXVECTOR3 pos = *pPos;			// ����Ώۂ̈ʒu

	CAR  *pCar;
	pCar = GetCar();

	int nCntItem = 0;
	int nCntItemPlayerVec = 0;

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// �I�u�W�F�N�g��`�̊e���_
		item[nCntItem].aPos[0 + (4 * nCntItem)] = D3DXVECTOR3(item[nCntItem].pos.x + item[nCntItem].vtxMinItem.x, 0.0f, item[nCntItem].pos.z + item[nCntItem].vtxMinItem.z);	// ����O
		item[nCntItem].aPos[1 + (4 * nCntItem)] = D3DXVECTOR3(item[nCntItem].pos.x + item[nCntItem].vtxMinItem.x, 0.0f, item[nCntItem].pos.z + item[nCntItem].vtxMaxItem.z);	// ����
		item[nCntItem].aPos[2 + (4 * nCntItem)] = D3DXVECTOR3(item[nCntItem].pos.x + item[nCntItem].vtxMaxItem.x, 0.0f, item[nCntItem].pos.z + item[nCntItem].vtxMaxItem.z);	// �E��
		item[nCntItem].aPos[3 + (4 * nCntItem)] = D3DXVECTOR3(item[nCntItem].pos.x + item[nCntItem].vtxMaxItem.x, 0.0f, item[nCntItem].pos.z + item[nCntItem].vtxMinItem.z);	// �E��O
																																												// �I�u�W�F�N�g��`�̊e�ʂ̃x�N�g��
		item[nCntItem].aVec[0 + (4 * nCntItem)] = item[nCntItem].aPos[1 + (4 * nCntItem)] - item[nCntItem].aPos[0 + (4 * nCntItem)];
		item[nCntItem].aVec[1 + (4 * nCntItem)] = item[nCntItem].aPos[2 + (4 * nCntItem)] - item[nCntItem].aPos[1 + (4 * nCntItem)];
		item[nCntItem].aVec[2 + (4 * nCntItem)] = item[nCntItem].aPos[3 + (4 * nCntItem)] - item[nCntItem].aPos[2 + (4 * nCntItem)];
		item[nCntItem].aVec[3 + (4 * nCntItem)] = item[nCntItem].aPos[0 + (4 * nCntItem)] - item[nCntItem].aPos[3 + (4 * nCntItem)];
	}

	for (int nCntItemUse = 0; nCntItemUse < MAX_ITEM; nCntItemUse++)
	{
		//�g�p����Ă���Ƃ�
		if (item[nCntItemUse].bUse == true)
		{
			//����������
			g_nCnyDateItem = 0;
			nCntItem = 0;

			// �I�u�W�F�N�g�Ƃ̓����蔻��
			for (int nCnt = 0; nCnt < COLLISION_PARTS; nCnt++)
			{
				if (nCnt == 0 + g_nCnyDateItem)
				{// ����
					aVec[nCnt] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - item[nCntItem].aPos[nCnt];
				}
				else if (nCnt == 1 + g_nCnyDateItem)
				{// ����
					aVec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - item[nCntItem].aPos[nCnt];
				}
				else if (nCnt == 2 + g_nCnyDateItem)
				{// �E��
					aVec[nCnt] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - item[nCntItem].aPos[nCnt];
				}
				else if (nCnt == 3 + g_nCnyDateItem)
				{// ��O
					aVec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - item[nCntItem].aPos[nCnt];
				}

				// ���l���u+�v�̎��A�����蔻�肪�L��
				fPlayerVec[nCnt] = (item[nCntItem].aVec[nCnt].z * aVec[nCnt].x) - (item[nCntItem].aVec[nCnt].x * aVec[nCnt].z);

				if (pPos->y <= item[nCntItem].pos.y + item[nCntItem].vtxMaxItem.y - fHeightMin && pPos->y > item[nCntItem].pos.y + item[nCntItem].vtxMinItem.y - fHeightMax)
				{
					if (fPlayerVec[0 + (4 * nCntItem)] > 0.0f && fPlayerVec[1 + (4 * nCntItem)] > 0.0f && fPlayerVec[2 + (4 * nCntItem)] > 0.0f && fPlayerVec[3 + (4 * nCntItem)] > 0.0f)
					{
						if (item[nCntItem].bUse == true)
						{
							//�A�C�e��������
							item[nCntItem].bUse = false;

							//�X�R�A���Z
							AddScore(1);

							//�N���A����
							nItemScoe++;
						}
					}
				}

				//���̃I�u�W�F�N�g�̓����蔻��
				if (nCnt == 3 + (4 * nCntItem))
				{
					//������ς���
					g_nCnyDateItem += 4;

					//���̃I�u�W�F�N�g��
					nCntItem += 1;
				}
			}
		}
	}

	return bLand;
}

//==============================================================================
// �I�u�W�F�N�g�̐ݒ�
//==============================================================================
void SetItem(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, int nType)
{
	//VERTEX_3D *pVtx;
	//LPDIRECT3DDEVICE9 pDevice;

	////�f�o�C�X�̎擾
	//pDevice = GetDevice();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{

		// ���_�o�b�t�@�����b�N
		g_pMeshItem[0]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&item[nCntItem].pVtxBuff);

		//�g�p����Ă���Ƃ�
		if (item[nCntItem].bUse == false)
		{
			//�ʒu
			item[nCntItem].pos = Pos;

			//����
			item[nCntItem].rot = rot;

			//�^�C�v
			item[nCntItem].nType = nType;

			//�g�p����
			item[nCntItem].bUse = true;

			//��O�̃I�u�W�F�N�g���L��
			g_nDateItemNumberItem = nCntItem;

			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pMeshItem[0]->UnlockVertexBuffer();
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
int GetitemNumber(void)
{
	return MaxItem;
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
int GetitemDate(void)
{
	return g_nDateItemNumberItem2;
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
int GetitemType(void)
{
	return MaxItemType;
}