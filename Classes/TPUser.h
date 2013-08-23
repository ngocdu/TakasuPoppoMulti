//
//  TPUser.h
//  Cocos2Dx
//
//  Created by macbook_017 on 8/12/13.
//
//
#ifndef __TaKaSuPoppo__TPUser__
#define __TaKaSuPoppo__TPUser__

#define IP_SERVER "https://takasuapp.com/takasu_poppo"
//#define IP_SERVER ""


#include "cocos2d.h"

using namespace  cocos2d;
using namespace std;

USING_NS_CC;

class TPUser :public CCObject {
private:
    string _serverIP;

public:
    TPUser();
    static TPUser* shareTPUser();
    
    string getUserName();
    void setUserName(string name);
    
    string getUserEmail();
    void setUserEmail(string email);
    
    int getUserScore();
    void setUserScore(int score);
    
    int getUserReward();
    void setUserReward(int reward);
    
    string getServerIp();
    void setServerIp(string ip);
    
    int getUserHeart();
    void setUserHeart(int heart);

    
    int getCrystal();
    void setCrystal(int crystal);
    
    bool ExistUser();
//    void setExistUser(bool existUser);
    
    float getLastTime();
    void setLastTime(float lastTime);
    
    float getBMG();
    void setBMG(float bmg);

    float getVolume();
    void setVolume(float volume);

    int getScoreLowestTopRanking();
    void setScoreLowestTopRanking(int scoreLowest);

};

#endif