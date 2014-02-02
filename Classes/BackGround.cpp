//
//  BackGround.cpp
//  crazymario1
//
//  Created by cocos2d-x on 14/01/26.
//
//

#include "BackGround.h"
#include "CoinData.h"
#include "GameScene.h"

// ステージ作成
BackGround* BackGround::createStage(StageData *stageData)
{
    BackGround *backGround = new BackGround();
    if (backGround && backGround->init())
    {
        backGround->autorelease();
        backGround->setStageData(stageData);
        return backGround;
    }
    CC_SAFE_DELETE(backGround);
    return NULL;
}

void BackGround::setStageData(StageData *stageData)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 背景を生成
    CCSprite* pBG = CCSprite::create( "bgimage/stage0001.png" );
//    pBG->setTag( StageTag );
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
    
    paraNode = CCParallaxNode::create();
    //pCoins = createCoin( stageData );
    //CCTMXTiledMap* pSky = CCTMXTiledMap::create( "ui/bgSky.tmx" );
    //pSky->setTag( StageTag );


    paraNode->addChild( pBG, 1, ccp( 0.0f, 0 ), ccp( -size.width * 0.5, size.height * 0.5 ) );
    
    //地面を初期化の時点で２つ入れる
    addNewGround();
    addNewGround();
    
    CCTMXTiledMap* pGround2 = CCTMXTiledMap::create( "ui/groundStage001.tmx" );
    
    paraNode->setPosition( ccp( size.width * 0.5, size.height * 0.5 ) );
    this->addChild( paraNode );
}


void BackGround::goAhead(int diff)
{
    int w = 140 * 16; //"ui/groundStage001.tmx"からとった地面の一塊のwidth
    currentDiff += diff;
    paraNode->setPosition(ccp(paraNode->getPositionX() - diff, paraNode->getPositionY()));
    if(w < currentDiff){
        currentDiff = currentDiff - w;
        addNewGround();
    }
}

void BackGround::addNewGround()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCTMXTiledMap* pGround = CCTMXTiledMap::create( "ui/groundStage001.tmx" );
    pGround->setTag(555);
    paraNode->addChild(pGround,
                       2,
                       ccp( 1.0f, 0 ),
                       ccp( -size.width * 0.5 + 2240 * currentGroundIndex, 0));
    currentGroundIndex++;
    
    CCArray *arr = CCArray::create();
    for (int i = 0; i < paraNode->getChildren()->count(); i++) {
        if ( ((CCSprite*) paraNode->getChildren()->objectAtIndex(i))->getTag() == 555 ) {
            arr->addObject(paraNode->getChildren()->objectAtIndex(i));
        }
    }
    
    if (arr->count() > 2) {
        //先頭の地面削除
        ((CCSprite*) arr->objectAtIndex(0))->removeFromParentAndCleanup(true);
    }
}


// コイン作成
CCSpriteBatchNode* BackGround::createCoin( StageData *stageData )
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    // コイン画像をCCSpriteBatchNodeに登録
    CCSpriteBatchNode* pBatchNode = CCSpriteBatchNode::create("item/coin/goldCoin5.png" );
    // シーンにバッチノードを追加
//    float x = 0;
    //Scene->addChild( pBatchNode );
    for ( int i=0; i < stageData->coinList->count(); i++ )
    {
        CCSprite* sprite = CCSprite::createWithTexture( pBatchNode->getTexture() );
        // コインの座標を設定
        // @todo なにか情報を受け取って情報を作成する
        //float x = CCRANDOM_0_1()*size.width;
        int x = ((CoinData*)stageData->coinList->objectAtIndex(i))->x;
        //float y = CCRANDOM_0_1()*size.height*0.7 + size.height*0.3;
        int y = ((CoinData*)stageData->coinList->objectAtIndex(i))->y;
        sprite->setPosition( ccp( x, y ) );
        // スプライトをバッチノードに追加する
        pBatchNode->addChild(sprite, 10, tag_coin_base + i);
        
        CCLOG("x:%d", x);
        
        // ランダムな時間でフェードアウト
        //CCFadeOut* fade = CCFadeOut::create( CCRANDOM_0_1()*10.0f );
        //sprite->runAction( fade );
    }
    return pBatchNode;
}
