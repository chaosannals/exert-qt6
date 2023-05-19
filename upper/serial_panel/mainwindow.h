#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onClickOpenButton(bool);
    void onReadData();
    void onSendData();
private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;

    void output(const QString &text);
    template<typename ...A>
    void output(const QString &format, A ...args)
    {
        QString result = format.arg(args...);
        output(result);
    }
};
#endif // MAINWINDOW_H
