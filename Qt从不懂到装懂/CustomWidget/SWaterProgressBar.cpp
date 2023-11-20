#include "SWaterProgressBar.h"
#include <QPainter>
#include <QPainterPath>
#include <QTimer>


SWaterProgressBar::SWaterProgressBar(QWidget* parent)
	:QWidget(parent)
{
	d.reset(new SWaterProgressBarPrivate);
	resize(100, 100);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SWaterProgressBar::updaterWater);
    timer->start(30);//定时30毫秒
}

void SWaterProgressBar::resizeEvent(QResizeEvent* ev)
{
    d->minRadius = qMin(width(), height()) / 2;
}

void SWaterProgressBar::paintEvent(QPaintEvent* ev)
{
	Q_UNUSED(ev);
    //d->value 在range内所占比例
    d->scale = (qreal)(qAbs(d->value - d->minValue)) / (qAbs(d->maxValue - d->minValue));
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);	//设置抗锯齿
	painter.translate(width() / 2, height() / 2);	//设置坐标原点为控件中心
	//painter.scale(side / 200.0, side / 200.0);//设置坐标系拉伸为200*200
	drawBackground(&painter);
    drawWater(&painter);
	drawText(&painter);
 
}

void SWaterProgressBar::drawBackground(QPainter* painter)
{
	painter->save();

	painter->setPen(Qt::NoPen);
	painter->setBrush(QColor(40, 40, 40));
	QRect rect(-d->minRadius, -d->minRadius, d->minRadius * 2, d->minRadius * 2);
	painter->drawEllipse(rect);

	painter->restore();
}

void SWaterProgressBar::drawText(QPainter* painter)
{
    if (d->textVisible)
    {
        painter->save();
        d->text = QString("%1%").arg(d->scale * 100,2,'f', 1);
        //设置字体大小
        //QFont font = painter->font();
        //font.setPixelSize(30);
        //painter->setFont(font);
        //设置画笔
        painter->setPen(QPen(Qt::white, 4));
        //绘制文本
        QRect r(-d->minRadius, -d->minRadius, d->minRadius * 2, d->minRadius * 2);
        painter->drawText(r, Qt::AlignCenter, d->text);

        painter->restore();
    }
}

void SWaterProgressBar::drawWater(QPainter* painter)
{
    if (d->value == d->minValue) //没波浪，不用画
    {
        return;
    }
    else if (d->value == d->maxValue) //波浪满，直接画圆
    {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(QColor(100, 180, 250, 230)));
        painter->drawEllipse(QRect(-d->minRadius, -d->minRadius, d->minRadius * 2, d->minRadius * 2));
        painter->restore();
    }
    else//画波浪
    {
        int side = qMin(width(), height());
        int height = side/2 - d->scale * side;  //100/2 - 0.5 * 100
        painter->save();
        QPainterPath wavePath; //波浪区域
        QPainterPath wavePath2; //波浪区域
      
        //1.8 角速度
        //4   振幅
        //height y轴相对远点偏移
        //d->yOffset x=0时的相位；反映在坐标系上则为图像的左右移动。
        //x * M_PI / 180  把x当做角度，转成弧度
        wavePath.moveTo(-d->minRadius, d->minRadius);       //第一点坐标为（0,height）;
        for (int x = -d->minRadius; x <= d->minRadius; x++)  //x从0~w的值而改变，从而得到正弦曲线
        {
            double waveY = 4 * qSin(1.8 * (x * M_PI / 180 + d->yOffset)) + height;// waveY随着x的值改变而改变，从而得到正弦曲线
            wavePath.lineTo(x, waveY);   //从上一个绘制点画一条线到（x，waveY）；
        }
        wavePath.lineTo(d->minRadius, d->minRadius); //右下角，坐标（width, height），移动到右下角结束点,整体形成一个闭合路径

        wavePath2.moveTo(-d->minRadius, d->minRadius);//第一点坐标为（0,height）;
        for (int x = -d->minRadius; x <= d->minRadius; x++)  //x从0~w的值而改变，从而得到正弦曲线
        {
           double waveY = 4 * qSin(1.8 * (x * M_PI / 180 + d->yOffset + 2)) + height;// waveY随着x的值改变而改变，从而得到正弦曲线
           wavePath2.lineTo(x, waveY);   //从上一个绘制点画一条线到（x，waveY）；
        }
        wavePath2.lineTo(d->minRadius, d->minRadius); //右下角，坐标（width, height），移动到右下角结束点,整体形成一个闭合路径

        QPainterPath bigPath;
        bigPath.addEllipse(QRect(-d->minRadius, -d->minRadius, d->minRadius * 2, d->minRadius * 2));
        wavePath = bigPath.intersected(wavePath);
        wavePath2 = bigPath.intersected(wavePath2);

        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(QColor(100, 184, 255, 80)));
        painter->drawPath(wavePath);      //绘制路径
        painter->setBrush(QBrush(QColor(100, 180, 250, 230)));
        painter->drawPath(wavePath2);      //绘制路径
        painter->restore();
    }
}

int SWaterProgressBar::minimum() const
{
    return d->minValue;
}

int SWaterProgressBar::maximum() const
{
    return d->maxValue;
}

int SWaterProgressBar::value() const
{
    return d->value;
}

QString SWaterProgressBar::text() const
{
    return d->text;
}

void SWaterProgressBar::setTextVisible(bool visible)
{
    d->textVisible = visible;
}

bool SWaterProgressBar::isTextVisible() const
{
    return d->textVisible;
}

void SWaterProgressBar::reset()
{
    d->minValue = 0;
    d->maxValue = 100;
}
void SWaterProgressBar::setRange(int minimum, int maximum)
{
    d->minValue = minimum;
    d->maxValue = maximum;
    d->value = minimum;
}
void SWaterProgressBar::setMinimum(int minimum)
{
    d->minValue = minimum;
    d->value = minimum;
}
void SWaterProgressBar::setMaximum(int maximum)
{
    d->maxValue = maximum;
}
void SWaterProgressBar::setValue(int value)
{
    if (value != d->value)
    {
        d->value = value;
        emit valueChanged(value);
    }   
}


void SWaterProgressBar::updaterWater()
{
    d->yOffset += 0.15;//波浪偏移
    if (d->yOffset >= 360)
        d->yOffset = 0;
    update();
}
