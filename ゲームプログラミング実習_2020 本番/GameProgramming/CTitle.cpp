#include"CTitle.h"
#include"CKey.h"
void CTitle::Init() {
	//�e�N�X�`���t�@�C����ǂݍ���
	//�t�H���g�̐ݒ�
	CText::mFont.Load("font.tga");
	//�V�[���̐ݒ�
	mScene = ETITLE;
}
void CTitle::Update() {

	//������̕`��
	CText::DrawString("SHOOT", -190, 210, 30, 50);
	CText::DrawString("&", 0, 120, 30, 35);
	CText::DrawString("DODGE", -70, 20, 30, 50);
	CText::DrawString("Push ENTER Key", -200, -200, 16, 16);
	if (CKey::Once(VK_RETURN)) {
		//���̃V�[���̓Q�[��
		mScene = EGAME;
	}
}
//���̃V�[���̎擾
CScene::EScene CTitle::GetNextScene() {
	return mScene;
}