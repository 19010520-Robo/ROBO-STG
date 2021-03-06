#ifndef CXPLAYER_H
#define CXPLAYER_H
#include"CEye.h"
#include"CXCharacter.h"
#include"CCollider.h"

class CXPlayer :public CXCharacter{
public:
	static int PHP;
	int X;
	int Y;
	int L;
	float mVelovcityJump;
	CCollider mColSphereBody;  //体
	CCollider mColSphereHead;  //頭
	CCollider mColSphereSword; //剣
	CCollider mAshi1;
	CCollider mAshi2;
	CCollider mSight;
	static bool mLook;
	static bool mInSight;
	static bool mAttack;
	static bool mAttackS;
	static bool mPDeath;
	bool mRengeki;
	bool mHyuu;
	bool mCancel;
	bool Down;
	bool Back;
	bool Yokeru;
	//デフォルトコンストラクタ
	CXPlayer();
	//更新処理
	void Update();
	void Init(CModelX*model);
	void Collision(CCollider*mp, CCollider*yp);
	static CXPlayer*mPlayer;
	CXPlayer*mpPoint;//目指すポイント
	float kasoku;
	int hayasa;
	float kasokuB;
	float kasokuC;
	static int mPLife;
	bool mStop;
	CXPlayer*ENEMY;
};


#endif
