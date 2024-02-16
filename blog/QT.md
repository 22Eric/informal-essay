### 1.资源文件

2.1将图片文件拷贝到项目文件夹下

2.2右键项目.添加新文件.Qt.Qt resource File.给资源文件起名

2.3生成   .qrc  文件

2.4open in editor 编辑资源文件

2.5添加前缀，添加资源

2.6使用": +前缀名+文件名"

```c++
//action添加对应的图片，使用相对路径，格式如下
ui->actionnew->setIcon(QIcon(":/img/xinjian.png"));
ui->actionopen->setIcon(QIcon(":/img/dakai.png"));
```

## 2.创建对话框

```c++
//创建模态对话框(对话框必须先完成)
connect(ui->actionnew,&QAction::triggered,this,
        [](){QDialog dil;
             dil.resize(300,150);
             dil.exec();  //阻塞
            });


//创建非模态对话框1(多次点击新建时多次创建新的对话框)
connect(ui->actionnew,&QAction::triggered,this,
        [](){QDialog *pdil = new QDialog;
             pdil->show();
             pdil->setAttribute(Qt::WA_DeleteOnClose);    //Delete on close
            } );

//创建非模态对话框2(只创建一次对话框，点击X之后只是将对话框隐藏)
QDialog *pdil = new QDialog;
connect(ui->actionnew,&QAction::triggered,this,
        [=](){pdil->show();});

```

### 3.标准对话框

```c++
//标准对话框

    //QMessageBox::critical(this,"错误对话框","错误");     //错误对话框
    //QMessageBox::information(this,"信息对话框","信息");  //信息对话框
 	//QMessageBox::warning(this,"警告对话框","警告");     //警告对话框
 	
    //提问对话框
    //参数1：parent
    //参数2：title
    //参数3：提示内容
    //参数4：按键类型
    //参数5：默认关联回车按键
    //返回值类型：按键类型
    QMessageBox::question(this,"提问对话框","提问",QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Cancel);
```

ps:按键类型：StandardButton类型

### 4.自定义空间封装（举例）

4.1点击添加新文件，选中qt设计师界面类，选择界面类型，更改默认的类名（这里用的是smallWiget）。

4.2添加两个控件，Spin Box和Horizontal，下面我们会对这两个控件联动并封装起来。

4.3在主界面拖拽一个Widget控件，并右击将它提升为smallWiget。（封装）

4.4在smallWige的cpp文件中将两个控件的一些事件connect起来。（联动）

```c++
//因为valueChanged这个singal有重载函数，因此做信号时需要指出是使用的哪个函数
//使用函数指针指出
void (QSpinBox:: *pchange)(int) = &QSpinBox::valueChanged;

connect(ui->spinBox,pchange,ui->horizontalSlider,&QSlider::setValue);
connect(ui->horizontalSlider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);
```

### 5.定时器

包含在头文件QTimer中。

```c++
QTimer *timer = new QTimer(this);
timer->start(500);   //一开始的状态
int flag = 1;
//每个timeout n++
connect(timer,&QTimer::timeout,ui->label,[=](){
    static int n = 0;
    ui->label->setText(QString::number(n++));
});

//按下按钮，暂停/继续
connect(ui->btnPause,&QPushButton::clicked,timer,[=]()mutable{
    if(flag == 1)
    {
        timer->stop();
        flag = 0;
    }
    else if(flag == 0)
    {
        timer->start(500);
        flag = 1;
    }
});
```

### 6.event事件

6.1用途：事件的分发

6.2也可以做拦截操作，不建议

6.3 bool event(QEvent *e)

6.4返回值是true代表用户处理这个事件，不向下分发了。（拦截）

6.5 if(e->type == 鼠标按下)

### 7.绘图

7.1绘图事件 void paintevent()

7.2声明一个画家对象，Qpainter painter(this)，这里的this作用是指定绘图设备

7.3画线、画圆、画矩形、画文字

7.4设置画笔 QPen，设置画笔宽度以及风格

7.5设置画刷 Qbrush ,设置画刷风格

```c++
QPainter painter(this);

QPen pen(QColor(255,0,0));
pen.setWidth(3);
pen.setStyle(Qt::DotLine);

painter.setPen(pen);

//QBrush brush(QColor(0,255,0));
painter.drawLine(QPoint(0,0),QPoint(100,100));
painter.drawEllipse(QPoint(100,100),50,50);
painter.drawRect(QRect(20,20,50,50));
painter.drawText(QRect(10,200,150,50),"hello world");
```

### 8.绘图高级

```c++
 QPainter painter(this);
 //移动画家，是相对现在的位置移动
 painter.translate(100,0);
 //画圆，这个位置也是相对画家的位置
 painter.drawEllipse(QPoint(100,50),50,50);

painter.translate(100,0);
//设置抗锯齿，因为更精细，所以需要的时间更多
painter.setRenderHint(QPainter::HighQualityAntialiasing);
painter.drawEllipse(QPoint(100,50),50,50);


painter.save();//保存画家现在的状态
//对画家状态修改
painter.restore();//还原保存的状态

```

### 9.手动调用绘图事件

```c++
QTimer *timer = new QTimer(this);

timer->start(50);   //一开始的状态
//每个timeout n++
connect(timer,&QTimer::timeout,this,[=](){
    pox += 1;
   
    if(pox > this->frameGeometry().width())
        pox = 0;
    update();  //手动调用绘图事件，会调用paintEvent函数

});

```

















