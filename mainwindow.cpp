#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adbtool.h"
#include "QImageReader"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include "iconhelper.h"
#include "mainwindow.h"
#include <QGridLayout>
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMenu();
    initSetting();
}

MainWindow::~MainWindow()
{
    delete ui;
}


QPixmap loadImageFunc(const QString &path,const QSize &size){
    QImageReader imageRender;
    imageRender.setFileName(path);
    imageRender.setAutoTransform(true);

    //原图size
    auto old_size = imageRender.size();
    auto target_size = old_size.scaled(size,Qt::KeepAspectRatio);

    imageRender.setScaledSize(target_size);

    QPixmap pixmap = QPixmap::fromImageReader(&imageRender);
    return pixmap;
}

QToolButton& getListBtn(const QString &icon,const QString &text){
    QToolButton *btn = new QToolButton;
    QString style = QString("QToolButton{");
    style.append("color:rgb(47, 47, 47);");
    style.append("font-size:12;font-family:Microsoft YaHei;font-weight:normal;");
    style.append("qproperty-icon:url(%1); qproperty-iconSize:60px 60px;");
    style.append("padding:10px;border-radius: 10px");
    style.append("}\n");
    style.append("QToolButton::hover {");
    style.append("background-color:rgba(171, 171, 171,50);");
    style.append("}");

    QString style2 = QString(style).arg(icon);
    qDebug() << style2;

    btn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    btn->setText(text);
    btn->setFixedHeight(120);
    btn->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding));
    btn->setStyleSheet(style2);
    return *btn;
}


void MainWindow::initMenu()
{
    ui->stackedWidget->setCurrentIndex(0);



}

void MainWindow::initSetting()
{
    ui->adb_edit->setPlaceholderText("请输入或选择ADB路径");

    connect(AdbTool::getInstance(),&AdbTool::initAdb,this,&MainWindow::setAdbPath);

    AdbTool::getInstance()->autoDetachAdb();

    //手动选择adb路径
    connect(ui->btn_select_adb_path,&QToolButton::clicked,this,[=](){
        QString str = QFileDialog::getOpenFileName(this,"open file","/","adb (*.exe);;");
        if(!str.isEmpty()){
            QString adb = str.toUtf8();
            setAdbPath(adb);
        }
    });
}



void MainWindow::setAdbPath(const QString& adb)
{
    qDebug() << "setAdbPath:" << adb;

    //设置adb路径
    AdbTool::getInstance()->setAdbPath(adb);
    ui->adb_edit->setText(adb);

    connect(AdbTool::getInstance(),&AdbTool::initDeviceList,this,&MainWindow::setCurDevice);

    //初始化Android设备
    AdbTool::getInstance()->getDeviceList();
}

void MainWindow::setCurDevice(const QStringList& dl)
{
    qDebug() << "setCurDevice:" << dl;
    if(dl.empty()){
        AdbTool::getInstance()->curDevice = "";
        //未连接
        ui->btn_icon->setText("暂无设备连接");
        ui->btn_icon->setIcon(QIcon(":/new/image/image/AndroidDeviceDisConnect.png"));
        return;
    }

    QString device = dl.at(0);
    AdbTool::getInstance()->setCurDevice(device);
    if(device.size() != 0){
        //设备正常
        auto title = QString("当前设备：\n%1").arg(device);
        ui->btn_icon->setText(title);
        ui->btn_icon->setIcon(QIcon(":/new/image/image/AndroidDeviceConnected.png.png"));
    }else{
        //未连接
        ui->btn_icon->setText("暂无设备连接");
        ui->btn_icon->setIcon(QIcon(":/new/image/image/AndroidDeviceDisConnect.png"));
    }
}


void MainWindow::on_btn_menu_clicked()
{
    qDebug() << "菜单按钮被点击";
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_file_clicked()
{
    qDebug() << "文件按钮被点击";
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btn_log_clicked()
{
    qDebug() << "日志按钮被点击";
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_btn_setting_clicked()
{
    qDebug() << "设置按钮被点击";
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btn_icon_clicked()
{
    qDebug() << "设备按钮被点击";
    if(AdbTool::getInstance()->getAdbPath().size() == 0){
        AdbTool::getInstance()->autoDetachAdb();
    }
    else
    {
        QStringList dl = AdbTool::getInstance()->getDeviceList();
        //展示设备列表
        DeviceListDialog *dl_dialog = new DeviceListDialog();
        dl_dialog->setList(dl);
        dl_dialog->show();
    }
}

void MainWindow::on_btn_install_apk_clicked()
{
    qDebug() << "安装apk";

}

void MainWindow::on_btn_input_text_clicked()
{
    qDebug() << "输入文本";
}

void MainWindow::on_btn_get_screenshot_clicked()
{
    qDebug() << "获取截图";
}

void MainWindow::on_btn_cur_activity_clicked()
{
    qDebug() << "当前activity";

}

void MainWindow::on_btn_clear_app_data_clicked()
{
    qDebug() << "清除应用数据";
}

void MainWindow::on_btn_get_apk_clicked()
{
    qDebug() << "获取apk保存到本地";
}

void MainWindow::on_btn_get_apk_path_clicked()
{
    qDebug() << "获取app安装路径";
}

void MainWindow::on_btn_restart_app_clicked()
{
    qDebug() << "重启app";
}

void MainWindow::on_btn_start_app_clicked()
{
    qDebug() << "打开app";
}

void MainWindow::on_btn_stop_app_clicked()
{
    qDebug() << "关闭app";
}

void MainWindow::on_btn_uninstall_app_clicked()
{
    qDebug() << "卸载app";
}

void MainWindow::on_btn_get_android_id_clicked()
{
    qDebug() << "获取Android ID";
}

void MainWindow::on_btn_get_android_version_clicked()
{
    qDebug() << "获取Android版本号";
}

void MainWindow::on_btn_get_ip_clicked()
{
    qDebug() << "获取ip地址";
}

void MainWindow::on_btn_get_mac_clicked()
{
    qDebug() << "获取mac地址";
}

void MainWindow::on_btn_get_sys_info_clicked()
{
    qDebug() << "获取系统信息";
}

void MainWindow::on_btn_restart_phone_clicked()
{
    qDebug() << "重启手机";
}

void MainWindow::on_btn_start_video_clicked()
{
    qDebug() << "开启录屏";
}

void MainWindow::on_btn_add_volum_clicked()
{
    qDebug() << "增加音量";
}

void MainWindow::on_btn_reduce_volum_clicked()
{
    qDebug() << "降低音量";
}

void MainWindow::on_btn_change_app_clicked()
{
    qDebug() << "切换app";
}

void MainWindow::on_btn_home_clicked()
{
    qDebug() << "home按键";
}

void MainWindow::on_btn_menu_2_clicked()
{
    qDebug() << "菜单按键";
}

void MainWindow::on_btn_power_clicked()
{
    qDebug() << "电源按键";
}

void MainWindow::on_btn_reback_clicked()
{
    qDebug() << "返回按键";
}


//void MainWindow::on_btn_select_adb_path_clicked()
//{
//    qDebug() << "选择ADB文件";
//}
