#include "Player.h"
#include "Global.h"
#include "myAnimationManager.h"
#include "GameConstants.h"
Player::Player(void){
	sGlobal->player = this;
}
Player::~Player(void){


}
Node *Player::createNode(){
	auto node = Node::create();
	auto hero = Player::create();
	node->addChild(hero);
	return node;
}

bool Player::init(){
	if (!Node::init()){
		return	false;
	}
	_playerPos.x = 200;
	_playerPos.y = 500;

	Vspeed = 5;


	isJumping = false;
	rightActionBegan = false;
	jumpActionBegan = false;
	nomalActionBegan = false;
	leftActionBegan = false;

	_player = Sprite::create("hero/zou1.png");	
	//_player->setScale(1.5);
	myAnimationManager::instance()->initAnimationMap();

	_player->setAnchorPoint(Vec2(0, 0));
	_player->setPosition(_playerPos);
	_player->setTag(1);
	this->addChild(_player);
	scheduleUpdate();
	currentType = nomalStopType;
	return true;

	
}
void Player::playerScale(){

	_player->setScale(1.5);
}
void Player::runMyActionByKey(int key){
	if (key == HeroNomalKey){
		auto animation = myAnimationManager::instance()->getAnimation(HeroNomalKey);
		
		if (animation){
			auto action = Sequence::create(Animate::create(animation),NULL);
			action->setTag(HeroNomalKey);
			_player->runAction(action);
		}
	}

	if (key == HeroRightKey){
		auto animation = myAnimationManager::instance()->getAnimation(HeroRightKey);
		if (animation){
			auto action = Sequence::create(Animate::create(animation), NULL);
			action->setTag(HeroRightKey);
			_player->runAction(action);
		}
	}

	if (key == HeroJumpKey){
		auto animation = myAnimationManager::instance()->getAnimation(HeroJumpKey);
		if (animation){
			auto action = Sequence::create(Animate::create(animation), NULL);
			action->setTag(HeroJumpKey);
			_player->runAction(action);
		}
	}

	if (key == HeroLeftKey){


		auto animation = myAnimationManager::instance()->getAnimation(HeroLeftKey);
		if (animation){
			auto action = Sequence::create(Animate::create(animation), NULL);
			action->setTag(HeroLeftKey);
			_player->runAction(action);
		}
	}
}
void Player::stopMyActionByKey(int key){
	 
	if (key == HeroNomalKey){
		_player->stopActionByTag(HeroNomalKey);
	}
}



void Player::playerJump(){

	if (isJumping){
		return;
	}
	if (currentType!=jumpUpType){
		_player->stopAllActions();
		runMyActionByKey(HeroJumpKey);
		currentType = jumpUpType;
	}
	if (!checkUpLeft(_playerPos) && !checkUpRight(_playerPos)){
		for (int i = 12; i > 0; --i){
			_playerPos.y += 3 * i;
			auto dely = DelayTime::create(3);
			this->runAction(dely);
			if (checkUpLeft(_playerPos) || checkUpRight(_playerPos)){
				break;
			}
			isJumping = true;
			_player->setPosition(_playerPos);
			
		}

	}
	isJumping = false;

}

void Player::playerGlid(){

	log("now is gliding");

}
void Player::playerPreshoot(){
	log("now is preshooting");


}
void Player::playerRession(){

	log("now is recessioning");

}
void Player::update(float dt){
	
	if (true){
		if (!checkDownLeft(_playerPos) && !checkDownRight(_playerPos)
			){
			isJumping = true;
			_playerPos.y -= 5;
		}
	}
	
	if (checkDownLeft(_playerPos) && checkDownRight(_playerPos)){
	
		isJumping = false;
	}
	
	
	
	if (isLeftMove){
	     
		if (currentType !=leftWalkType){

			if (!_player->isFlippedX())
				_player->setFlippedX(true);
			
			_player->stopAllActions();	
			runMyActionByKey(HeroLeftKey);	
			currentType = leftWalkType;
		}
		if (!checkLeftUp(_playerPos) && !checkLeftDown(_playerPos)){
			if (_playerPos.x>=5)
			_playerPos.x -= Vspeed;
		}
	}


	//查看向右移动是否可以

	if (isRightMove){
		if (currentType !=rightWalkType){

			if (_player->isFlippedX()){
				_player->setFlippedX(false);
			}
			currentType = rightWalkType;
			_player->stopAllActions();
			runMyActionByKey(HeroRightKey);
		/*	rightActionBegan = true;
			nomalActionBegan = false;
			leftActionBegan = false;
			jumpActionBegan = false;*/
		}
		if (!checkRightUp(_playerPos) && !checkRightDown(_playerPos)){
			//当主角大于一定的值时候让地图移动
			if (_playerPos.x<300)
			_playerPos.x += Vspeed;
			else
			{
				sGlobal->gameMap->setCentralMap(-Vspeed);
			}
		}
	}


	if (currentType != nomalStopType &&!isLeftMove&&!isRightMove&&!isJumping){
		_player->stopAllActions();
		runMyActionByKey(HeroNomalKey);
		currentType = nomalStopType;
	/*	nomalActionBegan = true;
		rightActionBegan = false;
		leftActionBegan = false;
		jumpActionBegan = false;*/
	}
	_player->setPosition(_playerPos);

}


bool Player::checkLeftUp(Vec2 playerPos){
	auto tempPos = playerPos;
	tempPos.x = playerPos.x - 3;
	tempPos.y = playerPos.y + _player->getContentSize().height-3;
	tempPos.x -= sGlobal->gameMap->gameMapPos.x;
	tempPos.y -= sGlobal->gameMap->gameMapPos.y;
	if (tempPos.y >(sGlobal->gameMap->_tiledMap->getMapSize().height*sGlobal->gameMap->_tiledMap->getTileSize().height - 20) || tempPos.y<sGlobal->player->getContentSize().height)
	{
		return false;
	}
	else
	{
		Vec2 tileCoord = sGlobal->gameMap->tileCoordFromPosition(tempPos);
		auto _collidable = sGlobal->gameMap->_tiledMap->getLayer("collidable");
		int tileGid = _collidable->getTileGIDAt(tileCoord);
		if (tileGid > 0){
			Value prop = sGlobal->gameMap->
				_tiledMap->getPropertiesForGID(tileGid);
			ValueMap propValuMap = prop.asValueMap();
			std::string collision = propValuMap["Collidable"].asString();
			if (collision == "true"){
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			return false;
		}
	}


}
bool Player::checkLeftDown(Vec2 playerPos){
	auto tempPos = playerPos;
	tempPos.x = playerPos.x - 3; 
	tempPos.y = playerPos.y +3;
	tempPos.x -= sGlobal->gameMap->gameMapPos.x;
	tempPos.y -= sGlobal->gameMap->gameMapPos.y;
	if (tempPos.y >(sGlobal->gameMap->_tiledMap->getMapSize().height*sGlobal->gameMap->_tiledMap->getTileSize().height - 20) || tempPos.y<sGlobal->player->getContentSize().height)
	{
		return false;
	}
	else
	{
		Vec2 tileCoord = sGlobal->gameMap->tileCoordFromPosition(tempPos);
		auto _collidable = sGlobal->gameMap->_tiledMap->getLayer("collidable");
		int tileGid = _collidable->getTileGIDAt(tileCoord);
		if (tileGid > 0){
			Value prop = sGlobal->gameMap->
				_tiledMap->getPropertiesForGID(tileGid);
			ValueMap propValuMap = prop.asValueMap();
			std::string collision = propValuMap["Collidable"].asString();
			if (collision == "true"){
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			return false;
		}
	}
	 
}
bool Player::checkRightUp(Vec2 playerPos){
	auto tempPos = playerPos;
	tempPos.x = playerPos.x + _player->getContentSize().width + 3;
	tempPos.y = playerPos.y + _player->getContentSize().height - 3;
	tempPos.x -= sGlobal->gameMap->gameMapPos.x;
	tempPos.y -= sGlobal->gameMap->gameMapPos.y;
	if (tempPos.y >(sGlobal->gameMap->_tiledMap->getMapSize().height*sGlobal->gameMap->_tiledMap->getTileSize().height - 20)||tempPos.y<sGlobal->player->getContentSize().height)
	{
		return false;
	}
	else
	{
		Vec2 tileCoord = sGlobal->gameMap->tileCoordFromPosition(tempPos);
		auto _collidable = sGlobal->gameMap->_tiledMap->getLayer("collidable");
		int tileGid = _collidable->getTileGIDAt(tileCoord);
		if (tileGid > 0){
			Value prop = sGlobal->gameMap->
				_tiledMap->getPropertiesForGID(tileGid);
			ValueMap propValuMap = prop.asValueMap();
			std::string collision = propValuMap["Collidable"].asString();
			if (collision == "true"){
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			return false;
		}
	}

}
bool Player::checkRightDown(Vec2 playerPos){
	auto tempPos = playerPos;
	tempPos.x = playerPos.x + _player->getContentSize().width + 3;
	tempPos.y = playerPos.y +3;
	tempPos.x -= sGlobal->gameMap->gameMapPos.x;
	tempPos.y -= sGlobal->gameMap->gameMapPos.y;
	/*log("gameMapPos.x :::: %f", sGlobal->gameMap->gameMapPos.x);
	log("tempPos.x :::%f", sGlobal->gameMap->getScaleX());*/
	if (tempPos.y >(sGlobal->gameMap->_tiledMap->getMapSize().height*sGlobal->gameMap->_tiledMap->getTileSize().height - 20) || tempPos.y<sGlobal->player->getContentSize().height)
	{
		return false;
	}
	else
	{
		Vec2 tileCoord = sGlobal->gameMap->tileCoordFromPosition(tempPos);
		auto _collidable = sGlobal->gameMap->_tiledMap->getLayer("collidable");
		int tileGid = _collidable->getTileGIDAt(tileCoord);
		if (tileGid > 0){
			Value prop = sGlobal->gameMap->
				_tiledMap->getPropertiesForGID(tileGid);
			ValueMap propValuMap = prop.asValueMap();
			std::string collision = propValuMap["Collidable"].asString();
			if (collision == "true"){
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			return false;
		}
	}
}
bool Player::checkUpLeft(Vec2 playerPos){
	auto tempPos = playerPos;
	tempPos.x = playerPos.x + 3;
	tempPos.y = playerPos.y + _player->getContentSize().height+3;
//	log("...tempos X%f tempos Y %f", tempPos.x, tempPos.y);
	//log("..................:::%f", (sGlobal->gameMap->_tiledMap->getMapSize().height*sGlobal->gameMap->_tiledMap->getTileSize().height - 32));
	tempPos.x -= sGlobal->gameMap->gameMapPos.x;
	tempPos.y -= sGlobal->gameMap->gameMapPos.y;
	if (tempPos.y >(sGlobal->gameMap->_tiledMap->getMapSize().height*sGlobal->gameMap->_tiledMap->getTileSize().height - 20))
	{ 
		return false;
	}
	else
	{
	Vec2 tileCoord = sGlobal->gameMap->tileCoordFromPosition(tempPos);
	auto _collidable = sGlobal->gameMap->_tiledMap->getLayer("collidable");
	int tileGid = _collidable->getTileGIDAt(tileCoord);
	if (tileGid > 0){
		Value prop = sGlobal->gameMap->
			_tiledMap->getPropertiesForGID(tileGid);
		ValueMap propValuMap = prop.asValueMap();
		std::string collision = propValuMap["Collidable"].asString();
		if (collision == "true"){
			return true;
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
}

}
bool Player::checkUpRight(Vec2 playerPos){

	auto tempPos = playerPos;
	tempPos.x = playerPos.x + _player->getContentSize().width-3;
	tempPos.y = playerPos.y + _player->getContentSize().height+3;
	tempPos.x -= sGlobal->gameMap->gameMapPos.x;
	tempPos.y -= sGlobal->gameMap->gameMapPos.y;
	if (tempPos.y >(sGlobal->gameMap->_tiledMap->getMapSize().height*sGlobal->gameMap->_tiledMap->getTileSize().height - 20))
	{
		return false;
	}
	else
	{
		Vec2 tileCoord = sGlobal->gameMap->tileCoordFromPosition(tempPos);
		auto _collidable = sGlobal->gameMap->_tiledMap->getLayer("collidable");
		int tileGid = _collidable->getTileGIDAt(tileCoord);
		if (tileGid > 0){
			Value prop = sGlobal->gameMap->
				_tiledMap->getPropertiesForGID(tileGid);
			ValueMap propValuMap = prop.asValueMap();
			std::string collision = propValuMap["Collidable"].asString();
			if (collision == "true"){
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			return false;
		}
	}
}
bool Player::checkDownLeft(Vec2 playerPos){
	auto tempPos = playerPos;
	tempPos.x = playerPos.x +3;
	tempPos.y = playerPos.y-3;
	tempPos.x -= sGlobal->gameMap->gameMapPos.x;
	tempPos.y -= sGlobal->gameMap->gameMapPos.y;
	if ((tempPos.y < 20) || tempPos.y >(sGlobal->gameMap->_tiledMap->getMapSize().height*sGlobal->gameMap->_tiledMap->getTileSize().height - 20))
	{
		return false;
	}
	else
	{
		Vec2 tileCoord = sGlobal->gameMap->tileCoordFromPosition(tempPos);
		auto _collidable = sGlobal->gameMap->_tiledMap->getLayer("collidable");
		int tileGid = _collidable->getTileGIDAt(tileCoord);
		if (tileGid > 0){
			Value prop = sGlobal->gameMap->
				_tiledMap->getPropertiesForGID(tileGid);
			ValueMap propValuMap = prop.asValueMap();
			std::string collision = propValuMap["Collidable"].asString();
			if (collision == "true"){
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			return false;
		}
	}

}
bool Player::checkDownRight(Vec2 playerPos){
	auto tempPos = playerPos;
	tempPos.x = playerPos.x + _player->getContentSize().width-3;
	tempPos.y = playerPos.y-3;
	tempPos.x -= sGlobal->gameMap->gameMapPos.x;
	tempPos.y -= sGlobal->gameMap->gameMapPos.y;	
	if ((tempPos.y < 20) || tempPos.y >(sGlobal->gameMap->_tiledMap->getMapSize().height*sGlobal->gameMap->_tiledMap->getTileSize().height - 20))
	{
		return false;
	}
	else
	{
		Vec2 tileCoord = sGlobal->gameMap->tileCoordFromPosition(tempPos);
		auto _collidable = sGlobal->gameMap->_tiledMap->getLayer("collidable");
		int tileGid = _collidable->getTileGIDAt(tileCoord);
		if (tileGid > 0){
			Value prop = sGlobal->gameMap->
				_tiledMap->getPropertiesForGID(tileGid);
			ValueMap propValuMap = prop.asValueMap();
			std::string collision = propValuMap["Collidable"].asString();
			if (collision == "true"){
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			return false;
		}
	}

}



