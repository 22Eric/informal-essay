## 1. 安装git本地仓库

1.1 点击源代码管理，按指引安装git

![1742195597797_d](https://s2.loli.net/2025/03/17/HcKNyMtVdFAniIO.png)

1.2 选择打开文件夹。点击初始化仓库（与git init效果相同）

1.3 新建文件并提交

![1742195900071_d](https://s2.loli.net/2025/03/17/pFtuqozr36Sevc9.png)

1.4 删除commit

快捷键ctrl+j。 调出终端，输入

```
// 一个^表示恢复到上一级。（会删除现有的commit）
git reset --hard HEAD^
```

再输入

```
//提交到远端仓库
git push -f
```

## 2. 连接到远端仓库（github）

详细请看b站教程。

https://www.bilibili.com/video/BV1Hkr7YYEh8/?spm_id_from=333.1391.0.0&vd_source=3076b7865d54a5bdc68ba7704f19a89d