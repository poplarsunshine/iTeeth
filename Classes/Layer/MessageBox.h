//
//  MessageBox.h
//  MyTeeth
//
//  Created by Penny on 15/5/14.
//
//

#ifndef __MyTeeth__MessageBox__
#define __MyTeeth__MessageBox__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

typedef void (cocos2d::Node::*SEL_MessageBoxHandler)();

#define boxHandler_selector(_SELECTOR) (SEL_MessageBoxHandler)(&_SELECTOR)

class CMessageBox : public cocos2d::Layer
{
public:
    CMessageBox(void);
    ~CMessageBox(void);
    
    static CMessageBox* createBy(int type,
                                 cocos2d::Node* pLayerTarget,
                                 std::string title,
                                 std::string con,
                                 std::string leftLabel,
                                 std::string rightLabel,
                                 SEL_MessageBoxHandler leftBtnSel,
                                 SEL_MessageBoxHandler rightBtnSel,
                                 SEL_MessageBoxHandler backBtnSel);
    
private:
    bool init(int type,
              cocos2d::Node* pLayerTarget,
              std::string title,
              std::string con,
              std::string leftLabel,
              std::string rightLabel,
              SEL_MessageBoxHandler leftBtnSel,
              SEL_MessageBoxHandler rightBtnSel,
              SEL_MessageBoxHandler backBtnSel);
    
private:
    SEL_MessageBoxHandler     m_leftCallback;
    SEL_MessageBoxHandler     m_rightCallback;
    SEL_MessageBoxHandler     m_backCallback;
    
    cocos2d::Node           *m_pTarget;
    
    Scale9Sprite            *m_pBackgroundSpr;
    Scale9Sprite            *m_pLeftSpr;
    Scale9Sprite            *m_pRightSpr;
    cocos2d::Sprite         *m_pBackSpr;
    std::string               m_strTitle;
    std::string               m_strConnent;
    
    EventListenerTouchOneByOne* listener;
    
public:
    virtual void onEnter();
    virtual void onExit();
    
    virtual void myTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
public:
    bool checkBounding( cocos2d::Node* pNode, cocos2d::Point& point );
    void dismissThisLayer();

};

#endif /* defined(__MyTeeth__MessageBox__) */
