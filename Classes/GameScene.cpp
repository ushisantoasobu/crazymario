#include "GameScene.h"
#include "BackGround.h"
#include "Mario.h"
#include "GameUtil.h"
#include "UserStatus.h"
#include "CoinData.h"
#include "EnemyData.h"

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
    
    // 変数を初期化
    srand((unsigned)time(NULL));
    stageId = 1;
    marioPosition = 0;
    
    StageData* stageData = GameUtil::getGameData();
    
    //スコアラベルを作成する
    createScoreLabel();
    
    // 背景を作成する
    makeBackground(stageData);
    
    // marioの配置
    makeMario();
    
    //
    coins = makeCoins(stageData);
    
    //
    enemies = makeEnemies(stageData);
    
    // enemy & coinの配置マスタ情報取得
    cocos2d::extension::Json* json = constructStage();
    
    if (json)
    {
        // 最初のステージの情報取得
        cocos2d::extension::Json* stage = cocos2d::extension::Json_getItemAt(json, 0);
        cocos2d::extension::Json* coinList = cocos2d::extension::Json_getItem(stage, "coinList");
        for (int i = 0; i < cocos2d::extension::Json_getSize(coinList); i++)
        {
            cocos2d::extension::Json* coin = cocos2d::extension::Json_getItemAt(coinList, i);
            CCLOG("coin[%d]:%d", i, cocos2d::extension::Json_getInt(coin, "x", 1));
        }
        cocos2d::extension::Json* enemyList = cocos2d::extension::Json_getItem(stage, "enemyList");
        for (int j = 0; j < cocos2d::extension::Json_getSize(enemyList); j++)
        {
            cocos2d::extension::Json* enemy = cocos2d::extension::Json_getItemAt(enemyList, j);
            CCLOG("enemy[%d]:%d", j, cocos2d::extension::Json_getInt(enemy, "x", 1));
        }
    }
    else
    {
        CCLOG("init false");
        return false;
    }
    
    // enemyの配置
    
    // coinの配置
    
    // 毎フレーム、マリオを移動し、当り判定等
    this->schedule(schedule_selector(GameScene::moveMario));
    
    return true;
}

// ステージデータを作成する
cocos2d::extension::Json* GameScene::constructStage()
{
    const char *game_data = "[{\"stageId\":1, \"coinList\":[{\"x\":124, \"y\":56},{\"x\":456, \"y\":56}], \"enemyList\":[{\"x\":110, \"y\":56, \"type\":1},{\"x\":301, \"y\":56, \"type\":1},{\"x\":344, \"y\":56, \"type\":2}], \"bgImg\":\"bg_1.png\"}]";
    cocos2d::extension::Json* json = cocos2d::extension::Json_create(game_data);
    
    return json;
}

// マリオを作成する
void GameScene::makeMario()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // ここはマリオ担当が作ったメソッドを入れる
//    CCSprite* pMario = CCSprite::create("cloud.png");
//    pMario->setPosition(ccp(size.width * 0.1, size.height * 0.3));
//    pMario->setScale(0.2);
//    pMario->setTag(tag_crazyMario);
//    this->addChild(pMario);
//    
//    marioPosition = pMario->getPositionX();
    Mario::createMario(this, 1, tag_crazyMario);
}

// 背景を作成する
void GameScene::makeBackground(StageData* stageData)
{
    // タップイベントを取得する
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    // TODO: ここは背景担当が作ったメソッドを入れる??
    BackGround *bg = BackGround::createStage(stageData);
    this->addChild(bg, 0, tag_background);
}

CCSpriteBatchNode* GameScene::makeCoins(StageData* stageData)
{
    // コイン画像をCCSpriteBatchNodeに登録
    CCSpriteBatchNode* pBatchNode = CCSpriteBatchNode::create("item/coin/goldCoin5.png" );
    
    // シーンにバッチノードを追加
    for ( int i=0; i < stageData->coinList->count(); i++ )
    {
        CCSprite* sprite = CCSprite::createWithTexture( pBatchNode->getTexture() );
        // コインの座標を設定
        int x = ((CoinData*)stageData->coinList->objectAtIndex(i))->x;
        int y = ((CoinData*)stageData->coinList->objectAtIndex(i))->y;
        sprite->setPosition( ccp( x, y ) );
        
        // スプライトをバッチノードに追加する
        pBatchNode->addChild(sprite, 10, tag_coin_base + i);
    }
    
    this->addChild(pBatchNode);
    
    return pBatchNode;
}

CCSpriteBatchNode* GameScene::makeEnemies(StageData* stageData)
{
    // コイン画像をCCSpriteBatchNodeに登録
    CCSpriteBatchNode* pBatchNode = CCSpriteBatchNode::create("item/enemy/enemy1.png" );
    
    // シーンにバッチノードを追加
    for ( int i=0; i < stageData->enemyList->count(); i++ )
    {
        CCSprite* sprite = CCSprite::createWithTexture( pBatchNode->getTexture() );
        // コインの座標を設定
        int x = ((EnemyData*)stageData->enemyList->objectAtIndex(i))->x;
        int y = ((EnemyData*)stageData->enemyList->objectAtIndex(i))->y;
        sprite->setPosition( ccp( x, y ) );
        
        // スプライトをバッチノードに追加する
        pBatchNode->addChild(sprite, 12, tag_coin_base + i);
    }
    
    this->addChild(pBatchNode);
    
    return pBatchNode;
}

// マリオ移動や当り判定
void GameScene::moveMario(float fDelta)
{
    int speed = 10;
    int enemySpeed = 14;
    
    int coinCount = coins->getChildren()->count();
    for (int i = 0; i < coinCount; i++) {
        CCSprite* coin = (CCSprite*)coins->getChildren()->objectAtIndex(i);
        coin->setPosition(ccp(coin->getPositionX() - speed, coin->getPositionY()));
    }
    
    int enemyCount = enemies->getChildren()->count();
    for (int i = 0; i < enemyCount; i++) {
        CCSprite* enemy = (CCSprite*)enemies->getChildren()->objectAtIndex(i);
        enemy->setPosition(ccp(enemy->getPositionX() - enemySpeed, enemy->getPositionY()));
    }
    
    BackGround *bg = (BackGround *) this->getChildByTag(tag_background);
    bg->goAhead();
    
    //CCSprite* pMario = (CCSprite*)this->getChildByTag(tag_crazyMario);
    //pMario->setPositionX(marioPosition);
    
    //CCLog("marioPosition: %f", marioPosition);
    
    /*
    if (this->checkCollision()) {
        // ゲームオーバー処理
        CCLog("Game over..");
        this->gameOver();
    } else {
        Mario::moveMario(this, 1, tag_crazyMario, tag_crazyMarioJump);
    }
    */
    this->checkCollision();
    
    Mario::moveMario(this, 1, tag_crazyMario, tag_crazyMarioJump);
}

// 衝突判定
bool GameScene::checkCollision()
{
    CCLOG("---------------------------");
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* pMario = (CCSprite*)this->getChildByTag(tag_crazyMario);
    CCRect marioRect = CCRectMake(pMario->getPositionX(),
                                  pMario->getPositionY(),
                                  pMario->getContentSize().width / 4 + 4,
                                  pMario->getContentSize().height / 2 + 4); //少し多めにとっておくとゲーム的にいいかも
    CCArray* list = CCArray::create();
    list->retain();
    
    CCArray *arr = coins->getChildren();
    if (arr == NULL) {
        return false;
    }
    list->addObjectsFromArray(arr);
    for (int i = 0; i < list->count(); i++) {
        CCSprite *obj = (CCSprite *) list->objectAtIndex(i);
        obj->getTag();
        CCRect objRect = CCRectMake(obj->getPositionX(),
                                    obj->getPositionY(),
                                    obj->getContentSize().width,
                                    obj->getContentSize().height);
        if(obj->getTag() > tag_coin_base){
            /**/
            if (marioRect.intersectsRect(objRect) ) {
//                this->unschedule(schedule_selector(GameScene::moveMario));
//                this->gameOver();
                obj->removeFromParentAndCleanup(true);
                UserStatus::sharedUserStatus()->score += 100;
                updateScoreLabel();
                return false;
            }
            /* */

        }
    }
    return false;
}

// ゲームオーバー処理
void GameScene::gameOver()
{
    // TODO: ゲームオーバー画面に飛ばす？？
    CCScene* gameScene = (CCScene*)GameScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
}

// タップが開始されたときの処理
bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
    return true;
}

// タップが終了したときの処理
void GameScene::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
    // タップポイントを取得
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    CCLog("x: %f, y: %f", touchPoint.x, touchPoint.y);
    
    // TODO: ジャンプの処理呼び出し
    Mario::jumpMario(this, 1, tag_crazyMario, tag_crazyMarioJump);
}

void GameScene::createScoreLabel()
{
    cocos2d::CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *text = CCLabelTTF::create("score:0", "American Typewriter", 64);
    text->setAnchorPoint(ccp(0.0, 1.0));
    text->setHorizontalAlignment(kCCTextAlignmentLeft);
    text->setPosition(CCPointMake(winSize.width * 0.05, winSize.height * 0.92));
    this->addChild(text, 1, tag_score_label);
}

void GameScene::updateScoreLabel()
{
    CCLabelTTF *text = (CCLabelTTF *)this->getChildByTag(tag_score_label);    
    int score = UserStatus::sharedUserStatus()->score;
    
    CCString *str = CCString::createWithFormat("score:%d", score);
    text->setString(str->getCString());
}
