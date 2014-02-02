//
//  Animation.cpp
//  crazymario
//
//  Created by 是永 誠 on 2014/01/26.
//
//

#include "Animation.h"

#define WIN_WIDTH  CCDirector::sharedDirector()->getWinSize().width
#define WIN_HEIGHT CCDirector::sharedDirector()->getWinSize().height

CCFiniteTimeAction* Animation::vibrationAnimation()
{
    CCMoveBy* move1 = CCMoveBy::create(0.03, ccp( -5, 0));
    CCMoveBy* move2 = CCMoveBy::create(0.06, ccp( 10, 0));
    CCMoveBy* move3 = CCMoveBy::create(0.03, ccp( -5, 0));
    CCSequence* moves = CCSequence::create(move1, move2, move3, NULL);
    
    return CCRepeat::create(moves, 2);
}

CCFiniteTimeAction* Animation::resultAnimation(CCObject* target, SEL_CallFunc selector)
{
    CCScaleTo* scaleUp = CCScaleTo::create(0.5, 1);
    CCDelayTime* delay = CCDelayTime::create(1);
    CCCallFunc* func = CCCallFunc::create(target, selector);
    
    return CCSequence::create(scaleUp, delay, func, NULL);
}

/**
 * BY ムンク
 *
 */
CCFiniteTimeAction* Animation::marioAction() {
    CCArray *animFrames = CCArray::create();
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    for(int i = 0; i < 3; i++)
    {
        CCString* fileName = CCString::createWithFormat("mario/mario%d.png", i);
        CCSpriteFrame *frame = cache->spriteFrameByName(fileName->getCString());
        if (!frame)
        {
            CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(fileName->getCString());
            CCRect bounds = CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height);
            frame = CCSpriteFrame::createWithTexture(texture, bounds);
        }
        
        animFrames->addObject(frame);
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
    
    return CCAnimate::create(animation);
}

/**
 * BY ムンク
 *
 */
CCFiniteTimeAction* Animation::enemyJumpAction(int moveX, int moveY) {
    return CCJumpBy::create(5.0, ccp(moveX, moveY), 300, 1);
}
