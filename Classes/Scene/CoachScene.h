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
    
    TeethLayer * m_teethLy;

    bool b_gameIsStart;
    bool b_gameIsFinished;

    void setGameStart(bool isStart);
    
    //void update(float dt);
    
    void updateCustom(float dt);
    void updateTimeAndTooth(int time);
    
    void backToMain();
    void goonGame();
    
private:
    
    cocos2d::EventListenerTouchOneByOne* listener;

    int model;
    
    int i_limit_time;
    int i_cur_time;

    cocos2d::Label *p_timerLb;
};
#endif /* defined(__MyTeeth__CoachScene__) */
