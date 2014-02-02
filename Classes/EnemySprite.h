#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
USING_NS_CC;

/**
 * BY ムンク
 *
 */

class Enemy : public CCSprite {
private:
    int x;
    int y;
public:
    Enemy();
    CCSprite* createEnemy(int tagId, int x, int y);
    CCSprite* createMovingEnemy(int tagId, int enemyMoveTag, int x, int y);
    CCSprite* createJumpingEnemy(int tagId, int enemyJumpTag, int x, int y);
};

#endif