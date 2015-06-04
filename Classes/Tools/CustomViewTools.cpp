//
//  CustomViewTools.cpp
//  MyTeeth
//
//  Created by wlp on 15/5/6.
//
//

#include "CustomViewTools.h"
#include "header.h"

USING_NS_CC;

const float btnOpacityFloat = 200.0;

cocos2d::MenuItemSprite * CustomViewTools::creatMyMenuItemSprite(const std::string& filename, const cocos2d::ccMenuCallback& callback)
{
    auto spriteNormal = Sprite::create(filename);
    auto spriteSelected = Sprite::create(filename);
    spriteSelected->setOpacity(btnOpacityFloat);
    //auto disabledSprite = Sprite::create(filename);
    auto settingBtnOkItem = MenuItemSprite::create(spriteNormal, spriteSelected, nullptr, callback);
    return settingBtnOkItem;
}

cocos2d::LayerColor * CustomViewTools::creatMyLayerColor(const cocos2d::Color4B& color,
                                                         float width,
                                                         float height,
                                                         bool showSprites,
                                                         int spriteCount)
{
    auto colorLy = LayerColor::create(color, width, height);
    if (showSprites == true) {
        for (int i = 0; i < spriteCount; i++) {
            int index = i % 3 + 1;
            float randomx = CCRANDOM_0_1();
            float randomy = CCRANDOM_0_1();
            std::string filename = StringUtils::format("background_icon0%d.png", index);
            auto sprite = Sprite::create(filename);
            float y = (height / spriteCount) * (i + randomy);
            sprite->setPosition(Vec2(width * randomx, y));
            sprite->setScale(0.3 + (randomx + randomy) / 2);
            sprite->setOpacity(25 + 100 * (randomx + randomy) / 2);
            if (index != 1) {
                sprite->setRotation(360 * randomx);
            }
            colorLy->addChild(sprite, 0);
        }
    }
    return colorLy;
}

cocos2d::Label * CustomViewTools::creatTitleWith(GLfloat height, const std::string &title)
{
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto titleLabel = cocos2d::Label::createWithTTF(title, Default_Font_Name, Font_Size_LargeXX);
    titleLabel->setDimensions(visibleSize.width, height);
    titleLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    titleLabel->setVerticalAlignment(TextVAlignment::CENTER);
    titleLabel->setTextColor(Color4B::WHITE);
    titleLabel->enableOutline(ColorT2, 6.0);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - height / 2));
    return titleLabel;
}

bool CustomViewTools::checkBounding( Node* pNode, Point& point )
{
    if (pNode == NULL) {
        return false;
    }
    int x = pNode->getPositionX();
    int y = pNode->getPositionY();
    int w = pNode->getContentSize().width;
    int h = pNode->getContentSize().height;
    if ( point.x < x - w/2 || point.x > x + w/2 || point.y < y -h/2 || point.y > y + h/2 )
    {
        return false;
    }
    return true;
}

void CustomViewTools::addAnimationAction(Node* pNode, int type)
{
    switch (type) {
        case 0:
        {
            //scale
            //repeatForever
            cocos2d::ScaleTo *action1 = cocos2d::ScaleTo::create(0.8, 1.0);
            cocos2d::ScaleTo *action2 = cocos2d::ScaleTo::create(0.8, 0.9);
            cocos2d::Sequence *salceAction = cocos2d::Sequence::create(action1, action2, NULL);
            pNode->runAction(RepeatForever::create(salceAction));
        }
            break;
        case 1:
        {
            //scale & rotate
            //repeatForever
            cocos2d::ScaleTo *action1 = cocos2d::ScaleTo::create(0.4, 1.2);
            cocos2d::ScaleTo *action2 = cocos2d::ScaleTo::create(0.4, 0.8);
            cocos2d::Sequence *salceAction = cocos2d::Sequence::create(action1, action2, NULL);
            cocos2d::RotateBy *rotate = cocos2d::RotateBy::create(0.8, 30);
            cocos2d::Spawn *spawnAction = cocos2d::Spawn::create(rotate, salceAction, NULL);
            pNode->runAction(RepeatForever::create(spawnAction));
        }
            break;
        default:
            break;
    }
}
