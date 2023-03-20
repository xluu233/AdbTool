#include "devicelistdialog.h"
#include "ui_devicelistdialog.h"
#include <QStringListModel>
#include <QDebug>
#include "adbtool.h"

DeviceListDialog::DeviceListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceListDialog)
{
    ui->setupUi(this);
}

DeviceListDialog::~DeviceListDialog()
{
    delete ui;
}

void DeviceListDialog::setList(const QStringList &dl)
{
    qDebug() << "setList" << dl;
    QStringListModel *model = new QStringListModel(dl);
    ui->listview_dl->setModel(model);
//    ui->listview_dl->show();
}


void DeviceListDialog::on_listview_dl_clicked(const QModelIndex &index)
{
    auto model = qobject_cast<QStringListModel *>(ui->listview_dl->model());
    QString device = model->stringList().at(index.row());
    qDebug() << "选择设备:" << device;
    AdbTool::getInstance()->setCurDevice(device);
    this->close();
}
