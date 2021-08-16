#include "serialsetting.h"
#include "ui_serialsetting.h"

serialSetting::serialSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serialSetting)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    TitleBar *pTitleBar = new TitleBar(this);
    installEventFilter(pTitleBar);

    resize(400, 300);
    setWindowTitle("串口设置");
    setWindowIcon(QIcon(":/image/log/image/motolog.png"));

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pTitleBar);
    pLayout->addStretch();
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    ui->title->setLayout(pLayout);
    //定时器，用于更新串口
    timer = new QTimer();
    timer->start(1000); //一次检测
    QStringList newPortStringList;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        newPortStringList += info.portName();
    }
    //搜索串口
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite)){
            ui->PortBox->addItem(serial.portName());
            serial.close();
            }
    }
    //更新串口号
    if(newPortStringList.size() != oldPortStringList.size())
    {
        oldPortStringList = newPortStringList;
        ui->PortBox->clear();
        ui->PortBox->addItems(oldPortStringList);
    }

    //设置波特率下拉菜单默认显示第3项
    ui->BaudBox->setCurrentIndex(2);
    //绑定槽函数
    connect(timer,&QTimer::timeout,this,&serialSetting::UpdatePort);//更新端口号
    connect(ui->ok,SIGNAL(clicked()),this,SLOT(on_ok_clicked()));
}

serialSetting::~serialSetting()
{
    delete ui;
}

int serialSetting::getBaudRateIndex() const
{
    return baudRateIndex;
}

void serialSetting::setBaudRateIndex(int value)
{
    baudRateIndex = value;
}

QString serialSetting::getPortName() const
{
    return portName;
}

void serialSetting::setPortName(const QString &value)
{
    portName = value;
}

int serialSetting::getBitIndex() const
{
    return bitIndex;
}

void serialSetting::setBitIndex(int value)
{
    bitIndex = value;
}

int serialSetting::getParityIndex() const
{
    return ParityIndex;
}

void serialSetting::setParityIndex(int value)
{
    ParityIndex = value;
}

int serialSetting::getStopIndex() const
{
    return stopIndex;
}

void serialSetting::setStopIndex(int value)
{
    stopIndex = value;
}


void serialSetting::on_ok_clicked()
{
    setBaudRateIndex(ui->BaudBox->currentIndex());
    setPortName(ui->PortBox->currentText());
    setBitIndex(ui->BitBox->currentIndex());
    setParityIndex(ui->ParityBox->currentIndex());
    setStopIndex(ui->StopBox->currentIndex());
    this->close();
}

void serialSetting::on_cancel_clicked()
{
    this->close();
}

/**
 * @function  实时更新串口，检测是否有串口插入，拔出
 * @param     void
 * @return    void
 * @version   2019.11.3
 * @author    占建
 * @situation finish
 */
void serialSetting::UpdatePort()
{
    QStringList newPortStringList;//存放新串口号，用于比较检测和更新
    const auto infos = QSerialPortInfo::availablePorts();

    //自动搜索所有串口
    for (const QSerialPortInfo &info : infos)
    {
        newPortStringList += info.portName();
    }
    //更新串口号
    if(newPortStringList.size() != oldPortStringList.size())
    {
        oldPortStringList = newPortStringList;
         ui->PortBox->clear();
         ui->PortBox->addItems(oldPortStringList);
    }
}

