#ifndef CACTION_H
#define CACTION_H

#include "CScene.h"
#include"CXPlayer.h"
#include"CXEnemy.h"
#include"CKey.h"
#include"CMap.h"
#include"CEye.h"
#include"CSound.h"
/*
ゲームのシーン
*/
class CAction : public CScene {
public:
	CEye mEye;
	CXPlayer Player;
	CXEnemy2*mEnemy2;
	//CXEnemy3 *mEnemy3;
	static CModel mCube2;
	static CModel mPlane;
	~CAction();
	CAction(){};
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//キャラクタのインスタンス
	CMap*mMap;
	void Start2D(float left, float right, float bottom, float top);
	//2D描画終了
	void End2D();
	char buf[10];
	EScene GetNextScene();

};

#endif