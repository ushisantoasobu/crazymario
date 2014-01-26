#ifndef __GAMESCENE__H
#define __GAMESCENE__H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "spine/Json.h"
#include "StageData.h"

USING_NS_CC;
//USING_NS_CC_EXT;

enum Tag {
    tag_background,
    tag_crazyMario,
    tag_crazyMarioJump,
    tag_score_label,
    tag_coin_base = 10000
};

class GameScene : public CCLayer {
private:
    int stageId;
    float marioPosition;
    
    void makeBackground(StageData* stageData);
    void makeMario();
    cocos2d::extension::Json* constructStage();
    void moveMario(float fDelta);
    bool checkCollision();
    void gameOver();
    void createScoreLabel();
    void updateScoreLabel();
    
public:
    
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameScene);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif
