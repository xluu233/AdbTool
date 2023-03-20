#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void initMenu();

    //初始化设置页面
    void initSetting();


private slots:
    void on_btn_menu_clicked();

    void on_btn_file_clicked();

    void on_btn_log_clicked();

    void on_btn_setting_clicked();

    void on_btn_icon_clicked();

    void on_btn_install_apk_clicked();

    void on_btn_input_text_clicked();

    void on_btn_get_screenshot_clicked();

    void on_btn_cur_activity_clicked();

    void on_btn_clear_app_data_clicked();

    void on_btn_get_apk_clicked();

    void on_btn_get_apk_path_clicked();

    void on_btn_restart_app_clicked();

    void on_btn_start_app_clicked();

    void on_btn_stop_app_clicked();

    void on_btn_uninstall_app_clicked();

    void on_btn_get_android_id_clicked();

    void on_btn_get_android_version_clicked();

    void on_btn_get_ip_clicked();

    void on_btn_get_mac_clicked();

    void on_btn_get_sys_info_clicked();

    void on_btn_restart_phone_clicked();

    void on_btn_start_video_clicked();

    void on_btn_add_volum_clicked();

    void on_btn_change_app_clicked();

    void on_btn_home_clicked();

    void on_btn_menu_2_clicked();

    void on_btn_power_clicked();

    void on_btn_reback_clicked();

    void on_btn_reduce_volum_clicked();

//    void on_btn_select_adb_path_clicked();

private:
    Ui::MainWindow *ui;

    void setAdbPath(QString adb);

};
#endif // MAINWINDOW_H
