#ifndef __myANIMATIONMANAGER_H__
#define __myANIMATIONMANAGER_H__
#include "Singleton.h"
#include "cocos2d.h"
USING_NS_CC;

class myAnimationManager :public Singleton<myAnimationManager>{
public:
	myAnimationManager(void);
	~myAnimationManager(void);
	bool initAnimationMap();
	Animation * getAnimation(int key);
	Animation * createAnimation(int key);
	Animate* createAnimate(const char* key);
	SpriteFrame * getSpritFrame(int key);
protected:
	Animation *createHeroAnimationByKey(int key);

};

#define sAnimationMgr myAnimationManager::instance();
#endif