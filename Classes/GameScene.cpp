#include "GameScene.h"
#include "BackGround.h"

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
    marioPosition = 0;
    
    // 背景を作成する
    makeBackground();
    
    // marioの配置
    
    // enemy & coinの配置マスタ情報取得
    
    // enemyの配置
    
    // coinの配置
    
    // 毎フレーム、マリオを移動し、当り判定等
    this->schedule(schedule_selector(GameScene::moveMario));
    
    return true;
}

// 背景を作成する
void GameScene::makeBackground()
{
    // タップイベントを取得する
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    // TODO: ここは背景担当が作ったメソッドを入れる??
    BackGround::createStage( this, 1 );
}

// マリオ移動や当り判定
void GameScene::moveMario(float fDelta)
{
    marioPosition += fDelta;
    
    CCLog("marioPosition: %f", marioPosition);
    
    if (this->checkCollision()) {
        // ゲームオーバー処理
        CCLog("Game over..");
        this->gameOver();
    }
}

// 衝突判定
bool GameScene::checkCollision()
{
    int collision = false;
    if (rand() % 100 == 1) {
        collision = true;
    }
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
    
}
