//
//  StageData.cpp
//  crazymario
//
//  Created by cocos2d-x on 14/01/26.
//
//

#include "StageData.h"

StageData::StageData()
{
    coinList = CCArray::create();
    coinList->retain();
    
    enemyList = CCArray::create();
    enemyList->retain();
}

StageData::~StageData()
{
    
}