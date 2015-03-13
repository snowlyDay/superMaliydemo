#ifndef __TOUCHLAYER_H__
#define __TOUCHLAYER_H__
#include "cocos2d.h"

USING_NS_CC;
class TouchLayer :public Layer{
	 
	TouchLayer();
	~TouchLayer();
public:
	static Scene* createScene();
	virtual bool init();
	void updateCustom(float dt);
	CREATE_FUNC(TouchLayer);


private:
	bool issuofang = false;
	bool iskuoda = false;
	float myScale;
	
	bool onTouchBegan(Touch *pTouch, Event *even);
	void onTouchMove(Touch *pTouch, Event *even);
	void onTouchEnd(Touch *pTouch, Event *even);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
		void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

#endif