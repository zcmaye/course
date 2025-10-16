# Redis概述

![[python] redis 模块 -- 实现 python 与 Redis 数据库的结合-CSDN博客](./assets/OIP-C.webp)

**REmote DIctionary Server(Redis) 是一个由 Salvatore Sanfilippo 写的 key-value 存储系统，是跨平台的非关系型数据库。是一个开源的、基于内存的、键值对存储系统，它通常被用作数据库、缓存和消息中间件。**

> 简单来说，你可以把它想象成一个速度极快的、结构灵巧的“超级哈希表”。

Redis 是一个开源的使用 ANSI C 语言编写、遵守 BSD 协议、支持网络、可基于内存、分布式、可选持久性的键值对(Key-Value)存储数据库，并提供多种语言的 API。

Redis 通常被称为数据结构服务器，因为值（value）可以是字符串(String)、哈希(Hash)、列表(list)、集合(sets)和有序集合(sorted sets)等类型。

# Redis安装

## 安装

将存储库添加到APT索引，更新它，并安装Redis Open Source：

```shell
sudo apt-get install lsb-release curl gpg
curl -fsSL https://packages.redis.io/gpg | sudo gpg --dearmor -o /usr/share/keyrings/redis-archive-keyring.gpg
sudo chmod 644 /usr/share/keyrings/redis-archive-keyring.gpg
echo "deb [signed-by=/usr/share/keyrings/redis-archive-keyring.gpg] https://packages.redis.io/deb $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/redis.list
sudo apt-get update
sudo apt-get install redis
```

查看redis服务是否已经启动：

```shell
sudo systemctl status redis
```

如果没有启动可以设置开机自启并启动：

```shell
sudo systemctl enable redis-server
sudo systemctl start redis-server
```

## 配置

Redis配置文件在`/etc/redis`目录中，配置文件名为`/redis.conf`。

首先将配置文件备份一份：

```shell
cp redis.conf redis.conf.bak
```

然后就可以放心大胆的修改配置文件了。

**必须要修改**的一些配置如下：

```properties
#监听的地址，默认是127.0.0.1，也就是说只能在本地访问，修改为0.0.0.0，可以在任意IP访问。
bind 0.0.0.0 ::
#密码，设置密码后访问Redis必须输入密码。
requirepass 123456
```

其他常见配置：

```properties
#监听端口
port 6379
#工作目录，配置文件、日志、持久化文件都会存放在这里
dir /var/lib/redis
#设置数据库数量
databases 16
#设置redis能使用的最大内存
maxmemory 512mb
#设置日志文件名
logfile /var/log/redis/redis-server.log
```

修改配置之后需要重启服务：

```shell
sudo systemctl restart redis
```

# Redis客户端

安装完Reids后，我们就可以操作Redis了，这需要用到Redis客户端，包括：

+ 命令行客户端
+ 图形化客户端
+ 编程客户端

## 命令行客户端

`redis-cli`是跟随这Redis安装的命令行客户端，直接可以使用。

```shell
redis-cli [OPTIONS] [cmd]
```

常用选项如下：

+ `-h 127.0.0.1`：指定要连接的redis IP地址，默认是127.0.0.1
+ `-p 6379`：指定要连接的redis的端口，默认是6379
+ `-a 123456`：指定访问密码

登录Redis：

```shell
redis-cli -h localhost -p 6379 -a 123456
```

也可以在连接成功后，再输入密码：

```shell
localhost:6379> AUTH 123456 
```

使用`quit`命令退出。

## 图形化客户端

[Navicat | Free Download Navicat Premium Lite](https://www.navicat.com/en/download/navicat-premium-lite)

# Redis数据结构

## 数据结构介绍  

Redis拥有非常丰富的数据结构，这是 Redis 区别于其他简单键值存储的关键。它不仅仅支持简单的字符串（String），还支持：

![image-20251014182159321](./assets/image-20251014182159321.png)

- **String（字符串）**： 最基础的类型，可以存文本、数字甚至二进制数据。
- **Hash（哈希）**： 类似于编程语言中的 Map，可以存储一组字段-值对，非常适合存储对象（如用户信息）。
- **List（列表）**： 有序的字符串集合，支持从两端插入或弹出元素，可实现栈或队列。
- **Set（集合）**： 无序的、不重复的字符串集合，支持求交集、并集、差集。
- **Sorted Set（有序集合）**： 每个元素都关联一个分数（score），可以根据分数排序。非常适合排行榜、延迟队列等场景。
- **GEO（地理空间）**： 储地理位置，计算距离，查询附近点。
- **Bitmaps（位图）**和 **HyperLogLogs**： 用于处理位级操作和基数统计（估算集合中不重复元素的个数），非常节省空间。

## 通用命令

要使用redis，需要通过命令与redis服务器进行交互。

### 查看命令

[所有命令](https://redis.io/docs/latest/commands/)都可以在[redis官网](https://redis.io/docs)查看，也可以登录后通过`help <command>`进行查看。

**官网**

![image-20251015151634652](./assets/image-20251015151634652.png)

**help命令**

+ 查看指定组的所有命令

```
help @generic  
```

+ 查看指定命令

```shell
help set
```

### 通用命令

#### ping心跳命令

键入ping命令，会看到PONG响应，则说明该客户端与Redis的连接是正常的。

```shell
localhost:6379> ping
PONG
```

#### keys

`keys` 命令用于查找所有符合给定模式 `pattern` 的键。

##### 模式（Pattern）规则

模式 `pattern` 可以包含以下特殊字符：

- `*`： 匹配任意数量的任意字符（包括零个）。
  - 例如 `keys *` 匹配所有键。
  - `keys user*` 匹配所有以 `user` 开头的键。
  - `keys *:123` 匹配所有以 `:123` 结尾的键。
- `?`： 匹配一个任意字符。
  - 例如 `keys user?` 匹配 `user1`， `usera`， 但不匹配 `user10` 或 `user`。
- `[abc]`： 匹配括号内的任意一个字符。
  - 例如 `keys user[123]` 匹配 `user1`， `user2`， `user3`， 但不匹配 `user4`。
  - 可以使用短横线 `-` 表示一个范围，如 `[a-z]` 匹配任意小写字母。
- `\x`： 转义特殊字符。如果你需要匹配 `*`， `?` 这些字符本身，需要用反斜线转义。
  - 例如 `keys real\*key` 会匹配名为 `real*key` 的键。

#####  严重警告：生产环境慎用！

**`KEYS` 命令在生产环境中被强烈不建议使用，甚至在某些规范中被禁用。**

**原因：**

`KEYS` 命令在执行时，**会遍历数据库中的所有键**，然后与模式进行匹配。这个过程是 **O(N)** 的复杂度，其中 N 是数据库中的键总数。

- **性能问题**： 当数据库中有数百万甚至上亿个键时，执行一次 `KEYS *` 可能会**阻塞 Redis 服务器数秒甚至数分钟**。
- **单线程阻塞**： Redis 是单线程模型的。在执行 `KEYS` 命令期间，服务器无法处理任何其他请求（读、写、删除等），导致整个服务**不可用**，这被称为“灾难性命令”。

#### scan

为了解决 `KEYS` 命令的阻塞问题，Redis 提供了 `SCAN` 命令。

**`SCAN` 命令的特点：**

1. **非阻塞迭代**： `SCAN` 通过游标分批次遍历数据集，每次只返回一小部分元素。不会长时间阻塞服务器。
2. **可暂停和恢复**： 每次调用 `SCAN` 都会返回一个新的游标，下次调用时传入这个游标可以继续之前的迭代。
3. **可能重复**： 由于在迭代过程中数据集可能发生变化，`SCAN` 可能会返回重复的键，需要在客户端进行去重。

**`SCAN` 语法：**

```shell
SCAN cursor [MATCH pattern] [COUNT count]
```

- `cursor`： 游标，第一次调用时传入 `0`。
- `MATCH pattern`： 匹配模式，与 `KEYS` 的模式相同。
- `COUNT count`： 提示每次迭代返回多少元素，默认为 10。**这只是一个提示，返回的数量可能比 COUNT 多或少**。

> 永远不要在生产环境的代码中使用 `KEYS` 命令。如果你需要查找匹配模式的键，请务必使用 `SCAN` 命令及其相关命令（如 `SSCAN`， `HSCAN`， `ZSCAN` 用于遍历集合、哈希、有序集合的元素）。

#### type

`TYPE` 命令用于查看值的类型。

#### del/unlink 

`DEL` 命令用于删除一个或多个键。如果键不存在，则会被忽略。返回被删除的键的数量。

`UNLINK` 命令用于非阻塞删除一个或多个键(命令只是从键空间中解除键的链接。实际移除将在稍后异步发生)。如果键不存在，则会被忽略。返回被删除的键的数量。

#### exists

`EXISTS` 命令用于检查一个或多个键是否存在。返回存在的键的数量。

#### expire/ttl

`DEL` 是立即删除，而 `EXPIRE` 是设置一个过期时间，让 Redis 在未来的某个时间点自动删除键。你可以用 `TTL` 命令查看键的剩余生存时间。

```shell
127.0.0.1:6379> SET abc123 "user_data"
OK
127.0.0.1:6379> EXPIRE abc123 5  # 5 秒后自动删除
(integer) 1
127.0.0.1:6379> TTL abc123
(integer) 4
```

如果ttl返回的是-1，表示key永远不会过期，返回-2表示key不存在。

#### persist

删除 `key` 上的现有超时，key将不会自动过期。

#### select

`SELECT`命令用于切换数据库，默认数据库是0。

```shell
localhost:6379> select 1
localhost:6379[1]>
```

#### dbsize

`DBSIZE`命令用于查看当前数据库中key的数量。

#### flushdb/flushall

`FLUSHDB`命令用于清空当前数据库。

`FLUSHALL`命令用于清空所有数据库。

## string类型

### set

这是 Redis 中最基础、最常用的命令之一，用于为字符串类型的键设置值。

命令完整语法如下：

```bash
SET key value [NX|XX] [GET] [EX seconds|PX milliseconds|EXAT unix-time-seconds|PXAT unix-time-milliseconds|KEEPTTL]
```

#### 设置键值对

```bash
localhost:6379> set age 20
```

设置之后可以根据key获取对应的值。

```bash
localhost:6379> get age
"20"
```

#### 条件设置

这两个选项非常有用，常用于实现分布式锁、首次设置等场景。

+ 默认为不存在则设置，存在则覆盖。

- **`NX`**： **仅当键不存在时**才设置值。 (Not eXists)

  ```bash
  localhost:6379> set height 173
  OK  #设置成功，因为 height 之前不存在
  
  127.0.0.1:6379> SET height 188 NX
  (nil) # 设置失败，返回 nil，因为 height 已经存在
  ```

- **`XX`**： **仅当键已经存在时**才设置值。

  ```bash
  localhost:6379> set weight 120 XX
  (nil) 	# 设置失败，因为 weight 不已存在
  
  localhost:6379> set weight 120
  OK
  
  127.0.0.1:6379> SET weight 160 XX
  OK   #设置成功，因为 weight 存在
  ```

  

#### 设置过期时间

你可以直接在 `SET` 命令中为键设置过期时间，而无需再使用 `EXPIRE` 命令。

- **`EX seconds`**： 以**秒**为单位设置键的过期时间。

  ```bash
  localhost:6379> set name "maye" EX 10
  OK
  ```

  这条命令设置键 `name` 的值为 `"maye"`（值使用双引号包裹，也可以不用），并在 10 秒后自动过期。

- **`PX milliseconds`**： 以**毫秒**为单位设置键的过期时间。

  ```bash
  localhost:6379> set name "nihao" PX 5000
  OK
  ```

  这条命令设置的值将在 5000 毫秒（5秒）后过期。

- **`EXAT timestamp`**： 设置键在某个具体的 **Unix 时间戳（秒）** 过期。

  ```bash
  localhost:6379> set age 18 EXAT 1760604780
  OK
  ```

  该键将在 `1696147200` 这个时间点（北京时间 2023-10-01 00:00:00）过期。

- **`PXAT milliseconds-timestamp`**： 设置键在某个具体的 **Unix 时间戳（毫秒）** 过期。

  ```
  localhost:6379> set age 29 PXAT 1760604849817
  OK
  ```
  
  > [时间戳(Unix timestamp)转换工具 - 在线工具](https://tool.lu/timestamp/)

#### 保留 TTL

- **`KEEPTTL`**： 当你重新设置一个已经存在且带有过期时间的键时，保留其原有的生存时间。

  ```bash
  localhost:6379> set sex 1 EX 100
  OK
  localhost:6379> ttl sex
  (integer) 93	#还剩93秒
  localhost:6379> set sex 0
  OK				#修改成功
  localhost:6379> ttl sex
  (integer) -1	#TTL 被清除了，永不过期
  
  #使用 KEEPTTL
  localhost:6379> SET sex 1 EX 100
  OK
  localhost:6379> ttl sex
  (integer) 95
  localhost:6379> set sex 0 keepttl
  OK				#原有的ttl被保存了下来
  localhost:6379> ttl sex
  (integer) 83
  ```
  
  

## hash类型

## list类型

## set类型

## sortedSet类型