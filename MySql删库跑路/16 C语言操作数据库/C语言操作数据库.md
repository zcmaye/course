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

## 1.2 C API基本流程

```c
#include<stdio.h>
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

+ mysql_num_rows获取查询到的数据行数(只对SELECT语句有效)，如果是非查询语句可以使用`mysql_affected_rows`获取受影响的行数
+ `mysql_field_count`和`mysql_num_fields`都可以获取查询到的列数，但是参数不一样

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

最后必须释放结果集，并管理mysql连接。

## 1.3 获取字段信息

### 1.3.1 获取字段名

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

### 1.3.2 获取字段/数据长度

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

