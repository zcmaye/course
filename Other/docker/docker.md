## 安装Docker

### ubuntu

1. **设置apt存储库**

   ```shell
   # 更新软件包索引（软件源列表）
   sudo apt-get update
   # 添加Docker的官方GPG密钥
   sudo apt-get install ca-certificates curl
   # 以 root 权限创建一个目录 /etc/apt/keyrings，并设置其权限为 0755
   sudo install -m 0755 -d /etc/apt/keyrings
   # 使用curl下载docker官方GPG秘钥
   sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
   # 给秘钥添加所有用户可读权限
   sudo chmod a+r /etc/apt/keyrings/docker.asc
   
   # 将存储库添加到Apt源：
   echo \
     "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://mirrors.ustc.edu.cn/docker-ce/linux/ubuntu/ \
     $(. /etc/os-release && echo "${UBUNTU_CODENAME:-$VERSION_CODENAME}") stable" | \
     sudo tee /etc/apt/sources.list.d/docker.list > /dev/null  
   # 再次更新软件包索引（软件源列表）
   sudo apt-get update
   ```

2. **安装Docker包**

   ```shell
   sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
   ```

3. **运行`hello-world`镜像来验证Docker是否安装成功**

   ```shell
   sudo docker run hello-world
   ```

   > docker: Error response from daemon: Get "https://registry-1.docker.io/v2/": context deadline exceeded

   本地是没有`hello-world`镜像的，docker会尝试从docker官方镜像仓库拉取，但是国内是访问不了的，所以需要配置国内镜像源。

   ```shell
   sudo mkdir -p /etc/docker
   sudo tee /etc/docker/daemon.json << 'EOF'
   {
   	"registry-mirrors":[
   		"https://docker.1ms.run",
   		"https://docker.m.daocloud.io",
   		"https://docker-0.unsee.tech",
   		"https://docker.1panel.live",
   		"https://func.ink",
   		"https://lispy.org",
   		"https://docker.xiaogenban1993.com"
   	]
   }
   EOF
   sudo systemctl daemon-reload
   sudo systemctl restart docker
   ```

   使用如下命令，查看所有镜像源：

   ```shell
   docker info | grep -A 5 "Registry Mirrors"
   ```

   

4. **停止docker服务**

   ```shell
   sudo systemctl stop docker
   ```

5. **开启docker服务并保持开机自启**

   ```shell
   sudo systemctl enable docker --now
   ```


> 如果使用命令`sudo systemctl stop docker`停止docker，出现如下提示：`Stopping 'docker.service', but its triggering units are still active:docker.socket`。
>
> 1. 先使用命令`sudo systemctl stop docker.socket`停止socket服务
> 2. 再使用命令`sudo systemctl stop docker.service`停止docker服务
> 3. 最后运行命令`docker images`，出现这个提示`Cannot connect to the Docker daemon at unix:///var/run/docker.sock. Is the docker daemon running?`说明服务器已经停止！



## 镜像操作

### 下载镜像

1. **搜索镜像(国内用不了)**

   ```shell
   sudo docker search [nginx]
   ```

2. **下载镜像**

   ```shell
   sudo docker pull [nginx]			#下载latest版本
   sudo docker pull [nginx:1.27.4]		#下载1.27.4版本
   ```

   > 如果配置的docker镜像源没有问题，但是还是拉取失败，可以尝试重启一下网络
   >
   > `sudo systemctl restart NetworkManager`

3. **本地镜像列表**

   ```shell
   sudo docker images
   ```

4. **删除镜像**

   ```shell
   sudo docker rmi [nginx:1.27.4] | [nginx:latest]
   sudo docker rmi [IMAGE ID]
   ```

5. **删除镜像错误**

> 当我们执行命令sudo docker rmi hello-world删除`hello-world`镜像时，出现了报错：Error response from daemon: conflict: unable to remove repository reference "hello-world" (must force) - container 25d9ad03eb4d is using its referenced image 74cc54e27dc4
>
> 问题原因：该错误表明你尝试删除的 Docker 镜像（ID: `74cc54e27dc4`）被一个已停止的容器（ID: `25d9ad03eb4d`）引用，因此 Docker 阻止了删除操作以保护数据完整性。

+ 查看所有容器，包括已经停止的

  ```shell
  sudo docker ps -a
  ```

  > CONTAINER ID   IMAGE         COMMAND    CREATED          STATUS                      PORTS     NAMES
  > 7ea1d875bff5   hello-world   "/hello"   25 minutes ago   Exited (0) 25 minutes ago             gracious_jackson

我们发现hello-world存在一个已经退出的容器，我们需要把这个容器删掉，才能删除镜像！

+ 删除关联的已停止的容器

  ```shell
  # 删除指定容器（替换为你的容器ID）
  sudo docker rm 7ea1d875bff5
  
  # 如果容器较多，可批量删除所有已停止的容器（谨慎操作！）
  docker container prune
  ```

+ 再次尝试删除镜像

  ```shell
  sudo docker rmi hello-world
  ```

+ **如果删除了容器依然无法删除镜像，则使用以下命令强制删除**

  ```shell
  sudo docker rmi -f hello-world
  ```

  > **注意**：强制删除可能导致数据不一致，仅在其他方法无效时使用。

### 启动容器

+ **启动容器**

  ```shell
  docker run nginx 		#运行容器,会阻塞终端
  docker run -d nginx	#运行容器,不会阻塞终端，在后台运行
  docker run -d --name mynginx nginx 	#运行容器并给终端取个名字
  docker run -d --name mynginx -p 88:80 nginx 	#加入端口映射，在外部才能访问80是容器中nginx的默认端口号，88是映射到的主机端口号
  ```

+ **删除容器**

  ```shell
  docker rm mynginx	#根据容器名删除容器
  docker rm 152		#根据容器ID删除容器
  docker rm -f 152	#强制删除容器，即使容器正在运行
  ```

+ **进入容器内部**

  ```shell
  docker exec -it mynginx /bin/bash #进入容器内部，使用bash进行交互
  #使用exit退出容器
  ```

  

| 命令           | 描述                                                       |
| -------------- | ---------------------------------------------------------- |
|                | 运行容器(-d可以在后台启动，不会阻塞终端)                   |
| docker ps [-a] | 查看容器(-a选项可以查看已经停止的容器)                     |
| docker stop    | 停止容器                                                   |
| docker start   | 启动已经停止的容器(指定容器名或ID都可以)一般自动在后台运行 |
| docker restart | 重启容器                                                   |
| docker stats   | 查看容器容器                                               |
| docker logs    | 查看容器日志                                               |
|                |                                                            |
|                |                                                            |

### 保存镜像

1. **将修改后的镜像保存**

   ```shell
   docker commit -m"update index.html" mynginx mynginx:1.0
   ```

   保存之后可以使用`docker images`命令查看镜像。

> REPOSITORY   TAG       IMAGE ID       CREATED          SIZE
>        mynginx      1.0       46b75f338697   21 seconds ago   192MB

2. **将镜像保存为tar包**

   ```shell
   docker save -o mynginx.tar mynginx
   ```

   保存之后执行`ls`命令，会在当前目录看到一个名为`mynginx.tar`的包。

3. 加载`mynginx.tar`镜像包。

   ```shell
   docker load -i mynginx.tar
   ```

   