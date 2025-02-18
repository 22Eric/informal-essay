## 1. 什么是DbContext。我们可以用DbContext做什么？

`DbContext` 是 Entity Framework Core (EF Core) 中的一个核心类，用于管理与数据库的交互。它是应用程序与数据库之间的桥梁，负责以下任务：

- **数据库连接管理**：`DbContext` 负责打开和关闭数据库连接。
- **实体跟踪**：`DbContext` 跟踪实体对象的状态（如新增、修改、删除），并在调用 `SaveChanges` 时将更改同步到数据库。
- **查询执行**：通过 `DbSet<TEntity>` 属性，`DbContext` 允许你使用 LINQ 查询数据库。
- **事务管理**：`DbContext` 默认将多个操作包装在一个事务中，确保数据一致性。
- **模型配置**：通过 `OnModelCreating` 方法，`DbContext` 允许你配置实体与数据库表的映射关系。

## 2. 与传统方式相比DbContext有什么好处

### 2.1 **面向对象的编程模型**

- **传统方式**：需要手动编写 SQL 语句，并将数据库查询结果映射到对象。
- **DbContext**：通过实体类（POCO）和 `DbSet<TEntity>`，可以直接以面向对象的方式操作数据库，无需关心底层 SQL。

**示例**：

```c#
// 传统方式
var sql = "SELECT * FROM Users WHERE Age > 18";
var users = ExecuteQuery(sql); // 需要手动映射到对象

// DbContext 方式
var users = context.Users.Where(u => u.Age > 18).ToList(); // 直接返回对象
```

------

### 2.2 **自动跟踪实体状态**

- **传统方式**：需要手动管理实体的状态（如新增、修改、删除），并编写相应的 SQL 语句。
- **DbContext**：自动跟踪实体的状态变化，并在调用 `SaveChanges` 时生成并执行相应的 SQL 语句。

**示例**：

```c#
// 传统方式
var user = GetUserById(1);
user.Name = "Bob";
var sql = "UPDATE Users SET Name = 'Bob' WHERE UserId = 1";
ExecuteNonQuery(sql);

// DbContext 方式
var user = context.Users.Find(1);
user.Name = "Bob";
context.SaveChanges(); // 自动生成并执行 UPDATE 语句
```

------

### 2.3 **LINQ 支持**

- **传统方式**：需要手动编写 SQL 查询，容易出错且难以维护。
- **DbContext**：支持 LINQ（Language Integrated Query），可以使用强类型的查询语法，减少错误并提高代码可读性。

**示例**：

```c#
// 传统方式
var sql = "SELECT * FROM Users WHERE Age > 18 ORDER BY Name";
var users = ExecuteQuery(sql);

// DbContext 方式
var users = context.Users
    .Where(u => u.Age > 18)
    .OrderBy(u => u.Name)
    .ToList();
```

------

### 2.4 **数据库无关性**

- **传统方式**：SQL 语句通常与特定数据库（如 SQL Server、MySQL）绑定，切换数据库时需要重写 SQL。
- **DbContext**：EF Core 支持多种数据库（如 SQL Server、MySQL、PostgreSQL、SQLite 等），切换数据库时只需更改数据库提供程序，无需修改代码。

**示例**：

```c#
// 使用 SQL Server
optionsBuilder.UseSqlServer("YourConnectionString");

// 使用 MySQL
optionsBuilder.UseMySQL("YourConnectionString");
```

------

### 2.5 **迁移支持**

- **传统方式**：需要手动编写和维护数据库架构变更脚本（如创建表、添加列）。
- **DbContext**：EF Core 提供迁移（Migrations）功能，可以自动生成并应用数据库架构变更。

**示例**：

```c#
# 创建迁移
dotnet ef migrations add InitialCreate

# 应用迁移
dotnet ef database update
```

------

### 2.6**性能优化**

- **传统方式**：需要手动优化 SQL 查询和数据库操作。
- **DbContext**：EF Core 提供了多种性能优化功能，如延迟加载、显式加载、查询缓存等。

**示例**：

```c#
// 延迟加载
var user = context.Users.Find(1);
var orders = user.Orders; // 延迟加载 Orders

// 显式加载
context.Entry(user).Collection(u => u.Orders).Load();
```

------

### 2.7 **减少样板代码**

- **传统方式**：需要编写大量重复的代码（如打开连接、执行命令、关闭连接）。
- **DbContext**：封装了常见的数据库操作，减少了样板代码。

**示例**：

```c#
// 传统方式
using (var connection = new SqlConnection("YourConnectionString"))
{
    connection.Open();
    var command = new SqlCommand("SELECT * FROM Users", connection);
    var reader = command.ExecuteReader();
    while (reader.Read())
    {
        // 手动映射数据
       
    }
}

// DbContext 方式
var users = context.Users.ToList(); // 一行代码完成查询
```



------

### 2.8 **支持复杂查询和关系**

- **传统方式**：处理复杂查询和关系（如多表连接、一对多、多对多）时需要编写复杂的 SQL。
- **DbContext**：通过 LINQ 和导航属性，可以轻松处理复杂查询和关系。

**示例**：

```c#
var usersWithOrders = context.Users
    .Include(u => u.Orders) // 加载关联的 Orders
    .Where(u => u.Orders.Any(o => o.Total > 100))
    .ToList();
```



## 3.怎么使用DbContext

### 3.1创建 DbContext 类

首先，你需要创建一个继承自 `DbContext` 的类，并定义 `DbSet<TEntity>` 属性来表示数据库中的表

```c#
    public class AuthCenterDbContext:DbContext
    {
        public DbSet<UserModel> Users { get; set; }

        public DbSet<KeyPairModel> KeyPairs { get; set; }

        public DbSet<AuthRecord> AuthRecords { get; set; }

        public DbSet<UserActionModel> UserActionRecords { get; set; }
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            // 使用ConfigurationManager读取连接字符串
            var connectionString = ConfigurationManager.ConnectionStrings["DefaultConnection"].ConnectionString;
            optionsBuilder.UseMySQL(connectionString);
            base.OnConfiguring(optionsBuilder);
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
            //获取当前程序集默认的是查找所有继承了IEntityTypeConfiguration的类
            modelBuilder.ApplyConfigurationsFromAssembly(this.GetType().Assembly);
        }
    }
```

### 3.2 定义实体类

实体类对应数据库中的表结构。每个实体类通常对应一张表，类的属性对应表的列。

```c#
    public class UserActionModel:BaseModel
    {

        public string? Location { get; set; }
        public string? MachineName { get; set; }
        public string? Module { get; set; }
        public string? Action { get; set; }
        public DateTime? ActionTime { get; set; }
        public string? Customer { get; set; }

        //纬度
        public double? Latitude { get; set; }

        //经度
        public double? Longitude { get; set; }
    }
```

### 3.3实体类到数据表的映射

```c#
    public class UserMapping : BaseMapping<UserModel>
    {
        public UserMapping():base() { }
        public override void MapProperty(EntityTypeBuilder<UserModel> builder)
        {
            builder.Property(t => t.Account).HasColumnName("account");
            builder.Property(t=>t.Password).HasColumnName("passwd");
            builder.Property(t => t.RealName).HasColumnName("real_name");
            builder.Property(t => t.UserRoleId).HasColumnName("userRoleId");
        }

        public override void ToTable(EntityTypeBuilder<UserModel> builder)
        {
            builder.ToTable("tb_user");
        }
    }
```

### 3.4 调用

```C#
using (var context = new AuthCenterDbContext())
{
    try
    {
        var authRecord = new AuthCenterRepo.Model.UserActionModel
        {
            Action = e.Action,
            ActionTime = e.ActionTime,
            Customer = e.Customer,
            Location = e.Location,
            MachineName = e.MachineName,
            Module = e.Module,
            Latitude = e.Latitude,
            Longitude = e.Longitude
        };
        context.UserActionRecords.Add(authRecord); // 添加到上下文
        context.SaveChanges();
    }
    catch (DbUpdateException ex)
    {
        Console.WriteLine("Failed to save changes: " + ex.Message);
        if (ex.InnerException != null)
        {
            Console.WriteLine("Inner Exception: " + ex.InnerException.Message);
        }
    }
}
```



