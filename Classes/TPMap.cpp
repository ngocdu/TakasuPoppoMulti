//
//  TP_Map.cpp
//  Cocos2Dx
//
//  Created by macbook_006 on 13/06/28.
//
//

#include "TakasuPoppo.h"
#pragma mark Tile Functions

void TakasuPoppo::addTileMap () {
    map = CCTMXTiledMap::create("90x90TileMap.tmx");
    this->addChild(map, -1, -1);
    layer = map->layerNamed("Layer");
    layer->setPosition(4, 180);
    TakasuPoppo::createFixture();
    
    CCArray *pChildrenArray = map->getChildren();
    CCObject *pObject = NULL;
    CCSpriteBatchNode *child = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject) {
        child = ((CCSpriteBatchNode *)pObject);
        if (!child) break;
        child->getTexture()->setAntiAliasTexParameters();
    }
}

void TakasuPoppo::createFixture() {
    CCSize layerSize = layer->getLayerSize();
    
    for (int y = 0; y < layerSize.height; y++) {
        for (int x = 0; x < layerSize.width; x++) {
            
            CCSprite *tileSprite = layer->tileAt(ccp(x, y));
            unsigned int m_gid = layer->tileGIDAt(ccp(x, y));
            
            char tileName[7][20];
            strcpy(tileName[0], "Poppo1A");
            strcpy(tileName[1], "Poppo2A");
            strcpy(tileName[2], "Poppo3A");
            strcpy(tileName[3], "Poppo4A");
            strcpy(tileName[4], "Poppo5A");
            strcpy(tileName[5], "Poppo6A");
            strcpy(tileName[6], "Poppo7A");
            
            int randomTile = rand() % 7;
            char spriteName[100];
            
            while (TakasuPoppo::isTileMatched(m_gid, randomTile)) randomTile = rand() % 7;
            
            
            sprintf(spriteName, "%s.png", tileName[randomTile]);
            
            CCSprite *randomTileSprite = CCSprite::create(spriteName);
            CCPoint tilePosition = ccp(tileSprite->getPositionX() + 4 +tileSprite->getContentSize().width/2,
                                       tileSprite->getPositionY() + 180 + tileSprite->getContentSize().height/2);
            CCPoint tileCoordination = TakasuPoppo::tileCoorForPosition(tilePosition);
            randomTileSprite->setPosition(ccp(tilePosition.x, tilePosition.y + 10));
            CCObject *object = colorArray->objectAtIndex(m_gid - 1);
            TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
            TakasuPoppo::setValuesForExObj(exObj, randomTile, m_gid, randomTileSprite, tilePosition, tileCoordination, true, 0);
            
            this->addChild(randomTileSprite, 3, 300 + m_gid);
            CCLog("tilePosX: %f    tilePosY: %f", tilePosition.x, tilePosition.y);
        }
    }
    
    if(createThreeeHyper)
    {
        createMapWithHyperBlock();
        createThreeeHyper = false;
    }
}

CCPoint TakasuPoppo::tileCoorForPosition(CCPoint position) {
//    CCLog("pos %f %f", position.x, position.y);
    float x = (position.x - PADDING_X) / BLOCK_SIZE;
    int intX = (int)floor(x);
    float y = 6 - (position.y - PADDING_Y) / BLOCK_SIZE;
    int intY = (int)ceil(y);
//    CCLog("posmap %d %d", intX, intY);
    CCPoint transPos = CCPointMake(intX, intY);
    return transPos;
}

void TakasuPoppo::checkEmpty() {
    CCObject *object;
    CCARRAY_FOREACH_REVERSE(colorArray, object) {
        TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
        if (exObj->getID() == 7) {
//            generateRandomBlock(exObj, TakasuPoppo::getFallPos(exObj));
        }
    }
    controlable = true;
}

void TakasuPoppo::generateRandomBlock(TPObjectExtension *exObj, CCPoint fallCoor) {
    char tileName[7][20];
    strcpy(tileName[0], "Poppo1A");
    strcpy(tileName[1], "Poppo2A");
    strcpy(tileName[2], "Poppo3A");
    strcpy(tileName[3], "Poppo4A");
    strcpy(tileName[4], "Poppo5A");
    strcpy(tileName[5], "Poppo6A");
    strcpy(tileName[6], "Poppo7A");
    int randomTile = rand() % 7;
    char spriteName[100];
    
    sprintf(spriteName, "%s.png", tileName[randomTile]);
    
    CCSprite *randomTileSprite = CCSprite::create(spriteName);
    randomTileSprite->setPosition(fallCoor);
    float fallTime = GENERATE_FALL_TIME * ((fallCoor.y - exObj->getPosition().y) / BLOCK_SIZE);
    //randomTileSprite->runAction(CCMoveTo::create(fallTime, exObj->getPosition()));
    randomTileSprite->runAction(CCSequence::createWithTwoActions(CCMoveTo::create(fallTime, exObj->getPosition()),
                                                                 CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void *)exObj)));
    
    exObj->setSprite(randomTileSprite);
    exObj->setID(randomTile);
//    if (exObj->getControlTrigger() == false) exObj->setControlTrigger(true);
    // fix the bugs: sometimes cant swap a sprite, and still swap a sprite even it is falling
    // exObj->setControlTrigger(false);
    this->addChild(randomTileSprite, 3, 300 + exObj->getGid());
}

void TakasuPoppo::generateBlock(TPObjectExtension *exObj1, int type, CCPoint fallCoor) {
    if (type == 0) {
        CCSprite *randomTileSprite = CCSprite::create("Poppo1A.png");
        randomTileSprite->setPosition(ccp(exObj1->getPosition().x, exObj1->getPosition().y + 70));
        randomTileSprite->runAction(CCMoveTo::create(0.1, exObj1->getPosition()));
        exObj1->setSprite(randomTileSprite);
        exObj1->setID(0);
//        if (exObj1->getControlTrigger() == false)  exObj1->setControlTrigger(true);
        this->addChild(randomTileSprite, 3, 300 + exObj1->getGid());
        return;
    }
    if (type == 1) {
        CCSprite *randomTileSprite = CCSprite::create("Poppo2A.png");
        randomTileSprite->setPosition(ccp(exObj1->getPosition().x, exObj1->getPosition().y + 70));
        randomTileSprite->runAction(CCMoveTo::create(0.1, exObj1->getPosition()));
        exObj1->setSprite(randomTileSprite);
        exObj1->setID(1);
//        if (exObj1->getControlTrigger() == false) exObj1->setControlTrigger(true);
        this->addChild(randomTileSprite, 3, 300 + exObj1->getGid());
        return;
    }
    if (type == 2) {
        CCSprite *randomTileSprite = CCSprite::create("Poppo3A.png");
        randomTileSprite->setPosition(ccp(exObj1->getPosition().x, exObj1->getPosition().y + 70));
        randomTileSprite->runAction(CCMoveTo::create(0.1, exObj1->getPosition()));
        exObj1->setSprite(randomTileSprite);
        exObj1->setID(2);
//        if (exObj1->getControlTrigger() == false) exObj1->setControlTrigger(true);
        this->addChild(randomTileSprite, 3, 300 + exObj1->getGid());
        return;
    }
    if (type == 3) {
        CCSprite *randomTileSprite = CCSprite::create("Poppo4A.png");
        randomTileSprite->setPosition(ccp(exObj1->getPosition().x, exObj1->getPosition().y + 70));
        randomTileSprite->runAction(CCMoveTo::create(0.1, exObj1->getPosition()));
        exObj1->setSprite(randomTileSprite);
        exObj1->setID(3);
//        if (exObj1->getControlTrigger() == false) exObj1->setControlTrigger(true);
        this->addChild(randomTileSprite, 3, 300 + exObj1->getGid());
        return;
    }
    if (type == 4) {
        CCSprite *randomTileSprite = CCSprite::create("Poppo5A.png");
        randomTileSprite->setPosition(ccp(exObj1->getPosition().x, exObj1->getPosition().y + 70));
        randomTileSprite->runAction(CCMoveTo::create(0.1, exObj1->getPosition()));
        exObj1->setSprite(randomTileSprite);
        exObj1->setID(4);
//        if (exObj1->getControlTrigger() == false) exObj1->setControlTrigger(true);
        this->addChild(randomTileSprite, 3, 300 + exObj1->getGid());
        return;
    }
    if (type == 5) {
        CCSprite *randomTileSprite = CCSprite::create("Poppo6A.png");
        randomTileSprite->setPosition(ccp(exObj1->getPosition().x, exObj1->getPosition().y + 70));
        randomTileSprite->runAction(CCMoveTo::create(0.1, exObj1->getPosition()));
        exObj1->setSprite(randomTileSprite);
        exObj1->setID(5);
//        if (exObj1->getControlTrigger() == false) exObj1->setControlTrigger(true);
        this->addChild(randomTileSprite, 3, 300 + exObj1->getGid());
        return;
    }
    if (type == 6) {
        CCSprite *randomTileSprite = CCSprite::create("Poppo7A.png");
        randomTileSprite->setPosition(ccp(exObj1->getPosition().x, exObj1->getPosition().y + 70));
        randomTileSprite->runAction(CCMoveTo::create(0.1, exObj1->getPosition()));
        exObj1->setSprite(randomTileSprite);
        exObj1->setID(6);
//        if (exObj1->getControlTrigger() == false) exObj1->setControlTrigger(true);
        this->addChild(randomTileSprite, 3, 300 + exObj1->getGid());
        return;
    }
}


#pragma mark Array

void TakasuPoppo::addBlocksToArray() {
    for (int i = 0; i < 49; i ++) {
        TPObjectExtension *exObj = new TPObjectExtension(0, 0, NULL, ccp(0, 0), ccp(0, 0), false, 0);
        colorArray->addObject(exObj);
    }
}

void TakasuPoppo::setValuesForExObj(TPObjectExtension *exObj, int colorID, int gid, CCSprite *sprite,
                                    CCPoint position, CCPoint coordination, bool trigger, int blockType) {
    exObj->setID(colorID);
    exObj->setGid(gid);
    exObj->setSprite(sprite);
    exObj->setPosition(position);
    exObj->setCoordination(coordination);
    exObj->setControlTrigger(trigger);
    exObj->setBlockType(blockType);
    CCSprite *toMoveSprite = exObj->getSprite();
    toMoveSprite->runAction(CCMoveTo::create(0.1, exObj->getPosition()));
}

void TakasuPoppo::checkResetMap()
{
    hbcComboTimer = 0;
    hbcComboCounter = 0;
    score = 0;
    //gameTimer = 20;
    lastScores = 0;
    ComboCounter = 0;
    ComboTimer = 0;
    scoresBeforeLastBonus = 0;
    ComboScoreRequired = 1;
        feverTimer = 0;           //Timer for Fever Time
    feverTimeLimit = 3;
    feverCounter = 0;           //Counter for Fever Time
    isCreateFeverTime = false;
    isInFeverTime = false;
    
    hyperC = 10;
    hyperBlockC = false;
    gaugeComboCounter = 0;
    isCreateGaugeCombo = false;
    //item
    timeBonus = 0;
    increasedScore = 1;
    doubleScore = 1;
    endLastScore = false;
    createThreeeHyper = false;
    increaseComboTimes = 1;
    
    this->stopAllActions();
    this->unscheduleUpdate();
    
    this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(TakasuPoppo::destroyAllBlocks)),
                                           CCCallFunc::create(this, callfunc_selector(TakasuPoppo::createFixture)),NULL));
    this->scheduleUpdate();
    this->setTouchEnabled(true);
    this->scheduleOnce(schedule_selector(TakasuPoppo::timeSetup), 0);
    this->schedule(schedule_selector(TakasuPoppo::timeCounter));
}