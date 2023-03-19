#include "adbtool.h"

AdbTool::AdbTool()
{

}

AdbTool* AdbTool::p = nullptr;

AdbTool* AdbTool::getInstance()
{
    if(p == nullptr){
        p = new AdbTool();
    }
    return p;
}

bool AdbTool::isDeviceConnected()
{
    return deviceConnected;
}

std::string AdbTool::getDeviceName(const std::string &id)
{
    return "小米-dad0f12df";
}

