//
//  BackGround.h
//  crazymario1
//
//  Created by cocos2d-x on 14/01/26.
//
//

#ifndef __crazymario1__BackGround__
#define __crazymario1__BackGround__

#include "cocos2d.h"
#include "StageData.h"

USING_NS_CC;

class BackGround : public CCSprite
{
private:
    int currentDiff;
    int currentGroundIndex;
    virtual CCSpriteBatchNode* createCoin( StageData* stageId );
    void addNewGround();
    
public:
    CCParallaxNode* paraNode;
    CCSpriteBatchNode* pCoins;
    virtual void goAhead(int diff);
    static BackGround* createStage();
    virtual void setStageData( CCLayer* Scene, StageData *stageData, int StageTag );
};

#endif /* defined(__crazymario1__BackGround__) */
