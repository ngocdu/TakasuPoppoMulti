//
//  TPEndGameScreen.h
//  Cocos2Dx
//
//  Created by macbook_017 on 8/12/13.
//
//

#ifndef __TaKaSuPoppo__TPEndGameScreen__
#define __TaKaSuPoppo__TPEndGameScreen__

#include <iostream>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "TPUser.h"
#include "TPSocialScreen.h"

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;
USING_NS_CC;

class TPRegisterScreen:public CCLayer, extension::CCEditBoxDelegate {
    private :
    CCSize winSize;
    float w, h;
    CCLabelTTF *emailInvalidMsg;
    CCLabelTTF *nameInvalidMsg;
    CCEditBox *editBoxUserEmail;
    CCEditBox *editBoxUserName;
    CCLabelTTF *m_pTTFShowEditReturn;
    CCMenu *Menu;
public:
    virtual bool init();
    static CCScene *scene();
    
    void toExtensionsMainLayer(CCObject *sender);
    
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox,const string& text);
    virtual void editBoxReturn(CCEditBox* editBox);
    
    void SendData(CCObject *pSender);
       
    bool isValidEmail(string str);
    
    void convertName(char *str);
    void insertChar(char *str, int index);
    void standardSizeName(char *str);
    void removeSpace(char *str);
    
    CREATE_FUNC(TPRegisterScreen);
};

#endif