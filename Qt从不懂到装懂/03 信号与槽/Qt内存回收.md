# 玩个按钮(设置父对象)

QPushButton是Qt中常用的一个类

```cpp
QPushButton* btn = new QPushButton;
//show和setparent同时调用会让按钮显示在窗口中间
btn->show();			//显示控件
btn->setParent(this);	//将小部件的父组件设置为parent，小部件被移动到其父部件的(0,0)位置 
btn->setText("第一个按钮");

//通过构造函数指定父控件会让窗口以子控件的大小进行显示
QPushButton* btn2 = new QPushButton("第二个按钮",this);
//移动按钮到指定位置
btn2->move(100,0);
//重新调整窗口大小
this->resize(640,480);
//设置窗口标题
this->setWindowTitle("第一个窗口");
```



# Qt内存回收机制

## 一、简介

​       Qt内存管理机制：Qt 在内部能够维护对象的层次结构。对于可视元素，这种层次结构就是子组件与父组件的关系；对于非可视元素，则是一个对象与另一个对象的从属关系。在 Qt 中，在 Qt 中，删除父对象会将其子对象一起删除。

   C++中delete 和 new 必须配对使用(一 一对应)：delete少了，则内存泄露，多了麻烦更大。Qt中使用了new却很少delete，因为QObject的类及其继承的类，设置了parent（也可在构造时使用setParent函数或parent的addChild）故parent被delete时，这个parent的相关所有child都会自动delete，不用用户手动处理。但parent是不区分它的child是new出来的还是在栈上分配的。这体现delete的强大，可以释放掉任何的对象，而delete栈上对象就会导致内存出错，这需要了解Qt的半自动的内存管理。另一个问题：child不知道它自己是否被delete掉了，故可能会出现野指针。那就要了解Qt的智能指针QPointer。

## 二、关联图

在Qt中，最基础和核心的类是：QObject，QObject内部有一个list，会保存children，还有一个指针保存parent，当自己析构时，会自己从parent列表中删除并且析构所有的children。

![img](assets/20140612112758250)

## 三、详解

### 1、内存管理

（1）QObject及其派生类的对象，如果其parent非nullptr，那么其parent析构时会析构该对象。

（2）父子关系：父对象、子对象、父子关系。这是Qt中所特有的，与类的继承关系无关，传递参数是与parent有关（基类、派生类，或父类、子类，这是对于派生体系来说的，与parent无关）。

### 2、内存问题例子

```cpp
#include <QPushButton>

Widget::Widget(QWidget *parent)
{
    QLabel *label = new QLabel("Hello Qt!");
    label->show();
}
```

**分析：**`label 既没有指定parent，也没有对其调用delete，所以会造成内存泄漏。`

**改进方式：**

+ 分配对象到栈上而不是堆上

```cpp
#include <QLabel>

Widget::Widget(QWidget *parent)
{
    QLabel label("Hello Qt!");
    label.show();
}
```

**分析：**构造函数执行完毕，对象生命周期结束会被自动析构，窗口上的控件消失不见

+ 使用指定父对象的方式自动管理内存

```cpp
class MyPushButton:public QPushButton
{
public:
    using QPushButton::QPushButton;

    ~MyPushButton()
    {
        qDebug()<<"MyPushButton 析构~";
    }
};

Widget::Widget(QWidget *parent)
{
    QPushButton* btn2 = new MyPushButton("第二个按钮",this);
    btn2->move(100,0);
}
//运行之后关掉窗口，应用程序输出显示：MyPushButton 析构~
```





