//
//  GameScene.h
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#ifndef __MyTeeth__GameScene__
#define __MyTeeth__GameScene__

#include "cocos2d.h"
#include "TeethLayer.h"

typedef enum
{
    GAME_STATE_DAY      = 0,    //白天模式
    GAME_STATE_NIGHT    = 1,    //夜晚模式
    GAME_STATE_SUPER    = 2,    //超级模式
    GAME_STATE_MAX      = 3
}E_GAME_MODEL;

class GameScene : public cocos2d::Layer, public TeethLayerDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void loadView();

    // a selector callback
    void menuCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    virtual void onEnter();
    virtual void onExit();
    
    //
    cocos2d::Sprite *bg_a;
    cocos2d::Sprite *bg_b;
    cocos2d::Sprite *bg_c;

    cocos2d::LayerColor *colorLy_a;
    cocos2d::LayerColor *colorLy_b;
    cocos2d::LayerColor *colorLy_c;

    cocos2d::Sprite *tooth_bg_a;
    cocos2d::Sprite *tooth_bg_b;
    cocos2d::Sprite *tooth_bg_c;
    
    cocos2d::Sprite *p_panda;
    
    TeethLayer *m_teethLy;

    void setGameModel(E_GAME_MODEL);
    
private:
    
    cocos2d::EventListenerTouchOneByOne* listener;

    cocos2d::Vector<cocos2d::Sprite*> m_starList;

    int model;
};
#endif /* defined(__MyTeeth__GameScene__) */
