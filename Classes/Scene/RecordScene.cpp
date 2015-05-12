//
//  RecordScene.cpp
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#include "RecordScene.h"
#include "SceneManager.h"
#include "MainScene.h"
#include "CustomViewTools.h"

USING_NS_CC;

Scene* RecordScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = RecordScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RecordScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->loadView();
    
    this->updateAccountView();

    return true;
}

void RecordScene::loadView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    auto bgSprite = Sprite::create("score_bg.png");
//    bgSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(bgSprite, 0);
    
    auto colorLy = CustomViewTools::creatMyLayerColor(Color4B(255, 219, 8, 255), visibleSize.width, visibleSize.height, true);
    colorLy->setPosition(Vec2(origin.x, origin.y));
    this->addChild(colorLy, 0);
    
    float offsetX = 40.0;
    float infobgWidth = visibleSize.width - offsetX;
    float infobgHeight = 260;
    float infobgY = 100;
    float yOffset = 20.0;
    
    //account info
    Scale9Sprite *accountInfoBg = Scale9Sprite::create(cocos2d::Rect(70, 70, 20, 20), "white-background.png");
    accountInfoBg->setContentSize(cocos2d::Size(infobgWidth, infobgHeight));
    accountInfoBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - accountInfoBg->getContentSize().height / 2 - infobgY));
    this->addChild(accountInfoBg, 0);
    
    manSprite = Sprite::create("boy.png");
    manSprite->setPosition(Vec2(105, accountInfoBg->getContentSize().height/2));
    accountInfoBg->addChild(manSprite, 0);
    
    womSprite = Sprite::create("girl.png");
    womSprite->setPosition(Vec2(105, accountInfoBg->getContentSize().height/2));
    accountInfoBg->addChild(womSprite, 0);
    
    float fontSize = 36.0;
    float labelHeight = infobgHeight / 4;
    float labelX1 = accountInfoBg->getContentSize().width * 0.5;
    float labelX2 = accountInfoBg->getContentSize().width * 0.67;
    float labelX3 = accountInfoBg->getContentSize().width * 0.8;
    float labelX4 = accountInfoBg->getContentSize().width * 0.97;
    std::string fontName = "Arial";
    Color4B color = Color4B(233,223,32,255);
    Color4B color2 = Color4B(233,0,32,255);

    auto nameTitleLabel = Label::createWithSystemFont("姓名:",
                                                fontName,
                                                fontSize,
                                                cocos2d::Size(200, labelHeight),
                                                TextHAlignment::LEFT,
                                                TextVAlignment::CENTER
                                                );
    nameTitleLabel->setTextColor(color);
    nameTitleLabel->setPosition(Vec2(labelX1, accountInfoBg->getContentSize().height/2 + labelHeight));
    accountInfoBg->addChild(nameTitleLabel,0);
    
    name_lb = Label::createWithSystemFont("哎呀",
                                          fontName,
                                          fontSize,
                                          cocos2d::Size(200, labelHeight),
                                          TextHAlignment::LEFT,
                                          TextVAlignment::CENTER
                                          );
    name_lb->setTextColor(color2);
    name_lb->setPosition(Vec2(labelX2, accountInfoBg->getContentSize().height/2 + labelHeight));
    accountInfoBg->addChild(name_lb,0);
    
    auto sexTitleLabel = Label::createWithSystemFont("姓别:",
                                                      fontName,
                                                      fontSize,
                                                      cocos2d::Size(200, labelHeight),
                                                      TextHAlignment::LEFT,
                                                      TextVAlignment::CENTER
                                                      );
    sexTitleLabel->setTextColor(color);
    sexTitleLabel->setPosition(Vec2(labelX1, accountInfoBg->getContentSize().height/2));
    accountInfoBg->addChild(sexTitleLabel,0);
    
    sex_lb = Label::createWithSystemFont("男",
                                          fontName,
                                          fontSize,
                                          cocos2d::Size(200, labelHeight),
                                          TextHAlignment::LEFT,
                                          TextVAlignment::CENTER
                                          );
    sex_lb->setTextColor(color2);
    sex_lb->setPosition(Vec2(labelX2, accountInfoBg->getContentSize().height/2));
    accountInfoBg->addChild(sex_lb,0);
    
    auto ageTitleLabel = Label::createWithSystemFont("年龄:",
                                                fontName,
                                                fontSize,
                                                cocos2d::Size(200, labelHeight),
                                                TextHAlignment::LEFT,
                                                TextVAlignment::CENTER
                                                );
    ageTitleLabel->setTextColor(color);
    ageTitleLabel->setPosition(Vec2(labelX3, accountInfoBg->getContentSize().height/2));
    accountInfoBg->addChild(ageTitleLabel,0);
    
    age_lb = Label::createWithSystemFont("108",
                                         fontName,
                                         fontSize,
                                         cocos2d::Size(200, labelHeight),
                                         TextHAlignment::LEFT,
                                         TextVAlignment::CENTER
                                         );
    age_lb->setTextColor(color2);
    age_lb->setPosition(Vec2(labelX4, accountInfoBg->getContentSize().height/2));
    accountInfoBg->addChild(age_lb,0);
    
    auto scoreTitleLabel = Label::createWithSystemFont("星星积分:",
                                                     fontName,
                                                     fontSize,
                                                     cocos2d::Size(200, labelHeight),
                                                     TextHAlignment::LEFT,
                                                     TextVAlignment::CENTER
                                                     );
    scoreTitleLabel->setTextColor(color);
    scoreTitleLabel->setPosition(Vec2(labelX1, accountInfoBg->getContentSize().height/2 - labelHeight));
    accountInfoBg->addChild(scoreTitleLabel,0);
    
    score_lb = Label::createWithSystemFont("1088653",
                                         fontName,
                                         fontSize,
                                         cocos2d::Size(200, labelHeight),
                                         TextHAlignment::LEFT,
                                         TextVAlignment::CENTER
                                         );
    score_lb->setTextColor(color2);
    score_lb->setPosition(Vec2(labelX3, accountInfoBg->getContentSize().height/2 - labelHeight));
    accountInfoBg->addChild(score_lb,0);
    
    //add backBtn
    auto backItem = MenuItemImage::create("return.png",
                                            "return.png",
                                            CC_CALLBACK_1(RecordScene::menuCallback, this));
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width ,
                                 origin.y + visibleSize.height - backItem->getContentSize().height));
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void RecordScene::updateAccountView()
{
    
}

void RecordScene::menuCallback(Ref* pSender)
{
    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(MainScene::createScene(), true);
}