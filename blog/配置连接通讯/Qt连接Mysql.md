本文记录了作者安装Mysql,使用Navicat Premium 15连接数据库，使用Qt连接数据库的具体操作以及遇到的一些问题的解决方法。

版本：mysql-8.0.26-win64

​			navicat150_premiun_cs_x64

​			qt-opensource-windows-x86-5.9.0

### 1.安装Mysql及进行基本配置

1. 把压缩包解压，并将里面的bin文件目录增加到环境变量中

2. 以管理员身份运行cmd，切换到mysql的bin文件目录下

3. 输入以下语句完成mysql的创建

   ```mysql
   mysqld install                    //安装mysql
   mysqld --initialize --console     //初始化MySQL，会给一个初始密码
   net start mysql                   //开启mysql
   ```

### 2.使用Navicat Premium 15连接数据库

使用上面给出的初始密码连接Mysql，连接后会提示修改密码。

### 3.使用Qt连接数据库

**.pro文件中+= sql**，使用以下代码完成数据库的连接

```c++
#include "QDebug"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

        db.setHostName("localhost");
        db.setPort(3306);
        db.setDatabaseName("tyreinfo");
        db.setUserName("root");
        db.setPassword("123456");
        bool ok = db.open();
        if (ok){
            QMessageBox::information(this, "infor", "success");
        }
        else {
            QMessageBox::information(this, "infor", "open failed");
            qDebug()<<"error open database because" << db.lastError().text();
        }

}
```

### 4.问题及解决方法

问题1:

1. 现象：QMYSQL  driver not loaded
2. 原因：作者使用的qt5.9.0是32位，而Mysql8.0.26是64位，版本兼容问题。
3. 解决方法：下载32位的MySQL Connector，找到它安装目录下的libmysql.dll文件，将其复制到Qt安装目录下的bin文件夹下即可解决。

问题2:

1. 现象：QMYSQL  driver not loaded （qt6.2.4连接mysql8.0出现的问题）

2. 解决方案：到https://github.com/thecodemonkey86/qt_mysql_driver/releases?page=3找到对应qt版本，对应编译器（msvc/mingw）的文件下载。

3. 把`libmysql.dll、libcrypto-1_1-x64.dll、libssl-1_1-x64.dll`放到`C:\Qt\6.2.4\msvc2019_64\bin`文件夹下。

4. 把`qsqlmysql.dll、qsqlmysqld.dll`放到`C:\Qt\6.2.4\msvc2019_64\plugins\sqldrivers`即可解决

   

问题2：

1. 现象：Authentication plugin 'caching_sha2_password' cannot be loaded

2. 原因：Mysql8.0之后的版本默认加密规则是caching_sha2_password与Qt不兼容

3. 解决方法：以管理员身份运行cmd,登录MySQL；修改加密规则；更新用户的密码；刷新权限；重置密码。

   ```
   ALTER USER 'root'@'localhost' IDENTIFIED BY 'password' PASSWORD EXPIRE NEVER;
   ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';
   FLUSH PRIVILEGES; 
   alter user 'root'@'localhost' identified by '你的密码';
   ```

   ​		















