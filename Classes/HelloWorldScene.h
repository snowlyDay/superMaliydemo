#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
class HelloWorld : public cocos2d::Layer
{
	HelloWorld();
	~HelloWorld();
public:
   
    static cocos2d::Scene* createScene();

  
    virtual bool init();

    CREATE_FUNC(HelloWorld);
public:
	float _myScale;
private:
	Node *_tiledMap;
	Node *_player;
	Node *touchLayer;
	
};

#endif // __HELLOWORLD_SCENE_H__
