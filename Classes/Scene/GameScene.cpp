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
    
    return true;
}

void GameScene::loadView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    auto bgSprite = Sprite::create("play_bg.png");
//    bgSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(bgSprite, 0);
    
    //bg
    bg_a = Sprite::create("bg-a.png");
    bg_a->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg_a, 0);
    
    bg_b = Sprite::create("bg-b.png");
    bg_b->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg_b, 0);
    
    bg_c = Sprite::create("bg-c.png");
    bg_c->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg_c, 0);
    
    //add star
    m_starList = cocos2d::Vector<Sprite*>();
    for (int i=0; i<10; i++) {
        
    }
    
    //panda
    p_panda = Sprite::create("panda-02.png");
    p_panda->setPosition(Vec2(visibleSize.width * 0.26 + origin.x, visibleSize.height * 0.65 + origin.y));
    this->addChild(p_panda, 0);
    
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

    //add backBtn
    auto backItem = MenuItemImage::create("return.png",
                                          "return.png",
                                          CC_CALLBACK_1(GameScene::menuCallback, this));
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width ,
                               origin.y + visibleSize.height - backItem->getContentSize().height));
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

        cocos2d::Blink *action = cocos2d::Blink::create(0.4, 2);
        p_panda->runAction(action);
        
        model++;
        
        this->setGameModel(E_GAME_MODEL((model/4) % GAME_STATE_MAX));
        
        m_teethLy->setCurTooth(E_Tooth_SPACE(model % Tooth_Space_Type_Max));
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onExit()
{
    Layer::onExit();
    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}

void GameScene::menuCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(MainScene::createScene(), true);
}

void GameScene::setGameModel(E_GAME_MODEL model)
{
    bg_a->setVisible(false);
    bg_b->setVisible(false);
    bg_c->setVisible(false);
    colorLy_a->setVisible(false);
    colorLy_b->setVisible(false);
    colorLy_c->setVisible(false);
    tooth_bg_a->setVisible(false);
    tooth_bg_b->setVisible(false);
    tooth_bg_c->setVisible(false);

    switch (model) {
        case GAME_STATE_DAY:
        {
            bg_a->setVisible(true);
            colorLy_a->setVisible(true);
            tooth_bg_a->setVisible(true);
            break;
        }
        case GAME_STATE_NIGHT:
        {
            bg_b->setVisible(true);
            colorLy_b->setVisible(true);
            tooth_bg_c->setVisible(true);
            break;
        }
        case GAME_STATE_SUPER:
        {
            bg_c->setVisible(true);
            colorLy_c->setVisible(true);
            tooth_bg_c->setVisible(true);
            break;
        }
        default:
            break;
    }
}