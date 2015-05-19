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
    
    i_limit_time = 60;
    i_cur_time = i_limit_time;
    
    this->loadView();
    
    this->updateTimeAndTooth(i_cur_time);

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
    
    p_timerLb = Label::createWithTTF("", Default_Font_Name, Font_Size_Large);
    p_timerLb->setDimensions(timerBgSprite->getContentSize().width, timerBgSprite->getContentSize().height);
    p_timerLb->setHorizontalAlignment(TextHAlignment::CENTER);
    p_timerLb->setVerticalAlignment(TextVAlignment::CENTER);
    p_timerLb->setTextColor(Color4B::WHITE);
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
//        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);
//
//        model++;
//        
//        m_teethLy->setCurTooth((E_Tooth_SPACE)(model % Tooth_Space_Type_Max));
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //
    schedule(schedule_selector(CoachScene::updateCustom), 1.0f, kRepeatForever, 0);
    setGameStart(true);
}

void CoachScene::onExit()
{
    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

    unschedule(schedule_selector(CoachScene::updateCustom));

    Layer::onExit();
}

void CoachScene::setGameStart(bool isStart)
{
    if (b_gameIsFinished)
    {
        resume();
        return;
    }
    b_gameIsStart = isStart;
    if (isStart) {
        resume();
    }
    else{
        pause();
    }
}


void CoachScene::updateCustom(float dt)
{
    if (i_cur_time <= 0) {
        this->setGameStart(false);
        b_gameIsFinished = true;
    }
    else
    {
        i_cur_time--;
    }
    this->updateTimeAndTooth(i_cur_time);
}

void CoachScene::updateTimeAndTooth(int time)
{
    int curModel = Tooth_Space_Type_Max * time / (i_limit_time + 1);
    if (curModel != model) {
        model = curModel;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);
        m_teethLy->setCurTooth((E_Tooth_SPACE)(model));
    }
    
    int m = time/60;
    int s = time%60;
    std::string mStr = "";
    if (m < 10)
        mStr = StringUtils::format("0%d",m);
    else
        mStr = StringUtils::format("%d",m);

    std::string sStr = "";
    if (s < 10)
        sStr = StringUtils::format("0%d",s);
    else
        sStr = StringUtils::format("%d",s);
    std::string timeStr = StringUtils::format("%s:%s", mStr.c_str(), sStr.c_str());
    p_timerLb->setString(timeStr);
}

void CoachScene::menuCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

    this->setGameStart(false);
    CMessageBox* pBox = CMessageBox::createBy(0,
                                              this,
                                              "",
                                              "",
                                              "退出",
                                              "继续",
                                              boxHandler_selector(CoachScene::backToMain),
                                              boxHandler_selector(CoachScene::goonGame),
                                              NULL);
    this->addChild(pBox, 2);
}


void CoachScene::backToMain()
{
    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(MainScene::createScene(), true);
}

void CoachScene::goonGame()
{
    this->setGameStart(true);
}