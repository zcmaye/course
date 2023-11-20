#ifndef VOLUMESLIDER_H
#define VOLUMESLIDER_H

#include <QWidget>
#include <QSlider>
class VolumeSlider : public QWidget
{
    Q_OBJECT
public:
    explicit VolumeSlider(QWidget *parent = nullptr);
    inline QSlider* slider(){return m_slider;}
protected:
    void paintEvent(QPaintEvent *ev) override;
signals:
private:
    QSlider* m_slider;
};

#endif // VOLUMESLIDER_H
