#include"CTitle.h"
#include"CKey.h"
#include"CSceneGame.h"

void CTitle::Init() {
	//�e�N�X�`���t�@�C����ǂݍ���
	//�t�H���g�̐ݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	//�V�[���̐ݒ�
	mScene = ETITLE;
}
void CTitle::Update() {
	//������̕`��
	Start2D(0, 800, 0, 600);

	CText::DrawString("SWORD",400,300,30,30);
	End2D();

	if (CKey::Once(VK_RETURN)) {
		//���̃V�[���̓Q�[��
		mScene = EACTION;
	}
}
//���̃V�[���̎擾
CScene::EScene CTitle::GetNextScene() {
	return mScene;
}