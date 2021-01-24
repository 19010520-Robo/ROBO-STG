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
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//1:移動
	CRes::sKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:待機
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//3:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//4:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//5:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//6:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
	CRes::sKnight.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//9:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//10:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 1160, 1260, "death1");//11:ダウン
	BackGround.Load("sky.obj", "sky.mtl");
	CEye(&mCube, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f));
	//CEye2(&mCube, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f));
	//キャラクターにモデルを設定
	Player.Init(&CRes::sModelX);
	mEnemy = new CXEnemy(CVector(0.0f, 0.0f, 100.0f), CVector(), CVector(1.5f, 1.5f, 1.5f));
	//mEnemy = new CXEnemy(CVector(30.0f, 0.0f, 50.0f), CVector(), CVector(1.5f, 1.5f, 1.5f));
	mEnemy->Init(&CRes::sKnight);
	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	//敵の初期設定
	//敵の配置]
	Player.mPosition = CVector(0.0f, 2.0f, -100.0f);
	//new CXEnemy2(&mCube, CVector(100.0f, 20.0f, 100.0f), CVector(), CVector(1.5f, 1.5f, 1.5f));
	//new CXEnemy2(&mCube, CVector(10.0f, 20.0f, 30.0f), CVector(), CVector(1.5f, 1.5f, 1.5f));
	//mEnemy3 = new CXEnemy3(&ModelEnemy, CVector(100.0f, 35.0f, 100.0f), CVector(), CVector(1.5f, 1.5f, 1.5f));
	mEnemy->mAnimationFrameSize = 1024;
	mEnemy->ChangeAnimation(1, true, 60);
	mMap = new CMap();
}

void CSceneGame::Update() {
	
	//キャラクタークラスの更新0
	if (CXEnemy::mDeath == false){
		TaskManager.Update();
	}
	//最初のアニメーションの現在時間を45にする
	////最初のアニメーションの重みを1.0(100%)にする
	//CRes::sModelX.mAnimationSet[0]->mWeight = 1.0f;
	////フレームの変換行列をアニメーションで更新する
	//CRes::sModelX.AnimateFrame();
	////フレームの合成行列を計算する
	//CRes::sModelX.mFrame[0]->AnimateCombined(&Matrix);

	mEye.mPosition = Player.mPosition;
	if (CXPlayer::mLook == true){
		mEye.mRotation.mY = Player.mRotation.mY;
	}
	//mEye2.mPosition = mEnemy3->mPosition;
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	if (CXPlayer::mLook == false){
		e = CVector(0.0, 5.5, -7.0)*mEye.mMatrix;
		//注視点を求める
		c = CVector(0.0, 0.0, 30.0)*mEye.mMatrix; //Player.mPosition;
		//上方向を求める
		u = CVector(0.0, 0.5, 0.0)*mEye.mMatrixRotate;

	}
	if (CXPlayer::mLook == true){
		e = CVector(-2.5, 3.5, -6.0)*mEye.mMatrix;
		//注視点を求める
		c = CVector(0.0, 0.0, 30.0)*mEye.mMatrix; //Player.mPosition;
		//上方向を求める
		u = CVector(0.0, 0.5, 0.0)*mEye.mMatrixRotate;

	}
	//カメラの設定
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	////x軸＋回転
	//if (GetKeyState('K') & 0x8000){
	//	Matrix = Matrix*CMatrix().RotateX(1);
	//}
	////x軸＋回転
	//if (GetKeyState('I') & 0x8000){
	//	Matrix = Matrix*CMatrix().RotateX(-1);
	//}
	//y軸＋回転
	//if (GetKeyState('L') & 0x8000){
	//	Matrix = Matrix*CMatrix().RotateY(1);
	//}
	////y軸＋回転
	//if (GetKeyState('J') & 0x8000){
	//	Matrix = Matrix*CMatrix().RotateY(-1);
	//}
	//行列設定
	glMultMatrixf(Matrix.mF);
	//モデル描画
	BackGround.Render();
	//コライダの描画
	CollisionManager.Collision();
	TaskManager.Delete();
	TaskManager.Render();
	//  CRes::sModelX.Render();
	CollisionManager.Render();
	static int frame = 0;//フレーム数のカウント
	frame++;//フレーム数のカウント

	//テクスチャテスト
	//CRes::sModelX.mMaterial[0]->mpTexture->DrawImage
	//	(-5, 5, -5, 5, 0, 128, 128, 0);
	//2D描画開始
	Start2D(0, 800, 0, 600);
	sprintf(buf, "%d", CXPlayer::PHP);
	CText::DrawString(buf, 45, 550, 25, 25);
	CText::DrawString("HP", 40, 590, 10, 10);
	if (frame < 150){
		//2D描画
		CText::DrawString("GAME START", 170, 400, 20, 20);
	}
	if (CXEnemy::mDeath==true){
		CText::DrawString("GAME CLAER!", 180, 400, 20, 20);
	}
	if (CXPlayer::mPDeath == true){
		CText::DrawString("GAME OVER!", 180, 400, 20, 20);
	}


	//2D描画終了
	End2D();
	return;
}

CSceneGame::~CSceneGame() {
	delete[]CXEnemy3::mPoint;
	delete[]CXEnemy::mPoint;
}
void CSceneGame::Start2D(float left, float right, float bottom, float top){
	//モデルビュー行列の退選
	glPushMatrix();
	//モデルビュー行列の初期化
	glLoadIdentity();

	//モデルビュー行列から
	//プロジェクション行列へ切り替え
	glMatrixMode(GL_PROJECTION);
	//プロジェクション行列の退選
	glPushMatrix();
	//プロジェクション行列の初期化
	glLoadIdentity();
	//2D描画の設定
	gluOrtho2D(left, right, bottom, top);
	//Depthテストオフ
	glDisable(GL_DEPTH_TEST);
}
void CSceneGame::End2D(){
	//プロジェクション行列を戻す
	glPopMatrix();
	//モデルビューモードへ切り替え
	glMatrixMode(GL_MODELVIEW);
	//モデルビュー行列を戻す
	glPopMatrix();
	//Depthテストオン
	glEnable(GL_DEPTH_TEST);
}

