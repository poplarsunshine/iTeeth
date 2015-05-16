//
//  ToothLayer.cpp
//  MyTeeth
//
//  Created by Penny on 15/5/17.
//
//

#include "TeethLayer.h"

bool TeethLayer::init()
{
    m_teethList = cocos2d::Vector<cocos2d::Sprite*>();
    for (int i=0; i<16; i++) {
        std::string filename = cocos2d::StringUtils::format("tooth-%d.png", i);
        cocos2d::Sprite *tooth = cocos2d::Sprite::create(filename);
        this->addChild(tooth);
        m_teethList.pushBack(tooth);
    }
    
    this->setCurTooth(Tooth_down_left_inside);
    
    return true;
}

void TeethLayer::setAllToothHide()
{
    for (int i=0; i<m_teethList.size(); i++) {
        cocos2d::Sprite *tooth = m_teethList.at(i);
        tooth->setVisible(false);
    }
}

void TeethLayer::setCurTooth(E_Tooth_SPACE toothSpaceType)
{
    this->setAllToothHide();
    
    cocos2d::Sprite *tooth = m_teethList.at((int)toothSpaceType);
    tooth->setVisible(true);
}