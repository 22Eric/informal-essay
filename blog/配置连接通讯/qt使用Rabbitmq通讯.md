## 1.安装Rabbitmq服务

### 1.1 安装配置Erlang

首先，需要去Rabbitmq的官网[https://www.rabbitmq.com/docs/which-erlang](https://www.rabbitmq.com/docs/which-erlang)，查询Rabbitmq版本以及对应支持的Erlang版本。版本不匹配可能会导致服务无法使用。目前，我使用的是Erlang 26.2.5.4和RabbitMQ 4.0.3。

在giuthub（[https://github.com/erlang/otp](https://github.com/erlang/otp)）或erlang官网中下载对应的版本。默认下一步安装即可。

![image-20241102104158606](https://s2.loli.net/2024/11/02/D9bjH43sSaG5oIc.png)

接下来配置环境变量，常规操作，新建系统变量-键入变量名ERLANG_HOME，键入变量值:erlang安装路径。如下图：

![e31a57e082e57a4b691dcb7afb2c11a6](https://s2.loli.net/2024/11/02/NVO4Bd6Xbkosx25.png)

![ecff896a6da263f951cfdcd5175712c4](https://s2.loli.net/2024/11/02/ztDCda9MNY1XR7J.png)

然后打开cmd，输入erl，看到我们的erlang版本号，就说明安装成功了

![image-20241102105123471](https://s2.loli.net/2024/11/02/CFqlPELrS6jxDz7.png)

### 1.2 安装Rabbitmq

在giuthub（[https://github.com/rabbitmq/rabbitmq-server](https://github.com/rabbitmq/rabbitmq-server)）或Rabbitmq官网中下载对应的版本

![image-20241102104557697](https://s2.loli.net/2024/11/02/idTQH2DRUe793Pf.png)

默认下一步安装即可。

上面的命令执行成功之后，我们就可以通过[http://localhost:15672](http://localhost:15672/)来访问web端的管理界面

默认用户名、密码都是guest

![a4f27bcafb4c83b144a11f07fbbfbcb5](https://s2.loli.net/2024/11/02/AkToZyEhG7UznwV.png)

## 2.qt建立Rabbitmq客户端

### 2.1下载QAMQP并编译

在github（[https://github.com/mbroadst/qamqp](https://github.com/mbroadst/qamqp)）中下载qamqp。

使用qt creator打开qamqp.pro工程，并编译。找到对应的`qamqp.lib和qamqp.dll`或`qamqp0.lib和qamqp0.dll` 。

详细工程测试样例代码请看RabbitmqTest













