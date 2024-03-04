/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Create a WiFi access point and provide a web server on it. */
#include "ApServer.h"

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;
bool over_flag = false;
// 其它文件的变量
extern unsigned char irri_time_pump; // 灌溉20s
extern bool clear_flag;
extern bool check_state;
extern bool irri_time_pump_state;


ESP8266WebServer server(80);

bool ap_over_flag()
{
    return over_flag;
}

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
/******************************************************
   函 数 名: handleChangeLedState
   描   述: 用于向客户端发送200响应信息(成功)
   参   数: 无
   返 回 值: 无
 ******************************************************/
void respondOK()
{
    server.send(200, "text/plain", "Success");
}

void respondStatus(char const *replay)
{
    server.send(200, "text/plain", replay);
}

void handleRoot()
{
    server.send(200, "text/html", "<h1>You are connected</h1>");
}

void handleOver()
{
    over_flag = true;
    server.send(200, "text/html", "<h1>Over Setting</h1>");
}

void handleTimeSetting()
{
    // 取出请求URL的LedState字段
    String tmpTimeSetting = server.arg("IrriTimeSetting");
    Serial.print("tmpTimeSetting = ");
    Serial.println(tmpTimeSetting);
    // 将其转换成整形
    int TimeSettingness = tmpTimeSetting.toInt();
    if (TimeSettingness > 60)
    {
        respondStatus("larger than 60!!");
        TimeSettingness = 60;
    }
    else if (TimeSettingness < 1)
    {
        respondStatus("smaller than 1!!");
        TimeSettingness = 5;
    }
    else
    {
        // 向客户端发送200响应信息(成功)
        respondOK();
    }
    Serial.print("irri_time_pump = ");
    irri_time_pump = TimeSettingness;
    Serial.println(irri_time_pump);
    irri_time_pump_state = true;
}

void handleChangeClearState()
{
    // 取出请求URL的LedState字段
    String LedstateStr = server.arg("ClearState");
    Serial.print("ClearState = ");
    Serial.println(LedstateStr);
    // 如果是true，则开灯
    if (LedstateStr == "true")
    {
        clear_flag = true;
    }
    // 如果是false，则关灯
    if (LedstateStr == "false")
    {
        clear_flag = false;
    }
    // 向客户端发送200响应信息(成功)
    respondOK();
}

/******************************************************
   函 数 名: handleChangeLedState
   描   述: 用于控制LED灯的亮灭
   参   数: 无
   返 回 值: 无
 ******************************************************/
void handleChangeLedState()
{
    // 取出请求URL的LedState字段
    String LedstateStr = server.arg("LedState");
    Serial.print("LedState = ");
    Serial.println(LedstateStr);
    // 如果是true，则开灯
    if (LedstateStr == "true")
    {
        analogWrite(LED_BUILTIN, 0);
    }
    // 如果是false，则关灯
    if (LedstateStr == "false")
    {
        analogWrite(LED_BUILTIN, 1023);
    }
    // 向客户端发送200响应信息(成功)
    respondOK();
}

/******************************************************
   函 数 名: handleChangeLedState
   描   述: 用于控制LED灯的亮灭
   参   数: 无
   返 回 值: 无
 ******************************************************/
void handleChangePumpState()
{
    // 取出请求URL的LedState字段
    String LedstateStr = server.arg("PumpState");
    Serial.print("PumpState = ");
    Serial.println(LedstateStr);
    // 如果是true，则开灯
    if (LedstateStr == "true")
    {
        analogWrite(LED_BUILTIN, 0);
    }
    // 如果是false，则关灯
    if (LedstateStr == "false")
    {
        analogWrite(LED_BUILTIN, 1023);
    }
    // 向客户端发送200响应信息(成功)
    respondOK();
}

void handleUserNotfound()
{
    server.send(440, "text/html", "<h1>You are connected</h1>");
}
/******************************************************
   函 数 名: handleChangeLedBrightness
   描   述: 用于控制LED灯的亮度
   参   数: 无
   返 回 值: 无
 ******************************************************/
void handleChangeLedBrightness()
{
    // 取出请求URL的LedBrightness字段
    String LedBrightnessStr = server.arg("LedBrightness");
    // 映射前(也即原始的数值)
    Serial.print("LedBrightnessStr = ");
    Serial.println(LedBrightnessStr);
    // 将其转换成整形
    int LedBrightness = LedBrightnessStr.toInt();
    // 数值范围映射(求数值为0-100，转为0-1023)
    LedBrightness = 1023 - map(LedBrightness, 0, 100, 0, 1023);
    // 映射后(也即写入管脚的电平数值(对应不同pwm占空比))
    Serial.print("LedBrightness = ");
    Serial.println(LedBrightness);
    // 写入电平
    analogWrite(LED_BUILTIN, LedBrightness);
    // 向客户端发送200响应信息(成功)
    respondOK();
}

/******************************************************
   函 数 名: handleCheckState
   描   述: 用于查看eeprom中的值
   参   数: 无
   返 回 值: 无
 ******************************************************/
void handleCheckState()
{
    // 取出请求URL的LedBrightness字段
    String checkEeprom = server.arg("checkEeprom");
    Serial.print("checkEeprom = ");
    Serial.println(checkEeprom);
    // 如果是true，则开灯
    if (checkEeprom == "true")
    {
        check_state = true;
    }
    // 如果是false，则关灯
    if (checkEeprom == "false")
    {
        check_state = false;

    }
    // 向客户端发送200响应信息(成功)
    respondOK();
}

/*
用于处理浏览器的请求
*/
void handleRequest()
{
    server.on("/", handleRoot);
    server.on("/over", handleOver);

    // 处理时间设置
    server.on("/timeSetting", handleTimeSetting);
    server.on("/changeLedState", handleChangeLedState);
    // 处理浏览器对灯亮度调节的请求
    server.on("/changeLedBrightness", handleChangeLedBrightness);
    // 处理原来双击事件
    server.on("/ClearState", handleChangeClearState);
    // 处理检测运行状态
    server.on("/checkEeprom", handleCheckState);
    // 处理其他网络请求
    server.onNotFound(handleUserNotfound);

}

void ap_setup()
{
    Serial.println();
    Serial.print("Configuring access point...");
    /* You can remove the password parameter if you want the AP to be open. */
    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    // 初始化网络服务器
    handleRequest();
    server.begin();
    Serial.println("HTTP server started");
}

void ap_loop()
{

    server.handleClient();
}
