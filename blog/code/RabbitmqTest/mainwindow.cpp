#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include "qamqpqueue.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_rabbitClient = new QRabbitMQ(this);
    connect(m_rabbitClient, SIGNAL(msgSig(QString)), this, SLOT(showMsg(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMsg(QString msg)
{
    ui->plainTextEdit->appendPlainText(msg);
}

void MainWindow::on_btn_connect_clicked()
{
    m_rabbitClient->setServerParam(ui->ip->text(), ui->port->text().toInt());
    m_rabbitClient->setRabbitClientParam(ui->RoutingKey->text(), ui->BindingKey->text().split(";"));
    m_rabbitClient->start();
}

void MainWindow::on_btn_send_clicked()
{
    m_rabbitClient->sendMsg(ui->sendLineEdit->text());
    ui->plainTextEdit->appendPlainText("Send: " + ui->sendLineEdit->text());
}
