# nexus服务部署流程

## 一、安装linux的jdk环境

### 1.下载linux的jdk8压缩包

### 2.在linux服务上创建jdk安装的目录

```
mkdir  /usr/local/java #创建jdk安装路径
cd /usr/local/java #进入jdk安装目录
```

通过xftp将压缩包传输到新创建的目录下/usr/local/jdk

### 3.解压压缩包

```
cd /xxx/java  #进入jdk安装目录
tar -zxvf jdk-xxxx-linux-x64.tar.gz  #对压缩包解压，文件名为下载的压缩包的名称
```

### 4.删除linux中自带的jdk版本

命令：java -version：查看JDK安装版本

```
java -version
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/fc97263d70b9d4db910f1a51f97cdfff.png)

如果显示有java版本就查看系统的jdk安装包

```
cd ~

rpm -qa | grep java // 查看系统的jdk安装包
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/ddddbfb70734db6eca8f8eb421add7b4.png)

卸载掉系统jdk

```
rpm -e xxx --nodeps // 命令进行装卸 xxx是上面查询到的安装包的名称
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/fd6bfd7abeda2d560ee5e432a3f5ff4b.png)

### 4.配置环境变量

编辑配置文件

```
vim /etc/profile
```

在文件末尾添加

```
JAVA_HOME=/usr/local/java/jdk1.8.0_xxx
CLASSPATH=$JAVA_HOME/lib/
PATH=$PATH:$JAVA_HOME/bin
export PATH JAVA_HOME CLASSPATH
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/8a972b349474040561ab555a3f57a126.png)

重新加载配置文件

```
source /etc/profile
```

### 5.验证jdk是否安装成功

执行命令

```bash
java -version
```

## 二、安装nexus服务

### 1.下载nexus压缩包

### 2.解压压缩包

在指定目录下新建nexus文件夹，通过xftp将压缩包传输过去，解压压缩包

```
tar -zxvf nexus-3.38.1-01-unix.tar.gz
```

![image-20220523105731260](https://i-blog.csdnimg.cn/blog_migrate/6c20892b1b0eb4e94afdeaa550895018.png)

### 3.启动nexus

```
 进入 /nexus/nexus-3.38.1-01/bin  #目录，可以看见 nexus 文件，这就是 Nexus 服务的脚本文件:
 
通过观察该文件文本内容，可以看到 start 和 run 命令都可以用来启动 Nexus 服务；区别在于：
 
 
start 是后台启动，日志以文件形式保存；

run 是当前进程启动，直接打印在控制台；

1、其他常用命令还有：

stop 是停止服务；

restart 是重启服务；

status 是查看服务状态
```

建议通过start启动

```
./nexus start
```

查看状态

```
./nexus status
```

### 4.在浏览器访问nexus的web页面（该操作需关闭linux服务器的防火墙）

```
ifconfig // 通过shell命令拿到linux的ip地址
```

在浏览器访问 Nexus 的 **Web 端首页**，输入 linux 服务器ip:8081（默认端口）

默认账号admin，密码在sonatype-work/nexus3 目录下 的 admin.password 文件中查看初始化密码。

进入后会提示重置密码，修改为123456即可

