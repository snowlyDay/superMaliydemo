#include "myAnimationManager.h"
#include "GameConstants.h"
DECLARE_SINGLETON_MEMBER(myAnimationManager);
myAnimationManager::myAnimationManager(void)
{
}


myAnimationManager::~myAnimationManager(void)
{
}


bool myAnimationManager::initAnimationMap(){

	char temp[20];
	sprintf(temp, "%d", HeroNomalKey);
	AnimationCache::sharedAnimationCache()->addAnimation(createHeroAnimationByKey(HeroNomalKey), temp);

	sprintf(temp, "%d", HeroJumpKey);
	AnimationCache::sharedAnimationCache()->addAnimation(createHeroAnimationByKey(HeroJumpKey), temp);

	sprintf(temp, "%d", HeroLeftKey);
	AnimationCache::sharedAnimationCache()->addAnimation(createHeroAnimationByKey(HeroLeftKey), temp);

	sprintf(temp, "%d", HeroRightKey);
	AnimationCache::sharedAnimationCache()->addAnimation(createHeroAnimationByKey(HeroRightKey), temp);
	
	return true;
}

Animation * myAnimationManager::getAnimation(int key){
	  
	char temp[20];
	sprintf(temp, "%d", key);
	return CCAnimationCache::sharedAnimationCache()->animationByName(temp);

}
Animation *myAnimationManager::createHeroAnimationByKey(int key){


	//CCTexture2D *heroTexture = CCTextureCache::sharedTextureCache()->addImage("Hero_image.png");
	CCSpriteFrame *frame0, *frame1, *frame2,*frame3,*frame4;
	Vector<SpriteFrame*> animFrames;


	if (key == HeroNomalKey){
		frame0 = SpriteFrame::create("hero/titui1.png", Rect(0, 0, 48, 48));
		frame1 = SpriteFrame::create("hero/titui2.png", Rect(0, 0, 48, 48));
		frame2 = SpriteFrame::create("hero/titui3.png", Rect(0, 0, 48, 48));
		frame3 = SpriteFrame::create("hero/titui4.png", Rect(0, 0, 48, 48));
		frame4 = SpriteFrame::create("hero/titui5.png", Rect(0, 0, 48, 48));
		animFrames.pushBack(frame0);
		animFrames.pushBack(frame1);
		animFrames.pushBack(frame2);
		animFrames.pushBack(frame3);
		animFrames.pushBack(frame4);
		CCAnimation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f, -1);
		animFrames.clear();
		return animation;

	}
	if (key == HeroJumpKey){
		CCSpriteFrame *frame0, *frame1, *frame2, *frame3, *frame4;
		Vector<SpriteFrame*> animFrames;

		frame0 = SpriteFrame::create("hero/zou1.png", Rect(0, 0, 48, 48));
		frame1 = SpriteFrame::create("hero/zou2.png", Rect(0, 0, 48, 48));
		frame2 = SpriteFrame::create("hero/zou3.png", Rect(0, 0, 48, 48));
		frame3 = SpriteFrame::create("hero/zou4.png", Rect(0, 0, 48, 48));
		frame4 = SpriteFrame::create("hero/zou5.png", Rect(0, 0, 48, 48));
		animFrames.pushBack(frame0);
		animFrames.pushBack(frame1);
		animFrames.pushBack(frame2);
		animFrames.pushBack(frame3);
		animFrames.pushBack(frame4);
		CCAnimation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f, -1);
		animFrames.clear();
		return animation;

	}
	if (key == HeroLeftKey){
		frame0 = SpriteFrame::create("hero/zou1.png", Rect(0, 0, 48, 48));
		frame1 = SpriteFrame::create("hero/zou2.png", Rect(0, 0, 48, 48));
		frame2 = SpriteFrame::create("hero/zou3.png", Rect(0, 0, 48, 48));
		frame3 = SpriteFrame::create("hero/zou4.png", Rect(0, 0, 48, 48));
		frame4 = SpriteFrame::create("hero/zou5.png", Rect(0, 0, 48, 48));
		animFrames.pushBack(frame0);
		animFrames.pushBack(frame1);
		animFrames.pushBack(frame2);
		animFrames.pushBack(frame3);
		animFrames.pushBack(frame4);
		CCAnimation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f, -1);
		animFrames.clear();
		return animation;


	}
	if (key == HeroRightKey){
		frame0 = SpriteFrame::create("hero/zou1.png", Rect(0, 0, 48, 48));
		frame1 = SpriteFrame::create("hero/zou2.png", Rect(0, 0, 48, 48));
		frame2 = SpriteFrame::create("hero/zou3.png", Rect(0, 0, 48, 48));
		frame3 = SpriteFrame::create("hero/zou4.png", Rect(0, 0, 48, 48));
		frame4 = SpriteFrame::create("hero/zou5.png", Rect(0, 0, 48, 48));
		animFrames.pushBack(frame0);
		animFrames.pushBack(frame1);
		animFrames.pushBack(frame2);
		animFrames.pushBack(frame3);
		animFrames.pushBack(frame4);
		CCAnimation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f, -1);
		animFrames.clear();
		return animation;

	}
	
}