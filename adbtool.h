#ifndef ADBTOOL_H
#define ADBTOOL_H

#include <string>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>

using namespace std;

class AdbTool : public QObject
{
    Q_OBJECT
public:
    AdbTool();

    static AdbTool* getInstance();

    static QString adbPath;

    static QString curDevice;

    std::string getDeviceName(const std::string &id);

    //自动检测adb路径
    QString autoDetachAdb();

    static QString getAdbPath();
    static void setAdbPath(const QString &value);


    QString runCmd(const QString& c);
    QString runCmd(const QStringList& cl);

    QStringList runCmdWithList(const QString& c);
    QStringList runCmdWithList(const QStringList& cl);

    static QString getCurDevice();
    static void setCurDevice(const QString &value);

    QStringList getDeviceList();

signals:
    void initAdb(const QString& adb);
    void initDeviceList(const QStringList& deviceList);

private:
    static AdbTool *p;


};

#endif // ADBTOOL_H
