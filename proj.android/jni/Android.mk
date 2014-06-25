LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/PlayScene.cpp\
                   ../../Classes/Mgr/BackgroundMgr.cpp\
                   ../../Classes/Mgr/CoinMgr.cpp\
                   ../../Classes/Mgr/FishMgr.cpp\
                   ../../Classes/Mgr/LevelMgr.cpp\
                   ../../Classes/Mgr/NetMgr.cpp\
                   ../../Classes/Mgr/NumFactory.cpp\
                   ../../Classes/Mgr/UIMgr.cpp\
                   ../../Classes/Mgr/WaterWaveMgr.cpp\
                   ../../Classes/Obj/Background.cpp\
                   ../../Classes/Obj/Coin.cpp\
                   ../../Classes/Obj/Fish.cpp\
                   ../../Classes/Obj/Net.cpp\
                   ../../Classes/Obj/Number.cpp\
                   ../../Classes/Obj/Player.cpp\
                   ../../Classes/Obj/WaterWave.cpp\
                   ../../Classes/Ui/MainFrame.cpp\
                   ../../Classes/Ui/PopupLayer.cpp\
                   ../../Classes/Ui/SkillFrame.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
