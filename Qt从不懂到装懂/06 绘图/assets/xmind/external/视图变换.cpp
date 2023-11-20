    void paintEvent(QPaintEvent* ev)
    {
        QPainter painter(this);

        QRect rect(0, 0, 100, 100);
        //painter.setViewport(rect);
        painter.setWindow(rect);

        //画线
        painter.setPen(QPen(Qt::DotLine));
        painter.drawLine(0, 0, 640, 480);
        //绘制文本
        auto font = painter.font();
        font.setBold(true);
        font.setPointSize(23);
        painter.setFont(font);
        painter.drawText(0, 30, "我是玩蛇haha");

        //绘制图片
        //掩码图和原图大小必须一致
        //掩码图白色区域为透明，黑色区域为绘制
        QBitmap mask("mask.jpg");
        QPixmap pix = QPixmap("snowball.jpg").scaled(mask.size());
        pix.setMask(mask);
        painter.drawPixmap(0, 0,pix );

        //取消视图变换
        painter.setViewTransformEnabled(false);
        //绘制一个参照的矩形
        painter.setPen(QPen(Qt::red,2,Qt::SolidLine));  
        painter.drawRect(rect);
        //绘制矩形的宽度和高度
        font = painter.font();
        font.setBold(true);
        font.setPointSize(15);
        painter.setFont(font);
        painter.drawText(0, 130, "w:100 h:100");    
    }