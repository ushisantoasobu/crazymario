//
//  TitleScene.cpp
//  crazymario
//
//  Created by 是永 誠 on 2014/01/25.
//
//

#include "TitleScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Animation.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* TitleScene::scene()
{
    CCScene* scene = CCScene::create();
    TitleScene* layer = TitleScene::create();
    scene->addChild( layer );
    
    return scene;
}

bool TitleScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    srand( (unsigned int)time( NULL ) );
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // BGM再生
    if ( !SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying() )
    {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic( "bgm/Title.mp3", true );
    }
    
    // 背景
    CCSprite* pBG = CCSprite::create( "bgimage/TitleBGImage.png" );
    pBG->setPosition( ccp( size.width * 0.5, size.height * 0.5 ) );
    this->addChild( pBG );
    
    CCSize bgSize = pBG->getContentSize();
    
    // スタートボタン
    CCMenuItemImage* pStartItem;
    pStartItem = CCMenuItemImage::create( "ui/TitleStartButton.png",
                                         "ui/TitleStartButton.png",
                                         this,
                                         menu_selector( TitleScene::menuStartCallback) );
    pStartItem->setPosition( ccp( size.width * 0.50, size.height * 0.20 ) );
    pStartItem->setTag( kTag_StartButton );
    
    CCMenu* pMenu = CCMenu::create( pStartItem, NULL );
    pMenu->setPosition( CCPointZero );
    pMenu->setTag( kTag_Menu );
    this->addChild( pMenu );
    
    // ボタンアニメーション開始
    this->schedule( schedule_selector( TitleScene::itemVibration ), 1 );
    return true;
}

void TitleScene::itemVibration()
{
    int random = rand();
    
    if ( ( random % 2 ) ==0 )
    {
        // スタートボタンのアニメーション
        CCNode* pMenu = this->getChildByTag( kTag_Menu );
        if ( pMenu )
        {
            CCNode* pStartButton = pMenu->getChildByTag( kTag_StartButton );
            if ( pStartButton )
            {
                pStartButton->runAction( Animation::vibrationAnimation() );
            }
        }
    }
}

void TitleScene::menuStartCallback( CCObject* pSender )
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
    CCScene* scene = GameScene::scene();
    CCTransitionJumpZoom* tran = CCTransitionJumpZoom::create( 1, scene );
    CCDirector::sharedDirector()->replaceScene( tran );
}
