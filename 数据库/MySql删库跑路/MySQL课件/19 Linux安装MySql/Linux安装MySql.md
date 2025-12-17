## Docker

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

