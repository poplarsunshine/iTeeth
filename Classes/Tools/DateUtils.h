//
//  DateUtils.h
//  MyTeeth
//
//  Created by Penny on 15/5/26.
//
//

#ifndef __MyTeeth__DateUtils__
#define __MyTeeth__DateUtils__

#include "cocos2d.h"

USING_NS_CC;

class DateUtils
{
public:
    
    
    // 格式化时间返回
    
    // 获取系统毫秒时间
    static double getMillSecond();
    // 获取当天星期
    static int getDayOfWeek();
    
    // 日期
    static std::string getCurrentDate();
    // 时间
    static std::string getCurrentTime();
    // 根据日期获取星期
    //0----周一
    //1----周二
    static int getCaculateWeek(int y, int m, int d);
    // 获取指定年月的天数
    static int getDaysWithYM(int year, int month);

};

#endif /* defined(__MyTeeth__DateUtils__) */
