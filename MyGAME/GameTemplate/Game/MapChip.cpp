#include "stdafx.h"
#include "MapChip.h"

void MapChip::Init(const char* path01, Vector3 pos, Vector3 scale, Quaternion rot)
{
	m_modeldata.m_tkmFilePath = path01;
	m_modeldata.m_fxFilePath = "Assets/shader/model.fx";
	m_modeldata.m_expandConstantBuffer = &g_lig;
	m_modeldata.m_expandConstantBufferSize = sizeof(g_lig);
	m_model.Init(m_modeldata);
	m_model.UpdateWorldMatrix(pos, rot, scale);
}


void MapChip::Draw()
{
	m_model.Draw(g_graphicsEngine->GetRenderContext());
}