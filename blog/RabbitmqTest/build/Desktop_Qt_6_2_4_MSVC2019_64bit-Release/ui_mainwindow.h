/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ip;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *port;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *RoutingKey;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *BindingKey;
    QPushButton *btn_connect;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *sendLineEdit;
    QPushButton *btn_send;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(599, 493);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        ip = new QLineEdit(centralwidget);
        ip->setObjectName(QString::fromUtf8("ip"));

        horizontalLayout->addWidget(ip);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        port = new QLineEdit(centralwidget);
        port->setObjectName(QString::fromUtf8("port"));

        horizontalLayout_2->addWidget(port);


        gridLayout->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        RoutingKey = new QLineEdit(centralwidget);
        RoutingKey->setObjectName(QString::fromUtf8("RoutingKey"));

        horizontalLayout_3->addWidget(RoutingKey);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        BindingKey = new QLineEdit(centralwidget);
        BindingKey->setObjectName(QString::fromUtf8("BindingKey"));

        horizontalLayout_4->addWidget(BindingKey);


        gridLayout->addLayout(horizontalLayout_4, 1, 1, 1, 1);


        horizontalLayout_6->addLayout(gridLayout);

        btn_connect = new QPushButton(centralwidget);
        btn_connect->setObjectName(QString::fromUtf8("btn_connect"));

        horizontalLayout_6->addWidget(btn_connect);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        sendLineEdit = new QLineEdit(centralwidget);
        sendLineEdit->setObjectName(QString::fromUtf8("sendLineEdit"));

        horizontalLayout_5->addWidget(sendLineEdit);

        btn_send = new QPushButton(centralwidget);
        btn_send->setObjectName(QString::fromUtf8("btn_send"));

        horizontalLayout_5->addWidget(btn_send);


        verticalLayout->addLayout(horizontalLayout_5);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        plainTextEdit = new QPlainTextEdit(groupBox);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        gridLayout_2->addWidget(plainTextEdit, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 599, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ip:", nullptr));
        ip->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "port:", nullptr));
        port->setText(QCoreApplication::translate("MainWindow", "5672", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "RoutingKey:", nullptr));
        RoutingKey->setText(QCoreApplication::translate("MainWindow", "newExchange", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "BindingKey:", nullptr));
        BindingKey->setText(QCoreApplication::translate("MainWindow", "newExchange", nullptr));
        btn_connect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        btn_send->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
