#include "stdafx.h"
#include "ModelRender.h"


//�C���X�^���X������Ƃ��Ƀ��f���A�e�̃p�X�����Ă����B
void ModelRender::GiveData(const char* ModelPath, const char* ShaderPath)
{
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = ModelPath;
	modeldata.m_fxFilePath = ShaderPath;

	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	

	model.Init(modeldata);
}