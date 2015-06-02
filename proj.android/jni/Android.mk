LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../Classes/AppDelegate.cpp \
#                   ../../Classes/HelloWorldScene.cpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                ../../Classes/AppDelegate.cpp\
../../Classes/Layer/MessageBox.cpp\
../../Classes/Layer/TeethLayer.cpp\
../../Classes/Manager/SceneManager.cpp\
../../Classes/platform/ios/ios.cpp\
../../Classes/Scene/BBSScene.cpp\
../../Classes/Scene/CoachScene.cpp\
../../Classes/Scene/GameScene.cpp\
../../Classes/Scene/MainScene.cpp\
../../Classes/Scene/RecordDayScene.cpp\
../../Classes/Scene/RecordScene.cpp\
../../Classes/Scene/SettingScene.cpp\
../../Classes/Tools/AccountData.cpp\
../../Classes/Tools/CustomViewTools.cpp\
../../Classes/Tools/DateUtils.cpp\
                ../../Classes/Simple.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes\
                    $(LOCAL_PATH)/../../Classes/config\
                    $(LOCAL_PATH)/../../Classes/Layer\
                    $(LOCAL_PATH)/../../Classes/platform\
                    $(LOCAL_PATH)/../../Classes/platform/ios\
                    $(LOCAL_PATH)/../../Classes/Scene\
                    $(LOCAL_PATH)/../../Classes/Manager\
                    $(LOCAL_PATH)/../../Classes/Tools


# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
