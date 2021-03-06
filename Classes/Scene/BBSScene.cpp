//
//  BBSScene.cpp
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#include "BBSScene.h"
#include "SceneManager.h"
#include "MainScene.h"
#include "CustomViewTools.h"

USING_NS_CC;

Scene* BBSScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BBSScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BBSScene::init()
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

void BBSScene::loadView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    auto bgSprite = Sprite::create("bbs_bg.png");
//    bgSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(bgSprite, 0);
    
    auto colorLy = CustomViewTools::creatMyLayerColor(Color4B(255, 219, 8, 255), visibleSize.width, visibleSize.height, true);
    colorLy->setPosition(Vec2(origin.x, origin.y));
    this->addChild(colorLy, 0);
    
    //add scroll text
    float offset = 20.0;
    float topY = 100.0;
    float width = visibleSize.width - offset * 2;
    float height = visibleSize.height - topY - offset;
    float fontSize = 40.0;
    std::string fontName = "Arial";
    Color4B color = Color4B(255,255,255,255);

    ui::ScrollView* scrollView = ui::ScrollView::create();
    scrollView->setContentSize(Size(width, height));
    scrollView->setPosition(Vec2(offset,offset));
    this->addChild(scrollView);
    
    auto ageLabel = Label::createWithSystemFont("年sdoifusajdlj代理副驾驶上来的就发生地方洛杉矶的方式的发的啥链接发来撒龄:",
                                                fontName,
                                                fontSize,
                                                cocos2d::Size(width, 0),
                                                TextHAlignment::LEFT,
                                                TextVAlignment::CENTER
                                                );
    ageLabel->setTextColor(color);
    float lbHeight = ageLabel->getContentSize().height;
    float scrollViewConHeight = lbHeight > height ? lbHeight : height;
    ageLabel->setPosition(Vec2(ageLabel->getContentSize().width/2, scrollViewConHeight - ageLabel->getContentSize().height/2));
    scrollView->addChild(ageLabel,0);
    
    scrollView->setInnerContainerSize(Size(scrollView->getContentSize().width, lbHeight));
    
    //add backBtn
    auto backItem = CustomViewTools::creatMyMenuItemSprite("return.png", CC_CALLBACK_1(BBSScene::menuCallback, this));
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width ,
                               origin.y + visibleSize.height - backItem->getContentSize().height));
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void BBSScene::menuCallback(Ref* pSender)
{
    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(MainScene::createScene(), true);
}