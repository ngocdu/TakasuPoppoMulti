//
//  TPSocial.h
//  Cocos2Dx
//
//  Created by Kien MetalRock on 8/16/13.
//
//

#ifndef __Cocos2Dx__TPSocial__
#define __Cocos2Dx__TPSocial__

#include <iostream>

#include "cocos2d.h"
#include "TPMainScreen.h"
#include "TPUser.h"

using namespace  cocos2d;
USING_NS_CC;

class TPSocialScreen :public CCLayer {
private:
    CCSize _screenSize;
    float w, h;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
public:
    virtual bool init();
    static CCScene * scene();
    
    void Line();
    void Face();
    void Tweet();
    
    void Close();
    
    CREATE_FUNC(TPSocialScreen);
};



#endif /* defined(__Cocos2Dx__TPSocial__) */
