//-----------------------------------------------------------------
//
// �v���C���[�̏��� (model.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "car.h"
#include"camera.h"
#include "shadow.h"
#include "input.h"
#include "bullet.h"
#include "effect.h"
#include "object.h"
#include "gear.h"
#include "meshfield.h"
#include "gamepad.h"
#include "item.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define CAR_X			(50)									// ���S����[�܂ł܂ł̒���(x)
#define CAR_Y			(50)
#define CAR_MOVE		(0.3f + g_Car.nSpeed)
#define CAR_MOVE_BACK	(0.2f)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPD3DXMESH g_pMeshCar = NULL;	//���_���
LPD3DXBUFFER g_pBuffMetCar = NULL;
LPDIRECT3DTEXTURE9 g_pTextureCar[5] = {};			//�e�N�X�`��
DWORD  g_nNumMatCar = 0;							//�}�e���A���̐�
CAR g_Car;
D3DXMATRIX g_mtxWorldCar;							//���[���h�}�g���b�N�X
float g_carrot;
float g_SpeedCar = 0;

//-----------------------------------------------------------------------------
// �|���S���̏���������
//-----------------------------------------------------------------------------
HRESULT InitCar(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Car.MinCar = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);

	g_Car.MaxCar = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

	//model�ǂݍ���
	D3DXLoadMeshFromX("data/model/car004.x",D3DXMESH_SYSTEMMEM,pDevice,NULL,&g_pBuffMetCar,NULL,&g_nNumMatCar,&g_pMeshCar);
	//D3DXLoadMeshFromX("data/model/��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetCar, NULL, &g_nNumMatCar, &g_pMeshCar);
	//D3DXLoadMeshFromX("data/model/�W��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetCar, NULL, &g_nNumMatCar, &g_pMeshCar);

	int nNumVtx;			//���_��
	DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^ 

	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

	//���_�����擾
	nNumVtx = g_pMeshCar->GetNumVertices();

	//�}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)g_pBuffMetCar->GetBufferPointer();


	for (int nCntMat = 0; nCntMat < (int)g_nNumMatCar; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���ǂݍ���
			//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/50.png", &g_pTextureCar[0]);
		}
	}

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshCar->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshCar->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (g_Car.MinCar.x > vtx.x)
		{
			g_Car.MinCar.x = vtx.x;
		}

		if (g_Car.MaxCar.x < vtx.x)
		{
			g_Car.MaxCar.x = vtx.x;
		}

		if (g_Car.MinCar.y > vtx.y)
		{
			g_Car.MinCar.y = vtx.y;
		}

		if (g_Car.MaxCar.y < vtx.y)
		{
			g_Car.MaxCar.y = vtx.y;
		}

		if (g_Car.MinCar.z > vtx.z)
		{
			g_Car.MinCar.z = vtx.z;
		}

		if (g_Car.MaxCar.z < vtx.z)
		{
			g_Car.MaxCar.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y����i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pMeshCar->UnlockVertexBuffer();

	//�ʒu
	g_Car.pos = D3DXVECTOR3(0.0f, 0.0f, -600.0f);

	//����
	g_Car.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//-----------------------------------------------------------------------------
// �|���S���̏I������
//-----------------------------------------------------------------------------
void UninitCar(void)
{
	//�}�e���A���̊J��
	if (g_pBuffMetCar != NULL)
	{
		g_pBuffMetCar->Release();
		g_pBuffMetCar = NULL;
	}

	//���b�V���̊J��
	if (g_pMeshCar != NULL)
	{
		g_pMeshCar->Release();
		g_pMeshCar = NULL;
	}
}

//-----------------------------------------------------------------------------
// �|���S���̍X�V����
//-----------------------------------------------------------------------------
void UpdateCar(void)
{
	CAMERA  *pCamera;
	pCamera = GetCamera();

	EFFECT *pEffect;
	pEffect = GetEffect();

	//��ɏ����
	//g_Car.rotDest.y = pCamera->rot.y - D3DX_PI / 2;
	g_Car.rotDest.y = pCamera->rot.y;

	//�ړ��p�b�h
	if (IsButtonPush(KEYINFO_A))
	{
		g_Car.move.x += sinf(pCamera->rot.y) * CAR_MOVE;
		g_Car.move.z += cosf(pCamera->rot.y) * CAR_MOVE;

		//���̃G�t�F�N�g
		SetFire(D3DXVECTOR3(g_Car.pos.x, g_Car.pos.y, g_Car.pos.z));
	}

	////�ړ��L�[�{�[�h
	//if (GetKeyboardPress(DIK_SPACE) == true)
	//{
	//	g_Car.move.x += sinf(pCamera->rot.y) * CAR_MOVE;
	//	g_Car.move.z += cosf(pCamera->rot.y) * CAR_MOVE;
	//}

	//�o�b�N�p�b�h
	if (IsButtonPush(KEYINFO_B))
	{
		g_Car.move.x -= sinf(pCamera->rot.y) * CAR_MOVE_BACK;
		g_Car.move.z -= cosf(pCamera->rot.y) * CAR_MOVE_BACK;
	}

	////�o�b�N�L�[�{�[�h
	//if (GetKeyboardPress(DIK_M) == true)
	//{
	//	g_Car.move.x -= sinf(pCamera->rot.y) * CAR_MOVE_BACK;
	//	g_Car.move.z -= cosf(pCamera->rot.y) * CAR_MOVE_BACK;
	//}

	//// ���f���̈ړ�
	//if (GetKeyboardPress(DIK_W) == true)
	//{
	//	if (GetKeyboardPress(DIK_A) == true)
	//	{// �������
	//		g_Car.move.x -= cosf(pCamera->Camera + D3DX_PI / 4) * CAR_MOVE;
	//		g_Car.move.z += sinf(pCamera->Camera + D3DX_PI / 4) * CAR_MOVE;
	//		g_Car.rotDest.y = pCamera->Camera + (D3DX_PI * 3 / 4);
	//	}
	//	else if (GetKeyboardPress(DIK_D) == true)
	//	{// �E�����
	//		g_Car.move.x += cosf(pCamera->Camera - D3DX_PI / 4) * CAR_MOVE;
	//		g_Car.move.z -= sinf(pCamera->Camera - D3DX_PI / 4) * CAR_MOVE;
	//		g_Car.rotDest.y = pCamera->Camera - (D3DX_PI * 3 / 4);
	//	}
	//	else
	//	{// �����
	//		g_Car.move.x += sinf(pCamera->Camera) * CAR_MOVE;
	//		g_Car.move.z += cosf(pCamera->Camera) * CAR_MOVE;
	//		g_Car.rotDest.y = pCamera->Camera + D3DX_PI;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_S) == true)
	//{
	//	if (GetKeyboardPress(DIK_D) == true)
	//	{// �E�����
	//		g_Car.move.x += cosf(pCamera->Camera + D3DX_PI / 4) * CAR_MOVE;
	//		g_Car.move.z -= sinf(pCamera->Camera + D3DX_PI / 4) * CAR_MOVE;
	//		g_Car.rotDest.y = pCamera->Camera + D3DX_PI / -4;
	//	}
	//	else if (GetKeyboardPress(DIK_A) == true)
	//	{// �������
	//		g_Car.move.x -= cosf(pCamera->Camera - D3DX_PI / 4) * CAR_MOVE;
	//		g_Car.move.z += sinf(pCamera->Camera - D3DX_PI / 4) * CAR_MOVE;
	//		g_Car.rotDest.y = pCamera->Camera + D3DX_PI / 4;
	//	}
	//	else
	//	{// ������
	//		g_Car.move.x += sinf(pCamera->Camera - D3DX_PI) * CAR_MOVE;
	//		g_Car.move.z += cosf(pCamera->Camera - D3DX_PI) * CAR_MOVE;
	//		g_Car.rotDest.y = pCamera->Camera;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_A) == true)
	//{// ������
	//	g_Car.move.x -= cosf(pCamera->Camera) * CAR_MOVE;
	//	g_Car.move.z += sinf(pCamera->Camera) * CAR_MOVE;
	//	g_Car.rotDest.y = pCamera->Camera + (D3DX_PI / 2);
	//}
	//else if (GetKeyboardPress(DIK_D) == true)
	//{// �E����
	//	g_Car.move.x += cosf(pCamera->Camera) * CAR_MOVE;
	//	g_Car.move.z -= sinf(pCamera->Camera) * CAR_MOVE;
	//	g_Car.rotDest.y = pCamera->Camera + (D3DX_PI / -2);
	//}

	//�M�A�`�F���W
	if (IsButtonDown(KEYINFO_R1))
	{
		g_Car.nSpeed += 0.3f;
	}

	if (IsButtonDown(KEYINFO_L1))
	{
		g_Car.nSpeed -= 0.3f;
	}

	//�M�A���
	if (g_Car.nSpeed >= 1.5f)
	{
		g_Car.nSpeed = 1.5f;
	}

	if (g_Car.nSpeed <= 0.0f)
	{
		g_Car.nSpeed = 0.0f;
	}

	//�M�A�̕\��
	if (g_Car.nSpeed >= 0.0f)
	{
		AddGear(1);
	}

	if (g_Car.nSpeed >= 0.3f)
	{
		AddGear(2);
	}

	if (g_Car.nSpeed >= 0.6f)
	{
		AddGear(3);
	}

	if (g_Car.nSpeed >= 0.9f)
	{
		AddGear(4);
	}

	if (g_Car.nSpeed >= 1.2f)
	{
		AddGear(5);
	}

	if (g_Car.nSpeed >= 1.5f)
	{
		AddGear(6);
	}

	if (IsButtonUp(KEYINFO_A))
	{
		AddGear(1);
		g_Car.nSpeed = 0.0f;
	}


	////�㏸
	//if (GetKeyboardPress(DIK_W) == true)
	//{
	//	g_Car.pos.y += 0.5f;
	//}

	////���~
	//if (GetKeyboardPress(DIK_S) == true)
	//{
	//	g_Car.pos.y -= 0.5f;
	//}

	////���f������]
	//if (GetKeyboardPress(DIK_M) == true)
	//{
	//	g_carrot -= 0.1f;
	//	g_Car.rot = D3DXVECTOR3(0.0f, g_carrot, 0.0f);
	//}

	////���f���E��]
	//if (GetKeyboardPress(DIK_N) == true)
	//{
	//	g_carrot += 0.1f;
	//	g_Car.rot = D3DXVECTOR3(0.0f, g_carrot, 0.0f);
	//}

	////��]���Z�b�g
	//if (g_Car.rot.y < -D3DX_PI)
	//{
	//	g_Car.rot.y += D3DX_PI * 2.0f;
	//}

	//if (g_Car.rot.y > D3DX_PI)
	//{
	//	g_Car.rot.y -= D3DX_PI * 2.0f;
	//}

	//�e�̔���
	//if (GetKeyboardTrigger(DIK_SPACE) == true)
	//{
	//	//SetBullet(D3DXVECTOR3(g_Car.pos.x, g_Car.pos.y + 10, g_Car.pos.z), D3DXVECTOR3(sinf(g_Car.rot.y), 0.0f, cosf(g_Car.rot.y)), 5, 500);

	//}

	//// �ړI�̉�]�p�̏��
	//if (g_Car.rotDest.y - g_Car.rot.y < -D3DX_PI)
	//{
	//	g_Car.rotDest.y += D3DX_PI * 2.0f;
	//}
	//else if (g_Car.rotDest.y - g_Car.rot.y > D3DX_PI)
	//{
	//	g_Car.rotDest.y -= D3DX_PI * 2.0f;
	//}

	// �����̍X�V
	g_Car.rot.y += (g_Car.rotDest.y - g_Car.rot.y) * 0.1f;

	//�ړ��ʂ̌���
	g_Car.move.x -= (0 + g_Car.move.x) * 0.05f;
	g_Car.move.y -= (0 + g_Car.move.y) * 0.05f;
	g_Car.move.z -= (0 + g_Car.move.z) * 0.05f;

	//�ړ��ʂ̌���
	g_Car.rotmove.x -= (0 + g_Car.rotmove.x) * 0.2f;
	g_Car.rotmove.y -= (0 + g_Car.rotmove.y) * 0.2f;
	g_Car.rotmove.z -= (0 + g_Car.rotmove.z) * 0.2f;

	//�ʒu�X�V
	g_Car.pos.x += g_Car.move.x;
	g_Car.pos.y += g_Car.move.y;
	g_Car.pos.z += g_Car.move.z;

	//�ʒu�X�V
	g_Car.rot.x += g_Car.rotmove.x;
	g_Car.rot.y += g_Car.rotmove.y;
	g_Car.rot.z += g_Car.rotmove.z;

	//�e�̈ʒu�X�V
	SetPositionShadow(0, D3DXVECTOR3(g_Car.pos.x, 0.0f, g_Car.pos.z));

	//if (GetKeyboardPress(DIK_SPACE) == false)
	{
		//g_Car.pos.y -= 1.0f;
	}


	//�I�u�W�F�N�g�̓����蔻��
	CollisionVec(&g_Car.pos, &g_Car.posOld, &g_Car.move, g_Car.MaxCar.x, g_Car.MinCar.x, g_Car.MaxCar.z, g_Car.MinCar.z, g_Car.MaxCar.y, g_Car.MinCar.y);

	//�I�u�W�F�N�g�̓����蔻��
	CollisionVecItem(&g_Car.pos, &g_Car.posOld, &g_Car.move, g_Car.MaxCar.x, g_Car.MinCar.x, g_Car.MaxCar.z, g_Car.MinCar.z, g_Car.MaxCar.y, g_Car.MinCar.y);

	//�t�B�[���h�̓����蔻��
	//CollisionVecMesh(&g_Car.pos, &g_Car.posOld, &g_Car.move, g_Car.MaxCar.x, g_Car.MinCar.x, g_Car.MaxCar.z, g_Car.MinCar.z, g_Car.MaxCar.y, g_Car.MinCar.y);
}

//-----------------------------------------------------------------------------
// �|���S���̕`�揈��
//-----------------------------------------------------------------------------
void DrawCar(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ�
	D3DXMATERIAL *pMat;				//�}�e���A���ւ̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldCar);

	//�����̔��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Car.rot.y, g_Car.rot.x, g_Car.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldCar, &g_mtxWorldCar, &mtxRot);

	//�ʒu�̔��]
	D3DXMatrixTranslation(&mtxTrans, g_Car.pos.x, g_Car.pos.y, g_Car.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldCar, &g_mtxWorldCar, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldCar);

	//���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)g_pBuffMetCar->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatCar; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		//pDevice->SetTexture(0, g_pTextureCar[nCntMat]);

		//���f���p�[�c�̕`��
		g_pMeshCar->DrawSubset(nCntMat);
	}

	//�ۑ������}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
CAR *GetCar(void)
{
	return &g_Car;
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
float GetCarSpeed(void)
{
	return g_SpeedCar;
}