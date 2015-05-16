//
//  BBSScene.h
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#ifndef __MyTeeth__BBSScene__
#define __MyTeeth__BBSScene__

#include "Header.h"

using namespace cocos2d::ui;

class BBSScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void loadView();

    void menuCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(BBSScene);
};
#endif /* defined(__MyTeeth__BBSScene__) */
