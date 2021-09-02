#ifndef TITLEBARD_H
#define TITLEBARD_H

#include "titlebar.h"

class TitleBarD: public TitleBar
{
    Q_OBJECT
public:
    explicit TitleBarD(QWidget *parent = nullptr);
    ~TitleBarD();

protected:
    // 双击标题栏进行界面的最大化/还原
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    // 进行鼠界面的拖动
    virtual void mousePressEvent(QMouseEvent *event);

    // 设置界面标题与图标
    virtual bool eventFilter(QObject *obj, QEvent *event);
};

#endif // TITLEBARD_H
