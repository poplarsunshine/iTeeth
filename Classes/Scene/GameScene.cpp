//
//  GameScene.cpp
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#include "GameScene.h"
#include "SceneManager.h"
#include "MainScene.h"


USING_NS_CC;
USING_NS_CC_EXT;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("flyPanda.plist");
    
    this->loadView();
    
    this->setGameModel(GAME_STATE_DAY);
    
    //this->setGameStart(true);
    
    return true;
}

void GameScene::loadView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    f_mid_y = visibleSize.height * 0.65 + origin.y;
    f_starOffsetX = 80.0;
    f_starSpeed = 8.0;

//    auto bgSprite = Sprite::create("play_bg.png");
//    bgSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(bgSprite, 0);
    
    layer_a = Layer::create();
    this->addChild(layer_a, 0);
    
    layer_b = Layer::create();
    this->addChild(layer_b, 0);
    
    layer_c = Layer::create();
    this->addChild(layer_c, 0);

    //bg a
    Sprite *bg_a = Sprite::create("bg-a.png");
    bg_a->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    layer_a->addChild(bg_a, 0);
    
    m_cloudList = cocos2d::Vector<Sprite*>();
    for (int i=0; i<3; i++) {
        float randomx = CCRANDOM_0_1();
        Sprite *cloud = Sprite::create("cloud.png");
        cloud->setPosition(Vec2(visibleSize.width * randomx + origin.x, visibleSize.height * (1 + randomx) / 2 + origin.y));
        cloud->setOpacity(200 + 55 * randomx);
        cloud->setScale(0.5 + 0.5 * randomx);
        layer_a->addChild(cloud, 0);
        m_cloudList.pushBack(cloud);
    }
    
    //bg b
    Sprite *bg_b = Sprite::create("bg-b.png");
    bg_b->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    layer_b->addChild(bg_b, 0);
    
    cityBg1 = Sprite::create("bg-b-lou.png");
    cityBg1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    layer_b->addChild(cityBg1, 0);
    cityBg2 = Sprite::create("bg-b-lou.png");
    cityBg2->setPosition(Vec2(cityBg1->getPosition().x + cityBg1->getContentSize().width, cityBg1->getPosition().y));
    layer_b->addChild(cityBg2, 0);
    
    //bg c
    Sprite *bg_c = Sprite::create("bg-c.png");
    bg_c->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    layer_c->addChild(bg_c, 0);
    
    Sprite *light1 = Sprite::create("yanhua-3.png");
    light1->setPosition(Vec2(visibleSize.width * 0.9 + origin.x, visibleSize.height * 0.9 + origin.y));
    layer_c->addChild(light1, 0);
    CustomViewTools::addAnimationAction(light1, 1);
    
    Sprite *subBg1 = Sprite::create("bg-c-yuan3.png");
    subBg1->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.7 + origin.y));
    layer_c->addChild(subBg1, 0);
    
    Sprite *light2 = Sprite::create("yanhua-2.png");
    light2->setPosition(Vec2(visibleSize.width * 0.25 + origin.x, visibleSize.height * 0.8 + origin.y));
    layer_c->addChild(light2, 0);
    CustomViewTools::addAnimationAction(light2, 1);

    Sprite *light3 = Sprite::create("yanhua-1.png");
    light3->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, visibleSize.height * 0.8 + origin.y));
    layer_c->addChild(light3, 0);
    CustomViewTools::addAnimationAction(light3, 1);

    Sprite *subBg2 = Sprite::create("bg-c-yuan12.png");
    subBg2->setPosition(Vec2(subBg1->getPosition().x, subBg1->getPosition().y));
    layer_c->addChild(subBg2, 0);
    
    Sprite *item1 = Sprite::create("bg-c-cao.png");
    item1->setPosition(Vec2(visibleSize.width * 0.25 + origin.x, visibleSize.height * 0.45 + origin.y));
    item1->setScale(1.1);
    layer_c->addChild(item1, 0);
    
    Sprite *item2 = Sprite::create("bg-c-cao.png");
    item2->setPosition(Vec2(visibleSize.width * 0.75 + origin.x, visibleSize.height * 0.45 + origin.y));
    item2->setFlippedX(true);
    layer_c->addChild(item2, 0);
    
    Sprite *wall = Sprite::create("bg-c-woniu.png");
    wall->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height * 0.45 + origin.y));
    layer_c->addChild(wall, 0);
    
    //score
    auto sBgSprite = Scale9Sprite::create(cocos2d::Rect(80, 30, 12, 10), "star-bg.png");
    sBgSprite->setContentSize(Size(visibleSize.width / 4, 70));
    
    sBgSprite->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, origin.y + visibleSize.height - 50));
    this->addChild(sBgSprite, 0);
    
    auto starSprite = Sprite::create("big-star.png");
    starSprite->setPosition(Vec2(sBgSprite->getContentSize().width * 0.2, sBgSprite->getContentSize().height/2));
    sBgSprite->addChild(starSprite, 0);
    
    p_scoreLb = Label::createWithTTF("234", Default_Font_Name, Font_Size_LargeX);
    p_scoreLb->setDimensions(sBgSprite->getContentSize().width * 0.6, sBgSprite->getContentSize().height);
    p_scoreLb->setHorizontalAlignment(TextHAlignment::CENTER);
    p_scoreLb->setVerticalAlignment(TextVAlignment::CENTER);
    p_scoreLb->setTextColor(Color4B::WHITE);
    p_scoreLb->setPosition(Vec2(sBgSprite->getContentSize().width * 0.6, sBgSprite->getContentSize().height/2));
    sBgSprite->addChild(p_scoreLb,0);
    
    //add star
    m_starList = cocos2d::Vector<Sprite*>();
//    float beginX = visibleSize.width;
//    float beginY = this->getStarY(level);
//    for (int i=0; i<10; i++) {
//        auto star = Sprite::create("star.png");
//        star->setPosition(Vec2(beginX + f_starOffsetX * i, beginY));
//        this->addChild(star, 0);
//        m_starList.pushBack(star);
//    }
    
    //panda
    p_panda = Sprite::create("panda-02.png");

    f_offset_y = p_panda->getContentSize().height;
    
    p_panda->setPosition(Vec2(visibleSize.width * 0.26 + origin.x, f_mid_y));
    this->addChild(p_panda, 1);
    
    Animation*animation = Animation::create();
    for(int i=1; i<= 2; i++)
    {
        std::string frameName = StringUtils::format("panda-0%d.png", i);
        SpriteFrame*spriteFrame = SpriteFrameCache::getInstance()->
        getSpriteFrameByName(frameName);
        animation->addSpriteFrame(spriteFrame);
    }
    animation->setDelayPerUnit(0.3f);
    animation->setRestoreOriginalFrame(true);
    
    Animate*action = Animate::create(animation);
    p_panda->runAction(RepeatForever::create(action));

    //tooth bg
    float toothBgWidth = visibleSize.width;
    float toothBgHeight = 440;
    Color4B colorA = Color4B(118,209,255,255);
    Color4B colorB = Color4B(32,86,155,255);
    Color4B colorC = Color4B(23,164,237,255);
    
    colorLy_a = CustomViewTools::creatMyLayerColor(colorA,
                                                   toothBgWidth,
                                                   toothBgHeight,
                                                   true,
                                                   5);
    colorLy_b = CustomViewTools::creatMyLayerColor(colorB,
                                                   toothBgWidth,
                                                   toothBgHeight,
                                                   true,
                                                   5);
    colorLy_c = CustomViewTools::creatMyLayerColor(colorC,
                                                   toothBgWidth,
                                                   toothBgHeight,
                                                   true,
                                                   5);
    this->addChild(colorLy_a);
    this->addChild(colorLy_b);
    this->addChild(colorLy_c);
    
    //tooth time
    float toothTimeBgX = toothBgWidth/2;
    float toothTimeBgY = toothBgHeight / 2 + toothBgHeight / 11.0;

    tooth_bg_a = Sprite::create("tooth-bg-a.png");
    tooth_bg_a->setPosition(Vec2(toothTimeBgX, toothTimeBgY));
    this->addChild(tooth_bg_a, 0);
    tooth_bg_b = Sprite::create("tooth-bg-b.png");
    tooth_bg_b->setPosition(Vec2(toothTimeBgX, toothTimeBgY));
    this->addChild(tooth_bg_b, 0);
    tooth_bg_c = Sprite::create("tooth-bg-c.png");
    tooth_bg_c->setPosition(Vec2(toothTimeBgX, toothTimeBgY));
    this->addChild(tooth_bg_c, 0);
    
    //teeth
    m_teethLy = TeethLayer::create();
    m_teethLy->setPosition(Vec2(toothTimeBgX, toothTimeBgY));
    m_teethLy->setDelegate(this);
    m_teethLy->setScale(0.77);
    this->addChild(m_teethLy, 0);

    //temp contrl
    auto upItem = CustomViewTools::creatMyMenuItemSprite("background-icon01.png", CC_CALLBACK_1(GameScene::menuUpCallback, this));
    upItem->setPosition(Vec2(origin.x + upItem->getContentSize().width / 2,
                               origin.y + visibleSize.height * 0.3));
    
    auto downItem = CustomViewTools::creatMyMenuItemSprite("background-icon01.png", CC_CALLBACK_1(GameScene::menuDownCallback, this));
    downItem->setPosition(Vec2(origin.x + downItem->getContentSize().width / 2,
                             origin.y + visibleSize.height * 0.15));
    
    //add backBtn
    auto backItem = CustomViewTools::creatMyMenuItemSprite("return.png", CC_CALLBACK_1(GameScene::menuCallback, this));
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width ,
                               origin.y + visibleSize.height - backItem->getContentSize().height));
    //auto menu = Menu::create(backItem, upItem, downItem, NULL);
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //add listener
    
}

void GameScene::onEnter()
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

        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);
        
        model++;
        
        this->setGameModel(E_GAME_MODEL((model/4) % GAME_STATE_MAX));
        
        //m_teethLy->setCurTooth(E_Tooth_SPACE(model % Tooth_Space_Type_Max));
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //
    schedule(schedule_selector(GameScene::updateCustom), 1.0f / 30.0, kRepeatForever, 0);
    setGameStart(true);
    
    //
    NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(GameScene::brushNotification), "bluetoothBrushNotification", NULL);
}

void GameScene::onExit()
{
    NotificationCenter::getInstance()->removeObserver(this, "bluetoothBrushNotification");
    
    unschedule(schedule_selector(GameScene::updateCustom));

    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

    Layer::onExit();
}

void GameScene::brushNotification(cocos2d::Ref* obj)
{
    cocos2d::String *value = (cocos2d::String *)obj;
    int tag = atoi(value->getCString());
    if (tag < 8) {
        this->menuUpCallback(NULL);
    }
    else
    {
        this->menuDownCallback(NULL);
    }
    m_teethLy->setCurTooth(E_Tooth_SPACE(tag));
}

void GameScene::setGameStart(bool isStart)
{
    b_gameIsStart = isStart;
    if (isStart) {
        resume();
    }
    else{
        pause();
    }
}

//void GameScene::update(float dt)
//{
//    log("update dt=%f", dt);
//}

void GameScene::updateCustom(float dt)
{
    //star
    cocos2d::Vector<Sprite*> tempSprites = cocos2d::Vector<Sprite*>();

    //log("updateCustom dt=%f", dt);
    for (int i=0; i<m_starList.size(); i++) {
        cocos2d::Sprite *star = m_starList.at(i);
        //如果出左边界 置于末尾
        float curx = star->getPosition().x;
        float cury = star->getPosition().y;

        if (curx < -80) {
            tempSprites.pushBack(star);
        }
        else
        {
            star->setPosition(curx - f_starSpeed, star->getPosition().y);

            bool isHit = false;
            float leftX = p_panda->getPosition().x + p_panda->getContentSize().width / 2 - star->getContentSize().width / 2;
            float rightX = p_panda->getPosition().x + p_panda->getContentSize().width / 2 + star->getContentSize().width / 2;
            float panda_y = p_panda->getPosition().y;
            if (cury==panda_y && leftX < curx && curx < rightX) {
                isHit = true;
            }
            if (isHit) {
                score ++;
                tempSprites.pushBack(star);
            }
        }
    }
    
    for (int i=0; i<tempSprites.size(); i++) {
        cocos2d::Sprite *star = tempSprites.at(i);
        star->removeFromParent();
        m_starList.eraseObject(star, false);
    }
    tempSprites.clear();

    p_scoreLb->setString(StringUtils::format("%d", score));
    
    if (times >= 10) {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        auto star = Sprite::create("star.png");
        star->setPosition(Vec2(visibleSize.width, this->getStarY(level)));
        this->addChild(star, 0);
        m_starList.pushBack(star);
        times = 0;
    }
    else{
        times++;
    }
    
    //brush
    if (f_brushTimes >= 30) {
        b_isBrushing = false;
    }
    else
    {
        f_brushTimes++;
        b_isBrushing = true;
    }
    if (!b_isBrushing) {
        p_panda->setPosition(p_panda->getPosition().x, f_mid_y);
    }
    
    
    //bg a
    for (int i=0; i<m_cloudList.size(); i++) {
        Sprite *cloud = m_cloudList.at(i);
        float curx = cloud->getPosition().x;
        if (curx < -cloud->getContentSize().width) {
            cloud->setPosition(this->getContentSize().width + cloud->getContentSize().width, this->getContentSize().height * (1 + CCRANDOM_0_1()) / 2);
        }
        else{
            cloud->setPosition(curx - f_starSpeed / (10 - i), cloud->getPosition().y);
        }
    }
    
    //bg b
    float citySpeed = f_starSpeed / 6;
    float city1x = cityBg1->getPosition().x;
    if (city1x <= -cityBg1->getContentSize().width / 2) {
        cityBg1->setPosition(cityBg2->getPosition().x + cityBg2->getContentSize().width - citySpeed, cityBg2->getPosition().y);
    }
    else{
        cityBg1->setPosition(city1x - citySpeed, cityBg1->getPosition().y);
    }
    float city2x = cityBg2->getPosition().x;
    if (city2x <= -cityBg2->getContentSize().width / 2) {
        cityBg2->setPosition(cityBg1->getPosition().x + cityBg1->getContentSize().width - citySpeed, cityBg1->getPosition().y);
    }
    else{
        cityBg2->setPosition(city2x - citySpeed, cityBg2->getPosition().y);
    }
}

float GameScene::getStarY(int level)
{
    float random = CCRANDOM_MINUS1_1();
    if (random > 0) {
        return f_mid_y + f_offset_y;
    }
    else
    {
        return f_mid_y - f_offset_y;
    }
}

void GameScene::menuCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

    this->setGameStart(false);
    CMessageBox* pBox = CMessageBox::createBy(0,
                                              this,
                                              "",
                                              "",
                                              "退出",
                                              "继续",
                                              boxHandler_selector(GameScene::backToMain),
                                              boxHandler_selector(GameScene::goonGame),
                                              NULL);
    this->addChild(pBox, 2);
}

void GameScene::backToMain()
{
    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(MainScene::createScene(), true);
}

void GameScene::goonGame()
{
    this->setGameStart(true);
}

void GameScene::menuUpCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);
    
//    float curY = this->p_panda->getPosition().y;
//    if (curY != f_mid_y + f_offset_y) {
//        p_panda->setPosition(Vec2(p_panda->getPosition().x, curY + f_offset_y));
//    }
    
    p_panda->setPosition(Vec2(p_panda->getPosition().x, f_mid_y + f_offset_y));
    f_brushTimes = 0;
}

void GameScene::menuDownCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);
    
//    float curY = p_panda->getPosition().y;
//    if (curY != f_mid_y - f_offset_y) {
//        p_panda->setPosition(Vec2(p_panda->getPosition().x, curY - f_offset_y));
//    }
    
    p_panda->setPosition(Vec2(p_panda->getPosition().x, f_mid_y - f_offset_y));
    f_brushTimes = 0;
}

void GameScene::setGameModel(E_GAME_MODEL model)
{
    if (model >= GAME_STATE_MAX) {
        return;
    }
    
    layer_a->setVisible(false);
    layer_b->setVisible(false);
    layer_c->setVisible(false);

    colorLy_a->setVisible(false);
    colorLy_b->setVisible(false);
    colorLy_c->setVisible(false);
    tooth_bg_a->setVisible(false);
    tooth_bg_b->setVisible(false);
    tooth_bg_c->setVisible(false);

    switch (model) {
        case GAME_STATE_DAY:
        {
            layer_a->setVisible(true);
            colorLy_a->setVisible(true);
            tooth_bg_a->setVisible(true);
            break;
        }
        case GAME_STATE_NIGHT:
        {
            layer_b->setVisible(true);
            colorLy_b->setVisible(true);
            tooth_bg_c->setVisible(true);
            break;
        }
        case GAME_STATE_SUPER:
        {
            layer_c->setVisible(true);
            colorLy_c->setVisible(true);
            tooth_bg_c->setVisible(true);
            break;
        }
        default:
            break;
    }
}