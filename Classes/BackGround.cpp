//
//  BackGround.cpp
//  crazymario1
//
//  Created by cocos2d-x on 14/01/26.
//
//

#include "BackGround.h"

bool BackGround::createStage( CCLayer* Scene, int StageID )
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 背景を生成
    CCSprite* pBG = CCSprite::create( "bgimage/stage0001.png" );
    pBG->setPosition( ccp( size.width * 0.5, size.height * 0.5 ) );
    Scene->addChild( pBG );
    
    // 雲の表示
    //CCSprite* pCloud1 = CCSprite::create( "cloud.png" );
    //pCloud1->setPosition( ccp( size.width * 0.9, size.height * 0.83 ) );
    //pBG->addChild( pCloud1 );
    
    //CCSprite* pCloud2 = CCSprite::create( "cloud.png" );
    //pCloud2->setPosition( ccp( size.width * 0.7, size.height * 0.9 ) );
    //pCloud2->setScale( 0.6 );
    //pBG->addChild( pCloud2 );
    
    CCLOG( "StageID: %d", StageID );
    return true;
}