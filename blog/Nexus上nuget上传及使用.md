### 1. Nexus安装

Nexus安装完成后，会在Browse下自动创建nuget-group，nuget-hosted，nuget.org-proxy

### 2. 本地包编译

使用visual studio，打开csproj文件，在PropertyGroup中添加下面的信息

```C#
<PropertyGroup>
    	 <GeneratePackageOnBuild>True</GeneratePackageOnBuild><!--生成nuget包-->
 		 <VersionPrefix>1.0.0</VersionPrefix><!--版本号-->
</PropertyGroup>
```

重新编译生成后，可以在Debug/Release文件夹下发现 .nupkg 包。

### 3. 上传包

Nexus登录网页端后台，在Upload下的nuget-hosted里面将.nupkg 包上传。如图所示

![image-20251126103021184](https://s2.loli.net/2025/11/26/O2uV9cbQXnfKL1G.png)

#### 4. 下载nuget包使用

在本地电脑的`C:\Users\{用户名}\AppData\Roaming\NuGet\NuGet.Config`文件中增加一个key。(ip和端口进行对应的修改)

```C#
<configuration>
  <packageSources>    
    <add key="Nexus.hosted" value="http://192.168.5.38:8081//repository/nuget-hosted/" allowInsecureConnections="true" />
  </packageSources>
</configuration>
```

配置文件保存后，就可以找到刚刚上传的包了。

![1764124784607_d](https://s2.loli.net/2025/11/26/5qrtNZwlm8DQkYy.png)