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

USING_NS_CC;
USING_NS_CC_EXT;

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
    
    auto colorLy = CustomViewTools::creatMyLayerColor(Color4B(255, 219, 8, 255),
                                                      visibleSize.width,
                                                      visibleSize.height,
                                                      true);
    colorLy->setPosition(Vec2(origin.x, origin.y));
    this->addChild(colorLy, 0);
    
    //add scroll text
    float offset = 20.0;
    float topY = 100.0;
    float width = visibleSize.width - offset * 2;
    float height = visibleSize.height - topY - offset;
    
    auto titleLabel = CustomViewTools::creatTitleWith(topY, "社区论坛");
    this->addChild(titleLabel, 0);
    
    auto scrollView = ui::ScrollView::create();
    scrollView->setContentSize(Size(width, height));
    scrollView->setPosition(Vec2(offset,offset));
    this->addChild(scrollView);
    
    std::string content = "    itooth是一家“健康舒适、优质生活”的多元化公司，致力于通过及时地推出有意义的创新来改善人们的生活质量。作为全球医疗保健、优质生活和照明领域的领导者，基于对客户需求的了解以及“精于心 简于形”的品牌承诺，将技术和设计融入到了以人为本的解决方案中。\n\n    作为全球医疗保健、优质生活和照明领域的领导者，基于对客户需求的了解以及“精于心 简于形”的品牌承诺，将技术和设计融入到了以人为本的解决方案中。";
    float lineHeight = 46.0;
    float fontSize = Font_Size_Small;

    auto tempLabel = Label::createWithSystemFont(content,
                                                Default_Font_Name,
                                                fontSize,
                                                cocos2d::Size(width, 0),
                                                TextHAlignment::LEFT,
                                                TextVAlignment::CENTER
                                                );
    int numOfline = tempLabel->getContentSize().height / fontSize;
    
    auto contentLabel = Label::createWithTTF(content, Default_Font_Name, fontSize);
    contentLabel->setDimensions(width, numOfline * lineHeight);
    contentLabel->setHorizontalAlignment(TextHAlignment::LEFT);
    contentLabel->setVerticalAlignment(TextVAlignment::CENTER);
    contentLabel->setTextColor(ColorT1);
    contentLabel->setLineHeight(lineHeight);
    float lbHeight = contentLabel->getContentSize().height;
    float scrollViewConHeight = lbHeight > height ? lbHeight : height;
    contentLabel->setPosition(Vec2(contentLabel->getContentSize().width/2, scrollViewConHeight - contentLabel->getContentSize().height/2));
    scrollView->addChild(contentLabel,0);
    
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
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);

    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(MainScene::createScene(), true);
}