#ifndef CTITLE_H
#define CTITLE_H
#include"CScene.h"
#include"CText.h"
class CTitle:public CScene{
public:
	void Init();
	void Update();
	void Render();
	EScene GetNextScene();
	~CTitle();
};



#endif
