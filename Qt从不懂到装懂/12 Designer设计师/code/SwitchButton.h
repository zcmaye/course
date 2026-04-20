#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QWidget>

#include <QtUiPlugin/QDesignerExportWidget>


class QPropertyAnimation;

/**
 * @brief SwitchButton - 自定义开关按钮控件
 *
 * 一个仿iOS风格的滑动开关按钮，支持以下功能：
 * - 点击切换开关状态
 * - 平滑的动画过渡效果
 * - 自定义颜色配置
 * - toggled信号用于状态变化回调
 */
class QDESIGNER_WIDGET_EXPORT SwitchButton : public QWidget
{
	Q_OBJECT

    // Qt元对象系统属性，用于动画绑定
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked)
    Q_PROPERTY(qreal slidePosition READ getSlidePosition WRITE setSlidePosition)
public:
    /**
     * @brief 构造函数
     * @param parent 父控件指针
     */
    explicit SwitchButton(QWidget* parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~SwitchButton();

    /**
     * @brief 获取当前开关状态
     * @return true 表示开启状态，false 表示关闭状态
     */
    bool isChecked() const { return m_checked; }

    /**
     * @brief 设置开关状态
     * @param checked true 为开启，false 为关闭
     */
    void setChecked(bool checked);

    /**
     * @brief 获取滑块当前位置（0.0 ~ 1.0）
     * @return 滑块位置值
     */
    qreal getSlidePosition() const { return m_slidePosition; }

    /**
     * @brief 设置滑块位置
     * @param position 位置值（0.0 ~ 1.0）
     */
    void setSlidePosition(qreal position);

    /**
     * @brief 获取推荐的控件尺寸
     * @return 推荐尺寸 QSize
     */
    QSize sizeHint() const override;

signals:
    /**
     * @brief 开关状态变化信号
     * @param checked 当前开关状态
     */
    void toggled(bool checked);

protected:
    /**
     * @brief 绘制事件处理
     * @param event 绘制事件
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * @brief 鼠标按下事件处理
     * @param event 鼠标事件
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * @brief 鼠标释放事件处理
     * @param event 鼠标事件
     */
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    /**
     * @brief 初始化控件参数
     */
    void init();

    /**
     * @brief 更新滑块位置（带动画）
     * @param checked 目标状态
     */
    void updateThumbPosition(bool checked);

private:
    bool m_checked;                    ///< 当前开关状态
    qreal m_slidePosition;             ///< 滑块当前位置（0.0 ~ 1.0）
    QPropertyAnimation* m_animation;   ///< 位置动画对象

    QColor m_trackColorOff;    ///< 轨道关闭颜色（灰色）
    QColor m_trackColorOn;     ///< 轨道开启颜色（绿色）
    QColor m_thumbColorOff;    ///< 滑块关闭颜色（白色）
    QColor m_thumbColorOn;     ///< 滑块开启颜色（白色）
    QString m_textOff;         ///< 滑块关闭文本（关闭）
    QString m_textOn;          ///< 滑块开启文本（打开）
    QColor m_textColorOff;    ///< 滑块关闭文本颜色（白色）
    QColor m_textColorOn;     ///< 滑块开启文本颜色（黑色）
};

#endif

