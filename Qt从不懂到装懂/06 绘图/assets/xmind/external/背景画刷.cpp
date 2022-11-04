    void paintEvent(QPaintEvent* ev)
    {
        QPainter painter(this);
        painter.setBackgroundMode(Qt::OpaqueMode);
        painter.setBackground(QBrush(Qt::GlobalColor::yellow));

        painter.setPen(QPen(Qt::DotLine));
        painter.drawLine(0, 0, 640, 480);

        auto font = painter.font();
        font.setBold(true);
        font.setPointSize(23);
        painter.setFont(font);
        painter.drawText(0, 30, "我是玩蛇haha");  
    }