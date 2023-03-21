#include "messagedialog.h"
#include "ui_messagedialog.h"
#include <QLabel>

MessageDialog::MessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);
}

MessageDialog::~MessageDialog()
{
    delete ui;
}

void MessageDialog::setContent(const QString& str)
{
    QLabel *scrollArealabel = new QLabel;
    // 设置标签的最小尺寸，非常重要，否则有可能无法正常显示滚动条
    scrollArealabel->setMinimumSize(500,500);
    scrollArealabel->setText(str);
    ui->scrollArea->setWidget(scrollArealabel);
}
