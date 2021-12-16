#!/bin/bash

adb_uninstall() {
 result=$(adb shell pm uninstall -k --user 0 $1)
 echo "${1}: $result"
}

echo "Uninstalling starting"

adb_uninstall com.xiaomi.gamecenter
adb_uninstall com.xiaomi.vipaccount
adb_uninstall com.xiaomi.scanner
adb_uninstall com.xiaomi.payment
adb_uninstall com.xiaomi.smarthome
adb_uninstall com.xiaomi.o2o
adb_uninstall com.xiaomi.jr
adb_uninstall com.xiaomi.jr.security
adb_uninstall com.xiaomi.youpin
adb_uninstall com.xiaomi.shop
adb_uninstall com.xiaomi.mibrain.speech
adb_uninstall com.xiaomi.mimobile.noti

adb_uninstall com.miui.fm
adb_uninstall com.miui.compass
adb_uninstall com.miui.miuibbs
adb_uninstall com.miui.video
adb_uninstall com.miui.screenrecorder
adb_uninstall com.miui.hybrid
adb_uninstall com.miui.weather2
adb_uninstall com.miui.virtualsim
adb_uninstall com.miui.bugreport
adb_uninstall com.miui.voiceassist
adb_uninstall com.miui.yellowpage
adb_uninstall com.miui.personalassistant
adb_uninstall com.miui.klo.bugreport

adb_uninstall com.mi.liveassistant
adb_uninstall com.xiaomi.channel
adb_uninstall com.baidu.BaiduMap
adb_uninstall com.mipay.wallet

adb_uninstall com.android.email
adb_uninstall com.android.midrive
adb_uninstall com.android.soundrecorder

adb_uninstall com.wali.live
adb_uninstall com.duokan.reader
adb_uninstall com.yidian.xiaomi
adb_uninstall com.xiangkan.android
adb_uninstall com.codeaurora.fmradio
adb_uninstall com.cleanmaster.mguard_cn
adb_uninstall com.iflytek.inputmethod.miui
adb_uninstall com.duokan.phone.remotecontroller
adb_uninstall com.sohu.inputmethod.sogou.xiaomi
adb_uninstall com.google.android.marvin.talkback

echo "Uninstalling finished. Rebooting"

adb reboot

# NEVER DEBLOAT !!!
# com.xiaomi.market (App Store)
# com.xiaomi.account (Mi Account)
# com.android.quicksearchbox (Search)
# com.android.thememanager (Theme Manager)
