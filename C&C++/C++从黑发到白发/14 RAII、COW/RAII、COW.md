## RAII

RAII （Resource Acquisition Is Initialization）,也称为“资源获取就是初始化”，是C++语言的一种管理资源、避免泄漏的惯用法。C++标准保证任何情况下，已构造的对象最终会销毁，即它的析构函数最终会被调用。简单的说，RAII 的做法是使用一个对象，在其构造时获取资源，在对象生命期控制对资源的访问使之始终保持有效，最后在对象析构的时候释放资源。



## COW

COW（Copy-On-Write）,也称为"写时拷贝"。





## Copy And Swap

Copy And Swap，也称为"拷贝交换技术"。



```cpp
class Widget
{
    ...
private:
    Bitmap* pb;
}
Widget& Widget::operator=(const Widget& rhs)
{
    Bitmap* pOrig = pb;
    pb = new Bitmap(*rhs.pb);
    delete pOrig;
    return *this;
}
```

对于上述的类Widget定义是没有办法直接使用`copy and swap`技术的，原因是这个Widget的类定义，没有实现对资源的自动管理。也就是说他的析构函数上没有对`Bitmap* pb`进行释放。以a=b为例，`copy and swap`的核心是，先生成b的一份复制体c，然后把a里面旧的数据和资源与c进行交换，然后析构c，在析构c的时候，会把a原来旧的资源释放掉。所以要求c在析构的时候能够自己释放资源。同时我们还需要实现一个swap函数，用户交换a与c的数据。

综上要使用`copy and swap`技术，Widget类还需要一个能够管理资源的析构函数， 还需要一个swap函数，还需要一个拷贝构造函数(需要用这个函数生成复制体)。有了这些前提条件，才能使用该技术。

```cpp
typedef int Bitmap;
const int MAX = 10;
class Widget
{
public:
    Widget()
    {
        pb = new int[MAX]();
    }
    Widget(const Widget&rhs)
    {
        pb = new int[MAX]();
    	std::copy(rhs.pb, rhs.pb+MAX, pb);
    }
    void swap(Widget&a, Widget &c)
    {
        using std::swap;
        swap(a.pb,b.pb);
    }
    ~Widget()
    {
        delete[] pb;
    }
    Widget& operator= (const Widget& rhs)
    {
        Widget tmp(rhs);
        swap(*this,tmp);
        return *this;
    }
private:
    Bitmap* pb;
}
```

在上述的拷贝赋值函数中，我们先利用拷贝构造函数生成了一个复制体tmp，注意tmp里面的资源是独立的，自己维护的，只不过资源内容和复制主体一模一样而已。
 之后通过swap，把*this 内的数据与复制体交换。这里交换的只是指针索引，实际数据资源的位置并没有变化，只是归属发生了变化。
 最后return后，我们如愿赋值到了我们想要的数据。赋值前的老数据我们交换给了tmp，并且在函数体退出后，tmp自动释放了老数据。