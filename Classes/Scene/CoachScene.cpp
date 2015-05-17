//
//  CoachScene.cpp
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#include "CoachScene.h"
#include "SceneManager.h"
#include "MainScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* CoachScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CoachScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CoachScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->loadView();

    return true;
}

void CoachScene::loadView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    auto bgSprite = Sprite::create("tooth_bg.png");
//    bgSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(bgSprite, 0);
    
    auto colorLy = CustomViewTools::creatMyLayerColor(Color4B(23, 207, 77, 255),
                                                      visibleSize.width,
                                                      visibleSize.height,
                                                      true);
    colorLy->setPosition(Vec2(origin.x, origin.y));
    this->addChild(colorLy, 0);
    
    //teeth
    auto toothBgSprite = Sprite::create("center-bg.png");
    toothBgSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height * 0.4 + origin.y));
    this->addChild(toothBgSprite, 0);
    
    //teeth
    m_teethLy = TeethLayer::create();
    m_teethLy->setPosition(Vec2(toothBgSprite->getPosition().x, toothBgSprite->getPosition().y));
    //m_teethLy->setDelegate(this);
    this->addChild(m_teethLy, 0);
    
    //timer
    auto timerBgSprite = Scale9Sprite::create(cocos2d::Rect(80, 50, 12, 6), "countdown-bg.png");
    timerBgSprite->setContentSize(Size(visibleSize.width / 2, 100));
    float timerY = toothBgSprite->getPosition().y + toothBgSprite->getContentSize().height / 2 + timerBgSprite->getContentSize().height;
    timerBgSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, timerY));
    this->addChild(timerBgSprite, 0);
    
    p_timerLb = Label::createWithSystemFont("01:34",
                                            "Arial",
                                              40,
                                              timerBgSprite->getContentSize(),
                                              TextHAlignment::CENTER,
                                              TextVAlignment::CENTER
                                              );
    p_timerLb->setTextColor(Color4B(233,0,32,255));
    p_timerLb->setPosition(Vec2(timerBgSprite->getContentSize().width / 2, timerBgSprite->getContentSize().height/2));
    timerBgSprite->addChild(p_timerLb,0);
    
    //add backBtn
    auto backItem = CustomViewTools::creatMyMenuItemSprite("return.png", CC_CALLBACK_1(CoachScene::menuCallback, this));
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width ,
                                 origin.y + visibleSize.height - backItem->getContentSize().height));
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void CoachScene::onEnter()
{
    Layer::onEnter();
    
    listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    
    listener->onTouchMoved = [](Touch* touch, Event* event){
        log("sprite onTouchMoved.. ");
    };
    
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        log("sprite onTouchesEnded.. ");
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

        model++;
        
        m_teethLy->setCurTooth((E_Tooth_SPACE)(model % Tooth_Space_Type_Max));
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void CoachScene::onExit()
{
    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

    Layer::onExit();
}

void CoachScene::menuCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(MainScene::createScene(), true);
}