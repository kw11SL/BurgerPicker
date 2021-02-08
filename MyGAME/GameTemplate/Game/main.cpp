#include "stdafx.h"
#include "system/system.h"

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
	struct Light
	{
		//Direction
		Vector3 Direction;
		float pad;
		Vector3 Color;
		float pad1;
		Vector3 eyePos;
		float pad2;
		
		//Point
		Vector3 ptPosition;
		float pad3;
		Vector3 ptColor;
		float ptRange;

		//Spot
		Vector3 spDirection;
		float spAngle;
	};

	Light lig;

	lig.Direction.x = 1.0f;
	lig.Direction.y = 0.0f;
	lig.Direction.z = 0.0f;
	lig.Direction.Normalize();

	lig.Color.x = 1.0f;
	lig.Color.y = 1.0f;
	lig.Color.z = 1.0f;

	lig.eyePos = g_camera3D->GetPosition();
	
	//�|�C���g���C�g
	lig.ptPosition.x = 0.0f;
	lig.ptPosition.y = 60.0f;
	lig.ptPosition.z = 0.0f;
	
	lig.ptColor.x = 0.0f;
	lig.ptColor.y = 100.0f;
	lig.ptColor.z = 100.0f;

	lig.ptRange = 300.0f;

	//�X�|�b�g���C�g
	lig.spDirection.x = 1.0f;
	lig.spDirection.y = -1.0f;
	lig.spDirection.z = 0.0f;
	lig.spDirection.Normalize();
	
	lig.spAngle = Math::DegToRad(30.0f);

	struct Disco
	{
		Vector3 discoPos;
		float pad4;
		Vector3 discoDir;
		float pad;
		Vector3 discoColor;
		float discoRange;
		Vector3 eyePos;
	};

	Disco disco;
	disco.discoPos = { 0.0f,150.0f,0.0f };
	disco.discoDir = { 0.0f,1.0f,0.0f };
	disco.discoColor = { 1.0f,1.0f,1.0f };
	disco.discoDir.Normalize();
	disco.discoRange = 100.0f;
	disco.eyePos = g_camera3D->GetPosition();

	//Unity�p
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	modeldata.m_fxFilePath = "Assets/shader/model.fx";
	
	modeldata.m_expandConstantBuffer = &lig;
	modeldata.m_expandConstantBufferSize = sizeof(lig);
	
	Model Unity;
	Unity.Init(modeldata);

	//�X�e�[�W�p
	modeldata.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";

	Model Stage;
	Stage.Init(modeldata);

	//���C�g�p
	ModelInitData lightdata;
	lightdata.m_tkmFilePath = "Assets/modelData/light.tkm";

	lightdata.m_fxFilePath = "Assets/shader/model.fx";

	lightdata.m_expandConstantBuffer = &lig;
	lightdata.m_expandConstantBufferSize = sizeof(lig);

	Model Light;
	Light.Init(lightdata);

	

	ModelInitData discodata;
	discodata.m_tkmFilePath = "Assets/modelData/light.tkm";

	discodata.m_fxFilePath = "Assets/shader/model.fx";

	discodata.m_expandConstantBuffer = &disco;
	discodata.m_expandConstantBufferSize = sizeof(disco);

	Model Disco;
	Disco.Init(discodata);


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
		RotY.Apply(lig.spDirection);

		Vector3 rotAxis;
		rotAxis.Cross(g_vec3AxisY, lig.spDirection);
		Quaternion rotX;
		rotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * -0.03f);
		rotX.Apply(lig.spDirection);

		lig.ptPosition.x -= g_pad[0]->GetLStickXF() * 5.0f;
		lig.ptPosition.z -= g_pad[0]->GetLStickYF() * 5.0f;

		Light.UpdateWorldMatrix(lig.ptPosition, g_quatIdentity, g_vec3One);
		Disco.UpdateWorldMatrix(disco.discoPos, g_quatIdentity, g_vec3One);

		Unity.Draw(renderContext);
		Stage.Draw(renderContext);
		Light.Draw(renderContext);
		Disco.Draw(renderContext);
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

