//
//  GameScene.h
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#ifndef __MyTeeth__GameScene__
#define __MyTeeth__GameScene__

#include "Header.h"
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
    
    void brushNotification(cocos2d::Ref* obj);

    virtual void onEnter();
    virtual void onExit();
    
    //
    cocos2d::Layer *layer_a;
    cocos2d::Layer *layer_b;
    cocos2d::Layer *layer_c;

    cocos2d::Vector<cocos2d::Sprite*> m_cloudList;

    cocos2d::Sprite *cityBg1;
    cocos2d::Sprite *cityBg2;

//    cocos2d::Sprite *bg_b;
//    cocos2d::Sprite *bg_c;

    cocos2d::LayerColor *colorLy_a;
    cocos2d::LayerColor *colorLy_b;
    cocos2d::LayerColor *colorLy_c;

    cocos2d::Sprite *tooth_bg_a;
    cocos2d::Sprite *tooth_bg_b;
    cocos2d::Sprite *tooth_bg_c;
    
    cocos2d::Sprite *p_panda;
    
    TeethLayer *m_teethLy;
    
    bool b_gameIsStart;
    
    bool b_isBrushing;
    float f_brushTimes;

    void setGameModel(E_GAME_MODEL);
    
    void setGameStart(bool isStart);
    
    //void update(float dt);

    void updateCustom(float dt);

    void backToMain();
    void goonGame();

    void menuUpCallback(cocos2d::Ref* pSender);
    void menuDownCallback(cocos2d::Ref* pSender);
    
    float getStarY(int level);

private:
    
    cocos2d::EventListenerTouchOneByOne* listener;

    cocos2d::Vector<cocos2d::Sprite*> m_starList;
    
    cocos2d::Label *p_scoreLb;
    
    float f_mid_y;
    float f_offset_y;
    float f_starSpeed;
    float f_starOffsetX;
    
    int model;
    int level;
    int times;
    int score;
    
};
#endif /* defined(__MyTeeth__GameScene__) */
