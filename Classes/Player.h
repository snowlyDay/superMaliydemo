#ifndef __PLAYERr_H__
#define __PLAYERr_H__

#include "cocos2d.h"
USING_NS_CC;

class Player :public Node{
	Player();
	~Player();

public:
	static Node *createNode();
	virtual bool init();
	CREATE_FUNC(Player);
	
	void playerJump();
	void playerGlid();
	void playerPreshoot();
	void playerRession();
	
	void playerScale();
	void update(float dt);
	void runMyActionByKey(int key);
	void stopMyActionByKey(int key);
	bool isUpMove = false;
	bool isDownMove = false;
	bool isLeftMove = false;
	bool isRightMove = false;

private:
	
	int currentType;
	bool leftActionBegan = false;
	bool rightActionBegan = false;
	bool  nomalActionBegan = false;
	bool jumpActionBegan = false;



private:
	Sprite *_player;
	Point  _playerPos;
	bool checkLeftUp(Vec2 pos);
	bool checkLeftDown(Vec2 pos);
	bool checkRightUp(Vec2 pos);
	bool checkRightDown(Vec2 pos);
	bool checkUpLeft(Vec2 pos);
	bool checkUpRight(Vec2 pos);
	bool checkDownLeft(Vec2 pos);
	bool checkDownRight(Vec2 pos);
	bool isJumping=false;
	int Vspeed;
	int Hspeed;

};
#endif