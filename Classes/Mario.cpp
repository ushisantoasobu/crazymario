#include "Mario.h"
#include "Animation.h"

USING_NS_CC;

void Mario::createMario(cocos2d::CCLayer* gameScene, int stageId, int tagId) {
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* marioSprite = CCSprite::create("mario/mario1.png");
    //marioSprite->setContentSize(ccp(50, 50));
    marioSprite->setPosition(ccp( size.width * 0.5, size.height * 0.5 ) );
    marioSprite->setTag(tagId);
    gameScene->addChild(marioSprite);
}

void Mario::moveMario(CCLayer* gameScene, int stageId, int tagId, int marioActionTag) {
    CCSprite* marioSprite = (CCSprite*) gameScene->getChildByTag(tagId);
    marioSprite->setPosition(ccp(marioSprite->getPosition().x + 1, marioSprite->getPosition().y));
    CCAction* marioAction = marioSprite->getActionByTag(marioActionTag);
    CCLog("start");
    if (!marioAction) {
        CCLog("not null");
        CCFiniteTimeAction* action = Animation::marioAction();
        action->setTag(marioActionTag);
        marioSprite->runAction(action);
    }
    CCLog("over");
}

void Mario::jumpMario(CCLayer* gameScene, int stageId, int tagId, int marioJumpTag){
    CCSprite* marioSprite = (CCSprite*) gameScene->getChildByTag(tagId);
    int moveX = 4;
    int moveY = 0;
    marioSprite->runAction(CCJumpBy::create(1.0, ccp(moveX, moveY), 300, 1));
    //marioSprite->setPosition(ccp(marioSprite->getPositionX(), (marioSprite->getPositionY()));
}

