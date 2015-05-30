//
//  XBridge.h
//  MyTeeth
//
//  Created by Penny on 15/5/30.
//
//

#ifndef __MyTeeth__XBridge__
#define __MyTeeth__XBridge__

class XBridge{
public:
    //ios call cocos2d-x
    static void iosBrushInfo(int type, int value);
    
    static void iosBluetoothConnect(bool isConnect);
    
    //cocos2d-x call ios
    static void setBluetoothEnable(bool bluetoothEnable);
};

#endif /* defined(__MyTeeth__XBridge__) */
