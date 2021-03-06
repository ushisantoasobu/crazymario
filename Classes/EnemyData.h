//
//  EnemyData.h
//  crazymario
//
//  Created by s-sato on 14/01/26.
//
//

#ifndef __crazymario__EnemyData__
#define __crazymario__EnemyData__

#include "cocos2d.h"

USING_NS_CC;

enum enemyType
{
    enemyTypeSmall,
    enemyTypeMedium,
    enemyTypeLarge
};

class EnemyData : public CCNode
{
public:
    
    EnemyData();
    ~EnemyData();
    
    int x;
    int y;
    enemyType type;
};

#endif /* defined(__crazymario__EnemyData__) */
