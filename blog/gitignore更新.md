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

   
