#ifndef __MARIO_H__
#define __MARIO_H__

#include "cocos2d.h"
USING_NS_CC;

/**
 * BY ムンク
 *
 */

class Mario : public CCSprite {
private:
    CCSprite* mario;
    int x;
    int y;
    //Mario(CCSprite* mario);
public:
    static void createMario(cocos2d::CCLayer* gameScene, int stageId, int tagId);
    static void moveMario(CCLayer* gameScene, int stageId, int tagId, int marioMoveTag);
    static void jumpMario(CCLayer* gameScene, int stageId, int tagId, int marioJumpTag);
    static void die(CCLayer* gameScene, int stageId, int tagId, int marioJumpTag);
    //~Mario();
};

#endif