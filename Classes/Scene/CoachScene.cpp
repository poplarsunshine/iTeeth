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
    
    model = -1;
    
    i_limit_time = 60;
    i_cur_time = i_limit_time;
    this->updateTimeAndTooth(i_cur_time);

    return true;
}

void CoachScene::loadView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
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
    
    //score
    auto sBgSprite = Scale9Sprite::create(cocos2d::Rect(80, 30, 12, 10), "star-bg.png");
    sBgSprite->setContentSize(Size(visibleSize.width / 4, 70));

    sBgSprite->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, origin.y + visibleSize.height - 50));
    this->addChild(sBgSprite, 0);
    
    auto starSprite = Sprite::create("big-star.png");
    starSprite->setPosition(Vec2(sBgSprite->getContentSize().width * 0.2, sBgSprite->getContentSize().height/2));
    sBgSprite->addChild(starSprite, 0);
    
    p_scoreLb = Label::createWithTTF("0", Default_Font_Name, Font_Size_LargeX);
    p_scoreLb->setDimensions(sBgSprite->getContentSize().width * 0.6, sBgSprite->getContentSize().height);
    p_scoreLb->setHorizontalAlignment(TextHAlignment::CENTER);
    p_scoreLb->setVerticalAlignment(TextVAlignment::CENTER);
    p_scoreLb->setTextColor(Color4B::WHITE);
    p_scoreLb->setPosition(Vec2(sBgSprite->getContentSize().width * 0.6, sBgSprite->getContentSize().height/2));
    sBgSprite->addChild(p_scoreLb,0);
    
    //timer
    auto timerBgSprite = Scale9Sprite::create(cocos2d::Rect(80, 50, 12, 6), "countdown-bg.png");
    timerBgSprite->setContentSize(Size(visibleSize.width / 2, 100));
    float timerY = toothBgSprite->getPosition().y + toothBgSprite->getContentSize().height / 2 + timerBgSprite->getContentSize().height;
    timerBgSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, timerY));
    this->addChild(timerBgSprite, 2);
    
    auto timerMenu = Scale9Sprite::create(cocos2d::Rect(80, 50, 12, 6), "countdown-bg.png");
    timerMenu->setContentSize(Size(visibleSize.width / 2, 100));
    auto timerItem = MenuItemSprite::create(timerMenu, timerMenu, nullptr, CC_CALLBACK_1(CoachScene::setTimeMax, this));
    timerItem->setPosition(Vec2(visibleSize.width/2 + origin.x, timerY));
    
    auto clockSprite = Sprite::create("clock.png");
    clockSprite->setPosition(Vec2(timerBgSprite->getContentSize().width * 0.33 / 2, timerBgSprite->getContentSize().height/2));
    timerBgSprite->addChild(clockSprite, 0);
    
    p_timerLb = Label::createWithTTF("", Default_Font_Name, Font_Size_LargeXX);
    p_timerLb->setDimensions(timerBgSprite->getContentSize().width * 0.6, timerBgSprite->getContentSize().height);
    p_timerLb->setHorizontalAlignment(TextHAlignment::CENTER);
    p_timerLb->setVerticalAlignment(TextVAlignment::CENTER);
    p_timerLb->setTextColor(Color4B::WHITE);
    p_timerLb->setPosition(Vec2(timerBgSprite->getContentSize().width * 0.6, timerBgSprite->getContentSize().height/2));
    timerBgSprite->addChild(p_timerLb,0);
    
    this->startTimeLbAnimation();

    //add backBtn
    auto backItem = CustomViewTools::creatMyMenuItemSprite("return.png", CC_CALLBACK_1(CoachScene::menuCallback, this));
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width ,
                                 origin.y + visibleSize.height - backItem->getContentSize().height));
    auto menu = Menu::create(backItem, timerItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //
    m_starNormalList = cocos2d::Vector<Sprite*>();
    m_starSelectList = cocos2d::Vector<Sprite*>();
    float r = 250.0;
    float centerX = toothBgSprite->getPosition().x;
    float centerY = toothBgSprite->getPosition().y;
    int itemCount = 16;
    for (int i=0; i<itemCount; i++) {
        float angle = 2 * M_PI * i / itemCount;
        float x = centerX + r * sinf(angle);
        float y = centerY + r * cosf(angle);
        
        auto starSprite1 = Sprite::create("star.png");
        starSprite1->setPosition(x, y);
        starSprite1->setRotation(360.0 * i / itemCount);
        this->addChild(starSprite1, 0);
        m_starNormalList.pushBack(starSprite1);
        
        auto starSprite2 = Sprite::create("big-star.png");
        starSprite2->setPosition(x, y);
        starSprite2->setRotation(360.0 * i / itemCount);
        this->addChild(starSprite2, 0);
        m_starSelectList.pushBack(starSprite2);

        starSprite2->setVisible(false);
    }
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
    schedule(schedule_selector(CoachScene::startTimer), ready_time);
    
    NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(CoachScene::brushNotification), "bluetoothBrushNotification", NULL);

}

void CoachScene::onExit()
{
    NotificationCenter::getInstance()->removeObserver(this, "bluetoothBrushNotification");

    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

    unschedule(schedule_selector(CoachScene::updateCustom));
    unschedule(schedule_selector(CoachScene::startTimer));

    Layer::onExit();
}

void CoachScene::brushNotification(cocos2d::Ref* obj)
{
    cocos2d::String *value = (cocos2d::String *)obj;
    int tag = atoi(value->getCString());
    if (tag>=0 && tag < Tooth_Space_Type_Max) {
        if (tag == model) {
            Sprite *star = m_starSelectList.at(model);
            if (!star->isVisible()) {
                star->setVisible(true);
                i_score++;
                p_scoreLb->setString(StringUtils::format("%d", i_score));
            }
        }
    }
    else{
        log("brushNotification tag error");
    }
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

void CoachScene::startTimeLbAnimation()
{
    float dTime = 1.0;
    p_timerLb->stopAllActions();
    cocos2d::ScaleTo *action1 = cocos2d::ScaleTo::create(dTime * 0.5, 1.2);
    cocos2d::ScaleTo *action2 = cocos2d::ScaleTo::create(dTime * 0.5, 1.0);
    cocos2d::Sequence *salceAction = cocos2d::Sequence::create(action1, action2, NULL);
    p_timerLb->runAction(Repeat::create(salceAction, int(ready_time / dTime)));
}

void CoachScene::setTimeMax(Ref* pSender)
{
    if (b_gameIsStart || b_gameIsFinished) {
        return;
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

    unschedule(schedule_selector(CoachScene::startTimer));

    i_limit_time += 60;
    if (i_limit_time > 180) {
        i_limit_time = 60;
    }
    i_cur_time = i_limit_time;
    this->updateTimeAndTooth(i_cur_time);
    
    schedule(schedule_selector(CoachScene::startTimer), ready_time);
    
    this->startTimeLbAnimation();
}

void CoachScene::startTimer(float dt)
{
    unschedule(schedule_selector(CoachScene::startTimer));
    schedule(schedule_selector(CoachScene::updateCustom), 1.0f, kRepeatForever, 0);
    setGameStart(true);
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
    int curModel = Tooth_Space_Type_Max * (i_limit_time - time) / (i_limit_time + 1);
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
