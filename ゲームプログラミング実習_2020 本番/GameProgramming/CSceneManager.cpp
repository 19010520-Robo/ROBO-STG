#include "CSceneManager.h"
#include "CSceneGame.h"
#include"CTitle.h"
#include"CAction.h"
CSceneManager SceneManager;

//�R���X�g���N�^
CSceneManager::CSceneManager()
: mpScene(0)
{}
//�f�X�g���N�^�i�폜�����Ƃ��Ɏ��s����܂��j
CSceneManager::~CSceneManager() {
	//�V�[��������΍폜
	if (mpScene)
		//�V�[���̍폜
		delete mpScene;
	mpScene = 0;
}
//����������
void CSceneManager::Init() {
	mScene = CScene::ETITLE;
	//�V�[���𐶐����A�|�C���^��ݒ肷��
	mpScene = new CTitle();
	//���������N���X�̃��\�b�h���Ă΂��
	mpScene->Init();
}
//�X�V����
void CSceneManager::Update() {
	//�|�C���^��Update���Ă�
	mpScene->Update();
	if (mScene != mpScene->GetNextScene()) {
		mScene = mpScene->GetNextScene();
		delete mpScene;//���̃V�[���폜
		//�Y������V�[���𐶐�
		switch (mScene) {
		case CScene::EGAME:
			mpScene = new CSceneGame();
			mpScene->Init();
			break;
		case CScene::EACTION:
			mpScene = new CAction();
			mpScene->Init();
			break;
		case CScene::ETITLE:
			mpScene = new CTitle();
			mpScene->Init();

		}
	}
}
