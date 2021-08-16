#ifndef SERIALSETTING_H
#define SERIALSETTING_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>

namespace Ui {
class serialSetting;
}

class serialSetting : public QDialog
{
    Q_OBJECT

public:
    explicit serialSetting(QWidget *parent = nullptr);
    ~serialSetting();


    int getBaudRateIndex() const;
    void setBaudRateIndex(int value);

    QString getPortName() const;
    void setPortName(const QString &value);

    int getBitIndex() const;
    void setBitIndex(int value);

    int getParityIndex() const;
    void setParityIndex(int value);

    int getStopIndex() const;
    void setStopIndex(int value);

private:
    Ui::serialSetting *ui;
    QTimer *timer;
    QStringList oldPortStringList;

    int  baudRateIndex=0;
    QString portName;
    int  bitIndex=8;
    int  ParityIndex=0;
    int  stopIndex=1;

    void UpdatePort();
private slots:

    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // SERIALSETTING_H
