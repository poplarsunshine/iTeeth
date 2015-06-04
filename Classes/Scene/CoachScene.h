//
//  CoachScene.h
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#ifndef __MyTeeth__CoachScene__
#define __MyTeeth__CoachScene__

#include "Header.h"
#include "TeethLayer.h"

class CoachScene : public cocos2d::Layer, public TeethLayerDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void loadView();

    void menuCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(CoachScene);
    
    virtual void onEnter();
    virtual void onExit();
    
    void brushNotification(cocos2d::Ref* obj);

    TeethLayer * m_teethLy;

    bool b_gameIsStart;
    bool b_gameIsFinished;

    void setGameStart(bool isStart);
    
    void startTimeLbAnimation();
    
    void updateCustom(float dt);
    void updateTimeAndTooth(int time);
    void setTimeMax(cocos2d::Ref* pSender);
    void startTimer(float dt);

    void backToMain();
    void goonGame();
    
    int GetDayOfWeek();
    
    cocos2d::Vector<cocos2d::Sprite*> m_starNormalList;
    cocos2d::Vector<cocos2d::Sprite*> m_starSelectList;

private:
    
    cocos2d::EventListenerTouchOneByOne* listener;

    int model;
    
    float ready_time = 4.0f;
    
    int i_limit_time;
    int i_cur_time;

    int i_score;
    cocos2d::Label *p_timerLb;
    cocos2d::Label *p_scoreLb;
};
#endif /* defined(__MyTeeth__CoachScene__) */
