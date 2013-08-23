//
//  TP_takasuPoppo_Swiped.cpp
//  Cocos2Dx
//
//  Created by macbook_006 on 13/06/28.
//
//

#include "TakasuPoppo.h"

#pragma mark Swipe Actions

void TakasuPoppo::swipeSetup() {

}

void TakasuPoppo::didSwipe(int direction) {
    
}

void TakasuPoppo::swipedRight(TPObjectExtension *exObj) {
    if (!endTime && exObj != NULL && exObj->getCoordination().x != 6 && exObj->getControlTrigger()) {
        unsigned int swapedGit = exObj->getGid() + 1;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

void TakasuPoppo::swipedLeft(TPObjectExtension *exObj) {
    if (!endTime && exObj != NULL && exObj->getCoordination().x != 0  && exObj->getControlTrigger()) {
        unsigned int swapedGit = exObj->getGid() - 1;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

void TakasuPoppo::swipedUp(TPObjectExtension *exObj) {
    if (!endTime && exObj != NULL && exObj->getCoordination().y != 0 && exObj->getControlTrigger()) {
        unsigned int swapedGit = exObj->getGid() - 7;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

void TakasuPoppo::swipedDown(TPObjectExtension *exObj) {
    if (!endTime && exObj != NULL && exObj->getCoordination().y != 6 && exObj->getControlTrigger()) {
        unsigned int swapedGit = exObj->getGid() + 7;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

#pragma mark Tile Interactions
void TakasuPoppo::swapTilesCheck(TPObjectExtension *exObj, int swpGid) {
    TakasuPoppo::lookForMatches();
    TPObjectExtension *swpObj = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(swpGid- 1)); //Out of range error
    
    if(swpObj == NULL || exObj == NULL || ( !swpObj->getControlTrigger() || !exObj->getControlTrigger() || isObjectMoving(swpObj) || isObjectMoving(exObj)))
    {
        return ;
    }
    
    if (TakasuPoppo::matchAble(swpObj->getCoordination(), swpObj->getID()) == true ||
        TakasuPoppo::matchAble(exObj->getCoordination(), exObj->getID()) == true)
    {
        return;
    }
    
    
    if (exObj != NULL &&
        exObj->getControlTrigger() != false &&
        swpObj != NULL &&
        swpObj->getControlTrigger() != false &&
        exObj->getID() != 7 &&
        swpObj->getID() != 7) {

        if(swpObj->getBlockType() == HBC_BLOCK_TYPE)
        {
            swpObj->getSprite()->stopActionByTag(1210);
        }
        if(exObj->getBlockType() == HBC_BLOCK_TYPE)
        {
            exObj->getSprite()->stopActionByTag(1210);
        }
        TakasuPoppo::swapColorID(exObj, swpObj);
        if (TakasuPoppo::matchAble(swpObj->getCoordination(), swpObj->getID()) == true ||
            TakasuPoppo::matchAble(exObj->getCoordination(), exObj->getID()) == true) {
            //============= moveback when position of moving havd a blockset================
            
            if (!executingLogic && (checkCreatedBlockSet(swpObj->getCoordination(), swpObj->getID()) || checkCreatedBlockSet(exObj->getCoordination(), exObj->getID())))
            {
                TakasuPoppo::swapColorID(exObj, swpObj);
                if(exObj->getSprite() != NULL && swpObj->getSprite() != NULL)
                {
                    TakasuPoppo::swapTilesBack(swpObj, exObj);
                    if(swpObj->getBlockType() == HBC_BLOCK_TYPE)
                    {
                        makeBlockToBeHBC(swpObj);
                    }
                    if(exObj->getBlockType() == HBC_BLOCK_TYPE)
                    {
                        makeBlockToBeHBC(exObj);
                    }
                }
                return;
            }
            //==========================================================================
            
            TakasuPoppo::checkPosition(swpObj, exObj);
//            this->runAction(CCSequence::create(CCDelayTime::create(SWAP_TIME+0.02),
//                                               CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlableBlockSet), (void*)swpObj),
//                                               CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlableBlockSet), (void*)exObj),
//                                               NULL));
            moveCounter = 0;
            this->schedule(schedule_selector(TakasuPoppo::movingBoolSwitch), SWAP_TIME);
            
            if(TakasuPoppo::matchAble(swpObj->getCoordination(), swpObj->getID()) == true){
                if(swpObj->getBlockType() == HBC_BLOCK_TYPE)
                {
                    makeBlockToBeHBC(swpObj);
                }
                if(exObj->getBlockType() == HBC_BLOCK_TYPE)
                {
                    makeBlockToBeHBC(exObj);
                }
                if(swpObj->getBlockType() == NORMAL_BLOCK_TYPE)
                    swpObj->setBlockType(MOVED_NORMAL_BLOCK_TYPE);
                if(swpObj->getBlockType() == HBA_BLOCK_TYPE)
                    swpObj->setBlockType(MOVED_HBA_BLOCK_TYPE);
                if(swpObj->getBlockType() == HBB_BLOCK_TYPE)
                    swpObj->setBlockType(MOVED_HBB_BLOCK_TYPE);
                if(swpObj->getBlockType() == MB1_BLOCK_TYPE)
                    swpObj->setBlockType(MB1_BLOCK_TYPE + 10);
                if(swpObj->getBlockType() == MB2_BLOCK_TYPE)
                    swpObj->setBlockType(MB2_BLOCK_TYPE + 10);
                if(swpObj->getBlockType() == MB3_BLOCK_TYPE)
                    swpObj->setBlockType(MB3_BLOCK_TYPE + 10);
            }
            if(TakasuPoppo::matchAble(exObj->getCoordination(), exObj->getID()) == true){
                
                if(exObj->getBlockType() == HBC_BLOCK_TYPE)
                {
                    makeBlockToBeHBC(exObj);
                }
                if(swpObj->getBlockType() == HBC_BLOCK_TYPE)
                {
                    makeBlockToBeHBC(swpObj);
                }
                if(exObj->getBlockType() == NORMAL_BLOCK_TYPE)
                    exObj->setBlockType(MOVED_NORMAL_BLOCK_TYPE);
                if(exObj->getBlockType() == HBA_BLOCK_TYPE)
                    exObj->setBlockType(MOVED_HBA_BLOCK_TYPE);
                if(exObj->getBlockType() == HBB_BLOCK_TYPE)
                    exObj->setBlockType(MOVED_HBB_BLOCK_TYPE);
                if(exObj->getBlockType() == MB1_BLOCK_TYPE)
                    exObj->setBlockType(MB1_BLOCK_TYPE + 10);
                if(exObj->getBlockType() == MB2_BLOCK_TYPE)
                    exObj->setBlockType(MB2_BLOCK_TYPE + 10);
                if(exObj->getBlockType() == MB3_BLOCK_TYPE)
                    exObj->setBlockType(MB3_BLOCK_TYPE + 10);
            }
            
        }
        else {
            TakasuPoppo::swapColorID(exObj, swpObj);
            if(exObj->getSprite() != NULL && swpObj->getSprite() != NULL)
            {
                TakasuPoppo::swapTilesBack(swpObj, exObj);
                if(swpObj->getBlockType() == HBC_BLOCK_TYPE)
                {
                    makeBlockToBeHBC(swpObj);
                }
                if(exObj->getBlockType() == HBC_BLOCK_TYPE)
                {
                    makeBlockToBeHBC(exObj);
                }
            }
        }
    }
    //this->setTouchEnabled(true);
    
}

void TakasuPoppo::swapColorID(TPObjectExtension *exObj, TPObjectExtension *swpObj) {
    int exID = exObj->getID();
    int swpID = swpObj->getID();
    exObj->setID(swpID);
    swpObj->setID(exID);
    
    //Vinh nt - Swap block type
    int exBlockId = exObj->getBlockType();
    int swpBlockId = swpObj->getBlockType();
    exObj->setBlockType(swpBlockId);
    swpObj->setBlockType(exBlockId);
    
    CCSprite *moveSprite = exObj->getSprite();
    CCSprite *swapSprite = swpObj->getSprite();
    exObj->setSprite(swapSprite);
    swpObj->setSprite(moveSprite);
}

void TakasuPoppo::swapTilesBack(TPObjectExtension *exObj, TPObjectExtension *swpObj) {
    CCPoint moveDes = swpObj->getPosition();
    CCPoint swapDes = exObj->getPosition();
    if(exObj != NULL && swpObj != NULL &&
       exObj->getSprite() != NULL &&
       exObj->getSprite()->numberOfRunningActions() == 0 &&
       swpObj->getSprite() != NULL && swpObj->getControlTrigger() && exObj->getControlTrigger())
        
    {
        CCSprite* move_Sprite = exObj->getSprite();
        CCSprite* swape_Sprite = swpObj->getSprite();
        if(fabs(move_Sprite->getPosition().x - exObj->getPosition().x) < 1 &&
           fabs(move_Sprite->getPosition().y - exObj->getPosition().y) < 1  &&
           fabs(swape_Sprite->getPosition().x - swpObj->getPosition().x) < 1 &&
           fabs(swape_Sprite->getPosition().y - swpObj->getPosition().y) < 1)
            move_Sprite->runAction(CCSequence::create(
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)swpObj),
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)exObj),
                                                      CCMoveBy::create(SWAP_TIME, ccp(moveDes.x - swapDes.x, moveDes.y - swapDes.y)),
                                                      CCMoveBy::create(SWAP_TIME, ccp(swapDes.x - moveDes.x, swapDes.y - moveDes.y)),
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void*)exObj),
                                                        NULL));

            swape_Sprite->runAction(CCSequence::create(
                                                       CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)swpObj),
                                                       CCMoveBy::create(SWAP_TIME, ccp(swapDes.x - moveDes.x, swapDes.y - moveDes.y)),
                                                       CCMoveBy::create(SWAP_TIME, ccp(moveDes.x - swapDes.x, moveDes.y - swapDes.y)),
                                                       CCDelayTime::create(0.001),
                                                       CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void*)swpObj),
                                                        NULL));
            
    }
}

void TakasuPoppo::switchControlable(TPObjectExtension *exObj) {
    exObj->setControlTrigger(!exObj->getControlTrigger());    
}

void TakasuPoppo::setTrueControlable(CCNode *sender, void* data)
{
        TPObjectExtension * exObj = (TPObjectExtension*)data;
        if(exObj != NULL)
        {
            exObj->setControlTrigger(true);
        }
}
void TakasuPoppo::setFalseControlable(CCNode *sender, void* data)
{
    TPObjectExtension* exObj = (TPObjectExtension*)data;
    if(exObj != NULL)
    {
        exObj->setControlTrigger(false);
    }
}

void TakasuPoppo::checkPosition(TPObjectExtension *exObj, TPObjectExtension *swpObj) {
    CCPoint moveDes = swpObj->getPosition();
    CCPoint swapDes = exObj->getPosition();
    if(swpObj->getSprite()->numberOfRunningActions() == 0 && exObj->getSprite()->numberOfRunningActions() == 0)
    {
        if (fabs(swpObj->getSprite()->getPosition().x - swpObj->getPosition().x) > 1 ||
            fabs(swpObj->getSprite()->getPosition().y - swpObj->getPosition().y) > 1 ) {
            
            CCSprite* swape_Sprite = swpObj->getSprite();
            swape_Sprite->runAction(CCSequence::create(
                                                       CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)swpObj),
                                                       CCMoveBy::create(SWAP_TIME, ccp(moveDes.x - swapDes.x, moveDes.y - swapDes.y)),
                                                       CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void*)swpObj),
                                                        NULL));
        }
        if (fabs(exObj->getSprite()->getPosition().x - exObj->getPosition().x) > 1 ||
            fabs(exObj->getSprite()->getPosition().y - exObj->getPosition().y) > 1 ) {
            
            CCSprite* move_Sprite = exObj->getSprite();
            move_Sprite->runAction(CCSequence::create(
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)exObj),
                                                      CCMoveBy::create(SWAP_TIME, ccp(swapDes.x - moveDes.x, swapDes.y - moveDes.y)),
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void*)exObj),
                                                      NULL));
        }
    }
}
TPObjectExtension* TakasuPoppo::checkSwipe(TPBlockSet *blockSet){
    if (blockSet->getEx1() != NULL && blockSet->getEx1()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx1();
    if (blockSet->getEx2() != NULL && blockSet->getEx2()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx2();
    if (blockSet->getEx3() != NULL && blockSet->getEx3()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx3();
    if (blockSet->getEx4() != NULL && blockSet->getEx4()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx4();
    if (blockSet->getEx5() != NULL && blockSet->getEx5()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx5();
    if (blockSet->getEx6() != NULL && blockSet->getEx6()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx6();
    if (blockSet->getEx7() != NULL && blockSet->getEx7()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx7();
    return blockSet->getEx2();
}

bool TakasuPoppo::isObjectMoving(TPObjectExtension *obj) {
    CCSprite *exSprite = obj->getSprite();
    if (exSprite != NULL && obj->getID() != 7 && (floatCompare(exSprite->getPositionX(), obj->getPosition().x, 0.00001) == true || floatCompare(exSprite->getPositionY(), obj->getPosition().y, 0.00001) == true))
        return false;
    else return true;
}

bool TakasuPoppo::floatCompare(float x, float y, float epsilon) {
    float diff = fabs(x-y);
    x = fabs(x);
    y = fabs(y);
    float largest = y > x ? y : x;
    if (diff <= largest * epsilon)
        return true;
    else return false;
}

void TakasuPoppo::setFalseControlableBlockSet(cocos2d::CCNode *sender, void *data){
    TPObjectExtension* exObj = (TPObjectExtension*) data;
    
    int exID, exGID, leftGID, rightGID, downGID, upGID, left = 0, right = 0, up = 0, down = 0;
    TPObjectExtension* tempObj;
    CCArray *rsH, *rsV;
    rsH = new CCArray;
    rsV = new CCArray;
    rsH->autorelease();
    rsV->autorelease();
    
    exGID = exObj->getGid();
    exID = exObj->getID();
    
    for (int i = 0; i < 6; i++) {
        if ((exGID-1) % 7 > i && left == 0) {
            leftGID = exGID - i - 1;
            tempObj = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(leftGID - 1));
            if (tempObj->getID() == exID) {
                rsV->addObject(tempObj);
            }
            else
                left = 1;
        }
        if ((exGID-1) % 7 < (7-i-1) && right == 0) {
            rightGID = exGID + i + 1;
            tempObj = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(rightGID - 1));
            if (tempObj->getID() == exID)
                rsV->addObject(tempObj);
            else
                right = 1;
        }
        if ((exGID+7*(i+1)) < 50 && down == 0) {
            downGID = exGID + 7*(i+1);
            tempObj = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(downGID - 1));
            if (tempObj->getID() == exID)
                rsH->addObject(tempObj);
            else
                down = 1;
        }
        if ((exGID-7*(i+1)) > 0 && up == 0) {
            upGID = exGID - 7*(i+1);
            tempObj = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(upGID - 1));
            if (tempObj->getID() == exID)
                rsH->addObject(tempObj);
            else
                up = 1;
        }
    }
    if (rsH->count() > 1 || rsV->count() > 1) {
        CCObject *obj;
        CCARRAY_FOREACH(rsH, obj) {
            tempObj = dynamic_cast<TPObjectExtension*>(obj);
            tempObj->setControlTrigger(false);
        }
        CCARRAY_FOREACH(rsV, obj) {
            tempObj = dynamic_cast<TPObjectExtension*>(obj);
            tempObj->setControlTrigger(false);
        }
        exObj->setControlTrigger(false);
    }
}
