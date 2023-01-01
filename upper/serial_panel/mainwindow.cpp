#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

// 数据位
static QMap<QString, QSerialPort::DataBits> dataBits {
    { "8", QSerialPort::DataBits::Data8 },
    { "7", QSerialPort::DataBits::Data7 },
    { "6", QSerialPort::DataBits::Data6 },
    { "5", QSerialPort::DataBits::Data5 },
};

// 停止位
static QMap<QString, QSerialPort::StopBits> stopBits {
    { "OneStop", QSerialPort::StopBits::OneStop },
    { "TwoStop", QSerialPort::StopBits::TwoStop },
    { "OneAndHalfStop", QSerialPort::StopBits::OneAndHalfStop },
};

// 校验模式
static QMap<QString, QSerialPort::Parity> parity {
    { "NoParity", QSerialPort::Parity::NoParity },
    { "OddParity", QSerialPort::Parity::OddParity },
    { "EvenParity", QSerialPort::Parity::EvenParity },
    { "MarkParity", QSerialPort::Parity::MarkParity },
    { "SpaceParity", QSerialPort::Parity::SpaceParity },
};

// 流控制
static QMap<QString, QSerialPort::FlowControl> flowControl {
    { "NoFlowControl", QSerialPort::FlowControl::NoFlowControl },
    { "HardwareControl", QSerialPort::FlowControl::HardwareControl },
    { "SoftwareControl", QSerialPort::FlowControl::SoftwareControl },
};

// 打开模式
static QMap<QString, QIODevice::OpenModeFlag> openMode {
    {"只读", QIODevice::ReadOnly },
    {"只写", QIODevice::WriteOnly },
    {"读写", QIODevice::OpenModeFlag::ReadWrite },
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialPort = new QSerialPort(this);

    connect(ui->openButton, &QPushButton::clicked, this , &MainWindow::onClickOpenButton);
    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::onReadData);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendData);
    connect(ui->clearButton, &QPushButton::clicked, this, [&] {
        ui->outputTextEdit->clear();
    });

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->serialPortComboBox->addItem(info.portName());
    }
    ui->rateComboBox->addItem("9600");
    ui->rateComboBox->addItem("115200");
    for (const auto &key : dataBits.keys()) {
        ui->dataBitsComboBox->addItem(key);
    }
    for (const auto &key : stopBits.keys()) {
        ui->stopBitsComboBox->addItem(key);
    }
    for (const auto &key : parity.keys()) {
        ui->parityComboBox->addItem(key);
    }
    for (const auto &key : flowControl.keys()) {
        ui->flowControlComboBox->addItem(key);
    }
    for (const auto &key : openMode.keys()) {
        ui->modeComboBox->addItem(key);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClickOpenButton(bool)
{
    auto state = ui->openButton->text();
    if (state.compare("打开") == 0) {
        ui->openButton->setText("关闭");
        serialPort->setPortName(ui->serialPortComboBox->currentText());
        serialPort->setBaudRate(ui->rateComboBox->currentText().toInt());
        serialPort->setDataBits(dataBits[ui->dataBitsComboBox->currentText()]);
        serialPort->setStopBits(stopBits[ui->stopBitsComboBox->currentText()]);
        serialPort->setParity(parity[ui->parityComboBox->currentText()]);
        serialPort->setFlowControl(flowControl[ui->flowControlComboBox->currentText()]);

        if (true == serialPort->open(openMode[ui->modeComboBox->currentText()])) {
            output("提示：打开成功！");
            ui->sendButton->setEnabled(true);
        } else {
            ui->openButton->setText("打开");
            output("提示：打开失败！");
        }
    } else {
        ui->openButton->setText("打开");
        ui->sendButton->setEnabled(false);
        serialPort->close();
        output("提示：已经关闭！");
    }
}

void MainWindow::onReadData()
{
    auto buffer = serialPort->readAll();
    if (!buffer.isEmpty()) {
        output("数据：");
        output(buffer);
    }
    buffer.clear();
}

void MainWindow::onSendData()
{
    serialPort->write(ui->sendEdit->text().toUtf8());
    output("已发送");
}

void MainWindow::output(const QString &text)
{
    auto now = QDateTime::currentDateTime();
    QString format("[%1] %2");
    QString result = format.arg(now.toString("yyyy-MM-dd hh:mm:ss"), text);
    ui->outputTextEdit->append(result);
}
