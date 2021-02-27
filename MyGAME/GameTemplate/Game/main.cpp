#include "stdafx.h"
#include "system/system.h"
#include "Level.h"
#include "ModelRender.h"
#include "Light.h"
#include <string>


// �E�B���h�E�v���O�����̃��C���֐��B
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	//�f�B���N�V�������C�g�A�|�C���g���C�g
	//�ꏏ�����ɂ��Ȃ��Ɨ����̃��C�g�̉e�����󂯂Ȃ��Ȃ�B
	
	g_lig.DirDirection = { -1.0f,1.0f,0.0f };
	g_lig.DirDirection.Normalize();
	g_lig.DirColor = { 1.0f,1.0f,1.0f };
	g_lig.eyePos = g_camera3D->GetPosition();
	
	//�|�C���g���C�g
	g_lig.ptPosition = { 0.0f, 60.0f,0.0f };
	g_lig.ptColor = { 0.0f, 100.0f,100.0f };
	g_lig.ptRange = 300.0f;

	//�X�|�b�g���C�g
	g_lig.spDirection = { 1.0f,-1.0f,0.0f };
	g_lig.spDirection.Normalize();
	
	g_lig.spAngle = Math::DegToRad(30.0f);


	//���C�g�p
	//ModelInitData lightdata;
	//lightdata.m_tkmFilePath = "Assets/modelData/light.tkm";

	//lightdata.m_fxFilePath = "Assets/shader/model.fx";

	//lightdata.m_expandConstantBuffer = &g_lig;
	//lightdata.m_expandConstantBufferSize = sizeof(g_lig);

	//Model Light;
	//Light.Init(lightdata);
	/// ���x���\���p
	Level level;
	level.Init("Assets/level/level001.tkl", [&](ObjectData& objectData) {return false;});

	ModelRender* re[2];
	re[0] = NewGO<ModelRender>(0);
	re[0]->SetPlayerNo(1);
	re[1] = NewGO<ModelRender>(0);
	re[1]->SetPlayerNo(2);

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		
		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////
		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		Quaternion RotY;
		RotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.03f);
		RotY.Apply(g_lig.spDirection);

		Vector3 rotAxis;
		rotAxis.Cross(g_vec3AxisY, g_lig.spDirection);
		Quaternion rotX;
		rotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * -0.03f);
		rotX.Apply(g_lig.spDirection);

		//g_lig.ptPosition.x -= g_pad[0]->GetLStickXF() * 5.0f;
		//g_lig.ptPosition.z -= g_pad[0]->GetLStickYF() * 5.0f;

		//Light.UpdateWorldMatrix(g_lig.ptPosition, g_quatIdentity, g_vec3One);

		//�������o�͂���B
		

		//�J�����̈ړ�
		float move = g_pad[0]->GetRStickYF() * 30.0f;
		Vector3 camerapos = g_camera3D->GetPosition();
		camerapos.z -= move;
		g_camera3D->SetPosition(camerapos);

		//Light.Draw(renderContext);
		level.Draw();
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

