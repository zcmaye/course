## Git error

### errno 10054 

> SSL_read: Connection was reset, errno 10054 

关闭ssl验证即可

```sh
git config --global http.sslVerify false
```

## 覆盖远程仓库

```sh
git push --force --set-upstream origin master
```

[GIT 10种撤销方式，反悔必备](https://blog.csdn.net/jiahaoangle/article/details/107384856)

## 访问GitHub慢

[Watt Toolkit](https://steampp.net/ '本地反代来支持更快的访问')

