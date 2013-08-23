//  Created by MinhNT on 13/05/16.
//  Copyright FRAMGIA 2013年. All rights reserved.
//

#include "TakasuPoppo.h"
#include "SimpleAudioEngine.h"
#include "TPObjectExtension.h"
#include "TPBlockSet.h"
#include "CCGestureRecognizer.h"
#include "TPMainScreen.h"
#include "TPUser.h"
#include "TPSocialScreen.h"


using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


#pragma mark Default

CCScene* TakasuPoppo::scene(TPItemObject* itemObjectD) {
    CCScene *scene = CCScene::create();
    TakasuPoppo *layer = TakasuPoppo::create(itemObjectD);
    scene->addChild(layer);
    return scene;
}

bool TakasuPoppo::init(TPItemObject* itemObject) {
    srand(time(NULL));
    _itemObject = new TPItemObject(itemObject->getIsFirstItemOn(), itemObject->getIsSecondItemOn(), itemObject->getIsThirdItemOn(), itemObject->getSpecialItemID());

    if(_itemObject->getIsFirstItemOn())
    {
        createThreeeHyper = true;
    }
    if(_itemObject->getIsSecondItemOn())
    {
        addTime();
    }
    if(_itemObject->getIsThirdItemOn())
    {
        increasedScores();
    }
    
    if (!CCLayer::init()) return false;
    
    colorArray = new CCArray;
    toDestroyArray = new CCArray;
    pickedArray = new CCArray;
    hintArray = new CCArray;
    tempHBCArray = new CCArray;
    
    TakasuPoppo::addBlocksToArray();
    
    TakasuPoppo::addTileMap();
    TakasuPoppo::lookForMatches();
    
    controlable = true;
    
    //========================= New Init ============================
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    hbcComboCounter = 0;
    hbcComboTimer = 0;
    
    executionTime = 3.5;
    endTimeCounter = 4.5;
    hintCounter = 3;
    
    movingSpeed = AFTER_CLEAN_FALL_TIME;
    gameTimer = PLAY_TIME;
    
    counterExist1 = false;
    counterExist2 = false;
    counterExist3 = false;
    
    prepareToEnd = false;
    timeOverOn = false;
    takasuBonusOn = false;
    
    gridOn = false;
    
    debugRun = 0;
    
    score = 0;
    ComboScoreRequired = 1;
    
    // Vinhnt - for fever time
    feverTimer = 0;           //Timer for Fever Time
    feverTimeLimit = 3;
    feverCounter = 0;           //Counter for Fever Time
    isCreateFeverTime = false;
    isInFeverTime = false;
    
    hyperC = 10;
    hyperBlockC = false;
    //Vinhnt - for Gauge Combo
    gaugeComboCounter = 0;
    isCreateGaugeCombo = false;
    lastGaugeCombo = 0;
    gaugePeriod = GAUGE_PERIOD;
    
    //item
    timeBonus = 0;
    increasedScore = 1;
    doubleScore = 1;
    endLastScore = false;
    createThreeeHyper = false;
    increaseComboTimes = 0;
    lastScores = 0;
    scoresBeforeLastBonus = 0;
    //moveto
    move =false;
    mainPoint = CCPoint();
    swape = true;
    runningAfter = false;
    boolMoveTo = new CCArray();
    boolAfterClean = new CCArray();
    //time----
    endTime = false;
    
    // fixed hyper block C
    isHBCinBlockSet = false;
    createB = false;
    currentBlockSet = NULL;
    
    // Vinhnt - for the really combo
    ComboTimer = 0;           //Timer for combos
    ComboCounter = 0;           //Counter for combos
    
    //Vinhnt - plus combo just in 1 function
    plusAllComboCounter();
    
    //Vinhnt - logic Delay
    executingLogic = false;
    logicCounter = 0;
    logicDelayTime = LOGIC_DELAY;
    isMatchListDone = false;
    // set logic Delay time in a dynamic way
    fallDistance = 0; // after clean and generate block fall distance is the same.
    gbFallDistance = 0;
    
    swapruning = false;
    
    //===============================================================
    
    //========================= Debugs =============================
//    debugTilesArray = new CCArray;
//    TakasuPoppo::setupDebugButton();
//    
//    sprintf(comboCounterString, "Combo: %i", hbcComboCounter);
//    comboCounterLabel = CCLabelTTF::create(comboCounterString, "Arial", FONT_SIZE);
//    comboCounterLabel->setZOrder(15);
//    comboCounterLabel->setColor(ccc3(225, 225, 225));
//    comboCounterLabel->setPosition(ccp(80, 850));
//    
//    sprintf(comboTimerString, "Timer: %f", hbcComboTimer);
//    comboTimerLabel = CCLabelTTF::create(comboTimerString, "Arial", FONT_SIZE);
//    comboTimerLabel->setZOrder(15);
//    comboTimerLabel->setColor(ccc3(225, 225, 225));
//    comboTimerLabel->setPosition(ccp(330, 850));
//    
//    this->addChild(comboCounterLabel);
//    this->addChild(comboTimerLabel);
    //===============================================================
    
    //==========================SCORE ===============================
//    CCLabelTTF* lbScoreTitle = CCLabelTTF::create("SCORE", "Arial", FONT_SIZE);
//    lbScoreTitle->setZOrder(15);
//    lbScoreTitle->setColor(ccc3(225, 225, 225));
//    lbScoreTitle->setPosition(ccp(80, 920));
//    this->addChild(lbScoreTitle);
    
    
    string str = static_cast<ostringstream*>( &(ostringstream() << score) )->str();
    bmScore = CCLabelBMFont::create(str.c_str(), "TakasuScore.fnt", 30, kCCTextAlignmentLeft);
    bmScore->setZOrder(15);
    bmScore->setPosition(ccp(160, winSize.height - 40));
    this->addChild(bmScore);
    //===============================================================
    
    //======================== Interface ============================
    CCSprite *background = CCSprite::create("poppo_background2.png");
    background->setPosition(ccp(winSize.width / 2,
                                winSize.height / 2 + 33));
    this->addChild(background, -3, -1);
    
    CCSprite *upperCover = CCSprite::create("UpperCover.png");
    upperCover->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 450));
    this->addChild(upperCover, 10, -4);
    
    CCSprite *ideGauge = CCSprite::create("ComboGaugeCircle.png");
    ideGauge->setPosition(ccp(330, winSize.height - 40));
    this->addChild(ideGauge, 13, -2);
    
    CCSprite *comboGauge = CCSprite::create("ComboBarOut.png");
    comboGauge->setPosition(ccp(440, winSize.height - 40));
    this->addChild(comboGauge, 11, -3);
    
    CCSprite *timerBar = CCSprite::create("TimeBarOut.png");
    timerBar->setPosition(ccp(winSize.width / 2 - 2, 136));
    this->addChild(timerBar, -2, -3);
    
    CCSprite *bottomCover = CCSprite::create("BottomCover.png");
    bottomCover->setPosition(ccp(winSize.width / 2, 40));
    this->addChild(bottomCover, -2);
    
    //===============================================================
    
    //======================== Item Object ==========================
    
    _spcialItemID = _itemObject->getSpecialItemID() ;
    CCLog("special item: %d", _spcialItemID);
    switch (_spcialItemID) {
        case SPECIAL_ITEM_1_ID:
            timeToCreateMB1 = rand() % (PLAY_TIME/2) + (PLAY_TIME/3) ;
            isCleanMB1 = false;
            isCreateMB1 = false;
            CCLog("time will create MB1: %i", timeToCreateMB1);
            break;
            
        case SPECIAL_ITEM_2_ID:
            timeToCreateMB2 = rand() % PLAY_TIME;
            isCleanMB2 = false;
            isCreateMB2 = false;
            isExistMB2 = false;
            countMB2 = 0;
            CCLog("time will create MB2: %i", timeToCreateMB2);
            break;
            
        case SPECIAL_ITEM_4_ID:
            doubleScoreStartTime = 0;
            isCleanMB3 = false;
            isCreateMB3 = false;
            timeToCreateMB3 = rand() % (PLAY_TIME/2) + (PLAY_TIME/2);
            CCLOG("Time to create MB2: %d", timeToCreateMB3);
            
        case SPECIAL_ITEM_5_ID:
            increaseComboTimes = ITEM_INCREASE_COMBOTIME;
            break;
            
        default:
            break;
    }
    
    //===============================================================
    
    hintCount = TakasuPoppo::lookForMatches();
    
    this->scheduleUpdate();
    
    this->schedule(schedule_selector(TakasuPoppo::startGame));
    
//    this->setTouchEnabled(true);
    
    //this->schedule(schedule_selector(TakasuPoppo::fixedUpdate));
    
//    this->scheduleOnce(schedule_selector(TakasuPoppo::timeSetup), 0);
//    
//    this->schedule(schedule_selector(TakasuPoppo::timeCounter));
//    
//    this->schedule(schedule_selector(TakasuPoppo::refreshWhenNoCombo), 2);
    
    this->schedule(schedule_selector(TakasuPoppo::matchList));
    return true;
}

void TakasuPoppo::startGame() {
    hintCounter = 5;
    executionTime -= deltaTime;
    this->setTouchEnabled(false);
    
    
    CCSprite *counter3 = CCSprite::create("Ready.png");
    //CCSprite *counter2 = CCSprite::create("Counter2.png");
    CCSprite *counter1 = CCSprite::create("Go.png");
    
    counter3->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    //counter2->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    counter1->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    
    counter3->setTag(403);
    //counter2->setTag(402);
    counter1->setTag(401);
    
    if (executionTime < 3) {
        if (!counterExist3) this->addChild(counter3, 5);
        counterExist3 = true;
    }
    if (executionTime < 2) {
        if (counterExist3) this->removeChildByTag(403, true);
        counterExist3 = false;
        
        counterExist2 = true;
    }
    if (executionTime < 1) {
        counterExist2 = false;
        
        if (!counterExist1) this->addChild(counter1, 5);
        counterExist1 = true;
    }
    if (executionTime <= 0) {
        if (counterExist1) this->removeChildByTag(401, true);
        counterExist1 = false;
        
        TakasuPoppo::swipeSetup();
        
        this->setTouchEnabled(true);
        
        //this->schedule(schedule_selector(TakasuPoppo::fixedUpdate));
        
        this->scheduleOnce(schedule_selector(TakasuPoppo::timeSetup), 0);
        this->schedule(schedule_selector(TakasuPoppo::timeCounter));        
        this->schedule(schedule_selector(TakasuPoppo::refreshWhenNoCombo), 2);
        
        this->unschedule(schedule_selector(TakasuPoppo::startGame));
    }
}

void TakasuPoppo::endGame() {
    endTimeCounter -= deltaTime;
    
    CCSprite *counter3 = CCSprite::create("TimeUp.png");
    CCSprite *counter1 = CCSprite::create("LastBonus.png");
    
    counter3->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    counter1->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    
    counter3->setTag(1406);
    counter1->setTag(1404);
    
    if (endTimeCounter < 4) {
        if (!timeOverOn) this->addChild(counter3, 5);
        timeOverOn = true;
    }
    if (endTimeCounter < 3) {
        if (timeOverOn) this->removeChildByTag(1406, true);
        timeOverOn = false;
        if (!takasuBonusOn) this->addChild(counter1, 5);
        takasuBonusOn = true;
    }
    if (endTimeCounter < 2) {
        if (takasuBonusOn) this->removeChildByTag(1404, true);
        takasuBonusOn = false;
    }
    if (endTimeCounter < 1) {
        
    }
    if (endTimeCounter <= 0) {
        TakasuPoppo::timeOver();
        this->unschedule(schedule_selector(TakasuPoppo::endGame));
    }
}


void TakasuPoppo::update(float dt) {
    deltaTime = dt;
    if (executingLogic == false && isMatchListDone == true && !inTheMove && toDestroyArray->count() > 0) {
        this->unschedule(schedule_selector(TakasuPoppo::matchList));
        this->unschedule(schedule_selector(TakasuPoppo::refreshWhenNoCombo));
        executingLogic = true;
        isMatchListDone = false;
        this->scheduleOnce(schedule_selector(TakasuPoppo::logicExecution), 0);
    }

    //================== Combo related updates ======================

    if (hbcComboTimer > 0) {
        hbcComboTimer -= dt;
    }
    if (hbcComboTimer < 0) {
        hbcComboTimer = 0;
        hbcComboCounter = 0;
    }
    if (hbcComboCounter >= HBC_COMBO_MAXCOUNT) {
        hyperBlockC =true;
        hbcComboCounter = hbcComboCounter % HBC_COMBO_MAXCOUNT;
    }
    //===============================================================
    
    
    //=================== Really Combo updates ======================
    // ComboTimer is set to 3 if ComboCounter + 1 (user hit score)
    if (ComboTimer > 0) {
        ComboTimer -= dt;
    }
    if (ComboTimer < 0) {
        ComboTimer = 0;
        ComboCounter = 0;
    }
//    CCLog("ComboTimer: %f", ComboTimer);

    //===============================================================
    
    
    //=================== Hint related updates ======================

    if (hintCounter > 0) {
        hintCounter -= dt;
    }
    
    if (hintCounter <= 0 && hintDisplaying == false) {
        hintDisplaying = true;
        hintArray->removeAllObjects();
        hintCount = TakasuPoppo::lookForMatches();
        this->scheduleOnce(schedule_selector(TakasuPoppo::hintGeneration), 0);
    }
    //================================================================
    
    
    
    //=================== Swipe related updates ======================
    if (controlable) {
        if (swipeRight && swape && !runningAfter) {
            move =false;
            TakasuPoppo::swipedRight(mainSprite);
            swipeRight = false;
            swipeLeft = false;
            swipeUp = false;
            swipeDown = false;
        }
        if (swipeLeft && swape && !runningAfter) {
            move =false;
            TakasuPoppo::swipedLeft(mainSprite);
            swipeRight = false;
            swipeLeft = false;
            swipeUp = false;
            swipeDown = false;
        }
        if (swipeUp && swape && !runningAfter) {
            move =false;
            TakasuPoppo::swipedUp(mainSprite);
            swipeRight = false;
            swipeLeft = false;
            swipeUp = false;
            swipeDown = false;
        }
        if (swipeDown && swape && !runningAfter) {
            
            TakasuPoppo::swipedDown(mainSprite);
            move =false;
            swipeRight = false;
            swipeLeft = false;
            swipeUp = false;
            swipeDown = false;
        }
    }
    //================================================================
    
    
    
    //===================== Fever Time updates =======================
    
    if (feverCounter > 0) {
        
        if (feverCounter > FEVER_COMBO_REQUIRED ) {
            
            feverCounter = 0;
            feverTimer = 0;
        }
        else {
            feverTimer += dt;
            if (feverTimer > FEVER_TIME_REQUIRED) {
                feverTimer = 0;
                feverCounter = 0;
            } else {
                if (feverCounter == FEVER_COMBO_REQUIRED && isCreateFeverTime == false) {
                    isCreateFeverTime = true;
                }
            }
        }
    }
    
    if (isCreateFeverTime == true) {
        isInFeverTime = true;
        feverTimeLimit = 3;
        isCreateFeverTime = false;
    }
    
    if (isInFeverTime == true) {
        feverTimeLimit -= dt;
        
        if (!this->getChildByTag(888)) {
            burningTakasuOn = true;
            TakasuPoppo::burnOnTakasu();
        }
        
        if (feverTimeLimit < 0) {
            isInFeverTime = false;
            feverTimeLimit = 0;
            if (this->getChildByTag(888)) {
                burningTakasuOn = false;
                TakasuPoppo::burnOnTakasu();
            }
        }
        
    }
    //================================================================

    
    //========================SCORE UPDATE ===========================
    string str = static_cast<ostringstream*>( &(ostringstream() << score) )->str();
    bmScore->setString(str.c_str());
    //================================================================
    
    
    //======================== Item Object ===========================
    switch (_spcialItemID) {
        case SPECIAL_ITEM_1_ID:
            if (gameTimer < timeToCreateMB1 && isCreateMB1 == false) {
                isCreateMB1 = true;
                CCLog("time will create MB1: %i", timeToCreateMB1);
            }
            if (isCreateMB1 == true) {
                timeToCreateMB1 = -1;
            }
            if (isCleanMB1 == true) {
                this->runAction(CCSequence::create(   CCCallFunc::create(this, callfunc_selector(TakasuPoppo::destroyAllBlocks)), CCCallFunc::create(this, callfunc_selector(TakasuPoppo::generateBlocksAfterCleanMB1)),NULL));
         }
            break;
            
        case SPECIAL_ITEM_2_ID:
            if ( ( (rand() % PLAY_TIME) == timeToCreateMB2) && isCreateMB2 == false && isExistMB2 == false && countMB2 < MISSION_BLOCK2_MAX_AMOUNT) {
                isCreateMB2 = true;
                countMB2 ++;
            }
            if (isCleanMB2 == true) {
                CCLOG("count : %d",countMB2);
                CCLOG("gameTimer : %f",gameTimer);
                gameTimer += 2;
                isCleanMB2 = false;
            }
            break;
        
        case SPECIAL_ITEM_4_ID:
            
            if (gameTimer < timeToCreateMB3 && isCreateMB3 == false) {
                isCreateMB3 = true;
            }
            if (isCreateMB3 == true) {
                timeToCreateMB3 = -1;
            }
            if (isCleanMB3 == true) {
                doubleScoreStartTime = gameTimer;
                isCleanMB3 = false;
            }
            if (doubleScoreStartTime != 0) {
                if (gameTimer <= doubleScoreStartTime && gameTimer >= (doubleScoreStartTime - DOUBLE_SCORE_TIME) ) {
                    // do some code logic here
                    doubleScore = 2;
                }
                else{
                    doubleScore = 1;
                }
            }
            break;

        default:
            break;
    }
    
    //================================================================

}

void TakasuPoppo::movingBoolSwitch(float dt) {
    inTheMove = true;
    moveCounter += deltaTime;
    if (moveCounter > MOVE_TIME) {
        inTheMove = false;
        this->unschedule(schedule_selector(TakasuPoppo::movingBoolSwitch));
    }
}

void TakasuPoppo::scheduleGenerate() {
    TakasuPoppo::smartGeneration();
}

void TakasuPoppo::hintGeneration() {
    int hintCount = hintArray->count();
    if (hintCount > 0) {
        TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(hintArray->objectAtIndex(0));
        TakasuPoppo::hintSprite(exObj->getPosition());
    }
}


void TakasuPoppo::logicExecution() {
    
    if(ComboCounter >= COMBO_REQUIRED)
    {
        ComboScoreRequired = 1 + ((int)(ComboCounter/COMBO_REQUIRED)) / 10;
    }
//    this->unschedule(schedule_selector(TakasuPoppo::matchList));
//    this->unschedule(schedule_selector(TakasuPoppo::refreshWhenNoCombo));
    inCleaning = true;
    this->runAction(CCSequence::create(
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::cleanBlocks)),
                                       CCDelayTime::create(setCleanDelay()),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::afterClean)),
                                       CCDelayTime::create(AFTER_CLEAN_FALL_TIME * fallDistance + SWAP_TIME*2),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::scheduleGenerate))
                                       ,NULL));
//    CCLog("Logic Delay Time: %f", logicDelayTime);
    logicCounter = 0;
    this->schedule(schedule_selector(TakasuPoppo::logicDelaySwitch), 0);
}

void TakasuPoppo::timeSetup() {
    CCSprite *timer = CCSprite::create("TimeBarIn.png");
    timer->setAnchorPoint(ccp(0, 0));
    timerBar = CCProgressTimer::create(timer);
    
    timerBar->setType(kCCProgressTimerTypeBar);
    timerBar->setAnchorPoint(ccp(0, 0));
    
    timerBar->setPosition(30, 112);
    timerBar->setMidpoint(ccp(0, 0));
    timerBar->setBarChangeRate(ccp(1, 0));
    
    timerBar->setTag(405);
    this->addChild(timerBar, 5);
    
    CCSprite *combo = CCSprite::create("ComboBarIn.png");
    combo->setAnchorPoint(ccp(0, 0));
    comboBar = CCProgressTimer::create(combo);
    
    comboBar->setType(kCCProgressTimerTypeBar);
    comboBar->setAnchorPoint(ccp(0, 0));
    
    comboBar->setPosition(ccp(338, winSize.height - 60)); //-70 140
    comboBar->setMidpoint(ccp(0, 0));
    comboBar->setBarChangeRate(ccp(1, 0));
    
    comboBar->setTag(406);
    
    gaugeComboCounter = 0;
    
    this->addChild(comboBar, 12);
}

void TakasuPoppo::timeCounter() {
    if (gameTimer > 0) {
        gameTimer -= deltaTime;
        timerBar->setPercentage(1.66 * gameTimer);
        scoresBeforeLastBonus = score;
    }
//=================================RESET GAME =====================
    
//    if(gameTimer < 5)
//        checkResetMap();

// ===============================================================
    if (gameTimer < 0) {
        timeBonus += deltaTime;
        hintCounter = 3;
        hintArray->removeAllObjects();
        if (this->getChildByTag(778)) this->removeChildByTag(778);
        hintDisplaying = false;
        //this->setTouchEnabled(false);
        this->unschedule(schedule_selector(TakasuPoppo::hintGeneration));
        TakasuPoppo::timeOver();
        if (!prepareToEnd) {
            executionTime = 3;
            this->schedule(schedule_selector(TakasuPoppo::endGame));
            prepareToEnd = true;
        }

    }

    //====================== Gauge Bar updates =======================
    if (gaugePeriod > 0) {
        gaugePeriod -= deltaTime;
    }
    if (gaugePeriod < 0) {
        if (gaugeComboCounter >= 0) {
            gaugeComboCounter -= deltaTime/2;
        }
        else gaugeComboCounter = 0;
    }

    if (gaugeComboCounter >= 0 && gaugeComboCounter <= GAUGE_COMBO_REQUIRED) {
        comboBar->setPercentage(gaugeComboCounter * 100/GAUGE_COMBO_REQUIRED);
    }

    
    if (gaugeComboCounter >= GAUGE_COMBO_REQUIRED) {
        isCreateGaugeCombo = true;
        
    }
    
    if (gaugeComboCounter >= GAUGE_COMBO_REQUIRED) {
        comboBar->setPercentage(0);
        gaugeComboCounter = gaugeComboCounter - GAUGE_COMBO_REQUIRED;
    }
    
    //================================================================
    
}

void TakasuPoppo::timeOver() {
    
    CCObject *obj;
    CCARRAY_FOREACH(colorArray, obj){
        TPObjectExtension* exObj = dynamic_cast<TPObjectExtension*>(obj);
        exObj->setControlTrigger(false);
    }
    move = false;
    endTime = true;
    runningAfter = true;
    swape = false;
    CCBool * boolMoving = new CCBool(true);
    boolMoveTo->addObject(boolMoving);

    if (lastScore()) {
        if(_spcialItemID == SPECIAL_ITEM_3_ID)
            modefiedLastBonus();
        CCLOG("SCORE * %d",score);
        
        if (!TPUser::shareTPUser()->ExistUser()) {
            TPUser::shareTPUser()->setUserScore(score);
            CCScene *registerScene  = TPRegisterScreen::scene();
            CCTransitionScene* transition = CCTransitionSlideInT::create(1, registerScene);
            CCDirector::sharedDirector()->replaceScene(transition);


        } else if (TPUser::shareTPUser()->ExistUser()) {
            CCLOG("current lowest ranking %d: ", TPUser::shareTPUser()->getScoreLowestTopRanking());
            if (score > TPUser::shareTPUser()->getScoreLowestTopRanking()) {
               string nameUser = TPUser::shareTPUser()->getUserName();
                TakasuPoppo::removeSpace((char*)nameUser.c_str());
                
                char strScore[100] = {0};
                sprintf(strScore, "%i", score);
                string emailUser  = TPUser::shareTPUser()->getUserEmail();
                string serverIP = TPUser::shareTPUser()->getServerIp();
                
                string url = serverIP + "/users?name="+nameUser+"&point="+strScore+"&email="+emailUser;
                CURL *curl;
                CURLcode res;
                curl = curl_easy_init();
                if (curl) {
                    //133.242.203.251
                    //http://Pe4L60aeke:dhWLtJ8F1w@takasuapp.com
                    
                    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                    curl_easy_setopt(curl, CURLOPT_USERNAME, "Pe4L60aeke");
                    curl_easy_setopt(curl, CURLOPT_PASSWORD, "dhWLtJ8F1w");
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "account=kienbg");
                    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
                    //        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
                    curl_easy_setopt(curl, CURLOPT_NOPROGRESS ,1);
                    curl_easy_setopt(curl, CURLOPT_POST, true);
                    
                    res = curl_easy_perform(curl);
                    curl_easy_cleanup(curl);
                    
                    if (res == 0) {
                        CCLOG("0 response OK");
                    } else {
                        CCLog("code: %i",res);
                    }
                }
            }
            if (score > TPUser::shareTPUser()->getUserScore()) {
                TPUser::shareTPUser()->setUserScore(score);
                CCScene *socialScene = TPSocialScreen::scene();
                CCTransitionScene* transition = CCTransitionSlideInT::create(1, socialScene);
                CCDirector::sharedDirector()->replaceScene(transition);
            }
            
            CCScene *mainScene = TPMainScreen::scene(true, score);
            CCTransitionScene* transition = CCTransitionSlideInT::create(1, mainScene);
            CCDirector::sharedDirector()->replaceScene(transition);
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }
        this->unscheduleUpdate();
    }
}

//for Mission Block
TakasuPoppo* TakasuPoppo::create(TPItemObject* itemObject){
    TakasuPoppo *pRet = new TakasuPoppo();
    if (pRet && pRet->init(itemObject)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \

}

bool TakasuPoppo::checkUpdate()
{
    CCObject* obj;
    CCARRAY_FOREACH(colorArray, obj)
    {
        TPObjectExtension* exObj = dynamic_cast<TPObjectExtension*>(obj);
        if(exObj->getID() == 7)
            return true;
    }
    return false;
}

void TakasuPoppo::logicDelaySwitch(){
//    this->unschedule(schedule_selector(TakasuPoppo::matchList));
    logicCounter += deltaTime;
//    CCLog("logic counter: %f", logicCounter);
    if (logicCounter > logicDelayTime) {
//        CCObject* obj;
//        CCARRAY_FOREACH(colorArray, obj){
//            TPObjectExtension* exObj = dynamic_cast<TPObjectExtension*>(obj);
//
//            CCPoint destination = exObj->getPosition();
//            CCSprite *exSprite = exObj->getSprite();
//            CCPoint spritePos = exObj->getPosition();
//            if(exSprite != NULL)
//                spritePos.setPoint(exSprite->getPositionX(), exSprite->getPositionY());
//            if (exObj->getID() != 7) {
//                if (exSprite != NULL) {
//                    if (fabs(destination.x - spritePos.x) < 1) {
//                        exObj->setControlTrigger(true);
//                    }
//                }
//            }
//        }
        this->schedule(schedule_selector(TakasuPoppo::matchList));
        
        this->schedule(schedule_selector(TakasuPoppo::refreshWhenNoCombo));

        controlable = true;
        executingLogic = false;
        this->unschedule(schedule_selector(TakasuPoppo::logicDelaySwitch));
    }
}

void TakasuPoppo::refreshWhenNoCombo(){
    hintCount = TakasuPoppo::lookForMatches();
    if (hintCount == 0 && toDestroyArray->count() == 0 && checkRefresh()) {
        this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(TakasuPoppo::destroyAllBlocks)),
                                           CCCallFunc::create(this, callfunc_selector(TakasuPoppo::createFixture)),NULL));
    }
}

bool TakasuPoppo::checkRefresh()
{
    CCObject *object;
    CCARRAY_FOREACH_REVERSE(colorArray, object) {
        TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
        if (exObj->getID() == 7) {
            return false;
        }
    }
    return true;
    
}

void TakasuPoppo::removeSpace(char *str) {
    int len = 0;
    int i = 0;
    len=strlen(str);
    for(i=0;i<len;i++)
    {
        if(str[i] == ' ')
        {
            str[i] = '_';
        }
    }
}

float TakasuPoppo::getTime(){
    timeval time;
    gettimeofday(&time, NULL);
    unsigned long millisecs = (time.tv_sec *1000) + (time.tv_usec/1000);
    return (float)millisecs;
}



