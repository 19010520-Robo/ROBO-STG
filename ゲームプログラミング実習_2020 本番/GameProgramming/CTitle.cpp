#include"CTitle.h"
#include"CKey.h"
void CTitle::Init() {
	//テクスチャファイルを読み込む
	//フォントの設定
	CText::mFont.Load("font.tga");
	//シーンの設定
	mScene = ETITLE;
}
void CTitle::Update() {

	//文字列の描画
	CText::DrawString("SHOOT", -190, 210, 30, 50);
	CText::DrawString("&", 0, 120, 30, 35);
	CText::DrawString("DODGE", -70, 20, 30, 50);
	CText::DrawString("Push ENTER Key", -200, -200, 16, 16);
	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム
		mScene = EGAME;
	}
}
//次のシーンの取得
CScene::EScene CTitle::GetNextScene() {
	return mScene;
}