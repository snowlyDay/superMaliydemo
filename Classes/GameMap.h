#ifndef _GAMEMAPf_H__
#define _GAMEMAPf_H__
#include "cocos2d.h"
USING_NS_CC;
class GameMap :public Layer{
	GameMap();
	~GameMap();
public:
	static Scene * createScene();
	virtual bool init();
	Vec2 tileCoordFromPosition(Vec2 pos);
	TMXTiledMap *_tiledMap;
	TMXLayer *_tiledColl;
	CREATE_FUNC(GameMap);
	Vec2 gameMapPos;
	void setCentralMap(float dt);
private:
	

};

#endif