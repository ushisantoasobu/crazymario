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
    return true;
}