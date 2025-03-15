### 1. ROS2一键安装

```shell
sudo apt update
wget http://fishros.com/install -O fishros && bash fishros  //所有的选择都选1
```

安装结束后，关闭当前终端，打开一个新的终端，输入ros2，查看是否安装完成

### 2. hardware_interface安装

```shell
sudo apt install ros-humble-hardware-interface //如果用的不是humble，则替换成使用的ROS 2 发行版（例如 foxy、galactic 等）

```

使用下面的语句查看是否安装成功

```shell
ros2 pkg list | grep hardware_interface
```

### 3. 编译法奥功能包

![image-20250218153543399](https://s2.loli.net/2025/02/18/6cvIfAdpoMZlKX1.png)

创建一个文件夹ros2_ws/src。把要编译的文件放入这个文件夹下

![image-20250218153748822](https://s2.loli.net/2025/02/18/jHYkXGDRSdBabrg.png)

#### 3.1 编译功能包

**编译fairino_msgs功能包**

```
cd ros2_ws
colcon build --packages-select fairino_msgs
source install/setup.bash
```

![image-20250218154006162](https://s2.loli.net/2025/02/18/e2KuEpDamHnWdxO.png)



**编译fairino_hardware功能包**

```
cd ros2_ws
colcon build --packages-select fairino_hardware
source install/setup.bash
```

需要编译两遍，第二遍才会提示成功。

![image-20250218154247254](https://s2.loli.net/2025/02/18/yZiFHxaRuBdgvlr.png)



**编译fairino_description功能包**

```
cd ros2_ws
colcon build --packages-select fairino_description
source install/setup.bash
```



**编译法奥机器人moveit2配置包，以fairino3_v6_moveit2_config为例**

```
cd ros2_ws
colcon build --packages-select fairino3_v6_moveit2_config
source install/setup.bash
```



全部编译完成后，查看是否成功

```
ros2 pkg list | grep fair
```

![image-20250218155239045](https://s2.loli.net/2025/02/18/YJfKDXbFgzoVqxt.png)

### 4. 配置法奥机械臂Moveit2模型

#### 4.1 安装moveit

```shell
sudo apt install ros-humble-moveit-setup-assistant
```

#### 4.1  创建工作空间

```shell
mkdir -p test_fa_ws/src
cd test_fa_w/src
mkdir fairino3_v6_robot_moveit_config
cd ..
```

编译功能包，并source

```shell
colcon build
source install/setup.bash
```

启动moveit_setup_assistant进行机器人配置

```
ros2 launch moveit_setup_assistant setup_assistant.launch.py
```

#### 4.2 配置机器人

**启动配置界面**

在test_fa_ws目录下打开终端，配置界面选择“Create New Moveit Configuration Package”，创建新的moveit配置功能包。

![image-20250218160851745](https://s2.loli.net/2025/02/18/bgUVTJ79GdStl8h.png)

然后选中机器人的描述文件，即.urdf这个文件，然后选择Load Files，加载机器人模型，就可以看到右边加载出来了机器人的模型。

![image-20250218161141008](https://s2.loli.net/2025/02/18/5bOiIfo8gGBR3Xh.png)

**配置Self-Collisions**

Self-Collisions为机器人碰撞设置，点击Generate Collision Matrix既可自动生成关节碰撞矩阵，其会将两接触连杆以及永远接触不到的连杆之间的碰撞取消，从而配置机器人关节碰撞矩阵的，进而避免计算两接触面碰撞，点击Generate Collision Matrix既可自动生成。

![image-20250218161349854](https://s2.loli.net/2025/02/18/mr6dzxFIlB13Hi7.png)

**配置Virtual Joints**

Virtual Joints为机器人虚拟轴，当机器人安装在移动平台上是就需要给机器人设置虚拟轴，设置虚拟轴的name、子连杆、关节类型等，当移动平台移动时，虚拟轴也同步运动，从而带动机器人运动，实现机器人随着移动平台运动的功能本次直接将机器人放置在world坐标系中，取名为virtual_joints。

![image-20250218161404098](https://s2.loli.net/2025/02/18/rYukZ4eIst2XBcx.png)

**配置Planning Groups**

Planning Groups为机器人的规划组，它将进行运动学计算时需要同一考虑的关节划在同一规划组内，进行统一的正逆向运动学计算，如将一机器人放在AGV小车上，再在机器人末端安装夹具，测试将AGV小车的四个关节划在一个规划组，机器人的六个关节划在一个规划组，夹具的一个关节划在一个规划组进行运动学计算。

由于本次不涉及夹具所以只添加机器人的各个关节组，即arm组，首先添加arm组，动力学求解器Kinematic Solver选择kdl_kinematics_plugin/KDLKinematicsPlugin，然后默认的规划器Group Default Planner选TRRT，然后点击Add Joints为这个规划组添加关节。

![image-20250218161525078](https://s2.loli.net/2025/02/18/VHy7bdTkZI5OPYj.png)

arm的关节按住shift可以进行多选，点击’>’进行添加，然后点击save保存。

![image-20250218161609327](https://s2.loli.net/2025/02/18/Prd8GEin9xWueZV.png)

**配置Robot Poses**

Robot Poses为机器人预设位姿，其为每个规划组定义一些预设的位姿，为arm定义一个home位姿态，这个姿态可以随意选择。

![image-20250218161703359](https://s2.loli.net/2025/02/18/3cMi1hFRukPY4sz.png)

Robot Poses可以为每个规划组定义预设姿态，当机器人中存在夹具时，可在Planning Groups部分添加夹具规划组，然后在Robot Poses设置姿态时就可为夹具设置预设姿态。

**配置End Effectors**

End Effectors为机器人末端执行机构，末端执行机构的规划组为hand，然后默认连接的parent_link是panda_link8，由于本次没有末端执行器，所以这一步可跳过。

**ros2_control URDF Modifications**

ros2_control URDF Modifications主要用于设置下发和反馈的关节数据类型，可以选择位置、速度、扭矩三种，本次选择下发和反馈的关节数据类型都为位置控制，然后直接Add interfaces即可。

![../_images/fairino_harware_011.png](https://s2.loli.net/2025/02/18/VKxaz2ic16sHJMf.png)

**ROS 2 Controllers**

ROS 2 Controllers主要用于生成ros2_controllers.yaml文件，该文件设置了发布频率、关节名称、控制器名称、控制器类型等，配置ROS 2 Controllers，为每个规划组配置控制器，点击Auto Add JointTrajectoryController Controllers For Each Planning Group即可。

![../_images/fairino_harware_012.png](https://s2.loli.net/2025/02/18/SevxuIGtBK9jpfo.png)

**Moveit Controllers**

Moveit Controllers主要用于生成moveit_controllers文件，该文件设置了控制器名称、控制器类型等，需要注意的是moveit_controllers中的控制器名称需要与ros2_controllers的控制器名称相同，否则不能顺利运行。

并且当moveit_controllers中的控制器名称与ros2_controllers中的控制器名称相同时，moveit_controllers中的控制器类型会自动与ros2_controllers中的控制器类型映射到一起，实现下发的控制数据通过moveit_controllers发送给ros2_controllers，然后再通过ros2_controllers中的插件驱动实际机器人运动。

![image-20250218161946127](https://s2.loli.net/2025/02/18/ywOiPVGatZ3KmfQ.png)

**Launch Files**

配置Launch Files，使用默认配置即可。

**作者信息**

![../_images/fairino_harware_015.png](https://s2.loli.net/2025/02/18/TFJrlfX6n4OKZvk.png)

**生成Launch文件**

生成Launch文件，选择生成位置，本次在test_fa_ws/src文件路径下创建一个文件夹fairino3_v6_robot_moveit_config用于存放配置文件，然后选择生成。

![../_images/fairino_harware_016.png](https://s2.loli.net/2025/02/18/jXUDMvhd4uTnae1.png)

由于本次之前已经配置过一遍，若为初次配置Check files you want to be generated部分内容为黑色，说明可以生成Launch文件。

#### 4.3 安装插件库

```shell
sudo apt update
sudo apt install ros-humble-controller-manager
sudo apt install ros-humble-moveit-planners-ompl
sudo apt install ros-humble-moveit-planners-chomp
sudo apt install ros-humble-joint-trajectory-controller
sudo apt install ros-humble-joint-state-broadcaster
```

#### 4.4 启动Launch

在配置完成后就可以进行功能包的编译，可以使用自定义机器人moveit2配置包替换法奥机器人moveit2配置包，实现针对用户自定义机器人的插件兼容使用

```shell
colcon build --packages-select fairino3_v6_robot_moveit_config
source install/setup.bash
```

然后直接运行刚才配置好的Launch文件

```shell
ros2 launch fairino3_v6_robot_moveit_config demo.launch.py
```
