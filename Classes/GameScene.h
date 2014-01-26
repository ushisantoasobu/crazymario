#ifndef __GAMESCENE__H
#define __GAMESCENE__H

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public CCLayer {
private:
    float marioPosition;
    enum Tag {
        tag_background,
        tag_crazyMario,
    };
    
    void makeBackground();
    void moveMario(float fDelta);
    bool checkCollision();
    void gameOver();
    
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameScene);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif
