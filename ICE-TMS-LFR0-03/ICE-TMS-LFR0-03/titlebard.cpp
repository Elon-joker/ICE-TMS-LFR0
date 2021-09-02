#include "titlebard.h"

TitleBarD::TitleBarD(QWidget *parent)
    : TitleBar(parent)
{

}

TitleBarD::~TitleBarD()
{

}

void TitleBarD::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

}

void TitleBarD::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

bool TitleBarD::eventFilter(QObject *obj, QEvent *event)
{
     TitleBar::eventFilter(obj,event);
     return QWidget::eventFilter(obj, event);
}
