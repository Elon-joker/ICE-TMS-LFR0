#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "titlebar.h"
#include "log.h"

#include <QDebug>

#define HEAD 0xABCD
#define ROW 8
#define COLUMN 10

#define P 0.256/32768.0

#define P1 0.04161
#define P2 -0.1395
#define BATTERY_MAX 3.0
#define BATTERY_MIN 2.5

#define F(x,y) ( ((x)*1000-P2)/(P1)+(y) )
#define GS(x) ( (x)>COLUMN?(x)-COLUMN:0 )
#define CHECK(x) x

#define TEMPERTURE_MAX 500
#define TEMPERTURE_DELTA 10

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    TitleBar *pTitleBar = new TitleBar(this);
    installEventFilter(pTitleBar);

    resize(400, 300);
    setWindowTitle("ICE-TMS-LFR0");
    setWindowIcon(QIcon(":/image/log/image/motolog.png"));

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pTitleBar);
    pLayout->addStretch();
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    ui->title->setLayout(pLayout);
    // 申请空间储存数据:
    y.resize(ROW);
    x.resize(ROW);
    for(int i=0;i<ROW;i++){
        y[i].resize(COLUMN);
        x[i].resize(COLUMN);
    }
    //统一存储控件
    CP[0]=ui->customPlot0;
    CP[1]=ui->customPlot1;
    CP[2]=ui->customPlot2;
    CP[3]=ui->customPlot3;
    CP[4]=ui->customPlot4;
    CP[5]=ui->customPlot5;
    CP[6]=ui->customPlot6;
    CP[7]=ui->customPlot7;
    //初始化图表控件
    init();
    //创建数据文件夹
    QDir dir;
    summaryPath=qApp->applicationDirPath()+"/data/summary";
    sublistPath=qApp->applicationDirPath()+"/data/sublist";
    if (!dir.exists(summaryPath))
    {
      dir.mkpath(summaryPath);
    }
    if (!dir.exists(sublistPath))
    {
      dir.mkpath(sublistPath);
    }

    //链接信号与槽（即动作与响应的关联）
    //connect（谁发出信号，什么信号，谁响应事件，什么响应事件）；
    connect(ui->btnSerialSetting,SIGNAL(clicked()),this,SLOT(on_serialSetting()));//窗口设置
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @function  打开串口
 * @param     void
 * @return    void
 * @version   2019.11.3
 * @author    占建
 * @situation finish
 */
void MainWindow::on_OpenSerialButton_clicked()
{
    if(setting->getPortName()==tr("NO"))
    {
    //提示串口错误
      Log::warming("串口错误","未发现串口",this);
    }
    else {
        if(ui->OpenSerialButton->text() == tr("打开串口"))
        {
            serial = new QSerialPort;
            //设置串口名
            serial->setPortName(setting->getPortName());
            //打开串口
            serial->open(QIODevice::ReadWrite);
            //设置波特率
            switch (setting->getBaudRateIndex())
            {
            case 0:
                serial->setBaudRate(QSerialPort::Baud9600);
                break;
            case 1:
                serial->setBaudRate(QSerialPort::Baud38400);
              break;
            case 2:
                serial->setBaudRate(QSerialPort::Baud115200);
              break;
            default:
                break;
            }

            //设置数据位数
            switch (setting->getBitIndex())
            {
            case 8:
                serial->setDataBits(QSerialPort::Data8);//设置数据位8
                break;
            default:
                break;
            }
            //设置校验位
            switch (setting->getParityIndex())
            {
            case 0:
                serial->setParity(QSerialPort::NoParity);
                break;
            default:
                break;
            }
            //设置停止位
            switch (setting->getStopIndex())
            {
            case 0:
                serial->setStopBits(QSerialPort::OneStop);//停止位设置为1
                break;
            case 1:
                serial->setStopBits(QSerialPort::TwoStop);
                break;
            default:
                break;
            }
            //设置流控制
            serial->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控制

            ui->OpenSerialButton->setText(tr("关闭串口"));

            //连接信号槽
            QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::ReadData);
        }
        else
        {
            //关闭串口
            serial->clear();
            serial->close();
            serial->deleteLater();

            ui->OpenSerialButton->setText(tr("打开串口"));
            //将保存数据相关内容清空
            ui->btnSave->setText("开始记录");
            flageSaveData=false;
            sequence_last=-1;
            sequence_error_count=0;

        }

    }

}

/**
 * @function  读取串口信息
 * @param     void
 * @return    void
 * @version   2021.7.8
 * @author    占建
 * @situation TEST
 */
void MainWindow::ReadData()
{
   //接收数据
   sleep(50);//为防止数据未完全接收，增加延时等待接收完毕
   buf_hex=serial->readAll();//将串口里的可读信息全部读取
   qDebug()<<buf_hex;
   if(buf_hex.size()>30)
        dataProcess(buf_hex);
}

 /**
 * @function  画图函数
 * @param     void
 * @return    void
 * @version   2021.07.26
 * @author    占建
 * @situation finish
 *
 */
void MainWindow::showChart()
{
    //实现动态窗口范围
    for (int i=0;i<8;i++) {
        CP[i]->xAxis->setRange(GS(count),count);
    }
    //设置数据源和绘图画笔
    for(int i=0;i<8;i++){
        pGraph[i]->setData(x[i],y[i]);
        pGraph[i]->setPen(QPen(ColorLine1,2));
    }
   //绘制曲线
    for (int i=0;i<8;i++) {
        CP[i]->yAxis->rescale(true);
        CP[i]->graph(0)->rescaleAxes();
        CP[i]->replot();
    }
}

/**
 * @function  保存数据
 * @param     void
 * @return    void
 * @version   2021.7.3
 * @author    占建
 * @situation TODO 保存八通道数据-》用户选择路径
 */
void MainWindow::on_btnSave_clicked()
{
    if(ui->btnSave->text()==tr("开始记录")){
        if(ui->OpenSerialButton->text()==tr("关闭串口")){
            if(setting->getPortName()!=tr("NO")){
                ui->btnSave->setText("停止记录");
                //由于数据传输较慢，所以每一帧数据直接存储
                QString m;
                m.append(tr("%1\t").arg(ID&0xffffffff,0,16).toUpper());
                m.append(tr("%1\t").arg(sequence));
                for (int j=0;j<8;j++)
                {
                    m.append(tr("%1\t").arg(y[j][count%COLUMN]));
                }
                m.append(tr("%1\t").arg(static_cast<double>(Temperature)));
                m.append(tr("%1\t").arg(Voltage));
                //时间
                QDateTime current_date_time = QDateTime::currentDateTime();
                QString date=current_date_time.toString("yyyy-MM-dd hh:mm::ss");
                 m.append(date+"\n");
                 //保存总表
                summaryFile=QDateTime::currentDateTime().toString("yyyy-MM-dd")+".txt";
                saveData(m,summaryPath,summaryFile);
                //保存子表，开启子表保存
                sublistFile=QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".txt";
                saveData(m,sublistPath,sublistFile);
                flageSaveData=true;
            }
            else{
                Log::warming("串口错误","未找到串口",this);
            }
        }
        else{
            Log::warming("串口错误","串口未打开！",this);
        }

    }
    else{
        ui->btnSave->setText("开始记录");
        flageSaveData=false;
    }
}

/**
 * @function  初始化图表控件
 * @param     void
 * @return    void
 * @version   2021.7.17
 * @author    占建
 * @situation  finish
 */
void MainWindow::init()
{
    //设置基础配置
    for(int i=0;i<8;i++){
        CP[i]->xAxis->setLabel("t");
        CP[i]->yAxis->setLabel("℃");
        pGraph[i]=CP[i]->addGraph();
        //设置基本坐标轴（左侧Y轴和下方X轴）可拖动、可缩放、曲线可选、legend可选、设置伸缩比例，使所有图例可见legend->setVisible(false)
        CP[i]->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
        CP[i]->axisRect()->setRangeDrag(Qt::Horizontal);  //设置允许在某一方向上拽托
        CP[i]->legend->setVisible(false);
        //设置坐标系 自动缩放以正常显示所有的数据
        CP[i]->yAxis->rescale(true);
        CP[i]->graph(0)->rescaleAxes();
    }

    m_title[0] = new QCPTextElement(CP[0], "通道一");
    m_title[1] = new QCPTextElement(CP[1], "通道二");
    m_title[2] = new QCPTextElement(CP[2], "通道三");
    m_title[3] = new QCPTextElement(CP[3], "通道四");
    m_title[4] = new QCPTextElement(CP[4], "通道五");
    m_title[5] = new QCPTextElement(CP[5], "通道六");
    m_title[6] = new QCPTextElement(CP[6], "通道七");
    m_title[7] = new QCPTextElement(CP[7], "通道八");

    for (int i=0;i<8;i++) {
        CP[i]->plotLayout()->insertRow(0);
        m_title[i]->setTextColor(ColorChartText);
        CP[i]->plotLayout()->addElement(0, 0, m_title[i]);
        //颜色设定
        CP[i]->setBackground(ColorChartBg);
        CP[i]->xAxis->setBasePen(QPen(ColorChartGrid,4));
        CP[i]->yAxis->setBasePen(QPen(ColorChartGrid,4));
        CP[i]->xAxis->grid()->setPen(QPen(ColorChartGrid, 1, Qt::PenStyle::DashLine));//网格白色虚线
        CP[i]->yAxis->grid()->setPen(QPen(ColorChartGrid, 1, Qt::PenStyle::DashLine));
        CP[i]->xAxis->grid()->setSubGridPen(QPen(ColorChartGrid, 1, Qt::DotLine));//网格浅色点线
        CP[i]->yAxis->grid()->setSubGridPen(QPen(ColorChartGrid, 1, Qt::DotLine));
        CP[i]->xAxis->grid()->setSubGridVisible(true);//显示x轴子网格线
        CP[i]->yAxis->grid()->setSubGridVisible(true);
        CP[i]->xAxis->setLabelColor(ColorChartText);
        CP[i]->yAxis->setLabelColor(ColorChartText);
        CP[i]->xAxis->setTickLabelColor(ColorChartText);
        CP[i]->yAxis->setTickLabelColor(ColorChartText);
    }

    Voltage=BATTERY_MIN;

    ui->lbMsg->setText("最高温度:\t*\t通道数:\t*\t\t最低温度:\t*\t通道数:\t*");
    UpdateBattery();
}

void MainWindow::on_serialSetting()
{
    setting->setWindowModality(Qt::ApplicationModal);
    setting->show();
    qDebug()<<setting->getBaudRateIndex();
}

/* ******************************************************************************
 * @author 占建
 * @date   2021-08-13
 * *****************************************************************************/
/**
 * @brief MainWindow::savaData
 * @param data
 * @param path
 * @param fileName
 */
void MainWindow::saveData(QString data,QString path,QString fileName)
{
    QFile file(path+"/"+fileName);

   if(!file.open(QIODevice::Append|QIODevice::Text))
   {
       QMessageBox::critical(nullptr,"提示","无法创建文件");
       return;
   }

   std::string str = data.toStdString();
   const char* ch = str.c_str();

   file.write(ch);//将ch存进test.txt文件夹里面
    file.flush();
    file.close();
}

/* ******************************************************************************
 * @author 占建
 * @date   2021-09-09
 * *****************************************************************************/
/**
 * @brief MainWindow::UpdateBattery
 *        用于更新电池电量显示
 */
void MainWindow::UpdateBattery()
{
    QProgressBar *pProgressBar = ui->pbBattery;
    pProgressBar->setOrientation(Qt::Horizontal);  // 水平方向
    int batteryValue=static_cast<int>(((Voltage>3.0?3.0:Voltage)-BATTERY_MIN)*1000/(BATTERY_MAX-BATTERY_MIN));
    if(batteryValue/10>=60)
        pProgressBar->setStyleSheet(
                    "QProgressBar {border: 2px solid grey;border-radius: 5px;background-color: #FFFFFF;}"
                    "QProgressBar::chunk{background-color: #00FF00;width: 20px;}");
    else
        if(batteryValue/10>=30)
            pProgressBar->setStyleSheet(
                        "QProgressBar {border: 2px solid grey;border-radius: 5px;background-color: #FFFFFF;}"
                        "QProgressBar::chunk{background-color: #FFBF00;width: 20px;}");
        else
         pProgressBar->setStyleSheet(
                        "QProgressBar {border: 2px solid grey;border-radius: 5px;background-color: #FFFFFF;}"
                        "QProgressBar::chunk{background-color: #FF0000;width: 20px;}");
    if(ui->OpenSerialButton->text() == tr("关闭串口")&&Voltage<=BATTERY_MIN)
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();

        ui->OpenSerialButton->setText(tr("打开串口"));
        //设置弹窗，防止无串口输出异常
        QMessageBox msg0(this);  //对话框设置父组件
        msg0.setWindowTitle("警告！");//对话框标题
        msg0.setText("请更换电池");//对话框提示文本
        msg0.setIcon(QMessageBox::Warning);//设置图标类型
        msg0.setStandardButtons(QMessageBox::Ok );//对话框上包含的按钮

        if(msg0.exec() == QMessageBox::Ok)  // 判断是否退出弹窗
        {
            qDebug()<<"Ok is clicked!";
        }
    }
    pProgressBar->setMinimum(0);  // 最小值
    pProgressBar->setMaximum(50);  // 最大值
    pProgressBar->setValue(batteryValue/20);  // 当前进度
    double dProgress = batteryValue/10.0;
    pProgressBar->setFormat(tr("%1%").arg(dProgress));
    pProgressBar->setAlignment(Qt::AlignVCenter);  // 对齐方式
}

bool MainWindow::checkData()
{
    if(count<10)//前10帧内的数据不做校验
        return true;
    for (int i=0;i<8;i++)
    {
        if(y[i][count]>TEMPERTURE_MAX)
            return false;
        if( (y[i][count]-y[i][count-1])>TEMPERTURE_DELTA||
            (y[i][count]-y[i][count-1])<-TEMPERTURE_DELTA )
            return false;
    }

    return true;
}

void MainWindow::dataProcess(QByteArray data)
{
    //协议解析
    //解析出数据存储到对应位置
   sequence=static_cast<int>( (data[2]&0xff)<<8 | (data[3]&0xff) );
   ID=static_cast<unsigned int>( (data[7]&0xff)<<24|(data[6]&0xff)<<16|(data[5]&0xff)<<8|(data[4]&0xff) );
   Temperature=static_cast<float>(data[24]&0xff)-55.0f;
   Voltage=static_cast<double>(data[25]&0xff)/100+1.22;
   CRC=static_cast<char>(data[26]&0xff);

   //动态存储数据
   int maxIndex=0,minIndex=0;
   double maxT=0.0,minT=INT_MAX;
   //数据转换
   for(int i=0;i<8;i++){
       double data_temp=CHECK(static_cast<int16_t>( (data[8+i*2]&0xff)<<8|(data[9+i*2]&0xff) ))*P;

       if(count < COLUMN)
       {
           y[i][count]=F(data_temp,static_cast<double>(Temperature));
           x[i][count]=count;
       }
       else
       {
           //容器数据现在是正好COLUMN个  把第一个出栈  把第COLUMN+1个入栈  正好还是COLUMN个数据
           y[i].removeFirst();
           x[i].removeFirst();
           //入栈
           y[i].append(F(data_temp,static_cast<double>(Temperature)));
           x[i].append(count);
       }

       if(maxT<y[i][count%COLUMN])
       {
           maxT=y[i][count%COLUMN];
           maxIndex=i;
       }
       if(minT>y[i][count%COLUMN])
       {
           minT=y[i][count%COLUMN];
           minIndex=i;
       }

   }

   ui->lbMsg->setText(tr("最高温度:\t%1\t通道数:\t%2\t\t最低温度:\t%3\t通道数 %4")
                      .arg(maxT).arg(maxIndex+1).arg(minT).arg(minIndex+1));

   if(flageSaveData)
   {
       //由于数据传输较慢，所以每一帧数据直接存储
       QString m;
       m.append(tr("%1\t").arg(count));
       m.append(tr("%1\t").arg(ID&0xffffffff,0,16).toUpper());
       m.append(tr("%1\t").arg(sequence));
       for (int j=0;j<8;j++)
       {
           m.append(tr("%1\t").arg(y[j][count%COLUMN]));
       }
       m.append(tr("%1\t").arg(static_cast<double>(Temperature)));
       m.append(tr("%1\t").arg(Voltage));
       //时间
       QDateTime current_date_time = QDateTime::currentDateTime();
        m.append(current_date_time.toString("yyyy-MM-dd hh:mm::ss\n"));
       //检测丢帧
       if(sequence_last!=-1)//起始标号
       {
           sequence_error_count+=sequence-sequence_last-1;
           sequence_last=sequence;
       }
       else
       {
           sequence_last=sequence;
       }
       if(count%100==0)
       {
           m.append(tr("%1\n").arg(sequence_error_count*1.0/100));
           sequence_error_count=0;
       }

       saveData(m,sublistPath,sublistFile);
   }

   //得到一组数据后即绘制一次图像
   showChart();

   ui->ID->setText(tr("%1").arg(ID&0xffffffff,0,16).toUpper());
   ui->temp->setText(tr("%1").arg(static_cast<double>(Temperature)));
   ui->voltage->setText(tr("%1").arg(static_cast<double>(Voltage)));

   //更新电量
   UpdateBattery();

   count++;
}

/**
 * @brief MainWindow::sleep
 *        简单的延时函数
 * @param msec 延时时间，单位毫秒
 */
void MainWindow::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        //这条语句能够使程序在while等待期间，去处理一下本线程的事件循环，处理事件循环最多100ms必须返回本语句，
        //如果提前处理完毕，则立即返回这条语句。这也就导致了该Delay_MSec函数的定时误差可能高达100ms。
    }

}

