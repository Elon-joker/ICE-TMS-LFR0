#include "log.h"

#include <QMessageBox>
#include <QDebug>

Log::Log()
{

}

void Log::warming(QString windowTitle,QString msg,QWidget *parent)
{
    //设置弹窗，防止无串口输出异常
    QMessageBox msg0(parent);  //对话框设置父组件
    msg0.setWindowTitle(windowTitle);//对话框标题
    msg0.setText(msg);//对话框提示文本
    msg0.setIcon(QMessageBox::Information);//设置图标类型
    msg0.setStandardButtons(QMessageBox::Ok | QMessageBox:: Cancel);//对话框上包含的按钮
    if(msg0.exec() == QMessageBox::Ok)  // 判断是否退出弹窗
    {
        qDebug() << parent;   //数据处理
    }
}
