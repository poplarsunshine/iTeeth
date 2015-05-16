//
//  MessageBox.cpp
//  MyTeeth
//
//  Created by Penny on 15/5/14.
//
//

#include "MessageBox.h"

//CMessageBox::CMessageBox():
//m_pTarget(NULL),
//m_leftCallback(NULL),
//m_rightCallback(NULL),
//m_backCallback(NULL),
//m_strTitle(""),
//m_strConnent(""),
//m_pLeftSpr(NULL),
//m_pRightSpr(NULL),
//m_pBackSpr(NULL)
//{
//    
//}
//
//CMessageBox::~CMessageBox( void )
//{
//    
//}

CMessageBox *CMessageBox::createBy(int type,
                                   Node* pLayerTarget,
                                   std::string title,
                                   std::string con,
                                   std::string leftLabel,
                                   std::string rightLabel,
                                   SEL_MessageBoxHandler leftBtnSel,
                                   SEL_MessageBoxHandler rightBtnSel,
                                   SEL_MessageBoxHandler backBtnSel)
{
    CMessageBox *pRet = new(std::nothrow) CMessageBox();
    if (pRet && pRet->init(type,
                           pLayerTarget,
                           title,
                           con,
                           leftLabel,
                           rightLabel,
                           leftBtnSel,
                           rightBtnSel,
                           backBtnSel))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool CMessageBox::init(int type,
                       Node* pLayerTarget,
                       std::string title,
                       std::string con,
                       std::string leftLabelTitle,
                       std::string rightLabelTitle,
                       SEL_MessageBoxHandler leftBtnSel,
                       SEL_MessageBoxHandler rightBtnSel,
                       SEL_MessageBoxHandler backBtnSel)
{
    m_pTarget = pLayerTarget;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto pLayerColor = LayerColor::create(Color4B(0, 0, 0, 255), visibleSize.width * 2, visibleSize.height * 2);
    pLayerColor->setOpacity(50);
    this->addChild(pLayerColor);
    
    Size bgSize = Size(visibleSize.width - 80, 300);
    Size btnSize = Size(visibleSize.width / 3, 100);

    m_pBackgroundSpr = Scale9Sprite::create(Rect(70, 70, 20, 20), "white-background.png");
    m_pBackgroundSpr->setContentSize(bgSize);
    m_pBackgroundSpr->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(m_pBackgroundSpr, 0);
    
    if ("" != leftLabelTitle)
    {
        m_pLeftSpr = Scale9Sprite::create( Rect(20, 20, 20, 20), "button-yellow-default.png" );
        m_pLeftSpr->setContentSize(btnSize);
        m_pLeftSpr->setPosition(Vec2(visibleSize.width * 0.3, m_pBackgroundSpr->getPosition().y));
        this->addChild(m_pLeftSpr);
        //m_pLeftSpr->autorelease();
        
        m_leftCallback = leftBtnSel;
        
        auto label = Label::createWithSystemFont(leftLabelTitle.c_str(),
                                                     "Arial",
                                                     40,
                                                     btnSize,
                                                     TextHAlignment::CENTER,
                                                     TextVAlignment::CENTER
                                                     );
        label->setPosition(Vec2(m_pLeftSpr->getPosition().x, m_pLeftSpr->getPosition().y));
        this->addChild(label,0);
    }
    
    if ("" != rightLabelTitle)
    {
        m_pRightSpr = Scale9Sprite::create( Rect(20, 20, 20, 20), "button-green-default.png" );
        m_pRightSpr->setContentSize(btnSize);
        m_pRightSpr->setPosition(Vec2(visibleSize.width * 0.7, m_pBackgroundSpr->getPosition().y));
        this->addChild(m_pRightSpr);
        //m_pRightSpr->autorelease();

        m_rightCallback = rightBtnSel;
        
        auto label = Label::createWithSystemFont(rightLabelTitle.c_str(),
                                                 "Arial",
                                                 40,
                                                 btnSize,
                                                 TextHAlignment::CENTER,
                                                 TextVAlignment::CENTER
                                                 );
        label->setPosition(Vec2(m_pRightSpr->getPosition().x, m_pRightSpr->getPosition().y));
        this->addChild(label,0);
    }
    
    if (1 == type)
    {

    }
    
    return true;
}

void CMessageBox::onEnter()
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

void CMessageBox::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}

void CMessageBox::myTouchEnded( Touch *pTouch, Event *pEvent )
{
    Point point = pTouch->getLocation() - this->getPosition();
    bool needDis = false;
    
    if ( !checkBounding( m_pBackgroundSpr, point ) )
    {
        needDis = true;
    }
    else
    {
        if ( checkBounding( m_pLeftSpr, point ) )
        {
            if ( NULL != m_leftCallback && NULL != m_pTarget)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);
                (m_pTarget->*m_leftCallback)();
                needDis = true;
            }
        }
        else if ( checkBounding( m_pRightSpr, point )  )
        {
            if ( NULL != m_rightCallback && NULL != m_pTarget)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileName_AudioEffect);
                (m_pTarget->*m_rightCallback)();
                this->dismissThisLayer();
            }
        }
        else
        {
            
        }
    }
    
    if (needDis) {
        this->dismissThisLayer();
    }
}

void CMessageBox::dismissThisLayer()
{
    this->removeFromParent();
    //CMyMusic::sharedMyMusic()->playEffect("buttonT.mp3");
}

bool CMessageBox::checkBounding( Node* pNode, Point& point )
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