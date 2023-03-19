#ifndef ADBTOOL_H
#define ADBTOOL_H

#include <string>

class AdbTool
{
public:
    AdbTool();

    static AdbTool* getInstance();

    bool isDeviceConnected();

    std::string getDeviceName(const std::string &id);

private:
    static AdbTool *p;
    bool deviceConnected = false;

};

#endif // ADBTOOL_H
