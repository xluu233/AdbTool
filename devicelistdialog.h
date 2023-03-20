#ifndef DEVICELISTDIALOG_H
#define DEVICELISTDIALOG_H

#include <QDialog>

namespace Ui {
class DeviceListDialog;
}

class DeviceListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceListDialog(QWidget *parent = nullptr);
    ~DeviceListDialog();

    void setList(const QStringList& dl);
private slots:
//    void on_listview_dl_doubleClicked(const QModelIndex &index);

    void on_listview_dl_clicked(const QModelIndex &index);

private:
    Ui::DeviceListDialog *ui;
};

#endif // DEVICELISTDIALOG_H
