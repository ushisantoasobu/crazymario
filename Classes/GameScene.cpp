#include "GameScene.h"

CCScene* GameScene::scene() {
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 背景の表示
    CCSprite* pBG = CCSprite::create( "bgimage/stage0001.png" );
    pBG->setPosition( ccp( size.width * 0.5, size.height * 0.5 ) );
    this->addChild( pBG, 0, tag_background );
    return true;
}