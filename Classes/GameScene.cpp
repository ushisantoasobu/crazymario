#include "GameScene.h"
#include "BackGround.h"
#include "Mario.h"

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
    
    // 背景を作成する
    makeBackground();
    
    // marioの配置
    makeMario();
    
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
void GameScene::makeBackground()
{
    // タップイベントを取得する
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    // TODO: ここは背景担当が作ったメソッドを入れる??
    BackGround::createStage( this, 1, tag_background );
}

// マリオ移動や当り判定
void GameScene::moveMario(float fDelta)
{
    marioPosition += fDelta * 10;
    
    //CCSprite* pMario = (CCSprite*)this->getChildByTag(tag_crazyMario);
    //pMario->setPositionX(marioPosition);
    
    CCLog("marioPosition: %f", marioPosition);
    
    
    if (this->checkCollision()) {
        // ゲームオーバー処理
        CCLog("Game over..");
        this->gameOver();
    } else {
        Mario::moveMario(this, 1, tag_crazyMario, tag_crazyMarioJump);
    }
}

// 衝突判定
bool GameScene::checkCollision()
{
    int collision = false;
//    if (rand() % 100 == 1) {
//        collision = true;
//    }
    return collision;
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
