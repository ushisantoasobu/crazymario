#ifndef __GAMESCENE__H
#define __GAMESCENE__H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "spine/Json.h"
#include "StageData.h"

USING_NS_CC;
//USING_NS_CC_EXT;

enum Tag {
    tag_background = 1,
    tag_crazyMario,
    tag_crazyMarioJump,
    tag_score_label,
    tag_paranode,
    tag_coinbatch,
    tag_ground,
    tag_coin_base = 10000
};

class GameScene : public CCLayer {
private:
    int stageId;
    float marioPosition;
    const int MAX_JUMP_COUNT = 1;
    int currentJumpCount = 0;
    int currentDistance;
    
    StageData* stageData;
    void makeBackground(StageData* stageData);
    void makeMario();
    cocos2d::extension::Json* constructStage();
    void moveMario(float fDelta);
    bool checkCollision(const int type);
    bool checkJumping();
    void gameOver();
    void gotoGameOver();
    void createScoreLabel();
    void updateScoreLabel();
    void processMarioJump(CCNode* groundNode, CCSprite* marioSprite);
    CCSpriteBatchNode* enemies;
    CCSpriteBatchNode* makeEnemies(StageData* stageData);
    
public:
    
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameScene);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif
