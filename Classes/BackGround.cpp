//
//  BackGround.cpp
//  crazymario1
//
//  Created by cocos2d-x on 14/01/26.
//
//

#include "BackGround.h"

// ステージ作成
bool BackGround::createStage( CCLayer* Scene, int StageID, int StageTag )
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 背景を生成
    CCSprite* pBG = CCSprite::create( "bgimage/stage0001.png" );
    //pBG->setPosition( ccp( size.width * 0.5, size.height * 0.5 ) );
    //Scene->addChild( pBG, 0, StageTag );
    
    // 雲の表示
    //CCSprite* pCloud1 = CCSprite::create( "cloud.png" );
    //pCloud1->setPosition( ccp( size.width * 0.9, size.height * 0.83 ) );
    //pBG->addChild( pCloud1 );
    
    //CCSprite* pCloud2 = CCSprite::create( "cloud.png" );
    //pCloud2->setPosition( ccp( size.width * 0.7, size.height * 0.9 ) );
    //pCloud2->setScale( 0.6 );
    //pBG->addChild( pCloud2 );
    
    CCParallaxNode* paraNode = CCParallaxNode::create();
    CCSpriteBatchNode* pCoins = createCoin( Scene );
    CCTMXTiledMap* pGround = CCTMXTiledMap::create( "ui/groundStage001.tmx" );
    paraNode->addChild( pBG, 1, ccp( 0.1f, 0 ), ccp( 0, size.height * 0.5 ) );
    paraNode->addChild( pCoins, 3, ccp( 1.0f, 0 ), ccp( 0, size.height * 0.3 ) );
    paraNode->addChild( pGround, 2, ccp( 1.0f, 0 ), ccp( -size.width * 0.5, 0 ) );
    paraNode->setPosition( ccp( size.width * 0.5, size.height * 0.5 ) );
    Scene->addChild( paraNode );
    
    CCMoveBy* move = CCMoveBy::create( 10.0f, ccp( -size.width / 2, 0 ) );
    CCSequence* seq = (CCSequence*)CCSequence::create( move, NULL );
    CCRepeatForever* repeat = CCRepeatForever::create( seq );
    paraNode->runAction( repeat );
    
    
    CCLOG( "StageID: %d", StageID );
    CCLOG( "StageTag: %d", StageTag );
    return true;
}
// コイン作成
CCSpriteBatchNode* BackGround::createCoin( CCLayer* Scene )
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    // コイン画像をCCSpriteBatchNodeに登録
    CCSpriteBatchNode* pBatchNode = CCSpriteBatchNode::create("item/coin/goldCoin5.png" );
    // シーンにバッチノードを追加
    float x = 0;
    //Scene->addChild( pBatchNode );
    for ( int i=0; i < 100; i++ )
    {
        CCSprite* sprite = CCSprite::createWithTexture( pBatchNode->getTexture() );
        // コインの座標を設定
        // @todo なにか情報を受け取って情報を作成する
        //float x = CCRANDOM_0_1()*size.width;
        x += 50;
        //float y = CCRANDOM_0_1()*size.height*0.7 + size.height*0.3;
        float y = size.height*0.3;
        sprite->setPosition( ccp( x, y ) );
        // スプライトをバッチノードに追加する
        pBatchNode->addChild( sprite );
        
        // ランダムな時間でフェードアウト
        //CCFadeOut* fade = CCFadeOut::create( CCRANDOM_0_1()*10.0f );
        //sprite->runAction( fade );
    }
    return pBatchNode;
}