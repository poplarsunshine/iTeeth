//
//  ios.cpp
//  MyTeeth
//
//  Created by Penny on 15/5/30.
//
//

#include "API_Interface.h"
#include <stdio.h>

#include "Header.h"
//#include "GameScene.h"

#if defined(CC_TARGET_OS_IPHONE)

#include "XBridge.h"

//-x call ios


void setBluetoothEnable(bool btEnable)
{
    XBridge::setBluetoothEnable(btEnable);
}

//ios call -x

void brushCallBack(int type, int value)
{
    printf("type=%d, value=%d", type, value);
    std::string sData = StringUtils::format("%d", value);
    auto stringData = String::create(sData);
    NotificationCenter::getInstance()->postNotification("bluetoothBrushNotification", stringData);
}

void bluetoothConnect(bool isConnect)
{
    std::string sData = "";
    if (isConnect == true) {
        sData = "1";
    }else{
        sData = "0";
    }
    auto stringData = String::create(sData);
    NotificationCenter::getInstance()->postNotification("bluetoothConnectNotification", stringData);
}

#endif
