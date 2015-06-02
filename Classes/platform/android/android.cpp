#include "android.h"
#include "../../../cocos2d/cocos/cocos2d.h"

#include <stdio.h>
#include "Header.h"

USING_NS_CC;

#if defined(ANDROID)

#include <jni.h>
#include "../../../cocos2d/cocos/platform/android/jni/JniHelper.h"


//java call C++
extern "C"
{
    JNIEXPORT jboolean JNICALL Java_jni_JniApi_androidBluetoothConnected(JNIEnv *env, jobject thiz, jboolean isConnect)
    {
        std::string sData = "";
        if (isConnect == true) {
            sData = "1";
        }else{
            sData = "0";
        }
        auto stringData = String::create(sData);
        NotificationCenter::getInstance()->postNotification("bluetoothConnectNotification", stringData);
        return true;
    }
    
    JNIEXPORT jboolean JNICALL Java_jni_JniApi_androidBluetoothEvent(JNIEnv *env, jobject thiz, jint type, jint value)
    {
        CCLOG("******Java_jni_JniApi_androidBluetoothEvent****** type=%d, value=%d", type, value);
        std::string sData = StringUtils::format("%d", value);
        auto stringData = String::create(sData);
        NotificationCenter::getInstance()->postNotification("bluetoothBrushNotification", stringData);
        return true;
    }
};

void setBluetoothEnable(bool btEnable)
{
	JniMethodInfo method;

	bool b = JniHelper::getStaticMethodInfo(method, "jni.JniApi", "setAndroidBluetoothEnable", "(Z)V");
	if(b) {
		method.env->CallStaticVoidMethod(method.classID, method.methodID, btEnable);
		method.env->DeleteLocalRef(method.classID);
	}
}

#endif
