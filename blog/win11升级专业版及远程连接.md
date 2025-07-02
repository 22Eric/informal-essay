### 1. win11 升级专业版

1. 断网

2. 到系统输入密钥。我目前使用的是`BCQNW-3VWYB-4V7QD-M6R2B-7MH26`。等待系统重启

   ![image-20250702151221856](https://s2.loli.net/2025/07/02/VpA6qxFoNQY7Xgn.png)

3. win+R, 输入powershell， 回车, 再在弹出的窗口内输：
   `irm massgrave.dev/get.ps1 | iex`

4. 弹出窗口选[1]

5. 回到系统查看会显示”激活成功“

### 2. 远程桌面

1. 打开远程桌面设置

   ![image-20250702151552800](https://s2.loli.net/2025/07/02/Dm5u9yASlawB6fX.png)

2. 如果忘记密码怎么办？
   （1）修改密码

   ```
   net user 用户名 新密码
   ```

   （2）新建用户

   在此电脑—管理—本地用户和组 中新建用户，并在设置中增加远程桌面用户。

   

