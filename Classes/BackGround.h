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

class BackGround
{
public:
    static bool createStage( CCLayer* Scene, StageData* stageId, int StageTag );
    static CCSpriteBatchNode* createCoin( CCLayer* Scene, StageData* stageId );
};

#endif /* defined(__crazymario1__BackGround__) */
