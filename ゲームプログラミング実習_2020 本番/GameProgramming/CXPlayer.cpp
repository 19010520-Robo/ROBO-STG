#include"CXPlayer.h"
#include"CKey.h"
#include"CSceneGame.h"
#include"CXPlayerS.h"
CXPlayer *CXPlayer::mPlayer = 0;
int CXPlayer::mPLife;
bool CXPlayer::mInSight = false;
bool CXPlayer::mLook = false;
bool CXPlayer::mAttack = false;
bool CXPlayer::mAttackS = false;
bool CXPlayer::mPDeath = false;
int CXPlayer::PHP = 30;

CXPlayer::CXPlayer()
:mColSphereBody(this, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.7f)
, mColSphereHead(this, CVector(0.0f, 5.0f, -3.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.5f)
, mColSphereSword(this, CVector(-10.0f, 10.0f, 50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.9f)
, mAshi1(this, CVector(0.0f, 1.5f, 0.0f), CVector(), CVector(5.0f, 5.0f, 5.0f),0.5f)
, mAshi2(this, CVector(0.0f, 1.5f, 0.0f), CVector(), CVector(5.0f, 5.0f, 5.0f), 0.5f)
, mSight(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 50.0f)

{
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//タグにプレイヤーを設定します
	mTag = EPLAYER;
	mColSphereBody.mTag = CCollider::EPBODY;
	mColSphereSword.mTag = CCollider::ESWORD;
	mSight.mTag = CCollider::ESIGHT;
	mVelovcityJump = 0;
	X = 0;
	Y = 0;
	L = 0;
	mHyuu = true;
	mPlayer = this;
	mPLife = 3;
	mRengeki = false;
	mStop = false;
	mCancel = false;
	Back = false;
	Down = false;
	Yokeru = false;
}

void CXPlayer::Update(){
	if (PHP<1){
		ChangeAnimation(11, false, 90);
		mPDeath = true;
		PHP = DEAD;
		}
	if (PHP > 0){
		if (mAnimationIndex == 4 && mRengeki == true){
			if (CKey::Once(VK_SPACE)){
				ChangeAnimation(5, false, 20);
				mPosition = CVector(0.0f, 0.0f, 2.0f)*mMatrix;
				mAttackS = true;
				Yokeru = false;
			}
		}
		if (mAnimationIndex == 5){
			if (mAnimationFrame >= mAnimationFrameSize){
				ChangeAnimation(6, false, 40);
				mRengeki = false;
				Yokeru = true;
			}
		}
		if (mAnimationIndex == 3){
			if (mAnimationFrame >= mAnimationFrameSize){
				ChangeAnimation(4, false, 40);
				mRengeki = true;
				Yokeru = true;
			}
		}
		if (mAnimationIndex == 4 || mAnimationIndex == 6){
			if (mAnimationFrame >= mAnimationFrameSize){
				ChangeAnimation(0, true, 60);
				mRengeki = false;
				mAttack = false;
				mAttackS = false;
				mStop = false;
				Yokeru = false;
			}
		}

		if (CKey::Once(VK_SPACE)){
			if (mAnimationIndex == 0 || mAnimationIndex == 1){
				ChangeAnimation(3, false, 40);
				mPosition = CVector(0.0f, 0.0f, 1.0f)*mMatrix;
				mAttack = true;
				mStop = true;
			}
			//CXCharacter::Update();
		}
		if (Yokeru == true){
			if (CKey::Once('A')){
				mPosition = CVector(2.0f, 0.0f, 0.0f)*mMatrix;
				ChangeAnimation(0, true, 60);
				mStop = false;
				Yokeru = false;
				mAttack = false;
				mAttackS = false;
				mRengeki = false;

			}
			if (CKey::Once('D')){
				mPosition = CVector(-2.0f, 0.0f, 0.0f)*mMatrix;
				ChangeAnimation(0, true, 60);
				mStop = false;
				Yokeru = false;
				mAttack = false;
				mAttackS = false;
				mRengeki = false;

			}
		}
		else{
			if (mStop == false && Back == false&&Down==false){
				if (CKey::Push('W')){
					ChangeAnimation(1, true, 60);
					mPosition = CVector(0.0f, 0.0f, 0.2f + kasoku)*mMatrix;
					if (hayasa > 0){
						hayasa--;
					}
					else if (CKey::Push('B') && kasoku<0.5f){
						kasoku += SPEED;
						hayasa = KASOKUMAX;
					}
					else if (kasoku > 0.0f){
						kasoku -= GENSOKU;
					}
				}
				else
				{
					kasoku = STOP;
					if (mAnimationIndex == 1){
						ChangeAnimation(0, true, 60);
					}
				}
				if (CKey::Push('S')){
					ChangeAnimation(1, true, 60);
					mPosition = CVector(0.0f, 0.0f, -0.2f)*mMatrix;
				}

				if (CKey::Push('A')){
					kasoku = STOP;
					mPosition = CVector(0.2f + kasokuB, 0.0f, 0.0f)*mMatrix;
					if (hayasa > 0){
						hayasa--;
					}
					else if (CKey::Push('B') && kasokuB<0.4f){
						kasokuB += SPEED;
						hayasa = KASOKUMAX;
					}
					else if (kasokuB > 0.0f){
						kasokuB -= GENSOKU;
					}
				}
				else
				{
					kasokuB = STOP;
				}
				if (CKey::Push('D')){
					kasoku = STOP;
					mPosition = CVector(-0.2f + kasokuC, 0.0f, 0.0f)*mMatrix;
					if (hayasa > 0){
						hayasa--;
					}
					else if (CKey::Push('B') && kasokuC >= -0.4){
						kasokuC -= SPEED;
						hayasa = KASOKUMAX;
					}
					else if (kasokuC < 0.0f){
						kasokuC += GENSOKU;
					}
				}

				else
				{
					kasokuC = STOP;
				}
			}
			if (Back == true){
				ChangeAnimation(2, false, 60);
				mPosition = CVector(0.0f, 0.0f, -0.5f)*mMatrix;
				mStop = false;
			}
			if (X > 0){
				X--;
			}
			if (X == 0){
				Back = false;
			}
			if (mAnimationFrame >= mAnimationFrameSize&&mAnimationIndex == 2){
				ChangeAnimation(0, true, 60);
			}
			if (Down == true){
				ChangeAnimation(11, false, 60);
				if (PHP < 1 && mAnimationFrame>50 && mAnimationIndex == 11){
					mAnimationFrame = 60;
					mStop = false;
				}
			}
			if (Y > 0){
				mPosition = CVector(0.0f, 0.0f, -2.0f)*mMatrix;
				Y--;
			}
			if (Y == 0 && mAnimationFrame >= mAnimationFrameSize&&PHP > 0&& mAnimationIndex == 11){

				Down = false;
			}
			if (mAnimationFrame >= mAnimationFrameSize&&mAnimationIndex == 11){
				ChangeAnimation(0, true, 60);
				mStop = false;
			}
			if (mLook == false && Back == false && Down == false){
				if (CKey::Push('J')){
					mRotation.mY += SITEN;
				}
				if (CKey::Push('L')){
					mRotation.mY -= SITEN;
				}
			}
			if (mInSight == false){
				mLook = false;
			}
			if (mLook == true){
				if (CKey::Once('Q')){
					mLook = false;
					L = 1;
					if (L > 0){
						L--;
					}
				}
			}
			if (mInSight == true&&L==0){
				if (CKey::Once('Q')){
					mLook = true;
				}
				if (mLook == true){
					CVector dir = CXEnemy::mEnemy->mPosition - mPosition;
					//左方向のベクトルを求める
					CVector left = CVector(1.0f, 0.0f, 0.0f)*
						CMatrix().RotateY(mRotation.mY);
					CVector right = CVector(-1.0f, 0.0f, 0.0f)*
						CMatrix().RotateY(mRotation.mY);
					//左右の回転処理
					if (left.Dot(dir) > 0.0f){
						mRotation.mY += 1.0f;
					}
					else if (left.Dot(dir) < 0.0f){
						mRotation.mY -= 1.0f;
					}
				}
				mInSight = false;
			}
		}
		if (CKey::Once('T') && mHyuu == true && Back == false && Down == false){
			mVelovcityJump = JUMPV0;
			mHyuu = false;
		}
	}
	mVelovcityJump = mVelovcityJump - G;
	mPosition.mY = mPosition.mY + mVelovcityJump;
	CXCharacter::Update();
}
void CXPlayer::Init(CModelX*model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.mpCombinedMatrix = &mpCombinesMatrix[8];
	//頭
	mColSphereHead.mpCombinedMatrix = &mpCombinesMatrix[11];
	//剣
	mColSphereSword.mpCombinedMatrix = &mpCombinesMatrix[21];

	mAshi1.mpCombinedMatrix = &mpCombinesMatrix[25];

	mAshi2.mpCombinedMatrix = &mpCombinesMatrix[30];
}

void CXPlayer::Collision(CCollider*mp, CCollider*yp){
//自身のコライダの判定タイプ
	switch (mp->mType){
	case CCollider::ESPHERE://球コライダ
		if (mp->mTag == !CCollider::ESIGHT){
			if (yp->mType == CCollider::ETRIANGLE){
				CVector adjust;//調整用ベクトル
				if (CCollider::CollisionTriangleSphere(yp, mp, &adjust)){
					mVelovcityJump = 0;
					//位置の更新
					mPosition = mPosition - adjust*-1;
					mHyuu = true;
					//行列の更新
					CXCharacter::Update();
				}
			}
		}
	}
	if (mp->mType == CCollider::ESPHERE&&yp->mType == CCollider::ESPHERE){
		if (CCollider::Collision(mp, yp)){
			if (mp->mTag == CCollider::ESIGHT){
				switch (yp->mpParent->mTag){
				case EENEMY:
					if (yp->mTag == CCollider::EEBODY){
						mInSight = true;
					}
				}
			}
			if (mp->mTag == CCollider::EPBODY){
				switch (yp->mpParent->mTag){
				case EENEMY:
					if (yp->mTag == CCollider::EESWORD&&CXEnemy::mEAttack == true || yp->mTag == CCollider::EEBODY&&CXEnemy::mEAttack == true){
						Back = true;
						CXEnemy::mEAttack = false;
						PHP -= DAMEGE;
						X += BACK;
					}
					if (yp->mTag == CCollider::EESWORD&&CXEnemy::mEAttackS == true){
						X = 0;
						Down = true;
						CXEnemy::mEAttackS = false;
						PHP -= DAMEGES;
						Y += BACKS;
					}

				}
			}
		}
	}
}