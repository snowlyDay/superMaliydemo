#include "GameMap.h"
#include "Global.h"	
GameMap::GameMap(){
	sGlobal->gameMap = this;
}
GameMap::~GameMap(){


}
Scene *GameMap::createScene(){
	auto scene = Scene::create();
	auto layer = GameMap::create();
	scene->addChild(layer);
	return scene;
}
bool GameMap::init(){
	if (!Layer::init())
	{
		return false;
	}
	gameMapPos.x = 0;
	gameMapPos.y = 0;
	_tiledMap = TMXTiledMap::create("map2.tmx");
	_tiledMap->setAnchorPoint(Vec2(0,0));
	_tiledMap->setPosition(gameMapPos);
	this->addChild(_tiledMap);
	return true;

}
void  GameMap::setCentralMap(float dt){
	gameMapPos.x += dt;
	_tiledMap->setPosition(gameMapPos);
	//_tiledColl = _tiledMap->getLayer("collidable");
	//_tiledColl->setPosition(gameMapPos);
	
}
Vec2 GameMap::tileCoordFromPosition(Vec2 pos){

	int x = pos.x / _tiledMap->getTileSize().width;
	int y = ((_tiledMap->getMapSize().height*_tiledMap->getTileSize().height) - pos.y) / _tiledMap->getTileSize().height;

	return Vec2(x, y);
}