## 透明窗口(不规则窗口)

[透明窗体](https://blog.csdn.net/zzwdkxx/article/details/30034403)

### 窗口拖动

### 窗口拉伸

## 圆形头像 

[圆形头像](https://zhuanlan.zhihu.com/p/131260375)

```cpp
QLabel *label = new QLabel("hello",this);;
label->move(100,100);

//label->setMask(QRegion(0,0,250,250,QRegion::RegionType::Ellipse));
label->setMask(QBitmap("://images/mask.jpg"));
label->setPixmap(QPixmap("://images/zay.png").scaled(250,250,Qt::AspectRatioMode::KeepAspectRatio));
//在圆形头像和矩形头像之间切换
QPushButton*newBtn = new QPushButton("显示原矩形头像",this);
newBtn->move(100,0);
newBtn->setCheckable(true);
connect(newBtn,&QPushButton::clicked,this,[=](bool check)
{
    if(check)
    {
        label->clearMask();
        newBtn->setText("显示矩形头像");
    }
    else
    {
        label->setMask(QBitmap("://images/mask.jpg"));
        newBtn->setText("显示圆形头像");
    }
});
```



## windowModified(窗口文档是否修改)

就是窗口的标题上加个*号(在wps里就可以看到修改的文档会加个\*)

## 窗口翻转特效

[窗口翻转特效](https://blog.csdn.net/wanghualin033/article/details/78619222)



## 窗口任务栏隐藏

有时候有特殊需求，不希望在任务栏上出现应用程序的图标。该怎么办呢？

其实可以通过设置窗口标志来实现。

调用QWidget的setWindowFlags()函数。 设置为Qt::Tool、Qt::SubWindow、Qt::Popup可以达到目的。



但是这样做会有副作用：

设置Qt::Popup不能设置保持窗口在顶层和底层。

设置Qt::SubWindow的窗口没有标题栏，没有关闭按钮，也不能进行拉伸。这些功能需要自己实现。

设置Qt::Tool窗口可以拉伸也有关闭按钮，但是点击关闭按钮，程序并不退出。



## 代码编辑器库

[Qscitinlla 官网 ](https://qscintilla.com/#home)           

[CSDN](https://blog.csdn.net/weixin_38326893/article/details/80001548)

[PyQt5](https://blog.csdn.net/caojianhua2018/article/details/102454748)



## QScreen

