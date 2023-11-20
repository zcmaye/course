#include "widget.h"
#include<QHBoxLayout>
#include<QFile>
#include<QDebug>
#include<QPropertyAnimation>
#include"eventfilterobject.h"
#include<QDir>
#include<QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    ,m_mdiPlayer(new QMediaPlayer)
    ,m_mdiPlaylist(new QMediaPlaylist)
    ,m_videoWidget(new QVideoWidget)
{

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    m_mdiPlayer->setPlaylist(m_mdiPlaylist);
    //切歌之后，在list中设为选中
    connect(m_mdiPlayer,&QMediaPlayer::currentMediaChanged,this,&Widget::onCurrentMediaChanged);
    connect(m_mdiPlayer,QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),this,&Widget::onError);
    connect(m_mdiPlayer,&QMediaPlayer::metaDataAvailableChanged,this,&Widget::onMetaDataAvailableChanged);
    connect(m_mdiPlayer,&QMediaPlayer::durationChanged,this,&Widget::onDurationChanged);

    initUi();
    resize(300,60);
    this->installEventFilter(new eventFilterObject);
    QFile file("://images/styles.css");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning("styles.css open falied");
    }
    this->setStyleSheet(file.readAll());

    loadMedia("../MusicPlay/media");

}

Widget::~Widget()
{
}

void Widget::initUi()
{
    m_btnPrevSong = new QPushButton;
    m_btnPlay = new QPushButton;
    m_btnNextSong = new QPushButton;
    m_btnVol = new QPushButton;
    m_btnPlaylist = new QPushButton;
    m_btnClose = new QPushButton;
    m_playlist = new QListWidget;

    m_sliderVol = new VolumeSlider(this);
    m_sliderVol->setObjectName("sliderVol");
    m_sliderVol->slider()->setValue(m_mdiPlayer->volume());


    m_btnPrevSong->setObjectName("btnPrevSong");
    m_btnPlay->setObjectName("btnPlay");
    m_btnNextSong->setObjectName("btnNextSong");
    m_btnVol->setObjectName("btnVol");
    m_btnPlaylist->setObjectName("btnPlaylist");
    m_btnClose->setObjectName("btnClose");
    m_playlist->setObjectName("playlist");

    m_playlist->setWindowFlags(m_playlist->windowFlags() | Qt::WindowType::FramelessWindowHint | Qt::WindowType::Tool);
    m_playlist->setAlternatingRowColors(true);

    auto *hlayout = new QHBoxLayout(this);
    hlayout->setMargin(0);
    hlayout->setSpacing(0);
    hlayout->addWidget(m_btnPrevSong);
    hlayout->addWidget(m_btnPlay);
    hlayout->addWidget(m_btnNextSong);
    hlayout->addWidget(m_btnVol);
    hlayout->addWidget(m_btnPlaylist);

    QVBoxLayout* vlayout= new QVBoxLayout;
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_btnClose);
    vlayout->addStretch();
    hlayout->addLayout(vlayout);

    connect(m_btnClose,&QPushButton::released,this,&QWidget::close);
    connect(m_btnPrevSong,&QPushButton::released,this,&Widget::onPrevSong);
    connect(m_btnPlay,&QPushButton::released,this,&Widget::onPlay);
    connect(m_btnNextSong,&QPushButton::released,this,&Widget::onNextSong);
    connect(m_btnVol,&QPushButton::released,this,&Widget::onVolume);
    connect(m_btnPlaylist,&QPushButton::released,this,&Widget::onPlaylist);

    connect(m_sliderVol->slider(),&QSlider::valueChanged,this,&Widget::onValueChanged);

    connect(m_playlist,&QListWidget::currentRowChanged,this,[=](int val)
    {
        m_mdiPlaylist->setCurrentIndex(val);
        if(m_mdiPlayer->state() == QMediaPlayer::State::StoppedState)
        {
            m_mdiPlayer->play();
        }
    });
}

void Widget::loadMedia(const QString &filePath)
{
    QDir dir(filePath);
    QStringList list = dir.entryList(QStringList()<<"*.mp3"<<"*.mp4");
    for(auto file : list)
    {
        m_mdiPlaylist->addMedia(QUrl::fromLocalFile(filePath+"/"+file));
        m_playlist->addItem(file);
    }
}

void Widget::moveEvent(QMoveEvent *ev)
{
    m_playlist->move(frameGeometry().bottomLeft());
    m_playlist->setFixedWidth(this->width());
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    m_sliderVol->hide();
}

void Widget::onPrevSong()
{
    qDebug()<<"onPrevSong";
    m_mdiPlaylist->previous();
}

void Widget::onPlay()
{
    static bool playState = false;  //false为暂停状态  true为播放状态
    QString img = playState?"play":"pause";

    m_btnPlay->setStyleSheet(QString("QPushButton{image:url(:/images/%1.png);}"
                                             "QPushButton:hover{image:url(:/images/%1-hover.png);}").arg(img));
    qDebug()<<"onPlay";
    playState?m_mdiPlayer->stop():m_mdiPlayer->play();


    playState = !playState;
}

void Widget::onNextSong()
{
    qDebug()<<"onNextSong";
    m_mdiPlaylist->next();
}

void Widget::onVolume()
{
    m_sliderVol->setHidden(!m_sliderVol->isHidden());
    m_sliderVol->move(mapToGlobal(m_btnVol->pos()-QPoint((m_sliderVol->width()-m_btnVol->width())/2,40)));

    qDebug()<<"onVolume";
}

void Widget::onPlaylist()
{
    m_playlist->move(frameGeometry().bottomLeft());
    m_playlist->setFixedWidth(this->width());

    QPropertyAnimation * anim = new QPropertyAnimation(m_playlist,"size",this);
    anim->setStartValue(QSize(m_playlist->width(),0));
    anim->setEndValue(QSize(m_playlist->width(),250));
    anim->setDuration(500);
    //展开列表处理
    if(m_playlist->isHidden())
    {
        anim->setDirection(QPropertyAnimation::Direction::Forward);
        m_playlist->show();
    }
    else
    {
        anim->setDirection(QPropertyAnimation::Direction::Backward);
    }
    //折叠处理
    connect(anim,&QPropertyAnimation::finished,this,[=]()
    {
        //如果动画是反向的，而且list是显示的，动画结束则隐藏list
        if(anim->direction() == QPropertyAnimation::Direction::Backward && !m_playlist->isHidden())
        {
            m_playlist->hide();
        }
    });
    anim->start();
    qDebug()<<"onPlaylist";
}

void Widget::onValueChanged(int value)
{
     QString img = value?"volume":"mute";
     m_btnVol->setStyleSheet(QString("QPushButton{image:url(:/images/%1.png);}"
                                     "QPushButton:hover{image:url(:/images/%1-hover.png);}").arg(img));
     m_mdiPlayer->setVolume(value);
}

void Widget::onCurrentMediaChanged(const QMediaContent &media)
{
    QString filename = media.request().url().fileName();
    auto  items = m_playlist->findItems(filename,Qt::MatchFlag::MatchWrap);
    if(!items.isEmpty())
    {
        m_playlist->setCurrentItem(items.first());
    }
    if(m_mdiPlayer->currentMedia().request().url().fileName().contains(".mp4"))
    {
        m_mdiPlayer->setVideoOutput(m_videoWidget);
        m_videoWidget->show();
    }
    else
    {
        m_videoWidget->hide();
    }

}

void Widget::onError(QMediaPlayer::Error error)
{
    switch (error)
    {
    case QMediaPlayer::NoError:
        qWarning("没有错误");
        break;
    case QMediaPlayer::ResourceError:
        qWarning("媒体资源无法解析");
        break;
    case QMediaPlayer::FormatError:
        qWarning("不(完全)支持媒体资源的格式。 重新播放仍然是可能的，但没有音频或视频组件。");
        break;
    case QMediaPlayer::NetworkError:
        qWarning("网络错误");
        break;
    case QMediaPlayer::AccessDeniedError:
        qWarning("没有播放媒体资源的适当权限。");
        break;
    case QMediaPlayer::ServiceMissingError:
        qWarning("没有找到有效的播放服务，播放无法继续。");
        break;
    }
}

void Widget::onDurationChanged(qint64 duration)
{
    qDebug()<<m_mdiPlayer->currentMedia().request().url()<<"time is"<<duration;
}

void Widget::onMetaDataAvailableChanged(bool available)
{
    if(available)
    {
        auto pix = QPixmap::fromImage(m_mdiPlayer->metaData("CoverArtImage").value<QImage>());
        qDebug()<<"pixmap"<<pix<<m_mdiPlayer->metaData("Title").toString()
               <<m_mdiPlayer->metaData("Genre")
              <<m_mdiPlayer->metaData("SubTitle")
             <<m_mdiPlayer->metaData("Author")
            <<m_mdiPlayer->metaData("Comment")
           <<m_mdiPlayer->metaData("Description")
          <<m_mdiPlayer->metaData("Category")
         <<m_mdiPlayer->metaData("Year")
        <<m_mdiPlayer->metaData("Date")
        <<m_mdiPlayer->metaData("UserRating")
        <<m_mdiPlayer->metaData("Keywords")
        <<m_mdiPlayer->metaData("Language")
        <<m_mdiPlayer->metaData("Copyright")
        <<m_mdiPlayer->metaData("Size")
        <<m_mdiPlayer->metaData("MediaType")
        <<m_mdiPlayer->metaData("Duration");
    }
}

