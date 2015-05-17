//
//  SettingScene.h
//  MyTeeth
//
//  Created by wlp on 15/4/30.
//
//

#ifndef __MyTeeth__SettingScene__
#define __MyTeeth__SettingScene__

#include "Header.h"

class SettingScene : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{
public:
    
    int i_sex;
    std::string nameStr;
    std::string ageStr;
    
    cocos2d::Sprite *manSelectSpreite;
    
    cocos2d::Sprite *womSelectSpreite;
    
    //
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void loadView();

    void menuCallback(cocos2d::Ref* pSender);
    
    void manMenuCallback(cocos2d::Ref* pSender);

    void womMenuCallback(cocos2d::Ref* pSender);

    void setSexDisplay(int sex);
    
    void confirmMenuCallback(cocos2d::Ref* pSender);
    
    //
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);

protected:

    cocos2d::ui::EditBox* _editName;
    cocos2d::ui::EditBox* _editAge;
    
    CREATE_FUNC(SettingScene);
};
#endif /* defined(__MyTeeth__SettingScene__) */
