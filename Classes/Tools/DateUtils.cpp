//
//  DateUtils.cpp
//  MyTeeth
//
//  Created by Penny on 15/5/26.
//
//

#include "DateUtils.h"

std::string DateUtils::getCurrentDate()
{
    //获取系统时间
    struct timeval now;
    struct tm *time;
    
    gettimeofday(&now, NULL);
    
    time = localtime(&now.tv_sec);      //microseconds: 微秒
    int year = time->tm_year +1900;
    //log("year = %d", year);         //显示年份
    
    char date1[32] = {0};
    sprintf(date1, "%d%02d%02d", (int)time->tm_year + 1900, (int)time->tm_mon + 1, (int)time->tm_mday);
    log("date1=%s", date1);        //显示年月日
    
    return date1;
}

std::string DateUtils::getCurrentTime()
{
    //获取系统时间
    struct timeval now;
    struct tm *time;
    
    gettimeofday(&now, NULL);
    
    time = localtime(&now.tv_sec);      //microseconds: 微秒
    
    char date2[50] = {0};
    sprintf(date2, "%02d%02d", (int)time->tm_hour, (int)time->tm_min);
    log("date2=%s", date2);       //显示时分
    return date2;
}

double DateUtils::getMillSecond()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    
    log("CurrentTime MillSecond %f", (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000);
    
    return (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
}


int DateUtils::getDayOfWeek()
{
    struct tm tinfo;
    time_t rawtime;
    time (&rawtime);
    
    tinfo = *localtime(&rawtime);
    
    return (int)tinfo.tm_wday;
}

int DateUtils::getDaysWithYM(int year, int month)
{
    switch (month - 1) {
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
            return 31;
            break;
        case 1:
        {
            if ((year % 4 == 0 && year % 100 != 0)|| year % 400 == 0)
            {
                return 29;
            }
            else
            {
                return 28;
            }
            break;
        }
        case 3:
        case 5:
        case 8:
        case 10:
            return 30;
            break;
        default:
            return 0;
            break;
    }
}

int DateUtils::getCaculateWeek(int y, int m, int d)
{
    if(m==1||m==2) {
        m+=12;
        y--;
    }
    int iWeek=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
    return iWeek;
}