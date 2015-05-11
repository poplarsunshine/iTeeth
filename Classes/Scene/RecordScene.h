//
//  RecordScene.h
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#ifndef __MyTeeth__RecordScene__
#define __MyTeeth__RecordScene__

#include "cocos2d.h"

class RecordScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void loadView();

    void menuCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(RecordScene);
};
#endif /* defined(__MyTeeth__RecordScene__) */
