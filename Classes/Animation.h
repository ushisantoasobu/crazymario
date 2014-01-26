//
//  Animation.h
//  crazymario
//
//  Created by 是永 誠 on 2014/01/26.
//
//

#ifndef __crazymario__Animation__
#define __crazymario__Animation__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_ACTION 1001

class Animation
{
public:
    static CCFiniteTimeAction* vibrationAnimation();
    
    static CCFiniteTimeAction* resultAnimation(CCObject* target, SEL_CallFunc selector);
    
    //  マリオアニメーション
    static CCFiniteTimeAction* marioAction();
    // ジャンプする敵
    static CCFiniteTimeAction* enemyJumpAction(int moveX, int moveY);
    // 水平アニメーションをする敵
    static CCFiniteTimeAction* enemyMoveAction();
};

#endif /* defined(__crazymario__Animation__) */
