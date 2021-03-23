#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 选择目录
    connect(ui->runDirButton, &QPushButton::clicked, this, [&]() {
        auto dir = QFileDialog::getExistingDirectory(this, "选择项目目录", QDir::currentPath());
        if (!dir.isEmpty()) {
            ui->runDirEdit->setText(dir);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

