#ifndef __GAMESCENE__H
#define __GAMESCENE__H

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public CCLayer {
private:
    float marioPosition;
    enum TagId {
        background = 1,
        crazyMarioSprite = 10,
        crazyMarioMove = 11,
        crazyMarioJump = 12
    };
    
    void makeBackground();
    void moveMario(float fDelta);
    bool checkCollision();
    void gameOver();
    
    bool isJump = false;
    
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameScene);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif
