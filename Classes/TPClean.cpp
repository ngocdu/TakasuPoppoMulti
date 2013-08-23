//
//  TPClean.cpp
//  Cocos2Dx
//
//  Created by Ace on 2013/07/01.
//
//


#include "TakasuPoppo.h"
#include "TPBlockSet.h"
void TakasuPoppo::cleanBlocks() {    
    
    createB = false;
    if (toDestroyArray->count() != 0) {
        
        CCObject *object;
        CCARRAY_FOREACH(toDestroyArray, object) {            
            bool hyperA = false;
            bool hyperB = false;
            TPBlockSet *blockSet = dynamic_cast<TPBlockSet*>(object);
            if (blockSet->getType() == "hyperBlockC") {
                TakasuPoppo::cleanHyperBlockC(blockSet->getEx1());
            } else {
                hintCounter = 3;
                TakasuPoppo::plusAllComboCounter();
                // update current block set
                currentBlockSet = blockSet->getBlocksArray();
                
                //===============================
                
                if(blockSet->getEx3() != NULL)
                {
                    score = score + (int)(ComboScoreRequired * increasedScore * SCORE_THREE * doubleScore);
                }
                if(blockSet->getEx4() != NULL && blockSet->getEx4()->getID() != 7)
                {
                    score = score + (int)(ComboScoreRequired * increasedScore * SCORE_FOUR * doubleScore);
                    hyperA = true;
                }
                if(blockSet->getEx5() != NULL)
                {
                    score =score + (int)(ComboScoreRequired * increasedScore * SCORE_FIVE *doubleScore);
                    hyperA = false;
                    hyperB = true;
                }
                
                if (isValidEx(blockSet->getEx1())){
                    TakasuPoppo::cleanOneBlock(blockSet->getEx1());
                    if(hyperA || hyperB)
                        generationEffect(blockSet->getEx1()->getPosition(), checkSwipe(blockSet)->getPosition());
                }
                
                if (isValidEx(blockSet->getEx2())){
                    if((!hyperA && !hyperB) || checkSwipe(blockSet)->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE)
                    {
                        
                        TakasuPoppo::cleanOneBlock(blockSet->getEx2());
                        if(hyperA || hyperB)
                            generationEffect(blockSet->getEx2()->getPosition(), checkSwipe(blockSet)->getPosition());
                    }
                }
                
                if (isValidEx(blockSet->getEx3())) {
                    TakasuPoppo::cleanOneBlock(blockSet->getEx3());
                    if(hyperA || hyperB)
                        generationEffect(blockSet->getEx3()->getPosition(), checkSwipe(blockSet)->getPosition());
                }
                
                if (isValidEx(blockSet->getEx4())) {
                    TakasuPoppo::cleanOneBlock(blockSet->getEx4());
                    if(hyperA || hyperB)
                        generationEffect(blockSet->getEx4()->getPosition(), checkSwipe(blockSet)->getPosition());
                }
                if (isValidEx(blockSet->getEx5())) {
                    TakasuPoppo::cleanOneBlock(blockSet->getEx5());
                    if(hyperA || hyperB)
                        generationEffect(blockSet->getEx5()->getPosition(), checkSwipe(blockSet)->getPosition());
                }
                
                if (isValidEx(blockSet->getEx6())) {
                    TakasuPoppo::cleanOneBlock(blockSet->getEx6());
                    if(hyperA || hyperB)
                        generationEffect(blockSet->getEx6()->getPosition(), checkSwipe(blockSet)->getPosition());
                    
                }
                
                if (isValidEx(blockSet->getEx7())) {
                    TakasuPoppo::cleanOneBlock(blockSet->getEx7());
                    if(hyperA || hyperB)
                        generationEffect(blockSet->getEx7()->getPosition(), checkSwipe(blockSet)->getPosition());
                    
                }
                
                if(checkSwipe(blockSet)->getBlockType() == 13)
                {
                    createSpecialBlock(checkSwipe(blockSet), HBB_BLOCK_TYPE);
                    currentBlockSet = NULL;
                    continue;
                }
                
                if(checkSwipe(blockSet)->getBlockType() >= 20)
                {
                    if (checkSwipe(blockSet)->getBlockType() == 21) {
                        cleanA(checkSwipe(blockSet));
                    }
                    if (checkSwipe(blockSet)->getBlockType() == 22) {
                        cleanB(checkSwipe(blockSet));
                    }
                    if(checkSwipe(blockSet)->getBlockType() == 26)
                        isCleanMB1 = true;
                    if(checkSwipe(blockSet)->getBlockType() == 27)
                        isCleanMB2 = true;
                    if(checkSwipe(blockSet)->getBlockType() == 28)
                        isCleanMB3 = true;
                    checkSwipe(blockSet)->setBlockType(13);

                }
                else if (checkSwipe(blockSet)->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE && hyperA)
                {
                    if(checkSwipe(blockSet)->getBlockType() == MOVED_HBA_BLOCK_TYPE)
                        cleanA(checkSwipe(blockSet));
                    if(checkSwipe(blockSet)->getBlockType() == MOVED_HBB_BLOCK_TYPE)
                        cleanB(checkSwipe(blockSet));
                    if(checkSwipe(blockSet)->getBlockType() == MB1_BLOCK_TYPE + 10)
                        isCleanMB1 = true;
                    if(checkSwipe(blockSet)->getBlockType() == MB2_BLOCK_TYPE + 10)
                        isCleanMB2 = true;
                    if(checkSwipe(blockSet)->getBlockType() == MB3_BLOCK_TYPE + 10)
                        isCleanMB3 = true;
                    createSpecialBlock(checkSwipe(blockSet), HBA_BLOCK_TYPE);
                    hyperA = false;
                    hyperB = false;
                }
                else if(hyperA)
                {
                    createSpecialBlock(blockSet->getEx2(), HBA_BLOCK_TYPE);
                    hyperA = false;
                    hyperB = false;
                }
                else if (checkSwipe(blockSet)->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE && hyperB)
                {
                    if(checkSwipe(blockSet)->getBlockType() == MOVED_HBA_BLOCK_TYPE)
                        cleanA(checkSwipe(blockSet));
                    if(checkSwipe(blockSet)->getBlockType() == MOVED_HBB_BLOCK_TYPE)
                        cleanB(checkSwipe(blockSet));
                    if(checkSwipe(blockSet)->getBlockType() == MB1_BLOCK_TYPE + 10)
                        isCleanMB1 = true;
                    if(checkSwipe(blockSet)->getBlockType() == MB2_BLOCK_TYPE + 10)
                        isCleanMB2 = true;
                    if(checkSwipe(blockSet)->getBlockType() == MB3_BLOCK_TYPE + 10)
                        isCleanMB3 = true;
                    
                    createSpecialBlock(checkSwipe(blockSet), HBB_BLOCK_TYPE);
                    hyperA = false;
                    hyperB = false;
                }
                else if(hyperB)
                {
                    createSpecialBlock(blockSet->getEx2(), HBB_BLOCK_TYPE);
                    hyperB = false;
                    hyperA = false;
                }
                else {
                    cleanOneBlock(checkSwipe(blockSet));
                }
                currentBlockSet = NULL;
            }
        }
        
        
        CCObject* ox;
        CCARRAY_FOREACH(toDestroyArray, ox)
        {
            TPBlockSet *ex = dynamic_cast<TPBlockSet*>(ox);
            if(ex->getEx1() != NULL && ex->getEx1()->getBlockType() != 0 && ex->getEx1()->getBlockType() != 1 && ex->getEx1()->getBlockType() != 2 && ex->getEx1()->getBlockType() != 3 && ex->getEx1()->getBlockType() != 6 && ex->getEx1()->getBlockType() != 7 && ex->getEx1()->getBlockType() != 8)
                cleanOneBlock(ex->getEx1());
            if(ex->getEx2() != NULL && ex->getEx2()->getBlockType() != 0 && ex->getEx2()->getBlockType() != 1 && ex->getEx2()->getBlockType() != 2 && ex->getEx2()->getBlockType() != 3 && ex->getEx2()->getBlockType() != 6 && ex->getEx2()->getBlockType() != 7 && ex->getEx2()->getBlockType() != 8)
                cleanOneBlock(ex->getEx2());
            if(ex->getEx3() != NULL && ex->getEx3()->getBlockType() != 0 && ex->getEx3()->getBlockType() != 1 && ex->getEx3()->getBlockType() != 2 && ex->getEx3()->getBlockType() != 3 && ex->getEx3()->getBlockType() != 6 && ex->getEx3()->getBlockType() != 7 && ex->getEx3()->getBlockType() != 8)
                cleanOneBlock(ex->getEx3());
            if(ex->getEx4() != NULL && ex->getEx4()->getBlockType() != 0 && ex->getEx4()->getBlockType() != 1 && ex->getEx4()->getBlockType() != 2 && ex->getEx4()->getBlockType() != 3 && ex->getEx4()->getBlockType() != 6 && ex->getEx4()->getBlockType() != 7 && ex->getEx4()->getBlockType() != 8)
                cleanOneBlock(ex->getEx4());
            if(ex->getEx5() != NULL && ex->getEx5()->getBlockType() != 0 && ex->getEx5()->getBlockType() != 1 && ex->getEx5()->getBlockType() != 2 && ex->getEx5()->getBlockType() != 3 && ex->getEx5()->getBlockType() != 6 && ex->getEx5()->getBlockType() != 7 && ex->getEx5()->getBlockType() != 8)
                cleanOneBlock(ex->getEx5());
            
            if(ex->getEx6() != NULL && ex->getEx6()->getBlockType() != 0 && ex->getEx6()->getBlockType() != 1 && ex->getEx6()->getBlockType() != 2 && ex->getEx6()->getBlockType() != 3 && ex->getEx6()->getBlockType() != 6 && ex->getEx6()->getBlockType() != 7 && ex->getEx6()->getBlockType() != 8)
                cleanOneBlock(ex->getEx6());
            if(ex->getEx7() != NULL && ex->getEx7()->getBlockType() != 0 && ex->getEx7()->getBlockType() != 1 && ex->getEx7()->getBlockType() != 2 && ex->getEx7()->getBlockType() != 3 && ex->getEx7()->getBlockType() != 6 && ex->getEx7()->getBlockType() != 7 && ex->getEx7()->getBlockType() != 8)
                cleanOneBlock(ex->getEx7());
        }
        toDestroyArray->removeAllObjects();
        
    }
    toDestroyArray->removeAllObjects();
    
}


void TakasuPoppo::afterClean(){
    // when it run to afterClean, all block has ben clean and remove it from toDestroyArray, so we set isHBCinBlockSet = false
    isHBCinBlockSet = false;
    
    CCObject *object;
    CCARRAY_FOREACH_REVERSE(colorArray, object) {
        TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
        if (exObj != NULL && exObj->getID() == 7 && exObj->getCoordination().y != 0) {

            CCObject *object2;
            CCARRAY_FOREACH_REVERSE(colorArray, object2) {
                TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(object2);
                if (exObj2 != NULL && exObj2->getCoordination().x == exObj->getCoordination().x &&
                    exObj2->getCoordination().y < exObj->getCoordination().y &&
                    exObj2->getID() != 7 && exObj2->getSprite() && exObj2->getSprite() != NULL) {
                    int blocksAway = exObj->getCoordination().y - exObj2->getCoordination().y;
                    CCLog("BlocksAway: %d", blocksAway);
                    CCSprite *toMoveSprite =  exObj2->getSprite();

                    TakasuPoppo::swapColorID(exObj, exObj2);
                    exObj2->setControlTrigger(false);
                    //exObj->getSprite()->setPosition(exObj2->getPosition());
                        toMoveSprite->runAction(CCSequence::create(
                                                               CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable),(void*)exObj2),
                                                               CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable),(void*)exObj),
                                                               CCMoveBy::create(movingSpeed * blocksAway, ccp(0, - BLOCK_SIZE * blocksAway)),
//                                                               CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable),(void*)exObj2),

                                                               CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable),(void*)exObj),
                                                               NULL));

                    break;
                }
            }
//            exObj->setControlTrigger(true);
        }
    }
//    toDestroyArray->removeAllObjects();
}

void TakasuPoppo::changeID(CCNode *sender, void* data) {
    TPObjectExtension *exObj = (TPObjectExtension*)data;
    exObj->setID(7);

    //exObj->setSprite(NULL);
    // change block type
    exObj->setBlockType(NORMAL_BLOCK_TYPE);
}

void TakasuPoppo::cleanSprite(TPObjectExtension *exObj) {
    exObj->setControlTrigger(false);
    score =score + (int)(ComboScoreRequired * increasedScore * ONE_BLOCK *doubleScore);
    CCSprite *exSprite = exObj->getSprite();
    if (exSprite != NULL && exObj != NULL && exObj->getID() != 7 && exObj->getSprite() != NULL) {
        exSprite->stopActionByTag(1210);
        CCPoint *spritePosition = new CCPoint(exObj->getPosition());
        exSprite->runAction(CCSequence::create(
                CCDelayTime::create(CLEAN_DELAY),
                CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::changeID), (void*)exObj),
                CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::popAnimation), (void*)spritePosition),
                CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::removeSprite), (void*)exSprite),
//                                               CCRemoveSelf::create(true),
                                               NULL));
        

    }
}

void TakasuPoppo::removeSprite(CCNode* sender, void* data)
{
    if(data != NULL)
    {
        CCSprite *exSprite = (CCSprite*)data;
        exSprite->removeFromParentAndCleanup(true);
    }
}

/*
 |======================================|
 |         clean Hyper BLock A          |
 |======================================|
 |    |     -2  -1   0  +1  +2  +3      |
 |----|---------------------------------|
 | -3 |                                 |
 | -2 |                                 |
 | -1 |          k   b  c               |
 |  0 |          i  [a] d               |
 | +1 |          h   g  e               |
 | +2 |                                 |
 |======================================|
 */


void TakasuPoppo::cleanHyperBlockA(TPObjectExtension* exObj){
    // if this Hyper Block is not in current block, plus 1 to combo and fever Counter
    if (gameTimer > 0) {
        if (isInCurrentBlockSet(exObj)  == false) {
            TakasuPoppo::plusAllComboCounter();
        }

    }
    else{
        
    }
    
    CCPoint aPoint = exObj->getCoordination();
    int x = aPoint.x;
    int y = aPoint.y;
    
    CCPoint bPoint = ccp( x, y - 1);
    CCPoint cPoint = ccp(x + 1, y - 1);
    CCPoint dPoint = ccp(x + 1, y);
    CCPoint ePoint = ccp(x + 1, y + 1);
    CCPoint gPoint = ccp(x, y + 1);
    CCPoint hPoint = ccp(x - 1, y + 1);
    CCPoint iPoint = ccp(x - 1, y);
    CCPoint kPoint = ccp(x - 1, y - 1);
    
    
    exObj->setBlockType(NORMAL_BLOCK_TYPE);
    
    TPObjectExtension *bExObj = TakasuPoppo::coorToExObj(bPoint);
    TPObjectExtension *cExObj = TakasuPoppo::coorToExObj(cPoint);
    TPObjectExtension *dExObj = TakasuPoppo::coorToExObj(dPoint);
    TPObjectExtension *eExObj = TakasuPoppo::coorToExObj(ePoint);
    TPObjectExtension *gExObj = TakasuPoppo::coorToExObj(gPoint);
    TPObjectExtension *hExObj = TakasuPoppo::coorToExObj(hPoint);
    TPObjectExtension *iExObj = TakasuPoppo::coorToExObj(iPoint);
    TPObjectExtension *kExObj = TakasuPoppo::coorToExObj(kPoint);
    
    if (bExObj != NULL && bExObj->getSprite() != NULL && bExObj->getID() != 7 && bExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(bExObj);
    }
    
    if (cExObj != NULL && cExObj->getSprite() != NULL && cExObj->getID() != 7 && cExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(cExObj);
    }
    
    if (dExObj != NULL && dExObj->getSprite() != NULL && dExObj->getID() != 7 && dExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(dExObj);
    }
    
    if (eExObj != NULL && eExObj->getSprite() != NULL && eExObj->getID() != 7 && eExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(eExObj);
    }
    
    if (gExObj != NULL && gExObj->getSprite() != NULL && gExObj->getID() != 7 && gExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(gExObj);
    }
    
    if (hExObj != NULL && hExObj->getSprite() != NULL && hExObj->getID() != 7 && hExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(hExObj);
    }
    
    if (iExObj != NULL && iExObj->getSprite() != NULL && iExObj->getID() != 7 && iExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(iExObj);
    }
    
    if (kExObj != NULL && kExObj->getSprite() != NULL && kExObj->getID() != 7 && kExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(kExObj);
    }
    
    if (exObj->getSprite() != NULL || exObj->getID() != 7) TakasuPoppo::cleanSprite(exObj);
    
}

void TakasuPoppo::cleanHyperBlockB(TPObjectExtension* exObj) {

    int x = exObj->getCoordination().x;
    int y = exObj->getCoordination().y;
    
    if (isInCurrentBlockSet(exObj) == false) {
        
        exObj->setBlockType(NORMAL_BLOCK_TYPE);
        
        TakasuPoppo::plusAllComboCounter();
    }
    else { // this Hyper Block B is in the current Block, so dont plus the counter
        
        if (isInFeverTime == true) {
            exObj->setBlockType(HBA_BLOCK_TYPE);
        }
        else {
            exObj->setBlockType(NORMAL_BLOCK_TYPE);
        }
    }
    
    for (int i = 6; i >= 0 ; i--) {
        TPObjectExtension* block1 = TakasuPoppo::coorToExObj(ccp(x, i));
        if (block1 != NULL && i != y && block1->getSprite() != NULL && block1->getID() != 7 && block1->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) TakasuPoppo::cleanOneBlock(block1);
        
        TPObjectExtension* block2 = TakasuPoppo::coorToExObj(ccp(i, y));
        if (block1 != NULL && i!=x && block2->getSprite() != NULL && block2->getID() != 7 && block2->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) TakasuPoppo::cleanOneBlock(block2);
        
    }
    

    if (exObj->getID() != 7 || exObj->getSprite() != NULL) TakasuPoppo::cleanSprite(exObj);
    
}

void TakasuPoppo::cleanOneBlock(TPObjectExtension* exobj){
    switch (exobj->getBlockType()) {
        case HBA_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockA(exobj);
            break;
            
        case HBB_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
//            TakasuPoppo::exPopBlast(exobj->getPosition());
            TakasuPoppo::exPopBlast(ccp(400, 400));
            break;
            
        case HBC_BLOCK_TYPE:
//            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
//                TakasuPoppo::cleanHyperBlockC(exobj);
            break;
        case MB1_BLOCK_TYPE:
            if (gameTimer >= 0) {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
                isCleanMB1 = true;
            }
            else TakasuPoppo::cleanSprite(exobj);
            
            break;
        case MB2_BLOCK_TYPE:
            if (gameTimer >= 0) {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
                isCleanMB2 = true;
                isExistMB2 = false;

            } else {
                TakasuPoppo::cleanSprite(exobj);
            }

            break;
        case MB3_BLOCK_TYPE:
            isCleanMB3 = true;
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;

        case (MB1_BLOCK_TYPE + 10):
            if (gameTimer >= 0) {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
                isCleanMB1 = true;
            }
            else TakasuPoppo::cleanSprite(exobj);
            
            break;
        case (MB2_BLOCK_TYPE + 10):
            if (gameTimer >= 0) {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
                isCleanMB2 = true;
                isExistMB2 = false;
                
            } else {
                TakasuPoppo::cleanSprite(exobj);
            }
            
            break;
        case (MB3_BLOCK_TYPE + 10):
            isCleanMB3 = true;
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;

        case MOVED_HBA_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockA(exobj);
            break;
        case MOVED_HBB_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            TakasuPoppo::exPopBlast(exobj->getPosition());
            break;
        case NORMAL_BLOCK_TYPE:
            if (isInFeverTime == true) {
                // in fever time and this block is in currentBlockSet, we clean blocks around like Hyper Block A
                if (isInCurrentBlockSet(exobj)) {
                    currentBlockSet->removeObject(exobj);
                    if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                        TakasuPoppo::cleanHyperBlockA(exobj);

                }
                else {
                    if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
                }
                
            } else {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
            }
            
            break;
        case MOVED_NORMAL_BLOCK_TYPE + 10:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
            
        case (MOVED_HBA_BLOCK_TYPE + 10):
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
        case (MOVED_HBB_BLOCK_TYPE + 10):
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            TakasuPoppo::exPopBlast(exobj->getPosition());
            break;

            
        default:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;
    }
}

void TakasuPoppo::makeBlockToBeHBC(TPObjectExtension *exObj){
    exObj->setBlockType(HBC_BLOCK_TYPE);
    exObj->setID(8);

    CCAnimation *animation = CCAnimation::create();
    for (int i = 1; i < 8; i++) {
        char fileName[15] = {0};
        sprintf(fileName, "Poppo%dA.png", i);
        animation->addSpriteFrameWithFileName(fileName);
        
    }
    animation->setDelayPerUnit(0.05f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(MAXFLOAT);
    CCAnimate* animate = CCAnimate::create(animation);
    animate->setTag(1210);
    exObj->getSprite()->runAction(animate);
}

bool TakasuPoppo::isInCurrentBlockSet(TPObjectExtension *exObj){
    // if this Hyper Block is not in current block, plus 1 to combo and fever Counter
    CCObject* obj;
    if (currentBlockSet != NULL && currentBlockSet->count() > 0) {
        CCARRAY_FOREACH(currentBlockSet, obj){
            if (obj != NULL ) {
                TPObjectExtension* block = dynamic_cast<TPObjectExtension*>(obj);
                if (block->getGid() == exObj->getGid()) {
                    return true;
                }
                
            }
        }        
    }
    
    return false;
    
}

bool TakasuPoppo::isValidEx(TPObjectExtension * ex){
//    if (ex != NULL && (checkCreateHyperB(ex->getCoordination(), ex->getID()) || ex->getBlockType() == 13)) {
//        return false;
//    }
    if(ex != NULL && ex->getID() != 7 && ex->getSprite() && ex->getSprite() != NULL && ex->getBlockType() < MOVED_NORMAL_BLOCK_TYPE)
            return true;
    else    return false;
}

void TakasuPoppo::cleanA(TPObjectExtension* exObj){
    
    CCPoint aPoint = exObj->getCoordination();
    int x = aPoint.x;
    int y = aPoint.y;
    
    CCPoint bPoint = ccp( x, y - 1);
    CCPoint cPoint = ccp(x + 1, y - 1);
    CCPoint dPoint = ccp(x + 1, y);
    CCPoint ePoint = ccp(x + 1, y + 1);
    CCPoint gPoint = ccp(x, y + 1);
    CCPoint hPoint = ccp(x - 1, y + 1);
    CCPoint iPoint = ccp(x - 1, y);
    CCPoint kPoint = ccp(x - 1, y - 1);
    
    
    //exObj->setBlockType(0);
    
    TPObjectExtension *bExObj = TakasuPoppo::coorToExObj(bPoint);
    TPObjectExtension *cExObj = TakasuPoppo::coorToExObj(cPoint);
    TPObjectExtension *dExObj = TakasuPoppo::coorToExObj(dPoint);
    TPObjectExtension *eExObj = TakasuPoppo::coorToExObj(ePoint);
    TPObjectExtension *gExObj = TakasuPoppo::coorToExObj(gPoint);
    TPObjectExtension *hExObj = TakasuPoppo::coorToExObj(hPoint);
    TPObjectExtension *iExObj = TakasuPoppo::coorToExObj(iPoint);
    TPObjectExtension *kExObj = TakasuPoppo::coorToExObj(kPoint);
    
    if (bExObj != NULL && bExObj->getSprite() != NULL && bExObj->getID() != 7) {
        
        TakasuPoppo::cleanOneBlock(bExObj);
    }
    
    if (cExObj != NULL && cExObj->getSprite() != NULL && cExObj->getID() != 7) {
        
        TakasuPoppo::cleanOneBlock(cExObj);
    }
    
    if (dExObj != NULL && dExObj->getSprite() != NULL && dExObj->getID() != 7) {
        
        TakasuPoppo::cleanOneBlock(dExObj);
    }
    
    if (eExObj != NULL && eExObj->getSprite() != NULL && eExObj->getID() != 7) {
        
        TakasuPoppo::cleanOneBlock(eExObj);
    }
    
    if (gExObj != NULL && gExObj->getSprite() != NULL && gExObj->getID() != 7) {
        
        TakasuPoppo::cleanOneBlock(gExObj);
    }
    
    if (hExObj != NULL && hExObj->getSprite() != NULL && hExObj->getID() != 7) {
        
        TakasuPoppo::cleanOneBlock(hExObj);
    }
    
    if (iExObj != NULL && iExObj->getSprite() != NULL && iExObj->getID() != 7) {
        
        TakasuPoppo::cleanOneBlock(iExObj);
    }
    
    if (kExObj != NULL && kExObj->getSprite() != NULL && kExObj->getID() != 7) {
        
        TakasuPoppo::cleanOneBlock(kExObj);
    }
}

void TakasuPoppo::cleanB(TPObjectExtension* exObj) {
    
    int x = exObj->getCoordination().x;
    int y = exObj->getCoordination().y;
    
    for (int i = 6; i >= 0 ; i--) {
        TPObjectExtension* block1 = TakasuPoppo::coorToExObj(ccp(x, i));
        if (i != y && block1->getSprite() != NULL && block1->getID() != 7 && block1->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) TakasuPoppo::cleanOneBlock(block1);

        TPObjectExtension* block2 = TakasuPoppo::coorToExObj(ccp(i, y));
        if (i!=x && block2->getSprite() != NULL && block2->getID() != 7 && block2->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) TakasuPoppo::cleanOneBlock(block2);
        
    }
    
    TakasuPoppo::exPopBlast(exObj->getPosition());

}

//==============================clean Block ===========
// call when time out
void TakasuPoppo::cleanHyperBlockA(CCNode* sender, void* data){
    
    TPObjectExtension* exObj = (TPObjectExtension*)data;
    plusAllComboCounter();
    CCPoint aPoint = exObj->getCoordination();
    int x = aPoint.x;
    int y = aPoint.y;
    
    CCPoint bPoint = ccp( x, y - 1);
    CCPoint cPoint = ccp(x + 1, y - 1);
    CCPoint dPoint = ccp(x + 1, y);
    CCPoint ePoint = ccp(x + 1, y + 1);
    CCPoint gPoint = ccp(x, y + 1);
    CCPoint hPoint = ccp(x - 1, y + 1);
    CCPoint iPoint = ccp(x - 1, y);
    CCPoint kPoint = ccp(x - 1, y - 1);
    
    
    exObj->setBlockType(NORMAL_BLOCK_TYPE);
    
    TPObjectExtension *bExObj = TakasuPoppo::coorToExObj(bPoint);
    TPObjectExtension *cExObj = TakasuPoppo::coorToExObj(cPoint);
    TPObjectExtension *dExObj = TakasuPoppo::coorToExObj(dPoint);
    TPObjectExtension *eExObj = TakasuPoppo::coorToExObj(ePoint);
    TPObjectExtension *gExObj = TakasuPoppo::coorToExObj(gPoint);
    TPObjectExtension *hExObj = TakasuPoppo::coorToExObj(hPoint);
    TPObjectExtension *iExObj = TakasuPoppo::coorToExObj(iPoint);
    TPObjectExtension *kExObj = TakasuPoppo::coorToExObj(kPoint);
    
    if (bExObj != NULL && bExObj->getSprite() != NULL && bExObj->getID() != 7 && bExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(bExObj);
    }
    
    if (cExObj != NULL && cExObj->getSprite() != NULL && cExObj->getID() != 7 && cExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(cExObj);
    }
    
    if (dExObj != NULL && dExObj->getSprite() != NULL && dExObj->getID() != 7 && dExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(dExObj);
    }
    
    if (eExObj != NULL && eExObj->getSprite() != NULL && eExObj->getID() != 7 && eExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(eExObj);
    }
    
    if (gExObj != NULL && gExObj->getSprite() != NULL && gExObj->getID() != 7 && gExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(gExObj);
    }
    
    if (hExObj != NULL && hExObj->getSprite() != NULL && hExObj->getID() != 7 && hExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(hExObj);
    }
    
    if (iExObj != NULL && iExObj->getSprite() != NULL && iExObj->getID() != 7 && iExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(iExObj);
    }
    
    if (kExObj != NULL && kExObj->getSprite() != NULL && kExObj->getID() != 7 && kExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(kExObj);
    }
    
    if (exObj->getSprite() != NULL || exObj->getID() != 7) TakasuPoppo::cleanSprite(exObj);
    
}

void TakasuPoppo::cleanHyperBlockB(CCNode* sender, void* data) {
    TPObjectExtension* exObj = (TPObjectExtension*)data;
    int x = exObj->getCoordination().x;
    int y = exObj->getCoordination().y;

    TakasuPoppo::plusAllComboCounter();

    if (isInFeverTime == true) {
        exObj->setBlockType(HBA_BLOCK_TYPE);
    }
    else {
        exObj->setBlockType(NORMAL_BLOCK_TYPE);
    }
    
    for (int i = 0; i < 7; i++) {
        TPObjectExtension* block1 = TakasuPoppo::coorToExObj(ccp(x, i));
        if (block1->getSprite() != NULL && block1->getID() != 7  && block1->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) TakasuPoppo::cleanOneBlock(block1);
        
        TPObjectExtension* block2 = TakasuPoppo::coorToExObj(ccp(i, y));
        if (block2->getSprite() != NULL && block2->getID() != 7 && block2->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) TakasuPoppo::cleanOneBlock(block2);
    }

    if (exObj->getID() != 7 || exObj->getSprite() != NULL) TakasuPoppo::cleanSprite(exObj);
}


void TakasuPoppo::cleanHyperBlockC(CCNode* sender, void* data) {
    TPObjectExtension* exObj = (TPObjectExtension*)data;
    plusAllComboCounter();
    
    exObj->setBlockType(NORMAL_BLOCK_TYPE);
    // random an ID and clean all block with this ID
    if(exObj->getSprite() != NULL)
        exObj->getSprite()->stopActionByTag(1210);
    int a = rand() % 7;
    exObj->setID(a);
    int imageId = exObj->getID() + 1;
    CCImage *poppoC = new CCImage;
    string str = static_cast<ostringstream*>( &(ostringstream() << imageId) )->str();
    str = "Poppo" + str + "A.png";
    poppoC->initWithImageFile(str.c_str());
    CCTexture2D *poppoTexture = new CCTexture2D;
    poppoTexture->initWithImage(poppoC);
    CCSprite *poppoSprite = exObj->getSprite();
    poppoSprite->setTexture(poppoTexture);
    exObj->setSprite(poppoSprite);
    
    CCObject* obj;
    CCARRAY_FOREACH(colorArray, obj){
        TPObjectExtension* block = dynamic_cast<TPObjectExtension* >(obj);
        if (block != NULL && block->getID() == exObj->getID() &&
            block->getID() != 7 && block->getSprite() != NULL) {
            CCSprite *cloneSprite = CCSprite::createWithTexture(poppoTexture);
            
            cloneSprite->setPosition(block->getSprite()->getPosition());
            cloneSprite->setZOrder(500);
            this->addChild(cloneSprite);
            
            cloneSprite->runAction(CCSequence::create(
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable),(void*)block),
                                                      CCScaleTo::create(HBC_SCALE_DELAY, 1.5f),
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::cleanOneBlock),(void*)block),
                                                      CCRemoveSelf::create(true),
                                                      NULL));
            
        }
    }
    
    isHBCinBlockSet = true;

}

void TakasuPoppo::cleanHyperBlockC(TPObjectExtension* exObj){
    plusAllComboCounter();
    
    isHBCinBlockSet = true;
    exObj->setBlockType(NORMAL_BLOCK_TYPE);
    // random an ID and clean all block with this ID
    exObj->getSprite()->stopActionByTag(1210);
    int a = rand() % 7;
    exObj->setID(a);
    int imageId = exObj->getID() + 1;
    CCImage *poppoC = new CCImage;
    string str = static_cast<ostringstream*>( &(ostringstream() << imageId) )->str();
    str = "Poppo" + str + "A.png";
    poppoC->initWithImageFile(str.c_str());
    CCTexture2D *poppoTexture = new CCTexture2D;
    poppoTexture->initWithImage(poppoC);
    CCSprite *poppoSprite = exObj->getSprite();
    poppoSprite->setTexture(poppoTexture);
    exObj->setSprite(poppoSprite);
    
    CCObject* obj;
    CCARRAY_FOREACH(colorArray, obj){
        TPObjectExtension* block = dynamic_cast<TPObjectExtension* >(obj);
        if (block != NULL && block->getID() == exObj->getID() &&
            block->getID() != 7 && block->getSprite() != NULL) {
            CCSprite *cloneSprite = CCSprite::createWithTexture(poppoTexture);
            
            cloneSprite->setPosition(block->getSprite()->getPosition());
            cloneSprite->setZOrder(500);
            this->addChild(cloneSprite);            
            cloneSprite->runAction(CCSequence::create(
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable),(void*)block),
                                                      CCScaleTo::create(HBC_SCALE_DELAY, 1.5f),
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::cleanOneBlock),(void*)block),
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::changeID),(void*)block),
                                                      CCRemoveSelf::create(true),
                                                      NULL));
            
        }
    }
    


}
void TakasuPoppo::cleanOneBlock(cocos2d::CCNode *sender, void *data){
    TPObjectExtension *exobj = (TPObjectExtension*)data;
    switch (exobj->getBlockType()) {
        case HBA_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockA(exobj);
            break;
            
        case HBB_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            TakasuPoppo::exPopBlast(exobj->getPosition());
            break;
            
        case HBC_BLOCK_TYPE:
            //            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
            //                TakasuPoppo::cleanHyperBlockC(exobj);
            break;
        case MB1_BLOCK_TYPE:
            if (gameTimer >= 0) {
                isCleanMB1 = true;
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
            }
            else TakasuPoppo::cleanSprite(exobj);
            
            break;
        case MB2_BLOCK_TYPE:
            if (gameTimer >= 0) {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
                isCleanMB2 = true;
                isExistMB2 = false;
                
            } else {
                TakasuPoppo::cleanSprite(exobj);
            }
            
            break;
        case MB3_BLOCK_TYPE:
            isCleanMB3 = true;
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;

        case (MB1_BLOCK_TYPE + 10):
            if (gameTimer >= 0) {
                isCleanMB1 = true;
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
            }
            else TakasuPoppo::cleanSprite(exobj);
            
            break;
        case (MB2_BLOCK_TYPE + 10):
            if (gameTimer >= 0) {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
                isCleanMB2 = true;
                isExistMB2 = false;
                
            } else {
                TakasuPoppo::cleanSprite(exobj);
            }
            
            break;
        case (MB3_BLOCK_TYPE + 10):
            isCleanMB3 = true;
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;

        case MOVED_HBA_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockA(exobj);
            break;
        case MOVED_HBB_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            TakasuPoppo::exPopBlast(exobj->getPosition());
            break;
        case NORMAL_BLOCK_TYPE:
            if (isInFeverTime == true) {
                // in fever time and this block is in currentBlockSet, we clean blocks around like Hyper Block A
                if (isInCurrentBlockSet(exobj)) {
                    currentBlockSet->removeObject(exobj);
                    if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                        TakasuPoppo::cleanHyperBlockA(exobj);
                    
                }
                else {
                    if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                        TakasuPoppo::cleanSprite(exobj);
                }
                
            } else {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
            }
            
            break;
        case MOVED_NORMAL_BLOCK_TYPE + 10:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
            
        case (MOVED_HBA_BLOCK_TYPE + 10):
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
        case (MOVED_HBB_BLOCK_TYPE + 10):
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            TakasuPoppo::exPopBlast(exobj->getPosition());
            break;
            
            
        default:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;
    }
}

float TakasuPoppo::setCleanDelay(){
    if (isHBCinBlockSet) {
        fallDistance = 6;
        gbFallDistance = 7;
        logicDelayTime = AFTER_CLEAN_FALL_TIME*fallDistance + GENERATE_FALL_TIME*gbFallDistance + SWAP_TIME*2 + CLEAN_DELAY + POP_ANIMATION_DELAY + HBC_SCALE_DELAY;
        return (HBC_SCALE_DELAY + CLEAN_DELAY + POP_ANIMATION_DELAY);
    } else {
        logicDelayTime = AFTER_CLEAN_FALL_TIME*fallDistance + GENERATE_FALL_TIME*gbFallDistance + SWAP_TIME*2 + CLEAN_DELAY + POP_ANIMATION_DELAY;
        return (CLEAN_DELAY + POP_ANIMATION_DELAY);
    }
}

void TakasuPoppo::plusAllComboCounter(){
    // count the combo to generate hyper block
    hbcComboCounter += 1;
    if (hbcComboTimer <= 0) hbcComboTimer = HBC_COMBO_MAXTIME;

    // count the combo for the Fever Time
    feverCounter += 1;
    
    //count the combo for the Gauge Bar
    gaugeComboCounter += 1;
    if (gaugePeriod != GAUGE_PERIOD) {
        gaugePeriod = GAUGE_PERIOD;
    }
    
    // count the really combo
    ComboCounter += 1;
    if (ComboTimer != (3 + increaseComboTimes)) ComboTimer = (3 + increaseComboTimes);
    
}

void TakasuPoppo::deleteMainSprite()
{
   // returnNormalSprite(mainSprite);
    mainSprite = NULL;
}
