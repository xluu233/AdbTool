#ifndef DESIGNTOOL_H
#define DESIGNTOOL_H

#include <QString>
#include <QFileDialog>

class DesignTool
{
public:
    DesignTool();

    //选择adb路径
    QString selectAdbFile();

};

#endif // DESIGNTOOL_H
