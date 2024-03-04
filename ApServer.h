#ifndef __APSERVER_H_
#define __APSERVER_H_
/*
在WWW上，每一信息资源都有统一的且在网上唯一的地址，该地址就叫URL（Uniform Resource Locator，统一资源定位器），它是WWW的统一资源定位标志，就是指网络地址。

组成：<协议>://<主机>:<端口>/<路径>，端口和路径有时可以省略，HTTP默认端口号为80。

参数：以 “?” 开始，格式为 “name=value” ，如果存在多个参数，则参数之间用 “&” 隔开，后端在收到前端的请求时，可以解析出URL参数。

项目中控制板载LED亮的请求URL，其中LedState=true就是参数。
https://blog.csdn.net/weixin_45734719/article/details/113698990

# 打开灯光
http://192.168.4.1/
http://192.168.4.1/over
http://192.168.4.1/changeLedState?LedState=true 
http://192.168.4.1/ClearState?ClearState=true 
http://192.168.4.1/changeLedBrightness?LedBrightness=80 
http://192.168.4.1/timeSetting?IrriTimeSetting=50 
http://192.168.4.1/checkEeprom?checkEeprom=50 
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK "12345678"
#endif


void ap_setup();
void ap_loop();
bool ap_over_flag();



#endif



