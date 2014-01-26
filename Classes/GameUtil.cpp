//
//  GameUtil.cpp
//  crazymario
//
//  Created by cocos2d-x on 14/01/26.
//
//

#include "GameUtil.h"
#include "CoinData.h"
#include "EnemyData.h"

StageData* GameUtil::getGameData()
{
    // File path.
    const char* fileName = "gamadata.json";
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    
    // File open mode. (See "fopen" in the "stdio.h")
    const char* openMode = "r";
    
    // File size (will be set when open the     file).
    unsigned long fileSize = 0;
    
    // Open the file and get the data.
    unsigned char* fileData = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), openMode, &fileSize);
    
    // Create json parsing the data.
    Json *json = Json_create((char*) fileData);
    
    // Dispose data.
    delete[] fileData;
    
    // Use the json as you like ...
  
    
    
    StageData* stageData = new StageData();
    
    // Ex) Get string value.
    int value = Json_getInt(json, "stageId", -999);
    
    Json *jsonCoinList = Json_getItem(json, "coinList");
    for (int i = 0; i < Json_getSize(jsonCoinList); i++) {
        Json *jsonCoinData = Json_getItemAt(jsonCoinList, i);
        CoinData* coinData = new CoinData();
        coinData->x = Json_getInt(jsonCoinData, "x", 0);
        coinData->y = Json_getInt(jsonCoinData, "y", 0);
        coinData->type = (coinType)Json_getInt(jsonCoinData, "type", 0);
        CCLOG("name: %d", coinData->x);
        CCLOG("name: %d", coinData->y);
        CCLOG("name: %d", coinData->type);
        stageData->coinList->addObject(coinData);
        coinData->release();
    }
//    Json_dispose(jsonCoinList);
    
    Json *jsonEnemyList = Json_getItem(json, "enemyList");
    for (int j = 0; j < Json_getSize(jsonEnemyList); j++) {
        Json *jsonEnemyData = Json_getItemAt(jsonEnemyList, j);
        EnemyData* enemyData = new EnemyData();
        enemyData->x = Json_getInt(jsonEnemyData, "x", 0);
        enemyData->y = Json_getInt(jsonEnemyData, "y", 0);
        enemyData->type = (enemyType)Json_getInt(jsonEnemyData, "type", 0);
        CCLOG("name: %d", enemyData->x);
        CCLOG("name: %d", enemyData->y);
        CCLOG("name: %d", enemyData->type);
        stageData->enemyList->addObject(enemyData);
        enemyData->release();
    }
    
    // Dispose json.
    //Json_dispose(jsonEnemyList);
    //Json_dispose(jsonCoinList);
    Json_dispose(json);
    
    return stageData;
}

