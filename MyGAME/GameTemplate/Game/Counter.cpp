#include "stdafx.h"
#include "Counter.h"
#include "ModelRender.h"
#include "Burger.h"

bool Counter::Start()
{
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = "Assets/modelData/box.tkm";
	modeldata.m_fxFilePath = "Assets/shader/model.fx";

	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	modeldata.m_modelUpAxis = enModelUpAxisY;

	m_skeleton.Init("Assets/modelData/unityChan.tks");
	modeldata.m_skeleton = &m_skeleton;

	model.Init(modeldata);

	m_charaCon.Init(0.0f, 0.0f, CounterPos);

	CounterPos2.y += 100.0f;

	return true;
}

//Burger�͏o�����Ă���B�����ĂȂ��B
void Counter::Delete()
{
	ModelRender* pl = FindGO<ModelRender>("player01");
	Vector3 plPos = pl->GetPosition();

	float pl2Counter = (plPos.x - CounterPos.x) * (plPos.x - CounterPos.x) + (plPos.y - CounterPos.y) * (plPos.y - CounterPos.y) + (plPos.z - CounterPos.z) * (plPos.z - CounterPos.z);
	pl2Counter = sqrt(pl2Counter);

	//�v���C���[���o�[�K�[�������Ă�����
	if (pl->have == 2) {
		Burger* bu = FindGO<Burger>("burger");

		//�L�b�`���ɒu������
		if (g_pad[0]->IsPress(enButtonB) && pl2Counter < 200.0f) {
			bu->putOnKitchen = 1;
		}

		if (bu->putOnKitchen == 1) {
			Delay++;
			bu->SetPosition(CounterPos2);

			if (Delay == 30) {
				DeleteGO(bu);
				Delay = 0;
				pl->have = 0;
			}
			
		}
	}
}

//bool Counter::Judge()
//{
//	Burger* bu = FindGO<Burger>("burger");
//	ModelRender* pl = FindGO<ModelRender>("player01");
//
//	int num = 5;
//	for (int i = 0; i < num; i++) {
//		
//	}
//
//}

void Counter::Update()
{
	Delete();
	model.UpdateWorldMatrix(m_charaCon.GetPosition(), g_quatIdentity, g_vec3One);
}