# MySQL 8.0 C API开发指南

# 1. C API基本接口

## 1.1 C API 基本数据结构

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

## 1.2 C API基本接口概述

```c
#include<mysql.h>
```

把mysql头文件包含到代码中。

```c
int main()
{
    //初始化MYSQL
    MYSQL* mycon = NULL;
    mycon = mysql_init(NULL);
    if(mycon == NULL)
    {
		printf("[error:%d]%s\n",mysql_errno(mycon),mysql_error(mycon));
        return -1;
    }
```

mycon是一个MySQL的连接指针，先初始化为NULL；接下来通过mysql_init分配或初始化一个适用于 mysql_real_connect() 的 MYSQL 对象。 如果参数是一个 NULL 指针，该函数分配、初始化并返回一个新对象。 否则，初始化对象并返回对象的地址。 如果 mysql_init() 分配了一个新对象，则在调用 mysql_close() 以关闭连接时将其释放。

```c
	mycon = mysql_real_connect(mycon,		//连接对象
                      "localhost",	//主机名或ip地址
                      "root",		//用户名
                      "123456",		//密码
                      "test",		//数据库名
                      3306,			//端口号
                      NULL,			//一般为NULL
                      0);			//通常为0
    if(mycon == NULL)
    {
		printf("[error:%d]%s\n",mysql_errno(mycon),mysql_error(mycon));
        return -1;
    }
```

mysql_real_connect() 尝试建立与在主机上运行的 MySQL 服务器的连接。 在执行任何其他需要有效 MYSQL 连接处理程序结构的 API 函数之前，客户端程序必须成功连接到服务器。

```c
	char query[]="SELECT * FROM emp";
	if(0 != mysql_query(mycon,query))
    {
        printf("[error:%d]%s\n",mysql_errno(mycon),mysql_error(mycon));
    }
```

连接成功之后，使用myql_query或mysql_real_query执行 SQL 语句。执行成功返回0，失败返回非零值。

通常，字符串必须由单个 SQL 语句组成，不带终止分号 ( `;`) 或`\g`. 如果启用了多语句执行，则字符串可以包含多个用分号分隔的语句。

+ [`mysql_query()`](https://dev.mysql.com/doc/c-api/8.0/en/mysql-query.html)执行以 \0  结尾的 SQL 语句字符串，不能用于包含二进制数据的语句；
+ [`mysql_real_query()`](https://dev.mysql.com/doc/c-api/8.0/en/mysql-real-query.html)可以执行以非\0结尾的字符串（二进制数据可能包含`\0`字符）

```c
 	MYSQL_RES* result = mysql_store_result(mycon);	//存储结果到客户端
	int row_num = mysql_num_rows(result);			//获取查询到的行数(只对SELECT语句有效)
	int col_num = mysql_field_count(mycon);			//返回最近查询的列数(结果集中的列数)
	//unsigned int mysql_num_fields(MYSQL_RES *result) //从结果集中获取查询到的字段数量
```

调用 mysql_real_query() 或 mysql_query() 后，必须为每个成功生成结果集的语句（SELECT、SHOW、DESCRIBE、EXPLAIN、CHECK TABLE 等）调用 mysql_store_result() 。 完成结果集后，还必须调用 mysql_free_result()。

```c
	if(row_num>0)
    {
        MYSQL_ROW row;
        while(row = mysql_fetch_row(result))
        {
            for(int i =0;i<col_num;i++)
            {
                printf("%s ",row[i]);
            }
            printf("\n");
        }
    }
```

`mysql_fetch_row()`检索结果集的下一行，如果没有更多行要检索(抓完了)则返回NULL;

通过字段数量可以遍历到每一个字段值。

```c
	mysql_free_result(result);
	mysql_close(mycon);
	return 0;
}
```

