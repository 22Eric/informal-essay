1. 若gitignore更改后，想要应用到远程仓库/本地。

```
# 最简单的做法（推荐）
git rm -r --cached .
git add .
git commit -m "Apply .gitignore"
git push
```

2. 适用于.net的通用gitignore

   ```
   # .gitignore — 通用 .NET / Visual Studio / VS Code / Rider 配置
   # 参考 Microsoft 官方与常见社区规则，适用于 ASP.NET / .NET Core / .NET Framework 项目
   
   # Visual Studio
   .vs/
   **/.vs/
   *.suo
   *.user
   *.userosscache
   *.userprefs
   *.vcxproj.user
   *.vcxproj.filters
   *.pdb
   *.ilk
   *.ipdb
   *.sdf
   
   # Build / output
   [Bb]in/
   [Oo]bj/
   build/
   out/
   publish/
   artifacts/
   generated/
   *_Published/
   *.Publish.xml
   
   # Configuration / local settings
   appsettings.*.json
   appsettings.Development.json
   *.Local.json
   secrets.json
   .env
   local.settings.json
   
   # NuGet
   *.nupkg
   *.snupkg
   packages/
   **/packages/
   project.lock.json
   project.fragment.lock.json
   .nuget/
   .nuget/packages/
   
   # dotnet tools
   .dotnet/tools/
   
   # Rider / JetBrains
   .idea/
   *.sln.iml
   *.DotSettings.user
   _ReSharper*/
   *.DotSettings
   
   # VS Code
   .vscode/
   .vscode/*
   
   # Test results / coverage
   TestResults/
   *.trx
   *.coverage
   coverage/
   coverage/**
   
   # Logs / temp
   *.log
   *.tlog
   *.tmp
   *.temp
   *.bak
   *.orig
   *.old
   logs/
   
   # Database / local dev files
   *.mdf
   *.ldf
   *.sqlite
   *.db
   *.db-journal
   
   # IIS / IIS Express
   /IISExpress/
   /.vs/**/applicationhost.config
   
   # Publish / deployment
   publish/
   *.azurePubxml
   *.PublishSettings
   
   # Package managers / frontend
   node_modules/
   npm-debug.log
   yarn-error.log
   package-lock.json
   yarn.lock
   
   # IDE / tooling artifacts
   *.resharper
   *.ncrunch*
   *.VisualState.xml
   .vscode-test/
   
   # Coverage / profiling
   *.coverage
   *.coveragexml
   *.opencover
   *.prof
   
   # OS generated
   .DS_Store
   Thumbs.db
   ehthumbs.db
   
   # Misc
   *.class
   *.jar
   *.war
   *.war.orig
   
   
   ```

   3. 适用于qt C++ windows的.gitignore
   
      ```
      # Qt / C++ (Windows) 常用 .gitignore
      
      
      # --- VS Code / 其它 IDE ---
      .vscode/
      .idea/
      *.code-workspace
      .qtc_clangd/
      
      
      # --- 构建产物 ---
      /build/
      /build-*/
      cmake-build-*/
      out/
      CMakeFiles/
      CMakeCache.txt
      cmake_install.cmake
      Makefile
      install_manifest.txt
      
      # --- qmake / Qt Creator ---
      *.pro.user
      *.pro.user.*
      *.qmake.stash
      *.qmake.cache
      *.creator.user
      *.creator.user.*
      
      # --- Visual Studio / MSVC ---
      *.sln
      *.vcxproj*
      *.vcproj*
      *.vcxproj.user
      *.user
      *.suo
      *.sdf
      *.VC.db
      *.opendb
      
      # --- VS Code / 其它 IDE ---
      .vscode/
      .idea/
      *.code-workspace
      
      # --- 自动生成的 Qt 文件 ---
      moc_*.cpp
      qrc_*.cpp
      ui_*.h
      *.moc
      *.moc.h
      *.ui.user
      
      # --- 编译产物 ---
      *.obj
      *.o
      *.a
      *.lib
      *.dll
      *.exp
      *.exe
      *.pdb
      *.ilk
      *.idb
      
      # --- 临时 / 日志 / 备份 ---
      *.log
      *.log.*
      *.tmp
      *.tmp.*
      *.swp
      *~ 
      *.bak
      *.orig
      *.rej
      *.txt
      
      # --- 系统文件 ---
      Thumbs.db
      desktop.ini
      .DS_Store
      
      # --- 可选：打包 / 发布产物 ---
      /dist/
      /release/
      /bin/
      ```
      
      
