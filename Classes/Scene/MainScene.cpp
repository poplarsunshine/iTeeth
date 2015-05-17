//
//  MainScene.cpp
//  MyTeeth
//
//  Created by wlp on 15/4/29.
//
//

#include "MainScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "CoachScene.h"
#include "RecordScene.h"
#include "SettingScene.h"
#include "BBSScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->loadView();
    
    return true;
}

void MainScene::loadView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //bg
//    auto sprite = Sprite::create("main_bg.png");
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(sprite, 0);
    
    //colorbg
    auto colorLy = LayerColor::create(Color4B(80, 177, 255, 255), visibleSize.width, visibleSize.height);
    colorLy->setPosition(Vec2(origin.x, origin.y));
    this->addChild(colorLy, 0);

    //cloud
    auto cloudSprite1 = Sprite::create("cloud.png");
    cloudSprite1->setPosition(Vec2(visibleSize.width * 0.2 + origin.x, visibleSize.height * 0.85 + origin.y));
    cloudSprite1->setOpacity(140);
    this->addChild(cloudSprite1, 0);
    
    auto cloudSprite2 = Sprite::create("cloud.png");
    cloudSprite2->setPosition(Vec2(visibleSize.width * 0.9 + origin.x, visibleSize.height * 0.88 + origin.y));
    cloudSprite2->setScale(0.4);
    cloudSprite2->setOpacity(40);
    this->addChild(cloudSprite2, 0);
    
    //sun
    auto sunSprite = Sprite::create("sun.png");
    sunSprite->setPosition(Vec2(visibleSize.width*0.78 + origin.x, visibleSize.height*0.8 + origin.y));
    this->addChild(sunSprite, 0);
    
    //tooth
    auto toothSprite = Sprite::create("tooth.png");
    toothSprite->setPosition(Vec2(visibleSize.width + origin.x - toothSprite->getContentSize().width * 2.4, origin.y + toothSprite->getContentSize().height * 0.7));
    this->addChild(toothSprite, 0);
    
    //toothbrush
    auto toothbrushSprite = Sprite::create("toothbrush.png");
    toothbrushSprite->setPosition(Vec2(visibleSize.width + origin.x - toothbrushSprite->getContentSize().width * 1.5, origin.y + toothbrushSprite->getContentSize().height * 0.6));
    this->addChild(toothbrushSprite, 0);
    
    //panda
    auto pandaSprite = Sprite::create("panda.png");
    pandaSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.5 + origin.y));
    this->addChild(pandaSprite, 0);
    
    //add btn
    auto recordItem = CustomViewTools::creatMyMenuItemSprite("record.png", CC_CALLBACK_1(MainScene::menuGoRecord, this));
    recordItem->setPosition(Vec2(origin.x + recordItem->getContentSize().width ,
                                origin.y + visibleSize.height - recordItem->getContentSize().height));
    auto settingItem = CustomViewTools::creatMyMenuItemSprite("setting.png", CC_CALLBACK_1(MainScene::menuGoSetting, this));
    settingItem->setPosition(Vec2(origin.x + visibleSize.width - settingItem->getContentSize().width ,
                                 origin.y + visibleSize.height - settingItem->getContentSize().height));
    auto playItem = CustomViewTools::creatMyMenuItemSprite("play.png", CC_CALLBACK_1(MainScene::menuGoPlay, this));
    playItem->setPosition(Vec2(origin.x + visibleSize.width * 0.84,
                                 origin.y + visibleSize.height * 0.3));
    
    //musice----_ ——
    auto openSprite = Sprite::create("music-open.png");
    auto closeSprite = Sprite::create("music-close.png");
    auto openToggleMenuItem = MenuItemSprite::create(openSprite, openSprite);
    auto closeToggleMenuItem = MenuItemSprite::create(closeSprite,closeSprite);
    soundItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MainScene::menuGoSound, this),
                                                        closeToggleMenuItem,
                                                        openToggleMenuItem,
                                                        NULL);
    
    bool bgMusicOn = UserDefault::getInstance()->getBoolForKey(MusicIsPlayKey);
    this->setCurMusicPlay(bgMusicOn);
    
//    auto soundItem = MenuItemImage::create("music-open.png",
//                                            "music-open.png",
//                                            CC_CALLBACK_1(MainScene::menuGoSound, this));
    soundItem->setPosition(Vec2(origin.x + visibleSize.width * 0.11,
                                 origin.y + visibleSize.height * 0.30));
    
    auto blueToothItem = MenuItemImage::create("bluetooth-close.png",
                                           "bluetooth-close.png",
                                           CC_CALLBACK_1(MainScene::menuGoBlueTooth, this));
    blueToothItem->setPosition(Vec2(origin.x + visibleSize.width * 0.62,
                                origin.y + visibleSize.height * 0.18));
    auto bbsItem = CustomViewTools::creatMyMenuItemSprite("BBS.png", CC_CALLBACK_1(MainScene::menuGoBBS, this));
    bbsItem->setPosition(Vec2(origin.x + bbsItem->getContentSize().width/2,
                                 origin.y + bbsItem->getContentSize().height * 0.9));
    
    auto menu = Menu::create(recordItem,
                             settingItem,
                             playItem,
                             soundItem,
                             blueToothItem,
                             bbsItem,
                             NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //
    //toggle菜单
//    auto goSprite = Sprite::createWithSpriteFrameName("go.png");
//    auto stopSprite = Sprite::createWithSpriteFrameName("stop.png");
//    auto goToggleMenuItem = MenuItemSprite::create(goSprite, goSprite);
//    auto stopToggleMenuItem = MenuItemSprite::create(stopSprite,stopSprite);
//    auto toggleMenuItem = MenuItemToggle::createWithCallback(
//                                                             CC_CALLBACK_1(MainScene::menuGoSound,this),
//                                                             goToggleMenuItem , stopToggleMenuItem, NULL);
//    toggleMenuItem->setPosition(Director::getInstance()->convertToGL(Point(930,540)));
//    auto mn = Menu::create(toggleMenuItem, NULL);
//    mn->setPosition(Point::ZERO);
//    this->addChild(mn);
}

void MainScene::setCurMusicPlay(bool play)
{
    isPlaying = play;
    if (play)
    {
        soundItem->setSelectedIndex(1);
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(FileName_AudioBg);
    }
    else
    {
        soundItem->setSelectedIndex(0);
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
    //default save
    UserDefault::getInstance()->setBoolForKey(MusicIsPlayKey, isPlaying);
}

void MainScene::menuGoRecord(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(RecordScene::createScene(), true);
}

void MainScene::menuGoSetting(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(SettingScene::createScene(), true);
}

void MainScene::menuGoSound(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);
    
    isPlaying = !isPlaying;
    
    this->setCurMusicPlay(isPlaying);
}

void MainScene::menuGoBlueTooth(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);
}

void MainScene::menuGoBBS(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(BBSScene::createScene(), true);
}

void MainScene::menuGoPlay(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

    CMessageBox* pBox = CMessageBox::createBy(0,
                                              this,
                                              "",
                                              "",
                                              "教程",
                                              "游戏",
                                              boxHandler_selector(MainScene::goToLearn),
                                              boxHandler_selector(MainScene::goToPlay),
                                              NULL);
    this->addChild(pBox, 2);
}

void MainScene::goToPlay()
{
    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(GameScene::createScene(), true);
}

void MainScene::goToLearn()
{
    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(CoachScene::createScene(), true);
}