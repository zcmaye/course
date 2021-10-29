# XML

## 简介

可扩展标记语言，[标准通用标记语言](通用标言是1986年国际标准化组织出版发布的一个信息管理方面的国际标准)的子集，简称XML，是一种定义电子文档结构和描述其内容的国际标准语言，被设计用来传输和存储数据。

可扩展标记语言与Access]，Oracle]和SQL Server等数据库不同，数据库提供了更强有力的数据存储和分析能力，例如：数据索引、排序、查找、相关一致性等，可扩展标记语言仅仅是存储数据。事实上它与其他数据表现形式最大的不同是：可扩展标记语言极其简单，这是一个看上去有点琐细的优点，但正是这点使它与众不同。

XML的简单易于在任何应用程序中读/写数据，这使XML很快成为数据交换的唯一公共语言，虽然不同的应用软件也支持其他的数据交换格式，但不久之后它们都将支持XML，那就意味着程序可以更容易的与[Windows]()、[Mac OS]()、[Linux]()以及其他平台下产生的信息结合，然后可以很容易加载XML数据到程序中并分析它，并以XML格式输出结果。

## 与HTML的区别

(1)可扩展性方面：HTML不允许用户自行定义他们自己的标识或属性，而在XML中，用户能够根据需要自行定义新的标识及属性名，以便更好地从语义上修饰数据。 

(2)结构性方面：HTML不支持深层的结构描述，XML的文件结构嵌套可以复杂到任意程度，能表示面向对象的等级层次。 

(3)可校验性方面：HTML没有提供规范文件以支持应用软件对HTML文件进行结构校验，而XML文件可以包括一个语法描述，使应用程序可以对此文件进行结构校验。

总之，XML使用一个简单而又灵活的标准格式，为基于Web的应用提供了一个描述数据和交换数据的有效手段。但是，XML并非是用来取代HTML的。HTML着重如何描述将文件显示在浏览器中，而XML，它着重描述如何将数据以结构化方式表示。

## 格式

**为了避免错误，需要规定 XML 编码，或者将 XML 文档存为 Unicode。**

[W3school XML教程](https://www.w3school.com.cn/xml/index.asp)

XML文件格式是纯文本格式，在许多方面类似于HTML，XML由XML元素组成，每个XML元素包括一个开始标记<>，一个结束标记</>以及两个标记之间的内容，例如，可以将XML元素标记为价格、订单编号或名称。标记是对文档存储格式和逻辑结构的描述。在形式上，标记中可能包括注释、引用、字符数据段、起始标记、结束标记、空元素、文档类型声明( DTD)和序言。

**具体规则如下：**

+ 1、必须有声明语句。 

XML声明是XML文档的第一句，其格式如下： 

```css
<?xml version="1.0" encoding="utf-8"?>
```

+ 2、注意大小写

在XML文档中，大小写是有区别的。“A”和“a”是不同的标记。注意在写元素时，前后标记的大小写要保持一致。最好养成一种习惯，或者全部大写，或者全部小写，或者大写第一个字母，这样可以减少因为大小写不匹配而产生的文档错误。  

+ 3、XML文档有且只有一个根元素

良好格式的XML文档必须有一个根元素，就是紧接着声明后面建立的第一个元素，其他元素都是这个根元素的子元素，根元素完全包括文档中其他所有的元素。根元素的起始标记要放在所有其他元素的起始标记之前；根元素的结束标记要放在所有其他元素的结束标记之后。 

+ 4、属性值使用引号

在HTML代码里面，属性值可以加引号，也可以不加。但是XML规定，所有属性值必须加引号（可以是单引号，也可以是双引号，建议使用双引号），否则将被视为错误。 

+ 5、所有的标记必须有相应的结束标记

在HTML中，标记可以不成对出现，而在XML中，所有标记必须成对出现，有一个开始标记，就必须有一个结束标记，否则将被视为错误。 

+ 6、所有的空标记也必须被关闭

空标记是指标记对之间没有内容的标记，比如“”等标记。在XML中，规定所有的标记必须有结束标记。 

[xml&json](https://www.cnblogs.com/SanMaoSpace/p/3139186.html)

## XML解析

Qt 提供了三种读取 XML 文档的方法：

+ QXmlStreamReader：一种快速的基于流的方式访问良格式 XML 文档，特别适合于实现一次解析器（所谓“一次解析器”，可以理解成我们只需读取文档一次，然后像一个遍历器从头到尾一次性处理 XML 文档，期间不会有反复的情况，也就是不会读完第一个标签，然后读第二个，读完第二个又返回去读第一个，这是不允许的）；
+ DOM（Document Object Model）：将整个 XML 文档读入内存，构建成一个树结构，允许程序在树结构上向前向后移动导航，这是与另外两种方式最大的区别，也就是允许实现多次解析器（对应于前面所说的一次解析器）。DOM 方式带来的问题是需要一次性将整个 XML 文档读入内存，因此会占用很大内存；
+ SAX（Simple API for XML）：提供大量虚函数，以事件的形式处理 XML 文档。这种解析办法主要是由于历史原因提出的，为了解决 DOM 的内存占用提出的（在现代计算机上，这个一般已经不是问题了）。
  



有如下XML文档，描述了登录数据库所需要的信息，通过解析可以获取信息以登录数据库。

```xml
<?xml version="1.0" encoding="utf-8"?>
<root>
    <HostName>localhost</HostName>
    <Port>3306</Port>
    <UserName>root</UserName>
    <PassWord>123456789</PassWord>
    <DatabaseName>Maye</DatabaseName>
</root>
```

上面的xml不带属性，下面的xml是Qt ui文件部分代码

```xml
<?xml version="1.0" encoding="utf-8"?>
<ui>
    <widget class="QWidget" name="MainWindow">
        <property name="geometry">
            <rect>
                <x>0</x>
                <y>0</y>
                <width>989</width>
                <height>594</height>
            </rect>
        </property>
    </widget>
</ui>
```



### QXmlStreamReader

QXmlStreamReader类提供了一个快速解析器，通过简单的流API读取格式良好的XML 。

QXmlStreamReader从QIODevice或原始QByteArray读取数据。  

```cpp
void Widget::parseXml(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qWarning("%s 文件打开失败",filename.toUtf8().data());
        return;
    }

    //定义解析器对象
    QXmlStreamReader xmlReader(&file);

    //解析xml，直到结束或发送错误
    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType type = xmlReader.readNext();
        //是申明：<?xml version="1.0" encoding="utf-8"?>
        if(type == QXmlStreamReader::TokenType::StartDocument)
        {
            qDebug() <<xmlReader.documentVersion()<<xmlReader.documentEncoding();
        }
        else if (type == QXmlStreamReader::TokenType::StartElement)
        {
            //读取元素名和元素文本
            if(xmlReader.name() == "HostName")
            {
                qDebug()<<xmlReader.name()<<xmlReader.readElementText();
            }
            else if(xmlReader.name() == "Port")
            {
                qDebug()<<xmlReader.name()<<xmlReader.readElementText();
            }
            else if(xmlReader.name() == "UserName")
            {
                qDebug()<<xmlReader.name()<<xmlReader.readElementText();
            }
            else if(xmlReader.name() == "PassWord")
            {
                qDebug()<<xmlReader.name()<<xmlReader.readElementText();
            }
            else if(xmlReader.name() == "DatabaseName")
            {
                qDebug()<<xmlReader.name()<<xmlReader.readElementText();
            }
            else
            {
                //读取，直到当前元素的结尾，跳过任何子节点。此函数对于跳过未知元素非常有用。
                xmlReader.skipCurrentElement();
            }
        }
    }
}
```



#### 常用函数

```cpp
//如果读取器一直读取到XML文档的末尾，或者发生了error()并中止了读取，则返回true。 否则，返回false。  
bool atEnd() const
//如果发生错误则返回true，否则返回false。  
bool hasError();
//获取错误码
QXmlStreamReader::Error error() const
//获取错误字符串
QString errorString() const
//读取下一个标记并返回其类型
QXmlStreamReader::TokenType readNext()
//以字符串的形式返回读取器的当前标记类型
QString tokenString() const
//获取标记
QStringRef name() const    
//获取当前元素的文本(StartElement和EndElement之间的文本)    
QString readElementText(QXmlStreamReader::ReadElementTextBehaviour behaviour = ErrorOnUnexpectedElement)
//获取当前元素的属性
QXmlStreamAttributes attributes() const    
	//例：QXmlStreamAttributes attrs = xmlReader.attributes();
	//例：qDebug()<<attrs.value("class").toString()<<attrs.value("name").toString();  
//读取当前元素之后的起始元素。 当到达start元素时返回true。 当到达end元素时，或者发生错误时，返回false。  
bool readNextStartElement()    
//获取当前元素的属性列表
QXmlStreamAttributes attributes() const    
```

### DOM（Document Object Model）

DOM 是由 W3C 提出的一种处理 XML 文档的标准接口。Qt 实现了 DOM Level 2 级别的不验证读写 XML 文档的方法。DOM 一次性读入整个 XML 文档，在内存中构造为一棵树（被称为 DOM 树）。我们能够在这棵树上进行导航，比如移动到下一节点或者返回上一节点，也可以对这棵树进行修改，或者是直接将这颗树保存为硬盘上的一个 XML 文件。

在使用之前需要在pro文件里加上xml模块。

```cpp
void Widget::parseDocXml(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        qWarning("%s 文件打开失败",filename.toUtf8().data());
        return;
    }

    QString err;
    int errline;
    int errcol;

    QDomDocument domdoc;
    //成功解析返回true，否则返回false
    if(!domdoc.setContent(&file,false,&err,&errline,&errcol))
    {
        qWarning("xml 解析失败");
        return;
    }
    //获取版本信息和编码信息
    qDebug()<< domdoc.firstChild().nodeName()<<domdoc.firstChild().nodeValue();

    //获取dom树的根元素(标签)
    QDomElement root = domdoc.documentElement();
    if(root.tagName() != "root")
    {
        qWarning("根元素不是root，xml文档有误~");
        return;
    }else
    {
        //traverseXmlNode(root);
        QDomElement node = root.firstChild().toElement();
        while(!node.isNull())
        {
            if(node.tagName() == "HostName")
            {
                qDebug()<<node.text();
            }
            else if(node.tagName() == "Port")
            {
                QDomElement subNode = node.firstChildElement();
                while(!subNode.isNull())
                {
                    if(subNode.tagName() == "a")
                    {
                        qDebug()<<subNode.text();
                    }
                    else if(subNode.tagName() == "fuck")
                    {
                        qDebug()<<subNode.text();
                    }
                    subNode = subNode.nextSiblingElement();
                }
            }
            else if(node.tagName() == "UserName")
            {
                qDebug()<<node.text();
            }
            else if(node.tagName() == "PassWord")
            {
                qDebug()<<node.text();
            }
            else if(node.tagName() == "DatabaseName")
            {
                qDebug()<<node.text();
            }
            node = node.nextSiblingElement();
        }
    }
} 
```

### SAX（Simple API for XML）

## XML生成

至于生成 XML 文档，Qt 同样提供了三种方式：

+ QXmlStreamWriter，与QXmlStreamReader相对应；
+ DOM 方式，首先在内存中生成 DOM 树，然后将 DOM 树写入文件。不过，除非我们程序的数据结构中本来就维护着一个 DOM 树，否则，临时生成树再写入肯定比较麻烦；
+ 纯手工生成 XML 文档，显然，这是最复杂的一种方式。
  

### QXmlStreamWriter

QXmlStreamWriter类提供了一个带有简单流API的XML编写器。  

QXmlStreamWriter是用于编写XML的QXmlStreamReader的对等物。 像它的相关类一样，它操作由setDevice()指定的QIODevice。 这个API简单明了:对于您想要编写的每个XML标签或事件，编写器提供一个专门的函数。  

```cpp
void Widget::writeXml(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning("文件打开失败");
        return ;
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);         //设置自动格式化(有缩进有换行，否则都是在同一行)

    writer.writeStartDocument("1.0");
    writer.writeStartElement("ui");
    writer.writeAttribute("effect","描述界面");

    writer.writeStartElement("widget");
    writer.writeAttribute("class","QWidget");
    writer.writeAttribute("name","MainWindow");
    writer.writeComment("helo");
    writer.writeStartElement("property");
    writer.writeAttribute("name","property");

    writer.writeStartElement("rect");
    writer.writeTextElement("x","0");
    writer.writeTextElement("y","0");
    writer.writeTextElement("width","640");
    writer.writeTextElement("height","480");
    writer.writeEndElement();   // end widget
    writer.writeEndElement();   // end property
    writer.writeEndElement();   // end rect

    writer.writeEndElement();   //end ui
    writer.writeEndDocument();
    file.close();
}
```



# JSON

JSON(JavaScript Object Notation, JS 对象简谱) 是一种轻量级的数据交换格式。它基于 ECMAScript (欧洲计算机协会制定的js规范)的一个子集，采用完全独立于编程语言的文本格式来存储和表示数据。简洁和清晰的层次结构使得 JSON 成为理想的数据交换语言。 易于人阅读和编写，同时也易于机器解析和生成，并有效地提升网络传输效率。

## 格式

JSON是一个标记符的序列。这套标记符包含六个**构造字符**、**字符串**、**数字**和三个**字面名**。

+ 1，六个构造字符
  + 开始和结束数组：[  ]
  + 开始和结束对象：{  }
  + 名称分隔：:	 (冒号)
  + 值分隔：,		(逗号)

+ 2，字符串用双引号包含
+ 3，数字直接表示，不用引号包含
+ 4，三个字面量
  + true
  + flase
  + null

JSON是一个序列化的**对象**或**数组**。

+ **对象**由花括号括起来的逗号分割的成员构成，成员是字符串键和值(**值**可以是**对象**、**数组**、**数字**、**字符串**或者三个**字面值**(false、null、true)中的一个)组成

  ```json
  {"name":"maye","age":18,"address":{"country":"china","city":"changsha"}}
  ```

+ **数组**是由方括号括起来的一组值构成

  ```json
  {"city":["长沙","南京","北京"]}
  ```

## Json解析

在Qt库中，为JSON的相关操作提供了完整的类支持，包括QJsonValue，QJsonObject，QJsonArray，QJsonDocument和QJsonParseError。其中，QJsonValue类表示json格式中的一个值；QJsonObject表示一个json对象；QJsonArray顾名思义表示一个json数组；QJsonDocument主要用来读写json文档；而QJsonParseError是用来表示json解析过程中出现的错误的方便类。

### QJsonDocument

QJsonDocument类提供了一种读取和写入JSON文档的方法。  

QJsonDocument是一个包装完整JSON文档的类，可以从基于UTF-8编码的文本表示以及Qt自己的二进制格式读取和写入该文档。  

可以使用QJsonDocument::fromJson()将JSON文档从基于文本的表示转换为QJsonDocument。 toJson()将其转换回文本。 该解析器非常快速和高效，并将JSON转换为Qt使用的二进制表示。  

可以使用!isNull()查询已解析文档的有效性  

可以使用isArray()和isObject()查询文档是否包含数组或对象。 可以使用array()或object()检索文档中包含的数组或对象，然后读取或操作。  

还可以使用fromBinaryData()或fromRawData()从存储的二进制表示创建文档。  

```cpp
bool isArray() const		//是否包含数组  {"name":"maye"}  ["maye","顽石","wwk"]
bool isEmpty() const		//是不是空
bool isNull() const
bool isObject() const		//是否包含对象

QJsonArray array() const	//返回文档中包含的QJsonObject。如果文档包含数组，则返回空对象。  
QJsonObject object() const	//返回文档中包含的QJsonArray。 如果文档包含一个对象，则返回一个空数组。  
//根据key或下标获取对应的值
const QJsonValue operator[](const QString &key) const
const QJsonValue operator[](int i) const    
//将arrayh或object设置为本文档的主对象。      
void setArray(const QJsonArray &array)
void setObject(const QJsonObject &object)    
//设置主对象之后可以tojson，然后保存到文件
QByteArray toJson() const
QByteArray toJson(QJsonDocument::JsonFormat format) const    
```



### QJsonObject

QJsonObject类封装了一个JSON对象 。

JSON对象是键值对的列表，其中键是唯一的字符串，值由QJsonValue表示。  

QJsonObject可以转换为QVariantMap，也可以转换为QVariantMap。 可以使用size()、insert()和remove()条目从它查询(键、值)对的数量，并使用标准c++迭代器模式遍历其内容。  

```cpp
for(QJsonObject::const_iterator it = obj.constBegin();it != obj.constEnd() ;it++)
{
     qDebug()<<it.key()<< it.value();
}
for(QJsonValue val : obj)
{
     qDebug()<<val;
}
```

QJsonObject是一个隐式共享类，只要它没有被修改，它就与创建它的文档共享数据。  

```cpp
//查找key为指定key的项，如果没有返回constEnd();
QJsonObject::const_iterator constFind(const QString &key) const
QJsonObject::iterator find(const QString &key)
//返回key对应的QJsonValue 如果键不存在，则返回QJsonValue为QJsonValue::Undefined。  
QJsonValue value(const QString &key) const
QJsonValue operator[](const QString &key) const
      
//如果对象包含key key，则返回true。  
bool contains(const QString &key) const
//从映射中移除迭代器所指向的(键，值)对，并返回一个指向映射中下一项的迭代器。  
QJsonObject::iterator erase(QJsonObject::iterator it) 
//从对象中移除key
void remove(const QString &key)    
//插入键值对    
QJsonObject::iterator insert(const QString &key, const QJsonValue &value)    
    
//返回存储在对象中的(键，值)对的数目。  
int count() const
int length() const
int size() const
//是否为空
bool empty() const
```



### QJsonArray

QJsonArray类封装了一个JSON数组。

JSON数组是一个值列表。 可以通过从数组中插入和删除QJsonValue操作列表。  

QJsonArray可以转换为QVariantList，也可以转换为QVariantList。 您可以查询它的size()、insert()和removeAt()条目的数量，并使用`标准c++迭代器模式遍历`其内容。  

```cpp
for(QJsonValue val : json_array)
{
}
```

QJsonArray是一个隐式共享类，只要它没有被修改，它就与创建它的文档共享数据。  

```cpp
//在数组的末尾追加value
void append(const QJsonValue &value)
//在数组的开头插入value
void prepend(const QJsonValue &value)
void push_back(const QJsonValue &value)
void push_front(const QJsonValue &value)
    void insert(int i, const QJsonValue &value)
QJsonArray::iterator insert(QJsonArray::iterator before, const QJsonValue &value)   
    
//获取指定位置的值，如果i越界，则返回的QJsonValue为Undefined。  
QJsonValue at(int i) const    
QJsonValue operator[](int i) const 
QJsonValue first() const
QJsonValue last() const
//如果数组中包含值的出现，则返回true，否则返回false。  
bool contains(const QJsonValue &value) const  
    
//移除，数组不能为空。 如果数组可以为空，则在调用该函数之前调用isEmpty()。     
void pop_back()
void pop_front()
void removeAt(int i)
void removeFirst()
void removeLast()    
//替换
void replace(int i, const QJsonValue &value)
//
QVariantList toVariantList() const
   
int count() const
int size() const    
bool empty() const   
```



### QJsonValue

QJsonValue类用JSON封装了一个值。  

JSON中的值可以是6种基本类型之一:  

JSON是一种存储结构化数据的格式。 它有6种基本数据类型:  

+ bool QJsonValue::Bool
+ double QJsonValue::Double
+ string QJsonValue::String
+ array QJsonValue::Array
+ object QJsonValue::Object
+ null QJsonValue::Null

值可以表示上述任何数据类型。 此外，QJsonValue有一个特殊的标志来表示未定义的值。 这可以通过isUndefined()进行查询。  

可以使用type()或isBool()、isString()等访问器查询值的类型。 同样，可以使用tobool()、toString()等将值转换为存储在其中的类型。  

值在内部是严格类型的，与QVariant相反，它不会尝试执行任何隐式类型转换。 这意味着转换为不存储在值中的类型将返回一个默认构造的返回值。  

```cpp
//判断类型
QJsonValue::Type type() const
//以下是方便的函数    
bool isArray() const
bool isBool() const
bool isDouble() const
bool isNull() const
bool isObject() const
bool isString() const
bool isUndefined() const
//将值转换为特定类型并返回，如果type()不是特定类型，则返回defaultValue。  
QJsonArray 	toArray(const QJsonArray &defaultValue) const
QJsonArray 	toArray() const
bool 		toBool(bool defaultValue = false) const
double 		toDouble(double defaultValue = 0) const
int 		toInt(int defaultValue = 0) const
QJsonObject toObject(const QJsonObject &defaultValue) const
QJsonObject toObject() const
QString 	toString() const
QString 	toString(const QString &defaultValue) const
QVariant 	toVariant() const


bool operator==(const QJsonValue &other) const
const QJsonValue operator[](const QString &key) const
const QJsonValue operator[](int i) const   
```





```cpp
void Widget::parseJson(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning("文件读取失败");
        return;
    }
    QJsonParseError error;
    QJsonDocument json = QJsonDocument::fromJson(file.readAll(),&error);
    if(json.isNull())
    {
        qWarning("json 解析失败:%s",error.errorString().toUtf8().data());
        return;
    }
    qDebug()<<json["test"];
    qDebug()<<json["HostName"].toString()<<json["Port"].toInt()<<json["Username"].toString()
            <<json["Password"].toString()<<json["DatabaseName"].toString();

    void showAll(const QJsonObject & obj);
    showAll(json.object());


}

void showAll(const QJsonObject & obj)
{
    for(QJsonValue value : obj)
    {
        if(value.isObject())
        {
            showAll(value.toObject());
        }
        else if(value.isArray())
        {
             for(QJsonValue a : value.toArray())
             {
                 qDebug()<<a;
             }
        }else
        {
            qDebug()<<value;
        }

    }
}
```



## json生成

生成也是用上面的类，需要注意的是：生成json时会自动把key排序

```cpp
void Widget::writeJson(const QString &filename)
{
    QJsonDocument json;

    //构建一个主对象
    QJsonObject obj;
    obj.insert("year","2019");
    obj.insert("month","10");
    obj.insert("day","29");
    obj.insert("weather","晴");
    //构建一个数组
    QJsonArray array ={"北京","天津"};
    array.append("上海");
    obj.insert("city",array);
    //构建一个子对象
    QJsonObject subObj;
    subObj.insert("one",1);
    subObj.insert("two",2);
    obj.insert("list",subObj);

    //给jsonDocument设置主对象
    json.setObject(obj);
    //保存
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
         qWarning("文件打开失败");
         return;
    }
    QByteArray jsonText = json.toJson();
    file.write(jsonText);
}
```

结果：

```cpp
{
    "city": [
        "北京",
        "天津",
        "上海"
    ],
    "day": "29",
    "list": {
        "one": 1,
        "two": 2
    },
    "month": "10",
    "weather": "晴",
    "year": "2019"
}
```

