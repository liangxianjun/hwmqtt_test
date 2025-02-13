#include <iostream>
#include <unistd.h>
extern "C" {
#include "cJSON.h"
#include "json_util.h"
#include "log_util.h"
#include "iota_init.h"
#include "iota_cfg.h"
#include "iota_login.h"
#include "iota_datatrans.h"
#include "mqtt_base.h"
#include "subscribe.h"
}

char *g_address = "1145141919.st1.iotda-device.cn-south-1.myhuaweicloud.com"; 
char *g_port = "8883";
char *g_deviceId = "sb"; 
char *g_password = "sb";

#ifndef CUSTOM_RECONNECT_SWITCH
static int g_connectFailedTimes = 0;
#endif

void TimeSleep(int ms)
{
#if defined(WIN32) || defined(WIN64)
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

static void MyPrintLog(int level, char *format, va_list args)
{
    vprintf(format, args);
}

static void HandleMessageDown(EN_IOTA_MESSAGE *rsp, void *mqttv5)
{
    if (rsp == NULL) {
        return;
    }
    PrintfLog(EN_LOG_LEVEL_INFO, "basic_test: %s(), content: %s\n", __FUNCTION__,  rsp->content);
    PrintfLog(EN_LOG_LEVEL_INFO, "basic_test: %s(), id: %s\n", __FUNCTION__, rsp->id);
    PrintfLog(EN_LOG_LEVEL_INFO, "basic_test: %s(), name: %s\n", __FUNCTION__,  rsp->name);
    PrintfLog(EN_LOG_LEVEL_INFO, "basic_test: %s(), objectDeviceId: %s\n", __FUNCTION__, rsp->object_device_id);
}

static void SubscribeDeviceTpoic(void)
{
    SubscribeAllQos(1);
}

static void HandleConnectSuccess(EN_IOTA_MQTT_PROTOCOL_RSP *rsp)
{
    (void)rsp;
    PrintfLog(EN_LOG_LEVEL_INFO, "basic_test: HandleConnectSuccess(), login success\n");
    /* Connection successful, subscribe */
    SubscribeDeviceTpoic();
}

static void HandleConnectionBroken(const char *handleName, const EN_IOTA_MQTT_PROTOCOL_RSP *rsp)
{
    PrintfLog(EN_LOG_LEVEL_ERROR, "device_demo: %s() error, messageId %d, code %d, messsage %s\n", handleName,
        rsp->mqtt_msg_info->messageId, rsp->mqtt_msg_info->code, rsp->message);

#ifndef CUSTOM_RECONNECT_SWITCH
    // judge if the network is available etc. and login again
    // ...
    PrintfLog(EN_LOG_LEVEL_ERROR, "device_demo: %s() login again\n", handleName);

    g_connectFailedTimes++;
    if (g_connectFailedTimes < 10) {
        TimeSleep(5000);
    } else {
        TimeSleep(25000);
    }

    int ret = IOTA_Connect();
    if (ret != 0) {
        PrintfLog(EN_LOG_LEVEL_ERROR, "device_demo: HandleAuthFailure() error, login again failed, result %d\n", ret);
    }
#endif
}

static void HandleConnectFailure(EN_IOTA_MQTT_PROTOCOL_RSP *rsp)
{
    HandleConnectionBroken("HandleConnectFailure", rsp);
}

int main() {
    if(IOTA_Init("..") < 0) {
        std::cerr<<"device_demo: IOTA_Init() error, init failed\n";
        return 1;
    }
    
    IOTA_SetPrintLogCallback(MyPrintLog);
    IOTA_ConfigSetUint(EN_IOTA_CFG_AUTH_MODE, EN_IOTA_CFG_AUTH_MODE_SECRET);
    IOTA_ConnectConfigSet(g_address, g_port, g_deviceId, g_password);
    
    IOTA_SetProtocolCallback(EN_IOTA_CALLBACK_CONNECT_SUCCESS, HandleConnectSuccess);
    // Set connection callback function
    IOTA_SetProtocolCallback(EN_IOTA_CALLBACK_CONNECT_FAILURE, HandleConnectFailure);
    IOTA_SetProtocolCallback(EN_IOTA_CALLBACK_CONNECTION_LOST, HandleConnectFailure);

    IOTA_SetMessageCallback(HandleMessageDown);

    int ret = IOTA_Connect();
     if (ret != 0) {
        PrintfLog(EN_LOG_LEVEL_ERROR, "basic_test: IOTA_Connect() error, Auth failed, result %d\n", ret);
        return -1;
    }

    while(!IOTA_IsConnected()) {
        TimeSleep(300);
        std::cout<<"s"<<std::endl;
    }
    std::cout<<"b"<<std::endl;;
    while(1) {
        // Report a message with ID of "id" to the device, with the message content "hello!"
        ST_IOTA_MESS_REP_INFO mass = {NULL, "name", "id", "hello", NULL};
        int messageId = IOTA_MessageDataReport(mass, NULL);
        if (messageId < 0) {
            PrintfLog(EN_LOG_LEVEL_ERROR, "basic_test: Test_MessageReport() failed, messageId %d\n", messageId);
        }
        TimeSleep(3000);
    }
    return 0;
}
