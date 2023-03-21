#include "applistdialog.h"
#include "ui_applistdialog.h"
#include <QStringListModel>
#include <QDebug>

AppListDialog::AppListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppListDialog)
{
    ui->setupUi(this);
}

AppListDialog::~AppListDialog()
{
    delete ui;
}

void AppListDialog::setList(const QStringList &list)
{
    QStringListModel *model = new QStringListModel(list);
    ui->listView->setModel(model);

}

void AppListDialog::setFunction(const fp& f)
{
    this->f = f;
}

void AppListDialog::on_listView_clicked(const QModelIndex &index)
{
    auto model = qobject_cast<QStringListModel *>(ui->listView->model());
    curApp = model->stringList().at(index.row());
    qDebug() << "选择app:" << curApp;
//    this->f(curApp);
//    close();
}
