#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QRabbitMQ.h"
QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showMsg(QString msg);
    void on_btn_connect_clicked();

    void on_btn_send_clicked();

private:
    Ui::MainWindow *ui;
    QRabbitMQ *m_rabbitClient;
};
#endif  // MAINWINDOW_H
