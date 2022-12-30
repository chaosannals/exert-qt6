#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    serialPort = new QSerialPort(this);
    ui->setupUi(this);
    connect(ui->openButton, &QPushButton::clicked, this , &MainWindow::onClickOpenButton);

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->serialPortComboBox->addItem(info.portName());
    }
    ui->rateComboBox->addItem("9600");
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
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setParity(QSerialPort::NoParity);
        if (true == serialPort->open(QIODevice::ReadWrite)) {
            ui->outputTextEdit->append("提示：打开成功！");
        } else {
            ui->outputTextEdit->append("提示：打开失败！");
        }
    } else {
        ui->openButton->setText("打开");
        serialPort->close();
        ui->outputTextEdit->append("提示：已经关闭！");
    }
}
