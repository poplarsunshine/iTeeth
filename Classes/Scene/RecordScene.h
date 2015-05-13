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
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class RecordScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void loadView();

    void menuCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(RecordScene);
    
private:
    cocos2d::Sprite* manSprite;
    cocos2d::Sprite* womSprite;
    
    cocos2d::Label* name_lb;
    cocos2d::Label* sex_lb;
    cocos2d::Label* age_lb;
    cocos2d::Label* score_lb;
    
    cocos2d::Label* month_lb;

    void updateAccountView();
};
#endif /* defined(__MyTeeth__RecordScene__) */
