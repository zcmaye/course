# Osg

## 介绍

Osg（OpenSceneGraph）是一个开源的场景图形管理开发库，主要为图形图像应用程序的开发提供场景管理和图形渲染优化功能。也是一个开源的三维实时场景图开发引擎，被广泛应用在可视化（飞行、船舶、车辆、工艺等仿真）、增强现实以及医药、教育、游戏等领域。

OSG可以支持几乎所有的操作系统平台，它使用OpenGL ES使得可以支持手持台、平板以及其它嵌入式设备，使用OpenGL使得其可以在所有的家用电脑以及中型大型机和集群上进行工作。

OSG采用C++书写，使用了标准模版库（STL）。OSG使用场景树的方式来管理三维场景，使用逻辑组来构建场景树，以便进行高效的渲染和遍历等。

OSG使用运行时对各种显卡扩展的实时检测，使得OSG支持从OpenGL1.0到OpenGL4.2以及OpenGL ES 1.1 到2.0的所有设备，所以不管设备新旧，操作系统如何，OSG均能及时识别出它支持什么版本的OGL或OES，然后完好的在其上运行。

OSG采用模块化的设计，降低了OSG内部模块的耦合性，使得用户更加容易理解。并且OSG提供了丰富的示例，通过阅读这些示例可以很好的学习这些模块（学习例子对于学习OSG是非常重要的---FreeSouth注）。模块化的设计使得用户不仅可以只学习和使用自己需要的模块，也可以根据需要定制自己的模块。

## 特点

OSG的关键特点可以使用如下关键词进行总结：高性能、可扩展性、接口化等，具体如下：

- **高性能**

支持基于视锥体的裁切、基于遮档的裁切以及其它的小特性裁切，支持LOD、OpenGL状态排序、VAO、VBO以及着色语言、显示列表等所有的图形学里经常提到的提高效率的招数。它使得OSG成为一个效率高，表现力好的引擎。OSG同样支持客户化的LOD，客户可以自己定制基于分页的四叉树场景结构用来实现复杂场景，具体可以看一下VTP和Delta3D以及osgEarth。

- **生产力**

OSG的核心支持所有的OpenGL扩展，哪怕是刚发布的最新扩展，对其进行封装，优化使得用户不用关注OpenGL那些底层的代码和扩展等，就可以快速的搭建基于最新特性的三维应用程序。

除对底层代码的封装外，OSG还有着与其它系统类似Performer以及OpenInventor等各种现代高级系统的结合，这些结合的案例可以使得用户快速的将OSG与自己的系统相结合提供帮助。OSG和现有与三维相关的，尤其是基于OpenGL的系统有着丰富的结合案例，可以看一下业内知名人士array的osgRecipes、osgXI以及osgCookbook从中获取三维系统与OSG相结合的方案灵感。

- **数据加载**

OSG支持市面上几乎所有的数据格式，无论是图片还是三维模型，以及字体等都能很好的读取。

除了支持单一的格式外，OSG还有VPB、osgEarth以及其它不常用的扩展来支持对海量数据的处理和读取。

- **工具类**

OSG提供一些工具类用来完成一些相互独立的功能，列举如下：

- osgParticle-粒子系统。（OSG的粒子系统从OSG的1.2版本以来，鲜有改变，八年了，它没发展，推荐使用Spark粒子系统，其与OSG的结合array的osgXI还是osgRecipes中有示例）。

  osgText-文字处理与显示。

  osgFX-特殊效果。

  osgShadow-阴影。

  osgManipulator-对模型的局部操作器。

  osgSim-一些可视化效果。

  osgTerrain-地形渲染。（针对地形，推荐使用VPB或osgEarth）。

  osgAnimation-动画。

  osgVolume-体渲染。

- **接口化**

OSG做到不依赖任何与操作系统有关的中间件，只使用标准C++和OpenGL，早期在IRIX上开发，随后扩展到Linux、Windows、Mac、AIX以及Andriod和其它中国人不关心也用得少的操作系统。

OSG的接口化保证了其高度独立，这也使得其除了跨各种平台以外，还可以支持各种UI，比如MFC、QT、SDL、GLUT、WxWidget、Cocoa等。OSG的示例中有这些UI与OSG相结合的例子。（国内使用最多的是QT和MFC）。

- **可伸缩性**

OSG可以运行在多核的CPU和GPU上，这缘于OSG对OpenGL显示列表和纹理单元以及拣选、绘制遍历等过程实施了保护措施，使这些阶段可以单独为一个线程也可以在一个线程中串行执行。可以通过osgViewer以及所有的例子来配置当前OSG应用程序的线程模型。

- **多语言支持**

Lua、Python、甚至JAVA都有与OSG的结合。

## 官方网站

国外官网：[OpenSceneGraph | Objexx Engineering](https://objexx.com/OpenSceneGraph.html)

国内网站：[osg（osg中文社区）](https://www.osgchina.cn/)

GitHub：[GitHub - openscenegraph/OpenSceneGraph: OpenSceneGraph git repository · GitHub](https://github.com/openscenegraph/OpenSceneGraph)

百度网盘：[OpenSceneGraph-3.6.5-VC2022-64-2025-04.7z](https://pan.baidu.com/s/1fahEriHIB06ImoIcS0syBA=jkpn )

# OsgEarth

官网：[Welcome to osgEarth! — osgEarth 3.8.0 documentation](https://docs.osgearth.org/en/latest/)

GitHub:[GitHub - pelicanmapping/osgearth: 3D Maps & Terrain SDK (C++) · GitHub](https://github.com/pelicanmapping/osgearth)