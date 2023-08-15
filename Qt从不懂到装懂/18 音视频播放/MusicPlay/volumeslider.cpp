#include "volumeslider.h"
#include<QPainter>
#include<QBoxLayout>
VolumeSlider::VolumeSlider(QWidget *parent) : QWidget(parent)
  ,m_slider(new QSlider(this))
{
    m_slider->setOrientation(Qt::Orientation::Horizontal);
    m_slider->setRange(0,100);


    this->setWindowFlags(this->windowFlags()| Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(125,50);


    auto* layout = new QVBoxLayout(this);
    layout->addWidget(m_slider);
    layout->addSpacing(20);
}

void VolumeSlider::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    //painter.setPen(Qt::PenStyle::NoPen);
    painter.setBrush(QColor(255,255,255,240));

    painter.drawRoundedRect(rect().adjusted(0,0,0,-20),5,5);

    int centerX = width()/2;
    QPoint tri[4]={QPoint(centerX-10,50-20),QPoint(centerX+10,50-20),
                   QPoint(centerX+1,50-10),QPoint(centerX-1,50-10)};
    painter.drawPolygon(tri,4);
}
