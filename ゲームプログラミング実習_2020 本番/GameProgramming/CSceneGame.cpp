#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"

#include"CRes.h"


#include<Windows.h>


#include"CXCharacter.h"

#include"CCollisionManager.h"

CMatrix Matrix;
CModel BackGround;
CModel CSceneGame::mCube;
CModel ModelEnemy;
void CSceneGame::Init() {

	CXEnemy3::mPointSize = 3;
	CXEnemy3::mPoint = new CPoint[CXEnemy3::mPointSize];
	CXEnemy3::mPoint[0].Set(CVector(35.0f, 35.0f, 100.0f), 10.0f);
	CXEnemy3::mPoint[1].Set(CVector(-35.0f, 35.0f, 50.0f), 10.0f);
	CXEnemy3::mPoint[2].Set(CVector(35.0f, 35.0f, 0.0f), 10.0f);

	CXEnemy::mPointSize = 3;
	CXEnemy::mPoint = new CPoint[CXEnemy3::mPointSize];
	CXEnemy::mPoint[0].Set(CVector(35.0f, 0.0f, 100.0f), 10.0f);
	CXEnemy::mPoint[1].Set(CVector(-35.0f, 0.0f, 50.0f), 10.0f);
	CXEnemy::mPoint[2].Set(CVector(35.0f, 0.0f, 0.0f), 10.0f);

	mCube.Load("cube.obj", "cube.mtl");
	ModelEnemy.Load("f16.obj", "f16.mtl");

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
	BackGround.Load("sky.obj", "sky.mtl");
	CEye(&mCube, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f));
	//CEye2(&mCube, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f));
	//�L�����N�^�[�Ƀ��f����ݒ�
	Player.Init(&CRes::sModelX);
	mEnemy = new CXEnemy(CVector(0.0f, 0.0f, 100.0f), CVector(), CVector(1.5f, 1.5f, 1.5f));
	//mEnemy = new CXEnemy(CVector(30.0f, 0.0f, 50.0f), CVector(), CVector(1.5f, 1.5f, 1.5f));
	mEnemy->Init(&CRes::sKnight);
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	//�G�̏����ݒ�
	//�G�̔z�u]
	Player.mPosition = CVector(0.0f, 2.0f, -100.0f);
	//new CXEnemy2(&mCube, CVector(100.0f, 20.0f, 100.0f), CVector(), CVector(1.5f, 1.5f, 1.5f));
	//new CXEnemy2(&mCube, CVector(10.0f, 20.0f, 30.0f), CVector(), CVector(1.5f, 1.5f, 1.5f));
	//mEnemy3 = new CXEnemy3(&ModelEnemy, CVector(100.0f, 35.0f, 100.0f), CVector(), CVector(1.5f, 1.5f, 1.5f));
	mEnemy->mAnimationFrameSize = 1024;
	mEnemy->ChangeAnimation(1, true, 60);
	mMap = new CMap();
}

void CSceneGame::Update() {
	
	//�L�����N�^�[�N���X�̍X�V0
	if (CXEnemy::mDeath == false){
		TaskManager.Update();
	}
	//�ŏ��̃A�j���[�V�����̌��ݎ��Ԃ�45�ɂ���
	////�ŏ��̃A�j���[�V�����̏d�݂�1.0(100%)�ɂ���
	//CRes::sModelX.mAnimationSet[0]->mWeight = 1.0f;
	////�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	//CRes::sModelX.AnimateFrame();
	////�t���[���̍����s����v�Z����
	//CRes::sModelX.mFrame[0]->AnimateCombined(&Matrix);

	mEye.mPosition = Player.mPosition;
	if (CXPlayer::mLook == true){
		mEye.mRotation.mY = Player.mRotation.mY;
	}
	//mEye2.mPosition = mEnemy3->mPosition;
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	if (CXPlayer::mLook == false){
		e = CVector(0.0, 5.5, -7.0)*mEye.mMatrix;
		//�����_�����߂�
		c = CVector(0.0, 0.0, 30.0)*mEye.mMatrix; //Player.mPosition;
		//����������߂�
		u = CVector(0.0, 0.5, 0.0)*mEye.mMatrixRotate;

	}
	if (CXPlayer::mLook == true){
		e = CVector(-2.5, 3.5, -6.0)*mEye.mMatrix;
		//�����_�����߂�
		c = CVector(0.0, 0.0, 30.0)*mEye.mMatrix; //Player.mPosition;
		//����������߂�
		u = CVector(0.0, 0.5, 0.0)*mEye.mMatrixRotate;

	}
	//�J�����̐ݒ�
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	////x���{��]
	//if (GetKeyState('K') & 0x8000){
	//	Matrix = Matrix*CMatrix().RotateX(1);
	//}
	////x���{��]
	//if (GetKeyState('I') & 0x8000){
	//	Matrix = Matrix*CMatrix().RotateX(-1);
	//}
	//y���{��]
	//if (GetKeyState('L') & 0x8000){
	//	Matrix = Matrix*CMatrix().RotateY(1);
	//}
	////y���{��]
	//if (GetKeyState('J') & 0x8000){
	//	Matrix = Matrix*CMatrix().RotateY(-1);
	//}
	//�s��ݒ�
	glMultMatrixf(Matrix.mF);
	//���f���`��
	BackGround.Render();
	//�R���C�_�̕`��
	CollisionManager.Collision();
	TaskManager.Delete();
	TaskManager.Render();
	//  CRes::sModelX.Render();
	CollisionManager.Render();
	static int frame = 0;//�t���[�����̃J�E���g
	frame++;//�t���[�����̃J�E���g

	//�e�N�X�`���e�X�g
	//CRes::sModelX.mMaterial[0]->mpTexture->DrawImage
	//	(-5, 5, -5, 5, 0, 128, 128, 0);
	//2D�`��J�n
	Start2D(0, 800, 0, 600);
	sprintf(buf, "%d", CXPlayer::PHP);
	CText::DrawString(buf, 45, 550, 25, 25);
	CText::DrawString("HP", 40, 590, 10, 10);
	if (frame < 150){
		//2D�`��
		CText::DrawString("GAME START", 170, 400, 20, 20);
	}
	if (CXEnemy::mDeath==true){
		CText::DrawString("GAME CLAER!", 180, 400, 20, 20);
	}
	if (CXPlayer::mPDeath == true){
		CText::DrawString("GAME OVER!", 180, 400, 20, 20);
	}


	//2D�`��I��
	End2D();
	return;
}

CSceneGame::~CSceneGame() {
	delete[]CXEnemy3::mPoint;
	delete[]CXEnemy::mPoint;
}
void CSceneGame::Start2D(float left, float right, float bottom, float top){
	//���f���r���[�s��̑ޑI
	glPushMatrix();
	//���f���r���[�s��̏�����
	glLoadIdentity();

	//���f���r���[�s�񂩂�
	//�v���W�F�N�V�����s��֐؂�ւ�
	glMatrixMode(GL_PROJECTION);
	//�v���W�F�N�V�����s��̑ޑI
	glPushMatrix();
	//�v���W�F�N�V�����s��̏�����
	glLoadIdentity();
	//2D�`��̐ݒ�
	gluOrtho2D(left, right, bottom, top);
	//Depth�e�X�g�I�t
	glDisable(GL_DEPTH_TEST);
}
void CSceneGame::End2D(){
	//�v���W�F�N�V�����s���߂�
	glPopMatrix();
	//���f���r���[���[�h�֐؂�ւ�
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�s���߂�
	glPopMatrix();
	//Depth�e�X�g�I��
	glEnable(GL_DEPTH_TEST);
}

