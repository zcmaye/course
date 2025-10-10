## QCustomPlot简介

### 什么是QCustomPlot

QCustomPlot是一个基于Qt框架的C++绘图库，专门用于创建高质量的2D图表和数据可视化。它具有以下特点：

- **轻量级集成**：只需要包含一个.h和.cpp文件即可使用
- **丰富的图表类型**：支持线图、散点图、柱状图、统计箱图、极坐标图等
- **高度可定制**：几乎所有视觉元素都可以自定义
- **优秀的性能**：支持大量数据的实时绘制
- **完善的交互**：内置缩放、拖拽、选择等交互功能
- **导出功能**：支持导出为PDF、PNG、JPG、BMP等格式

### 核心概念与架构

#### QCustomPlot架构概览

QCustomPlot的核心架构包含以下几个重要组件：

```cpp
QCustomPlot (主画布)
├── QCPLayoutGrid (布局管理器)
│   ├── QCPAxisRect (坐标轴矩形区域)
│   │   ├── QCPAxis (坐标轴)
│   │   └── QCPGraph/QCPCurve等 (图形元素)
│   └── QCPLegend (图例)
├── QCPLayer (图层系统)
└── QCPPlottable (可绘制对象基类)
```

####  坐标系统

QCustomPlot默认提供四个坐标轴：

- `xAxis`：底部X轴
- `yAxis`：左侧Y轴
- `xAxis2`：顶部X轴
- `yAxis2`：右侧Y轴

## 常用接口详解

### 基础绘图接口

#### 创建和配置画布

```cpp
// 创建QCustomPlot实例
QCustomPlot *customPlot = new QCustomPlot(parent);

// 设置画布大小
customPlot->setMinimumSize(600, 400);

// 设置背景色
customPlot->setBackground(QBrush(Qt::white));

// 设置抗锯齿
customPlot->setAntialiasedElements(QCP::aeAll);
```

#### 图形(Graph)管理

```cpp
// 添加新图形
QCPGraph *graph = customPlot->addGraph();

// 通过索引获取图形
QCPGraph *graph = customPlot->graph(0);

// 删除图形
customPlot->removeGraph(graph);
// 或通过索引删除
customPlot->removeGraph(0);

// 清空所有图形
customPlot->clearGraphs();

// 获取图形数量
int count = customPlot->graphCount();
```

#### 数据操作

```cpp
// 方式1：使用QVector设置数据
QVector<double> x(100), y(100);
for (int i = 0; i < 100; ++i) {
    x[i] = i / 10.0;
    y[i] = qSin(x[i]);
}
graph->setData(x, y);

// 方式2：逐点添加数据
graph->addData(1.0, 2.0);

// 方式3：使用QCPGraphDataContainer
QSharedPointer<QCPGraphDataContainer> data = 
    QSharedPointer<QCPGraphDataContainer>::create();
data->add(QCPGraphData(1.0, 2.0));
graph->setData(data);

// 清空数据
graph->data()->clear();

// 删除指定范围的数据
graph->data()->removeAfter(10.0);  // 删除x>10的数据
graph->data()->removeBefore(0.0);  // 删除x<0的数据
```

### 坐标轴配置

#### 基本设置

```cpp
// 设置坐标轴标签
customPlot->xAxis->setLabel("时间 (s)");
customPlot->yAxis->setLabel("幅值 (V)");

// 设置坐标轴范围
customPlot->xAxis->setRange(0, 10);
customPlot->yAxis->setRange(-1, 1);

// 自动调整范围以显示所有数据
customPlot->rescaleAxes();
// 只调整某个轴
customPlot->xAxis->rescale();

// 设置刻度
customPlot->xAxis->ticker()->setTickCount(5);  // 主刻度数量
customPlot->xAxis->setSubTicks(true);  // 显示子刻度
customPlot->xAxis->ticker()->setTickStepStrategy(
    QCPAxisTicker::tssMeetTickCount);  // 刻度策略
```

#### 高级配置

```cpp
// 设置对数坐标轴
customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);
QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
customPlot->yAxis->setTicker(logTicker);

// 设置时间坐标轴
QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
dateTicker->setDateTimeFormat("yyyy-MM-dd hh:mm:ss");
customPlot->xAxis->setTicker(dateTicker);

// 设置文本标签坐标轴
QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
textTicker->addTick(1, "一月");
textTicker->addTick(2, "二月");
customPlot->xAxis->setTicker(textTicker);

// 设置网格线
customPlot->xAxis->grid()->setVisible(true);
customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
customPlot->yAxis->grid()->setSubGridVisible(true);
```

### 图形样式设置

#### 线条和点样式

```cpp
// 设置线条样式
graph->setPen(QPen(Qt::blue, 2));  // 颜色和宽度
graph->setPen(QPen(Qt::red, 2, Qt::DashLine));  // 虚线

// 设置点样式
graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
// 自定义散点样式
QCPScatterStyle scatterStyle;
scatterStyle.setShape(QCPScatterStyle::ssSquare);
scatterStyle.setPen(QPen(Qt::blue));
scatterStyle.setBrush(Qt::white);
scatterStyle.setSize(10);
graph->setScatterStyle(scatterStyle);

// 设置线型
graph->setLineStyle(QCPGraph::lsLine);  // 直线连接
graph->setLineStyle(QCPGraph::lsStepLeft);  // 阶梯线
graph->setLineStyle(QCPGraph::lsImpulse);  // 脉冲线
graph->setLineStyle(QCPGraph::lsNone);  // 不显示线
```

#### 填充设置

```cpp
// 设置图形下方填充
graph->setBrush(QBrush(QColor(0, 0, 255, 50)));

// 设置两个图形之间的填充
graph->setChannelFillGraph(otherGraph);
graph->setBrush(QBrush(QColor(0, 255, 0, 50)));
```

#### 图例配置

```cpp
// 显示/隐藏图例
customPlot->legend->setVisible(true);

// 设置图例位置
customPlot->axisRect()->insetLayout()->setInsetAlignment(
    0, Qt::AlignTop | Qt::AlignRight);

// 设置图例样式
customPlot->legend->setBrush(QColor(255, 255, 255, 200));
customPlot->legend->setBorderPen(QPen(Qt::black));
QFont legendFont = font();
legendFont.setPointSize(10);
customPlot->legend->setFont(legendFont);

// 设置图形在图例中的名称
graph->setName("信号1");

// 选择性显示图例项
graph->removeFromLegend();  // 从图例中移除
graph->addToLegend();  // 添加到图例
```

### 其他绘图元素

#### 添加文本

```cpp
// 添加文本标注
QCPItemText *textLabel = new QCPItemText(customPlot);
textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
textLabel->position->setCoords(0.5, 0);
textLabel->setText("图表标题");
textLabel->setFont(QFont(font().family(), 16));
```

#### 添加箭头和线条

```cpp
// 添加箭头
QCPItemArrow *arrow = new QCPItemArrow(customPlot);
arrow->start->setCoords(1, 1);
arrow->end->setCoords(4, 2);
arrow->setHead(QCPLineEnding::esSpikeArrow);

// 添加直线
QCPItemLine *line = new QCPItemLine(customPlot);
line->start->setCoords(0, 0);
line->end->setCoords(1, 1);
line->setPen(QPen(Qt::red, 2, Qt::DashLine));
```

## 交互功能实现

### 4.1 基础交互设置

```
// 设置交互权限
customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | 
                           QCP::iSelectPlottables | QCP::iSelectLegend);

// 常用交互标志
// QCP::iRangeDrag - 拖拽坐标轴范围
// QCP::iRangeZoom - 缩放坐标轴范围
// QCP::iSelectPlottables - 选择图形
// QCP::iSelectAxes - 选择坐标轴
// QCP::iSelectLegend - 选择图例
// QCP::iSelectItems - 选择其他项目
// QCP::iMultiSelect - 多选

// 设置拖拽和缩放的轴
customPlot->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
customPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
```

### 4.2 鼠标事件处理

```
// 连接鼠标事件信号
connect(customPlot, &QCustomPlot::mousePress, 
        this, &MyClass::onMousePress);
connect(customPlot, &QCustomPlot::mouseMove, 
        this, &MyClass::onMouseMove);
connect(customPlot, &QCustomPlot::mouseRelease, 
        this, &MyClass::onMouseRelease);
connect(customPlot, &QCustomPlot::mouseDoubleClick, 
        this, &MyClass::onMouseDoubleClick);
connect(customPlot, &QCustomPlot::mouseWheel, 
        this, &MyClass::onMouseWheel);

// 鼠标点击事件处理示例
void MyClass::onMousePress(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // 获取点击位置的坐标值
        double x = customPlot->xAxis->pixelToCoord(event->pos().x());
        double y = customPlot->yAxis->pixelToCoord(event->pos().y());
        
        // 添加标记点
        QCPItemTracer *tracer = new QCPItemTracer(customPlot);
        tracer->setGraph(customPlot->graph(0));
        tracer->setGraphKey(x);
        tracer->setStyle(QCPItemTracer::tsCircle);
        tracer->setPen(QPen(Qt::red));
        tracer->setBrush(Qt::red);
        tracer->setSize(7);
        
        customPlot->replot();
    }
}
```

### 4.3 选择功能

```
// 设置图形可选择
graph->setSelectable(QCP::stWhole);  // 整体选择
graph->setSelectable(QCP::stSingleData);  // 单点选择
graph->setSelectable(QCP::stDataRange);  // 范围选择

// 设置选中时的样式
QCPSelectionDecorator *decorator = graph->selectionDecorator();
decorator->setPen(QPen(Qt::blue, 3));
decorator->setScatterStyle(
    QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 10));

// 处理选择变化
connect(customPlot, &QCustomPlot::selectionChangedByUser, 
        [=]() {
    for (int i = 0; i < customPlot->graphCount(); ++i) {
        QCPGraph *graph = customPlot->graph(i);
        QCPDataSelection selection = graph->selection();
        if (!selection.isEmpty()) {
            // 处理选中的数据
            foreach (QCPDataRange dataRange, selection.dataRanges()) {
                qDebug() << "选中范围:" << dataRange.begin() << "-" << dataRange.end();
            }
        }
    }
});
```

### 4.4 缩放和平移

```
// 限制缩放范围
customPlot->axisRect()->setRangeZoomFactor(0.85);  // 缩放因子

// 自定义缩放行为
connect(customPlot, &QCustomPlot::mouseWheel, 
        [=](QWheelEvent *event) {
    // 以鼠标位置为中心缩放
    customPlot->axisRect()->setRangeZoomAxes(customPlot->xAxis, customPlot->yAxis);
    
    double factor = 1.0;
    if (event->angleDelta().y() > 0) {
        factor = 0.85;  // 放大
    } else {
        factor = 1.0 / 0.85;  // 缩小
    }
    
    customPlot->xAxis->scaleRange(factor, 
        customPlot->xAxis->pixelToCoord(event->pos().x()));
    customPlot->yAxis->scaleRange(factor, 
        customPlot->yAxis->pixelToCoord(event->pos().y()));
    
    customPlot->replot();
});

// 重置视图
void resetView() {
    customPlot->rescaleAxes();
    customPlot->replot();
}
```

### 4.5 数据提示(ToolTip)

```
// 实现鼠标悬停显示数据值
void MyClass::setupTooltip() {
    // 创建文本项作为tooltip
    QCPItemText *tooltip = new QCPItemText(customPlot);
    tooltip->setPositionAlignment(Qt::AlignTop | Qt::AlignLeft);
    tooltip->position->setType(QCPItemPosition::ptAbsolute);
    tooltip->setTextAlignment(Qt::AlignLeft);
    tooltip->setFont(QFont(font().family(), 9));
    tooltip->setPadding(QMargins(5, 5, 5, 5));
    tooltip->setBrush(QBrush(QColor(255, 255, 200)));
    tooltip->setPen(QPen(Qt::black));
    tooltip->setVisible(false);
    
    connect(customPlot, &QCustomPlot::mouseMove, 
            [=](QMouseEvent *event) {
        double x = customPlot->xAxis->pixelToCoord(event->pos().x());
        double y = customPlot->yAxis->pixelToCoord(event->pos().y());
        
        // 查找最近的数据点
        QCPGraph *graph = customPlot->graph(0);
        if (!graph) return;
        
        QCPGraphDataContainer::const_iterator it = 
            graph->data()->findBegin(x - 1);
        QCPGraphDataContainer::const_iterator end = 
            graph->data()->findEnd(x + 1);
        
        double minDistance = std::numeric_limits<double>::max();
        double nearestX = 0, nearestY = 0;
        
        while (it != end) {
            double distance = qAbs(it->key - x);
            if (distance < minDistance) {
                minDistance = distance;
                nearestX = it->key;
                nearestY = it->value;
            }
            ++it;
        }
        
        if (minDistance < 0.1) {  // 阈值
            tooltip->setText(QString("X: %1\nY: %2")
                           .arg(nearestX, 0, 'f', 2)
                           .arg(nearestY, 0, 'f', 2));
            tooltip->position->setPixelPosition(event->pos());
            tooltip->setVisible(true);
        } else {
            tooltip->setVisible(false);
        }
        
        customPlot->replot();
    });
}
```

## 直角坐标系实战示例

### 5.1 实时数据绘制

```
class RealTimePlot : public QWidget {
private:
    QCustomPlot *customPlot;
    QTimer *dataTimer;
    double timeCounter;
    
public:
    RealTimePlot(QWidget *parent = nullptr) : QWidget(parent) {
        setupPlot();
        setupRealtimeData();
    }
    
    void setupPlot() {
        customPlot = new QCustomPlot(this);
        
        // 添加两个图形
        customPlot->addGraph();  // 蓝线
        customPlot->graph(0)->setPen(QPen(Qt::blue));
        customPlot->graph(0)->setName("Channel 1");
        
        customPlot->addGraph();  // 红线
        customPlot->graph(1)->setPen(QPen(Qt::red));
        customPlot->graph(1)->setName("Channel 2");
        
        // 配置坐标轴
        customPlot->xAxis->setLabel("Time (s)");
        customPlot->yAxis->setLabel("Value");
        customPlot->xAxis->setRange(0, 10);
        customPlot->yAxis->setRange(-2, 2);
        
        // 显示图例
        customPlot->legend->setVisible(true);
        
        // 启用交互
        customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    }
    
    void setupRealtimeData() {
        timeCounter = 0;
        dataTimer = new QTimer(this);
        connect(dataTimer, &QTimer::timeout, this, &RealTimePlot::realtimeDataSlot);
        dataTimer->start(50);  // 20Hz刷新率
    }
    
    void realtimeDataSlot() {
        // 生成新数据
        double key = timeCounter;
        double value1 = qSin(key) + qrand()/(double)RAND_MAX * 0.5;
        double value2 = qCos(key) + qrand()/(double)RAND_MAX * 0.5;
        
        // 添加数据
        customPlot->graph(0)->addData(key, value1);
        customPlot->graph(1)->addData(key, value2);
        
        // 删除超出范围的旧数据
        customPlot->graph(0)->data()->removeBefore(key - 10);
        customPlot->graph(1)->data()->removeBefore(key - 10);
        
        // 自动滚动
        customPlot->xAxis->setRange(key, 10, Qt::AlignRight);
        
        // 自动调整Y轴（可选）
        customPlot->yAxis->rescale();
        
        customPlot->replot();
        
        timeCounter += 0.05;
    }
};
```

### 5.2 多Y轴绘图

```
void setupMultiAxis() {
    QCustomPlot *customPlot = new QCustomPlot();
    
    // 配置第一个Y轴（左侧）
    customPlot->yAxis->setLabel("温度 (°C)");
    customPlot->yAxis->setLabelColor(Qt::blue);
    customPlot->yAxis->setTickLabelColor(Qt::blue);
    
    // 配置第二个Y轴（右侧）
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setLabel("湿度 (%)");
    customPlot->yAxis2->setLabelColor(Qt::red);
    customPlot->yAxis2->setTickLabelColor(Qt::red);
    
    // 添加温度数据（使用左侧Y轴）
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue, 2));
    customPlot->graph(0)->setName("温度");
    customPlot->graph(0)->setValueAxis(customPlot->yAxis);
    
    // 添加湿度数据（使用右侧Y轴）
    customPlot->addGraph(customPlot->xAxis, customPlot->yAxis2);
    customPlot->graph(1)->setPen(QPen(Qt::red, 2));
    customPlot->graph(1)->setName("湿度");
    
    // 生成示例数据
    QVector<double> x(100), temp(100), humidity(100);
    for (int i = 0; i < 100; ++i) {
        x[i] = i;
        temp[i] = 20 + 5 * qSin(i / 10.0);
        humidity[i] = 60 + 20 * qCos(i / 8.0);
    }
    
    customPlot->graph(0)->setData(x, temp);
    customPlot->graph(1)->setData(x, humidity);
    
    // 调整坐标轴范围
    customPlot->xAxis->setRange(0, 100);
    customPlot->yAxis->setRange(10, 30);
    customPlot->yAxis2->setRange(30, 90);
    
    customPlot->replot();
}
```

### 5.3 统计图表

```cpp
void createStatisticalPlot() {
    QCustomPlot *customPlot = new QCustomPlot();
    
    // 创建柱状图
    QCPBars *bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    bars->setName("月销售额");
    bars->setPen(QPen(Qt::blue));
    bars->setBrush(QColor(0, 100, 255, 50));
    
    // 准备数据
    QVector<double> ticks = {1, 2, 3, 4, 5, 6};
    QVector<QString> labels = {"一月", "二月", "三月", "四月", "五月", "六月"};
    QVector<double> values = {15, 23, 18, 29, 35, 21};
    
    // 设置X轴为文本标签
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    for (int i = 0; i < ticks.size(); ++i) {
        textTicker->addTick(ticks[i], labels[i]);
    }
    customPlot->xAxis->setTicker(textTicker);
    
    // 设置数据
    bars->setData(ticks, values);
    
    // 添加误差线
    QCPErrorBars *errorBars = new QCPErrorBars(customPlot->xAxis, customPlot->yAxis);
    errorBars->removeFromLegend();
    errorBars->setDataPlottable(bars);
    QVector<double> errors = {2, 1.5, 2.2, 1.8, 2.5, 1.9};
    errorBars->setData(errors);
    
    // 设置坐标轴
    customPlot->xAxis->setLabel("月份");
    customPlot->yAxis->setLabel("销售额（万元）");
    customPlot->xAxis->setRange(0, 7);
    customPlot->yAxis->setRange(0, 40);
    
    // 添加网格
    customPlot->xAxis->grid()->setVisible(false);
    customPlot->yAxis->grid()->setVisible(true);
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    
    customPlot->legend->setVisible(true);
    customPlot->replot();
}
```

## 性能优化技巧

### 6.1 大数据量优化

```
// 1. 使用数据抽样
void plotLargeData(const QVector<double> &xData, const QVector<double> &yData) {
    if (xData.size() > 10000) {
        // 抽样显示
        int step = xData.size() / 5000;
        QVector<double> xSampled, ySampled;
        
        for (int i = 0; i < xData.size(); i += step) {
            xSampled.append(xData[i]);
            ySampled.append(yData[i]);
        }
        
        graph->setData(xSampled, ySampled);
    } else {
        graph->setData(xData, yData);
    }
}

// 2. 使用自适应采样
graph->setAdaptiveSampling(true);

// 3. 禁用抗锯齿（提升性能）
customPlot->setNotAntialiasedElements(QCP::aeAll);

// 4. 使用OpenGL加速
customPlot->setOpenGl(true);
```

### 6.2 刷新优化

```
// 1. 批量操作时禁用自动重绘
customPlot->setAutoReplot(false);

// 执行批量操作
for (int i = 0; i < 100; ++i) {
    customPlot->graph(0)->addData(i, qrand());
}

// 手动触发一次重绘
customPlot->replot();

// 2. 局部重绘
customPlot->replot(QCustomPlot::rpQueuedReplot);

// 3. 限制刷新率
QTimer *refreshTimer = new QTimer();
refreshTimer->setInterval(33);  // 约30 FPS
connect(refreshTimer, &QTimer::timeout, [=]() {
    if (needsReplot) {
        customPlot->replot();
        needsReplot = false;
    }
});
```

## 导出与打印

```
// 导出为图片
customPlot->savePng("plot.png", 800, 600, 1.0, -1);
customPlot->saveJpg("plot.jpg", 800, 600, 1.0, -1, 95);
customPlot->saveBmp("plot.bmp", 800, 600, 1.0);

// 导出为PDF
customPlot->savePdf("plot.pdf", 800, 600);

// 导出为矢量图
customPlot->saveRastered("plot.png", 800, 600, 2.0);  // 2倍分辨率

// 打印
QPrinter printer;
QPrintDialog printDialog(&printer);
if (printDialog.exec() == QDialog::Accepted) {
    customPlot->print(&printer);
}

// 复制到剪贴板
QApplication::clipboard()->setPixmap(customPlot->toPixmap());
```

## 极坐标系使用与踩坑记录

### 8.1 极坐标系简介

极坐标系使用角度（Angular）和半径（Radial）来定位点，与直角坐标系的x、y定位方式不同。在QCustomPlot中，极坐标系由`QCPPolarAxisAngular`和`QCPPolarAxisRadial`两个类组成。

### 8.2 创建极坐标系的正确步骤

```
// 1. 清空默认的直角坐标系布局（重要！）
customPlot->plotLayout()->clear();

// 2. 创建角度轴
QCPPolarAxisAngular *angularAxis = new QCPPolarAxisAngular(customPlot);
customPlot->plotLayout()->addElement(0, 0, angularAxis);

// 3. 使用angularAxis内置的radialAxis（不要自己创建新的！）
QCPPolarAxisRadial *radialAxis = angularAxis->radialAxis();

// 4. 设置坐标轴范围
angularAxis->setRange(0, 360);
radialAxis->setRange(0, 10);

// 5. 创建极坐标图形
QCPPolarGraph *polarGraph = new QCPPolarGraph(angularAxis, radialAxis);
```

### 8.3 踩坑记录与解决方案

#### 坑1：必须清空默认布局

**问题描述**：QCustomPlot默认会创建一个包含直角坐标系的`QCPAxisRect`，如果不清空这个布局直接添加极坐标系，会导致布局混乱或极坐标系无法正常显示。

**解决方案**：

```
// 在创建极坐标系前，必须先清空默认布局
customPlot->plotLayout()->clear();
```

**注意事项**：清空布局会同时清除Legend（图例），需要重新创建和配置图例。

#### 坑2：RadialAxis的创建陷阱

**问题描述**：`QCPPolarAxisAngular`在构造时会自动创建一个内置的`QCPPolarAxisRadial`，如果手动创建新的RadialAxis会导致坐标系关联错误。

**错误示例**：

```
// 错误做法
QCPPolarAxisAngular *angularAxis = new QCPPolarAxisAngular(customPlot);
QCPPolarAxisRadial *radialAxis = new QCPPolarAxisRadial(angularAxis); // 不要这样做！
```

**正确做法**：

```
// 正确做法：使用内置的radialAxis
QCPPolarAxisAngular *angularAxis = new QCPPolarAxisAngular(customPlot);
QCPPolarAxisRadial *radialAxis = angularAxis->radialAxis(); // 获取内置的radialAxis
```

#### 坑3：Graph管理权归属问题

**问题描述**：极坐标系中的Graph是由`QCPPolarAxisAngular`管理的，而不是由QCustomPlot直接管理。这导致清除Graph时不能使用常规方法。

**错误示例**：

```
// 这在极坐标系中不会生效
customPlot->clearGraphs();
```

**正确做法**：

```
// 需要通过angularAxis逐个删除
while (angularAxis->graphCount() > 0) {
    angularAxis->removeGraph(angularAxis->graph(0));
}

// 或者使用循环删除指定的graph
for (int i = angularAxis->graphCount() - 1; i >= 0; --i) {
    angularAxis->removeGraph(angularAxis->graph(i));
}
```

**问题延伸**：QCustomPlot没有提供类似`clearGraphs()`的批量清除接口，只能通过循环逐个删除，这在处理大量图形时可能影响性能。

#### 坑4：Legend（图例）的独立处理

**问题描述**：极坐标系的图例需要单独创建和布局，且存在一些显示问题。

**创建图例的方法**：

```
// 创建新的图例
QCPLegend *legend = new QCPLegend();
customPlot->plotLayout()->addElement(1, 0, legend);

// 将极坐标图形添加到图例
QCPPolarGraph *graph = new QCPPolarGraph(angularAxis, radialAxis);
graph->setName("数据系列1");
legend->addItem(new QCPPlottableLegendItem(legend, graph));
```

**未解决的问题**：

- 图例缺少外边框（border），视觉效果不理想
- 可能需要自定义绘制或继承QCPLegend类来添加边框功能

**临时解决方案**：

```
// 尝试通过设置背景色来改善视觉效果
legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
legend->setBorderPen(QPen(Qt::black)); // 这个可能不生效
```

### 8.4 完整的极坐标系示例

```
class PolarPlotWidget : public QWidget {
private:
    QCustomPlot *customPlot;
    QCPPolarAxisAngular *angularAxis;
    QCPPolarAxisRadial *radialAxis;
    
public:
    PolarPlotWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setupPolarPlot();
        addPolarData();
    }
    
    void setupPolarPlot() {
        customPlot = new QCustomPlot(this);
        
        // 1. 清空默认布局
        customPlot->plotLayout()->clear();
        
        // 2. 创建极坐标系
        angularAxis = new QCPPolarAxisAngular(customPlot);
        customPlot->plotLayout()->addElement(0, 0, angularAxis);
        
        // 3. 获取径向轴
        radialAxis = angularAxis->radialAxis();
        
        // 4. 配置角度轴
        angularAxis->setRange(0, 360);
        angularAxis->setTickStep(30);
        angularAxis->setSubTickCount(5);
        angularAxis->grid()->setVisible(true);
        angularAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
        
        // 5. 配置径向轴
        radialAxis->setRange(0, 100);
        radialAxis->setTickStep(20);
        radialAxis->setSubTickCount(4);
        radialAxis->setTickLabelRotation(0);
        
        // 6. 设置标签
        radialAxis->setLabel("幅值");
        angularAxis->setTickLabels(true);
        
        // 7. 创建图例（可选）
        QCPLegend *legend = new QCPLegend();
        customPlot->plotLayout()->addElement(1, 0, legend);
        legend->setVisible(true);
    }
    
    void addPolarData() {
        // 创建三个不同的数据系列
        
        // 系列1：正弦波形
        QCPPolarGraph *graph1 = new QCPPolarGraph(angularAxis, radialAxis);
        QVector<double> theta1, r1;
        for (int i = 0; i <= 360; i += 5) {
            theta1.append(i);
            r1.append(50 + 30 * qSin(qDegreesToRadians(i * 3.0)));
        }
        graph1->setData(theta1, r1);
        graph1->setPen(QPen(Qt::blue, 2));
        graph1->setName("正弦波");
        
        // 系列2：心形线
        QCPPolarGraph *graph2 = new QCPPolarGraph(angularAxis, radialAxis);
        QVector<double> theta2, r2;
        for (int i = 0; i <= 360; i += 2) {
            double t = qDegreesToRadians(i);
            theta2.append(i);
            r2.append(40 * (1 + qCos(t)));
        }
        graph2->setData(theta2, r2);
        graph2->setPen(QPen(Qt::red, 2));
        graph2->setName("心形线");
        
        // 系列3：螺旋线
        QCPPolarGraph *graph3 = new QCPPolarGraph(angularAxis, radialAxis);
        QVector<double> theta3, r3;
        for (int i = 0; i <= 720; i += 5) {
            theta3.append(i);
            r3.append(i / 10.0);
        }
        graph3->setData(theta3, r3);
        graph3->setPen(QPen(Qt::green, 2));
        graph3->setName("螺旋线");
        
        customPlot->replot();
    }
    
    // 清空所有极坐标图形
    void clearAllGraphs() {
        while (angularAxis->graphCount() > 0) {
            angularAxis->removeGraph(angularAxis->graph(0));
        }
        customPlot->replot();
    }
    
    // 动态更新数据
    void updatePolarData() {
        static double phase = 0;
        
        if (angularAxis->graphCount() > 0) {
            QCPPolarGraph *graph = angularAxis->graph(0);
            QVector<double> theta, r;
            
            for (int i = 0; i <= 360; i += 5) {
                theta.append(i);
                r.append(50 + 30 * qSin(qDegreesToRadians(i * 3.0 + phase)));
            }
            
            graph->setData(theta, r);
            customPlot->replot();
            
            phase += 10;
            if (phase >= 360) phase = 0;
        }
    }
};
```

### 8.5 极坐标系与直角坐标系的切换

```
class CoordinateSystemSwitcher : public QWidget {
private:
    QCustomPlot *customPlot;
    bool isPolar;
    
public:
    void switchToCartesian() {
        // 清空当前布局
        customPlot->plotLayout()->clear();
        
        // 创建直角坐标系
        QCPAxisRect *axisRect = new QCPAxisRect(customPlot);
        customPlot->plotLayout()->addElement(0, 0, axisRect);
        
        // 恢复默认坐标轴
        customPlot->xAxis = axisRect->axis(QCPAxis::atBottom);
        customPlot->yAxis = axisRect->axis(QCPAxis::atLeft);
        customPlot->xAxis2 = axisRect->axis(QCPAxis::atTop);
        customPlot->yAxis2 = axisRect->axis(QCPAxis::atRight);
        
        // 添加图例
        customPlot->legend = new QCPLegend();
        axisRect->insetLayout()->addElement(customPlot->legend, Qt::AlignTop | Qt::AlignRight);
        
        isPolar = false;
        customPlot->replot();
    }
    
    void switchToPolar() {
        // 清空当前布局
        customPlot->plotLayout()->clear();
        
        // 创建极坐标系
        QCPPolarAxisAngular *angularAxis = new QCPPolarAxisAngular(customPlot);
        customPlot->plotLayout()->addElement(0, 0, angularAxis);
        
        // 创建新图例
        QCPLegend *legend = new QCPLegend();
        customPlot->plotLayout()->addElement(1, 0, legend);
        
        isPolar = true;
        customPlot->replot();
    }
};
```

### 8.6 极坐标系性能优化建议

```
// 1. 批量操作时禁用自动重绘
customPlot->setAutoReplot(false);

// 添加多个极坐标图形
for (int i = 0; i < 10; ++i) {
    QCPPolarGraph *graph = new QCPPolarGraph(angularAxis, radialAxis);
    // 设置数据...
}

// 完成后手动重绘一次
customPlot->replot();

// 2. 数据抽样（对于大量数据点）
void addSampledPolarData(const QVector<double> &fullTheta, 
                         const QVector<double> &fullR) {
    if (fullTheta.size() > 5000) {
        int step = fullTheta.size() / 1000;
        QVector<double> sampledTheta, sampledR;
        
        for (int i = 0; i < fullTheta.size(); i += step) {
            sampledTheta.append(fullTheta[i]);
            sampledR.append(fullR[i]);
        }
        
        polarGraph->setData(sampledTheta, sampledR);
    } else {
        polarGraph->setData(fullTheta, fullR);
    }
}

// 3. 合理设置刷新频率（实时数据）
QTimer *updateTimer = new QTimer(this);
updateTimer->setInterval(50);  // 20 FPS
connect(updateTimer, &QTimer::timeout, this, &MyClass::updatePolarData);
```

## 总结

QCustomPlot是一个功能强大的Qt绘图库，虽然在某些方面（特别是极坐标系）的接口设计存在一些不够友好的地方，但通过正确理解其设计逻辑和采用适当的解决方案，仍然可以很好地满足各种绘图需求。

### 主要注意事项总结

**直角坐标系使用要点**：

1. 合理使用图层系统，将静态和动态元素分离
2. 大数据量时启用自适应采样或手动抽样
3. 批量操作时禁用自动重绘
4. 充分利用内置的交互功能

**极坐标系使用要点**：

1. 必须清空默认布局才能创建极坐标系
2. 使用AngularAxis内置的RadialAxis，不要手动创建
3. Graph由AngularAxis管理，清除时需要特殊处理
4. 图例需要单独创建和配置
5. 缺少批量操作接口，需要通过循环处理

### 未来改进建议

如果QCustomPlot能在以下方面改进，将大大提升极坐标系的使用体验：

- 提供统一的Graph管理接口
- 添加批量清除Graph的方法
- 改善图例的默认样式和边框支持
- 提供更便捷的坐标系切换机制

## 参考资源

- [QCustomPlot官方文档](https://www.qcustomplot.com/documentation/)
- [QCustomPlot示例代码](https://www.qcustomplot.com/demos.html)
- [Qt官方文档](https://doc.qt.io/)
- [QCustomPlot论坛](https://www.qcustomplot.com/index.php/support/forum)