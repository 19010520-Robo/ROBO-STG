#include"CTitle.h"
#include"CKey.h"
#include"CSceneGame.h"

void CTitle::Init() {
	//テクスチャファイルを読み込む
	//フォントの設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	//シーンの設定
	mScene = ETITLE;
}
void CTitle::Update() {
	//文字列の描画
	Start2D(0, 800, 0, 600);

	CText::DrawString("SWORD",400,300,30,30);
	End2D();

	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム
		mScene = EACTION;
	}
}
//次のシーンの取得
CScene::EScene CTitle::GetNextScene() {
	return mScene;
}