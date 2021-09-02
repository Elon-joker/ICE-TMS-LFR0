#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPointer>

#include "qcustomplot.h"
#include "serialsetting.h"
#include "color.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVector<QVector<double>> y,x; // initialize with entries (0..5000)x8
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QTimer *timer;

    //data filePath
    QString summaryPath;
    QString sublistPath;
    QString summaryFile;
    QString sublistFile;
    int count=0;
    QByteArray buf;
    char* buf_hex;

    //serial setting window
    serialSetting *setting=new serialSetting();

    int sequence;
    unsigned int ID;
    //检测丢帧率
    int sequence_last=-1;
    int sequence_error_count=0;
    QVector<double> temperature;
    double Temperature;
    double Voltage=0.0;
    char CRC;

    QCPGraph *pGraph[8];
    QCustomPlot *CP[8];
    QCPTextElement *m_title[8];


    bool flageSaveData=false;

    void init();
    void showChart();
    void saveData(QString data,QString path,QString fileName);
    bool checkData();
private slots:
    void on_OpenSerialButton_clicked();

    void ReadData();

    void on_saveButton_clicked();

    void on_serialSetting();

    void UpdateBattery();
};
#endif // MAINWINDOW_H
