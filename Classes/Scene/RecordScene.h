//
//  RecordScene.h
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#ifndef __MyTeeth__RecordScene__
#define __MyTeeth__RecordScene__

#include "Header.h"

using namespace cocos2d::ui;

class RecordScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void loadView();

    void leftMenuTouch(cocos2d::Ref* pSender);

    void rightMenuTouch(cocos2d::Ref* pSender);

    void menuCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(RecordScene);
    
public:
    virtual void onEnter();
    virtual void onExit();
    
    virtual void myTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
private:
    EventListenerTouchOneByOne* listener;

    cocos2d::Sprite* manSprite;
    cocos2d::Sprite* womSprite;
    
    cocos2d::Label* name_lb;
    cocos2d::Label* sex_lb;
    cocos2d::Label* age_lb;
    cocos2d::Label* score_lb;
    
    cocos2d::Label* month_lb;

    void updateAccountView();
    
    //record
private:
    Scale9Sprite* recordInfoBg;
    cocos2d::Vector<cocos2d::Label*> m_dayLabels;

    int min_y;
    int min_m;
    int max_y;
    int max_m;
    
    long beginDate;
    long nowDate;
    
    int cur_year;
    int cur_month;
    
    void updateRecordViewWithDate(int y, int m);
};
#endif /* defined(__MyTeeth__RecordScene__) */
