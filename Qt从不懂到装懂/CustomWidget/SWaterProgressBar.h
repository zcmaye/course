#ifndef _SWATERPROGRESSBAR_H_
#define _SWATERPROGRESSBAR_H_

#include <QWidget>
#include "CustomAnimation/SineWave.h"
struct SWaterProgressBarPrivate
{
	int value = 0;			//当前值
	qreal yOffset = 0;		//波浪偏移
	int minValue = 0;
	int maxValue = 100;
	QString text;
	bool textVisible = true;
	int minRadius = 0;		//qMin(width(),height())/2
	qreal scale = 0.;		//value 在最大值和最小值中的占比
};

class SWaterProgressBar : public QWidget
{
	Q_OBJECT
public:
	explicit SWaterProgressBar(QWidget* parent = nullptr);

	int minimum() const;
	int maximum() const;

	int value() const;

	virtual QString text() const;
	void setTextVisible(bool visible);
	bool isTextVisible() const;

protected:
	void resizeEvent(QResizeEvent* ev)override;
	void paintEvent(QPaintEvent* ev)override;
	void drawBackground(QPainter* painter);
	void drawText(QPainter* painter);
	void drawWater(QPainter* painter);
public Q_SLOTS:
	void updaterWater();

	void reset();
	void setRange(int minimum, int maximum);
	void setMinimum(int minimum);
	void setMaximum(int maximum);
	void setValue(int value);
Q_SIGNALS:
	void valueChanged(int value);
private:
	QScopedPointer<SWaterProgressBarPrivate> d;
};

#endif // !_SWATERPROGRESSBAR_H_
