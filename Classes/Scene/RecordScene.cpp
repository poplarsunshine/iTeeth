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
#include "AccountData.h"

USING_NS_CC;
USING_NS_CC_EXT;

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
    
    std::string name = UserDefault::getInstance()->getStringForKey(User_Name_Key);
    std::string age  = UserDefault::getInstance()->getStringForKey(User_Age_Key);
    std::string score = UserDefault::getInstance()->getStringForKey(User_Score_Key);
    int sexIndex = UserDefault::getInstance()->getIntegerForKey(User_Sex_Key);
    std::string sex = AccountData::getSexWithInt(sexIndex);
    
//    auto bgSprite = Sprite::create("score_bg.png");
//    bgSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(bgSprite, 0);
    
    auto colorLy = CustomViewTools::creatMyLayerColor(Color4B(255, 219, 8, 255),
                                                      visibleSize.width,
                                                      visibleSize.height,
                                                      true);
    colorLy->setPosition(Vec2(origin.x, origin.y));
    this->addChild(colorLy, 0);
    
    float offsetX = 40.0;
    float infobgWidth = visibleSize.width - offsetX;
    float infobgHeight = 260;
    float infobgY = 100;
    float offsetY = 20.0;
    
    float recordbgHeight = 580;

    //title
    auto titleLabel = CustomViewTools::creatTitleWith(infobgY, "积分记录");
    this->addChild(titleLabel, 0);
    
    //account info
    auto accountInfoBg = Scale9Sprite::create(cocos2d::Rect(70, 70, 20, 20), "white-background.png");
    accountInfoBg->setContentSize(cocos2d::Size(infobgWidth, infobgHeight));
    accountInfoBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - accountInfoBg->getContentSize().height / 2 - infobgY));
    this->addChild(accountInfoBg, 0);
    
    //sex
    if (sexIndex == 1) {
        manSprite = Sprite::create("boy.png");
        manSprite->setPosition(Vec2(105, accountInfoBg->getContentSize().height/2));
        accountInfoBg->addChild(manSprite, 0);
    }
    else
    {
        womSprite = Sprite::create("girl.png");
        womSprite->setPosition(Vec2(105, accountInfoBg->getContentSize().height/2));
        accountInfoBg->addChild(womSprite, 0);
    }
    
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
    
    name_lb = Label::createWithSystemFont(name,
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
    
    sex_lb = Label::createWithSystemFont(sex,
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
    
    age_lb = Label::createWithSystemFont(age,
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
    
    score_lb = Label::createWithSystemFont(score,
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
    auto backItem = CustomViewTools::creatMyMenuItemSprite("return.png", CC_CALLBACK_1(RecordScene::menuCallback, this));
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width ,
                                 origin.y + visibleSize.height - backItem->getContentSize().height));
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //record
    float recordLbHeight = recordbgHeight / 7;
    auto recordInfoBg = Scale9Sprite::create(cocos2d::Rect(70, 70, 20, 20), "calendar-bg.png");
    recordInfoBg->setContentSize(cocos2d::Size(infobgWidth, recordbgHeight));
    recordInfoBg->setPosition(Vec2(visibleSize.width/2 + origin.x, accountInfoBg->getPosition().y - (accountInfoBg->getContentSize().height / 2 + offsetY) - recordInfoBg->getContentSize().height / 2));
    this->addChild(recordInfoBg, 0);
    
    month_lb = Label::createWithSystemFont("五月记录",
                                         fontName,
                                         fontSize,
                                         cocos2d::Size(200, recordLbHeight),
                                         TextHAlignment::CENTER,
                                         TextVAlignment::CENTER
                                         );
    month_lb->setTextColor(color2);
    month_lb->setPosition(Vec2(recordInfoBg->getContentSize().width / 2, recordInfoBg->getContentSize().height - month_lb->getContentSize().height/2));
    recordInfoBg->addChild(month_lb,0);
    
    //add week lb
    std::vector<std::string> titles;
    titles.push_back("日");
    titles.push_back("一");
    titles.push_back("二");
    titles.push_back("三");
    titles.push_back("四");
    titles.push_back("五");
    titles.push_back("六");
    float weekTitleWidth = recordInfoBg->getContentSize().width / 8;
    float weekTitleY = recordInfoBg->getContentSize().height - recordLbHeight*1.4;
    for (int i=0; i<titles.size(); i++)
    {
        std::string title = titles.at(i);
        auto week_lb = Label::createWithSystemFont(title.c_str(),
                                               fontName,
                                               fontSize,
                                               cocos2d::Size(weekTitleWidth, recordLbHeight),
                                               TextHAlignment::CENTER,
                                               TextVAlignment::CENTER
                                               );
        week_lb->setTextColor(color2);
        week_lb->setPosition(Vec2(weekTitleWidth * (i + 1), weekTitleY));
        recordInfoBg->addChild(week_lb,0);
    }
}

void RecordScene::updateAccountView()
{
    
}

void RecordScene::menuCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(MainScene::createScene(), true);
}