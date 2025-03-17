### 1.安装ubuntu22.04

#### 1.1 工具

vmware workstation pro17.6.2

ubuntu-22.04.5-desktop-amd64.iso

#### 1.2 步骤

![image-20250218100828790](https://s2.loli.net/2025/02/18/nmCP5TLq4Q2p63g.png)

点击下一步，添加用户名密码

![image-20250218100947730](https://s2.loli.net/2025/02/18/isMGWx3CjERd1p2.png)

选择硬盘、内存、cpu个数等。点击完成，创建虚拟机。

![image-20250218101140296](https://s2.loli.net/2025/02/18/SPi7438rjOMphZf.png)

ubuntu初始化界面一直点击下一步即可。（可以选择最小化安装、下载第三方软件、自动登录）



### 2. 中文界面

打开设置，找到Region & Language，在 Manage installed Languages中下载中文，并重新登录即可。

![image-20250218102219954](https://s2.loli.net/2025/02/18/SZp1PRXw6HIel34.png)

### 3. 与Windows电脑之间拖放文件

#### 3.1 默认设置不能使用的原因

Ubuntu(22.04，20.04等)默认启用了新版的窗口系统Wayland而非原来的X11，Vware Tools似乎未支持这个特性。

#### 3.2 操作

1. 禁用Wayland

   ```
   sudo gedit /etc/gdm3/custom.conf
   ```

   删掉WaylandEnable=false这一行最开始的#号

2. 重新安装 Vware Tools

   ```
   sudo apt-get autoremove open-vm-tools
   sudo apt-get install open-vm-tools-desktop    //这一行需要手动输入
   sudo reboot
   ```

   

### 4. 魔法（没有需求可不配置）

根据购买魔法的网站提供的教程操作。

1. 执行 `mkdir ~/clash; cd ~/clash` 在用户目录下创建 clash 文件夹。

   下载适合的 Clash 二进制文件，解压，并将解压产物重命名为 `clash`

   ```
   https://github.com/DustinWin/proxy-tools/releases/tag/Clash-Premium
   ```

2. 在终端 `cd` 到 Clash 二进制文件所在的目录，执行 `wget -O config.yaml "https://x9cxu.no-mad-world.club/link/cI4az3rs2BU49OUf?clash=3"` 下载 Clash 配置文件

3. 执行 `./clash -d .` 即可启动 Clash，同时启动 HTTP 代理和 Socks5 代理。（第一次执行时会先下载文件）

   如提示权限不足，请执行 `chmod +x clash`

4. 访问 [Clash Dashboard ](https://clash.razord.top/)可以进行切换节点、测延迟等操作。

   Host: `127.0.0.1`，端口: `9090`

5. 以 Ubuntu 22.04 为例，打开系统设置，选择网络，点击网络代理右边的 ⚙ 按钮，选择手动，填写 HTTP 和 HTTPS 代理为 `127.0.0.1:7890`，填写 Socks 主机为 `127.0.0.1:7891`，即可启用系统代理。