//
//  GameUtil.h
//  ゲーム情報操作クラス
//
//  Created by s-sato on 14/01/26.
//
//

#ifndef __crazymario__GameUtil__
#define __crazymario__GameUtil__

#include "cocos2d.h"
#include "spine/Json.h"
#include "StageData.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class GameUtil
{    
public:
    static StageData* getGameData();
    
};

#endif /* defined(__crazymario__GameUtil__) */