QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QRabbitMQ.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    QRabbitMQ.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 替换为实际的 QAMQP 和 rabbitmq-c 库的路径
INCLUDEPATH += D:/GitProject/djh/RabbitmqTest/include  # QAMQP 的 include 文件夹路径
# INCLUDEPATH += D:/Git/rabbitmq-c-master/include  # rabbitmq-c 的 include 文件夹路径

LIBS += -LD:/GitProject/djh/RabbitmqTest/lib_dll -lqamqp  # QAMQP 的 lib 文件路径
# LIBS += -LD:/GitProject/djh/RabbitmqTest/lib_dll -lrabbitmq.4  # RabbitMQ 的 lib 文件路径
