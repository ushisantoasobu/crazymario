#include "EnemySprite.h"
#include "Animation.h"
USING_NS_CC;

Enemy::Enemy(){}

CCSprite* Enemy::createEnemy(int tagId, int x, int y) {
    
    CCSprite* enemySprite = CCSprite::create("item/enemy/enemy1.png");
    enemySprite->setScale(0.5);
    enemySprite->setPosition(ccp( x * 0.1, y * 0.41 ) );
    enemySprite->setTag(tagId);
    return enemySprite;
}

CCSprite* Enemy::createMovingEnemy(int tagId, int enemyMoveTag, int x, int y) {
}

CCSprite* Enemy::createJumpingEnemy(int tagId, int enemyJumpTag, int x, int y) {
    CCSprite* enemySprite = CCSprite::create("item/enemy/enemy1.png");
    enemySprite->setScale(0.5);
    enemySprite->setPosition(ccp( x * 0.8, y * 0.9 ) );
    enemySprite->setTag(tagId);
    
    CCFiniteTimeAction* action = Animation::enemyJumpAction(x, y);
    action->setTag(enemyJumpTag);
    enemySprite->runAction(action);
    return enemySprite;
}