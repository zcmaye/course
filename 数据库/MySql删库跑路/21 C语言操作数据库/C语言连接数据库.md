## MySQL C API

MySQL C API 是一个为 C 语言开发者提供的接口，用于实现对 MySQL 数据库的操作。通过这个 API，开发者可以在 C 或 C++ 程序中执行 SQL 语句，管理数据库连接，处理事务和结果集等。

C API 代码随 MySQL 一起分发，并在 `libmysqlclient` 库中实现。

当我们安装好MySQL发行版之后，就包含了CAPI。

用于链接 C API 客户端应用程序的库文件名称取决于发行版构建的库类型和平台。

- 在 Unix（和类 Unix）系统上，静态库为 `libmysqlclient.a`；动态库在大多数 Unix 系统上为 `libmysqlclient.so`。
- 在 Windows 上，静态库为 `mysqlclient.lib`，动态库为 `libmysql.dll`。Windows 发行版还包括 `libmysql.lib`，这是一个静态导入库，用于使用动态库。

### 配置

#### 找到库位置

找到MySQL安装目录；发现存在`inclue`和`lib`目录即可直接使用！

![image-20250308164903175](./assets/image-20250308164903175.png)

#### Vs中配置库

+ 将头文件目录`F:\Tools\MySQL\MySQLServer8.4\include`配置到包含目录
+ 将库文件目录`F:\Tools\MySQL\MySQLServer8.4\lib`配置到库目录

![image-20250308165039416](./assets/image-20250308165039416.png)

+ 将库`libmysql.lib`配置到，链接器/输入/附加依赖项中。

![image-20250308165202426](./assets/image-20250308165202426.png)

> 注意，运行时还需要加载`libmysql.dll`动态库，所以还需要将库目录配置到环境变量PATH中！！！

#### 测试配置

输入如下代码，编译运行，如果能打印客户端版本，即表示配置成功！

```c
#include <stdio.h>
#include "mysql.h"

int main()
{
	printf("%s %ld\n", mysql_get_client_info(), mysql_get_client_version());

	return 0;
}
```

### 使用

#### C API 基本数据结构

本节描述了用于准备语句、异步接口或复制流接口的 C API 数据结构。

- `MYSQL`

  此结构表示一个数据库连接的处理程序。它用于几乎所有 MySQL 功能。不要尝试复制`MYSQL`结构。无法保证此类副本将可用。

- `MYSQL_RES`

  此结构表示返回行 ( `SELECT`, `SHOW`, `DESC/DESCRIBE`, `EXPLAIN`) 的查询的结果。在本节的其余部分中，从查询返回的信息称为*结果集*。

- `MYSQL_ROW`

  这是一行数据的类型安全表示。它目前被实现为一个计数字节字符串的数组(char**)。通过调用 mysql_fetch_row() 获取行。

- `MYSQL_FIELD`

  此结构包含元数据：有关字段的信息，例如字段的名称、类型和大小。 本节稍后将更详细地描述其成员。 您可以通过重复调用 mysql_fetch_field() 来获取每个字段的 MYSQL_FIELD 结构。 字段值不属于此结构； 它们包含在 MYSQL_ROW 结构中。

- `MYSQL_FIELD_OFFSET`

  这是 MySQL 字段列表中偏移量的类型安全表示。 （由 mysql_field_seek() 使用。）偏移量是一行中的字段编号，从零开始。

#### C API基本流程

```c
#include<stdio.h>
#include<mysql.h>
```

把mysql头文件包含到代码中。

```c
int main()
{
    //初始化MYSQL
	MYSQL* mycon = mysql_init(NULL);
    if(mycon == NULL) {
		printf("mysql init failed\n");
        return -1;
    }
```

mycon是一个MySQL的连接指针，先初始化为NULL；接下来通过mysql_init分配或初始化一个适用于 mysql_real_connect() 的 MYSQL 对象。 如果参数是一个 NULL 指针，该函数分配、初始化并返回一个新对象。 否则，初始化对象并返回对象的地址。 如果 mysql_init() 分配了一个新对象，则在调用 mysql_close() 以关闭连接时将其释放。

```c
	if(!mysql_real_connect(mycon,		//连接对象
		"localhost",	//主机名或ip地址
		"root",			//用户名
		"123456",		//密码
		"hdy",			//数据库名
		3306,			//端口号
		NULL,			//一般为NULL
		0))				//通常为0
	{
		printf("Error %d (%s): %s\n", mysql_errno(mycon), mysql_sqlstate(mycon), mysql_error(mycon));
		goto done;
	}
```

mysql_real_connect() 尝试建立与在主机上运行的 MySQL 服务器的连接。 在执行任何其他需要有效 MYSQL 连接处理程序结构的 API 函数之前，客户端程序必须成功连接到服务器。

```c
	done:
	if (mycon)
		mysql_close(mycon);
	return 0;
}
```

goto done;用于在最后对mysql连接进行关闭。

```c
	char query[] = "SELECT * FROM emp";
	if (0 != mysql_query(mycon, query)) {
		printf("Error %d (%s): %s\n", mysql_errno(mycon), mysql_sqlstate(mycon), mysql_error(mycon));
		goto done;
	}
```

连接成功之后，使用myql_query或mysql_real_query执行 SQL 语句。执行成功返回0，失败返回非零值。

通常，字符串必须由单个 SQL 语句组成，不带终止分号 ( `;`) 或`\g`. 如果启用了多语句执行，则字符串可以包含多个用分号分隔的语句。

+ [`mysql_query()`](https://dev.mysql.com/doc/c-api/8.0/en/mysql-query.html)执行以` \0`  结尾的 SQL 语句字符串，不能用于包含二进制数据的语句；
+ [`mysql_real_query()`](https://dev.mysql.com/doc/c-api/8.0/en/mysql-real-query.html)可以执行以非`\0`结尾的字符串（二进制数据可能包含`\0`字符）

```c
	MYSQL_RES* result = mysql_store_result(mycon);
	if (!result) {
		if (mysql_errno(mycon) != 0) {
			printf("Error %d (%s): %s\n", mysql_errno(mycon), mysql_sqlstate(mycon), mysql_error(mycon));
			goto done;
		}
		else {
			printf("No result returned");
		}
	}
```

调用 mysql_real_query() 或 mysql_query() 后，必须为每个成功生成结果集的语句（SELECT、SHOW、DESCRIBE、EXPLAIN、CHECK TABLE 等）调用 mysql_store_result() 。 完成结果集后，还必须调用 mysql_free_result()。

```c
	else {
		//获取查询到的行数
		uint64_t rowsCount = mysql_num_rows(result);
		printf("rowsCount: %llu\n", rowsCount);
		//获取查询到的列数
		//uint32_t fieldsCount = mysql_field_count(mycon);		//从从连接对象获取查询到的列数
		uint32_t fieldsCount = mysql_num_fields(result);		//从结果集中获取查询到的列数（推荐）
		printf("fieldsCount: %u\n", fieldsCount);

```

+ `mysql_num_rows`获取查询到的数据行数(只对SELECT语句有效)，如果是非查询语句可以使用`mysql_affected_rows`获取受影响的行数
+ `mysql_field_count`和`mysql_num_fields`都可以获取查询到的列数，但是参数不一样

```c
		MYSQL_ROW row = NULL;
		while (row = mysql_fetch_row(result)) {
			for (uint32_t i = 0; i < fieldsCount; i++) {
				printf("%-12s", row[i] ? row[i] : "NULL");
			}
			printf("\n");
		}

		mysql_free_result(result);
	}

```

`mysql_fetch_row()`检索结果集的下一行，如果没有更多行要检索(抓完了)则返回NULL;

通过字段数量可以遍历到每一个字段值。

```c
	done:
	if (mycon)
		mysql_close(mycon);
	return 0;
}
```

最后必须关闭mysql连接。

如果查询结果中，**中文乱码**，则需要设置客户端字符集：

```c
	if (0 != mysql_query(mycon, "SET NAMES gbk")) {
		printf("Error %d (%s): %s\n", mysql_errno(mycon), mysql_sqlstate(mycon), mysql_error(mycon));
		goto done;
	}
```

#### 获取多个结果集

我们可以给`mysql_real_connect`最后一个参数传递`CLIENT_MULTI_STATEMENTS`，以支持同时写多个查询语句，并批量获取结果集！

```c
	char query[] = "SELECT * FROM emp;SELECT * FROM dept";
	if (0 != mysql_query(mycon, query)) {
		printf("Error %d (%s): %s\n", mysql_errno(mycon), mysql_sqlstate(mycon), mysql_error(mycon));
		goto done;
	}
```

在上面代码中，我们在一个query中写了两个查询语句，并执行，接下来我们得循环获取结果集：

```c
	//循环获取多个结果集
	do {
		//就是前面获取结果集的代码
	} while (mysql_next_result(mycon) == 0);
```

`mysql_next_result`函数用来判断是否有下一个结果集，返回0表示成功，有更多结果集；返回-1表示成功，没有更多结果集；返回大于0的数，表示发生错误！

#### 获取字段信息

##### 获取字段名

如果需要获取字段名，则需要在获取结果集之后获取。而且有多种获取字段名的方式。

```c
MYSQL_FIELD *field = NULL;
```

+ 方式一：从结果集中一个字段一个字段的抓取字段信息

```c
while (field = mysql_fetch_field(result))
{
    printf("%-15s", field->name);
}
```

+ 方式二：先把结果集中的所有字段都抓取到（返回存储所有字段的数组指针），然后通过字段总数去遍历数组

```c
field = mysql_fetch_fields(result);
for (int i = 0; i < col_num; i++)
{
    printf("%-15s", field[i].name);
}
```

+ 方式三：根据字段编号，从结果集中获取指定字段

```cpp
for (int i = 0; i < col_num; i++)
{
    field = mysql_fetch_field_direct(result, i);
    printf("%-15s", field->name);
}
```

##### 获取字段/数据长度

所谓字段长度是指，字段能够存储数据的长度。所有数据都是以字符串的方式存储的，这个其实就是能够存储的字符串的长度。

| 类型        | 字节 | 长度 | 描述                                                         |
| ----------- | ---- | ---- | ------------------------------------------------------------ |
| SMALLINT    | 2    | 6    | 存储范围是[-32768,32767]，加上符号总共六个字符，所有长度为6  |
| VARCHAR(10) | 4*10 | 40   | 不同的字符集可能不一样，总长度= 字符集规定的每个字符的字节数*指定的大小 |

```c
while (field = mysql_fetch_field(result))
{
    printf("%-15s", field->name,
           field->name_length
           field->length,
           field->max_length);
}
```

+ field->length为字段创建时指定的最大长度(如上表所示)
+ field->max_length为查询到该列数据中，最长的数据的长度
+ field->name_length为字段名的长度

如果想要获取每一行每个数据的长度，可以通过`mysql_fetch_lengths`函数来获取。

```c
MYSQL_ROW row;
//获取每一行记录
while (row = mysql_fetch_row(result))
{
    //获取每行记录的每个数据的长度
    unsigned long* lens = mysql_fetch_lengths(result);
    for (int i = 0; i < col_num; i++)
    {
        printf("%-15ld", lens[i]);
    }
	//获取每个数据
    for (int i = 0; i < col_num; i++)
    {
        printf("%-15s", row[i]);
    }
    printf("\n");
}
```

#### 选项设置

`mysql_options()` 是 MySQL C API 中用于设置连接选项的重要函数。它在建立连接之前调用，用于配置连接的各种参数。

函数原型如下：

```c
int mysql_options(MYSQL *mysql, enum mysql_option option, const void *arg);
```

**参数：**

- `mysql`: MYSQL 结构指针
- `option`: 要设置的选项
- `arg`: 选项值（类型取决于具体选项）

**返回值：**

- 成功：0
- 失败：非0

##### 连接和超时选项

```c
MYSQL mysql;
mysql_init(&mysql);

// 设置连接超时（秒）
unsigned int timeout = 5;
mysql_options(&mysql, MYSQL_OPT_CONNECT_TIMEOUT, &timeout);

// 设置读超时（秒）
unsigned int read_timeout = 10;
mysql_options(&mysql, MYSQL_OPT_READ_TIMEOUT, &read_timeout);

// 设置写超时（秒）
unsigned int write_timeout = 10;
mysql_options(&mysql, MYSQL_OPT_WRITE_TIMEOUT, &write_timeout);

// 启用自动重连
my_bool reconnect = 1;
mysql_options(&mysql, MYSQL_OPT_RECONNECT, &reconnect);
```

#####  字符集和编码选项

```c
mysql_options(mycon, MYSQL_SET_CHARSET_NAME, "gbk");
//或
mysql_options(mycon,MYSQL_INIT_COMMAND, "SET NAMES gbk");
```

##### 本地化和时区设置

```c
// 设置时区
mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET time_zone = '+08:00'");

// 设置 SQL 模式
mysql_options(&mysql, MYSQL_INIT_COMMAND, 
              "SET SESSION sql_mode='STRICT_TRANS_TABLES,NO_ENGINE_SUBSTITUTION'");

// 设置隔离级别
mysql_options(&mysql, MYSQL_INIT_COMMAND, 
              "SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED");
```



#### 准备语句

##### 1. 什么是数据库准备语句？

- **预编译 SQL**：将 SQL 语句的结构（如 `SELECT`, `INSERT`）提前发送给数据库服务器编译，后续只需传递参数。
- **参数化查询**：通过占位符（如 `?` 或命名参数）代替直接拼接变量，避免 **SQL 注入** 攻击。
- **性能优化**：重复执行相同结构的 SQL 时，复用编译后的执行计划，减少数据库解析开销。

##### 2. 为什么使用准备语句？

- **安全性**：防止 SQL 注入（恶意用户通过输入特殊字符篡改 SQL 逻辑）。
- **效率**：减少重复编译的开销，尤其适用于高频执行的查询。
- **可维护性**：代码更清晰，参数与 SQL 逻辑分离。

##### 使用准备语句查询结果

```cpp
	MYSQL* con = get_con();

	MYSQL_STMT* stmt = mysql_stmt_init(con);

	const char* sql = "SELECT empno,job FROM emp";
	if (0 != mysql_stmt_prepare(stmt, sql, strlen(sql))) {
		printf("mysql stmt prepare failed!\n");
		return -1;
	}


	if (0 != mysql_stmt_execute(stmt)) {
		printf("stmt execute failed~\n");
		return -1;
	}


	MYSQL_BIND binds[2] = {0};
	binds[0].buffer_type = MYSQL_TYPE_LONG;
	binds[0].buffer = malloc(sizeof(int));
	//binds[0].buffer_length = sizeof(int);

	binds[1].buffer_type = MYSQL_TYPE_STRING;
	binds[1].buffer = calloc(1,20);
	binds[1].buffer_length = 20;

	if (0 != mysql_stmt_bind_result(stmt, binds)) {
		printf("stmt bind result failed~\n");
		return -1;
	}
	while (mysql_stmt_fetch(stmt) == 0) {
		printf("%d  ", *(int*)binds[0].buffer);
		printf("%s\n", (char*)binds[1].buffer);
	}
	mysql_stmt_free_result(stmt);
	for (int i = 0;i < 2;i++) {
		free(binds[i].buffer);
		binds[i].buffer = NULL;
	}
	mysql_stmt_close(stmt);
```

##### 插入准备语句

```cpp
	MYSQL* con = get_con();

	MYSQL_STMT* stmt = mysql_stmt_init(con);

	const char* sql = "INSERT INTO emp(empno,ename,job,sal) VALUES(?,?,?,?)";
	if (0 != mysql_stmt_prepare(stmt, sql, strlen(sql))) {
		printf("mysql stmt prepare failed!\n");
		return -1;
	}

	int empno = 5678;
	char ename[] = "hello";
	char obj[] = "teacher";
	double sal = 15000.62;

	MYSQL_BIND params[4] = {0};
	params[0].buffer = &empno;
	params[0].buffer_type = MYSQL_TYPE_LONG;
	
	params[1].buffer = ename;
	params[1].buffer_type = MYSQL_TYPE_STRING;
	params[1].buffer_length = strlen(ename);

	params[2].buffer = obj;
	params[2].buffer_type = MYSQL_TYPE_STRING;
	params[2].buffer_length = strlen(obj);

	params[3].buffer = &sal;
	params[3].buffer_type = MYSQL_TYPE_DOUBLE;

	if (0 != mysql_stmt_bind_param(stmt, params)) {
		printf("bind params failed~%s\n",mysql_stmt_error(stmt));
		return -1;
	}

	if (0 != mysql_stmt_execute(stmt)) {
		printf("stmt execute failed~%s\n",mysql_stmt_error(stmt));
		return -1;
	}

	mysql_stmt_close(stmt);
```



## MySQL Connector/C 9.2

MySQL Connector/C是一个MySQL数据库连接器，用于C++应用程序连接MySQL服务器。

### Windows

#### 下载

直接在MySQL官网下载[MySQL :: Download Connector/C++](https://dev.mysql.com/downloads/connector/cpp/)，有Release版本和Debug版本，写代码是用什么版本就下载什么版本，也可以都下载，配置方式一样！

![image-20250308144720608](./assets/image-20250308144720608.png)

我这里以Release版本为例，点击之后进入如下图所示界面，点击`No thanks, just start my download.`进行下载。

![image-20250308144911655](./assets/image-20250308144911655.png)

下载完成后解压，解压后的目录如下图。

![image-20250308145322950](./assets/image-20250308145322950.png)

#### 配置

##### Vs2022

+ 将头文件目录`F:\Tools\mysql-connector-c++-9.2.0-winx64\include`配置到包含目录
+ 将库文件目录`F:\Tools\mysql-connector-c++-9.2.0-winx64\lib64\vs14`配置到库目录

![image-20250308163041814](./assets/image-20250308163041814.png)

+ 将库`mysqlcppconn.lib`配置到，链接器/输入/附加依赖项。

  ![image-20250308145956332](./assets/image-20250308145956332.png)

##### CMake



### Linux

直接使用命令进行安装即可！

```shell
sudo apt install libmysqlcppconn-dev
```



### 使用

#### 连接

+ 引入如下头文件

```cpp
#include "jdbc/mysql_connection.h"
#include "jdbc/mysql_driver.h"
#include "jdbc/cppconn/statement.h"
#include "jdbc/cppconn/prepared_statement.h"
```

+ 连接数据库

```cpp
void test_connect()
{
	//初始化驱动
	sql::mysql::MySQL_Driver* driver = nullptr;
	sql::Connection* con = nullptr;

	//获取驱动实例
	driver = sql::mysql::get_mysql_driver_instance();
	if (!driver) {
		std::cerr << "driver is null" << std::endl;
	}

	//连接mysql
	con = driver->connect("tcp://localhost:3306", "root", "123456");
}
```

+ 注意：连接失败会抛出异常，所以必须使用try快来捕获异常。

```cpp
int main()
{
	try {
		test_connect();
	}
	catch (const std::exception& e) {
		std::cerr <<"Exception:" << e.what() << std::endl;
	}
	return 0;
}
```

#### 查询

```cpp
	//创建SQL语句
	sql::Statement* stmt =  con->createStatement();
	stmt->execute("USE hdy");			//选择数据库，返回值好像没用???
	stmt->execute("SET NAMES gbk");		//设置客户端字符集，不设置会乱码,因为客户端默认是gbk的		

	//查询
	sql::ResultSet* res = stmt->executeQuery("SELECT * FROM emp");
	//获取查询到的行数
	std::cout << "rowsCount is " << res->rowsCount() << std::endl;;
	//查找字段所在的列数(序号，从1开始，0表示没有找到平)
	std::cout << "findColumn is " << res->findColumn("job") << std::endl;
	//遍历结果集
	while (res->next()) {
		std::cout << res->getInt("empno") << " ";
		std::cout << res->getString("ename") << " ";
		std::cout << res->getString("job") << " ";
		std::cout << res->getInt("mgr") << " ";
		std::cout << res->getString("hiredate") << " ";
		std::cout << res->getDouble("sal") << " ";
		std::cout << res->getDouble("comm") << " ";
		std::cout << res->getInt("deptno") << " ";
		std::cout << std::endl;
	}
	//查询emp表记录条数
	res = stmt->executeQuery("SELECT COUNT(*) FROM emp");
	if (res->next()) {
		std::cout << "emp count is " << res->getInt(1);
	}

```

#### 插入

```cpp
	con->setAutoCommit(0);	//关闭自动提交(开启事务)
	sql::PreparedStatement* prep_stmt = con->prepareStatement("INSERT INTO emp(empno,ename,job,hiredate,sal,deptno) \
VALUES(?,?,?,?,?,?)");
	prep_stmt->setInt(1,1234);
	prep_stmt->setString(2,"玩蛇haha");
	prep_stmt->setString(3,"teacher");
	prep_stmt->setString(4,"2025-03-08");
	prep_stmt->setDouble(5,15000);
	prep_stmt->setInt(6,20);
	try {
		auto count = prep_stmt->executeUpdate();
		std::cout << "count is " << count << std::endl;
		con->commit();
	}
	catch (const std::exception& e) {
		con->rollback();
		std::cerr << "insert exception:" << e.what() << std::endl;
	}
```

#### 更新

```cpp
	con->setAutoCommit(1);	//打开自动提交
	prep_stmt = con->prepareStatement("UPDATE emp SET job=?,deptno=? WHERE empno=?");
	prep_stmt->setString(1, "讲师");
	prep_stmt->setInt(2, 30);
	prep_stmt->setInt(3, 1234);
	try {
		prep_stmt->executeUpdate();
		std::cout << "update success!" << std::endl;
	}
	catch (const std::exception&e) {
		std::cerr << "update exception:" << e.what() << std::endl;
	}
```

#### 删除

```cpp
	try {
		auto cnt = stmt->executeUpdate("DELETE FROM emp WHERE empno = 1234");
		if (cnt > 0) {
			std::cout << "delete success!" << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "delete exception:" << e.what() << std::endl;
	}
```

## ORM(对象关系映射)

### 1、什么是ORM

ORM，即Object-Relational Mapping（对象关系映射），它的作用是在关系型数据库和业务实体对象之间作一个映射，这样，我们在具体的操作业务对象的时候，就不需要再去和复杂的SQL语句打交道，只需简单的操作对象的属性和方法。

### 2、为什么会出现ORM思想

先从项目中数据流存储形式这个角度说起.简单拿MVC这种分层模式.来说. Model作为数据承载实体. 在用户界面层和业务逻辑层之间数据实现面向对象OO形式传递. 当我们需要通过Control层分发请求把数据持久化时我们会发现. 内存中的面向对象的OO如何持久化成关系型数据中存储一条实际数据记录呢？

面向对象是从软件工程基本原则(如耦合、聚合、封装)的基础上发展起来的，而关系数据库则是从数学理论发展而来的. 两者之间是不匹配的.而ORM作为项目中间件形式实现数据在不同场景下数据关系映射. 对象关系映射（Object Relational Mapping，简称ORM）是一种为了解决面向对象与关系数据库存在的互不匹配的现象的技术.ORM就是这样而来的.



![img](./assets/v2-db533afb92b9d701330d71c16cef462c_720w.webp)



需要更多的学习资料私信小编（需要）即可免费领取

### 3、优缺点

**优势**

第一：隐藏了数据访问细节，“封闭”的通用数据库交互，ORM的核心。他使得我们的通用数据库交互变得简单易行，并且完全不用考虑该死的SQL语句。快速开发，由此而来。

第二：ORM使我们构造固化数据结构变得简单易行。在ORM年表的史前时代，我们需要将我们的对象模型转化为一条一条的SQL语句，通过直连或是DB helper在关系数据库构造我们的数据库体系。而现在，基本上所有的ORM框架都提供了通过对象模型构造关系数据库结构的功能。这，相当不错。

**缺点**

第一：无可避免的，自动化意味着映射和关联管理，代价是牺牲性能（早期，这是所有不喜欢ORM人的共同点）。现在的各种ORM框架都在尝试使用各种方法来减轻这块（LazyLoad，Cache），效果还是很显著的。

第二：面向对象的查询语言(X-QL)作为一种数据库与对象之间的过渡,虽然隐藏了数据层面的业务抽象,但并不能完全的屏蔽掉数据库层的设计,并且无疑将增加学习成本.

第三：对于复杂查询，ORM仍然力不从心。虽然可以实现，但是不值的。视图可以解决大部分calculated column，case ，group，having,order by, exists，但是查询条件(a and b and not c and (d or d))。

世上没有驴是不吃草的(又想好又想巧,买个老驴不吃草)，任何优势的背后都隐藏着缺点，这是不可避免的。问题在于，我们是否能容忍缺点。

## ormpp

ormpp是modern c++(c++11/14/17)开发的ORM库，目前支持了三种数据库：mysql, postgresql和sqlite，ormpp主要有以下几个特点：

1. header only
2. cross platform
3. unified interface
4. easy to use
5. easy to change database

你通过ormpp可以很容易地实现数据库的各种操作了，大部情况下甚至都不需要写sql语句。ormpp是基于编译期反射的，会帮你实现自动化的实体映射，你再也不用写对象到数据表相互赋值的繁琐易出错的代码了，更酷的是你可以很方便地切换数据库，如果需要从mysql切换到postgresql或sqlite只需要修改一下数据库类型就可以了，无需修改其他代码。

### 下载构建配置

从[ormpp](https://github.com/qicosmos/ormpp)下载并解压最新版本。

+ git拉取

```css
git clone https://github.com/qicosmos/ormpp.git
```

+ 进入ormpp目录

```css
cd ormpp

cmake -B build -DENABLE_MYSQL=ON -DCMAKE_BUILD_TYPE=Debug -DMYSQL_INCLUDE_DIR="F:\MySQL\MySQL8.4\include"
```

> 如果出现错误则需要配置mysql库目录： Found relative path while evaluating include directories of "ZERO_CHECK":"MYSQL_INCLUDE_DIR-NOTFOUND"



## sqlpp11

[sqlpp11](https://github.com/rbock/sqlpp11) 是 C++ 的类型安全 SQL 模版库，是一个挺好用的ORM框架。

### 下载构建配置

从[Tags · rbock/sqlpp11 (github.com)](https://github.com/rbock/sqlpp11/tags)下载并解压最新版本。

在目录中执行以下命令：

```shell
cmake -B build -DBUILD_MYSQL_CONNECTOR=ON
cmake --build build --target install
```

最后一步将构建库并在系统范围内安装它，因此它可能需要管理员权限。

> 前置条件：
>
> 1. 必须安装git以自动拉取 [Howard Hinnant 的日期库](https://github.com/HowardHinnant/date)
> 2. 必须安装python3，并且还得安装`pyparsing`模块。
>    + 安装pyparsing ：`pip install pyparsing`
>    + 可能需要更新pip：`python -m pip install --upgrade pip`
>    + 如果在使用pip时，提示`moduleNotFoundError:No module named 'pip'`，则需要先安装pip：`python -m ensurepip`
> 3. 必须配置好mysql开发环境(配置好环境变量)

如果在执行`cmake --build build --target install`有报错，部分报错截图如下：

![image-20240321141009406](./assets/image-20240321141009406.png)

则需要在sqlpp11中的CMakeLists.txt中添加NOMINMAX宏，如下图所示：

![image-20240321142233701](./assets/image-20240321142233701.png)

添加好之后，重新执行cmake命令：

```shell
cmake -B build -DBUILD_MYSQL_CONNECTOR=ON
cmake --build build --target install
```

构建成功后，库将安装到如下位置。

![image-20240321142405586](./assets/image-20240321142405586.png)

![image-20240319032736065](./assets/image-20240319032736065-1710790133310-1.png)

接下来把如下两个路径配置到环境变量path：

```css
C:\Program Files (x86)\sqlpp11
C:\Program Files (x86)\sqlpp11\bin
```

OK！至此，sqlpp11配置完成！

### CMake项目配置 

把你要操作的表的创建语句，放到sql文件中，如[test.sql](./assets/test.sql)：

```sql
-- 创建数据表
CREATE TABLE IF NOT EXISTS dept (
	deptno		SMALLINT  PRIMARY KEY,
	dname		VARCHAR(14) ,
	loc			VARCHAR(13) ) ;
	
CREATE TABLE IF NOT EXISTS emp (
	empno		SMALLINT  PRIMARY KEY,
	ename		VARCHAR(10),
	job			VARCHAR(9),
	mgr			SMALLINT,
	hiredate	DATE,
	sal			DECIMAL(7,2),
	comm		SMALLINT,
	deptno		SMALLINT  REFERENCES DEPT );
	
CREATE TABLE IF NOT EXISTS bonus (
	enamE		VARCHAR(10),
	job			VARCHAR(9) ,
	sal			DECIMAL(7,2),
	comm		SMALLINT ) ;
	
CREATE TABLE IF NOT EXISTS salgrade ( 
	grade		SMALLINT,
	losal		SMALLINT,
	hisal		SMALLINT );
```

然后打开cmd，并进入mtest.sql目录，执行如下命令：(会根据sql中的创建语句，生成头文件)

```shell
python "C:\Program Files (x86)\sqlpp11\bin\sqlpp11-ddl2cpp" test.sql mytest db_test
```

+ python 必须为python3
+ "C:\Program Files (x86)\sqlpp11\bin\sqlpp11-ddl2cpp" 是一个python脚本文件
+ test.sql 你要使用的sql文件，里面包含需要操作的表的创建语句。
+ mytest 为生成的头文件名称
+ db_test 数据库名称(对应到头文件中的命名空间名)

生成的mytest.h头文件大概内容如下图所示：

![image-20240328134712700](./assets/image-20240328134712700.png)

Dept_明明空间中定义了dept表中所有字段的声明。

Dept 结构体定义了dept表的结构。



CMakeLists.txt文件如下：

```cmake
cmake_minimum_required(VERSION 3.5.0)

project(sqlpp11_demo_1 VERSION 0.1.0 LANGUAGES C CXX)
# 强制要求支持C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 取消C语言标准的 min max宏
add_definitions(-DNOMINMAX)
# MySQL头文件目录
include_directories("F:/Tools/MySQL/MySQL Server 8.3/include")
# MySQL库文件目录
link_directories("F:/Tools/MySQL/MySQL Server 8.3/lib")
# 查找sqlpp11库(配置环境变量之后才能查找到)
find_package(sqlpp11 REQUIRED)
# 在当前目录，查找所有源文件，并保存到SOURCE_FILES变量中
aux_source_directory(. SOURCE_FILES)
# 指定项目源文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
# 把sqlpp11库 和libmysql库连接到可执行程序
target_link_libraries(${PROJECT_NAME} PRIVATE sqlpp11::sqlpp11 libmysql)
```



然后创建`app.cpp`文件，写入main函数，后续代码，都在此文件中进行编写。



### sqlpp11使用

#### 1. 连接数据库

sqlpp11支持**mysql、sqlite3、postgresql**三种数据库，所以连接的时候，需要选择对应的连接器。不同的连接器所属的命名空间不同。

##### 普通连接

要连接MYSQL，需要包含头文件：

```cpp
#include "sqlpp11/mysql/mysql.h"
```

如果在多线程环境中使用，则需要初始化mysql库：

```cpp
//定义在全局就好
const auto library_raii = sqlpp::mysql::scoped_library_initializer_t{0, nullptr, nullptr};
```

接着就可以通过连接配置对象来配置连接相关信息：

```cpp
int main(int argc, char const *argv[])
{    
	sql::connection_config config;
    config.host = "127.0.0.1";
    config.port = 33061;
    config.user = "root";
    config.password = "123456";
    config.database = "test";
```

`sql`是`sqlpp::mysql`的别名，是为了免去每次都写`sqlpp::mysql`这么长的命名空间的烦恼：

```cpp
namespace sql = sqlpp::mysql;
```

接下来就可以正式连接数据库了：

```cpp
    try
    {
        sql::connection db(config);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
```

`sql::connection`是一个连接类型，把连接配置传入连接对象即可建立连接。

> 注意：sqlpp11库是通过抛出异常来进行错误处理的，所以每一步操作都必须使用try语句进行异常捕获。

##### 连接池连接

普通的连接应该单线程程序足够了，但是在多线程程序中，每个线程必须有一个独立的连接。而数据库连接的创建和销毁是比较耗时，所以可以使用连接池**提高性能、优化资源分配、提高系统的稳定性和响应速度**。

- 提高性能。数据库连接池通过在应用程序启动时初始化一部分数据库连接，避免了每次进行CRUD操作时创建和销毁数据库连接的开销，从而提高了系统的性能。

> CRUD 是指在做计算处理时的增加(Create)、读取(Read)、更新(Update)和删除(Delete)几个单词的首字母简写

- 优化资源分配。在多应用共享同一数据库的系统中，通过数据库连接池的配置，可以限制每个应用的最大可用数据库连接数，避免某个应用独占所有数据库资源。

- 提高系统的稳定性。在高并发情况下，直接创建数据库连接可能导致系统无法创建更多连接，从而引发系统崩溃。而使用连接池可以有效地控制并发请求的数量，保证系统的稳定性。

- 提高响应速度。使用连接池可以减少等待数据库连接的时间，因为连接池已经预先创建了一些连接对象供用户使用。用户需要连接数据库时，只需从连接池中获取一个连接进行使用，使用完毕后归还给连接池，这样实现了资源的重用，节省了频繁创建和销毁连接的时间，从而提升了系统的响应速度。

为了使用连接池，先把配置对象改为智能指针对象：

```cpp
auto config = std::make_shared<sql::connection_config>();
```

接着将config传入`sql::connection_pool`连接池对象：

```cpp
sql::connection_pool pool(config,10);
```

需要数据库连接时，调用pool的`get()`方法即可：

```cpp
    try
    {
        sql::pooled_connection db =  pool.get();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
```

> 注意：池连接和普通连接的类型不一样，普通连接类型为`sql::connection`，而池连接为`sql::pooled::connection`。

#### 2.查询

##### 2.1 基本查询

首先，需要定义一个表对象，用来进行查询。

```cpp
void test_select(sql::connection_pool &pool)
{
   //定义表对象 
   db_test::Emp emp{};
```

然后，从连接池中获取连接。

```cpp
   auto &db = pool.get();
```

接着，就可以进行查询了。

```cpp
   //查询emp表
   auto& result = db(sqlpp::select(all_of(emp))
                     .from(emp)
                     .unconditionally());
```

> select函数需要包含头文件 ==> #include "sqlpp11/sqlpp11.h"
>
> + select 函数需要传入查询的字段，返回查询对象，以进行链式操作。all_of表示所有字段。
> + from 函数需要传入表对象
> + unconditionally 函数表示没有查询(where)条件

最后，遍历结果集，拿到每条记录；而每条记录的所有字段都可以直接通过row的成员拿到。

```cpp
   //遍历结果集，获取每条记录
   for(auto& row : result)
   {
	   std::cout << row.ename << "\t" << row.sal << "\t" << row.hiredate << "\t" << row.deptno << std::endl;
   }
}
```

通过row获取到的数据是字段类型，如果需要获取底层类型的数据，可以通过vlaue函数访问。

```cpp
	   std::cout 
           << row.ename.value() << "\t" 
           << row.sal.value() << "\t" 
           << row.hiredate << "\t" 
           << row.deptno.value() << std::endl;
```

> 可以通过typeid获取具体的类型名：   typeid(row.ename.value()).name();

```cpp
	   std::cout 
           << typeid(row.ename.value()).name() << "\t" 		//std::string
           << typeid(row.sal.value()).name() << "\t" 		//double
           << typeid(row.hiredate.value()).name()<< "\t" 
           << typeid(row.deptno.value()).name() << std::endl;//uint64_t
```

在上面的代码中，发现hiredate并没有通过value取值，因为hiredate是日期类型，获取之后通过cout输出不了。

但是可以通过字符串流`std::stringstream`转成字符串。

```cpp
 std::stringstream ss;
 ss << row.hiredate;
 std::cout << ss.str();
```

##### 2.2 别名

###### 查询指定字段

在上面的代码中我们使用`all_of()`查询了emp表的所有字段，如果只想查询指定的字段，只需要在`select()`函数中写入指定字段即可！

```cpp
auto &result = db(sqlpp::select(emp.ename,emp.sal,emp.hiredate,emp.deptno)
                          .from(emp)
                          .unconditionally());
```

###### 给字段取别名

sqlpp11给我们提供了一些内置别名(a~z，left，right)共28个，通过字段的`as()`函数即可使用这些别名。

当然也可以自定义别名，使用`SQLPP_ALIAS_PROVIDER()`带参宏定义别名。

```cpp
SQLPP_ALIAS_PROVIDER(emp_sal)	//自定义别名，不能放到函数内部
    
void test_alias_select(sql::connection_pool& pool)
{
    // 定义表对象
    db_test::Emp emp{};
    // 查询emp表
    auto &db = pool.get();

    auto &result = db(sqlpp::select(emp.ename.as(sqlpp::alias::a)  //这里使用内置别名
                                   ,emp.sal.as(emp_sal)		//这里写入自定义的别名
                                   ,emp.hiredate
                                   ,emp.deptno)
                          .from(emp)
                          .unconditionally());
    // 遍历结果集，获取每条记录
    for (auto &row : result)
    {
        std::cout << row.a<< "\t" 		//这里使用别名a
            << row.emp_sal << "\t" 		//这里使用别名emp_sal
            << row.hiredate << "\t" 
            << row.deptno << std::endl;
    }
}
```

对于未命名的字段，必须使用别名才好处理。

+ 把`(e.sal * 12)`取别名为`e.sal`，访问时直接使用row.sal即可获得年薪

```cpp
	for (auto& row : db(sqlpp::select(e.ename, (e.sal * 12).as(e.sal))
		.from(e)
		.unconditionally()))
	{
		std::cout << row.ename << "\t" << row.sal << std::endl;
	}
```

+ 当然，如果你还需要查看月薪，那必须换一种方式

```cpp
SQLPP_ALIAS_PROVIDER(year_sal)
...    
for (auto& row : db(sqlpp::select(e.ename,e.sal, (e.sal * 12).as(year_sal))
		.from(e)
		.unconditionally()))
	{
		std::cout << row.ename << "\t" << row.sal<<"\t"<<row.year_sal << std::endl;
	}
```



###### 给表取别名

```cpp
    //给表取别名
    auto mgr = emp.as(sqlpp::alias::a);

	for (const auto& row : db(
           select(emp.ename,mgr.ename.as(mgr_name))
           .from(emp.join(mgr).on(emp.empno == mgr.empno))
           .unconditionally()
		))
	{
		std::cout << row.ename<< "\t" << row.mgr_name<< std::endl;
	}
```

##### 2.3 条件查询

+ 查询工资等于3000的员工

```cpp
	for (auto& row : db(sqlpp::select(sqlpp::all_of(emp))
		.from(emp)
		.where(emp.sal == 3000)))
	{
		std::cout << row.ename << "\t" << row.sal << std::endl;
	}
```

+ 查询工资在1200到1800之间的员工(包含1200和1800)

```cpp
	for (auto& row : db(sqlpp::select(sqlpp::all_of(emp))
		.from(emp)
		.where(emp.sal >= 1200 && emp.sal <= 1800))) {
		std::cout << row.ename << "\t" << row.sal << std::endl;
	}
```

+ 查询姓名中包含`L`的员工

```cpp
	for (auto& row : db(sqlpp::select(sqlpp::all_of(emp))
		.from(emp)
		.where(emp.ename.like("%L%")))) {
		std::cout << row.ename << "\t" << row.sal << std::endl;
	}
```

+ 查询没有奖金的员工

```cpp
	for (auto& row : db(sqlpp::select(sqlpp::all_of(emp))
		.from(emp)
		.where(sqlpp::is_null(emp.comm)))) {
		std::cout << row.ename << "\t" << row.sal << std::endl;
	}
```

+ 查询工资为800 或 3000 或 5000的员工

```cpp
	for (auto& row : db(sqlpp::select(sqlpp::all_of(emp))
		.from(emp)
		.where(emp.sal.in(800,3000,5000)))) {
		std::cout << row.ename << "\t" << row.sal << std::endl;
	}
```



##### 2.4. 排序查询

在`where()`或者`  unconditionally()`函数后面使用`order_by()`函数即可指定排序字段和方式。

```cpp
    auto &result = db(sqlpp::select(emp.ename, emp.sal, emp.hiredate, emp.deptno)
                          .from(emp)
                          .unconditionally()
                          .order_by(emp.deptno.asc(),emp.sal.desc())
                          );
```



##### 2.5. 分页查询

分页子句必须放到语句的最后面，`limit()`指定显示的记录条数、`offset()`指定偏移量。`limit`函数可以单独使用，也可以搭配`offset`函数使用。

**limit单独使用**

单独使用，offset默认为0，也就是说从第一条数据开始显示，共显示5u条。

<font color=red>注意：limit和offset的参数类型必须为无符号整型(unsigned int)</font>

```cpp
    auto &result = db(sqlpp::select(emp.ename, emp.sal, emp.hiredate, emp.deptno)
                          .from(emp)
                          .unconditionally()
                          .limit(5u));			//从第1条数据开始，共显示5条
```

**搭配offset使用**

搭配offset使用，表示从offset条数据开始显示，共显示limit条。

```cpp
    auto &result = db(sqlpp::select(emp.ename, emp.sal, emp.hiredate, emp.deptno)
                          .from(emp)
                          .unconditionally()
                          .limit(5u).offset(2u));	//从第2条数据开始，共显示5条
```



##### 2.6. 聚合函数

###### count

count函数用来统计记录条数，有两种使用方式。

```cpp
sqlpp::count('*');
sqlpp::count(emp.empno));

for (auto &row : result)
{
    std::cout << row.count << std::endl;	//通过row.count访问
}
```

如果在一个查询中，调用多次`count()`函数，则必须取别名，否则多个个的字段名都是count，会发生冲突。

```cpp
SQLPP_ALIAS_PROVIDER(total_count)
SQLPP_ALIAS_PROVIDER(total_size)

void test_func_1_select(sql::connection_pool &pool)
{
    // 定义表对象
    db_test::Emp emp{};
    // 查询emp表
    auto &db = pool.get();
    
    auto &result = db(sqlpp::select(
        sqlpp::count('*').as(total_count), 			//取别名
        sqlpp::count(emp.empno).as(total_size))		//取别名
                          .from(emp)
                          .unconditionally());

    // 遍历结果集，获取每条记录
    for (auto &row : result)
    {
        //通过别名访问
        std::cout << row.total_count << " " << row.total_size << std::endl;
    }
}
```

###### avg

求平均值。

```cpp
    std::cout << "===agv===" << std::endl;
	{
        auto &result = db(sqlpp::select(sqlpp::avg(emp.sal))
                              .from(emp)
                              .unconditionally());

        // 遍历结果集，获取每条记录
        for (auto &row : result){
            std::cout << "agv:" << row.avg << std::endl;
        }
    }
```

###### max

求最大值。

```cpp
    std::cout << "===max===" << std::endl;
	{
        auto &result = db(sqlpp::select(sqlpp::max(emp.sal))
                              .from(emp)
                              .unconditionally());

        // 遍历结果集，获取每条记录
        for (auto &row : result){
            std::cout << row.max<< std::endl;
        }
    }
```

###### min

求最小值。

```cpp
    std::cout << "===min===" << std::endl;
	{
        auto &result = db(sqlpp::select(sqlpp::min(emp.sal))
                              .from(emp)
                              .unconditionally());

        // 遍历结果集，获取每条记录
        for (auto &row : result){
            std::cout << row.min<< std::endl;
        }
    }
```

###### sum

求总和。

```cpp
    std::cout << "===sum===" << std::endl;
	{
        auto &result = db(sqlpp::select(sqlpp::sum(emp.sal))
                              .from(emp)
                              .unconditionally());

        // 遍历结果集，获取每条记录
        for (auto &row : result){
            std::cout  << row.sum<< std::endl;
        }
    }
```



##### 2.7. 分组查询

+ 统计每个部门人数，输出部门编号和人数。

```cpp
    auto &result = db(sqlpp::select(emp.deptno,sqlpp::count('*'))
                          .from(emp)
                          .unconditionally()
                          .group_by(emp.deptno)     
    );

    // 遍历结果集，获取每条记录
    for (auto &row : result)    
    {
        std::cout << row.deptno << "\t" << row.count << std::endl;
    }
```

+ 输出部门平均薪资大于1500的部门。

```cpp
    auto &result = db(sqlpp::select(emp.deptno,sqlpp::avg(emp.sal))
                          .from(emp)
                          .unconditionally()
                          .group_by(emp.deptno)
                          .having(sqlpp::avg(emp.sal) > 1500)
    );
```

这里使用having语句在group by分支之后进行筛选，值得注意的是having中使用了平均薪资字段`sqlpp::avg(emp.sal)>1500`，形式比较复杂。

可以提前保存avg函数的结果，方便使用。

```cpp
    auto& avg_sal = sqlpp::avg(emp.sal);
    auto &result = db(sqlpp::select(emp.deptno,avg_sal)
                          .from(emp)
                          .unconditionally()
                          .group_by(emp.deptno)
                          .having(avg_sal > 2000)
    );
```

> 注意：这里并没有别名，指定别名可以用如下代码：`    auto& avg_sal = sqlpp::avg(emp.sal).as(avg_sal);`

##### 2.8. 多表查询

先来看一个有问题的查询。

```cpp
	for (const auto& row : db(
		select(emp.deptno,dept.deptno)
		.from(emp.join(dept).on(emp.deptno == dept.deptno))
		.unconditionally()))
	{
		std::cout << row.deptno << std::endl;
	}
```

当你连接表并且有个相同名称的列时，会产生编译错误。因为在一个查询中不能有两个相同的字段名称。

```css
 error C2385: 对“deptno”的访问不明确。
```

使用别名也很方便。

```cpp
SQLPP_ALIAS_PROVIDER(dept_dno)
select(emp.deptno,dept.deptno.as(dept_dno));
std::cout << row.deptno << "\t" << row.dept_dno << std::endl;
```

+ 查看员工姓名、薪资以及所在部门名称

```cpp
	for (const auto& row : db(
		select(emp.ename, emp.sal, dept.dname)
		.from(emp.join(dept).on(emp.deptno == dept.deptno))
		.unconditionally()))
	{
		std::cout << row.ename << " \t " << row.sal << " \t " << row.dname << std::endl;
	}
```

+ 查看员工姓名、薪资以及薪资等级

```cpp
	for (const auto& row : db(
		select(emp.ename, emp.sal, salgrade.grade)
		.from(emp.join(salgrade).on(emp.sal >= salgrade.losal && emp.sal <= salgrade.hisal))
		.unconditionally()))
	{
		std::cout << row.ename << " " << row.sal << " " << row.grade << std::endl;
	}
```

+ 查看员工姓名以及领导的姓名

```cpp
    //给表取别名
    auto mgr = emp.as(sqlpp::alias::a);

	for (const auto& row : db(
           select(emp.ename,mgr.ename.as(mgr_name))
           .from(emp.join(mgr).on(emp.empno == mgr.empno))
           .unconditionally()
		))
	{
		std::cout << row.ename<< "\t" << row.mgr_name<< std::endl;
	}
```



##### 2.9. 子查询

+ 查询工资比`ALLEN`的工资高的员工。

```cpp
    auto e1 = emp.as(sqlpp::alias::a);
    for (auto& row : db(
        select(emp.ename,emp.sal)
        .from(emp)
        .where(emp.sal > select(e1.sal).from(e1).where(e1.ename == "ALLEN"))
        //使用verbatim也可以
        //.where(sqlpp::verbatim<sqlpp::floating_point>("emp.sal") > subquery)
    ))
    {
        std::cout << row.ename << "\t" << row.sal << std::endl;
    }
```

或者

```cpp
   auto e1 = emp.as(sqlpp::alias::a);
   //先定义子查询
   auto subquery = select(e1.sal).from(e1).where(e1.ename == "ALLEN");
   for (auto& row : db(
       select(emp.ename,emp.sal)
       .from(emp)
       .where(emp.sal > subquery)
   ))
   {
       std::cout << row.ename << "\t" << row.sal << std::endl;
   }
```

+ 查询工资比任何管理工资都要高的员工信息

```cpp
        auto e1 = emp.as(sqlpp::alias::a);
        auto subquery = select(e1.sal).from(e1).where(e1.ename == "ALLEN");
        for (auto& row : db(
            select(emp.ename,emp.sal)
            .from(emp)
            .where(emp.sal > subquery)
        ))
        {
            std::cout << row.ename << "\t" << row.sal << std::endl;
        }
```

###### 在HAVING子句中使用子查询

+ 查询部门编号、员工人数、平均工资，并且要求这些部门的平均工资高于公司平均薪资。

```mysql
//有bug
SELECT deptno,COUNT(deptno) cnt,AVG(sal) avgsal 
FROM emp 
GROUP BY deptno
HAVING avgsal>
(
	SELECT AVG(sal) FROM emp
);

   auto subquery = sqlpp::select(sqlpp::avg(emp.sal))
                        .from(emp)
                        .unconditionally();

    for (auto &row : db(
             sqlpp::select(emp.deptno, sqlpp::count('*'), sqlpp::avg(emp.sal))
                 .from(emp)
                 .unconditionally()
                 .group_by(emp.deptno)
                 //.having(sqlpp::avg(emp.sal) > 100)
                 .having(sqlpp::verbatim<sqlpp::boolean>("(SELECT AVG(sal) FROM emp )"))
                 ))
    { 
        std::cout << "deptno:" << row.deptno << " count:" << row.count << " avg:" << row.avg << std::endl;
    }
```

+ 查询出所有部门中平均工资最高的部门名称及平均工资

```mysql
SELECT e.deptno,d.dname,ROUND(AVG(sal),2) avgsal
FROM emp e,dept d
WHERE e.deptno=d.deptno
GROUP BY e.deptno
HAVING avgsal>
(
    #查询出所有部门平均工资中最高的薪资
	 SELECT MAX(avgsal) FROM 
		(SELECT AVG(sal) avgsal FROM emp GROUP BY deptno) AS temp
)
```



###### 在SELECT字句中使用子查询

+ 查询出公司每个部门的编号、名称、位置、部门人数、平均工资

```mysql
#1多表查询
SELECT d.deptno,d.dname,d.loc,COUNT(e.deptno),AVG(e.sal)
FROM emp e,dept d
WHERE e.deptno=d.deptno
GROUP BY e.deptno;
#2
SELECT d.deptno,d.dname,d.loc,temp.cnt,temp.avgsal
FROM dept d,(SELECT deptno,COUNT(deptno) cnt,AVG(sal) avgsal FROM emp GROUP BY deptno) temp
WHERE d.deptno=temp.deptno;
#3 关联子查询
SELECT d.deptno,d.dname,d.loc,
(SELECT COUNT(deptno) FROM emp WHERE deptno=d.deptno) cnt,
(SELECT AVG(sal) FROM emp WHERE deptno=d.deptno) avgsal
FROM dept d;
```

sqlpp

```cpp
 //3 关联子查询
	for (auto &row : db(sqlpp::select(dept.deptno, dept.dname, dept.loc,
                                    sqlpp::select(sqlpp::count(emp.deptno))
                                    .from(emp).where(emp.deptno == dept.deptno),
                                    sqlpp::select(sqlpp::avg(emp.sal))
                                    .from(emp).where(emp.deptno == dept.deptno))
                                .from(dept)
                                .unconditionally()))
        {
            std::cout << row.deptno << "\t" << row.dname << "\t" 
            << row.loc << "\t" << row.avg << "\t" << row.count << std::endl;
        }
```

### 3. 插入

向emp中插入数据，`set()`函数中没有指定的字段，将被设置为默认值。

```cpp
db(insert_into(emp).set(emp.ename="sqlpp",emp.empno =3333,emp.sal=10000.26));
```

同时插入多条记录，<font color='red'>请注意，`add()`中每个字段都必须传递精确的类型，比如emp.sal需要浮点数，就不能传递整型，否则会报错。</font>

```cpp
    auto multi_insert = insert_into(emp).columns(emp.empno, emp.ename, emp.job, emp.sal);
    multi_insert.values.add(emp.empno = 5201, emp.ename = "name1", emp.job = "dev1", emp.sal = 8848.0);
    multi_insert.values.add(emp.empno = 5202, emp.ename = "name2", emp.job = default_value, emp.sal = null);
    multi_insert.values.add(emp.empno = 5203, emp.ename = value_or_null("name3"), emp.job = value_or_null("dev"), emp.sal = value_or_null<double>(10000));

    db(multi_insert);
```



### 4. 删除

```cpp
db(remove_from(emp).where(emp.ename.like("name%")));
```

USING语法：`DELETE FROM table_name USING table_name,... WHERE  `

```cpp
db(remove_from(emp).using_(emp, dept).where(emp.deptno == dept.deptno && dept.dname == "SALES"));
```

### 5. 更新

```cpp
//设置客户端字符集
db.execute("set character_set_client ='gbk'");
//执行更新
db(update(emp).set(emp.ename = "maye").where(emp.ename == "顽石"));
```

### 6. 准备语句

#### 插入

```cpp
    auto prepared_insert = db.prepare(
        insert_into(emp).set(
            emp.empno = parameter(emp.empno),
            emp.ename = parameter(emp.ename),
            emp.job = parameter(emp.job),
            emp.sal = parameter(emp.sal)));

    prepared_insert.params.empno = 74040;
    prepared_insert.params.ename = "74040";
    db(prepared_insert);

    prepared_insert.params.empno = 7403;
    prepared_insert.params.ename = "7403";
    prepared_insert.params.job = "7403";
    prepared_insert.params.sal = 7403;
    db(prepared_insert);
```

#### 删除

```cpp
    auto prepared_remove = db.prepare(
        remove_from(emp).where(emp.ename == parameter(emp.ename))
    );

    prepared_remove.params.ename = "7404";
    db(prepared_remove);
```

另一种，给参数命名的方式：

```cpp
SQLPP_ALIAS_PROVIDER(emp_no)
...
auto prepared_remove = db.prepare(
       remove_from(emp).where(
           emp.empno == parameter(sqlpp::integer(),emp_no));
       
   prepared_remove.params.emp_no = 7403;
   db(prepared_remove);
```

#### 更新

```cpp
    auto prepared_update = db.prepare(
        update(emp).set(emp.ename = "顽石").where(emp.ename == parameter(emp.ename))
    );
    prepared_update.params.ename = "maye";
    db(prepared_update);
```

#### 查询

```cpp
    db.execute("set character_set_client ='gbk'");

    auto prepared_select = db.prepare(
        select(all_of(emp)).from(emp).where(emp.deptno == parameter(emp.deptno))
    );
    prepared_select.params.deptno = 20;
    for(auto& row : db(prepared_select))
    {
        std::cout << row.empno << " " << row.ename << " " << row.job << " " << row.sal << std::endl;
    }
```

取别名

```cpp
SQLPP_ALIAS_PROVIDER(dept_no)
void test_prepare_select(sql::connection_pool &pool)
{
    ...
    db.execute("set character_set_client ='gbk'");

    auto prepared_select = db.prepare(
        select(all_of(emp)).from(emp).where(emp.deptno >= parameter(sqlpp::integer(),dept_no))
    );
    prepared_select.params.dept_no = 10;
    for(auto& row : db(prepared_select))
    {
        std::cout << row.empno << " " << row.ename << " " << row.job << " " << row.sal <<" "<<row.deptno<< std::endl;
    }
}
```

