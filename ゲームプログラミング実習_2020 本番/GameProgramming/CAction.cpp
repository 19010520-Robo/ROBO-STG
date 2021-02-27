#include"CAction.h"
#include "CCamera.h"
//
#include "CText.h"

#include"CRes.h"


#include<Windows.h>


#include"CXCharacter.h"

#include"CCollisionManager.h"
CMatrix Matrix2;
CModel BackGround2;
CModel CAction::mCube2;
CModel ModelEnemy2;

void CAction::Init(){
	//�V�[�����̓A�N�V����
	mScene = EACTION;

	CXEnemy2::mPointSize = 3;
	CXEnemy2::mPoint = new CPoint[CXEnemy2::mPointSize];
	CXEnemy2::mPoint[0].Set(CVector(35.0f, 0.0f, 100.0f), 10.0f);
	CXEnemy2::mPoint[1].Set(CVector(-35.0f, 0.0f, 50.0f), 10.0f);
	CXEnemy2::mPoint[2].Set(CVector(35.0f, 0.0f, 0.0f), 10.0f);


	mCube2.Load("cube.obj", "cube.mtl");
	ModelEnemy2.Load("f16.obj", "f16.mtl");
	BackGround2.Load("sky.obj", "sky.mtl");
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);

	CRes::sModelX.Load(MODEL_FILE);
	CRes::sKnight.Load(MODEL_FILE2);
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//1:�ړ�
	CRes::sKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:�ҋ@
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//3:�_�~�[
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//4:�_�~�[
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//5:�_�~�[
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//6:�_�~�[
	CRes::sKnight.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
	CRes::sKnight.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//9:�_�~�[
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//10:�_�~�[
	CRes::sKnight.SeparateAnimationSet(0, 1160, 1260, "death1");//11:�_�E��
	CEye(&mCube2, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f));
	//�L�����N�^�[�Ƀ��f����ݒ�
	Player.Init(&CRes::sModelX);
	//�G�̏����ݒ�
	mEnemy2 = new CXEnemy2(CVector(0.0f, 0.0f, 100.0f), CVector(), CVector(1.5f, 1.5f, 1.5f));
	mEnemy2->Init(&CRes::sKnight);
	//�G�̔z�u]
	mEnemy2->mAnimationFrameSize = 1024;
	mEnemy2->ChangeAnimation(1, true, 60);

	Player.mPosition = CVector(0.0f, 2.0f, -100.0f);

	mMap = new CMap();

}

void CAction::Update(){
	if (CXEnemy2::mEncount == false){
		TaskManager.Update();
	}
	//�J�����̈ʒu���v���C���[�̈ʒu�ɌŒ肷��
	mEye.mPosition = Player.mPosition;

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	if (CXPlayer::mLook == false){
		e = CVector(0.0, 5.5, -7.0)*mEye.mMatrix;
		//�����_�����߂�
		c = CVector(0.0, 0.0, 30.0)*mEye.mMatrix; //Player.mPosition;
		//����������߂�
		u = CVector(0.0, 0.5, 0.0)*mEye.mMatrixRotate;
	}
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	//�s��ݒ�
	glMultMatrixf(Matrix2.mF);
	//���f���`��
	BackGround2.Render();
	//�R���C�_�̕`��
	CollisionManager.Collision();
	TaskManager.Delete();
	TaskManager.Render();
	CollisionManager.Render();
	if (CXEnemy2::mEncount == true){
		mScene = EGAME;
	}
}

CAction::~CAction() {
	delete[]CXEnemy2::mPoint;
}
CScene::EScene CAction::GetNextScene() {
	return mScene;
}
