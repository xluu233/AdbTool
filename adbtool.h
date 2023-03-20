#ifndef ADBTOOL_H
#define ADBTOOL_H

#include <string>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>

using namespace std;

class AdbTool
{
public:
    AdbTool();

    static AdbTool* getInstance();

    static QString adbPath;

    bool isDeviceConnected();

    std::string getDeviceName(const std::string &id);

    //自动检测adb路径
    QString autoDetachAdb();

    static QString getAdbPath();
    static void setAdbPath(const QString &value);


    QString runCmd(const QString& c);
    QString runCmd(const QStringList& cl);

    QStringList runCmdWithList(const QString& c);
    QStringList runCmdWithList(const QStringList& cl);

private:
    static AdbTool *p;
    bool deviceConnected = false;

};

#endif // ADBTOOL_H
