//==============================================================================
//
// ���b�V���t�B�[���h�̕`��kmeshfield.cpp�l
// AUTHOR : TAKAHASHI SHOTA
//
//==============================================================================
#include "meshfield.h"
#include "model.h"
#include "car.h"
#include "input.h"
#include "score.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define WIDTHNUM	(100)									// ��(��)
#define DEPTHNUM	(100)									// �s��(���s)
#define WIDTH		(100.0f)								// ���̑傫��
#define DEPTH		(100.0f)								// ���s�̑傫��
//#define DATE_CAR	(g_CarDate)								// �v���C���[�̏������Ƃ�


//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	// �o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;		// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posMeshfield;							// �ʒu
D3DXVECTOR3 g_rotMeshfield;							// ����
D3DXMATRIX g_mtxWorldMeshfield;						// ���[���h�}�g���b�N�X
MeshField g_aField[FIELD_MAX];						//�t�B�[���h�̏��
int g_nAllPoint;									// �����_��
int g_nPolygon;										// �|���S����
int g_nIdxPoint;									// �C���f�b�N�X�o�b�t�@�̕K�v�Ȋm�ې�
float g_fWidth = WIDTH;								// �����̒[
float g_fDepth = DEPTH;								// ���s�̒[
int g_nWidth = WIDTHNUM + 1;						// �����̒��_��
int g_nDepth = DEPTHNUM + 1;						// ���s�̒��_��
//float g_SpeedCarDate;
//float g_CarDate;
									
//==============================================================================
// ����������
//==============================================================================
HRESULT InitMeshfield(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	WORD *pIdx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,"data/TEXTURE/field2.jpg",&g_pTextureMeshfield);

	// �ϐ��̏�����
	g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	g_nAllPoint = DEPTHNUM * 2 * (WIDTHNUM + 2) - 2;				// �����_��
	g_nPolygon = WIDTHNUM * DEPTHNUM * 2 + (4 * (DEPTHNUM - 1));	// ���|���S����
	g_nIdxPoint = g_nWidth * g_nDepth;								// �C���f�b�N�X�o�b�t�@�ł̒��_��

	for (int nCnt = 0; nCnt < FIELD_MAX; nCnt++)
	{
		g_aField[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCnt].g_rotMeshfield = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		g_aField[nCnt].g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCnt].nAllPoint = 0;
		g_aField[nCnt].nPolygon = 0;
		g_aField[nCnt].nIdxPoint = 0;
		g_aField[nCnt].bUse = false;
	}

	float fWidthMax = g_fWidth * (float)WIDTHNUM;
	float fDepthMax = g_fDepth * (float)DEPTHNUM;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * g_nIdxPoint,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < g_nDepth; nCnt++)
	{// ���s��
		for (int nCntA = 0; nCntA < g_nWidth; nCntA++ )
		{

			// ����
			// �|���S���̊e���_���W
			pVtx[0].pos = D3DXVECTOR3(-fWidthMax / 2.0f + (float)nCntA * g_fWidth, g_posMeshfield.y, fDepthMax / 2.0f - (float)nCnt * g_fDepth);

			//pVtx[0].pos = D3DXVECTOR3(g_aField[nCntA].g_posMeshfield.x + (float)nCntA * g_fWidth, g_posMeshfield.y, g_aField[nCntA].g_posMeshfield.z - (float)nCnt * g_fDepth);
			
			// �@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// �e���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCntA, 1.0f * nCnt);

			pVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshfield->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * g_nAllPoint,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield,
		NULL);

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntA = 0; nCntA < DEPTHNUM; nCntA++)
	{
		for (int nCnt = 0; nCnt < g_nWidth + 1; nCnt++, pIdx += 2)
		{
			if (nCnt != 0 && nCnt == g_nWidth && nCntA != DEPTHNUM - 1)
			{// �E�[����܂�Ԃ���
				pIdx[0] = pIdx[-1];
				pIdx[1] = pIdx[-2] + 1;
			}
			else if (nCntA == DEPTHNUM - 1 && nCnt == g_nWidth)
			{// �I�����ɖ�������
				break;
			}
			else
			{// �ʏ�z�u
				pIdx[0] = g_nWidth + (g_nWidth * nCntA) + nCnt;
				pIdx[1] = pIdx[0] - g_nWidth;
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshfield->Unlock();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitMeshfield(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateMeshfield(void)
{
	//CAR  *pCar;
	//pCar = GetCar();

	//g_SpeedCarDate = GetCarSpeed();

	//if (g_SpeedCarDate >= 0.2f)
	//{
	//	g_CarDate = 0.8f;
	//	AddScore(1);
	//}

	//if (g_SpeedCarDate >= 0.4f)
	//{
	//	g_CarDate = 1.5f;
	//	AddScore(2);
	//}

	//if (g_SpeedCarDate >= 0.6f)
	//{
	//	g_CarDate = 2.2f;
	//	AddScore(3);
	//}

	//if (g_SpeedCarDate >= 0.8f)
	//{
	//	g_CarDate = 2.9f;
	//	AddScore(4);
	//}

	//if (g_SpeedCarDate >= 1.0f)
	//{
	//	g_CarDate = 3.6f;
	//	AddScore(5);
	//}
}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawMeshfield(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	MeshField *pField;
	pField = &g_aField[0];

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < FIELD_MAX; nCnt++, pField++)
	{
		if (pField->bUse == true)
		{

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldMeshfield);

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pField->g_rotMeshfield.y, pField->g_rotMeshfield.x, pField->g_rotMeshfield.z);
			D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pField->g_posMeshfield.x, pField->g_posMeshfield.y, pField->g_posMeshfield.z);
			D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshfield);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshfield);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				0,
				0,
				g_nIdxPoint,			// ���_��
				0,
				g_nPolygon);			// �v���~�e�B�u��
		}
	}
}

MeshField * GetMesh(void)
{
	return &g_aField[0];
}

//==============================================================================
// �t�B�[���h�̐ݒ�
//==============================================================================
void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float X, float Z)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;

	MeshField *pField;
	pField = &g_aField[0];

	// �t�B�[���h�̐ݒ�
	for (int nCnt = 0; nCnt < FIELD_MAX; nCnt++, pField++)
	{
		if (pField->bUse == false)
		{
			//����
			pField->g_rotMeshfield = rot;
			
			//�ʒu
			pField->g_posMeshfield = pos;

			//if (pField->g_rotMeshfield.y == 0.0f && pField->g_rotMeshfield.z == 0.2f)
			//{
			//	pField->nType = 1;
			//}

			//if (pField->g_rotMeshfield.y == D3DX_PI)
			//{
			//	pField->nType = 2;
			//}

			//if (pField->g_rotMeshfield.y == D3DX_PI / 2)
			//{
			//	pField->nType = 3;
			//}

			//if (pField->g_rotMeshfield.y == -D3DX_PI / 2)
			//{
			//	pField->nType = 4;
			//}

			pField->posM = pos;

			//�g�p���Ă����邩
			pField->bUse = true;

			break;
		}
	}
}

//==============================================================================
// �t�B�[���h�̓����蔻��
//==============================================================================
void CollisionVecMesh(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
{
	//// ���[�J���ϐ��錾
	//VERTEX_3D *pVtx;

	//// ����Ώۂ̈ʒu
	//D3DXVECTOR3 pos = *pPos;
	//D3DXVECTOR3 posOld = *pPosOld;

	//MeshField *pField;
	//pField = &g_aField[0];

	//PLAYER *pModel;
	//pModel = GetModel();

	//CAR  *pCar;
	//pCar = GetCar();

	//// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//if (pField->bUse == true)
	//{
	//	for (int nCnt = 0; nCnt < FIELD_MAX; nCnt++, pField++)
	//	{
	//		if (pField->nType == 0)
	//		{
	//			//�����蔻��@����
	//			if (pField->posM.x <= pos.x && (pField->posM.x + 1000.0f) >= pos.x &&
	//				pField->posM.z >= pos.z && (pField->posM.z - 400.0f) <= pos.z&&
	//				pField->posM.y + 10 >= pos.y && (pField->posM.y - 10.0f) <= pos.y)
	//			{
	//				//������̎��̏����@����
	//				pModel->pos.y = pModel->posOld.y;
	//				pCar->pos.y = pCar->posOld.y;
	//				pos.y = posOld.y;
	//				break;
	//			}

	//			//�d��
	//			else
	//			{
	//				pModel->pos.y -= 0.1f;
	//				pCar->pos.y -= 0.1f;
	//				pos.y -= 0.1f;
	//				//break;
	//			}
	//		}

	//		if (pField->nType == 1)
	//		{
	//			//�����蔻��
	//			if (pField->posM.x <= pos.x && (pField->posM.x + 1000.0f) >= pos.x &&
	//				pField->posM.z >= pos.z && (pField->posM.z - 400.0f) <= pos.z)
	//			{
	//				//�d��
	//				//pModel->move.y += 0.0f;

	//				//�x�N�g���̌v�Z�ۑ�
	//				pField->vec = D3DXVECTOR3(pField->posM.x + 1000.0f, pField->posM.y + 200.0f, pField->posM.z);
	//				pField->vecA = pField->vec - pField->posM;
	//				pField->vecB = pos - pField->posM;

	//				//�x�N�g���̌v�Z�ۑ�
	//				pField->vec2 = D3DXVECTOR3(pField->posM.x + 1000.0f, pField->posM.y + 210.0f, pField->posM.z);
	//				pField->vec3 = D3DXVECTOR3(pField->posM.x, pField->posM.y + 10.0f, pField->posM.z);
	//				pField->vec2A = pField->vec2 - pField->vec3;
	//				pField->vec2B = pos - pField->vec3;

	//				//�����蔻��
	//				if (((pField->vec2A.x * pField->vec2B.y) - (pField->vec2A.y * pField->vec2B.x)) < 0)
	//				{
	//					//�����蔻��
	//					if (((pField->vecA.x * pField->vecB.y) - (pField->vecA.y * pField->vecB.x)) < 0)
	//					{
	//						//0�ȉ��ɂȂ����畂��
	//						pModel->pos.y = pModel->posOld.y + 0.8f;
	//						pCar->pos.y = pCar->posOld.y + DATE_CAR;
	//						//pos.y = posOld.y + 0.8f;
	//						break;
	//					}


	//					else
	//					{

	//						//0�ȏ�ɂȂ����牺�~
	//						pModel->pos.y = pModel->posOld.y - 0.8f;
	//						pCar->pos.y = pCar->posOld.y - DATE_CAR;
	//						//pos.y = posOld.y - 0.8f;
	//						break;
	//					}

	//				}
	//			}

	//			//�d��
	//			else
	//			{
	//				pModel->pos.y -= 1.0f;
	//				pCar->pos.y -= 1.0f;
	//				//pos.y -= 1.0f;
	//			}
	//		}

	//		//�����ɂ����
	//		if (pField->nType == 2)
	//		{

	//			if (pField->posM.x - 1000.0f <= pos.x && pField->posM.x >= pos.x &&
	//				pField->posM.z + 400.0f >= pos.z && pField->posM.z <= pos.z)
	//			{
	//				//�x�N�g���̌v�Z�ۑ�
	//				pField->vec = D3DXVECTOR3(pField->posM.x - 1000.0f, pField->posM.y + 200.0f, pField->posM.z);
	//				pField->vecA = pField->posM - pField->vec;
	//				pField->vecB = pos - pField->vec;

	//				//�x�N�g���̌v�Z�ۑ�
	//				pField->vec2 = D3DXVECTOR3(pField->posM.x, pField->posM.y + 10.0f, pField->posM.z);
	//				pField->vec3 = D3DXVECTOR3(pField->posM.x - 1000.0f, pField->posM.y + 210.0f, pField->posM.z);
	//				pField->vec2A = pField->vec2 - pField->vec3;
	//				pField->vec2B = pos - pField->vec3;

	//				//�����蔻��
	//				if (((pField->vec2A.x * pField->vec2B.y) - (pField->vec2A.y * pField->vec2B.x)) < 0)
	//				{
	//					//�����蔻��
	//					if (((pField->vecA.x * pField->vecB.y) - (pField->vecA.y * pField->vecB.x)) < 0)
	//					{
	//						//0�ȉ��ɂȂ����畂��
	//						pModel->pos.y = pModel->posOld.y + 0.8f;
	//						pCar->pos.y = pCar->posOld.y + DATE_CAR;
	//						//pCar->pos.y = pCar->posOld.y;
	//						//pos.y = posOld.y + 0.8f;
	//						break;
	//					}

	//					else
	//					{
	//						//0�ȏ�ɂȂ����牺�~
	//						pModel->pos.y = pModel->posOld.y - 0.8f;
	//						pCar->pos.y = pCar->posOld.y - DATE_CAR;
	//						//pos.y = posOld.y - 0.8f;
	//						break;
	//					}
	//				}
	//			}
	//		}

	//		//�����ɂ����
	//		if (pField->nType == 3)
	//		{

	//			if (pField->posM.x - 400.0f <= pos.x && pField->posM.x >= pos.x &&
	//				pField->posM.z >= pos.z && pField->posM.z - 1000.0f <= pos.z)
	//			{
	//				//�x�N�g���̌v�Z�ۑ�
	//				pField->vec = D3DXVECTOR3(pField->posM.x, pField->posM.y + 200.0f, pField->posM.z - 1000.0f);
	//				pField->vecA = pField->posM - pField->vec;
	//				pField->vecB = pos - pField->vec;

	//				////�x�N�g���̌v�Z�ۑ�
	//				pField->vec2 = D3DXVECTOR3(pField->posM.x, pField->posM.y + 10.0f, pField->posM.z);
	//				pField->vec3 = D3DXVECTOR3(pField->posM.x, pField->posM.y + 210.0f, pField->posM.z - 1000.0f);
	//				pField->vec2A = pField->vec2 - pField->vec3;
	//				pField->vec2B = pos - pField->vec3;

	//				//�����蔻��
	//				if (((pField->vec2A.z * pField->vec2B.y) - (pField->vec2A.y * pField->vec2B.z)) < 0)
	//				{
	//					//�����蔻��
	//					if (((pField->vecA.z * pField->vecB.y) - (pField->vecA.y * pField->vecB.z)) < 0)
	//					{
	//						//0�ȉ��ɂȂ����畂��
	//						pModel->pos.y = pModel->posOld.y + 0.8f;
	//						pCar->pos.y = pCar->posOld.y + DATE_CAR;
	//						//pos.y = posOld.y + 0.8f;
	//						break;
	//					}

	//					else
	//					{
	//						//0�ȏ�ɂȂ����牺�~
	//						pModel->pos.y = pModel->posOld.y - 0.8f;
	//						pCar->pos.y = pCar->posOld.y - DATE_CAR;
	//						//pos.y = posOld.y - 0.8f;
	//						break;
	//					}
	//				}
	//			}
	//		}

	//		//�����ɂ����
	//		if (pField->nType == 4)
	//		{

	//			if (pField->posM.x <= pos.x && pField->posM.x + 400.0f >= pos.x &&
	//				pField->posM.z + 1000.0f >= pos.z && pField->posM.z <= pos.z)
	//			{
	//				//�x�N�g���̌v�Z�ۑ�
	//				pField->vec = D3DXVECTOR3(pField->posM.x, pField->posM.y + 200.0f, pField->posM.z + 1000.0f);
	//				pField->vecA = pField->vec - pField->posM;
	//				pField->vecB = pos - pField->posM;

	//				////�x�N�g���̌v�Z�ۑ�
	//				pField->vec2 = D3DXVECTOR3(pField->posM.x, pField->posM.y + 10.0f, pField->posM.z);
	//				pField->vec3 = D3DXVECTOR3(pField->posM.x, pField->posM.y + 210.0f, pField->posM.z + 1000.0f);
	//				pField->vec2A = pField->vec3 - pField->vec2;
	//				pField->vec2B = pos - pField->vec2;

	//				//�����蔻��
	//				if (((pField->vec2A.z * pField->vec2B.y) - (pField->vec2A.y * pField->vec2B.z)) < 0)
	//				{
	//					//�����蔻��
	//					if (((pField->vecA.z * pField->vecB.y) - (pField->vecA.y * pField->vecB.z)) < 0)
	//					{
	//						//0�ȉ��ɂȂ����畂��
	//						pModel->pos.y = pModel->posOld.y + 0.8f;
	//						pCar->pos.y = pCar->posOld.y + DATE_CAR;
	//						//pos.y = posOld.y + 0.8f;
	//						break;
	//					}

	//					else
	//					{
	//						//0�ȏ�ɂȂ����牺�~
	//						pModel->pos.y = pModel->posOld.y - 0.8f;
	//						pCar->pos.y = pCar->posOld.y - DATE_CAR;
	//						//pos.y = posOld.y - 0.8f;
	//						break;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	//// ���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffMeshfield->Unlock();
}