#include "GameScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;


Scene *GameScene::createScene(){
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return	 scene;
}

bool GameScene::init(){
	if (!Layer::init()){
		return false;

	}
	
	Node *_NodeScene = HelloWorld::createScene();

	//Director::getInstance()->runWithScene(_myScene);
	//_NodeScene->setAnchorPoint(Vec2(0, 0));
	//_myScene->setVisible(false);
	

	//_NodeScene->setVisible(false);
	//_NodeScene->setRotation(25);
	//_NodeScene->_mysca
	//_NodeScene->getChildByTag(1)->setScale(2);
	this->addChild(_NodeScene);



	return true;
}