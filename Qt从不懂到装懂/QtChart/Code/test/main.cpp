#include<QApplication>
#include<QChart>
#include<QChartView>

//折线
#include<QLineSeries>
#include<QLegendMarker>
#include<QEasingCurve>

void lineChart();
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	lineChart();

	return a.exec();
}

//折线图
void lineChart()
{
	//创建图表（实际上不需要自己创建，ChartView自带，直接获取即可）
	//auto chart = new QChart;
	
	//创建图表试图
	auto view = new QChartView;
	view->resize(640, 480);
	//设置渲染提示
	view->setRenderHint(QPainter::RenderHint::Antialiasing);
	view->show();


	//准备数据
	auto series = new QLineSeries;
	series->setName("测试数据");		//数据名称
	*series << QPointF(1, 2) << QPointF(2, 6) << QPointF(3, 8);
	series->append(4, 4.5);

	//设置数据对应的线条显示的颜色
	series->setColor(Qt::red);
	series->setMarkerSize(64);

	{
		//把数据交给图表
		view->chart()->addSeries(series);
		//设置图表标题
		view->chart()->setTitle("折线图测试");
		view->chart()->setTitleFont(QFont("楷体", 20));
		view->chart()->setTitleBrush(Qt::gray);
		//设置整个图表区背景
		view->chart()->setBackgroundBrush(Qt::gray);	//背景颜色
		view->chart()->setBackgroundRoundness(20);	//圆角半径
		view->chart()->setBackgroundPen(QPen(Qt::yellow, 2));	//背景边框颜色
		view->chart()->setBackgroundVisible(true);	//是否显示背景
		//背景是否启用阴影效果，默认禁用
		view->chart()->setDropShadowEnabled(true);
		//设置图形图背景
		view->chart()->setPlotAreaBackgroundBrush(QColor(93, 107, 153));
		view->chart()->setPlotAreaBackgroundPen(QPen(QColor(201, 180, 127), 2));
		view->chart()->setPlotAreaBackgroundVisible(false);
		//设置主题
		view->chart()->setTheme(QChart::ChartTheme::ChartThemeDark);
		//设置动画
		view->chart()->setAnimationOptions(QChart::AnimationOption::AllAnimations);
		view->chart()->setAnimationDuration(2000);
		view->chart()->setAnimationEasingCurve(QEasingCurve::Type::OutBounce);
	}

	{
		//图例
		auto markers = view->chart()->legend()->markers(series);
		markers.first()->setBrush(Qt::blue);
		markers.first()->setLabel("hello");
		markers.first()->setLabelBrush(Qt::darkMagenta);
		markers.first()->setShape(QLegend::MarkerShape::MarkerShapeRotatedRectangle);
	}

	//创建默认坐标轴(必须在数据添加完成之后创建)
	view->chart()->createDefaultAxes();

	//添加坐标轴

}
