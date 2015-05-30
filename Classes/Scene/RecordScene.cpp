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
#include "DateUtils.h"
#include "RecordDayScene.h"

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

    DateUtils::getCurrentTime();
    //recode
    m_dayLabels = cocos2d::Vector<Label*>();

    beginDate = 20150211;
    nowDate = atol(DateUtils::getCurrentDate().c_str());
    
    min_y = (int)(beginDate / 10000);
    min_m = (int)((beginDate % 10000) / 100);
    max_y = (int)(nowDate / 10000);
    max_m = (int)((nowDate % 10000) / 100);
    
    cur_year = max_y;
    cur_month = max_m;
    this->updateRecordViewWithDate(cur_year, cur_month);
    
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
    
    float labelHeight = infobgHeight / 4;
    float labelX1 = accountInfoBg->getContentSize().width * 0.5;
    float labelX2 = accountInfoBg->getContentSize().width * 0.67;
    float labelX3 = accountInfoBg->getContentSize().width * 0.8;
    float labelX4 = accountInfoBg->getContentSize().width * 0.97;
    std::string fontName = Default_Font_Name;
    float fontSize = Font_Size_Normal;
    Color4B color1 = ColorT1;
    Color4B color2 = ColorT2;

    auto nameTitleLabel = Label::createWithTTF("姓名:", fontName, fontSize);
    nameTitleLabel->setDimensions(200, labelHeight);
    nameTitleLabel->setHorizontalAlignment(TextHAlignment::LEFT);
    nameTitleLabel->setVerticalAlignment(TextVAlignment::CENTER);
    nameTitleLabel->setTextColor(color2);
    nameTitleLabel->setPosition(Vec2(labelX1, accountInfoBg->getContentSize().height/2 + labelHeight));
    accountInfoBg->addChild(nameTitleLabel,0);
    
    name_lb = Label::createWithTTF(name, fontName, fontSize);
    name_lb->setDimensions(200, labelHeight);
    name_lb->setHorizontalAlignment(TextHAlignment::LEFT);
    name_lb->setVerticalAlignment(TextVAlignment::CENTER);
    name_lb->setTextColor(color1);
    name_lb->setPosition(Vec2(labelX2, accountInfoBg->getContentSize().height/2 + labelHeight));
    accountInfoBg->addChild(name_lb,0);
    
    auto sexTitleLabel = Label::createWithTTF("姓别:", fontName, fontSize);
    sexTitleLabel->setDimensions(200, labelHeight);
    sexTitleLabel->setHorizontalAlignment(TextHAlignment::LEFT);
    sexTitleLabel->setVerticalAlignment(TextVAlignment::CENTER);
    sexTitleLabel->setTextColor(color2);
    sexTitleLabel->setPosition(Vec2(labelX1, accountInfoBg->getContentSize().height/2));
    accountInfoBg->addChild(sexTitleLabel,0);
    
    sex_lb = Label::createWithTTF(sex, fontName, fontSize);
    sex_lb->setDimensions(200, labelHeight);
    sex_lb->setHorizontalAlignment(TextHAlignment::LEFT);
    sex_lb->setVerticalAlignment(TextVAlignment::CENTER);
    sex_lb->setTextColor(color1);
    sex_lb->setPosition(Vec2(labelX2, accountInfoBg->getContentSize().height/2));
    accountInfoBg->addChild(sex_lb,0);
    
    auto ageTitleLabel = Label::createWithTTF("年龄:", fontName, fontSize);
    ageTitleLabel->setDimensions(200, labelHeight);
    ageTitleLabel->setHorizontalAlignment(TextHAlignment::LEFT);
    ageTitleLabel->setVerticalAlignment(TextVAlignment::CENTER);
    ageTitleLabel->setTextColor(color2);
    ageTitleLabel->setPosition(Vec2(labelX3, accountInfoBg->getContentSize().height/2));
    accountInfoBg->addChild(ageTitleLabel,0);

    age_lb = Label::createWithTTF(age, fontName, fontSize);
    age_lb->setDimensions(200, labelHeight);
    age_lb->setHorizontalAlignment(TextHAlignment::LEFT);
    age_lb->setVerticalAlignment(TextVAlignment::CENTER);
    age_lb->setTextColor(color1);
    age_lb->setPosition(Vec2(labelX4, accountInfoBg->getContentSize().height/2));
    accountInfoBg->addChild(age_lb,0);
    
    auto scoreTitleLabel = Label::createWithTTF("星星积分:", fontName, fontSize);
    scoreTitleLabel->setDimensions(200, labelHeight);
    scoreTitleLabel->setHorizontalAlignment(TextHAlignment::LEFT);
    scoreTitleLabel->setVerticalAlignment(TextVAlignment::CENTER);
    scoreTitleLabel->setTextColor(color2);
    scoreTitleLabel->setPosition(Vec2(labelX1, accountInfoBg->getContentSize().height/2 - labelHeight));
    accountInfoBg->addChild(scoreTitleLabel,0);
    
    score_lb = Label::createWithTTF("sdfsdf", fontName, fontSize);
    score_lb->setDimensions(200, labelHeight);
    score_lb->setHorizontalAlignment(TextHAlignment::LEFT);
    score_lb->setVerticalAlignment(TextVAlignment::CENTER);
    score_lb->setTextColor(color1);
    score_lb->setPosition(Vec2(labelX3, accountInfoBg->getContentSize().height/2 - labelHeight));
    accountInfoBg->addChild(score_lb,0);
    
    //record
    float recordLbHeight = recordbgHeight / 8;
    recordInfoBg = Scale9Sprite::create(cocos2d::Rect(70, 70, 20, 20), "calendar-bg.png");
    recordInfoBg->setContentSize(cocos2d::Size(infobgWidth, recordbgHeight));
    recordInfoBg->setPosition(Vec2(visibleSize.width/2 + origin.x, accountInfoBg->getPosition().y - (accountInfoBg->getContentSize().height / 2 + offsetY) - recordInfoBg->getContentSize().height / 2));
    this->addChild(recordInfoBg, 0);
    
    month_lb = Label::createWithTTF("", fontName, fontSize);
    month_lb->setDimensions(400, recordLbHeight);
    month_lb->setHorizontalAlignment(TextHAlignment::CENTER);
    month_lb->setVerticalAlignment(TextVAlignment::CENTER);
    month_lb->setTextColor(color2);
    month_lb->setPosition(Vec2(recordInfoBg->getContentSize().width / 2, recordInfoBg->getContentSize().height - recordLbHeight/2));
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
        auto week_lb = Label::createWithTTF(title.c_str(), fontName, fontSize);
        week_lb->setDimensions(weekTitleWidth, recordLbHeight);
        week_lb->setHorizontalAlignment(TextHAlignment::CENTER);
        week_lb->setVerticalAlignment(TextVAlignment::CENTER);
        week_lb->setTextColor(color2);
        week_lb->setPosition(Vec2(weekTitleWidth * (i + 1), weekTitleY));
        recordInfoBg->addChild(week_lb,0);
    }
    
    float xOffset = recordInfoBg->getContentSize().width / 3;
    float y = recordInfoBg->getPosition().y + recordInfoBg->getContentSize().height / 2 - 40.0;
    auto lItem = CustomViewTools::creatMyMenuItemSprite("left.png", CC_CALLBACK_1(RecordScene::leftMenuTouch, this));
    lItem->setPosition(Vec2(recordInfoBg->getPosition().x - xOffset, y));
    
    auto rItem = CustomViewTools::creatMyMenuItemSprite("right.png", CC_CALLBACK_1(RecordScene::rightMenuTouch, this));
    rItem->setPosition(Vec2(recordInfoBg->getPosition().x + xOffset, y));
    
    //add backBtn
    auto backItem = CustomViewTools::creatMyMenuItemSprite("return.png", CC_CALLBACK_1(RecordScene::menuCallback, this));
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width ,
                               origin.y + visibleSize.height - backItem->getContentSize().height));
    auto menu = Menu::create(backItem, lItem, rItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void RecordScene::updateAccountView()
{
    
}

void RecordScene::leftMenuTouch(cocos2d::Ref* pSender)
{
    if (cur_year <= min_y && cur_month <= min_m) {
        
    }
    else
    {
        cur_month--;
        if (cur_month == 0) {
            cur_month = 12;
            cur_year--;
        }
    }
    this->updateRecordViewWithDate(cur_year, cur_month);
}

void RecordScene::rightMenuTouch(cocos2d::Ref* pSender)
{
    if (cur_year >= max_y && cur_month >= max_m) {
        
    }
    else
    {
        cur_month++;
        if (cur_month == 13) {
            cur_month = 1;
            cur_year++;
        }
    }
    this->updateRecordViewWithDate(cur_year, cur_month);
}

void RecordScene::menuCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(MainScene::createScene(), true);
}

void RecordScene::updateRecordViewWithDate(int y, int m)
{
    int beginWeek = DateUtils::getCaculateWeek(y, m, 1);
    int days = DateUtils::getDaysWithYM(y, m);

    month_lb->setString(StringUtils::format("%d年%d月", cur_year, cur_month));
    
    //
    for (int i=0; i<m_dayLabels.size(); i++) {
        Label *day = m_dayLabels.at(i);
        day->removeFromParent();
    }
    m_dayLabels.clear();
    
    int vNum = 7;
    float w = recordInfoBg->getContentSize().width / (vNum + 1);
    float h = recordInfoBg->getContentSize().height / (vNum + 1.3);
    float beginX = (recordInfoBg->getPosition().x - recordInfoBg->getContentSize().width / 2) + recordInfoBg->getContentSize().width / (vNum + 1);
    float beginY = (recordInfoBg->getPosition().y - recordInfoBg->getContentSize().height / 2) + recordInfoBg->getContentSize().height * 0.72;
    
    int offset = (beginWeek + 1) % vNum;

    for (int i=offset; i<days + offset; i++) {
        //add backBtn
        auto day_lb = Label::createWithTTF(StringUtils::format("%d", (i - offset) + 1) , Default_Font_Name, Font_Size_LargeX);
        day_lb->setDimensions(w, h);
        day_lb->setHorizontalAlignment(TextHAlignment::CENTER);
        day_lb->setVerticalAlignment(TextVAlignment::CENTER);
        day_lb->setTextColor(ColorT2);
        day_lb->setPosition(Vec2(beginX + w * (i % vNum), beginY - h * (i / vNum)));
        this->addChild(day_lb,0);
        
        m_dayLabels.pushBack(day_lb);
    }
}

#pragma listener

void RecordScene::onEnter()
{
    Layer::onEnter();
    
    listener = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener->setSwallowTouches(true); //设置是否向下传递触摸
    
    //通过 lambda 表达式 直接实现触摸事件的回掉方法
    listener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    
    listener->onTouchMoved = [](Touch* touch, Event* event){
        log("sprite onTouchMoved.. ");
    };
    
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        log("sprite onTouchesEnded.. ");
        this->myTouchEnded(touch, event);
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void RecordScene::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
    
    Layer::onExit();
}

void RecordScene::myTouchEnded( Touch *pTouch, Event *pEvent )
{
    Point point = pTouch->getLocation() - this->getPosition();

    for (int i=0; i<m_dayLabels.size(); i++) {
        Label *day = m_dayLabels.at(i);
        if (CustomViewTools::checkBounding( day, point )) {
            //int curday = atoi(day->getString().c_str());
            log("label onTouchesEnded.. %s", day->getString().c_str());
            
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);
            
            SceneManager *sManager = SceneManager::sharedSceneManager();
            Scene *dayRecord = RecordDayScene::createScene();
            sManager->runScene(dayRecord, true);
            
            return;
        }
    }
}