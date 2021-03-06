#include "Mario.h"
#include "Animation.h"

USING_NS_CC;

/**
 * BY ムンク
 *
 */

void Mario::createMario(cocos2d::CCLayer* gameScene, int stageId, int tagId) {
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* marioSprite = CCSprite::create("mario/mario1.png");
    marioSprite->setScale(0.5);
    marioSprite->setAnchorPoint(ccp(0.5, 0.5));
    marioSprite->setPosition(ccp( size.width * 0.1, size.height * 0.41 ) );
    marioSprite->setTag(tagId);
    gameScene->addChild(marioSprite);
}

void Mario::moveMario(CCLayer* gameScene, int stageId, int tagId, int marioActionTag) {
    CCSprite* marioSprite = (CCSprite*) gameScene->getChildByTag(tagId);
    if(!marioSprite){
        return;
    }
    int moveSpeedX = 0.2;
    marioSprite->setPosition(ccp(marioSprite->getPosition().x + moveSpeedX, marioSprite->getPosition().y));
    CCAction* marioAction = marioSprite->getActionByTag(marioActionTag);
    if (!marioAction) {
        CCFiniteTimeAction* action = Animation::marioAction();
        action->setTag(marioActionTag);
        marioSprite->runAction(action);
    }
}

void Mario::jumpMario(CCLayer* gameScene, int stageId, int tagId, int marioJumpTag){
    CCSprite* marioSprite = (CCSprite*) gameScene->getChildByTag(tagId);
    if(!marioSprite){
        return;
    }
    int moveX = 0;
    int moveY = 0;
    marioSprite->runAction(CCJumpBy::create(1.0, ccp(moveX, moveY), 300, 1));
}


/**
 * マリオ死亡アニメーション
 *
 * Created by s-sato on 14/01/26.
 */
void Mario::die(CCLayer* gameScene, int stageId, int tagId, int marioJumpTag){
    gameScene->removeChildByTag(tagId);
    CCParticleSystemQuad* p = CCParticleSystemQuad::create("particle/dead.plist");
    gameScene->addChild(p);
}

