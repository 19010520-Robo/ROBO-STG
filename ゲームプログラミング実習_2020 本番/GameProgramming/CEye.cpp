#include"CEye.h"7
#include"CKey.h"
#include"CSceneGame.h"
CEye::CEye(CModel*model, CVector position, CVector rotation, CVector scale)
{
	//モデル、位置、回転、拡縮
	mpModel = model;

	mPosition = position;

	mRotation = rotation;

	mScale = scale;
}
void CEye::Update(){
	if (CXPlayer::mLook == false){
		if (CKey::Push('J')){
			mRotation.mY += 3;
		}
		if (CKey::Push('L')){
			mRotation.mY -= 3;
		}
	}
	if (CXPlayer::mLook == false){
		if (CKey::Push('I')){
			mRotation.mX -= 1.0;
		}
		if (CKey::Push('K')){
			mRotation.mX += 1.0;
		}
	}
	if (CXPlayer::mLook == true){
		mRotation.mX = 0;
	}
	CCharacter::Update();

}

CEye2::CEye2(CModel*model, CVector position, CVector rotation, CVector scale){
	//モデル、位置、回転、拡縮
	mpModel = model;

	mPosition = position;

	mRotation = rotation;

	mScale = scale;
}
void CEye2::Update(){

	CVector dir = CXPlayer::mPlayer->mPosition - mPosition;
	CVector left = CVector(1.0f, 0.0f, 0.0f)*
		CMatrix().RotateY(mRotation.mY);
	CVector up = CVector(0.0f, 1.0f, 0.0f)*
		CMatrix().RotateX(mRotation.mX)*
		CMatrix().RotateY(mRotation.mY);

	//左右の回転処理
	if (left.Dot(dir) > 0.0f){
		mRotation.mY += 5.0f;
	}
	else if (left.Dot(dir) < 0.0f){
		mRotation.mY -= 5.0f;
	}
	//上下の回転処理
	if (up.Dot(dir)>0.0f){
		mRotation.mX -= 5.0f;
	}
	else if (up.Dot(dir) < 0.0f){
		mRotation.mX += 5.0f;
	}
	
	//if (CXEnemy3::Senser == true){
	//	if (FireCount3 > 0) {
	//		FireCount3--;
	//	}
	//	else {
	//		CBullet2*bullet = new CBullet2();
	//		bullet->Set(0.1f, 1.5f);
	//		bullet->mPosition = CVector(0.0f, 0.0f, 1.0f)*mMatrix;
	//		bullet->mRotation = mRotation;
	//		FireCount3 = 60;
	//	}
	//}
	CCharacter::Update();
}
