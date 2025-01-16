+ 先查看openssh服务有没有启动

```sh
sudo service ssh status
```

> Unit ssh.service could not be found.

如果输出如上所示，表示openssh服务没有安装，则需要先安装一下。

+ ubuntu先安装openssh服务

```shell
sudo apt install openssh-server
```

+ 安装完再次执行`sudo service ssh status`，如果提示如下所示，则表示安装完毕。

```sh
ssh.service - OpenBSD Secure Sheel server
	Loaded: loaded(/usr/lib/systemd/system/ssh.service;disable;preset..)
	Active: inactive (dead)
```

+ 然后启动ssh服务

```sh
sudo service ssh start		#启动服务
```

+ 最后就可以通过cmd链接了

```sh
ssh root@192.168.1.46
```

> 登录的时候需要输入root密码，所以还必须先使用`sudo passwd root`设置密码。

+ 如果输入密码正确，但是总是提示验证失败，则需要检查`/etc/ssh/sshd_config`配置文件，确保以下正确设置。

```sh
PermitRootLogin yes				#允许远程登录
PasswordAuthentication yes		#允许使用密码验证
```

+ 记得重启ssh服务哟

```sh
sudo service ssh restart	#重启服务
```

