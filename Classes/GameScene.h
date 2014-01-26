#ifndef __GAMESCENE__H
#define __GAMESCENE__H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "spine/Json.h"

USING_NS_CC;
//USING_NS_CC_EXT;

class GameScene : public CCLayer {
private:
    int stageId;
    float marioPosition;
    enum Tag {
        tag_background,
        tag_crazyMario,
        tag_crazyMarioJump
    };
    
    void makeBackground();
    void makeMario();
    cocos2d::extension::Json* constructStage();
    void moveMario(float fDelta);
    bool checkCollision(const int type);
    bool checkJumping();
    void gameOver();
    
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameScene);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif
