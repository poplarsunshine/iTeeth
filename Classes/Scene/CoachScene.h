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

private:
    
    cocos2d::EventListenerTouchOneByOne* listener;

    int model;
    
    cocos2d::Label *p_timerLb;
};
#endif /* defined(__MyTeeth__CoachScene__) */
