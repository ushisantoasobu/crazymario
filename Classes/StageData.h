//
//  StageData.h
//  crazymario
//
//  Created by s-sato on 14/01/26.
//
//

#ifndef __crazymario__StageData__
#define __crazymario__StageData__

#include "cocos2d.h"

USING_NS_CC;

class StageData : public CCObject
{
public:
    
    StageData();
    ~StageData();
    
    int stageId;
    CCArray* coinList;
    CCArray* enemyList;
};

#endif /* defined(__crazymario__StageData__) */
