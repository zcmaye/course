## Vue环境搭建

### nvm

nvm是node.js管理工具，安装node很方便，只需要一条命令；可以轻松切换node版本；可以多版本node并存。

#### 下载

+ [Linux&Mac](https://github.com/nvm-sh/nvm)

+ [Windows](https://github.com/coreybutler/nvm-windows)

![image-20230424225216880](assets/image-20230424225216880.png)

下载之后，傻瓜式安装即可，记得修改安装路径哟~

#### 使用

使用如下命令查看node.js的所有可用版本：

```css
nvm list available
```

使用如下命令安装指定版本的node.js：

```css
nvm install 18.16.0
```

使用如下命令查看已经安装的node.js版本：

```css
 nvm list
```

### npm

安装好node.js时会自动安装npm，不过需要配置一下环境变量才能才cmd使用命令。

找到你的nvm安装目录，进入node.js版本目录，把他配置到环境变量PATH中，重启cmd即可！

```css
D:\MySoftWare\nvm\v18.16.0
```

#### 换源

如果npm下载包太慢可以切换到淘宝源：

```css
// npm设置新淘宝源
npm config set registry https://registry.npmmirror.com
// npm设置回本源
npm config set registry https://registry.npmjs.org
```



### vite

使用vite作为vue的构建工具。

```css
npm init vite@latest
```

执行命令之后，需要输入项目名称：

![image-20230424230645478](assets/image-20230424230645478.png)

接着选择Vue：

![image-20230424230727777](assets/image-20230424230727777.png)

选择JavaScript：

![image-20230424230745426](assets/image-20230424230745426.png)

成功！运行提示的三条指令，即可成功运行：

![image-20230424230831061](assets/image-20230424230831061.png)

### 运行项目

找到项目目录，并进入：

![image-20230425022149082](assets/image-20230425022149082.png)

执行如下命令下载依赖到当前项目：

```css
npm install
```

![image-20230425022345326](assets/image-20230425022345326.png)

执行如下命令运行项目：

```css
npm run dev
```

然后点击出现的Local 后面的[链接](http://localhost:5173/)，访问即可！

![image-20230425022431622](assets/image-20230425022431622.png)

### 构建路由

在src目录，创建一个router目录：

![image-20230425022815239](assets/image-20230425022815239.png)

然后执行如下命令安装路由：

```css
npm install vue-router@4 --save
```

然后再router目录中创建`index.js`:

![image-20230425023241774](assets/image-20230425023241774.png)

写入以下代码：