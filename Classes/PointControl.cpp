#include "PointControl.h"
#include "Global.h"

PointControl::PointControl(){
	 
	 
}
PointControl::~PointControl(){
	 
}
Scene * PointControl::createScene(){

	auto scene = Scene::create();
	auto layer = PointControl::create();
	scene->addChild(layer);
	return scene;
}
bool PointControl::init(){
	\
	if (!Layer::init()){
		return false;

	}

	data.clear();
	  //ming zhong i : 0   j : 1
	//	ming zhong i : 1   j : 1
	//	ming zhong i : 2   j : 1
	jump[0] = 0;
	jump[1] = 1;
	jump[2] = 1;
	jump[3] = 1;
	jump[4] = 2;
	jump[5] = 1;
	isJump = true;

	preshoot[0] = 1;
	preshoot[1] = 0;
	preshoot[2] = 1;
	preshoot[3] = 1;
	preshoot[4] = 1;
	preshoot[5] = 2;
	isPreshoot = true;



	star = Sprite::create("PIC_XX.png");
	star->setPosition(100, 100);
	this->addChild(star);

	streak = MotionStreak::create(0.1f, 0.5, 10, Color3B::GREEN, "steak.png");
	streak->setPosition(star->getPosition()); 
	this->addChild(streak);


	EventListenerTouchOneByOne* _listener_touch = EventListenerTouchOneByOne::create();
	_listener_touch->onTouchBegan = CC_CALLBACK_2(PointControl::onTouchBegan, this);
	_listener_touch->onTouchMoved = CC_CALLBACK_2(PointControl::onTouchMoved, this);
	_listener_touch->onTouchEnded = CC_CALLBACK_2(PointControl::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener_touch, this);
	
	drawDian();

	return true;

}
bool PointControl::onTouchBegan(Touch *touch, Event *event){
	auto touchLocation = touch->getLocation();
	// 设置位置
	streak->reset();
	star->setPosition(touchLocation);
	streak->setPosition(star->getPosition());


	this->removeChildByTag(1);
	
	data.push_back(touchLocation);
	

	return true;
}
void PointControl::onTouchMoved(Touch *touch, Event *event){
	auto touchLocation = touch->getLocation();
	touchLocation = this->convertToNodeSpace(touchLocation);

	Vec2 delta = touch->getDelta();

	// 设置位置
	star->setPosition(star->getPosition() + delta);
	streak->setPosition(star->getPosition());

	Point nextPoint = touch->getLocationInView();
	nextPoint = Director::sharedDirector()->convertToGL(nextPoint);

	Point preMovePoint = touch->getPreviousLocationInView();
	preMovePoint = Director::sharedDirector()->convertToGL(preMovePoint);
	//log("in onTouchMvoe check about xand y ,x %f ,y%f", preMovePoint.x, preMovePoint.y);
	float distance = ccpDistance(nextPoint, preMovePoint);
	if (distance > 1){
		
		int d = (int)distance;
		for (int i = 0; i < d; i = i + 5){
			float distanceX = nextPoint.x - preMovePoint.x;
			float distanceY = nextPoint.y - preMovePoint.y;
			float percent = i / distance;
			Point newpoint;
			newpoint.x = preMovePoint.x + (distanceX *percent);
			newpoint.y = preMovePoint.y + (distanceY *percent);
			data.push_back(newpoint);
		}
	}
	//data.push_back(touchLocation);



}
void PointControl::onTouchEnded(Touch *touch, Event *event){
	auto touchLocation = touch->getLocation();
	data.push_back(touchLocation);
	addColor();
	data.clear();
	dianIn.clear();
	deletD = Vec2(0, 0);


}

void PointControl::drawDian(){


	dian[0][0] = Point(600, 200);
	for (int j = 0; j <3; j++){

		for (int i = 1; i < 3; i++)
		{

			dian[j][i].x = dian[j][i - 1].x + radius*2;
			dian[j][i].y = dian[j][i - 1].y;

		}
		dian[j + 1][0].y = dian[j][0].y +  radius*2;
		dian[j + 1][0].x = dian[j][0].x;
	}


	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){

				DrawNode* drawNode = DrawNode::create();
			this->addChild(drawNode);
			drawNode->drawDot(dian[i][j], 5, Color4F::RED);

		}
	}




}

void  PointControl::addColor(){

	for (Vector <Point>::iterator it = data.begin(); it != data.end(); it++){
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				Point temp = *it;//9个点
				isCircle(dian[i][j], temp);

			}
		}
	}

	DrawNode* drawNode = DrawNode::create();
	drawNode->setTag(1);
	this->addChild(drawNode);
	int PointNum = 0;
	for (Vector <Point>::iterator it = dianIn.begin() ; it < dianIn.end(); it++)
	{
		Point temp = *it;
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++){
				if (dian[i][j].x == temp.x&&dian[i][j].y==temp.y){
					log("shoo t %d  %d", i, j);
					PointNum++;
					a[PointNum] = i;
					PointNum++;
					a[PointNum] = j;
				}
			}
		}
		
		/*  1 2 3
		  4 5 6
		  7 8 9*/
		/*Point preTemp = *(it - 1);
		Point temp = *it;
		log("preTemp ::::X%f::Y::%f,temp ::::X:%f,:: Y:%f", preTemp.x, preTemp.y, temp.x, temp.y);
		if (preTemp.x>0&&preTemp.y>0)

			drawNode->drawSegment(preTemp, temp, 5, Color4F(0, 1, 0, 1));
			*/
	}
	if (PointNum==6){

		//向上跳的点的判定
		for (int i = 4; i <= PointNum; i=i+2){
			if (a[i] != a[i - 2]||a[i-1]<a[i-3]){
				isJump = false;
		}
	}
	
	if (isJump){
		log("now is jumping");
		sGlobal->player->playerJump();
	
	}
	

	//向下滑动的判定
	for (int i = 4; i <= PointNum; i = i + 2){
		if (a[i] != a[i - 2] || a[i - 1]>a[i - 3]){
			isGlid = false;
		}
	}
	
	if (isGlid){
		
		sGlobal->player->playerGlid();

	}
	
	//向前冲的点的判定
	for (int i = 3; i <= PointNum; i = i + 2){
		if (a[i] != a[i - 2] || a[i +1]<a[i - 1]){
			isPreshoot = false;
		}
	}
	
	if (isPreshoot){
	
		sGlobal->player->playerPreshoot();
		

	}


	//向后撤的点的判定
	for (int i = 3; i <= PointNum; i = i + 2){
		if (a[i] != a[i - 2] || a[i +1]>a[i - 1]){
			isRecession = false;
		}
	}
	
	if (isRecession){
	
		sGlobal->player->playerRession();
		//return;

	}

	isJump = true;
	isGlid = true;
	isPreshoot = true;
	isRecession = true;


	for (int i = 1; i <= PointNum; i++){
		a[i] = 0;
		}
	}

}


void  PointControl::isCircle(Point dian, Point temp){

	int  origin_X = (int)dian.x;
	int  origin_Y = (int)dian.y;
	int dis_X = (int)(temp.x - origin_X);
	int dis_Y = (int)(temp.y - origin_Y);
	if (sqrt(pow(dis_X, 2) + pow(dis_Y, 2)) < radius){
		if (deletD.x == 0 && deletD.y == 0){
			deletD = dian;
			dianIn.push_back(dian);
		}
		else
		{
			if (deletD.x != dian.x || deletD.y != dian.y){
				deletD = dian;
				dianIn.push_back(dian);
	
			}
		}

	}

}





void PointControl::removeNode(int count){

	for (int i = 1; i <= count; i++)
		this->removeChildByTag(i);
}