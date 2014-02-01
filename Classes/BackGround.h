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
    virtual void setStageData(StageData *stageData);
    virtual CCSpriteBatchNode* createCoin( StageData* stageId );
    
public:
    CCParallaxNode* paraNode;
    CCSpriteBatchNode* pCoins;
    virtual void goAhead();
    static BackGround* createStage(StageData *stageData);
};

#endif /* defined(__crazymario1__BackGround__) */
