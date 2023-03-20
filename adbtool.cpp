#include "adbtool.h"


QString AdbTool::adbPath = "";
QString AdbTool::curDevice = "";

AdbTool* AdbTool::p = nullptr;

AdbTool* AdbTool::getInstance()
{
    if(p == nullptr){
        p = new AdbTool();
    }
    return p;
}

QString AdbTool::getCurDevice()
{
    return curDevice;
}

void AdbTool::setCurDevice(const QString &value)
{
    curDevice = value;
}

AdbTool::AdbTool() : QObject()
{

}


QString AdbTool::runCmd(const QStringList &cl)
{
    qDebug() << "runCmd:" << cl;
    QProcess p(0);
    p.start("cmd", cl);
    p.waitForStarted();
    p.waitForFinished();
    QString strTemp = QString::fromLocal8Bit(p.readAllStandardOutput());
    return strTemp;
}

QString AdbTool::runCmd(const QString &c)
{
    QStringList cl = QStringList()<< "/c" << c;;
    return runCmd(cl);
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


QStringList AdbTool::getDeviceList()
{
    QString cmd = QString(adbPath).append(" ").append("devices");
    QStringList outputList = runCmdWithList(cmd);
    qDebug() << "getDeviceList:" << outputList;

    QStringList res;
    //可能会出现offline状态，暂时不处理
    for(auto& s: outputList){
        if(s.contains("\tdevice") && s.size() != 0 && outputList.indexOf(s) != 0){
            res.push_back(s.remove("\tdevice"));
        }
    }
    qDebug() << "emit initDeviceList";
    emit initDeviceList(res);
//    qDebug() << "getDeviceList:" << res;
    return res;
}

QString AdbTool::getAdbPath()
{
    return adbPath;
}

void AdbTool::setAdbPath(const QString &value)
{
    adbPath = value;
}

std::string AdbTool::getDeviceName(const std::string &id)
{
    return "小米-dad0f12df";
}

QString AdbTool::autoDetachAdb()
{
    QStringList strList = runCmdWithList("adb version");
    qDebug() << "autoDetachAdb：" << strList;

    QString adbPath;
    if(strList.size() >= 3){
        for(auto &s :strList){
            if(s.contains("adb.exe")){
                adbPath = s.remove("Installed as ");
            }
        }
    }
    emit initAdb(adbPath);
//    qDebug() << "autoDetachAdb：" << adbPath;
    return adbPath;
}

