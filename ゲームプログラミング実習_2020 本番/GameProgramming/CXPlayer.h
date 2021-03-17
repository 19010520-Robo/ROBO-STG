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
	CCollider mColSphereBody;  //��
	CCollider mColSphereHead;  //��
	CCollider mColSphereSword; //��
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
	//�f�t�H���g�R���X�g���N�^
	CXPlayer();
	//�X�V����
	void Update();
	void KeyProc();
	void Init(CModelX*model);
	void Collision(CCollider*mp, CCollider*yp);
	static CXPlayer*mPlayer;
	CXPlayer*mpPoint;//�ڎw���|�C���g
	float kasoku;
	int hayasa;
	float kasokuB;
	float kasokuC;
	static int mPLife;
	bool mStop;
	CXPlayer*ENEMY;
};


#endif
