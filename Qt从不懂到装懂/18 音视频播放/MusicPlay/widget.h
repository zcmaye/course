#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QListWidget>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include"volumeslider.h"
#include<QVideoWidget>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initUi();
    void loadMedia(const QString& filePath);    //从指定路径中加载文件
protected:
    void moveEvent(QMoveEvent*ev)override;
    void mousePressEvent(QMouseEvent *event) override;
public slots:
    void onPrevSong();
    void onPlay();
    void onNextSong();
    void onVolume();
    void onPlaylist();
    void onValueChanged(int value);  //音量滑块
    void onCurrentMediaChanged(const QMediaContent &media);

    void onError(QMediaPlayer::Error error);
    //获取歌曲总时长
    void onDurationChanged(qint64 duration);

    //获取歌曲信息
    void onMetaDataAvailableChanged(bool available);


private:
    QPushButton* m_btnPrevSong;
    QPushButton* m_btnPlay;
    QPushButton* m_btnNextSong;
    QPushButton* m_btnVol;      //音量
    QPushButton* m_btnPlaylist; //播放列表
    QPushButton* m_btnClose;    //关闭
    QListWidget* m_playlist;    //播放列表控件

    VolumeSlider* m_sliderVol;       //音量调节滑块
private:
    QMediaPlayer *m_mdiPlayer;      //播放器
    QMediaPlaylist* m_mdiPlaylist;  //播放列表

    QVideoWidget* m_videoWidget;
};
#endif // WIDGET_H
