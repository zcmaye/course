#include "switchbutton.h"

#include <QPropertyAnimation>
#include <QPainter>
#include <QMouseEvent>

/**
 * @brief 构造函数
 * @param parent 父控件指针
 */
SwitchButton::SwitchButton(QWidget* parent)
    : QWidget(parent)
    , m_checked(false)
    , m_slidePosition(0.0)
    , m_animation(new QPropertyAnimation(this, "slidePosition", this))
{
    init();
}

/**
 * @brief 析构函数
 */
SwitchButton::~SwitchButton()
{
}

/**
 * @brief 初始化控件参数
 * 设置默认的颜色和动画参数
 */
void SwitchButton::init()
{
    // 轨道和滑块尺寸在paintEvent中根据控件实际大小动态计算
    // 这里只设置颜色
    m_trackColorOff = QColor(204, 204, 204);  // 关闭状态：灰色
    m_trackColorOn = QColor(52, 199, 89);     // 开启状态：绿色（iOS风格）
    m_thumbColorOff = QColor(255, 255, 255);  // 关闭状态：白色
    m_thumbColorOn = QColor(255, 255, 255);   // 开启状态：白色
    m_textOff = "关闭";
    m_textOn = "打开";
    m_textColorOff = Qt::white;
    m_textColorOn = Qt::black;

    // 配置动画参数
    m_animation->setDuration(200);              // 动画持续时间200毫秒
    m_animation->setEasingCurve(QEasingCurve::InOutQuad);  // 使用缓入缓出曲线

    // 设置最小尺寸，确保控件不会过小
    //setMinimumSize(52, 24);
}

/**
 * @brief 设置开关状态
 * @param checked true 为开启状态，false 为关闭状态
 *
 * 如果状态发生变化，会触发toggled信号和滑块动画
 */
void SwitchButton::setChecked(bool checked)
{
    // 如果状态未改变，则不进行任何操作
    if (m_checked == checked) {
        return;
    }

    // 更新状态
    m_checked = checked;

    // 触发滑块位置动画
    updateThumbPosition(checked);

    // 发出状态变化信号
    emit toggled(checked);
}

/**
 * @brief 设置滑块位置（供QPropertyAnimation调用）
 * @param position 位置值，范围0.0 ~ 1.0
 *
 * 这是一个setter方法，被Q_PROPERTY绑定，用于动画驱动滑块移动
 */
void SwitchButton::setSlidePosition(qreal position)
{
    m_slidePosition = position;
    // 触发重绘以更新滑块位置
    update();
}

/**
 * @brief 获取推荐的控件尺寸
 * @return QSize 推荐尺寸（52x24）
 */
QSize SwitchButton::sizeHint() const
{
    return QSize(52, 24);
}

/**
 * @brief 绘制事件处理
 * @param event 绘制事件
 *
 * 负责绘制开关的轨道和滑块，根据控件实际大小动态计算尺寸
 */
void SwitchButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 开启抗锯齿

    int w = width();   // 控件宽度
    int h = height();  // 控件高度

    // 根据控件高度动态计算轨道和滑块尺寸
    // 滑块略小于轨道高度，保持一定边距
    int trackHeight = h;
    int thumbSize = h - 4;  // 滑块比轨道高度小4像素
    if (thumbSize < 12) {
        thumbSize = 12;  // 确保滑块不会过小
    }

    // 根据当前状态选择颜色
    QColor trackColor = m_checked ? m_trackColorOn : m_trackColorOff;
    QColor thumbColor = m_checked ? m_thumbColorOn : m_thumbColorOff;

    // 1. 绘制轨道（背景）- 圆角矩形
    QRect trackRect(0, 0, w, h);
    painter.setBrush(trackColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(trackRect, trackHeight / 2.0, trackHeight / 2.0);

    // 2. 计算滑块位置
    // 根据m_slidePosition在水平方向上移动滑块
    int thumbX = (w - thumbSize) * m_slidePosition;
    int thumbY = (h - thumbSize) / 2;

    thumbX = qBound(1, thumbX, w - thumbSize - 1);  // 限制滑块位置在轨道范围内

    // 3. 绘制滑块（圆形按钮）
    QRect thumbRect(thumbX, thumbY, thumbSize, thumbSize);
    painter.setBrush(thumbColor);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(thumbRect);

    // 4. 绘制滑块阴影效果（可选，增加立体感）
    painter.setPen(QColor(0, 0, 0, 20));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(thumbRect.adjusted(1, 1, -1, -1));

    // 5. 绘制文字
    auto text = m_checked ? m_textOn : m_textOff;
    painter.setPen(m_checked ? m_textColorOn : m_textColorOff);
    painter.drawText(rect(), text, QTextOption(Qt::AlignCenter));
}

/**
 * @brief 鼠标按下事件处理
 * @param event 鼠标事件
 *
 * 捕获左键点击事件，防止事件传递给父控件
 */
void SwitchButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        event->accept();  // 接受事件，防止冒泡
    }
}

/**
 * @brief 鼠标释放事件处理
 * @param event 鼠标事件
 *
 * 在鼠标释放时切换开关状态
 */
void SwitchButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        // 切换状态（开启变关闭，关闭变开启）
        setChecked(!m_checked);
    }
}

/**
 * @brief 更新滑块位置（带动画效果）
 * @param checked 目标状态，true为最右侧，false为最左侧
 *
 * 使用QPropertyAnimation实现平滑的滑块移动动画
 */
void SwitchButton::updateThumbPosition(bool checked)
{
    // 先停止当前正在进行的动画
    m_animation->stop();

    // 设置动画起始位置（当前位置）
    m_animation->setStartValue(m_slidePosition);

    // 设置动画结束位置
    // checked为true时滑块移动到最右侧（1.0），否则移动到最左侧（0.0）
    m_animation->setEndValue(checked ? 1.0 : 0.0);

    // 启动动画
    m_animation->start();
}
