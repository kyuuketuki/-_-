//==============================================================================
//
// �J�����̐ݒ�kcamera.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "camera.h"
#include "model.h"
#include "car.h"
#include "input.h"
#include "game.h"
#include "gamepad.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define CAMERA_MOVE				(2.0f)							// �J�����̈ړ���
#define CAMERA_TURN				(D3DX_PI / 100.0f)				// �J�����̐��񑬓x
#define CAMERA_RANGE_CAR		(150.0f)						// ���_�E�����_�Ԃ̋���
#define CAMERA_RANGE_MODEL		(300.0f)						// ���_�E�����_�Ԃ̋���
#define CAMERA_HEIGHT			(500.0f)						// �J����(���_)�̍���
#define CAMERA_SPDOWN			(0.5f)							// �����W�� 

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
CAMERA g_camera;
float nHeight = 0;

//==============================================================================
// ����������
//==============================================================================
void InitCamera(void)
{
	// ���[�J���ϐ��錾
	PLAYER *player;
	player = GetModel();

	CAR  *pCar;
	pCar = GetCar();

	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �����_�ʒu
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// ������x�N�g��
	g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ���
	g_camera.rot = D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f);		// �J�����̊p�x
	g_camera.fLength = CAMERA_RANGE_CAR;						// ���_�E�����_�Ԃ̋���
	g_camera.fHeightV = -60.0f;									// ���_�̍���
	g_camera.fHeightR = player->pos.y + 50.0f;					// �����_�̍���
	g_camera.fFront = 15.0f;									// ���f���̑O���̋���
	g_camera.bAutoTurn = false;									// �J�����̉�荞��ON�EOFF
	g_camera.viewport.X = 0;									//�`�悷���ʂ̍���X���W
	g_camera.viewport.Y = 0;									//�`�悷���ʂ̍���Y���W
	g_camera.viewport.Width = 860.0f;							//��
	g_camera.viewport.Height = SCREEN_HEIGHT;					//��
	g_camera.viewport.MinZ = 0.0f;								//�Œ�
	g_camera.viewport.MaxZ = 1.0f;								//�Œ�
}

//==============================================================================
// �I������
//==============================================================================
void UninitCamera(void)
{

}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateCamera(void)
{
	// �����_�Ƃ̋���
	//g_camera.fLength = sqrtf(
	//	(g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y) + 
	//	(g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z));

	// ���[�J���ϐ��錾
	PLAYER *player;
	player = GetModel();

	CAR  *pCar;
	pCar = GetCar();

	pCar->posOld = pCar->pos;

	// ���Z�b�g
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �J�����̊p�x
	}

	//���_�E�����_�̈ړ�
	//if (GetKeyboardPress(KEYINFO_UP) == true)
	//{
	//	g_camera.move.x += sinf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.move.z += cosf(g_camera.rot.y) * CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(KEYINFO_DOWN) == true)
	//{
	//	g_camera.move.x -= sinf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.move.z -= cosf(g_camera.rot.y) * CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(KEYINFO_LEFT) == true)
	//{
	//	g_camera.move.x -= cosf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.move.z += sinf(g_camera.rot.y) * CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	//{
	//	g_camera.move.x += cosf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.move.z -= sinf(g_camera.rot.y) * CAMERA_MOVE;
	//}

	//�����_�̈ړ�(���E)
	//if (GetKeyboardPress(KEYINFO_LEFT_CENTER) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

	//	if (g_camera.rot.y < -D3DX_PI)
	//	{
	//		g_camera.rot.y += D3DX_PI * 2.0f;
	//	}
	//}
	//if (GetKeyboardPress(KEYINFO_RIGHT_CENTER) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / CAMERA_TURN;

	//	if (g_camera.rot.y > D3DX_PI)
	//	{
	//		g_camera.rot.y -= D3DX_PI * 2.0f;
	//	}
	//}

	//// �����_�̈ړ�(�㉺)(T,B�L�[)
	//if (GetKeyboardPress(DIK_T) == true)
	//{
	//	g_camera.fHeightR += CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(DIK_B) == true)
	//{
	//	g_camera.fHeightR -= CAMERA_MOVE;
	//}

	if (GetGame() == 1)
	{
		g_camera.fHeightV = 500.0f + nHeight;				// ���_�̍���
		g_camera.fLength = CAMERA_RANGE_MODEL;				//���_�̋���
		
		//��������
		if (GetKeyboardPress(DIK_8) == true)
		{
			nHeight += 10.0f;
		}

		if (GetKeyboardPress(DIK_9) == true)
		{
			nHeight -= 10.0f;
		}

		if (GetKeyboardPress(DIK_C) == true)
		{
			g_camera.rot.y += CAMERA_TURN;

			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2.0f;
			}

			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
		}
		if (GetKeyboardPress(DIK_Z) == true)
		{
			g_camera.rot.y -= CAMERA_TURN;

			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2.0f;
			}

			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
		}

		// �ړI�̒����_
		g_camera.posRDest.x = player->pos.x - g_camera.fFront * sinf(player->rotDest.y);
		g_camera.posRDest.z = player->pos.z - g_camera.fFront * cosf(player->rotDest.y);
		g_camera.posRDest.y = player->pos.y + g_camera.fHeightR;

		// �ړI�̎��_
		g_camera.posVDest.x = player->pos.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posVDest.z = player->pos.z - cosf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posVDest.y = player->pos.y + cosf(g_camera.rot.x) * g_camera.fLength + g_camera.fHeightV;

	}

	//�Ԃ̎�
	if (GetGame() == 0)
	{
		g_camera.fHeightV = -60.0f;							// ���_�̍���
		g_camera.fHeightR = player->pos.y + 50.0f;			// �����_�̍���
		g_camera.fLength = CAMERA_RANGE_CAR;				// ���_�̋���

		//���_�̈ړ�(���E)(Z,C�L�[)
		if (IsButtonPush(KEYINFO_A))
		{
			if (IsButtonPush(KEYINFO_RIGHT))
			{
				g_camera.rot.y += CAMERA_TURN;

				/*if (g_camera.rot.y > D3DX_PI)
				{
					g_camera.rot.y -= D3DX_PI * 2.0f;
				}*/

				g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
				g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
			}
			if (IsButtonPush(KEYINFO_LEFT))
			{
				g_camera.rot.y -= CAMERA_TURN;

				/*if (g_camera.rot.y < -D3DX_PI)
				{
					g_camera.rot.y += D3DX_PI * 2.0f;
				}*/

				g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
				g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
			}
		}

		if (IsButtonPush(KEYINFO_B))
		{
			if (IsButtonPush(KEYINFO_LEFT))
			{
				g_camera.rot.y += CAMERA_TURN;

				/*if (g_camera.rot.y > D3DX_PI)
				{
					g_camera.rot.y -= D3DX_PI * 2.0f;
				}*/

				g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
				g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
			}
			if (IsButtonPush(KEYINFO_RIGHT))
			{
				g_camera.rot.y -= CAMERA_TURN;

				/*if (g_camera.rot.y < -D3DX_PI)
				{
					g_camera.rot.y += D3DX_PI * 2.0f;
				}*/

				g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
				g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
			}
		}

		// �ړI�̒����_
		g_camera.posRDest.x = pCar->pos.x - g_camera.fFront * sinf(pCar->rotDest.y);
		g_camera.posRDest.z = pCar->pos.z - g_camera.fFront * cosf(pCar->rotDest.y);
		g_camera.posRDest.y = pCar->pos.y + g_camera.fHeightR;

		// �ړI�̎��_
		g_camera.posVDest.x = pCar->pos.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posVDest.z = pCar->pos.z - cosf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posVDest.y = pCar->pos.y + cosf(g_camera.rot.x) * g_camera.fLength + g_camera.fHeightV;
	}


	//// ���_�̈ړ�(�㉺)(Y,N�L�[)
	//if (GetKeyboardPress(DIK_Y) == true)
	//{
	//	g_camera.fHeightV += CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(DIK_N) == true)
	//{
	//	g_camera.fHeightV -= CAMERA_MOVE;
	//}

	//// �����_�ւ̃Y�[������(U,M�L�[)
	//if (GetKeyboardPress(DIK_U) == true && g_camera.fLength >= 100.0f)
	//{
	//	g_camera.fLength -= CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(DIK_M) == true && g_camera.fLength <= 300.0f)
	//{
	//	g_camera.fLength += CAMERA_MOVE;
	//}
	//if (g_camera.fLength > 300.0f)
	//{
	//	g_camera.fLength = 300.0f;
	//}
	//if (g_camera.fLength < 100.0f)
	//{
	//	g_camera.fLength = 100.0f;
	//}

	//// ���f���O���̋���
	//if (GetKeyboardPress(DIK_Q) == true && g_camera.fFront <= 25.0f)
	//{
	//	g_camera.fFront += 0.1f;
	//}
	//if (GetKeyboardPress(DIK_E) == true && g_camera.fFront >= 0.0f)
	//{
	//	g_camera.fFront -= 0.1f;
	//}
	//if (g_camera.fFront > 25.0f)
	//{
	//	g_camera.fFront = 25.0f;
	//}
	//if (g_camera.fFront < 0.0f)
	//{
	//	g_camera.fFront = 0.0f;
	//}

	//// 1�������p�x�̏C��
	//if (g_camera.rot.y < -D3DX_PI)
	//{
	//	g_camera.rot.y += D3DX_PI * 2.0f;
	//}
	//else if (g_camera.rot.y > D3DX_PI)
	//{
	//	g_camera.rot.y -= D3DX_PI * 2.0f;
	//}

	// �����̍X�V
	//g_camera.rot.y += (g_camera.rotDest.y - g_camera.rot.y) * 0.1f;


	// �ړ��ʂ̌���(����)
	//g_camera.move.x += (0.0f - g_camera.move.x) * 0.4f;
	//g_camera.move.z += (0.0f - g_camera.move.z) * 0.4f;

	// �ړ��ʂ̉��Z
	//g_camera.posV.x += g_camera.move.x;
	//g_camera.posV.z += g_camera.move.z;
	//g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
	//g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;

	// ���f���̈ʒu�֒����_��u��
	//g_camera.posR.x = model.pos.x;
	//g_camera.posR.z = model.pos.z;
	//g_camera.posV.x = model.pos.x + sinf(g_camera.rot.y) * -g_camera.fLength;
	//g_camera.posV.z = model.pos.z + cosf(g_camera.rot.y) * -g_camera.fLength;
	//g_camera.posV.y = model.pos.y + cosf(g_camera.rot.x) * 200.0f;

	//// �ړI�̒����_
	//g_camera.posRDest.x = model.pos.x - g_camera.fFront * sinf(model.rotDest.y);
	//g_camera.posRDest.z = model.pos.z - g_camera.fFront * cosf(model.rotDest.y);
	//g_camera.posRDest.y = model.pos.y + g_camera.fHeightR;

	//// �ړI�̎��_
	//g_camera.posVDest.x = model.pos.x - sinf(g_camera.rot.y) * g_camera.fLength;
	//g_camera.posVDest.z = model.pos.z - cosf(g_camera.rot.y) * g_camera.fLength;
	//g_camera.posVDest.y = model.pos.y + cosf(g_camera.rot.x) * g_camera.fLength + g_camera.fHeightV;

	//// �����_�̈ʒu�X�V
	//g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * CAMERA_SPDOWN;
	//g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * CAMERA_SPDOWN;
	//g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * CAMERA_SPDOWN;

	//// ���_�̈ʒu�X�V
	//g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * CAMERA_SPDOWN;
	//g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * CAMERA_SPDOWN;
	//g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * CAMERA_SPDOWN;

	//// �ړI�̒����_
	//g_camera.posRDest.x = player->pos.x - g_camera.fFront * sinf(player->rotDest.y);
	//g_camera.posRDest.z = player->pos.z - g_camera.fFront * cosf(player->rotDest.y);
	//g_camera.posRDest.y = player->pos.y + g_camera.fHeightR;

	/*g_camera.posRDest.x = pCar->pos.x - g_camera.fFront * sinf(pCar->rotDest.y);
	g_camera.posRDest.z = pCar->pos.z - g_camera.fFront * cosf(pCar->rotDest.y);
	g_camera.posRDest.y = pCar->pos.y + g_camera.fHeightR;*/

	//// �ړI�̎��_
	//g_camera.posVDest.x = player->pos.x - sinf(g_camera.rot.y) * g_camera.fLength;
	//g_camera.posVDest.z = player->pos.z - cosf(g_camera.rot.y) * g_camera.fLength;
	//g_camera.posVDest.y = player->pos.y + cosf(g_camera.rot.x) * g_camera.fLength + g_camera.fHeightV;

	/*g_camera.posVDest.x = pCar->pos.x - sinf(g_camera.rot.y) * g_camera.fLength;
	g_camera.posVDest.z = pCar->pos.z - cosf(g_camera.rot.y) * g_camera.fLength;
	g_camera.posVDest.y = pCar->pos.y + cosf(g_camera.rot.x) * g_camera.fLength + g_camera.fHeightV;*/

	// �����_�̈ʒu�X�V
	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * CAMERA_SPDOWN;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * CAMERA_SPDOWN;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * CAMERA_SPDOWN;

	// ���_�̈ʒu�X�V
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * CAMERA_SPDOWN;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * CAMERA_SPDOWN;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * CAMERA_SPDOWN;

	//if (GetKeyboardPress(KEYINFO_UP) == true)
	//{
	//	g_camera.moveZVR.x = sinf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.moveZVR.z = cosf(g_camera.rot.y) * CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(KEYINFO_DOWN) == true)
	//{
	//	g_camera.moveZVR.x = sinf(g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	//	g_camera.moveZVR.z = cosf(g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	//}
	//else
	//{
	//	g_camera.moveZVR.x = 0.0f;
	//	g_camera.moveZVR.z = 0.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_LEFT) == true)
	//{
	//	g_camera.moveXVR.x = cosf(-g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	//	g_camera.moveXVR.z = sinf(-g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	//{
	//	g_camera.moveXVR.x = cosf(-g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.moveXVR.z = sinf(-g_camera.rot.y) * CAMERA_MOVE;
	//}
	//else
	//{
	//	g_camera.moveXVR.x = 0.0f;
	//	g_camera.moveXVR.z = 0.0f;
	//}

	//// �����_�̈ړ�(���E)
	//if (GetKeyboardPress(KEYINFO_LEFT_CENTER) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;
	//}
	//else if(GetKeyboardPress(KEYINFO_RIGHT_CENTER) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / CAMERA_TURN;

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;
	//}

	//// �����_�̈ړ�(�㉺)
	//if (GetKeyboardPress(KEYINFO_UP_CENTER) == true)
	//{
	//	g_camera.moveR.y = CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(KEYINFO_DOWN_CENTER) == true)
	//{
	//	g_camera.moveR.y = -CAMERA_MOVE;
	//}
	//else
	//{
	//	g_camera.moveR.y = 0.0f;
	//}

	//// ���_�̈ړ�(���E)
	//if (GetKeyboardPress(KEYINFO_LEFT_TURN) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_RANGE;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_RANGE;
	//}
	//else if (GetKeyboardPress(KEYINFO_RIGHT_TURN) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / CAMERA_TURN;

	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_RANGE;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_RANGE;
	//}

	//// ���_�̈ړ�(�㉺)
	//if (GetKeyboardPress(KEYINFO_UP_SIGHT) == true)
	//{
	//	g_camera.moveV.y = CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(KEYINFO_DOWN_SIGHT) == true)
	//{
	//	g_camera.moveV.y = -CAMERA_MOVE;
	//}
	//else
	//{
	//	g_camera.moveV.y = 0.0f;
	//}

	//if (g_camera.rot.y < -D3DX_PI)
	//{
	//	g_camera.rot.y += D3DX_PI * 2;
	//}
	//else if (g_camera.rot.y > D3DX_PI)
	//{
	//	g_camera.rot.y -= D3DX_PI * 2;
	//}

	//// �ړ��ʂ̉��Z
	//g_camera.posV += g_camera.moveV;
	//g_camera.posR += g_camera.moveR;
	//g_camera.posV += g_camera.moveXVR;
	//g_camera.posR += g_camera.moveXVR;
	//g_camera.posV += g_camera.moveZVR;
	//g_camera.posR += g_camera.moveZVR;
}

//==============================================================================
// �J�����̐ݒ菈��
//==============================================================================
void SetCamera(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	//�r���[�|�[�g���擾
	//pDevice->SetViewport(&g_camera.viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(
		&g_camera.mtxProjection,
		D3DXToRadian(45.0f),									// ��p�̐ݒ�
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,				// ��ʔ䗦�̐ݒ� �r���[�|�[�g�̕�����
		//860 / (float)SCREEN_HEIGHT,							// ��ʔ䗦�̐ݒ� �r���[�|�[�g�̕�����
		10.0f,													// ��O���E�̕`�拗��
		5000.0f);												// �����E�̕`�拗��

														// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//==============================================================================
// �J�����̎擾
//==============================================================================
CAMERA *GetCamera(void)
{
	return &g_camera;
}