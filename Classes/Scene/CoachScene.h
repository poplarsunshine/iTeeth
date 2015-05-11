//
//  CoachScene.h
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#ifndef __MyTeeth__CoachScene__
#define __MyTeeth__CoachScene__

#include "cocos2d.h"

class CoachScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void loadView();

    void menuCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(CoachScene);
};
#endif /* defined(__MyTeeth__CoachScene__) */
