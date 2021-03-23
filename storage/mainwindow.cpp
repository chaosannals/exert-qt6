#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TesterModel::init();

    // 表格模型
    tableModel = new QStandardItemModel();
    tableModel->setHorizontalHeaderItem(0, new QStandardItem("账号"));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem("昵称"));
    tableModel->setHorizontalHeaderItem(2, new QStandardItem("密码"));
    tableModel->setHorizontalHeaderItem(3, new QStandardItem("日期"));
    ui->testerTable->setModel(tableModel);

    // 查询
    connect(ui->findButton, &QPushButton::clicked, this, [&]() {
        auto testers = TesterModel::find(ui->findEdit->text());
        output("find");
        tableModel->clear();
        for (auto t : testers) {
            tableModel->appendRow(QList{
                                 new QStandardItem(t.getAccount()),
                                 new QStandardItem(t.getNickname()),
                                 new QStandardItem(t.getPassword()),
                                 new QStandardItem(t.getCreatedAt().toString("yyyy-MM-dd")),
                             });
        }
    });

    // 保存
    connect(ui->saveButton, &QPushButton::clicked, this, [&]() {
        QString text = ui->idShowLabel->text();
        int id = text.isEmpty() ? 0 : text.toInt();
        TesterModel a(id);
        a.setAccount(ui->accountEdit->text());
        a.setCreatedAt(ui->createdAtEdit->dateTime());
        a.setNickName(ui->nicknameEdit->text());
        a.setPassword(ui->passwordEdit->text());
        a.save();
        output(id == 0 ? "insert": "update");
        ui->idShowLabel->setText(QString("%1").arg(a.getId()));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tableModel;
}

void MainWindow::output(const QString &text) {
    auto now = QDateTime::currentDateTime();
    auto date = now.toString("yyyy-MM-dd hh:mm:ss.zzz");
    auto content = QString("[%1] %2 \r\n").arg(date, text);
    ui->outputBrowser->textCursor().insertText(content);
}

