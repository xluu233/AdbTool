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

//    ui->scrollArea->setWidget();


//    QList<QString> titles;
//    titles.append("快捷功能");
//    titles.append("文件管理");
//    titles.append("LogCat");
//    titles.append("设置");

//    QList<QString> icons;
//    icons.append(":/new/image/image/main_menu.png");
//    icons.append(":/new/image/image/main_file.png");
//    icons.append(":/new/image/image/main_log.png");
//    icons.append(":/new/image/image/main_setting.png");

//    QVBoxLayout *vlayout_main = new QVBoxLayout;
//    QLabel *title_main = new QLabel;
//    title_main->setText("▎常用功能");
//    title_main->setMargin(10);
//    title_main->setStyleSheet("QLabel{color:rgb(255,228,196);font-weight:bold}");
//    vlayout_main->addWidget(title_main);

//    QGridLayout *gridLayout = new QGridLayout;
//    gridLayout->addWidget(&getListBtn(":/new/image/image/main_menu.png","安装应用"),0,0);
//    gridLayout->addWidget(&getListBtn(":/new/image/image/main_menu.png","安装应用2"),0,1);
//    gridLayout->addWidget(&getListBtn(":/new/image/image/main_menu.png","安装应用3"),0,2);
//    gridLayout->setColumnMinimumWidth(0,300);
//    gridLayout->setVerticalSpacing(100);
//    gridLayout->setAlignment(Qt::AlignCenter);
//    gridLayout->setRowStretch(0,1);



//    gridLayout->setRowStretch(3,3);
//    gridLayout->setColumnStretch(3,3);
//    vlayout_main->addLayout(gridLayout);

    //    ui->vlayout_menu->addLayout(vlayout_main);
}

void MainWindow::initSetting()
{
    ui->adb_edit->setPlaceholderText("请输入或选择ADB路径");


    QString adb = AdbTool::getInstance()->autoDetachAdb();
    setAdbPath(adb);

    //手动选择adb路径
    connect(ui->btn_select_adb_path,&QToolButton::clicked,this,[=](){
        QString str = QFileDialog::getOpenFileName(this,"open file","/","adb (*.exe);;");
        if(!str.isEmpty()){
            QString adb = str.toUtf8();
            setAdbPath(adb);
        }
    });
}


void MainWindow::setAdbPath(QString adb)
{
    AdbTool::getInstance()->setAdbPath(adb);
    ui->adb_edit->setText(adb);
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
