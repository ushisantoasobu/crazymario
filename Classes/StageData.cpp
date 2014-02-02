//
//  StageData.cpp
//  crazymario
//
//  Created by s-sato on 14/01/26.
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