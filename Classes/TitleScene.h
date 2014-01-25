//
//  TitleScene.h
//  crazymario
//
//  Created by 是永 誠 on 2014/01/25.
//
//

#ifndef __crazymario__TitleScene__
#define __crazymario__TitleScene__

#include "cocos2d.h"

class TitleScene : public cocos2d::CCLayer
{
protected:
    enum kTag
    {
        kTag_Menu = 1,
        kTag_StartButton,
    };
    void itemVibration();
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC( TitleScene );
    virtual void menuStartCallback( CCObject* pSender );
};

#endif /* defined(__crazymario__TitleScene__) */
