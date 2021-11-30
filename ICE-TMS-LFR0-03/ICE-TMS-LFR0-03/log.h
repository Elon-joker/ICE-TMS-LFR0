#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QWidget>

class Log
{
public:
    Log();
    static void warming(QString windowTitle, QString msg, QWidget *parent);
};

#endif // LOG_H
