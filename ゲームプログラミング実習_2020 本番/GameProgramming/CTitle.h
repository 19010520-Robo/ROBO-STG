#ifndef CTITLE_H
#define CTITLE_H
#include"CScene.h"
#include"CText.h"

class CTitle:public CScene{
public:
	void Init();
	void Update();
	EScene GetNextScene();
	char buf[10];

};



#endif
