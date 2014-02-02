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
    
    //敵の作成
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
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
    
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
    BackGround *bg = BackGround::createStage();
    this->addChild(bg, 0, tag_background);
    bg->setStageData( this, stageData, tag_background );
}

// マリオ移動や当り判定
void GameScene::moveMario(float fDelta)
{
    marioPosition += fDelta * 10;
    
    //CCSprite* pMario = (CCSprite*)this->getChildByTag(tag_crazyMario);
    //pMario->setPositionX(marioPosition);
    
    CCLog("marioPosition: %f", marioPosition);
    
    
    if (this->checkCollision(1))
    {   // ゲームオーバー処理
        this->gameOver();
    } else {
        if (this->checkCollision(2))
        {   // コイン取得処理
            
            // コイン削除処理
            CCLog("Get coin!!");
            updateScoreLabel();
        }
        
        if (!this->checkJumping())
        {
            Mario::moveMario(this, 1, tag_crazyMario, tag_crazyMarioJump);
        }
    }
}

CCSpriteBatchNode* GameScene::makeEnemies(StageData* stageData)
{
    // コイン画像をCCSpriteBatchNodeに登録
    CCSpriteBatchNode* pBatchNode = CCSpriteBatchNode::create("item/enemy/enemy2.png" );
    
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

// ジャンプ判定
bool GameScene::checkJumping()
{
    bool jumping = false;
    
    
    // 床との設置判定
    
    return jumping;
}

// 衝突判定
bool GameScene::checkCollision(const int type)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // マリオ情報取得
    CCSprite* marioSprite = (CCSprite*)this->getChildByTag(tag_crazyMario);
    
    BackGround *bg = (BackGround *) this->getChildByTag(tag_background);
    CCParallaxNode* paraNode = bg->paraNode;
    CCNode* coinBatchNode = (CCNode*)paraNode->getChildByTag(tag_coinbatch);
    CCNode* bgNode = this->getChildByTag(tag_background);
    CCNode* groundNode = (CCNode*)paraNode->getChildByTag(tag_ground);
    
    CCArray* objectList = NULL;
    StageData* stageData = GameUtil::getGameData();
    bool collision = false;
    CCRect marioRect = marioSprite->boundingBox();
    //marioRect.setRect(marioRect.getMinX(), marioRect.getMinY(), marioRect.size.width - 10, marioRect.size.height - 10);
    CCRect bgRect = bgNode->boundingBox();
    //CCRect groundRect = groundNode->boundingBox();
    
    CCLog("mario : %f,%f,%f,%f", marioRect.getMinX(), marioRect.getMaxX(), marioRect.getMinY(), marioRect.getMaxY());
    CCLog("bg : %f,%f,%f,%f", bgRect.getMinX(), bgRect.getMaxX(), bgRect.getMinY(), bgRect.getMaxY());
    CCLog("paraNode : %f,%f", paraNode->getPositionX(), paraNode->getPositionY());
    
    bg->goAhead(4);
    
    int enemySpeed = 4;
    currentDistance += enemySpeed;
    int enemyCount = enemies->getChildren()->count();
    for (int i = 0; i < enemyCount; i++) {
        CCSprite* enemy = (CCSprite*)enemies->getChildren()->objectAtIndex(i);
        enemy->setPosition(ccp(enemy->getPositionX() - enemySpeed, enemy->getPositionY()));
    }
    
    if (type == 1)
    {   // enemy情報取得
        CCArray* list = CCArray::create();
        list->retain();
        
        CCArray *arr = enemies->getChildren();
        if (arr == NULL) {
            return false;
        }
        list->addObjectsFromArray(arr);
        for (int i = 0; i < list->count(); i++) {
            CCSprite *obj = (CCSprite *) list->objectAtIndex(i);
            obj->getTag();
            CCRect objRect = CCRectMake(obj->getPositionX() - obj->getContentSize().width / 2,
                                        obj->getPositionY(),
                                        obj->getContentSize().width / 2,
                                        obj->getContentSize().height / 2);
            /**/
            CCRect tempMarioRect = CCRectMake(marioRect.origin.x,
                                              marioRect.origin.y,
                                              marioRect.size.width / 2,
                                              marioRect.size.height / 2);
            if (tempMarioRect.intersectsRect(objRect) ) {
                //                this->gameOver();
                return 1;
            }

        }
    }
    else if (type == 2)
    {   // コイン情報取得
        objectList = stageData->coinList;
        CCLog("check coin!!");
        for (int i=0; i < objectList->count(); i++)
        {
            CCSprite* coinSprite = (CCSprite*)coinBatchNode->getChildByTag(tag_coin_base + i);
            //CCRect coinRect = ((CCSprite*)coinBatchNode->getChildByTag(tag_coin_base + i))->boundingBox();
            if (coinSprite == 0)
            {
                CCLog("coinSprite is already deleted!!");
                continue;
            }
            CCRect coinRect = coinSprite->boundingBox();
            
            coinRect.setRect(coinRect.getMidX() + paraNode->getPositionX(), coinRect.getMidY() + size.height * 0.4, coinRect.size.width, coinRect.size.height);
            //coinRect.setRect(coinRect.getMidX() + paraNode->getPositionX(), ((CoinData*)objectList->objectAtIndex(i))->y, coinRect.size.width, coinRect.size.height);
            CCLog("coin%d : %f,%f,%f,%f", i, coinRect.getMinX(), coinRect.getMaxX(), coinRect.getMinY(), coinRect.getMaxY());
            if (marioRect.intersectsRect(coinRect))
            {
                collision = true;
                coinBatchNode->removeChildByTag(tag_coin_base + i);
                UserStatus* userStatus = UserStatus::sharedUserStatus();
                userStatus->score += 10;
                break;
            }
        }
    }
    else
    {   // それ以外は何もしない
        return false;
    }
    
    
    return collision;
}

// ゲームオーバー処理
void GameScene::gameOver()
{
    //スケジュールとめる
    this->unschedule(schedule_selector(GameScene::moveMario));
    
    //マリオ死亡アニメーション
    Mario::die(this, 1, tag_crazyMario, tag_crazyMarioJump);
    
    this->schedule(schedule_selector(GameScene::gotoGameOver), 2);
    
    // TODO: ゲームオーバー画面に飛ばす？？
    //CCScene* gameScene = (CCScene*)GameScene::create();
    //CCDirector::sharedDirector()->replaceScene(gameScene);
}

void GameScene::gotoGameOver()
{
    this->unschedule(schedule_selector(GameScene::gotoGameOver));
    
    CCLOG("gameoverシーンへ遷移");
    
    // TODO: ゲームオーバー画面に飛ばす？？
    //CCScene* gameScene = (CCScene*)GameScene::create();
    //CCDirector::sharedDirector()->replaceScene(gameScene);
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
    this->addChild(text, 100, tag_score_label);
}

void GameScene::updateScoreLabel()
{
    CCLabelTTF *text = (CCLabelTTF *)this->getChildByTag(tag_score_label);    
    int score = UserStatus::sharedUserStatus()->score;
    
    CCString *str = CCString::createWithFormat("score:%d", score);
    text->setString(str->getCString());
}
