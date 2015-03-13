#include "TouchLayer.h"
#include "Global.h"
#include "GameConstants.h"
USING_NS_CC;

TouchLayer::TouchLayer(void){
	sGlobal->touchLayer = this;
}
TouchLayer::~TouchLayer(void){

}
Scene* TouchLayer::createScene(){

	auto scene = Scene::create();
	auto layer = TouchLayer::create();
	scene->addChild(layer);

	return scene;

}

bool TouchLayer::init(){
	if (!Layer::init()){
		return false;
	}
	 auto dispatcher =Director::getInstance()->getEventDispatcher();

	 auto listener = EventListenerTouchOneByOne::create();
	 listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
	 listener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMove, this);
	 listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnd, this);
	 dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	 auto Keylistener = EventListenerKeyboard::create();
	 Keylistener->onKeyPressed = CC_CALLBACK_2(TouchLayer::onKeyPressed, this);
	 Keylistener->onKeyReleased = CC_CALLBACK_2(TouchLayer::onKeyReleased, this);

	 _eventDispatcher->addEventListenerWithSceneGraphPriority(Keylistener, this);
	 myScale = 1;
	 schedule(schedule_selector(TouchLayer::updateCustom), 0.005f, kRepeatForever, 0);
	 return true;
}

void TouchLayer::updateCustom(float dt)
{ 
	if (myScale >= 1.5){
		issuofang = false;
	//	log("scale d d a %f", myScale);
		myScale = 1.5;
	}
	if (myScale <= 1.0){
		iskuoda = false;
		myScale = 1;
	}
	if (issuofang){
		myScale += 0.01;
		

		auto anchorX = (sGlobal->gameMap->getScaleX()*sGlobal->player->getChildByTag(1)->getPositionX()) / sGlobal->gameMap->getBoundingBox().size.width;
		auto anchorY = (sGlobal->gameMap->getScaleY()*sGlobal->player->getChildByTag(1)->getPositionY())/ sGlobal->gameMap->getBoundingBox().size.height; 
	
	//	log("  kuadazhihou %f anchork dd  x%f  yxx^%f  jjj%f", sGlobal->gameMap->getScaleX()*sGlobal->player->getChildByTag(1)->getPositionX(), sGlobal->player->getChildByTag(1)->getPositionX(), sGlobal->gameMap->getBoundingBox().size.height, anchorX);
		
		sGlobal->gameMap->setAnchorPoint(Vec2(anchorX, anchorY));
		
		sGlobal->gameMap->setScale(myScale);
	//	log("getpos X %f   getpos Y %f", sGlobal->gameMap->getPositionX(), sGlobal->gameMap->getPositionY());
	//	sGlobal->player->setAnchorPoint(Vec2(0.5, 0.5));
		//sGlobal->player->setScale(myScale);

	}
	if (iskuoda){
		myScale -= 0.1;
	
	}
	auto anchorX = (sGlobal->gameMap->getScaleX()*sGlobal->player->getChildByTag(1)->getPositionX()) / sGlobal->gameMap->getBoundingBox().size.width;
	auto anchorY = (sGlobal->gameMap->getScaleY()*sGlobal->player->getChildByTag(1)->getPositionY()) / sGlobal->gameMap->getBoundingBox().size.height;

	//	log("  kuadazhihou %f anchork dd  x%f  yxx^%f  jjj%f", sGlobal->gameMap->getScaleX()*sGlobal->player->getChildByTag(1)->getPositionX(), sGlobal->player->getChildByTag(1)->getPositionX(), sGlobal->gameMap->getBoundingBox().size.height, anchorX);

	sGlobal->gameMap->setAnchorPoint(Vec2(anchorX, anchorY));

	sGlobal->gameMap->setScale(myScale);
	
}


bool TouchLayer::onTouchBegan(Touch *pTouch, Event *even){

	return	 true;
}

void TouchLayer::onTouchMove(Touch *pTouch, Event *even){



}
void TouchLayer::onTouchEnd(Touch *pTouch, Event *even){


}

void TouchLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*KEY_LEFT_ARROW,
		KEY_RIGHT_ARROW,
		KEY_UP_ARROW,
		KEY_DOWN_ARROW,*/
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW){
		sGlobal->player->isLeftMove = true;
	}

//	sGlobal->player->isRightMove = true;
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){
		
		sGlobal->player->isRightMove = true;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW){
		sGlobal->player->playerJump();
		//sGlobal->player->isUpMove = true;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW){
		sGlobal->player->isDownMove = true;
	}
}

void TouchLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW){
		sGlobal->player->isLeftMove = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE){
		
		sGlobal->player->playerScale();
		issuofang = true;
		//sGlobal->player->setAnchorPoint(Vec2(0, 0));
		//sGlobal->player->setScale(1.5);
	//log("pos xx%f,pos yyy %f", sGlobal->gameMap->getPosition().x, sGlobal->gameMap->getPosition().x);
		
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE){
		iskuoda = true;
		//sGlobal->gameMap->setScale(1);
	//log("pos xx%f,pos yyy %f", sGlobal->gameMap->getPosition().x, sGlobal->gameMap->getPosition().x); 
	//	sGlobal->player->setScale(0.5);	

	}

	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){
		
		sGlobal->player->isRightMove = false;

	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW){
		sGlobal->player->isUpMove = false;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW){
		sGlobal->player->isDownMove = false;
	}
	
}