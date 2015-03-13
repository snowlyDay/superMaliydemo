#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "GameMap.h"
#include "Global.h"	
#include "TouchLayer.h"
#include  "PointControl.h"
USING_NS_CC;

using namespace cocostudio::timeline;
HelloWorld::HelloWorld(){
	//sGlobal->helloWord = this;
}
HelloWorld::~HelloWorld(){
	 
}
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
		
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    return scene;
}


bool HelloWorld::init()
{
   
    if ( !Layer::init() )
    {
        return false;
    }
	_myScale = 1;
	
	_tiledMap = GameMap::createScene();
	this->setAnchorPoint(Vec2(0, 0));
	//_tiledMap->setScale(0.5);
	_tiledMap->setTag(1);
	if (!_tiledMap){
		return false;
	}
	
	this->addChild(_tiledMap);


	_player = Player::createNode();
	this->setAnchorPoint(Vec2(0, 0)); 
	_player->setTag(2);
	_player->setScale(_myScale);
	if (!_player){
		return false;
	}
	
	this->addChild(_player);
    
	touchLayer = TouchLayer::createScene();
	if (!touchLayer){
		return false;
	}
	this->addChild(touchLayer);


	auto controlLayer = PointControl::createScene();
	this->addChild(controlLayer);

	this->setScale(2);
	//this->setScale(2);
    return true;
}
