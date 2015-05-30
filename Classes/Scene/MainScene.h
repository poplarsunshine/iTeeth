//
//  MainScene.h
//  MyTeeth
//
//  Created by wlp on 15/4/29.
//
//

#ifndef __MyTeeth__MainScene__
#define __MyTeeth__MainScene__

#include "Header.h"

extern int BluetoothConnect;

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    void loadView();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCallback(cocos2d::Ref* pSender);
    
    void menuGoRecord(cocos2d::Ref* pSender);
    void menuGoSetting(cocos2d::Ref* pSender);
    void menuGoPlay(cocos2d::Ref* pSender);
    void menuGoSound(cocos2d::Ref* pSender);
    void menuGoBlueTooth(cocos2d::Ref* pSender);
    void menuGoBBS(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
    void blueConnectNotification(cocos2d::Ref* obj);
    
    virtual void onEnter();
    virtual void onExit();
    
    //
    cocos2d::MenuItemToggle *soundItem;
    cocos2d::MenuItemToggle *blueToothItem;

    void goToPlay();
    void goToLearn();
    
    void setCurMusicPlay(bool play);

private:
    
    bool isPlaying = false;
};

#endif /* defined(__MyTeeth__MainScene__) */
