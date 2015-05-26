//
//  RecordDayScene.h
//  MyTeeth
//
//  Created by Penny on 15/5/27.
//
//

#ifndef __MyTeeth__RecordDayScene__
#define __MyTeeth__RecordDayScene__

#include "Header.h"

using namespace cocos2d::ui;

class RecordDayScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void loadView();
    
    void menuCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(RecordDayScene);
    
    void updateRecord(int y, int m, int d);
    
    virtual void onEnter();
    virtual void onExit();
    
    int year;
    int month;
    int day;
    
    cocos2d::Label* date_lb;
    cocos2d::Label* time_lb;
};

#endif /* defined(__MyTeeth__RecordDayScene__) */
