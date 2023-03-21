#include "adbtool.h"
#include <QTime>


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

QString AdbTool::curTime()
{
//    QTime time = QTime::currentTime();
//    return time.toString("hh_mm_ss");

    QDateTime dateTime = QDateTime::currentDateTime();
    return dateTime.toString("yyyy-MM-dd_hh-mm-ss");
}


QString AdbTool::runCmd(const QStringList &cl)
{
    qDebug() << "runCmd:" << cl;
    QProcess p(0);
    curProcess = &p;
    p.start("cmd", cl,QProcess::ReadWrite);
    p.waitForStarted();
    p.waitForFinished();
    QString strTemp = QString::fromLocal8Bit(p.readAllStandardOutput());
    qDebug() << "runCmd-result:" << strTemp;
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

bool AdbTool::installApk(QString &apk)
{
    if(apk.length() == 0)
        return false;

    //install apk路径
    QString cmd = QString(adbPath).append(" ").append("install ").append(apk);
    QString res = runCmd(cmd);

    if(res.contains("Success")){
        return true;
    }else{
        return false;
    }
}

bool AdbTool::getScreenShot(QString &path)
{
    //adb shell screencap /sdcard/screen.png
    //adb pull /sdcard/screen.png F:\screenshot

    QString fileName = QString("/sdcard/DCIM/screen_%1.png").arg(curTime());

    QString cmd = QString(adbPath).append(" ").append("shell screencap ").append(fileName);
    runCmd(cmd);
    QString cmd2 = QString(adbPath).append(" ").append("pull  ").append(fileName).append("  ").append(path);
    QString res = runCmd(cmd2);
    if(res.contains("file pulled")){
        return true;
    }else{
        return false;
    }
}


void AdbTool::startScreenVideo(const QString &fileName)
{
    QString cmd = QString(adbPath).append(" ").append("shell screenrecord ").append(fileName);
    //子线程运行
    QtConcurrent::run([=](){
        runCmd(cmd);
    });

}


bool AdbTool::stopScreenVideo(QString &path, QString& fileName)
{
//    curProcess->close();;
//    curProcess->waitForFinished();
//    curProcess->kill();
//    curProcess->terminate();
    QtConcurrent::run([=](){
        curProcess->close();
    });
    QString cmd2 = QString(adbPath).append(" ").append("pull ").append(fileName).append("  ").append(path);
    QString res = runCmd(cmd2);
    if(res.contains("file pulled")){
        return true;
    }else{
        return false;
    }
}

QString AdbTool::getCurActivity()
{
   //adb
   QString cmd = QString(adbPath).append("  shell dumpsys window | findstr mCurrentFocus");
   QString res = runCmd(cmd);
   //  mCurrentFocus=Window{b7daccd u0 com.android.mms/com.android.mms.ui.MmsTabActivity}\r\n
   res.remove(0,res.indexOf('{'));
   res.remove(res.lastIndexOf('}')+1,res.length());
   qDebug() << res;
   return res;
}

void AdbTool::shellKey(int key)
{
    //adb shell input keyevent 26
    QString cmd = QString(adbPath).append("  shell input keyevent %1").arg(key);
    runCmd(cmd);
}

QStringList AdbTool::getAllApp()
{
    //adb shell pm list packages
    QString cmd = QString(adbPath).append(" shell pm list packages");
    return runCmd(cmd).split("\r\n");
}

QString AdbTool::getPhoneModel()
{
    QString brand = runCmd(QString(adbPath).append(" shell getprop ro.product.brand")).remove("\r\n");
//    QString board = runCmd(QString(adbPath).append(" shell getprop ro.product.board")).remove("\r\n");
    QString model = runCmd(QString(adbPath).append(" shell getprop ro.product.model")).remove("\r\n");
    //brand.append(" ").append(board).append(" ").append(model);
    return brand.append(" ").append(model);
}

QString AdbTool::getIpAddr()
{
    QString ip = QString(adbPath).append(" shell ifconfig wlan0");
    return runCmd(ip);
}

QString AdbTool::getMacAddr()
{
    //adb shell cat /sys/class/net/wlan0/address
    return runCmd(QString(adbPath).append(" shell cat /sys/class/net/wlan0/address"));
}

QString AdbTool::getAndroidId()
{
    //adb shell settings get secure android_id
    return runCmd(QString(adbPath).append(" shell settings get secure android_id"));
}

QString AdbTool::getAndroidVersion()
{
    // shell getprop ro.build.version.sdk
    // shell getprop ro.build.version.release
    QString sdk = runCmd(QString(adbPath).append(" shell getprop ro.build.version.sdk"));
    QString release = runCmd(QString(adbPath).append(" shell getprop ro.build.version.release"));
    return "Android" + release.remove("\r\n") + "  (" + sdk.remove("\r\n") + ")";
}

void AdbTool::rebot()
{
    runCmd(QString(adbPath).append(" reboot"));
}

void AdbTool::uninstallApk(const QString &app)
{
    runCmd(QString(adbPath).append(" uninstall ").append(app));
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

