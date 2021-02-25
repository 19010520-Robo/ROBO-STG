#ifndef CXENEMY_H
#define CXENEMY_H


#include"CPoint.h"
#include"CXCharacter.h"
#include"CCollider.h"
class CXEnemy :public CXCharacter{
public:
	int FireCount;
	int EHP;
	int X;
	int Y;
	int Counter;
	int T;
	CCollider mColSphereBody;  //体
	CCollider mColSphereHead;  //頭
	CCollider mColSphereSword0; //剣
	CCollider mSearch;
	CCollider mSearchA;
	CCollider mSearchB;
	int Time;
	static CXEnemy*mEnemy;
	void Init(CModelX*model);
	CXEnemy(CVector position, CVector rotation, CVector scale);
	void Collision(CCollider*m, CCollider*y);
	void Update();
	static int mPointSize;//ポイントの数
	CPoint*mpPoint;//目指すポイント
	int mPointCnt;//ポインタのカウンタ
	//誘導ポイント
	static CPoint *mPoint;
	bool mKAKUNIN;
	bool mSWORD;
	bool mHANTEI;
	bool mKAIHI;
	bool mKnockBack;
	bool mDown;
	bool mHangeki;
	bool mStop;
	static bool mEAttack;
	static bool mEAttackS;
	static bool mDeath;

};

class CXEnemy2 :public CXCharacter{
public:
	CCollider mColSphereBody;  //体
	CCollider mColSphereHead;  //頭
	CCollider mColSphereSword0; //剣
	CCollider mSearch;
	CCollider mSearchA;
	CCollider mSearchB;
	static CXEnemy2*mEnemy2;
	void Init(CModelX*model);
	CXEnemy2(CVector position, CVector rotation, CVector scale);
	void Collision(CCollider*m, CCollider*y);
	void Update();
	static int mPointSize;//ポイントの数
	CPoint*mpPoint;//目指すポイント
	int mPointCnt;//ポインタのカウンタ
	//誘導ポイント
	static CPoint *mPoint;
	bool mKAKUNIN;
	static bool mEncount;
};

//class CXEnemy2 :public CCharacter{
//public:
//	void Update();
//	CXEnemy2();
//	CCollider mBall;
//	int FireCount2;
//	void Collision(CCollider*mm, CCollider*ym);
//	CXEnemy2(CModel*model, CVector position, CVector rotation, CVector scale);
//	CCollider mSearch3;
//	int tyuusen;
//};
//
//class CXEnemy3 :public CCharacter{
//public:
//	void Update();
//	CXEnemy3()
//	{};
//	CCollider mAir;
//	CCollider mSearch2;
//	int FireCount3;
//	CXEnemy3(CModel*model, CVector position, CVector rotation, CVector scale);
//	static int mPointSize;//ポイントの数
//	CPoint*mpPoint;//目指すポイント
//	int mPointCnt;//ポインタのカウンタ
//	//誘導ポイント
//	static CPoint *mPoint;
//	void Collision(CCollider*ms, CCollider*ys);
//	static CXEnemy3*mEnemy3;
//	static bool Senser;
//};
//
//
#endif
