//
//  XBridge.cpp
//  MyTeeth
//
//  Created by Penny on 15/5/30.
//
//

#include "XBridge.h"
#include "API_Interface.h"
#import "AppController.h"

//ios call -x
void XBridge::iosBrushInfo(int type, int value)
{
    brushCallBack(type, value);
}

void XBridge::iosBluetoothConnect(bool isConnect)
{
    bluetoothConnect(isConnect);
}


//-x call ios
void XBridge::setBluetoothEnable(bool bluetoothEnable)
{
    NSLog(@"ios setBluetoothEnable %d", bluetoothEnable);
    AppController *app = (AppController*)([[UIApplication sharedApplication] delegate]);
    [app scanBluetoothDevice:bluetoothEnable];
}