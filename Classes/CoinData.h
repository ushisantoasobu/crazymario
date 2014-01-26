//
//  CoinData.h
//  crazymario
//
//  Created by cocos2d-x on 14/01/26.
//
//

#ifndef __crazymario__CoinData__
#define __crazymario__CoinData__

#include "cocos2d.h"

USING_NS_CC;

enum coinType
{
    coinTypeSmal,
    coinTypeMedium,
    coinTypeLarge
};

class CoinData : public CCObject
{
public:

    CoinData();
    ~CoinData();
    
    int x;
    int y;
    coinType type;
};

#endif /* defined(__crazymario__CoinData__) */
