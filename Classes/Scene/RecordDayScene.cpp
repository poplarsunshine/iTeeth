//
//  RecordDayScene.cpp
//  MyTeeth
//
//  Created by Penny on 15/5/27.
//
//

#include "RecordDayScene.h"
#include "SceneManager.h"
#include "RecordScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* RecordDayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = RecordDayScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RecordDayScene::init()
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

void RecordDayScene::loadView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto colorLy = CustomViewTools::creatMyLayerColor(Color4B(255, 219, 8, 255),
                                                      visibleSize.width,
                                                      visibleSize.height,
                                                      true);
    colorLy->setPosition(Vec2(origin.x, origin.y));
    this->addChild(colorLy, 0);
    
    float offsetX = 40.0;
    float infobgWidth = visibleSize.width - offsetX;
    float infobgHeight = 360;
    float infobgY = 100;
    float offsetY = 20.0;
    
    //title
    auto titleLabel = CustomViewTools::creatTitleWith(infobgY, "日记");
    this->addChild(titleLabel, 0);
    
    //info
    auto accountInfoBg = Sprite::create("round.png");
    accountInfoBg->setContentSize(cocos2d::Size(visibleSize.width * 0.6, visibleSize.width * 0.6));
    accountInfoBg->setPosition(Vec2(visibleSize.width/2, visibleSize.height + origin.y - accountInfoBg->getContentSize().height / 2 - infobgY - offsetY));
    this->addChild(accountInfoBg, 0);
    
    date_lb = Label::createWithTTF("", Default_Font_Name, Font_Size_Large);
    date_lb->setDimensions(200, accountInfoBg->getContentSize().height / 4);
    date_lb->setHorizontalAlignment(TextHAlignment::CENTER);
    date_lb->setVerticalAlignment(TextVAlignment::CENTER);
    date_lb->setTextColor(Color4B::WHITE);
    date_lb->setPosition(Vec2(accountInfoBg->getContentSize().width/2, accountInfoBg->getContentSize().height * 5 / 8));
    accountInfoBg->addChild(date_lb,0);

    time_lb = Label::createWithTTF("", Default_Font_Name, Font_Size_LargeXX);
    time_lb->setDimensions(200, accountInfoBg->getContentSize().height / 4);
    time_lb->setHorizontalAlignment(TextHAlignment::CENTER);
    time_lb->setVerticalAlignment(TextVAlignment::CENTER);
    time_lb->setTextColor(Color4B::WHITE);
    time_lb->setPosition(Vec2(accountInfoBg->getContentSize().width/2, accountInfoBg->getContentSize().height * 3 / 8));
    accountInfoBg->addChild(time_lb,0);
    
    //record
    auto recordInfoBg = Scale9Sprite::create(cocos2d::Rect(70, 70, 20, 20), "white-background.png");
    recordInfoBg->setContentSize(cocos2d::Size(infobgWidth, infobgHeight));
    recordInfoBg->setPosition(Vec2(visibleSize.width/2 + origin.x, accountInfoBg->getPosition().y - accountInfoBg->getContentSize().height / 2 - offsetY - recordInfoBg->getContentSize().height / 2));
    this->addChild(recordInfoBg, 0);
    
    //add backBtn
    auto backItem = CustomViewTools::creatMyMenuItemSprite("return.png", CC_CALLBACK_1(RecordDayScene::menuCallback, this));
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width ,
                               origin.y + visibleSize.height - backItem->getContentSize().height));
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void RecordDayScene::onEnter()
{
    Layer::onEnter();

    date_lb->setString(StringUtils::format("%d-%d\n刷牙时间", month, day));

    time_lb->setString(StringUtils::format("1分32秒"));
}

void RecordDayScene::onExit()
{
    Layer::onExit();
}

void RecordDayScene::menuCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);
    
    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(RecordScene::createScene(), true);
}