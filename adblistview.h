#ifndef ADBLISTVIEW_H
#define ADBLISTVIEW_H

#include <QObject>
#include <QListView>

class AdbListView : public QListView
{
    Q_OBJECT
public:
    explicit AdbListView(QWidget *parent = nullptr);

    void initItems(QStringList &titles,QStringList &icons);


signals:

};

#endif // ADBLISTVIEW_H
