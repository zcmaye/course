# Linux安装MySQL

当你需要在Ubuntu上安装MySQL时，有两种主要的方式：**在线安装**和**离线安装**。在线安装是通过Ubuntu软件包管理器直接下载和安装MySQL，而离线安装则涉及手动下载MySQL安装包并在离线环境中进行安装。

## 在线安装

### 更新软件包列表

在进行任何软件安装之前，请确保你的系统的软件包列表是最新的。打开终端并运行以下命令：

```bash
sudo apt update
```

### 安装MySQL服务器

在更新软件包列表后，这里我们可以查看一下可使用的MySQL安装包：

```bash
root@maye-vm-pc:~# sudo apt search mysql-server
正在排序... 完成
全文搜索... 完成  
default-mysql-server/noble 1.1.0build1 all
  MySQL database server binaries and system database setup (metapackage)

default-mysql-server-core/noble 1.1.0build1 all
  MySQL database server binaries (metapackage)

mysql-server/noble-updates 8.0.44-0ubuntu0.24.04.2 all
  MySQL database server (metapackage depending on the latest version)

mysql-server-8.0/noble-updates 8.0.44-0ubuntu0.24.04.2 amd64
  MySQL database server binaries and system database setup

mysql-server-core-8.0/noble-updates 8.0.44-0ubuntu0.24.04.2 amd64
  MySQL database server binaries
```

根据结果发现没有找到我们需要的`8.4.7`版本，没关系后面我们通过离线安装就可以安装需要的版本！！！

接下来使用如下命令安装MySQL服务器：

```bash
# 安装最新版本
sudo apt install -y mysql-server
# 安装指定版本
sudo apt install -y mysql-server-8.0
```

### 检查MySQL服务状态

安装完成后，你可以使用以下命令来检查MySQL是否正在运行：

```bash
root@maye-vm-pc:~# sudo systemctl status mysql
● mysql.service - MySQL Community Server
     Loaded: loaded (/usr/lib/systemd/system/mysql.service; enabled; preset: enabled)
     Active: active (running) since Fri 2026-01-09 13:37:58 CST; 1min 41s ago
    Process: 6140 ExecStartPre=/usr/share/mysql/mysql-systemd-start pre (code=exited, status=0/SUCCESS)
   Main PID: 6149 (mysqld)
     Status: "Server is operational"
      Tasks: 37 (limit: 4604)
     Memory: 363.7M (peak: 377.9M)
        CPU: 1.118s
     CGroup: /system.slice/mysql.service
             └─6149 /usr/sbin/mysqld

1月 09 13:37:57 maye-vm-pc systemd[1]: Starting mysql.service - MySQL Community Server...
1月 09 13:37:58 maye-vm-pc systemd[1]: Started mysql.service - MySQL Community Server.
```

至此，你已经成功在线安装了MySQL服务器。

### 修改密码

默认安装是没有设置密码的，需要我们自己设置密码。

+ 首先，直接登录服务器：

  ```bash
  mysql -uroot
  ```

+ 然后，设置密码

  ```sql
  ALTER USER USER() IDENTIFIED BY '123456';
  ```

### 启用远程登录

要实现所有IP都能登录MySQL服务器；必须通过直接修改配置文件才能实现。

MySQL8.0版本把配置文件 `my.cnf` 拆分成`mysql.cnf `和`mysqld.cnf`，我们需要修改的是`mysqld.cnf`文件：

```bash
sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf
```

将`bind-address`修改一下：

```bash
#bind-address           = 127.0.0.1
bind-address            = 0.0.0.0
```

然后重启MySQL服务器：

```bash
sudo systemctl restart mysql;
```

注意：此时还不能登录，如果登录会有错误。

```bash
C:\Users\Maye>mysql -uroot -p123456 -h 192.168.1.202 -P 3306
mysql: [Warning] Using a password on the command line interface can be insecure.
ERROR 1130 (HY000): Host '192.168.1.200' is not allowed to connect to this MySQL server
```

错误原因就是不允许root用户远程登录，需要将root用户的host改为百分号:

```sql
RENAME USER CURRENT_USER TO root@'%';
```

查看是否修改成功：

```sql
mysql> SELECT user,host FROM mysql.user;
+------------------+-----------+
| user             | host      |
+------------------+-----------+
| root             | %         |
| debian-sys-maint | localhost |
| mysql.infoschema | localhost |
| mysql.session    | localhost |
| mysql.sys        | localhost |
+------------------+-----------+
5 rows in set (0.00 sec)
```

修改成功后，即可登录成功！

### 卸载

在 Ubuntu 系统中卸载 MySQL 时，如果需要**彻底清除所有数据与配置文件**，可以按照以下步骤操作。执行前请务必**备份重要数据库**，因为此过程不可逆。

#### 卸载MySQL服务

+ 停止MySQL服务，这样可确保卸载过程中不会有 MySQL 进程占用文件。

```bash
sudo systemctl stop mysql
```

+ 使用 `--purge` 参数可同时删除配置文件：

```bash
sudo apt remove --purge mysql-server
```

+ 然后删除MySQL服务的依赖包：

```bash
sudo apt autoremove
sudo apt autoclean
```

+ 接着，清除单元文件

```bash
sudo systemctl daemon-reload
```

#### 删除残留文件

+ MySQL 的数据目录和日志目录需手动清理：

```bash
sudo rm -rf /etc/mysql /var/lib/mysql /var/log/mysql
```

## 离线安装

### 下载包

+ 进入[MySQL :: Download MySQL Community Server](https://dev.mysql.com/downloads/mysql/)

![image-20260109144426490](./assets/image-20260109144426490.png)

+ 在下一个页面点击下载

![image-20260109144532506](./assets/image-20260109144532506.png)

也可以右击上方红框里面的超链接，复制链接，然后使用`wget`命令下载：

```bash
wget https://dev.mysql.com/get/Downloads/MySQL-8.4/mysql-server_8.4.7-1ubuntu24.04_amd64.deb-bundle.tar
```

也可以在`windows`上下载完毕之后，通过`rz`命令上传：

```bash
root@maye-vm-pc:/opt/mysql# rz
 ZMODEM  Session started            
------------------------            
  48% mysql-server_8.4.7-1ubuntu24.04_amd64.deb-bundle.tar 
```

输入rz命令之后，会弹出文件选择框，选择mysql包即可！

### 解压包

下载完成后使用`tar`命令进行解压：

```bash
tar xf mysql-server_8.4.7-1ubuntu24.04_amd64.deb-bundle.tar
```

解压之后有很多`deb`安装包：

```bash
root@maye-vm-pc:/opt/mysql# ls -l
libmysqlclient24_8.4.7-1ubuntu24.04_amd64.deb					# 客户端库（开发不需要）
libmysqlclient-dev_8.4.7-1ubuntu24.04_amd64.deb					# 开发库（开发不需要）
mysql-client_8.4.7-1ubuntu24.04_amd64.deb						# 客户端（可选）
mysql-common_8.4.7-1ubuntu24.04_amd64.deb						# 基础文件(必选)
mysql-community-client_8.4.7-1ubuntu24.04_amd64.deb
mysql-community-client-core_8.4.7-1ubuntu24.04_amd64.deb		# 客户端核心(必选)
mysql-community-client-plugins_8.4.7-1ubuntu24.04_amd64.deb		# 客户端插件(必选)
mysql-community-server_8.4.7-1ubuntu24.04_amd64.deb				# 主服务包（必选）
mysql-community-server-core_8.4.7-1ubuntu24.04_amd64.deb		# 服务器核心(必选)
mysql-community-server-debug_8.4.7-1ubuntu24.04_amd64.deb		# 调试版本
mysql-community-test_8.4.7-1ubuntu24.04_amd64.deb				# 测试
mysql-community-test-debug_8.4.7-1ubuntu24.04_amd64.deb			# 调试测试
mysql-server_8.4.7-1ubuntu24.04_amd64.deb						# 元包（依赖社区版）
mysql-server_8.4.7-1ubuntu24.04_amd64.deb-bundle.tar
mysql-testsuite_8.4.7-1ubuntu24.04_amd64.deb					# 测试套件
```

不需要全部安装，只需要按顺序安装如下一些包即可：

| 包名                                                     | 作用说明                                         | 必需性   | 安装建议                          |
| :------------------------------------------------------- | :----------------------------------------------- | :------- | :-------------------------------- |
| **mysql-common**                                         | 包含MySQL通用的配置文件、字符集文件、基础脚本等  | **必需** | 必须先安装，提供基础支持          |
| **mysql-community-client-plugins**                       | MySQL客户端插件，如caching_sha2_password认证插件 | **必需** | 服务器需要这些插件处理客户端连接  |
| **mysql-community-client-core**                          | MySQL核心客户端组件，包含基础客户端库            | **必需** | 服务器需要基础客户端功能          |
| **mysql-community-server-core**                          | MySQL服务器核心引擎，不含额外工具                | **必需** | 服务器核心，提供数据库引擎        |
| **mysql-community-server**                               | 完整的MySQL服务器主包，包含服务脚本、配置文件等  | **必需** | 主服务器包，安装后即可运行服务    |
| **mysql-community-client**                               | 完整的MySQL命令行客户端工具（mysql命令）         | 推荐安装 | 用于管理服务器，建议安装          |
| **mysql-client**                                         | MySQL客户端元包（指向mysql-community-client）    | 可选     | 元包，依赖mysql-community-client  |
| **libmysqlclient24**                                     | MySQL C语言客户端库（动态库）                    | 可选     | 如果其他程序需要连接MySQL则需安装 |
| **libmysqlclient-dev**                                   | MySQL开发头文件和静态库                          | 可选     | 开发MySQL应用程序时需要           |
| **mysql-server**                                         | MySQL服务器元包（指向mysql-community-server）    | 可选     | 元包，依赖mysql-community-server  |
| **mysql-community-server-debug**                         | 带调试信息的服务器版本                           | 不推荐   | 仅用于调试，生产环境不需要        |
| **mysql-community-test**                                 | MySQL测试套件                                    | 不推荐   | 包含测试用例，生产环境不需要      |
| **mysql-community-test-debug**                           | 带调试信息的测试套件                             | 不推荐   | 调试用测试套件                    |
| **mysql-testsuite**                                      | 测试套件元包                                     | 不推荐   | 测试用                            |
| **mysql-server_8.4.7-1ubuntu24.04_amd64.deb-bundle.tar** | 所有deb包的tar打包文件                           | -        | 源文件包，需要解压使用            |

### 安装流程建议

#### 最小化安装(仅服务器)

```bash
# 按依赖顺序安装
sudo dpkg -i mysql-common_*.deb
sudo dpkg -i mysql-community-client-plugins_*.deb
sudo dpkg -i mysql-community-client-core_*.deb
sudo dpkg -i mysql-community-server-core_*.deb

sudo dpkg -i mysql-community-client_*.deb
sudo dpkg -i mysql-client_*.deb
sudo dpkg -i libmysqlclient24_*.deb
sudo dpkg -i mysql-community-server_*.deb
```

在安装过程中可能会提示找不到xx包，安装一下即可：

```bash
sudo apt install libaio1t64 libmecab2
```

最后在弹出的窗口中，输入密码即可！

![image-20260109152915158](./assets/image-20260109152915158.png)

最终安装完成，提示如下：

```bash
root@maye-vm-pc:/opt/mysql# sudo dpkg -i mysql-community-server_*.deb
正在选中未选择的软件包 mysql-community-server。
(正在读取数据库 ... 系统当前共安装有 206117 个文件和目录。)
准备解压 mysql-community-server_8.4.7-1ubuntu24.04_amd64.deb  ...
正在解压 mysql-community-server (8.4.7-1ubuntu24.04) ...
正在设置 mysql-community-server (8.4.7-1ubuntu24.04) ...
update-alternatives: 使用 /etc/mysql/mysql.cnf 来在自动模式中提供 /etc/mysql/my.cnf (my.cnf)
Created symlink /etc/systemd/system/multi-user.target.wants/mysql.service → /usr/lib/systemd/system/mysql.service.
```

接着就可以查看服务状态了：

```bash
root@maye-vm-pc:/opt/mysql# systemctl status mysql
● mysql.service - MySQL Community Server
     Loaded: loaded (/usr/lib/systemd/system/mysql.service; enabled; preset: enabled)
     Active: active (running) since Fri 2026-01-09 15:30:08 CST; 1min 7s ago
       Docs: man:mysqld(8)
             http://dev.mysql.com/doc/refman/en/using-systemd.html
   Main PID: 10111 (mysqld)
     Status: "Server is operational"
      Tasks: 34 (limit: 4604)
     Memory: 420.0M (peak: 434.2M)
        CPU: 992ms
     CGroup: /system.slice/mysql.service
             └─10111 /usr/sbin/mysqld

1月 09 15:30:06 maye-vm-pc systemd[1]: Starting mysql.service - MySQL Community Server...
1月 09 15:30:08 maye-vm-pc systemd[1]: Started mysql.service - MySQL Community Server.
```

### 卸载

+ 先查看所有安装的mysql包：

```bash
sudo dpkg -l | grep 'mysql'
```

![image-20260109151739239](./assets/image-20260109151739239.png)

+ 然后使用如下命令卸载：

```bash
sudo dpkg --purge mysql-community-server
sudo dpkg --purge mysql-community-server-core 
sudo dpkg --purge mysql-community-client mysql-community-client-plugins mysql-community-client-core mysql-common mysql-client
```

[在Debian和Ubuntu上使用DEB包离线安装MySQL-开发者社区-阿里云](https://developer.aliyun.com/article/1684189)

## Docker安装

使用命令拉取mysql镜像。

```css
docker pull docker.1ms.run/library/mysql:8.4
```

启动镜像。

```css
sudo docker run -d \
  --name mysql-8.4 \
  -e MYSQL_ROOT_PASSWORD=123456 \
  -e MYSQL_DATABASE=hdy_student_manager \
  -p 3306:3306 \
  -v mysql-data:/var/lib/mysql \
  -v /usr/local/mysql/my.cnf:/etc/mysql/my.cnf \
  mysql:8.4
```

# 
