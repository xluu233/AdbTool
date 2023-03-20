#include "adbtool.h"


QString AdbTool::adbPath = "";

AdbTool* AdbTool::p = nullptr;

AdbTool* AdbTool::getInstance()
{
    if(p == nullptr){
        p = new AdbTool();
    }
    return p;
}

AdbTool::AdbTool()
{

}

QString AdbTool::runCmd(const QString &c)
{
    QProcess p(0);
    p.start("cmd", QStringList()<< "/c" << c);
    p.waitForStarted();
    p.waitForFinished();
    QString strTemp = QString::fromLocal8Bit(p.readAllStandardOutput());
    return strTemp;
}

QString AdbTool::runCmd(const QStringList &cl)
{
    QProcess p(0);
    p.start("cmd", cl);
    p.waitForStarted();
    p.waitForFinished();
    QString strTemp = QString::fromLocal8Bit(p.readAllStandardOutput());
    return strTemp;
}

QStringList AdbTool::runCmdWithList(const QString &c)
{
    QString str = runCmd(c);
    return str.split("\r\n");
}

QStringList AdbTool::runCmdWithList(const QStringList &cl)
{
    QString str = runCmd(cl);
    return str.split("\r\n");
}

QString AdbTool::getAdbPath()
{
    return adbPath;
}

void AdbTool::setAdbPath(const QString &value)
{
    adbPath = value;
}

bool AdbTool::isDeviceConnected()
{
    return deviceConnected;
}

std::string AdbTool::getDeviceName(const std::string &id)
{
    return "小米-dad0f12df";
}

QString AdbTool::autoDetachAdb()
{
    QStringList strList = runCmdWithList("adb version");
//    qDebug() << "autoDetachAdb：" << strList;

    QString adbPath;
    if(strList.size() >= 3){
        for(auto &s :strList){
            if(s.contains("adb.exe")){
                adbPath = s.remove("Installed as ");
            }
        }
    }

    qDebug() << "autoDetachAdb：" << adbPath;
    return adbPath;
}

