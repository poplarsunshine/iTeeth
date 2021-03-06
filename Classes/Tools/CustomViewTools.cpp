//
//  CustomViewTools.cpp
//  MyTeeth
//
//  Created by wlp on 15/5/6.
//
//

#include "CustomViewTools.h"

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

cocos2d::LayerColor * CustomViewTools::creatMyLayerColor(const cocos2d::Color4B& color, GLfloat width, GLfloat height, bool showSprites)
{
    int spriteCount = 12;
    auto colorLy = LayerColor::create(color, width, height);
    if (showSprites == true) {
        for (int i = 0; i < spriteCount; i++) {
            int index = i % 3 + 1;
            float randomx = CCRANDOM_0_1();
            float randomy = CCRANDOM_0_1();
            std::string filename = StringUtils::format("background-icon0%d.png", index);
            auto sprite = Sprite::create(filename);
            sprite->setPosition(Vec2(width * randomx, height * randomy));
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