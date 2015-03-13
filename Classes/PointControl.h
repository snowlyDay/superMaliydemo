#ifndef __POINTCONTROLK_H__
#define __POINTCONTROLK_H__

#include "cocos2d.h"
USING_NS_CC;
class PointControl :public Layer{
	PointControl();
	~PointControl();

public:
	static  Scene*  createScene();
	virtual bool init();
	CREATE_FUNC(PointControl);

private:
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	void drawDian();
	void addColor();   
	void isCircle(Point dian, Point temp);
	void removeNode(int count);
public:
	 
private	:
	int	radius = 50;
	std::vector<Point>  data;
	Point dian[4][4];
	Point deletD = Vec2(0, 0);

	bool  inRound[4][4];
	std::vector <Point>  dianIn;
	MotionStreak *streak;
	Sprite * star;
	int  a[10];
	int  jump[10] ;
	int  preshoot[20];

	bool isJump = true;
	bool isGlid = true;

	bool isPreshoot = true;
	bool isRecession = true;
	

};
#endif