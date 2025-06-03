# QML绘图系统

## 一、绘图系统四要素

+ 画布（Canvas，类似于Widget的QPaintDevice）
+ 画师（Context2d，类似于Widget的QPainter）
+ 画笔（strokeStyle属性，类似于Widget的QPen）
+ 画刷（fillStyle属性，类似于Widget的QBrush）

### 1.1、基本绘图模式

Canvas是Item的派生类，通过设置width和height属性，就可以定一个绘图区域，然后在onPaint()信号处理器内使用Context2D对象来绘图。

```js
import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true

	//=========================================
    Canvas {
        width: 400;
        height: 200;

        onPaint: {
            var ctx = getContext("2d");	//获取画师，每个画布都有一个独一无二的画师
            ctx.lineWidth = 2;	//设置画布宽度
            ctx.strokeStyle = "red";	//设置画布颜色
            ctx.fillStyle = "blue";	//设置画刷颜色
            ctx.beginPath();	//开始绘图信号
            ctx.rect(100,80,120,80);	//绘制一个矩形
            ctx.fill();	//使用画刷颜色填充
            ctx.stroke();	//使用画笔颜色勾勒边框
        }
    }
    //=========================================
    
}
```

paint是Canvas的信号，当需要绘图（更新）时会触发，开发者通过实现名为onPaint的信号处理器来响应paint信号，在信号处理器内进行绘图；
Context2D是QML中负责2D绘图的对象，与Canvas结合使用，有两种使用Context2D对象的方式：

+ 1、在onPaint信号处理器中调用getContext(“2d”)获取Context2D对象；
+ 2、设置Canvas对象的contextType属性（2D绘图时取值为“2d”）后，context属性就会保存一个可用的Context2D对象；故上例也可以写为如下方式：

```js
 Canvas {
        width: 400;
        height: 200;
        contextType: "2d";

        onPaint: {
            context.lineWidth = 2;	//设置画布宽度
            context.strokeStyle = "red";	//设置画布颜色
            context.fillStyle = "blue";	//设置画刷颜色
            context.beginPath();	//开始绘图信号
            context.rect(100,80,120,80);	//绘制一个矩形
            context.fill();	//使用画刷颜色填充
            context.stroke();	//使用画笔颜色勾勒边框
        }
    }

```
+ fillStyle和Qt C++中的QBrush类似，用于保存填充图元的画刷，它可以是一个颜色值，也可以是CanvasGradient或CanvasPattern对象
+ 当使用颜色时，支持下列语法：
  + rgb：例如 rgb(255,100,55);
  + rgba：例如（255，100，50，1.0）；
  + #RRGGBB：例如#00FFCC；
  + Qt.rgba（red,green,blue,alpha），例如 Qt.rgba(0.3,0.7,1,1.0)，类似的还有Qt.hsla()、Qt.lighter()等；
  + Context2D的createLinearGradient()方法用于创建一个线性渐变对象，createRadialGradient()方法用于创建一个放射渐变对象（类型为CanvasGradient），CanvasGradient对象的addColorStop()可以添加渐变路径上的关键点的颜色，例如：

```js
import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true

    Canvas {
        width: 400;
        height: 200;

        onPaint: {
            var ctx = getContext("2d");
            ctx.lineWidth = 2;
            var gradient = ctx.createLinearGradient(60,50,180,130);
            gradient.addColorStop(0.0,Qt.rgba(1,0,0,1.0));
            gradient.addColorStop(1.0,Qt.rgba(0,0,1,1.0));
            ctx.strokeStyle = "red";
            ctx.fillStyle = gradient;
            ctx.beginPath();
            ctx.rect(60,50,120,80);
            ctx.fill();
            ctx.stroke();

            gradient = ctx.createRadialGradient(230,160,30,260,200,20);
            gradient.addColorStop(0.0,Qt.rgba(1,0,0,1.0));
            gradient.addColorStop(1.0,Qt.rgba(0,0,1,1.0));
            ctx.fillStyle = gradient;
            ctx.beginPath();
            ctx.rect(200,140,80,80);
            ctx.fill();
            ctx.stroke();
        }
    }
}
```

## 二、绘制路径

使用Context2D绘制路径的一般步骤：

+ 调用beginPath()；
+ 调用moveTo()【移动到】、lineTo()【连线到】、arcTo()【画弧到】、rect()【矩形】、quadraticCurveTo()【二次方贝塞尔曲线】、arc()【弧线】、bezierCurveTo()【三次方贝塞尔曲线】、ellipse()【椭圆】、text()【文字】等构造路径元素的方法；
+ 调用fill()或stroke()；
+ 调用closePath()方法用于结束当前的路径，从路径终点到起点绘制一条直线来封闭路径（可选非必须）；

```js
import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 640
    height: 480
    visible: true

    Canvas {
        width: 400;
        height: 300;
        id: root;

        onPaint: {
            var ctx = getContext("2d");
            ctx.lineWidth = 2;
            ctx.strokeStyle = "red";
            ctx.font = "42px sans-serif";
            var gradient = ctx.createLinearGradient(0,0,width,height);
            gradient.addColorStop(0.0,Qt.rgba(0,1,0,1));
            gradient.addColorStop(1.0,Qt.rgba(0,0,1,1));
            ctx.fillStyle = gradient;

            ctx.beginPath();
            ctx.moveTo(4,4);
            ctx.bezierCurveTo(0,height-1,width-1,height/2,width/4,height/4);
            ctx.lineTo(width/2,height/4);
            ctx.arc(width*5/8,height/4,width/8,Math.PI,0,false);
            ctx.ellipse(width*11/16,height/4,width/8,height/4);
            ctx.lineTo(width/2,height*7/8);
            ctx.text("Complex Path",width/4,height*7/8);
            ctx.fill();
            ctx.stroke();
        }
    }
}
```

## 三、绘制文本

Context2D对象与文本相关的方法有三个：fillText()、strokeText()、text()

+ fillText()方法使用fillStyle填充文字；
+ strokeText()使用strokeStyle描画文字边框；
+ text()方法在路径上添加一串文本作为构成路径的元素之一

```js
import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 640
    height: 480
    visible: true

    Canvas {
        width: 400;
        height: 300;
        id: root;

        onPaint: {
            var ctx = getContext("2d");
            ctx.lineWidth = 2;
            ctx.strokeStyle = "red";
            ctx.font = "42px sans-serif";

            var gradient = ctx.createLinearGradient(0,0,width,height);
            gradient.addColorStop(0.0,Qt.rgba(0,1,0,1));
            gradient.addColorStop(1.0,Qt.rgba(0,0,1,1));
            ctx.fillStyle = gradient;

            ctx.beginPath();
            ctx.text("Fill Text On Path",10,50);
            ctx.fill();

            ctx.fillText("Fill Text",10,100);

            ctx.beginPath();
            ctx.text("Stroke Text On Path",10,150);
            ctx.stroke();

            ctx.strokeText("Stroke Text",10,200);

            ctx.beginPath();
            ctx.text("Stroke and Fill Text on Path",10,250);
            ctx.stroke();
            ctx.fill();
        }
    }

}
```

+ 描述font属性的语法与CSS font属性相同，font属性的默认值为“ 10px sans-serif ”；
+ Context2D的font属性，允许我们按顺序设置字体的下列属性：
  + font-style(可选)：可以取normal、italic、oblique三值之一；
  + font-variant(可选)：可以取normal、small-caps二值之一；
  + font-weight(可选)：可以取normal、bold二值之一，或0-99的数字；
  + font-size：取Npx或Npt，其中N为数字，px代表像素，pt代表点，对于移动设备，使用pt为单位更合适一些，能够适应各种屏幕尺寸；
  + font-family：常见的有serif、sans-serif、cursive、fantasy、monospace，详情参考http://www.w3.org/TR/CSS2/fonts.html#propdef-font-family

## 四、绘制图片

1、drawImage(variant image, real dx, read dy)

它在（dx,dy）位置绘制指定的image对象代表的图片，image可以是一个Image元素、一个图片URL，或者一个CanvasImageData对象

```js
import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 640
    height: 480
    visible: true

    Canvas {
        width: 400;
        height: 300;
        id: root;
        property var dartlikeWeapon: "dartlike_weapon.png"

        onPaint: {
            var ctx = getContext("2d");
            ctx.drawImage(dartlikeWeapon,0,0);
        }

        Component.onCompleted: {
            loadImage(dartlikeWeapon);
            console.log("图片加载：",isImageLoaded(dartlikeWeapon));
        }

        onImageLoaded: {
            requestPaint();
        }
    }
}
```



> 注意：需要确保dartlike_weapon.png和QML文件在同一目录下，因为是通过相对路径引用的；

+ Canvas对象内定义了一个dartlikeWeapon属性来保存图片URL；
+ 然后在Component.onCompleted附加信号处理器内调用Cancas的loadImage()方法来加载图片；该方法会异步加载图片，当图片加载完成时，发射imageLoaded信号；
+ 然后在对应的信号处理器onImageLoaded内调用了requestPaint()方法来重绘Canvas；
  可以通过Canvas的isImageError()、isImageLoaded()两个方法来判断图片是否加载成功，它们接受和loadImage()同样的参数，返回布尔值；
+ 只有成功加载的图片，才可以使用Context2D来绘制：
+ 在Canvas内定义的darklikeWeapon，可以理解为图片索引，加载图片、判断图片是否成功加载、绘制图片，都适用这个索引；

2、一个Canvas可以加载多张图片，既可以加载本地图片，也可以加载网络图片

```js
import QtQuick 2.2

Canvas {
	width: 400;
	height: 300;
	id: root;
	property var dartlikeWeapon: "dartlike_weapon.png";
	property var poster: "https://www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png"

	onPaint: {
		var ctx = getContext("2d");
		ctx.drawImage(poster,120,0);
		ctx.drawImage(dartlikeWeapon,0,0);
	}

	Component.onCompleted: {
		loadImage(dartlikeWeapon);
		loadImage(poster)
	}

	onImageLoaded: requestPaint();
}
```

3、绘制一个Image元素

```js
import QtQuick 2.2

Canvas {
    width: 400;
    height: 300;
    id: root;

    Image {
        id: poter;
        source: "https://www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png";
        visible: false;

        onStatusChanged: {
            if(status == Image.Ready) {
                root.requestPaint();
            }
        }
    }

    onPaint: {
        var ctx = getContext("2d");
        ctx.drawImage(poster,50,0);
    }

    Component.onCompleted: {
        loadImage(poster)
    }

    onImageLoaded: requestPaint();
}
```
## 五、变换

就像QPainter一样，Context2D也支持平移（translate()）、旋转（rotate()）、缩放（scale()）、错切（shear()）等简单的图像变换，它还支持简单的矩阵变换（setTransform()）：

```js
import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 400
    height: 400
    visible: true

    Canvas {
        width: 300;
        height: 300;
        id: root;
        contextType: "2d"

        onPaint: {
            context.lineWidth = 2;
            context.strokeStyle = "blue";
            context.fillStyle = "red";
            context.save();
            context.translate(width/2,height/2);
            context.beginPath();
            context.arc(0,0,30,0,Math.PI*2);
            context.arc(0,0,50,0,Math.PI*2);
            context.arc(0,0,70,0,Math.PI*2);
            context.arc(0,0,90,0,Math.PI*2);
            context.stroke();
            context.restore();

            context.save();
            context.translate(width/2,30);
            context.font = "26px serif";
            context.textAlign = "center";
            context.fillText("concentric circles",0,0);
            context.restore();
        }
    }
}
```

+ 绘制同心圆时，我们以(0,0)做圆心，按道理应该是在画布左上角绘制，但是结果确实在画布中心绘制，是因为使用context.translate(width/2,height/2);将坐标系平移到了画布中心，那么画布中心就是(0,0)点了；
+ 平移变换、绘图操作完成后，应当调用restore()来恢复之前的画布状态，否则发生重绘时（比如用户拖动窗口改变大小），你就看不见绘图的图元了，而要restore()必先save()；
+ translate(real x, real y)方法，平移画布原点，x、y两个参数是相对于当前原点的偏移量；
+ 示例中为了使“concentric circles”在画布上方居中显示，先恢复画布原点到左上角，然后sava()，接着再变换到（width/2,30），接着设置了textAlign属性为“center”，最后调用fillText()在原点处绘制文本，画完后再次调用restore()；

当然，也可以不多次平移，后面的针对平移后的画布原点计算坐标即可，例如上例：

```js
import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 400
    height: 400
    visible: true

    Canvas {
        width: 300;
        height: 300;
        id: root;
        contextType: "2d"

        onPaint: {
            context.lineWidth = 2;
            context.strokeStyle = "blue";
            context.fillStyle = "red";
            //context.save();
            context.translate(width/2,height/2);
            context.beginPath();
            context.arc(0,0,30,0,Math.PI*2);
            context.arc(0,0,50,0,Math.PI*2);
            context.arc(0,0,70,0,Math.PI*2);
            context.arc(0,0,90,0,Math.PI*2);
            context.stroke();
            //context.restore();

            //context.save();
            //context.translate(width/2,30);
            context.font = "26px serif";
            context.textAlign = "center";
            context.fillText("concentric circles",0,-height/2+30);
            //context.restore();
        }
    }
}
```

## 六、裁切

Context2D的clip()方法，让我们能够根据当前路径包围的区域来裁切后续的绘图操作，在此区域之外的图像会被毫不留情的丢弃掉。

步骤如下：

+ 调用beginPath()；
+ 使用lineTo()、arc()、bezierCurveTo()、moveTo()、closePath()等创建路径；
+ 调用clip()确定裁切区域；
+ 绘图，如使用drawImage()；

```js
import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root;
    width: 400
    height: 400
    visible: true

    Canvas {
        width: 400;
        height: 400;
        contextType: "2d";
        property var comicRole: "https://www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png";

        onPaint: {
            context.lineWidth = 2;
            context.strokeStyle = "blue";
            context.fillStyle = Qt.rgba(0.3,0.5,0.7,0.3);

            context.save();
            context.beginPath();
            context.arc(180,150,80,0,Math.PI*2,true);
            context.moveTo(180,230);
            context.lineTo(420,280);
            context.lineTo(160,320);
            context.closePath();
            context.clip();
            context.drawImage(comicRole,0,0,600,600,0,0,400,400);
            context.stroke();
            context.fill();

            context.rotate(Math.PI / 5);
            context.font = " italic bold 32px serif";
            context.fillStyle = "red";
            context.fillText("the text will be clipped",110,70);
            context.restore();
        }

        Component.onCompleted: loadImage(comicRole);
        onImageLoaded: requestPaint();
    }
}
```

## 七、图像合成

Context2D允许我们绘制一个图元，将其与已有的图像按照globalCompositeOperation属性指定的模式合成，globalCompositeOperation支持下列模式：

| 模式 | 详细说明 |
| ---- | -------- |
|source-over|	默认模式，新图形覆盖在原有内容之上|
|source-in	|新图形中仅仅出现与原有内容重叠的部分，其它区域变成透明的|
|source-out	|只有新图形中与原有内容不重叠的部分会被绘制出来|
|source-atop	|新图形中与原有内容重叠的部分会被绘制，并覆盖于原有内容之上|
|destination-over	|在原有内容至下绘制新图形|
|destination-in	|原有内容中与新图形重叠的部分会被保留，其它区域变成透明的|
|destination-out	|原有内容中与新图形不重叠的部分会被保留|
|destination-atop|	原有内容中与新内容重叠的部分会被保留，并且在原有内容至下绘制新图形|
|lighter	|两图形中的重叠部分做加色处理|
|copy|	只有新图形会被保留，其它都被清除掉|
|xor|	重叠部分会变成透明的|