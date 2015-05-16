//
//  SettingScene.cpp
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#include "SettingScene.h"
#include "SceneManager.h"
#include "MainScene.h"
#include "CustomViewTools.h"
//#include "../../cocos2d/cocos/ui/UIScale9Sprite.h"


USING_NS_CC;

Scene* SettingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SettingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SettingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->loadView();
    
    this->setSexDisplay(sex);

    return true;
}

void SettingScene::loadView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    auto bgSprite = Sprite::create("set_bg.png");
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
    float infobgHeight = 310;
    float infobgY = 100;
    float inputBgHeight = 140.0;
    float yOffset = 20.0;

    auto accountInfoBg = Scale9Sprite::create(cocos2d::Rect(70, 70, 20, 20), "white-background.png");
    accountInfoBg->setContentSize(cocos2d::Size(infobgWidth, infobgHeight));
    accountInfoBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - accountInfoBg->getContentSize().height / 2 - infobgY));
    this->addChild(accountInfoBg, 0);
    
    //name
    float fontSize = 40.0;
    std::string fontName = "Arial";
    Color4B color = Color4B(233,223,32,255);

    auto nameInputBg = Scale9Sprite::create(cocos2d::Rect(70, 70, 20, 20), "white-background.png");
    nameInputBg->setContentSize(cocos2d::Size(infobgWidth, inputBgHeight));
    nameInputBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - nameInputBg->getContentSize().height / 2 - (infobgY + infobgHeight + yOffset)));
    this->addChild(nameInputBg, 0);
    
    auto nameLabel = Label::createWithSystemFont("姓名:",
                                                   fontName,
                                                   fontSize,
                                                   cocos2d::Size(160, inputBgHeight),
                                                   TextHAlignment::RIGHT,
                                                   TextVAlignment::CENTER
                                                   );
    nameLabel->setTextColor(color);
    nameLabel->setPosition(Vec2(nameLabel->getContentSize().width/2, nameLabel->getContentSize().height/2));
    nameInputBg->addChild(nameLabel,0);
    
    auto editBoxSize = Size(infobgWidth - (160 + 40), inputBgHeight / 2);
    std::string pNormalSprite = "white-background.png";
    _editName = cocos2d::ui::EditBox::create(editBoxSize, pNormalSprite);
    _editName->setPosition(Vec2(infobgWidth - editBoxSize.width/2 - 20, nameInputBg->getContentSize().height / 2));
    _editName->setFontColor(color);
    _editName->setPlaceHolder("请输入姓名");
    //_editName->setInputMode(ui::EditBox::InputMode::EMAIL_ADDRESS);
    _editName->setMaxLength(16);
    _editName->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    _editName->setDelegate(this);
    nameInputBg->addChild(_editName);
    
    //age
    auto ageInputBg = Scale9Sprite::create(cocos2d::Rect(70, 70, 20, 20), "white-background.png");
    ageInputBg->setContentSize(cocos2d::Size(infobgWidth, inputBgHeight));
    ageInputBg->setPosition(Vec2(visibleSize.width/2 + origin.x, nameInputBg->getPosition().y - ageInputBg->getContentSize().height - yOffset));
    this->addChild(ageInputBg, 0);
    
    auto ageLabel = Label::createWithSystemFont("年龄:",
                                                 fontName,
                                                 fontSize,
                                                 cocos2d::Size(160, inputBgHeight),
                                                 TextHAlignment::RIGHT,
                                                 TextVAlignment::CENTER
                                                 );
    ageLabel->setTextColor(color);
    ageLabel->setPosition(Vec2(ageLabel->getContentSize().width/2, ageLabel->getContentSize().height/2));
    ageInputBg->addChild(ageLabel,0);
    
    _editAge = cocos2d::ui::EditBox::create(editBoxSize, pNormalSprite);
    _editAge->setPosition(Vec2(infobgWidth - editBoxSize.width/2 - 20, ageInputBg->getContentSize().height / 2));
    _editAge->setFontColor(color);
    _editAge->setPlaceHolder("请输入年龄");
    _editAge->setInputMode(ui::EditBox::InputMode::NUMERIC);
    _editAge->setMaxLength(3);
    _editAge->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    _editAge->setDelegate(this);
    ageInputBg->addChild(_editAge);
    
    //confirm
    auto btnBg = Scale9Sprite::create(cocos2d::Rect(70, 70, 4, 4), "button-default.png");
    btnBg->setContentSize(cocos2d::Size(infobgWidth, inputBgHeight));
    auto btnSelBg = Scale9Sprite::create(cocos2d::Rect(70, 70, 4, 4), "button-press.png");
    btnSelBg->setContentSize(cocos2d::Size(infobgWidth, inputBgHeight));
    auto confirmBtn = MenuItemSprite::create(btnBg, btnSelBg, CC_CALLBACK_1(SettingScene::confirmMenuCallback, this));
    confirmBtn->setPosition(Vec2(visibleSize.width/2 + origin.x, ageInputBg->getPosition().y - btnSelBg->getContentSize().height - yOffset));

    float iconOffsetX = (visibleSize.width/2 - offsetX) / 2;
    //man sex btn
    auto manItem = CustomViewTools::creatMyMenuItemSprite("boy.png", CC_CALLBACK_1(SettingScene::manMenuCallback, this));
    manItem->setPosition(Vec2(accountInfoBg->getPosition().x - iconOffsetX,
                               accountInfoBg->getPosition().y));
    manSelectSpreite = Sprite::create("right-boy.png");
    manSelectSpreite->setPosition(Vec2(manItem->getContentSize().width/2, 0));
    manSelectSpreite->setVisible(false);
    manItem->addChild(manSelectSpreite, 0);
    
    //wom sex btn
    auto womItem = CustomViewTools::creatMyMenuItemSprite("girl.png", CC_CALLBACK_1(SettingScene::womMenuCallback, this));
    womItem->setPosition(Vec2(accountInfoBg->getPosition().x + iconOffsetX,
                              accountInfoBg->getPosition().y));
    womSelectSpreite = Sprite::create("right-girl.png");
    womSelectSpreite->setPosition(Vec2(womItem->getContentSize().width/2, 0));
    womSelectSpreite->setVisible(false);
    womItem->addChild(womSelectSpreite, 0);
    
    //add backBtn
    auto backItem = CustomViewTools::creatMyMenuItemSprite("return.png", CC_CALLBACK_1(SettingScene::menuCallback, this));
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width ,
                                 origin.y + visibleSize.height - backItem->getContentSize().height));
    auto menu = Menu::create(backItem, confirmBtn, manItem, womItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void SettingScene::menuCallback(Ref* pSender)
{
    SceneManager *sManager = SceneManager::sharedSceneManager();
    sManager->runScene(MainScene::createScene(), true);
}

void SettingScene::manMenuCallback(Ref* pSender)
{
    if (sex == 0) {
        sex = 1;
        this->setSexDisplay(sex);
    }
}

void SettingScene::womMenuCallback(Ref* pSender)
{
    if (sex == 1) {
        sex = 0;
        this->setSexDisplay(sex);
    }
}

void SettingScene::setSexDisplay(int sexNum)
{
    switch (sexNum) {
        case 0:
            manSelectSpreite->setVisible(false);
            womSelectSpreite->setVisible(true);
            break;
        case 1:
            manSelectSpreite->setVisible(true);
            womSelectSpreite->setVisible(false);
            break;
        default:
            manSelectSpreite->setVisible(false);
            womSelectSpreite->setVisible(false);
            break;
    }
}

void SettingScene::confirmMenuCallback(Ref* pSender)
{
    log("confirmMenuCallback");
}

#pragma Editbox

void SettingScene::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
    log("editBox %p DidBegin !", editBox);
}

void SettingScene::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
    log("editBox %p DidEnd !", editBox);
}

void SettingScene::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
    log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void SettingScene::editBoxReturn(ui::EditBox* editBox)
{
    log("editBox %p was returned !",editBox);
    
    if (_editName == editBox)
    {
        log("_editName was returned !");
    }
}

