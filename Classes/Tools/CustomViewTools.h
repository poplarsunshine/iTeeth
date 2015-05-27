//
//  CustomViewTools.h
//  MyTeeth
//
//  Created by wlp on 15/5/6.
//
//

#ifndef __MyTeeth__CustomViewTools__
#define __MyTeeth__CustomViewTools__

#include <stdio.h>
#include "cocos2d.h"

class CustomViewTools
{
public:
    //利用一张图片创建 MenuItemSprite, 点击改变透明度
    static cocos2d::MenuItemSprite * creatMyMenuItemSprite(const std::string& filename, const cocos2d::ccMenuCallback& callback);
    
    //利用一张图片创建 MenuItemSprite, 点击改变透明度
    static cocos2d::LayerColor * creatMyLayerColor(const cocos2d::Color4B& color,
                                                   GLfloat width,
                                                   GLfloat height,
                                                   bool showSprites,
                                                   int spriteCount = 10);
    
    static cocos2d::Label * creatTitleWith(GLfloat height, const std::string& title);
    
    static bool checkBounding( cocos2d::Node* pNode, cocos2d::Point& point );
    
    static void addAnimationAction(cocos2d::Node* pNode, int type);
};

#endif /* defined(__MyTeeth__CustomViewTools__) */
