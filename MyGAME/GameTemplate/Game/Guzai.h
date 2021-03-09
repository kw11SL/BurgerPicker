#pragma once
#include <vector>

class Guzai : public IGameObject
{
private:
	Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;

public:	
	bool Start();
	void Update();
	
	Vector3 GetPosition();
	void SetPosition(Vector3 pos);

	void Render(RenderContext& rc) { model.Draw(rc); }

	//Update()�ŃC���N�������g����B
	int time = 0;
	//�P�Ȃ�Ύ�����Ă���B
	int state = 0;
	//�P�Ȃ�΂����L�b�`���ɒu����Ă���B
	int put = 0;
	//���i�ς�ł邩
	int stack = 0;
	//X�{�^���������Őςݏグ�Ă����ނ�S���폜����B���̂��߂̃^�C�}�[�B
	int DeleteTimer = 0;
	//��ނ̎�ޔԍ�
	//ToDo...�ύX�\�ɂ���B
	int TypeNo = 1;
};

