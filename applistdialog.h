#ifndef APPLISTDIALOG_H
#define APPLISTDIALOG_H

#include <QDialog>

typedef void (*fp)(const QString &app);

namespace Ui {
class AppListDialog;
}

class AppListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AppListDialog(QWidget *parent = nullptr);
    ~AppListDialog();

    QString curApp = "";

    fp f;

    void setList(const QStringList& list);

    void setFunction(const fp& f);


private slots:
    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::AppListDialog *ui;
};

#endif // APPLISTDIALOG_H
