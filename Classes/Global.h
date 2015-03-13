#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include"Player.h"	
#include "TouchLayer.h"
#include "GameMap.h"
#include "Singleton.h"
#include "HelloWorldScene.h"

class Player;
class TouchLayer;
class HelloWord;
class Global : public Singleton<Global>
{
public:
	Global(void);
	~Global(void);
	TouchLayer *touchLayer;
	Player *player;
	GameMap *gameMap;
	HelloWord *helloWord;
	bool isMusicOn;
	bool isEffectOn;
	int gameStage;
	int IQ;
	
};
#define sGlobal Global::instance()

#endif
