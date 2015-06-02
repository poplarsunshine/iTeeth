//
//  ToothLayer.h
//  MyTeeth
//
//  Created by Penny on 15/5/17.
//
//

#ifndef __MyTeeth__ToothLayer__
#define __MyTeeth__ToothLayer__

#include "Header.h"

typedef enum
{
    Tooth_down_left_inside      = 0,
    Tooth_down_left_outside     = 1,
    Tooth_up_right_outside      = 2,
    Tooth_down_right_inside     = 3,
    Tooth_down_right_outside    = 4,
    Tooth_front_down_inside     = 5,
    Tooth_front_down_left       = 6,
    Tooth_front_down_right      = 7,
    Tooth_front_down            = 8,
    Tooth_front_up_inside       = 9,
    Tooth_front_up_left         = 10,
    Tooth_front_up_right        = 11,
    Tooth_front_up              = 12,
    Tooth_up_left_inside        = 13,
    Tooth_up_left_outside       = 14,
    Tooth_up_right_inside       = 15,
    Tooth_Space_Type_Max        = 16
}E_Tooth_SPACE;

class TeethLayerDelegate
{
public:
    //virtual void gameCtrlLayerClickStartGame() = 0;
};

class TeethLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    
    CREATE_FUNC(TeethLayer);
    
    void setDelegate(TeethLayerDelegate *delegate) { m_delegate = delegate; }
    
    void setCurTooth(E_Tooth_SPACE toothSpaceType);

private:
    TeethLayerDelegate *m_delegate;
    
    cocos2d::Vector<cocos2d::Sprite*> m_teethList;
    
    void setAllToothHide();

};

#endif /* defined(__MyTeeth__ToothLayer__) */
