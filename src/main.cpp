#include "../3rdparty/huaweicloud-iot-device-sdk-c/include/third_party/cjson/cJSON.h"
#include "../3rdparty/huaweicloud-iot-device-sdk-c/include/util/json_util.h"
#include "../3rdparty/huaweicloud-iot-device-sdk-c/include/agentlite/iota_init.h"
#include "../3rdparty/huaweicloud-iot-device-sdk-c/include/base/mqtt_base.h"

static void MyPrintLog(int level, char *format, va_list args)
{
    vprintf(format, args);
    /*
     * if you want to printf log in system log files,you can do this:
     * vsyslog(level, format, args);
     **/
}

int main() {
    IOTA_SetPrintLogCallback(MyPrintLog);
    return 0;
}