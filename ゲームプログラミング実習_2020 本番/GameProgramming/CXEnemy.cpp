#include"CXEnemy.h"
#include"CXPlayer.h"
CXEnemy *CXEnemy::mEnemy = 0;
CPoint *CXEnemy3::mPoint;
int CXEnemy3::mPointSize = 0;
CPoint *CXEnemy::mPoint;
int CXEnemy::mPointSize = 0;
CXEnemy3*CXEnemy3::mEnemy3 = 0;
bool CXEnemy3::Senser = false;
bool CXEnemy::mEAttack = false;
bool CXEnemy::mEAttackS = false;
bool CXEnemy::mDeath = false;

CXEnemy::CXEnemy(CVector position, CVector rotation, CVector scale)
:mColSphereBody(this, CVector(0.5f, -1.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 2.0f)
, mColSphereHead(this, CVector(0.0f, 1.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.5f)
, mColSphereSword0(this, CVector(0.7f, 3.5f, -0.2f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.6f)
, mColSphereSword1(this, CVector(0.5f, 2.5f, -0.2f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.4f)
, mColSphereSword2(this, CVector(0.3f, 1.5f, -0.2f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.3f)
, mSearch(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 50.0f)
, mSearchA(this, CVector(0.0f, 2.5f, -2.5f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 20.0f)
, mSearchB(this, CVector(0.0f, 2.5f, -2.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 2.0f)
{
	mTag = EENEMY;
	EHP = 200;
	X = 0;
	Y = 0;
	T = 0;
	Counter = 0;
	Time = T * 60;
	mPosition = position;//位置の設定
	mRotation = rotation;//回転の設定
	mScale = scale;//拡縮の設定
	mColSphereBody.mTag = CCollider::EEBODY;
	mSearch.mTag = CCollider::ESEARCH;
	mSearchA.mTag = CCollider::ESEARCHA;
	mSearchB.mTag = CCollider::ESEARCHB;
	mColSphereSword0.mTag = CCollider::EESWORD;
	mColSphereSword1.mTag = CCollider::EESWORD;
	mColSphereSword2.mTag = CCollider::EESWORD;

	mPointCnt = 0;//最初のポイントを設定
	mpPoint = &mPoint[mPointCnt];//&mPoint[mPointCnt];//目指すポイントのポインタを設定
	mKAKUNIN = false;
	mSWORD = false;
	mEnemy = this;
	mKAIHI = false;
	mKnockBack = false;
	mDown = false;
	mHangeki = false;
	mStop = false;
}
void CXEnemy::Init(CModelX*model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.mpCombinedMatrix = &mpCombinesMatrix[1];
	//頭
	mColSphereHead.mpCombinedMatrix = &mpCombinesMatrix[1];
	//剣
	mColSphereSword0.mpCombinedMatrix = &mpCombinesMatrix[26];
	mColSphereSword1.mpCombinedMatrix = &mpCombinesMatrix[26];
	mColSphereSword2.mpCombinedMatrix = &mpCombinesMatrix[26];
}
void CXEnemy::Update(){
	if (mpPoint == 0)
	{
		return;
	}
	if (EHP<1){
		ChangeAnimation(11, false, 90);
		if (mAnimationFrame >= mAnimationFrameSize){
			mEnabled = false;
			mDeath = true;
		}
	}
	if (EHP > 0){
		if (mKAKUNIN == false){
			CVector dir = mpPoint->mPosition - mPosition;
			//左方向のベクトルを求める
			CVector left = CVector(1.0f, 0.0f, 0.0f)*
				CMatrix().RotateY(mRotation.mY);
			//CVector right = CVector(-1.0f, 0.0f, 0.0f)*
			//	CMatrix().RotateY(mRotation.mY);
			//上方向のベクトルを求める
			/*CVector up = CVector(0.0f, 1.0f, 0.0f)*
				CMatrix().RotateX(mRotation.mX)*
				CMatrix().RotateY(mRotation.mY);*/
			//左右の回転処理
			if (left.Dot(dir) > 0.0f){
				mRotation.mY -= 1.5f;
			}
			else if (left.Dot(dir) < 0.0f){
				mRotation.mY += 1.5f;
			}
			mPosition = CVector(0.0f, 0.0f, -0.1f)*mMatrix;
		}
		if (mKAKUNIN == true&&mDown==false&&mKnockBack==false){
			CVector dir = CXPlayer::mPlayer->mPosition - mPosition;
			//左方向のベクトルを求める
			CVector left = CVector(1.0f, 0.0f, 0.0f)*
				CMatrix().RotateY(mRotation.mY);
			//CVector right = CVector(-1.0f, 0.0f, 0.0f)*
			//	CMatrix().RotateY(mRotation.mY);
			//上方向のベクトルを求める
			/*CVector up = CVector(0.0f, 1.0f, 0.0f)*
			CMatrix().RotateX(mRotation.mX)*
			CMatrix().RotateY(mRotation.mY);*/
			//左右の回転処理
			if (left.Dot(dir) > 0.0f){
				mRotation.mY -= 5.0f;
			}
			else if (left.Dot(dir) < 0.0f){
				mRotation.mY += 5.0f;
			}
			if (mKAIHI == false){
				mPosition = CVector(0.0f, 0.0f, -0.1f)*mMatrix;
			}
			if (mKAIHI == true){
				mPosition = CVector(0.0f, 0.0f, 0.3f)*mMatrix;
			}
		}
		if (mStop == true){
			mPosition = CVector(0.0f, 0.0f, 0.0f)*mMatrix;
		}
		if (mSWORD == true && mKnockBack == false && mDown == false){
			ChangeAnimation(7, true, 80);
			if (mStop == false){
				if (mAnimationFrame<30){
					mPosition = CVector(0.0f, 0.0f, 0.0f)*mMatrix;
				}
				if (mAnimationFrame >= 30){
					mPosition = CVector(0.0f, 0.0f, -0.35f)*mMatrix;
				}
			}
			if (mAnimationFrame == 30){
				mEAttack = true;
			}
			if (mAnimationFrame > 50){
				if (mStop == false){
					mEAttack = false;
					mPosition = CVector(0.0f, 0.0f, -0.01f)*mMatrix;
				}
			}
			if (mAnimationFrame >= mAnimationFrameSize&&mAnimationIndex == 7){
				mSWORD = false;
				mStop = false;
			}
		}
		if (mSWORD == false && mKnockBack == false && mDown == false && mHangeki == false){
			ChangeAnimation(1, true, 30);
		}
		if (Counter > 999){
			mHangeki = true;
			mSWORD = false;
			mStop = false;
		}
		if (mHangeki == true){
			ChangeAnimation(7, false, 40);
			mPosition = CVector(0.0f, 0.0f, 0.06f)*mMatrix;
			mEAttack = false;
			mEAttackS = true;
			if (mAnimationFrame >= mAnimationFrameSize&&mAnimationIndex == 7){
				Counter = 0;
				mEAttackS = false;
				mHangeki = false;
				X = 0;
				Y = 0;
				mDown = false;
				mKnockBack = false;
			}
		}
		if (mHangeki == false){
			if (mKnockBack == true){
				ChangeAnimation(2, false, 100);
				mPosition = CVector(0.0f, 0.0f, 0.07f)*mMatrix;
			}
			if (X > 0){
				X--;
			}
			if (X == 0){
				mKnockBack = false;
			}
		}
		if (mHangeki == false){
			if (mDown == true){
				ChangeAnimation(11, false, 60);
				if (EHP < 1 && mAnimationFrame>50 && mAnimationIndex == 11){
					mAnimationFrame = 60;
				}
			}
			if (Y > 0){
				mPosition = CVector(0.0f, 0.0f, 0.25f)*mMatrix;
				Y--;
			}
			if (Y == 0 && mAnimationFrame >= mAnimationFrameSize&&EHP > 0){
				mDown = false;
			}
		}
	}
	////上下の回転処理
	//if (up.Dot(dir)>0.0f){
	//	mRotation.mX -= 0.3f;
	//}
	//else if (up.Dot(dir) < 0.0f){
	//	mRotation.mX += 0.3f;
	//}
	//行列を移動
	CXCharacter::Update();
	//CCharacter::Update();
	//位置を移動
}

void CXEnemy::Collision(CCollider*m, CCollider*y){
	if (m->mType == CCollider::ESPHERE&&y->mType == CCollider::ESPHERE){
		if (CCollider::Collision(m, y)){
			if (m->mTag == CCollider::ESEARCH){
				switch (y->mpParent->mTag){
				case EPLAYER:
					if (y->mTag==CCollider::EPBODY){
						mKAKUNIN = true;
					}
					if (y->mTag == CCollider::ESWORD){
						if (CXPlayer::mAttack == false){
							mKAIHI = false;
						}
					}
				}
			}
			if (m->mTag == CCollider::ESEARCHA){
				switch (y->mpParent->mTag){
				case EPLAYER:
					if (y->mTag == CCollider::EPBODY){
						mSWORD = true;
					}
					if (y->mTag == CCollider::ESWORD){
						if (CXPlayer::mAttack == true){
							//mKAIHI = true;
						}
					}
				}
			}
			if (m->mTag == CCollider::EEBODY){
				switch (y->mpParent->mTag){
				case EPLAYER:
					if (y->mTag == CCollider::ESWORD&&CXPlayer::mAttack==true){
						mKnockBack = true;
						CXPlayer::mAttack = false;
						EHP -= 5+rand()%10;
						X += 25;
						Counter += 70+rand()%30;
					}
					if (y->mTag == CCollider::ESWORD&&CXPlayer::mAttackS == true){
						X = 0;
						mDown = true;
						CXPlayer::mAttackS = false;
						EHP -= 10+rand()%15;
						Y += 25;
						Counter += 400+rand()%200;
					}
				}
			}
			if (m->mTag == CCollider::ESEARCHB){
				switch (y->mpParent->mTag){
				case EPLAYER:
					if (y->mTag == CCollider::EPBODY){
						mStop = true;
					}
				}
			}
			else{
				switch (y->mpParent->mTag){
				case EPOINT:
					if (y->mpParent == mpPoint){
						mPointCnt=rand()%3;//次のポイントにする
						//最後だったら最初にする
						//mPointCnt %= mPointSize;
						//次のポイントのポインタを設定
						mpPoint = &mPoint[mPointCnt];
					}
					break;
				}
			}
		}
	}
	else{
		mKAKUNIN = false;
	}
}
CXEnemy2::CXEnemy2(CModel*model, CVector position, CVector rotation, CVector scale)
:mBall(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 1.0f)
, mSearch3(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 30.0f)
{
	mTag = EENEMY;

	mpModel = model;//モデルの設定
	mPosition = position;//位置の設定
	mRotation = rotation;//回転の設定
	mScale = scale;//拡縮の設定
	mBall.mTag = CCollider::EEBODY;
	mSearch3.mTag = CCollider::ESEARCH3;
}
void CXEnemy2::Update(){
	CVector dir = CXPlayer::mPlayer->mPosition - mPosition;
	//左方向のベクトルを求める
	CVector left = CVector(1.0f, 0.0f, 0.0f)*
		CMatrix().RotateY(mRotation.mY);
	CVector up = CVector(0.0f, 1.0f, 0.0f)*
	CMatrix().RotateX(mRotation.mX)*
	CMatrix().RotateY(mRotation.mY);

	//左右の回転処理
	if (left.Dot(dir) > 0.0f){
		mRotation.mY += 1.5f;
	}
	else if (left.Dot(dir) < 0.0f){
		mRotation.mY -= 1.5f;
	}
	if (up.Dot(dir)>0.0f){
		mRotation.mX -= 1.0f;
	}
	else if (up.Dot(dir) < 0.0f){
		mRotation.mX += 1.0f;
	}

	if (FireCount2 > 0) {
		FireCount2--;
	}
	else
	{
		CBullet2*bullet = new CBullet2();
		bullet->Set(1.0f, 1.5f);
		bullet->mPosition = CVector(0.0f, 0.0f, 7.0f)*mMatrix;
		bullet->mRotation = mRotation;
		FireCount2 = 90;
	}
	CCharacter::Update();
}
void CXEnemy2::Collision(CCollider*mm, CCollider*ym){
	if (mm->mType == CCollider::ESPHERE&&ym->mType == CCollider::ESPHERE){
		if (CCollider::Collision(mm, ym)){
			if (mm->mTag == CCollider::ESEARCH3){
				if (ym->mTag == CCollider::EBULLET){
					mPosition = CVector(1.0f, 0.0f, 0.0f)*mMatrix;
				}
			}
		}
	}
}
CXEnemy3::CXEnemy3(CModel*model, CVector position, CVector rotation, CVector scale)
:mAir(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 1.0f)
, mSearch2(this, CVector(0.0f, -20.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 30.0f)
{
	mTag = EENEMY;

	mpModel = model;//モデルの設定
	mPosition = position;//位置の設定
	mRotation = rotation;//回転の設定
	mScale = scale;//拡縮の設定
	mAir.mTag = CCollider::EEBODY;
	mSearch2.mTag = CCollider::ESEARCH2;
	mPointCnt = 0;//最初のポイントを設定
	mpPoint = &mPoint[mPointCnt];//&mPoint[mPointCnt];//目指すポイントのポインタを設定
}

void CXEnemy3::Update(){
	if (mpPoint == 0){
		return;
	}
	CVector dir = mpPoint->mPosition - mPosition;
	//左方向のベクトルを求める
	CVector left = CVector(1.0f, 0.0f, 0.0f)*
		CMatrix().RotateY(mRotation.mY);
	//左右の回転処理
	if (left.Dot(dir) > 0.0f){
		mRotation.mY += 1.0f;
	}
	else if (left.Dot(dir) < 0.0f){
		mRotation.mY -= 1.0f;
	}
	CCharacter::Update();
	mPosition = CVector(0.0f, 0.0f, 0.2f)*mMatrix;
	

}
void CXEnemy3::Collision(CCollider*ms, CCollider*ys){
	if (ms->mType == CCollider::ESPHERE&&ys->mType == CCollider::ESPHERE){
		if (CCollider::Collision(ms, ys)){
			if (ms->mTag == CCollider::ESEARCH2){
				switch (ys->mpParent->mTag){
				case EPLAYER:
					CXEnemy3::Senser = true;
				}
			}
			else{
				switch (ys->mpParent->mTag){
				case EPOINT:
					if (ys->mpParent == mpPoint){
						mPointCnt++;//次のポイントにする
						//最後だったら最初にする
						mPointCnt %= mPointSize;
						//次のポイントのポインタを設定
						mpPoint = &mPoint[mPointCnt];
					}
					break;
				}
			}
		}
	}
	else{
		CXEnemy3::Senser = false;
	}
}