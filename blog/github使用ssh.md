1. 在 GitHub 上配置 SSH key 的步骤如下：

   ### 1. 生成 SSH key（如果你还没有）

   在终端（命令提示符或 PowerShell）输入：

   ```
   ssh-keygen -t ed25519 -C "你的邮箱@example.com"
   ```

   如果你的系统不支持 ed25519，可以用：

   ```
   ssh-keygen -t rsa -b 4096 -C "你的邮箱@example.com"
   ```

   按提示操作，生成的 key 默认保存在 `C:\Users\你的用户名\.ssh\id_ed25519` 和 `id_ed25519.pub`。

   **备注**：ssh-keygen每一次生成的公钥和私钥都是不一样的。不用担心重复。

   ​	   你的邮箱@example.com，可以用任意字符串，但推荐使用邮箱。

   ------

   ### 2. 复制公钥内容

   用记事本或命令复制公钥内容：

   type $env:USERPROFILE\.ssh\id_ed25519.pub

   或者直接用记事本打开 `id_ed25519.pub` 文件，复制全部内容。

   ------

   ### 3. 添加 SSH key 到 GitHub

   1. 登录 [GitHub](vscode-file://vscode-app/c:/Users/22594/AppData/Local/Programs/Microsoft VS Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html)。
   2. 点击右上角头像 → **Settings（设置）**。
   3. 左侧菜单选择 **SSH and GPG keys**。
   4. 点击 **New SSH key**。
   5. 填写标题（随便写），把刚才复制的公钥粘贴到 Key 区域。
   6. 点击 **Add SSH key**。

   ------

   ### 4. 测试 SSH 连接

   在终端输入：

   ssh -T git@github.com

   如果看到 `Hi 用户名! You've successfully authenticated...`，说明配置成功。

   **备注**：旧电脑不使用的话，直接把github上的公钥删除就行。