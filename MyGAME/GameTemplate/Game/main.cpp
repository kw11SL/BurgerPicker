#include "stdafx.h"
#include "system/system.h"
#include "Level.h"
#include "ModelRender.h"
#include "Light.h"
#include <string>
#include "FontRender.h"
#include "SpriteRender.h"
#include "Guzai.h"
#include "math.h"

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

	FontRender SCORE01;
	FontRender SCORE02;
	FontRender TIME;
	FontRender timer;
	
	NewGO<FontRender>(10);

	//Sprite sprite;
	//SpriteInitData spdata;
	//spdata.m_ddsFilePath[MAX_TEXTURE] = { "Assets/modelData/light.DDS" };		//DDS�t�@�C���̃t�@�C���p�X�B
	//spdata.m_fxFilePath = "Assets/shader/model.fx";						//.fx�t�@�C���̃t�@�C���p�X�B
	//spdata.m_width = 5;										//�X�v���C�g�̕��B
	//spdata.m_height = 5;
	//sprite.Init(spdata);p

	/// ���x���\���p
	Level level;
	level.Init("Assets/level/level001.tkl", [&](ObjectData& objectData) {return false;});

	//�v���C���[�̃��f�����쐬x2
	ModelRender* re[2];
	re[0] = NewGO<ModelRender>(0);
	re[0]->SetPlayerNo(1);
	re[1] = NewGO<ModelRender>(0);
	re[1]->SetPlayerNo(2);

	//��ނ��쐬
	/*Guzai* g[5];
	for (int i = 0;i < 5; i++) {
		g[i] = NewGO<Guzai>(0);
		g[i]->exist = i;
	}*/
	//���Ԃ��Ƃ������̃����p
	int noMemo;
	int putNo = 0;

	
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

		
		

		//�J�����̈ړ�
		float move = g_pad[0]->GetRStickYF() * 30.0f;
		Vector3 camerapos = g_camera3D->GetPosition();
		camerapos.z -= move;
		g_camera3D->SetPosition(camerapos);

		//Light.Draw(renderContext);
		level.Draw();
		//sprite.Draw(renderContext);

		//��ނƂ̋����𑪂�A���̋�������A�{�^���������ƁA�v���C���[�̓���ɋ�ނ������Ă���B////////////////////////////////////
		/*Vector3 pl1Diff = re[0]->GetPosition();
		Vector3 pl2Diff = re[1]->GetPosition();
		
		Vector3 Kitchen01 = { 900.0f, 0.0f, 00.0f };
		
		for (int i = 0; i < 5; i++) {
			Vector3 guzaiDiff = g[i]->GetPosition();

			float diff4pl1 = (guzaiDiff.x - pl1Diff.x) * (guzaiDiff.x - pl1Diff.x) + (guzaiDiff.y - pl1Diff.y) * (guzaiDiff.y - pl1Diff.y) + (guzaiDiff.z - pl1Diff.z) * (guzaiDiff.z - pl1Diff.z);
			diff4pl1 = sqrt(diff4pl1);

			if (g_pad[0]->IsPress(enButtonA) && re[0]->have == 0) {
				if (diff4pl1 < 100.0f) {
					g[i]->state = 1;
					noMemo = i;
					re[0]->have = 1;
				}
			}
			if (g[i]->state == 1) {
				pl1Diff.y += 10.0f;
				g[i]->SetPosition(pl1Diff);
			}
		}

		float Diff2Kit = (Kitchen01.x - pl1Diff.x) * (Kitchen01.x - pl1Diff.x) + (Kitchen01.y - pl1Diff.y) * (Kitchen01.y - pl1Diff.y) + (Kitchen01.z - pl1Diff.z) * (Kitchen01.z - pl1Diff.z);
		Diff2Kit = sqrt(Diff2Kit);

		if (Diff2Kit < 100.0f && g_pad[0]->IsTrigger(enButtonB)) {
			g[noMemo]->state = 0;
			re[0]->have = 0;
			g[noMemo]->put = 1;
			Kitchen01.y += putNo * 100.0f;
			g[noMemo]->SetPosition(Kitchen01);
			putNo++;
		}*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

