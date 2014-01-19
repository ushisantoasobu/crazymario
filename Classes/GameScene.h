#ifndef __GAMESCENE__H
#define __GAMESCENE__H

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public CCLayer {
private:
    enum Tag {
        tag_background,
        tag_crazyMario,
    };
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameScene);
};

#endif
